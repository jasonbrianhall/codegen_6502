#include <cstring>

#include "../Configuration.hpp"

#include "../Emulation/APU.hpp"
#include "../Emulation/Controller.hpp"
#include "../Emulation/PPU.hpp"

#include "SMBEngine.hpp"

#define DATA_STORAGE_OFFSET 0x8000 // Starting address for storing constant data

//---------------------------------------------------------------------
// Public interface
//---------------------------------------------------------------------

uint8_t i;
uint8_t d;
uint8_t b;
uint8_t v;

SMBEngine::SMBEngine(uint8_t* romImage) :
    a(*this, &registerA),
    x(*this, &registerX),
    y(*this, &registerY),
    s(*this, &registerS)
{
    apu = new APU();
    ppu = new PPU(*this);
    controller1 = new Controller();
    controller2 = new Controller();

    // CHR Location in ROM: Header (16 bytes) + 2 PRG pages (16k each)
    chr = (romImage + 16 + (16384 * 2));

    returnIndexStackTop = 0;
}

SMBEngine::~SMBEngine()
{
    delete apu;
    delete ppu;
    delete controller1;
    delete controller2;
}

void SMBEngine::audioCallback(uint8_t* stream, int length)
{
    apu->output(stream, length);
}

Controller& SMBEngine::getController1()
{
    return *controller1;
}

Controller& SMBEngine::getController2()
{
    return *controller2;
}

void SMBEngine::render(uint32_t* buffer)
{
    ppu->render(buffer);
}

void SMBEngine::reset()
{
    // Run the decompiled code for initialization
    code(0);
}

void SMBEngine::update()
{
    // Run the decompiled code for the NMI handler
    code(1);

    // Update the APU
    if (Configuration::getAudioEnabled())
    {
        apu->stepFrame();
    }
}

//---------------------------------------------------------------------
// Private methods
//---------------------------------------------------------------------

void SMBEngine::compare(uint8_t value1, uint8_t value2)
{
    uint8_t result = value1 - value2;
    c = (value1 >= value2);
    setZN(result);
}

void SMBEngine::bit(uint8_t value)
{
    n = (value & (1 << 7)) != 0;
    z = (registerA & value) == 0;
}

uint8_t* SMBEngine::getCHR()
{
    return chr;
}

uint8_t* SMBEngine::getDataPointer(uint16_t address)
{
    // Constant data
    if( address >= DATA_STORAGE_OFFSET )
    {
        return dataStorage + (address - DATA_STORAGE_OFFSET);
    }
    // RAM and Mirrors
    else if( address < 0x2000 )
    {
        return ram + (address & 0x7ff);
    }

    return nullptr;
}

MemoryAccess SMBEngine::getMemory(uint16_t address)
{
    uint8_t* dataPointer = getDataPointer(address);
    if( dataPointer != nullptr )
    {
        return MemoryAccess(*this, dataPointer);
    }
    else
    {
        return MemoryAccess(*this, readData(address));
    }
}

uint16_t SMBEngine::getMemoryWord(uint8_t address)
{
    return (uint16_t)readData(address) + ((uint16_t)(readData(address + 1)) << 8);
}

void SMBEngine::pha()
{
    writeData(0x100 | (uint16_t)registerS, registerA);
    registerS--;
}

int SMBEngine::popReturnIndex()
{
    return returnIndexStack[returnIndexStackTop--];
}

void SMBEngine::pushReturnIndex(int index)
{
    returnIndexStack[++returnIndexStackTop] = index;
}

uint8_t SMBEngine::readData(uint16_t address)
{
    // Constant data
    if( address >= DATA_STORAGE_OFFSET )
    {
        return dataStorage[address - DATA_STORAGE_OFFSET];
    }
    // RAM and Mirrors
    else if( address < 0x2000 )
    {
        return ram[address & 0x7ff];
    }
    // PPU Registers and Mirrors
    else if( address < 0x4000 )
    {
        return ppu->readRegister(0x2000 + (address & 0x7));
    }
    // IO registers
    else if( address < 0x4020 )
    {
        switch (address)
        {
        case 0x4016:
            return controller1->readByte(PLAYER_1);
        case 0x4017:
            return controller1->readByte(PLAYER_2);
        }
    }

    return 0;
}

// Push processor status to stack
void SMBEngine::php() {
    // Construct status byte from individual flags
    uint8_t status = 0;
    if (c) status |= 0x01;  // Carry flag
    if (z) status |= 0x02;  // Zero flag
    if (i) status |= 0x04;  // Interrupt disable
    if (d) status |= 0x08;  // Decimal mode
    if (b) status |= 0x10;  // Break command
    status |= 0x20;         // Bit 5 is always set
    if (v) status |= 0x40;  // Overflow flag
    if (n) status |= 0x80;  // Negative flag
    
    writeData(0x100 | (uint16_t)registerS, status);
    registerS--;
}

// Pull processor status from stack
void SMBEngine::plp() {
    registerS++;
    uint8_t status = readData(0x100 | (uint16_t)registerS);
    
    // Unpack status byte into flags
    c = (status & 0x01) != 0;  // Carry flag
    z = (status & 0x02) != 0;  // Zero flag
    i = (status & 0x04) != 0;  // Interrupt disable
    d = (status & 0x08) != 0;  // Decimal mode
    b = (status & 0x10) != 0;  // Break command
    // Bit 5 is ignored
    v = (status & 0x40) != 0;  // Overflow flag
    n = (status & 0x80) != 0;  // Negative flag
}

