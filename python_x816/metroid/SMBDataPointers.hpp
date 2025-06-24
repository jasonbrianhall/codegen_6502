// This is an automatically generated file.
// Do not edit directly.
//
#ifndef SMBDATAPOINTERS_HPP
#define SMBDATAPOINTERS_HPP

// Data Addresses (16-bit pointers) for Constants
//
struct SMBDataPointers
{
    uint16_t GFXInfo_ptr;
    uint16_t DataDisplay_ptr;
    uint16_t LEC00_ptr;
    uint16_t TileBlastAnim_ptr;
    uint16_t freeSpaceAddress;

    SMBDataPointers()
    {
        this->GFXInfo_ptr = 0x8000;
        this->DataDisplay_ptr = 0x8001;
        this->LEC00_ptr = 0x8029;
        this->TileBlastAnim_ptr = 0x802d;
        this->freeSpaceAddress = 0x8057;
    }
};

// Defines for quick access of the addresses within SMBDataPointers
//

#define GFXInfo (dataPointers.GFXInfo_ptr)
#define DataDisplay (dataPointers.DataDisplay_ptr)
#define LEC00 (dataPointers.LEC00_ptr)
#define TileBlastAnim (dataPointers.TileBlastAnim_ptr)

#endif // SMBDATAPOINTERS_HPP
