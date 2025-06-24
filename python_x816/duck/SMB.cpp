// This is an automatically generated file.
// Do not edit directly.
//
#include "SMB.hpp"

void SMBEngine::code(int mode)
{
    switch (mode)
    {
    case 0:
        loadConstantData();
        goto Reset;
    case 1:
        goto NMI;
    }


Reset:
    /* cld */ //  $C000  D8
    /* sei */ //  $C001  78

label_c002:
    a = M(PPU_STATUS); //  $C002  AD 02 20
    if (!n)
        goto label_c002; //  $C005  10 FB
    x = 0x00; //  $C007  A2 00
    writeData(PPU_CTRL, x); //  $C009  8E 00 20
    writeData(PPU_MASK, x); //  $C00C  8E 01 20
    --x; //  $C00F  CA
    s = x; //  $C010  9A
    x = M(var_05ec); //  $C011  AE EC 05
    y = 0x06; //  $C014  A0 06
    writeData(var_0001, y); //  $C016  84 01
    y = 0x00; //  $C018  A0 00
    writeData(var_0000, y); //  $C01A  84 00
    a = 0x00; //  $C01C  A9 00

label_c02c:
    writeData(var_05ec, x); //  $C02C  8E EC 05
    pushReturnIndex(0);
    goto func_c22b;
Return_0: //  $C02F  20 2B C2
    pushReturnIndex(1);
    goto func_c23b;
Return_1: //  $C032  20 3B C2
    y = 0x00; //  $C035  A0 00
    writeData(PPU_SCROLL, a); //  $C037  8D 05 20
    writeData(PPU_SCROLL, a); //  $C03A  8D 05 20
    y = 0x01; //  $C03D  A0 01
    writeData(var_0024, y); //  $C03F  84 24
    a = 0x0F; //  $C041  A9 0F
    writeData(APU_SND_CHN, a); //  $C043  8D 15 40
    pushReturnIndex(2);
    goto func_f581;
Return_2: //  $C046  20 81 F5
    a = 0x90; //  $C049  A9 90
    writeData(PPU_CTRL, a); //  $C04B  8D 00 20
    writeData(var_0008, a); //  $C04E  85 08
    a = 0x02; //  $C050  A9 02
    writeData(var_0009, a); //  $C052  85 09
    x = 0x0B; //  $C054  A2 0B

label_c061:
    a = M(var_0024); //  $C061  A5 24
    if (z)
        goto label_c06b; //  $C063  F0 06
    a = M(var_0026); //  $C065  A5 26
    compare(a, 0x01); //  $C067  C9 01
    if (!z)
        goto label_c06e; //  $C069  D0 03

label_c06b:
    pushReturnIndex(3);
    goto func_f56c;
Return_3: //  $C06B  20 6C F5

label_c06e:
    pushReturnIndex(4);
    goto func_c348;
Return_4: //  $C06E  20 48 C3
    pushReturnIndex(5);
    goto func_c284;
Return_5: //  $C071  20 84 C2
    pushReturnIndex(6);
    goto func_c0b3;
Return_6: //  $C074  20 B3 C0
    ++M(var_002f); //  $C077  E6 2F
    pushReturnIndex(7);
    goto func_c61e;
Return_7: //  $C079  20 1E C6

label_c07c:
    a = M(var_0020); //  $C07C  A5 20
    if (!z)
        goto label_c061; //  $C07E  D0 E1
    pushReturnIndex(8);
    goto func_c588;
Return_8: //  $C080  20 88 C5
    goto label_c07c; //  $C083  4C 7C C0

NMI:
    php(); //  $C086  08
    pha(); //  $C087  48
    a = x; //  $C088  8A
    pha(); //  $C089  48
    a = y; //  $C08A  98
    pha(); //  $C08B  48
    a = 0x00; //  $C08C  A9 00
    writeData(OAM_ADDR, a); //  $C08E  8D 03 20
    a = 0x02; //  $C091  A9 02
    writeData(OAM_DMA, a); //  $C093  8D 14 40
    a = M(var_0022); //  $C096  A5 22
    if (!z)
        goto label_c0a6; //  $C098  D0 0C
    pushReturnIndex(9);
    goto func_c2bf;
Return_9: //  $C09A  20 BF C2
    pushReturnIndex(10);
    goto func_c249;
Return_10: //  $C09D  20 49 C2
    pushReturnIndex(11);
    goto func_c263;
Return_11: //  $C0A0  20 63 C2
    pushReturnIndex(12);
    goto func_c3c1;
Return_12: //  $C0A3  20 C1 C3

label_c0a6:
    y = 0x01; //  $C0A6  A0 01
    writeData(var_0022, y); //  $C0A8  84 22
    writeData(var_0020, y); //  $C0AA  84 20
    pla(); //  $C0AC  68
    y = a; //  $C0AD  A8
    pla(); //  $C0AE  68
    x = a; //  $C0AF  AA
    pla(); //  $C0B0  68
    plp(); //  $C0B1  28
    return; //  $C0B2  40

func_c0b3:
    a = M(var_0024); //  $C0B3  A5 24
    if (z)
        goto label_c0ba; //  $C0B5  F0 03
    goto label_c14e; //  $C0B7  4C 4E C1

label_c0ba:
    a = M(var_0016); //  $C0BA  A5 16
    a &= 0x10; //  $C0BC  29 10
    if (z)
        goto label_c11e; //  $C0BE  F0 5E
    y = M(var_05fc); //  $C0C0  AC FC 05
    if (!z)
        goto label_c123; //  $C0C3  D0 5E
    ++y; //  $C0C5  C8
    writeData(var_05fc, y); //  $C0C6  8C FC 05
    y = M(var_0025); //  $C0C9  A4 25
    compare(y, 0x10); //  $C0CB  C0 10
    if (z)
        goto label_c0ff; //  $C0CD  F0 30
    compare(y, 0x03); //  $C0CF  C0 03
    if (z)
        goto label_c0df; //  $C0D1  F0 0C
    compare(y, 0x04); //  $C0D3  C0 04
    if (z)
        goto label_c0df; //  $C0D5  F0 08
    compare(y, 0x0B); //  $C0D7  C0 0B
    if (z)
        goto label_c0df; //  $C0D9  F0 04
    compare(y, 0x0C); //  $C0DB  C0 0C
    if (!z)
        goto label_c123; //  $C0DD  D0 44

label_c0df:
    x = 0x05; //  $C0DF  A2 05

label_c0ff:
    a = M(var_0009); //  $C0FF  A5 09
    a |= 0x10; //  $C101  09 10
    writeData(PPU_MASK, a); //  $C103  8D 01 20
    writeData(var_0009, a); //  $C106  85 09
    a = 0x11; //  $C108  A9 11
    writeData(var_0025, a); //  $C10A  85 25
    a = 0x30; //  $C10C  A9 30
    writeData(var_001c, a); //  $C10E  85 1C
    a = 0x00; //  $C110  A9 00

label_c112:
    pushReturnIndex(13);
    goto func_d464;
Return_13: //  $C112  20 64 D4
    pushReturnIndex(14);
    goto func_d4e2;
Return_14: //  $C115  20 E2 D4
    pushReturnIndex(15);
    goto func_c5d9;
Return_15: //  $C118  20 D9 C5
    goto label_d521; //  $C11B  4C 21 D5

label_c11e:
    a = 0x00; //  $C11E  A9 00
    writeData(var_05fc, a); //  $C120  8D FC 05

label_c123:
    a = M(var_0025); //  $C123  A5 25
    pushReturnIndex(16);
    goto jump_engine_c35e;
Return_16: //  $C125  20 5E C3

label_c14e:
    a = 0x00; //  $C14E  A9 00
    writeData(var_05ff, a); //  $C150  8D FF 05
    a = 0x01; //  $C153  A9 01
    writeData(var_00b9, a); //  $C155  85 B9
    writeData(var_00ba, a); //  $C157  85 BA
    a = M(var_0026); //  $C159  A5 26
    if (z)
        goto label_c18d; //  $C15B  F0 30
    pushReturnIndex(17);
    goto func_d131;
Return_17: //  $C15D  20 31 D1
    pushReturnIndex(18);
    goto func_d160;
Return_18: //  $C160  20 60 D1
    a = M(var_05ff); //  $C163  AD FF 05
    compare(a, 0x01); //  $C166  C9 01
    if (z)
        goto label_c176; //  $C168  F0 0C
    compare(a, 0x02); //  $C16A  C9 02
    if (z)
        goto label_c199; //  $C16C  F0 2B
    a = M(var_0016); //  $C16E  A5 16
    a &= 0x30; //  $C170  29 30
    compare(a, 0x10); //  $C172  C9 10
    if (!z)
        goto label_c189; //  $C174  D0 13

label_c176:
    a = 0x00; //  $C176  A9 00
    writeData(var_0024, a); //  $C178  85 24
    writeData(var_0025, a); //  $C17A  85 25
    pushReturnIndex(19);
    goto func_d4e2;
Return_19: //  $C17C  20 E2 D4
    pushReturnIndex(20);
    goto func_c5e1;
Return_20: //  $C17F  20 E1 C5
    a = 0x02; //  $C182  A9 02
    writeData(var_002a, a); //  $C184  85 2A
    writeData(var_002d, a); //  $C186  85 2D
    goto Return; //  $C188  60

//------------------------------------------------------------------------

label_c189:
    x = M(var_0026); //  $C189  A6 26
    if (!z)
        goto label_c190; //  $C18B  D0 03

label_c18d:
    goto label_c217; //  $C18D  4C 17 C2

label_c190:
    compare(a, 0x20); //  $C190  C9 20
    if (!z)
        goto label_c1a9; //  $C192  D0 15
    a = M(var_05fd); //  $C194  AD FD 05
    if (!z)
        goto label_c1b7; //  $C197  D0 1E

label_c199:
    y = M(var_05fe); //  $C199  AC FE 05
    ++y; //  $C19C  C8
    compare(y, 0x03); //  $C19D  C0 03
    if (!z)
        goto label_c1a3; //  $C19F  D0 02
    y = 0x00; //  $C1A1  A0 00

label_c1a3:
    writeData(var_05fe, y); //  $C1A3  8C FE 05
    goto label_c1b2; //  $C1A6  4C B2 C1

label_c1a9:
    compare(a, 0x00); //  $C1A9  C9 00
    if (!z)
        goto label_c1b2; //  $C1AB  D0 05
    writeData(var_05fd, a); //  $C1AD  8D FD 05
    if (z)
        goto label_c1bb; //  $C1B0  F0 09

label_c1b2:
    a = 0x01; //  $C1B2  A9 01
    writeData(var_05fd, a); //  $C1B4  8D FD 05

label_c1b7:
    a = 0xFF; //  $C1B7  A9 FF
    writeData(var_002d, a); //  $C1B9  85 2D

label_c1bb:
    compare(x, 0x01); //  $C1BB  E0 01
    if (!z)
        goto label_c217; //  $C1BD  D0 58
    a = 0x51; //  $C1BF  A9 51
    writeData(var_0500, a); //  $C1C1  8D 00 05
    a = 0x24; //  $C1C4  A9 24
    x = 0x04; //  $C1C6  A2 04

label_c20b:
    a = 0x16; //  $C20B  A9 16
    writeData(var_0500, a); //  $C20D  8D 00 05
    x = 0x12; //  $C210  A2 12
    y = 0x23; //  $C212  A0 23
    pushReturnIndex(21);
    goto func_c71d;
Return_21: //  $C214  20 1D C7

label_c217:
    a = M(var_002d); //  $C217  A5 2D
    if (!z)
        goto label_c222; //  $C219  D0 07
    pushReturnIndex(22);
    goto func_d509;
Return_22: //  $C21B  20 09 D5
    a = 0xFF; //  $C21E  A9 FF
    writeData(var_002d, a); //  $C220  85 2D

label_c222:
    a = M(var_0026); //  $C222  A5 26
    pushReturnIndex(23);
    goto jump_engine_c35e;
Return_23: //  $C224  20 5E C3

func_c22b:
    a = 0x02; //  $C22B  A9 02
    pushReturnIndex(24);
    goto func_c232;
Return_24: //  $C22D  20 32 C2

func_c230:
    a = 0x01; //  $C230  A9 01

func_c232:
    writeData(var_0001, a); //  $C232  85 01
    a = 0x24; //  $C234  A9 24
    writeData(var_0000, a); //  $C236  85 00
    goto func_c303; //  $C238  4C 03 C3

func_c23b:
    y = 0x00; //  $C23B  A0 00
    a = 0xF4; //  $C23D  A9 F4

label_c25b:
    writeData(var_0000, a); //  $C25B  85 00
    writeData(var_0001, x); //  $C25D  86 01
    pushReturnIndex(25);
    goto func_c3b8;
Return_25: //  $C25F  20 B8 C3

label_c262:
    goto Return; //  $C262  60

//------------------------------------------------------------------------

func_c263:
    y = M(var_0027); //  $C263  A4 27
    if (z)
        goto label_c262; //  $C265  F0 FB
    y = 0x00; //  $C267  A0 00
    writeData(var_0027, y); //  $C269  84 27
    a = 0x00; //  $C26B  A9 00
    x = 0x04; //  $C26D  A2 04
    if (!z)
        goto label_c25b; //  $C26F  D0 EA

label_c271:
    --M(var_001c); //  $C271  C6 1C
    if (!z)
        goto label_c283; //  $C273  D0 0E
    x = 0x05; //  $C275  A2 05

label_c283:
    goto Return; //  $C283  60

//------------------------------------------------------------------------

func_c284:
    x = 0x01; //  $C284  A2 01
    writeData(JOYPAD1, x); //  $C286  8E 16 40
    --x; //  $C289  CA
    writeData(JOYPAD1, x); //  $C28A  8E 16 40
    pushReturnIndex(26);
    goto func_c291;
Return_26: //  $C28D  20 91 C2
    ++x; //  $C290  E8

func_c291:
    y = 0x08; //  $C291  A0 08

label_c2be:
    goto Return; //  $C2BE  60

//------------------------------------------------------------------------

func_c2bf:
    a = M(var_0021); //  $C2BF  A5 21
    if (z)
        goto label_c302; //  $C2C1  F0 3F
    a = 0x61; //  $C2C3  A9 61
    writeData(var_0000, a); //  $C2C5  85 00
    a = 0x05; //  $C2C7  A9 05
    writeData(var_0001, a); //  $C2C9  85 01
    a = M(var_0008); //  $C2CB  A5 08
    a &= 0xFB; //  $C2CD  29 FB
    writeData(PPU_CTRL, a); //  $C2CF  8D 00 20
    writeData(var_0008, a); //  $C2D2  85 08
    x = M(PPU_STATUS); //  $C2D4  AE 02 20
    y = 0x00; //  $C2D7  A0 00
    if (z)
        goto label_c2f4; //  $C2D9  F0 19

label_c302:
    goto Return; //  $C302  60

//------------------------------------------------------------------------

func_c303:
    a = M(PPU_STATUS); //  $C303  AD 02 20

data_c306:
    a = M(var_0008); //  $C306  A5 08
    a &= 0xFB; //  $C308  29 FB
    writeData(PPU_CTRL, a); //  $C30A  8D 00 20
    writeData(var_0008, a); //  $C30D  85 08
    a = 0x1C; //  $C30F  A9 1C
    c = 0; //  $C311  18

label_c312:
    a += 0x04; //  $C312  69 04
    --M(var_0001); //  $C314  C6 01
    if (!z)
        goto label_c312; //  $C316  D0 FA
    writeData(var_0002, a); //  $C318  85 02
    writeData(PPU_ADDR, a); //  $C31A  8D 06 20
    a = 0x00; //  $C31D  A9 00
    writeData(PPU_ADDR, a); //  $C31F  8D 06 20
    x = 0x04; //  $C322  A2 04
    y = 0x00; //  $C324  A0 00
    a = M(var_0000); //  $C326  A5 00

label_c328:
    writeData(PPU_DATA, a); //  $C328  8D 07 20
    --y; //  $C32B  88
    if (!z)
        goto label_c328; //  $C32C  D0 FA
    --x; //  $C32E  CA
    if (!z)
        goto label_c328; //  $C32F  D0 F7
    a = M(var_0002); //  $C331  A5 02
    a += 0x03; //  $C333  69 03
    writeData(PPU_ADDR, a); //  $C335  8D 06 20
    a = 0xC0; //  $C338  A9 C0
    writeData(PPU_ADDR, a); //  $C33A  8D 06 20
    y = 0x40; //  $C33D  A0 40
    a = 0x00; //  $C33F  A9 00

label_c341:
    writeData(PPU_DATA, a); //  $C341  8D 07 20
    --y; //  $C344  88
    if (!z)
        goto label_c341; //  $C345  D0 FA
    goto Return; //  $C347  60

//------------------------------------------------------------------------

func_c348:
    x = 0x01; //  $C348  A2 01
    --M(var_002a); //  $C34A  C6 2A
    if (!n)
        goto label_c354; //  $C34C  10 06
    a = 0x0A; //  $C34E  A9 0A
    writeData(var_002a, a); //  $C350  85 2A
    x = 0x03; //  $C352  A2 03

label_c35a:
    --x; //  $C35A  CA
    if (!n)
        goto label_c354; //  $C35B  10 F7
    goto Return; //  $C35D  60

//------------------------------------------------------------------------

label_c392:
    writeData(PPU_CTRL, a); //  $C392  8D 00 20
    writeData(var_0008, a); //  $C395  85 08
    pla(); //  $C397  68
    M(a) <<= 1; //  $C398  0A
    if (!c)
        goto label_c39e; //  $C399  90 03
    a |= 0x02; //  $C39B  09 02
    ++y; //  $C39D  C8

label_c39e:
    M(a) >>= 1; //  $C39E  4A
    M(a) >>= 1; //  $C39F  4A
    x = a; //  $C3A0  AA

label_c3a1:
    if (c)
        goto label_c3a4; //  $C3A1  B0 01
    ++y; //  $C3A3  C8

func_c3c1:
    pha(); //  $C3C1  48
    a = M(var_000a); //  $C3C2  A5 0A
    writeData(PPU_SCROLL, a); //  $C3C4  8D 05 20
    a = M(0x0B); //  $C3C7  A5 0B
    writeData(PPU_SCROLL, a); //  $C3C9  8D 05 20
    pla(); //  $C3CC  68
    goto Return; //  $C3CD  60

//------------------------------------------------------------------------

label_c436:
    goto Return; //  $C436  60

//------------------------------------------------------------------------

func_c4bf:
    pushReturnIndex(27);
    goto func_c502;
Return_27: //  $C4BF  20 02 C5
    a += M(var_0001); //  $C4C2  65 01
    compare(a, 0x0A); //  $C4C4  C9 0A
    if (!c)
        goto label_c4ca; //  $C4C6  90 02
    a += 0x05; //  $C4C8  69 05

label_c4ca:
    c = 0; //  $C4CA  18
    a += M(var_0002); //  $C4CB  65 02
    writeData(var_0002, a); //  $C4CD  85 02
    a = M(var_0003); //  $C4CF  A5 03
    a &= 0xF0; //  $C4D1  29 F0
    a += M(var_0002); //  $C4D3  65 02
    if (!c)
        goto label_c4db; //  $C4D5  90 04

label_c4d7:
    a += 0x5F; //  $C4D7  69 5F
    c = 1; //  $C4D9  38
    goto Return; //  $C4DA  60

//------------------------------------------------------------------------

label_c4db:
    compare(a, 0xA0); //  $C4DB  C9 A0
    if (c)
        goto label_c4d7; //  $C4DD  B0 F8
    goto Return; //  $C4DF  60

//------------------------------------------------------------------------

func_c4e0:
    pushReturnIndex(28);
    goto func_c502;
Return_28: //  $C4E0  20 02 C5
    a -= M(var_0001); //  $C4E3  E5 01
    writeData(var_0001, a); //  $C4E5  85 01
    if (c)
        goto label_c4f3; //  $C4E7  B0 0A
    a += 0x0A; //  $C4E9  69 0A
    writeData(var_0001, a); //  $C4EB  85 01
    a = M(var_0002); //  $C4ED  A5 02
    a += 0x0F; //  $C4EF  69 0F
    writeData(var_0002, a); //  $C4F1  85 02

label_c4f3:
    a = M(var_0003); //  $C4F3  A5 03
    a &= 0xF0; //  $C4F5  29 F0
    c = 1; //  $C4F7  38
    a -= M(var_0002); //  $C4F8  E5 02
    if (c)
        goto label_c4ff; //  $C4FA  B0 03
    a += 0xA0; //  $C4FC  69 A0
    c = 0; //  $C4FE  18

label_c4ff:
    a |= M(var_0001); //  $C4FF  05 01
    goto Return; //  $C501  60

//------------------------------------------------------------------------

func_c502:
    pha(); //  $C502  48
    a &= 0x0F; //  $C503  29 0F
    writeData(var_0001, a); //  $C505  85 01
    pla(); //  $C507  68
    a &= 0xF0; //  $C508  29 F0
    writeData(var_0002, a); //  $C50A  85 02
    a = M(var_0003); //  $C50C  A5 03
    a &= 0x0F; //  $C50E  29 0F
    goto Return; //  $C510  60

//------------------------------------------------------------------------

func_c511:
    a = 0x00; //  $C511  A9 00
    writeData(var_0004, a); //  $C513  85 04
    c = 0; //  $C515  18
    a = M(var_0000); //  $C516  A5 00
    a += 0x10; //  $C518  69 10
    a &= 0xF0; //  $C51A  29 F0
    M(a) >>= 1; //  $C51C  4A
    M(a) >>= 1; //  $C51D  4A
    y = a; //  $C51E  A8
    a = M(var_0000); //  $C51F  A5 00
    a &= 0x07; //  $C521  29 07
    M(a) <<= 1; //  $C523  0A
    M(a) <<= 1; //  $C524  0A
    x = a; //  $C525  AA

label_c555:
    a = 0xFF; //  $C555  A9 FF
    writeData(var_0004, a); //  $C557  85 04
    c = 1; //  $C559  38

label_c56f:
    a = M(var_0000); //  $C56F  A5 00
    a &= 0x08; //  $C571  29 08
    if (z)
        goto label_c57b; //  $C573  F0 06
    --x; //  $C575  CA
    --x; //  $C576  CA
    --x; //  $C577  CA
    --x; //  $C578  CA
    if (!n)
        goto label_c526; //  $C579  10 AB

label_c57b:
    goto Return; //  $C57B  60

//------------------------------------------------------------------------

label_c585:
    c = 0; //  $C585  18
    if (!c)
        goto label_c55a; //  $C586  90 D2

func_c588:
    a = M(var_05ec); //  $C588  AD EC 05
    a &= 0x02; //  $C58B  29 02
    writeData(var_0007, a); //  $C58D  85 07
    a = M(var_05ed); //  $C58F  AD ED 05
    a &= 0x02; //  $C592  29 02
    a ^= M(var_0007); //  $C594  45 07
    c = 0; //  $C596  18
    if (z)
        goto label_c59a; //  $C597  F0 01
    c = 1; //  $C599  38

label_c59a:
    M(var_05ec).ror(); //  $C59A  6E EC 05
    M(var_05ed).ror(); //  $C59D  6E ED 05
    M(var_05ee).ror(); //  $C5A0  6E EE 05
    M(var_05ef).ror(); //  $C5A3  6E EF 05
    a = M(var_05ec); //  $C5A6  AD EC 05
    goto Return; //  $C5A9  60

//------------------------------------------------------------------------

label_c5aa:
    pushReturnIndex(29);
    goto func_c5e1;
Return_29: //  $C5AA  20 E1 C5
    pushReturnIndex(30);
    goto func_c230;
Return_30: //  $C5AD  20 30 C2
    pushReturnIndex(31);
    goto func_c5d9;
Return_31: //  $C5B0  20 D9 C5
    a = 0x02; //  $C5B3  A9 02
    writeData(var_0001, a); //  $C5B5  85 01
    a = 0x50; //  $C5B7  A9 50
    writeData(var_0000, a); //  $C5B9  85 00
    pushReturnIndex(32);
    goto func_c303;
Return_32: //  $C5BB  20 03 C3
    pushReturnIndex(33);
    goto func_c23b;
Return_33: //  $C5BE  20 3B C2
    pushReturnIndex(34);
    goto func_c5d9;
Return_34: //  $C5C1  20 D9 C5
    x = 0x04; //  $C5C4  A2 04
    y = 0xE4; //  $C5C6  A0 E4
    pushReturnIndex(35);
    goto func_c617;
Return_35: //  $C5C8  20 17 C6
    a = 0x01; //  $C5CB  A9 01
    writeData(var_0023, a); //  $C5CD  85 23
    a = 0x01; //  $C5CF  A9 01
    writeData(var_05fd, a); //  $C5D1  8D FD 05
    ++M(var_0026); //  $C5D4  E6 26
    goto func_c5ee; //  $C5D6  4C EE C5

func_c5d9:
    pushReturnIndex(36);
    goto func_c61e;
Return_36: //  $C5D9  20 1E C6

label_c5dc:
    a = M(var_0020); //  $C5DC  A5 20
    if (z)
        goto label_c5dc; //  $C5DE  F0 FC

label_c5e0:
    goto Return; //  $C5E0  60

//------------------------------------------------------------------------

func_c5e1:
    pushReturnIndex(37);
    goto func_c5d9;
Return_37: //  $C5E1  20 D9 C5
    a = M(var_0009); //  $C5E4  A5 09
    a &= 0xE7; //  $C5E6  29 E7

label_c5e8:
    writeData(var_0009, a); //  $C5E8  85 09
    writeData(PPU_MASK, a); //  $C5EA  8D 01 20
    goto Return; //  $C5ED  60

//------------------------------------------------------------------------

func_c5ee:
    pushReturnIndex(38);
    goto func_c5d9;
Return_38: //  $C5EE  20 D9 C5
    a = M(var_0009); //  $C5F1  A5 09
    a |= 0x18; //  $C5F3  09 18
    if (!z)
        goto label_c5e8; //  $C5F5  D0 F1

func_c5f7:
    writeData(var_00a2, y); //  $C5F7  84 A2
    x = 0x00; //  $C5F9  A2 00

func_c607:
    y = M(var_00a2); //  $C607  A4 A2
    x = 0x00; //  $C609  A2 00

func_c617:
    writeData(var_0000, x); //  $C617  86 00
    writeData(var_0001, y); //  $C619  84 01
    goto func_c3b8; //  $C61B  4C B8 C3

func_c61e:
    a = 0x00; //  $C61E  A9 00
    writeData(var_0020, a); //  $C620  85 20
    writeData(var_0022, a); //  $C622  85 22
    goto Return; //  $C624  60

//------------------------------------------------------------------------

label_c625:
    a = M(var_002d); //  $C625  A5 2D
    if (!z)
        goto label_c62d; //  $C627  D0 04
    a = M(0x1E); //  $C629  A5 1E
    writeData(var_0025, a); //  $C62B  85 25

label_c62d:
    goto Return; //  $C62D  60

//------------------------------------------------------------------------

label_c637:
    y = 0x00; //  $C637  A0 00
    a = y; //  $C639  98

func_c641:
    a = 0x00; //  $C641  A9 00
    x = 0x30; //  $C643  A2 30

func_c64b:
    a = 0x00; //  $C64B  A9 00
    x = 0x7F; //  $C64D  A2 7F

label_c694:
    goto Return; //  $C694  60

//------------------------------------------------------------------------

label_c695:
    c = 0; //  $C695  18
    a += M(var_00b1); //  $C696  65 B1
    compare(a, 0xA8); //  $C698  C9 A8
    if (!c)
        goto label_c69e; //  $C69A  90 02
    a = 0xF4; //  $C69C  A9 F4

func_c6c4:
    a = M(var_00ad); //  $C6C4  A5 AD
    if (z)
        goto label_c694; //  $C6C6  F0 CC
    a = 0x00; //  $C6C8  A9 00
    writeData(var_00ad, a); //  $C6CA  85 AD

func_c6cc:
    a = 0xD6; //  $C6CC  A9 D6
    y = M(var_001f); //  $C6CE  A4 1F
    compare(y, 0x02); //  $C6D0  C0 02
    if (!z)
        goto label_c6d6; //  $C6D2  D0 02
    a = 0xD4; //  $C6D4  A9 D4

label_c6d6:
    writeData(var_000c, a); //  $C6D6  85 0C
    x = 0x09; //  $C6D8  A2 09

func_c6f5:
    a = M(var_00be); //  $C6F5  A5 BE
    if (z)
        goto label_c694; //  $C6F7  F0 9B
    a = 0x00; //  $C6F9  A9 00
    writeData(var_00be, a); //  $C6FB  85 BE
    x = M(var_00ba); //  $C6FD  A6 BA
    y = 0x00; //  $C6FF  A0 00

label_c701:
    compare(x, 0x00); //  $C701  E0 00
    if (z)
        goto label_c70a; //  $C703  F0 05
    --x; //  $C705  CA
    a = 0xD9; //  $C706  A9 D9
    if (!z)
        goto label_c70c; //  $C708  D0 02

label_c70a:
    a = 0xB7; //  $C70A  A9 B7

func_c71d:
    writeData(var_0000, x); //  $C71D  86 00
    writeData(var_0001, y); //  $C71F  84 01
    x = 0x00; //  $C721  A2 00
    y = 0x05; //  $C723  A0 05
    writeData(var_0002, x); //  $C725  86 02
    writeData(var_0003, y); //  $C727  84 03
    goto label_c3ce; //  $C729  4C CE C3

label_c72c:
    a = M(var_002d); //  $C72C  A5 2D
    if (z)
        goto label_c73a; //  $C72E  F0 0A
    a = M(var_001f); //  $C730  A5 1F
    compare(a, 0x02); //  $C732  C9 02
    if (z)
        goto label_c739; //  $C734  F0 03
    goto func_cc94; //  $C736  4C 94 CC

label_c739:
    goto Return; //  $C739  60

//------------------------------------------------------------------------

label_c73a:
    x = 0x03; //  $C73A  A2 03

label_c779:
    pushReturnIndex(39);
    goto func_d50d;
Return_39: //  $C779  20 0D D5
    pushReturnIndex(40);
    goto func_c5d9;
Return_40: //  $C77C  20 D9 C5
    pushReturnIndex(41);
    goto func_d4fa;
Return_41: //  $C77F  20 FA D4
    a = 0x01; //  $C782  A9 01
    writeData(var_03a0, a); //  $C784  8D A0 03
    writeData(var_03a1, a); //  $C787  8D A1 03
    a = 0x07; //  $C78A  A9 07
    writeData(var_0025, a); //  $C78C  85 25
    a = 0x15; //  $C78E  A9 15
    writeData(var_002d, a); //  $C790  85 2D
    goto Return; //  $C792  60

//------------------------------------------------------------------------

func_c793:
    x = 0x0A; //  $C793  A2 0A

label_c795:
    compare(x, M(var_00ab)); //  $C795  E4 AB
    if (!c)
        goto label_c79f; //  $C797  90 06
    if (z)
        goto label_c79f; //  $C799  F0 04
    a = 0xB7; //  $C79B  A9 B7
    if (!z)
        goto label_c7a1; //  $C79D  D0 02

label_c79f:
    a = 0xD7; //  $C79F  A9 D7

func_c7b3:
    a = M(var_00c1); //  $C7B3  A5 C1
    writeData(var_0003, a); //  $C7B5  85 03
    a = 0x01; //  $C7B7  A9 01
    c = 0; //  $C7B9  18
    pushReturnIndex(42);
    goto func_c4bf;
Return_42: //  $C7BA  20 BF C4
    writeData(var_00c1, a); //  $C7BD  85 C1
    a = 0x12; //  $C7BF  A9 12
    writeData(var_0500, a); //  $C7C1  8D 00 05
    x = 0xDD; //  $C7C4  A2 DD
    a = M(var_001f); //  $C7C6  A5 1F
    compare(a, 0x02); //  $C7C8  C9 02
    if (z)
        goto label_c7ce; //  $C7CA  F0 02
    x = 0x50; //  $C7CC  A2 50

label_c7ef:
    a = M(var_009d); //  $C7EF  A5 9D
    if (z)
        goto label_c7f6; //  $C7F1  F0 03
    goto func_c7fb; //  $C7F3  4C FB C7

label_c7f6:
    a = 0x0A; //  $C7F6  A9 0A
    writeData(var_0025, a); //  $C7F8  85 25
    goto Return; //  $C7FA  60

//------------------------------------------------------------------------

label_c818:
    a = 0x00; //  $C818  A9 00
    writeData(var_009d, a); //  $C81A  85 9D

label_c81c:
    goto Return; //  $C81C  60

//------------------------------------------------------------------------

label_c81d:
    pushReturnIndex(43);
    goto func_c641;
Return_43: //  $C81D  20 41 C6
    pushReturnIndex(44);
    goto func_c5d9;
Return_44: //  $C820  20 D9 C5
    pushReturnIndex(45);
    goto func_c22b;
Return_45: //  $C823  20 2B C2
    pushReturnIndex(46);
    goto func_d4d9;
Return_46: //  $C826  20 D9 D4
    x = 0x01; //  $C829  A2 01
    a = M(var_05fe); //  $C82B  AD FE 05
    writeData(var_001f, a); //  $C82E  85 1F
    compare(a, 0x02); //  $C830  C9 02
    if (!c)
        goto label_c836; //  $C832  90 02
    x = 0x08; //  $C834  A2 08

label_c836:
    writeData(var_0025, x); //  $C836  86 25
    goto Return; //  $C838  60

//------------------------------------------------------------------------

label_c839:
    pushReturnIndex(47);
    goto func_c5d9;
Return_47: //  $C839  20 D9 C5
    x = 0x42; //  $C83C  A2 42
    y = 0xE0; //  $C83E  A0 E0
    pushReturnIndex(48);
    goto func_c617;
Return_48: //  $C840  20 17 C6
    a = 0x02; //  $C843  A9 02
    writeData(var_0023, a); //  $C845  85 23
    a = 0x02; //  $C847  A9 02
    writeData(var_0025, a); //  $C849  85 25
    pushReturnIndex(49);
    goto func_c3c1;
Return_49: //  $C84B  20 C1 C3
    pushReturnIndex(50);
    goto func_c5ee;
Return_50: //  $C84E  20 EE C5
    goto label_d515; //  $C851  4C 15 D5

label_c854:
    pushReturnIndex(51);
    goto func_d4d9;
Return_51: //  $C854  20 D9 D4
    pushReturnIndex(52);
    goto func_d2a4;
Return_52: //  $C857  20 A4 D2
    pushReturnIndex(53);
    goto func_c793;
Return_53: //  $C85A  20 93 C7
    pushReturnIndex(54);
    goto func_c7b3;
Return_54: //  $C85D  20 B3 C7
    ; // nop //  $C860  EA
    ; // nop //  $C861  EA
    ; // nop //  $C862  EA
    a = 0x00; //  $C863  A9 00
    writeData(var_00b5, a); //  $C865  85 B5
    writeData(var_009d, a); //  $C867  85 9D
    a = 0x03; //  $C869  A9 03
    writeData(var_0025, a); //  $C86B  85 25
    goto Return; //  $C86D  60

//------------------------------------------------------------------------

label_c86e:
    pushReturnIndex(55);
    goto func_d131;
Return_55: //  $C86E  20 31 D1
    pushReturnIndex(56);
    goto func_d160;
Return_56: //  $C871  20 60 D1
    pushReturnIndex(57);
    goto func_cc94;
Return_57: //  $C874  20 94 CC
    pushReturnIndex(58);
    goto func_c890;
Return_58: //  $C877  20 90 C8
    pushReturnIndex(59);
    goto func_c6f5;
Return_59: //  $C87A  20 F5 C6
    pushReturnIndex(60);
    goto func_d3d2;
Return_60: //  $C87D  20 D2 D3
    pushReturnIndex(61);
    goto func_c6c4;
Return_61: //  $C880  20 C4 C6
    pushReturnIndex(62);
    goto func_cfba;
Return_62: //  $C883  20 BA CF
    pushReturnIndex(63);
    goto func_d428;
Return_63: //  $C886  20 28 D4
    pushReturnIndex(64);
    goto func_c7fb;
Return_64: //  $C889  20 FB C7
    ; // nop //  $C88C  EA
    ; // nop //  $C88D  EA
    ; // nop //  $C88E  EA
    goto Return; //  $C88F  60

//------------------------------------------------------------------------

func_c890:
    a = M(var_0300); //  $C890  AD 00 03
    if (z)
        goto label_c8a2; //  $C893  F0 0D
    y = 0x00; //  $C895  A0 00
    writeData(var_00a1, y); //  $C897  84 A1
    pushReturnIndex(65);
    goto func_c5f7;
Return_65: //  $C899  20 F7 C5
    pushReturnIndex(66);
    goto func_c902;
Return_66: //  $C89C  20 02 C9
    pushReturnIndex(67);
    goto func_c607;
Return_67: //  $C89F  20 07 C6

label_c8a2:
    a = M(var_0350); //  $C8A2  AD 50 03
    if (z)
        goto label_c8b4; //  $C8A5  F0 0D
    y = 0x50; //  $C8A7  A0 50
    ++M(var_00a1); //  $C8A9  E6 A1
    pushReturnIndex(68);
    goto func_c5f7;
Return_68: //  $C8AB  20 F7 C5
    pushReturnIndex(69);
    goto func_c902;
Return_69: //  $C8AE  20 02 C9
    pushReturnIndex(70);
    goto func_c607;
Return_70: //  $C8B1  20 07 C6

label_c8b4:
    a = M(var_00b9); //  $C8B4  A5 B9
    if (z)
        goto label_c901; //  $C8B6  F0 49
    y = M(var_009f); //  $C8B8  A4 9F
    if (!z)
        goto label_c8c4; //  $C8BA  D0 08
    y = 0x41; //  $C8BC  A0 41
    a = M(var_00ba); //  $C8BE  A5 BA
    if (!z)
        goto label_c8c4; //  $C8C0  D0 02
    y = 0x15; //  $C8C2  A0 15

label_c8c4:
    --y; //  $C8C4  88
    writeData(var_009f, y); //  $C8C5  84 9F
    a = M(var_00bc); //  $C8C7  A5 BC
    if (!z)
        goto label_c8fb; //  $C8C9  D0 30
    a = M(var_0301); //  $C8CB  AD 01 03
    if (!z)
        goto label_c901; //  $C8CE  D0 31
    a = M(var_0351); //  $C8D0  AD 51 03
    if (!z)
        goto label_c901; //  $C8D3  D0 2C
    a = M(var_002b); //  $C8D5  A5 2B
    if (!z)
        goto label_c901; //  $C8D7  D0 28
    a = 0x0A; //  $C8D9  A9 0A
    y = 0x07; //  $C8DB  A0 07
    x = M(var_00bd); //  $C8DD  A6 BD
    if (z)
        goto label_c8e5; //  $C8DF  F0 04
    a = 0x0C; //  $C8E1  A9 0C
    y = 0x02; //  $C8E3  A0 02

label_c8e5:
    writeData(var_03a1, a); //  $C8E5  8D A1 03
    writeData(var_0023, y); //  $C8E8  84 23
    pushReturnIndex(71);
    goto func_c5d9;
Return_71: //  $C8EA  20 D9 C5
    pushReturnIndex(72);
    goto func_d446;
Return_72: //  $C8ED  20 46 D4
    a = 0x40; //  $C8F0  A9 40
    writeData(var_002b, a); //  $C8F2  85 2B
    a = 0x00; //  $C8F4  A9 00
    writeData(var_00b9, a); //  $C8F6  85 B9
    goto func_d464; //  $C8F8  4C 64 D4

label_c8fb:
    a = M(var_00a6); //  $C8FB  A5 A6
    if (z)
        goto label_c901; //  $C8FD  F0 02
    --M(var_00a6); //  $C8FF  C6 A6

label_c901:
    goto Return; //  $C901  60

//------------------------------------------------------------------------

label_c92f:
    ++M(var_0031); //  $C92F  E6 31
    goto Return; //  $C931  60

//------------------------------------------------------------------------

func_cc94:
    a = M(var_03a0); //  $CC94  AD A0 03
    if (z)
        goto label_cca8; //  $CC97  F0 0F
    a = 0x02; //  $CC99  A9 02
    writeData(var_00a1, a); //  $CC9B  85 A1
    y = 0xA0; //  $CC9D  A0 A0
    pushReturnIndex(73);
    goto func_c5f7;
Return_73: //  $CC9F  20 F7 C5
    pushReturnIndex(74);
    goto func_cca9;
Return_74: //  $CCA2  20 A9 CC
    pushReturnIndex(75);
    goto func_c607;
Return_75: //  $CCA5  20 07 C6

label_cca8:
    goto Return; //  $CCA8  60

//------------------------------------------------------------------------

func_cfba:
    x = 0x00; //  $CFBA  A2 00
    y = 0x00; //  $CFBC  A0 00
    pushReturnIndex(76);
    goto func_cfc5;
Return_76: //  $CFBE  20 C5 CF
    x = 0x04; //  $CFC1  A2 04
    y = 0x08; //  $CFC3  A0 08

label_cff8:
    goto Return; //  $CFF8  60

//------------------------------------------------------------------------

func_d131:
    a = M(JOYPAD2); //  $D131  AD 17 40
    a &= 0x10; //  $D134  29 10
    compare(a, M(var_00b7)); //  $D136  C5 B7
    if (z)
        goto label_d141; //  $D138  F0 07
    writeData(var_00b7, a); //  $D13A  85 B7

label_d13c:
    a = 0x00; //  $D13C  A9 00
    writeData(var_00b8, a); //  $D13E  85 B8

label_d140:
    goto Return; //  $D140  60

//------------------------------------------------------------------------

label_d141:
    ++M(var_00b8); //  $D141  E6 B8
    y = M(var_00b8); //  $D143  A4 B8
    compare(y, 0x01); //  $D145  C0 01
    if (!z)
        goto label_d140; //  $D147  D0 F7
    a &= 0x10; //  $D149  29 10
    if (z)
        goto label_d153; //  $D14B  F0 06
    a = 0x01; //  $D14D  A9 01
    writeData(var_00b6, a); //  $D14F  85 B6
    if (!z)
        goto label_d13c; //  $D151  D0 E9

label_d153:
    a = M(var_00b6); //  $D153  A5 B6
    if (z)
        goto label_d13c; //  $D155  F0 E5
    y = 0x00; //  $D157  A0 00
    writeData(var_00b6, y); //  $D159  84 B6
    ++y; //  $D15B  C8
    writeData(var_00b5, y); //  $D15C  84 B5
    if (!z)
        goto label_d13c; //  $D15E  D0 DC

func_d160:
    a = M(var_00b9); //  $D160  A5 B9
    if (!z)
        goto label_d169; //  $D162  D0 05

label_d164:
    a = 0x00; //  $D164  A9 00
    writeData(var_00b5, a); //  $D166  85 B5

label_d168:
    goto Return; //  $D168  60

//------------------------------------------------------------------------

label_d169:
    a = M(var_00b5); //  $D169  A5 B5
    if (z)
        goto label_d168; //  $D16B  F0 FB
    a = M(var_00ba); //  $D16D  A5 BA
    if (z)
        goto label_d164; //  $D16F  F0 F3
    --M(var_00ba); //  $D171  C6 BA
    a = 0x01; //  $D173  A9 01
    writeData(var_00be, a); //  $D175  85 BE
    a = 0x00; //  $D177  A9 00
    writeData(var_00b5, a); //  $D179  85 B5
    pushReturnIndex(77);
    goto func_d4e6;
Return_77: //  $D17B  20 E6 D4
    a = 0x04; //  $D17E  A9 04
    writeData(var_0023, a); //  $D180  85 23
    pushReturnIndex(78);
    goto func_c23b;
Return_78: //  $D182  20 3B C2
    pushReturnIndex(79);
    goto func_c5e1;
Return_79: //  $D185  20 E1 C5
    a = M(var_0024); //  $D188  A5 24
    if (z)
        goto label_d19f; //  $D18A  F0 13
    pushReturnIndex(80);
    goto func_d4e2;
Return_80: //  $D18C  20 E2 D4
    pushReturnIndex(81);
    goto func_f56c;
Return_81: //  $D18F  20 6C F5
    pushReturnIndex(82);
    goto func_d4e6;
Return_82: //  $D192  20 E6 D4
    a = 0x02; //  $D195  A9 02
    writeData(var_00b0, a); //  $D197  85 B0
    a = 0xFF; //  $D199  A9 FF
    writeData(var_000a, a); //  $D19B  85 0A
    if (!z)
        goto label_d1ca; //  $D19D  D0 2B

label_d19f:
    a = 0x05; //  $D19F  A9 05
    writeData(var_0023, a); //  $D1A1  85 23
    a = 0x00; //  $D1A3  A9 00
    writeData(var_00b0, a); //  $D1A5  85 B0
    y = 0x00; //  $D1A7  A0 00
    a = M(var_0300); //  $D1A9  AD 00 03
    if (z)
        goto label_d1b5; //  $D1AC  F0 07
    a = M(var_0301); //  $D1AE  AD 01 03
    compare(a, 0x03); //  $D1B1  C9 03
    if (z)
        goto label_d1c7; //  $D1B3  F0 12

label_d1b5:
    a = 0x01; //  $D1B5  A9 01
    writeData(var_00b0, a); //  $D1B7  85 B0
    y = 0x50; //  $D1B9  A0 50
    a = M(var_0350); //  $D1BB  AD 50 03
    if (z)
        goto label_d1dd; //  $D1BE  F0 1D
    a = M(var_0351); //  $D1C0  AD 51 03
    compare(a, 0x03); //  $D1C3  C9 03
    if (!z)
        goto label_d1dd; //  $D1C5  D0 16

label_d1c7:
    pushReturnIndex(83);
    goto func_d292;
Return_83: //  $D1C7  20 92 D2

label_d1ca:
    pushReturnIndex(84);
    goto func_c61e;
Return_84: //  $D1CA  20 1E C6

label_d1cd:
    a = M(var_0020); //  $D1CD  A5 20
    if (!z)
        goto label_d1f4; //  $D1CF  D0 23
    a = M(JOYPAD2); //  $D1D1  AD 17 40
    a &= 0x08; //  $D1D4  29 08
    if (!z)
        goto label_d1cd; //  $D1D6  D0 F5
    a = M(var_00b0); //  $D1D8  A5 B0
    goto label_d28a; //  $D1DA  4C 8A D2

label_d1dd:
    a = M(var_001f); //  $D1DD  A5 1F
    compare(a, 0x02); //  $D1DF  C9 02
    if (!z)
        goto label_d1e6; //  $D1E1  D0 03
    goto label_d266; //  $D1E3  4C 66 D2

label_d1e6:
    y = 0x02; //  $D1E6  A0 02
    writeData(var_0023, y); //  $D1E8  84 23
    pushReturnIndex(85);
    goto func_c5d9;
Return_85: //  $D1EA  20 D9 C5
    y = 0x01; //  $D1ED  A0 01
    writeData(var_0027, y); //  $D1EF  84 27
    goto label_d26a; //  $D1F1  4C 6A D2

label_d1f4:
    pushReturnIndex(86);
    goto func_c61e;
Return_86: //  $D1F4  20 1E C6
    a = M(var_0009); //  $D1F7  A5 09
    a &= 0xE7; //  $D1F9  29 E7
    writeData(var_0009, a); //  $D1FB  85 09
    a = 0x08; //  $D1FD  A9 08
    y = M(var_00b0); //  $D1FF  A4 B0
    compare(y, 0x02); //  $D201  C0 02
    if (z)
        goto label_d207; //  $D203  F0 02
    a = 0x10; //  $D205  A9 10

label_d207:
    a |= M(var_0009); //  $D207  05 09
    writeData(var_0009, a); //  $D209  85 09
    writeData(PPU_MASK, a); //  $D20B  8D 01 20
    pushReturnIndex(87);
    goto func_c23b;
Return_87: //  $D20E  20 3B C2
    a = M(var_0350); //  $D211  AD 50 03
    if (z)
        goto label_d222; //  $D214  F0 0C
    a = M(var_0351); //  $D216  AD 51 03
    compare(a, 0x03); //  $D219  C9 03
    if (!z)
        goto label_d222; //  $D21B  D0 05
    y = 0x50; //  $D21D  A0 50
    pushReturnIndex(88);
    goto func_d292;
Return_88: //  $D21F  20 92 D2

label_d222:
    a = M(var_0020); //  $D222  A5 20
    if (!z)
        goto label_d270; //  $D224  D0 4A
    a = M(JOYPAD2); //  $D226  AD 17 40
    a &= 0x08; //  $D229  29 08
    if (!z)
        goto label_d222; //  $D22B  D0 F5
    a = M(var_00b0); //  $D22D  A5 B0
    compare(a, 0x02); //  $D22F  C9 02
    if (!z)
        goto label_d246; //  $D231  D0 13
    a = 0x01; //  $D233  A9 01

label_d235:
    writeData(var_05ff, a); //  $D235  8D FF 05
    a = 0x01; //  $D238  A9 01
    writeData(var_0023, a); //  $D23A  85 23
    a = 0x00; //  $D23C  A9 00
    writeData(var_000a, a); //  $D23E  85 0A
    pushReturnIndex(89);
    goto func_c5d9;
Return_89: //  $D240  20 D9 C5
    goto func_c5ee; //  $D243  4C EE C5

label_d246:
    ++M(var_00aa); //  $D246  E6 AA
    ++M(var_00bd); //  $D248  E6 BD
    x = 0x04; //  $D24A  A2 04
    a = M(var_00b0); //  $D24C  A5 B0
    if (!z)
        goto label_d256; //  $D24E  D0 06
    writeData(var_0301, x); //  $D250  8E 01 03
    goto label_d259; //  $D253  4C 59 D2

label_d256:
    writeData(var_0351, x); //  $D256  8E 51 03

label_d259:
    a = M(var_001f); //  $D259  A5 1F
    compare(a, 0x02); //  $D25B  C9 02

label_d25e:
    y = 0x01; //  $D25F  A0 01
    writeData(var_0027, y); //  $D261  84 27
    ++y; //  $D263  C8
    if (!z)
        goto label_d268; //  $D264  D0 02

label_d266:
    y = 0x03; //  $D266  A0 03

label_d268:
    writeData(var_0023, y); //  $D268  84 23

label_d26a:
    pushReturnIndex(90);
    goto func_c23b;
Return_90: //  $D26A  20 3B C2
    goto func_c5ee; //  $D26D  4C EE C5

label_d270:
    a = M(var_00b0); //  $D270  A5 B0
    if (!z)
        goto label_d28a; //  $D272  D0 16
    a = M(var_0350); //  $D274  AD 50 03
    if (z)
        goto label_d259; //  $D277  F0 E0
    a = M(var_0351); //  $D279  AD 51 03
    compare(a, 0x03); //  $D27C  C9 03
    if (!z)
        goto label_d259; //  $D27E  D0 D9
    a = 0x01; //  $D280  A9 01
    writeData(var_00b0, a); //  $D282  85 B0
    pushReturnIndex(91);
    goto func_c61e;
Return_91: //  $D284  20 1E C6
    goto label_d222; //  $D287  4C 22 D2

label_d28a:
    compare(a, 0x02); //  $D28A  C9 02
    if (!z)
        goto label_d259; //  $D28C  D0 CB
    a = 0x02; //  $D28E  A9 02
    if (!z)
        goto label_d235; //  $D290  D0 A3

func_d2a4:
    y = M(var_00c2); //  $D2A4  A4 C2

label_d2b1:
    ++y; //  $D2B1  C8
    writeData(var_00c2, y); //  $D2B2  84 C2
    writeData(var_00ab, a); //  $D2B4  85 AB
    a = 0x00; //  $D2B6  A9 00
    writeData(var_00bb, a); //  $D2B8  85 BB
    writeData(var_00aa, a); //  $D2BA  85 AA
    a = 0x01; //  $D2BC  A9 01
    writeData(var_03a0, a); //  $D2BE  8D A0 03
    writeData(var_03a1, a); //  $D2C1  8D A1 03
    a = 0xFF; //  $D2C4  A9 FF
    writeData(0x9C, a); //  $D2C6  85 9C
    goto Return; //  $D2C8  60

//------------------------------------------------------------------------

func_d3d2:
    a = M(var_0027); //  $D3D2  A5 27
    if (!z)
        goto label_d427; //  $D3D4  D0 51
    ++M(var_009b); //  $D3D6  E6 9B
    y = 0x00; //  $D3D8  A0 00
    pushReturnIndex(92);
    goto func_d3df;
Return_92: //  $D3DA  20 DF D3
    y = 0x50; //  $D3DD  A0 50

label_d3fb:
    a = M(var_009b); //  $D3FB  A5 9B
    a &= 0x0F; //  $D3FD  29 0F
    if (!z)
        goto label_d427; //  $D3FF  D0 26
    x = 0xB7; //  $D401  A2 B7
    a = M(var_009b); //  $D403  A5 9B
    a &= 0x10; //  $D405  29 10
    if (z)
        goto label_d413; //  $D407  F0 0A

label_d409:
    x = 0xD4; //  $D409  A2 D4

label_d40b:
    a = M(var_001f); //  $D40B  A5 1F
    compare(a, 0x02); //  $D40D  C9 02
    if (z)
        goto label_d413; //  $D40F  F0 02
    ++x; //  $D411  E8
    ++x; //  $D412  E8

label_d427:
    goto Return; //  $D427  60

//------------------------------------------------------------------------

func_d428:
    a = M(var_00b9); //  $D428  A5 B9
    if (z)
        goto label_d427; //  $D42A  F0 FB
    a = M(var_00ba); //  $D42C  A5 BA
    if (!z)
        goto label_d427; //  $D42E  D0 F7
    a = M(var_009a); //  $D430  A5 9A
    a &= 0x07; //  $D432  29 07
    if (!z)
        goto label_d461; //  $D434  D0 2B
    a = M(var_0027); //  $D436  A5 27
    if (!z)
        goto label_d427; //  $D438  D0 ED
    a = M(var_009a); //  $D43A  A5 9A
    a &= 0x08; //  $D43C  29 08
    if (z)
        goto func_d446; //  $D43E  F0 06
    a = 0xB7; //  $D440  A9 B7
    x = a; //  $D442  AA
    y = a; //  $D443  A8
    if (!z)
        goto label_d44c; //  $D444  D0 06

func_d446:
    a = 0xDA; //  $D446  A9 DA
    x = 0xDB; //  $D448  A2 DB
    y = 0xDC; //  $D44A  A0 DC

label_d44c:
    writeData(var_0501, a); //  $D44C  8D 01 05
    writeData(var_0502, x); //  $D44F  8E 02 05
    writeData(0x0503, y); //  $D452  8C 03 05
    a = 0x13; //  $D455  A9 13
    writeData(var_0500, a); //  $D457  8D 00 05
    x = 0x63; //  $D45A  A2 63
    y = 0x23; //  $D45C  A0 23
    pushReturnIndex(93);
    goto func_c71d;
Return_93: //  $D45E  20 1D C7

label_d461:
    ++M(var_009a); //  $D461  E6 9A
    goto Return; //  $D463  60

//------------------------------------------------------------------------

func_d464:
    pha(); //  $D464  48
    pushReturnIndex(94);
    goto func_c5d9;
Return_94: //  $D465  20 D9 C5
    pushReturnIndex(95);
    goto func_f56c;
Return_95: //  $D468  20 6C F5
    pla(); //  $D46B  68

label_d4a1:
    a = M(var_00c1); //  $D4A1  A5 C1
    a &= 0x0F; //  $D4A3  29 0F
    writeData(0x0519, a); //  $D4A5  8D 19 05
    goto label_d4cf; //  $D4A8  4C CF D4

label_d4ab:
    compare(a, 0x05); //  $D4AB  C9 05
    if (!z)
        goto label_d4cf; //  $D4AD  D0 20
    a = M(var_000c); //  $D4AF  A5 0C
    writeData(0x0521, a); //  $D4B1  8D 21 05
    a = M(var_000d); //  $D4B4  A5 0D
    writeData(0x0522, a); //  $D4B6  8D 22 05
    goto label_d4cf; //  $D4B9  4C CF D4

label_d4bc:
    x = 0x44; //  $D4BC  A2 44
    a = 0x24; //  $D4BE  A9 24

label_d4d4:
    y = 0x20; //  $D4D4  A0 20
    goto func_c71d; //  $D4D6  4C 1D C7

func_d4d9:
    pushReturnIndex(96);
    goto func_c23b;
Return_96: //  $D4D9  20 3B C2
    pushReturnIndex(97);
    goto func_c64b;
Return_97: //  $D4DC  20 4B C6
    goto label_c637; //  $D4DF  4C 37 C6

func_d4e2:
    a = 0x01; //  $D4E2  A9 01
    if (!z)
        goto label_d500; //  $D4E4  D0 1A

func_d4e6:
    a = 0x02; //  $D4E6  A9 02
    if (!z)
        goto label_d500; //  $D4E8  D0 16
    a = 0x04; //  $D4EA  A9 04
    if (!z)
        goto label_d500; //  $D4EC  D0 12
    a = 0x08; //  $D4EE  A9 08
    if (!z)
        goto label_d500; //  $D4F0  D0 0E
    a = 0x10; //  $D4F2  A9 10
    if (!z)
        goto label_d500; //  $D4F4  D0 0A
    a = 0x20; //  $D4F6  A9 20
    if (!z)
        goto label_d500; //  $D4F8  D0 06

func_d4fa:
    a = 0x40; //  $D4FA  A9 40
    if (!z)
        goto label_d500; //  $D4FC  D0 02

func_d4fe:
    a = 0x80; //  $D4FE  A9 80

label_d500:
    a |= M(var_00f0); //  $D500  05 F0
    writeData(var_00f0, a); //  $D502  85 F0
    goto Return; //  $D504  60

//------------------------------------------------------------------------

label_d505:
    a = 0x01; //  $D505  A9 01
    if (!z)
        goto label_d523; //  $D507  D0 1A

func_d509:
    a = 0x02; //  $D509  A9 02
    if (!z)
        goto label_d523; //  $D50B  D0 16

func_d50d:
    a = 0x04; //  $D50D  A9 04
    if (!z)
        goto label_d523; //  $D50F  D0 12
    a = 0x08; //  $D511  A9 08
    if (!z)
        goto label_d523; //  $D513  D0 0E

label_d515:
    a = 0x10; //  $D515  A9 10
    if (!z)
        goto label_d523; //  $D517  D0 0A
    a = 0x20; //  $D519  A9 20
    if (!z)
        goto label_d523; //  $D51B  D0 06
    a = 0x40; //  $D51D  A9 40
    if (!z)
        goto label_d523; //  $D51F  D0 02

label_d521:
    a = 0x80; //  $D521  A9 80

label_d523:
    a |= M(var_00f1); //  $D523  05 F1
    writeData(var_00f1, a); //  $D525  85 F1
    goto Return; //  $D527  60

//------------------------------------------------------------------------

label_d54b:
    pushReturnIndex(98);
    goto func_c5d9;
Return_98: //  $D54B  20 D9 C5
    x = 0x6C; //  $D54E  A2 6C
    y = 0xE2; //  $D550  A0 E2
    pushReturnIndex(99);
    goto func_c617;
Return_99: //  $D552  20 17 C6
    a = 0x03; //  $D555  A9 03
    writeData(var_0023, a); //  $D557  85 23
    a = 0x00; //  $D559  A9 00
    writeData(var_009d, a); //  $D55B  85 9D
    a = 0x09; //  $D55D  A9 09
    writeData(var_0025, a); //  $D55F  85 25
    pushReturnIndex(100);
    goto func_c3c1;
Return_100: //  $D561  20 C1 C3
    pushReturnIndex(101);
    goto func_c5ee;
Return_101: //  $D564  20 EE C5
    goto label_d505; //  $D567  4C 05 D5

label_d56a:
    pushReturnIndex(102);
    goto func_d4d9;
Return_102: //  $D56A  20 D9 D4
    pushReturnIndex(103);
    goto func_d2a4;
Return_103: //  $D56D  20 A4 D2
    pushReturnIndex(104);
    goto func_c793;
Return_104: //  $D570  20 93 C7
    pushReturnIndex(105);
    goto func_c7b3;
Return_105: //  $D573  20 B3 C7
    pushReturnIndex(106);
    goto func_c5d9;
Return_106: //  $D576  20 D9 C5
    pushReturnIndex(107);
    goto func_f56c;
Return_107: //  $D579  20 6C F5
    a = 0x01; //  $D57C  A9 01
    writeData(var_00be, a); //  $D57E  85 BE
    a = 0x03; //  $D580  A9 03
    writeData(var_00ba, a); //  $D582  85 BA
    pushReturnIndex(108);
    goto func_c6f5;
Return_108: //  $D584  20 F5 C6
    pushReturnIndex(109);
    goto func_c6cc;
Return_109: //  $D587  20 CC C6
    a = 0x06; //  $D58A  A9 06
    writeData(var_009d, a); //  $D58C  85 9D
    a = 0x0D; //  $D58E  A9 0D
    writeData(var_0025, a); //  $D590  85 25
    goto Return; //  $D592  60

//------------------------------------------------------------------------

label_d5ad:
    writeData(0xA8, a); //  $D5AD  85 A8
    a = 0x80; //  $D5AF  A9 80
    writeData(var_00a6, a); //  $D5B1  85 A6
    a = 0x01; //  $D5B3  A9 01
    writeData(var_00be, a); //  $D5B5  85 BE
    a = 0x03; //  $D5B7  A9 03
    writeData(var_00ba, a); //  $D5B9  85 BA
    a = 0x02; //  $D5BB  A9 02
    writeData(var_00bc, a); //  $D5BD  85 BC
    a = 0x00; //  $D5BF  A9 00
    writeData(var_00b5, a); //  $D5C1  85 B5
    writeData(var_00b9, a); //  $D5C3  85 B9
    writeData(var_00bd, a); //  $D5C5  85 BD
    pushReturnIndex(110);
    goto func_c6f5;
Return_110: //  $D5C7  20 F5 C6
    pushReturnIndex(111);
    goto func_c6cc;
Return_111: //  $D5CA  20 CC C6
    a = 0x0B; //  $D5CD  A9 0B
    writeData(var_0025, a); //  $D5CF  85 25
    goto Return; //  $D5D1  60

//------------------------------------------------------------------------

label_d5d2:
    pushReturnIndex(112);
    goto func_d131;
Return_112: //  $D5D2  20 31 D1
    pushReturnIndex(113);
    goto func_d160;
Return_113: //  $D5D5  20 60 D1
    pushReturnIndex(114);
    goto func_d5ee;
Return_114: //  $D5D8  20 EE D5
    pushReturnIndex(115);
    goto func_c6f5;
Return_115: //  $D5DB  20 F5 C6
    pushReturnIndex(116);
    goto func_d3d2;
Return_116: //  $D5DE  20 D2 D3
    pushReturnIndex(117);
    goto func_c6c4;
Return_117: //  $D5E1  20 C4 C6
    pushReturnIndex(118);
    goto func_cfba;
Return_118: //  $D5E4  20 BA CF
    pushReturnIndex(119);
    goto func_d428;
Return_119: //  $D5E7  20 28 D4
    ; // nop //  $D5EA  EA
    ; // nop //  $D5EB  EA
    ; // nop //  $D5EC  EA
    goto Return; //  $D5ED  60

//------------------------------------------------------------------------

func_d5ee:
    a = M(var_0300); //  $D5EE  AD 00 03
    if (z)
        goto label_d600; //  $D5F1  F0 0D
    y = 0x00; //  $D5F3  A0 00
    writeData(var_00a1, y); //  $D5F5  84 A1
    pushReturnIndex(120);
    goto func_c5f7;
Return_120: //  $D5F7  20 F7 C5
    pushReturnIndex(121);
    goto func_d652;
Return_121: //  $D5FA  20 52 D6
    pushReturnIndex(122);
    goto func_c607;
Return_122: //  $D5FD  20 07 C6

label_d600:
    a = M(var_0350); //  $D600  AD 50 03
    if (z)
        goto label_d612; //  $D603  F0 0D
    y = 0x50; //  $D605  A0 50
    ++M(var_00a1); //  $D607  E6 A1
    pushReturnIndex(123);
    goto func_c5f7;
Return_123: //  $D609  20 F7 C5
    pushReturnIndex(124);
    goto func_d652;
Return_124: //  $D60C  20 52 D6
    pushReturnIndex(125);
    goto func_c607;
Return_125: //  $D60F  20 07 C6

label_d612:
    a = M(var_00bc); //  $D612  A5 BC
    if (!z)
        goto label_d64b; //  $D614  D0 35
    x = M(var_0301); //  $D616  AE 01 03
    y = M(var_0351); //  $D619  AC 51 03
    compare(x, 0x03); //  $D61C  E0 03
    if (z)
        goto label_d627; //  $D61E  F0 07
    compare(y, 0x03); //  $D620  C0 03
    if (z)
        goto label_d627; //  $D622  F0 03
    pushReturnIndex(126);
    goto func_d4fe;
Return_126: //  $D624  20 FE D4

label_d627:
    compare(x, 0x00); //  $D627  E0 00
    if (!z)
        goto label_d651; //  $D629  D0 26
    compare(y, 0x00); //  $D62B  C0 00
    if (!z)
        goto label_d651; //  $D62D  D0 22
    pushReturnIndex(127);
    goto func_d446;
Return_127: //  $D62F  20 46 D4
    a = 0x00; //  $D632  A9 00
    writeData(var_00b9, a); //  $D634  85 B9
    a = M(var_00bb); //  $D636  A5 BB
    compare(a, 0x0A); //  $D638  C9 0A
    if (z)
        goto label_d640; //  $D63A  F0 04
    a = 0x0A; //  $D63C  A9 0A
    if (!z)
        goto label_d646; //  $D63E  D0 06

label_d640:
    a = 0x00; //  $D640  A9 00
    writeData(var_00a9, a); //  $D642  85 A9
    a = 0x0C; //  $D644  A9 0C

label_d646:
    writeData(var_0025, a); //  $D646  85 25
    goto func_c23b; //  $D648  4C 3B C2

label_d64b:
    a = M(var_00a6); //  $D64B  A5 A6
    if (z)
        goto label_d651; //  $D64D  F0 02
    --M(var_00a6); //  $D64F  C6 A6

label_d651:
    goto Return; //  $D651  60

//------------------------------------------------------------------------

data_e532:

data_e5df:

data_eb30:

data_ec02:

data_ec17:

data_ec1f:

data_ec38:

data_f300:

data_f350:

func_f35e:
    a = 0x00; //  $F35E  A9 00
    if (z)
        goto label_f36c; //  $F360  F0 0A

func_f362:
    a = 0x08; //  $F362  A9 08
    if (!z)
        goto label_f36c; //  $F364  D0 06

func_f366:
    a = 0x0C; //  $F366  A9 0C
    if (!z)
        goto label_f36c; //  $F368  D0 02

func_f36a:
    a = 0x04; //  $F36A  A9 04

label_f36c:
    writeData(var_00f4, a); //  $F36C  85 F4
    a = 0x40; //  $F36E  A9 40
    writeData(0xF5, a); //  $F370  85 F5
    writeData(var_00f6, x); //  $F372  86 F6
    writeData(0xF7, y); //  $F374  84 F7
    y = 0x00; //  $F376  A0 00

func_f3d0:
    a = 0x7F; //  $F3D0  A9 7F
    writeData(APU_PL1_SWEEP, a); //  $F3D2  8D 01 40
    writeData(APU_PL2_SWEEP, a); //  $F3D5  8D 05 40
    writeData(0xE9, x); //  $F3D8  86 E9
    writeData(var_00ea, y); //  $F3DA  84 EA
    goto Return; //  $F3DC  60

//------------------------------------------------------------------------

label_f443:
    a = 0x00; //  $F443  A9 00
    goto label_f68c; //  $F445  4C 8C F6

label_f46c:
    pushReturnIndex(128);
    goto func_f564;
Return_128: //  $F46C  20 64 F5
    if (!z)
        goto label_f475; //  $F46F  D0 04
    y = 0x10; //  $F471  A0 10
    if (!z)
        goto label_f477; //  $F473  D0 02

label_f475:
    y = M(var_00ea); //  $F475  A4 EA

label_f477:
    writeData(APU_PL2_VOL, y); //  $F477  8C 04 40
    a = M(0xDD); //  $F47A  A5 DD
    writeData(var_00d9, a); //  $F47C  85 D9

label_f501:
    goto Return; //  $F501  60

//------------------------------------------------------------------------

label_f51c:
    y = a; //  $F51C  A8
    compare(a, 0xFF); //  $F51D  C9 FF
    if (z)
        goto label_f52a; //  $F51F  F0 09
    a &= 0xC0; //  $F521  29 C0
    compare(a, 0xC0); //  $F523  C9 C0
    if (z)
        goto label_f536; //  $F525  F0 0F
    /* jmp (complex) */ //  $F527  6C 10 06  jump engine detected

label_f541:
    /* jmp (complex) */ //  $F541  6C 12 06  jump engine detected

label_f563:
    goto Return; //  $F563  60

//------------------------------------------------------------------------

func_f564:
    x = 0x04; //  $F564  A2 04
    if (!z)
        goto label_f552; //  $F566  D0 EA
    x = 0x08; //  $F568  A2 08
    if (!z)
        goto label_f552; //  $F56A  D0 E6

func_f56c:
    a = 0xC0; //  $F56C  A9 C0
    writeData(APU_FRAME, a); //  $F56E  8D 17 40
    pushReturnIndex(129);
    goto func_f6cf;
Return_129: //  $F571  20 CF F6
    pushReturnIndex(130);
    goto func_f621;
Return_130: //  $F574  20 21 F6
    pushReturnIndex(131);
    goto func_f7cc;
Return_131: //  $F577  20 CC F7
    pushReturnIndex(132);
    goto func_f591;
Return_132: //  $F57A  20 91 F5
    a = 0x00; //  $F57D  A9 00
    if (z)
        goto label_f58a; //  $F57F  F0 09

func_f581:
    a = 0xF4; //  $F581  A9 F4
    writeData(0x0613, a); //  $F583  8D 13 06
    writeData(0x0611, a); //  $F586  8D 11 06
    goto Return; //  $F589  60

//------------------------------------------------------------------------

label_f58a:
    writeData(var_00f0, a); //  $F58A  85 F0
    writeData(var_00f1, a); //  $F58C  85 F1
    writeData(var_00f2, a); //  $F58E  85 F2
    goto Return; //  $F590  60

//------------------------------------------------------------------------

func_f591:
    a = M(var_00f2); //  $F591  A5 F2
    M(a) >>= 1; //  $F593  4A
    if (c)
        goto label_f5a2; //  $F594  B0 0C
    M(a) >>= 1; //  $F596  4A
    if (c)
        goto label_f59a; //  $F597  B0 01
    goto Return; //  $F599  60

//------------------------------------------------------------------------

label_f59a:
    a = 0x20; //  $F59A  A9 20
    x = 0xF4; //  $F59C  A2 F4
    y = 0x0F; //  $F59E  A0 0F
    if (!z)
        goto label_f5a8; //  $F5A0  D0 06

label_f5a2:
    a = 0x20; //  $F5A2  A9 20
    x = 0xEC; //  $F5A4  A2 EC
    y = 0x0E; //  $F5A6  A0 0E

label_f5a8:
    writeData(APU_DMC_LEN, a); //  $F5A8  8D 13 40
    writeData(APU_DMC_START, x); //  $F5AB  8E 12 40
    writeData(APU_DMC_FREQ, y); //  $F5AE  8C 10 40
    a = 0x1F; //  $F5B1  A9 1F
    writeData(APU_SND_CHN, a); //  $F5B3  8D 15 40
    goto Return; //  $F5B6  60

//------------------------------------------------------------------------

label_f5bf:
    x = 0xDD; //  $F5BF  A2 DD
    y = 0xF3; //  $F5C1  A0 F3
    pushReturnIndex(133);
    goto func_f362;
Return_133: //  $F5C3  20 62 F3
    a = 0x00; //  $F5C6  A9 00
    writeData(var_00eb, a); //  $F5C8  85 EB
    writeData(var_00ed, a); //  $F5CA  85 ED
    writeData(var_00ee, a); //  $F5CC  85 EE
    a = 0x06; //  $F5CE  A9 06
    writeData(var_00ef, a); //  $F5D0  85 EF
    a = 0x3E; //  $F5D2  A9 3E
    writeData(var_00ec, a); //  $F5D4  85 EC
    a = 0x40; //  $F5D6  A9 40
    writeData(var_00f3, a); //  $F5D8  85 F3

label_f5da:
    goto Return; //  $F5DA  60

//------------------------------------------------------------------------

label_f5db:
    ++M(var_00ee); //  $F5DB  E6 EE
    a = M(var_00ee); //  $F5DD  A5 EE
    compare(a, 0x01); //  $F5DF  C9 01
    if (!z)
        goto label_f5da; //  $F5E1  D0 F7
    a = 0x00; //  $F5E3  A9 00
    writeData(var_00ee, a); //  $F5E5  85 EE
    ++M(var_00eb); //  $F5E7  E6 EB
    a = M(var_00eb); //  $F5E9  A5 EB
    compare(a, M(var_00ef)); //  $F5EB  C5 EF
    if (z)
        goto label_f5fb; //  $F5ED  F0 0C
    --M(var_00ec); //  $F5EF  C6 EC
    --M(var_00ec); //  $F5F1  C6 EC
    --M(var_00ec); //  $F5F3  C6 EC
    a = M(var_00ec); //  $F5F5  A5 EC
    writeData(APU_TRI_LO, a); //  $F5F7  8D 0A 40
    goto Return; //  $F5FA  60

//------------------------------------------------------------------------

func_f621:
    a = M(var_00f0); //  $F621  A5 F0
    M(a) <<= 1; //  $F623  0A
    if (c)
        goto label_f669; //  $F624  B0 43
    M(a) <<= 1; //  $F626  0A
    if (c)
        goto label_f5bf; //  $F627  B0 96
    M(a) <<= 1; //  $F629  0A
    if (c)
        goto label_f641; //  $F62A  B0 15
    M(a) <<= 1; //  $F62C  0A
    if (c)
        goto label_f639; //  $F62D  B0 0A
    a = M(var_00f3); //  $F62F  A5 F3
    M(a) <<= 1; //  $F631  0A
    M(a) <<= 1; //  $F632  0A
    if (c)
        goto label_f5db; //  $F633  B0 A6
    M(a) <<= 1; //  $F635  0A
    if (c)
        goto label_f655; //  $F636  B0 1D
    goto Return; //  $F638  60

//------------------------------------------------------------------------

label_f639:
    x = 0xEF; //  $F639  A2 EF
    y = 0xF3; //  $F63B  A0 F3
    pushReturnIndex(134);
    goto func_f35e;
Return_134: //  $F63D  20 5E F3
    goto Return; //  $F640  60

//------------------------------------------------------------------------

label_f641:
    x = 0xF3; //  $F641  A2 F3
    y = 0xF3; //  $F643  A0 F3
    pushReturnIndex(135);
    goto func_f36a;
Return_135: //  $F645  20 6A F3
    a = M(var_00f3); //  $F648  A5 F3
    a |= 0x20; //  $F64A  09 20
    writeData(var_00f3, a); //  $F64C  85 F3
    a = 0x00; //  $F64E  A9 00
    writeData(var_00ef, a); //  $F650  85 EF
    writeData(var_00ee, a); //  $F652  85 EE

label_f654:
    goto Return; //  $F654  60

//------------------------------------------------------------------------

label_f655:
    ++M(var_00ee); //  $F655  E6 EE
    a = M(var_00ee); //  $F657  A5 EE
    compare(a, 0x02); //  $F659  C9 02
    if (!z)
        goto label_f654; //  $F65B  D0 F7
    a = 0x00; //  $F65D  A9 00
    writeData(var_00ee, a); //  $F65F  85 EE
    ++M(var_00ef); //  $F661  E6 EF
    a = M(var_00ef); //  $F663  A5 EF
    compare(a, 0xA0); //  $F665  C9 A0
    if (!z)
        goto label_f654; //  $F667  D0 EB

label_f669:
    a = 0x10; //  $F669  A9 10
    writeData(APU_PL2_VOL, a); //  $F66B  8D 04 40
    a = M(var_00f3); //  $F66E  A5 F3
    a &= 0xDF; //  $F670  29 DF
    writeData(var_00f3, a); //  $F672  85 F3
    goto Return; //  $F674  60

//------------------------------------------------------------------------

label_f675:
    x = 0xF7; //  $F675  A2 F7
    y = 0xF3; //  $F677  A0 F3
    pushReturnIndex(136);
    goto func_f366;
Return_136: //  $F679  20 66 F3
    a = 0x10; //  $F67C  A9 10
    writeData(APU_PL1_VOL, a); //  $F67E  8D 00 40
    a = M(var_00f3); //  $F681  A5 F3
    a &= 0xF0; //  $F683  29 F0
    writeData(var_00f3, a); //  $F685  85 F3
    goto Return; //  $F687  60

//------------------------------------------------------------------------

label_f688:
    a = 0x00; //  $F688  A9 00
    writeData(var_00f3, a); //  $F68A  85 F3

label_f68c:
    writeData(APU_TRI_LINEAR, a); //  $F68C  8D 08 40
    writeData(APU_DMC_RAW, a); //  $F68F  8D 11 40
    writeData(var_00e6, a); //  $F692  85 E6
    writeData(var_00e4, a); //  $F694  85 E4
    a = 0x10; //  $F696  A9 10
    writeData(APU_PL1_VOL, a); //  $F698  8D 00 40
    writeData(APU_PL2_VOL, a); //  $F69B  8D 04 40
    writeData(APU_NOISE_VOL, a); //  $F69E  8D 0C 40
    goto Return; //  $F6A1  60

//------------------------------------------------------------------------

label_f6a2:
    x = 0xFB; //  $F6A2  A2 FB
    y = 0xF3; //  $F6A4  A0 F3
    pushReturnIndex(137);
    goto func_f366;
Return_137: //  $F6A6  20 66 F3
    a = 0x00; //  $F6A9  A9 00
    writeData(var_00eb, a); //  $F6AB  85 EB
    a = M(var_00f3); //  $F6AD  A5 F3
    a |= 0x08; //  $F6AF  09 08
    writeData(var_00f3, a); //  $F6B1  85 F3

label_f6b3:
    goto Return; //  $F6B3  60

//------------------------------------------------------------------------

data_f6cb:

func_f6cf:
    a = M(var_00f0); //  $F6CF  A5 F0
    M(a) >>= 1; //  $F6D1  4A
    if (c)
        goto label_f688; //  $F6D2  B0 B4
    M(a) >>= 1; //  $F6D4  4A
    if (c)
        goto label_f6e8; //  $F6D5  B0 11
    M(a) >>= 1; //  $F6D7  4A
    if (c)
        goto label_f675; //  $F6D8  B0 9B
    M(a) >>= 1; //  $F6DA  4A
    if (c)
        goto label_f6a2; //  $F6DB  B0 C5
    a = M(var_00f3); //  $F6DD  A5 F3
    M(a) >>= 1; //  $F6DF  4A
    M(a) >>= 1; //  $F6E0  4A
    if (c)
        goto label_f703; //  $F6E1  B0 20
    M(a) >>= 1; //  $F6E3  4A
    M(a) >>= 1; //  $F6E4  4A
    if (c)
        goto label_f6b4; //  $F6E5  B0 CD
    goto Return; //  $F6E7  60

//------------------------------------------------------------------------

label_f6e8:
    x = 0xFF; //  $F6E8  A2 FF
    y = 0xF6; //  $F6EA  A0 F6
    pushReturnIndex(138);
    goto func_f366;
Return_138: //  $F6EC  20 66 F3
    a = 0x00; //  $F6EF  A9 00
    writeData(var_00ec, a); //  $F6F1  85 EC
    writeData(var_00ed, a); //  $F6F3  85 ED
    writeData(APU_DMC_RAW, a); //  $F6F5  8D 11 40
    a = M(var_00f3); //  $F6F8  A5 F3
    a |= 0x02; //  $F6FA  09 02
    writeData(var_00f3, a); //  $F6FC  85 F3

label_f6fe:
    goto Return; //  $F6FE  60

//------------------------------------------------------------------------

label_f730:
    goto Return; //  $F730  60

//------------------------------------------------------------------------

label_f791:
    x = 0xB7; //  $F791  A2 B7
    y = 0xF5; //  $F793  A0 F5
    pushReturnIndex(139);
    goto func_f35e;
Return_139: //  $F795  20 5E F3
    x = 0xBB; //  $F798  A2 BB
    y = 0xF5; //  $F79A  A0 F5

label_f79c:
    pushReturnIndex(140);
    goto func_f36a;
Return_140: //  $F79C  20 6A F3
    goto Return; //  $F79F  60

//------------------------------------------------------------------------

label_f7a8:
    a = 0x00; //  $F7A8  A9 00
    writeData(APU_PL1_VOL, a); //  $F7AA  8D 00 40
    x = 0xA0; //  $F7AD  A2 A0
    y = 0xF7; //  $F7AF  A0 F7
    pushReturnIndex(141);
    goto func_f35e;
Return_141: //  $F7B1  20 5E F3
    x = 0xA4; //  $F7B4  A2 A4
    y = 0xF7; //  $F7B6  A0 F7
    if (!z)
        goto label_f79c; //  $F7B8  D0 E2

label_f7ba:
    y = 0x06; //  $F7BA  A0 06
    a = 0x80; //  $F7BC  A9 80
    if (!z)
        goto label_f82f; //  $F7BE  D0 6F

label_f7c0:
    y = 0x04; //  $F7C0  A0 04
    a = 0x04; //  $F7C2  A9 04
    if (!z)
        goto label_f826; //  $F7C4  D0 60

label_f7c6:
    y = 0x05; //  $F7C6  A0 05
    a = 0x08; //  $F7C8  A9 08
    if (!z)
        goto label_f826; //  $F7CA  D0 5A

func_f7cc:
    a = M(var_00f1); //  $F7CC  A5 F1
    M(a) >>= 1; //  $F7CE  4A
    if (c)
        goto label_f7fd; //  $F7CF  B0 2C
    M(a) >>= 1; //  $F7D1  4A
    if (c)
        goto label_f803; //  $F7D2  B0 2F
    M(a) >>= 1; //  $F7D4  4A
    if (c)
        goto label_f7c0; //  $F7D5  B0 E9
    M(a) >>= 1; //  $F7D7  4A
    if (c)
        goto label_f7c6; //  $F7D8  B0 EC
    M(a) >>= 1; //  $F7DA  4A
    if (c)
        goto label_f809; //  $F7DB  B0 2C
    M(a) >>= 1; //  $F7DD  4A
    if (c)
        goto label_f80f; //  $F7DE  B0 2F
    M(a) >>= 1; //  $F7E0  4A
    if (c)
        goto label_f815; //  $F7E1  B0 32
    M(a) >>= 1; //  $F7E3  4A
    if (c)
        goto label_f7ba; //  $F7E4  B0 D4
    a = M(var_00f2); //  $F7E6  A5 F2
    M(a) <<= 1; //  $F7E8  0A
    if (c)
        goto label_f81b; //  $F7E9  B0 30
    M(a) <<= 1; //  $F7EB  0A
    M(a) <<= 1; //  $F7EC  0A
    if (c)
        goto label_f791; //  $F7ED  B0 A2
    M(a) <<= 1; //  $F7EF  0A
    if (c)
        goto label_f840; //  $F7F0  B0 4E
    M(a) <<= 1; //  $F7F2  0A
    if (c)
        goto label_f7a8; //  $F7F3  B0 B3
    a = M(var_00e6); //  $F7F5  A5 E6
    if (!z)
        goto label_f7fa; //  $F7F7  D0 01
    goto Return; //  $F7F9  60

//------------------------------------------------------------------------

label_f7fa:
    goto label_f40f; //  $F7FA  4C 0F F4

label_f7fd:
    y = 0x00; //  $F7FD  A0 00
    a = 0x01; //  $F7FF  A9 01
    if (!z)
        goto label_f826; //  $F801  D0 23

label_f803:
    y = 0x03; //  $F803  A0 03
    a = 0x02; //  $F805  A9 02
    if (!z)
        goto label_f82f; //  $F807  D0 26

label_f809:
    y = 0x01; //  $F809  A0 01
    a = 0x10; //  $F80B  A9 10
    if (!z)
        goto label_f826; //  $F80D  D0 17

label_f80f:
    y = 0x07; //  $F80F  A0 07
    a = 0x20; //  $F811  A9 20
    if (!z)
        goto label_f826; //  $F813  D0 11

label_f815:
    y = 0x02; //  $F815  A0 02
    a = 0x40; //  $F817  A9 40
    if (!z)
        goto label_f826; //  $F819  D0 0B

label_f81b:
    a = 0x10; //  $F81B  A9 10
    writeData(APU_NOISE_VOL, a); //  $F81D  8D 0C 40
    y = 0x08; //  $F820  A0 08
    a = 0xEF; //  $F822  A9 EF
    if (!z)
        goto label_f82f; //  $F824  D0 09

label_f826:
    pushReturnIndex(142);
    goto func_f383;
Return_142: //  $F826  20 83 F3
    x = 0xC0; //  $F829  A2 C0
    y = 0xC0; //  $F82B  A0 C0
    if (!z)
        goto label_f836; //  $F82D  D0 07

label_f82f:
    pushReturnIndex(143);
    goto func_f383;
Return_143: //  $F82F  20 83 F3
    x = 0x86; //  $F832  A2 86
    y = 0x86; //  $F834  A0 86

label_f836:
    pushReturnIndex(144);
    goto func_f3d0;
Return_144: //  $F836  20 D0 F3
    a = 0x00; //  $F839  A9 00
    writeData(var_00e4, a); //  $F83B  85 E4
    goto label_f40f; //  $F83D  4C 0F F4

label_f840:
    y = 0x09; //  $F840  A0 09
    a = 0xEF; //  $F842  A9 EF
    if (!z)
        goto label_f826; //  $F844  D0 E0

data_f846:
    M(a) <<= 1; //  $F846  0A

data_f847:

data_f849:
    a &= M(0x2E); //  $F849  25 2E

data_f84b:

data_ff18:
    goto Skip_0;
// Return handler
// This emulates the RTS instruction using a generated jump table
//
Return:
    switch (popReturnIndex())
    {
    case 0:
        goto Return_0;
    case 1:
        goto Return_1;
    case 2:
        goto Return_2;
    case 3:
        goto Return_3;
    case 4:
        goto Return_4;
    case 5:
        goto Return_5;
    case 6:
        goto Return_6;
    case 7:
        goto Return_7;
    case 8:
        goto Return_8;
    case 9:
        goto Return_9;
    case 10:
        goto Return_10;
    case 11:
        goto Return_11;
    case 12:
        goto Return_12;
    case 13:
        goto Return_13;
    case 14:
        goto Return_14;
    case 15:
        goto Return_15;
    case 16:
        goto Return_16;
    case 17:
        goto Return_17;
    case 18:
        goto Return_18;
    case 19:
        goto Return_19;
    case 20:
        goto Return_20;
    case 21:
        goto Return_21;
    case 22:
        goto Return_22;
    case 23:
        goto Return_23;
    case 24:
        goto Return_24;
    case 25:
        goto Return_25;
    case 26:
        goto Return_26;
    case 27:
        goto Return_27;
    case 28:
        goto Return_28;
    case 29:
        goto Return_29;
    case 30:
        goto Return_30;
    case 31:
        goto Return_31;
    case 32:
        goto Return_32;
    case 33:
        goto Return_33;
    case 34:
        goto Return_34;
    case 35:
        goto Return_35;
    case 36:
        goto Return_36;
    case 37:
        goto Return_37;
    case 38:
        goto Return_38;
    case 39:
        goto Return_39;
    case 40:
        goto Return_40;
    case 41:
        goto Return_41;
    case 42:
        goto Return_42;
    case 43:
        goto Return_43;
    case 44:
        goto Return_44;
    case 45:
        goto Return_45;
    case 46:
        goto Return_46;
    case 47:
        goto Return_47;
    case 48:
        goto Return_48;
    case 49:
        goto Return_49;
    case 50:
        goto Return_50;
    case 51:
        goto Return_51;
    case 52:
        goto Return_52;
    case 53:
        goto Return_53;
    case 54:
        goto Return_54;
    case 55:
        goto Return_55;
    case 56:
        goto Return_56;
    case 57:
        goto Return_57;
    case 58:
        goto Return_58;
    case 59:
        goto Return_59;
    case 60:
        goto Return_60;
    case 61:
        goto Return_61;
    case 62:
        goto Return_62;
    case 63:
        goto Return_63;
    case 64:
        goto Return_64;
    case 65:
        goto Return_65;
    case 66:
        goto Return_66;
    case 67:
        goto Return_67;
    case 68:
        goto Return_68;
    case 69:
        goto Return_69;
    case 70:
        goto Return_70;
    case 71:
        goto Return_71;
    case 72:
        goto Return_72;
    case 73:
        goto Return_73;
    case 74:
        goto Return_74;
    case 75:
        goto Return_75;
    case 76:
        goto Return_76;
    case 77:
        goto Return_77;
    case 78:
        goto Return_78;
    case 79:
        goto Return_79;
    case 80:
        goto Return_80;
    case 81:
        goto Return_81;
    case 82:
        goto Return_82;
    case 83:
        goto Return_83;
    case 84:
        goto Return_84;
    case 85:
        goto Return_85;
    case 86:
        goto Return_86;
    case 87:
        goto Return_87;
    case 88:
        goto Return_88;
    case 89:
        goto Return_89;
    case 90:
        goto Return_90;
    case 91:
        goto Return_91;
    case 92:
        goto Return_92;
    case 93:
        goto Return_93;
    case 94:
        goto Return_94;
    case 95:
        goto Return_95;
    case 96:
        goto Return_96;
    case 97:
        goto Return_97;
    case 98:
        goto Return_98;
    case 99:
        goto Return_99;
    case 100:
        goto Return_100;
    case 101:
        goto Return_101;
    case 102:
        goto Return_102;
    case 103:
        goto Return_103;
    case 104:
        goto Return_104;
    case 105:
        goto Return_105;
    case 106:
        goto Return_106;
    case 107:
        goto Return_107;
    case 108:
        goto Return_108;
    case 109:
        goto Return_109;
    case 110:
        goto Return_110;
    case 111:
        goto Return_111;
    case 112:
        goto Return_112;
    case 113:
        goto Return_113;
    case 114:
        goto Return_114;
    case 115:
        goto Return_115;
    case 116:
        goto Return_116;
    case 117:
        goto Return_117;
    case 118:
        goto Return_118;
    case 119:
        goto Return_119;
    case 120:
        goto Return_120;
    case 121:
        goto Return_121;
    case 122:
        goto Return_122;
    case 123:
        goto Return_123;
    case 124:
        goto Return_124;
    case 125:
        goto Return_125;
    case 126:
        goto Return_126;
    case 127:
        goto Return_127;
    case 128:
        goto Return_128;
    case 129:
        goto Return_129;
    case 130:
        goto Return_130;
    case 131:
        goto Return_131;
    case 132:
        goto Return_132;
    case 133:
        goto Return_133;
    case 134:
        goto Return_134;
    case 135:
        goto Return_135;
    case 136:
        goto Return_136;
    case 137:
        goto Return_137;
    case 138:
        goto Return_138;
    case 139:
        goto Return_139;
    case 140:
        goto Return_140;
    case 141:
        goto Return_141;
    case 142:
        goto Return_142;
    case 143:
        goto Return_143;
    case 144:
        goto Return_144;
    }
}