void SMBEngine::setZN(uint8_t value)
{
    z = (value == 0);
    n = (value & (1 << 7)) != 0;
}

void SMBEngine::adc(uint8_t value)
{
    uint16_t result = registerA + value + (c ? 1 : 0);
    
    // Set overflow flag: overflow occurs if both operands have same sign
    // but result has different sign
    v = ((registerA ^ result) & (value ^ result) & 0x80) != 0;
    
    // Set carry flag if result > 255
    c = (result > 0xFF);
    
    // Update accumulator
    registerA = result & 0xFF;
    
    // Set N and Z flags based on result
    setZN(registerA);
}

// SBC - Subtract with Carry (actually subtract with borrow)
void SMBEngine::sbc(uint8_t value)
{
    // SBC is actually subtraction with borrow (inverse of carry)
    uint16_t result = registerA - value - (c ? 0 : 1);
    
    // Set overflow flag
    v = ((registerA ^ value) & (registerA ^ result) & 0x80) != 0;
    
    // Set carry flag (clear on borrow)
    c = (result < 0x100);
    
    // Update accumulator
    registerA = result & 0xFF;
    
    // Set N and Z flags
    setZN(registerA);
}

// ASL - Arithmetic Shift Left (Accumulator)
void SMBEngine::asl_acc()
{
    c = (registerA & 0x80) != 0;  // Carry = bit 7
    registerA = (registerA << 1) & 0xFF;
    setZN(registerA);
}

// ASL - Arithmetic Shift Left (Memory)
void SMBEngine::asl(uint16_t address)
{
    uint8_t value = readData(address);
    c = (value & 0x80) != 0;  // Carry = bit 7
    value = (value << 1) & 0xFF;
    writeData(address, value);
    setZN(value);
}

// LSR - Logical Shift Right (Accumulator)
void SMBEngine::lsr_acc()
{
    c = (registerA & 0x01) != 0;  // Carry = bit 0
    registerA = registerA >> 1;
    setZN(registerA);
}

// LSR - Logical Shift Right (Memory)
void SMBEngine::lsr(uint16_t address)
{
    uint8_t value = readData(address);
    c = (value & 0x01) != 0;  // Carry = bit 0
    value = value >> 1;
    writeData(address, value);
    setZN(value);
}

// ROL - Rotate Left (Accumulator)
void SMBEngine::rol_acc()
{
    bool oldCarry = c;
    c = (registerA & 0x80) != 0;  // New carry = bit 7
    registerA = ((registerA << 1) | (oldCarry ? 1 : 0)) & 0xFF;
    setZN(registerA);
}

// ROL - Rotate Left (Memory)
void SMBEngine::rol(uint16_t address)
{
    uint8_t value = readData(address);
    bool oldCarry = c;
    c = (value & 0x80) != 0;  // New carry = bit 7
    value = ((value << 1) | (oldCarry ? 1 : 0)) & 0xFF;
    writeData(address, value);
    setZN(value);
}

// ROR - Rotate Right (Accumulator)
void SMBEngine::ror_acc()
{
    bool oldCarry = c;
    c = (registerA & 0x01) != 0;  // New carry = bit 0
    registerA = (registerA >> 1) | (oldCarry ? 0x80 : 0);
    setZN(registerA);
}

// ROR - Rotate Right (Memory)
void SMBEngine::ror(uint16_t address)
{
    uint8_t value = readData(address);
    bool oldCarry = c;
    c = (value & 0x01) != 0;  // New carry = bit 0
    value = (value >> 1) | (oldCarry ? 0x80 : 0);
    writeData(address, value);
    setZN(value);
}

// Fix PLA to set flags (replace existing PLA function)
void SMBEngine::pla()
{
    registerS++;
    registerA = readData(0x100 | (uint16_t)registerS);
    setZN(registerA);  // PLA sets N and Z flags!
}

// Add setNZ as alias to setZN (or rename setZN to setNZ)
void SMBEngine::setNZ(uint8_t value)
{
    setZN(value);  // Just call the existing function
}


void SMBEngine::writeData(uint16_t address, uint8_t value)
{
    // RAM and Mirrors
    if( address < 0x2000 )
    {
        ram[address & 0x7ff] = value;
    }
    // PPU Registers and Mirrors
    else if( address < 0x4000 )
    {
        ppu->writeRegister(0x2000 + (address & 0x7), value);
    }
    // IO registers
    else if( address < 0x4020 )
    {
        switch( address )
        {
        case 0x4014:
            ppu->writeDMA(value);
            break;
        case 0x4016:
            controller1->writeByte(value);
            break;
        default:
            apu->writeRegister(address, value);
            break;
        }
    }
}

void SMBEngine::inc(uint16_t address)
{
    uint8_t value = readData(address);
    value = (value + 1) & 0xFF;
    writeData(address, value);
    setZN(value);
}

// DEC - Decrement Memory  
void SMBEngine::dec(uint16_t address)
{
    uint8_t value = readData(address);
    value = (value - 1) & 0xFF;
    writeData(address, value);
    setZN(value);
}

void SMBEngine::writeData(uint16_t address, const uint8_t* data, size_t length)
{
    address -= DATA_STORAGE_OFFSET;

    memcpy(dataStorage + (std::ptrdiff_t)address, data, length);
}
