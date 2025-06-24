// This is an automatically generated file.
// Do not edit directly.
//
#ifndef SMBDATAPOINTERS_HPP
#define SMBDATAPOINTERS_HPP

// Data Addresses (16-bit pointers) for Constants
//
struct SMBDataPointers
{
    uint16_t data_cafa_ptr;
    uint16_t data_cc4f_ptr;
    uint16_t data_ce4d_ptr;
    uint16_t data_dabd_ptr;
    uint16_t data_e533_ptr;
    uint16_t data_e5eb_ptr;
    uint16_t data_eb31_ptr;
    uint16_t data_ec39_ptr;
    uint16_t data_f301_ptr;
    uint16_t data_f3e1_ptr;
    uint16_t data_f731_ptr;
    uint16_t data_f761_ptr;
    uint16_t data_f91b_ptr;
    uint16_t data_f960_ptr;
    uint16_t data_f9f7_ptr;
    uint16_t freeSpaceAddress;

    SMBDataPointers()
    {
        this->data_cafa_ptr = 0x8000;
        this->data_cc4f_ptr = 0x8155;
        this->data_ce4d_ptr = 0x819a;
        this->data_dabd_ptr = 0x8307;
        this->data_e533_ptr = 0x8d7c;
        this->data_e5eb_ptr = 0x8e28;
        this->data_eb31_ptr = 0x936d;
        this->data_ec39_ptr = 0x943e;
        this->data_f301_ptr = 0x9b05;
        this->data_f3e1_ptr = 0x9b54;
        this->data_f731_ptr = 0x9b82;
        this->data_f761_ptr = 0x9bb2;
        this->data_f91b_ptr = 0x9be2;
        this->data_f960_ptr = 0x9c27;
        this->data_f9f7_ptr = 0x9cbe;
        this->freeSpaceAddress = 0xa1df;
    }
};

// Defines for quick access of the addresses within SMBDataPointers
//

#define data_cafa (dataPointers.data_cafa_ptr)
#define data_cc4f (dataPointers.data_cc4f_ptr)
#define data_ce4d (dataPointers.data_ce4d_ptr)
#define data_dabd (dataPointers.data_dabd_ptr)
#define data_e533 (dataPointers.data_e533_ptr)
#define data_e5eb (dataPointers.data_e5eb_ptr)
#define data_eb31 (dataPointers.data_eb31_ptr)
#define data_ec39 (dataPointers.data_ec39_ptr)
#define data_f301 (dataPointers.data_f301_ptr)
#define data_f3e1 (dataPointers.data_f3e1_ptr)
#define data_f731 (dataPointers.data_f731_ptr)
#define data_f761 (dataPointers.data_f761_ptr)
#define data_f91b (dataPointers.data_f91b_ptr)
#define data_f960 (dataPointers.data_f960_ptr)
#define data_f9f7 (dataPointers.data_f9f7_ptr)

#endif // SMBDATAPOINTERS_HPP
