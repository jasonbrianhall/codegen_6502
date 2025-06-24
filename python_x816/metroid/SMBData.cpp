// This is an automatically generated file.
// Do not edit directly.
//
#include "SMB.hpp"

void SMBEngine::loadConstantData()
{
    // BankInitTable
    //
    const uint8_t BankInitTable_data[] = {
        
        
        
        
        
        
        
        
            // GFXInfo
    //
    const uint8_t GFXInfo_data[] = {
        0x06
    };
    writeData(GFXInfo, GFXInfo_data, sizeof(GFXInfo_data));

    // DataDisplay
    //
    const uint8_t DataDisplay_data[] = {
        0x21, 0xA0, 0x01, 0x30, //  Upper health digit
        0x21, 0xA0, 0x01, 0x38, //  Lower health digit
        0x2B, 0xFF, 0x01, 0x28, //  Upper missile digit
        0x2B, 0xFF, 0x01, 0x30, //  Middle missile digit
        0x2B, 0xFF, 0x01, 0x38, //  Lower missile digit
        0x2B, 0x5E, 0x00, 0x18, //  Left half of missile
        0x2B, 0x5F, 0x00, 0x20, //  Right half of missile
        0x21, 0x76, 0x01, 0x18, //  E
        0x21, 0x7F, 0x01, 0x20, //  N
        0x21, 0x3A, 0x00, 0x28 //  ..
    };
    writeData(DataDisplay, DataDisplay_data, sizeof(DataDisplay_data));

    // LEC00
    //
    const uint8_t LEC00_data[] = {
        0x80,
        0xB0,
        0xA0,
        0x90
    };
    writeData(LEC00, LEC00_data, sizeof(LEC00_data));

    // TileBlastAnim
    //
    const uint8_t TileBlastAnim_data[] = {
        0x06, 0x07, 0x00, 0xFE,
        0x07, 0x06, 0x01, 0xFE,
        0x07, 0x06, 0x02, 0xFE,
        0x07, 0x06, 0x03, 0xFE,
        0x07, 0x06, 0x04, 0xFE,
        0x07, 0x06, 0x05, 0xFE,
        0x07, 0x06, 0x09, 0xFE,
        0x07, 0x06, 0x0A, 0xFE,
        0x07, 0x06, 0x0B, 0xFE,
        0x07, 0x06, 0x08, 0xFE,
        0x00,
        0x00
    };
    writeData(TileBlastAnim, TileBlastAnim_data, sizeof(TileBlastAnim_data));

}

