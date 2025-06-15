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
        goto Start;
    case 1:
        goto NonMaskableInterrupt;
    }


Reset:
    /* cld */ //  $C000  D8
    /* sei */ //  $C001  78

underscorelabelunderscorec002:
    a = M(PPUunderscoreSTATUS); //  $C002  AD 02 20
    if (!n)
        goto underscorelabelunderscorec002; //  $C005  10 FB
    x = 0x00; //  $C007  A2 00
    writeData(PPUunderscoreCTRL, x); //  $C009  8E 00 20
    writeData(PPUunderscoreMASK, x); //  $C00C  8E 01 20
    --x; //  $C00F  CA
    s = x; //  $C010  9A
    x = M(underscorevarunderscore05ec); //  $C011  AE EC 05
    y = 0x06; //  $C014  A0 06
    writeData(underscorevarunderscore0001, y); //  $C016  84 01
    y = 0x00; //  $C018  A0 00
    writeData(underscorevarunderscore0000underscoreindexed, y); //  $C01A  84 00
    a = 0x00; //  $C01C  A9 00

underscorelabelunderscorec01e:
    writeData(W(underscorevarunderscore0000underscoreindexed) + y, a); //  $C01E  91 00
    --y; //  $C020  88
    if (!z)
        goto underscorelabelunderscorec01e; //  $C021  D0 FB
    --M(underscorevarunderscore0001); //  $C023  C6 01
    if (!n)
        goto underscorelabelunderscorec01e; //  $C025  10 F7
    a = x; //  $C027  8A
    if (!z)
        goto underscorelabelunderscorec02c; //  $C028  D0 02
    x = 0x5F; //  $C02A  A2 5F

underscorelabelunderscorec02c:
    writeData(underscorevarunderscore05ec, x); //  $C02C  8E EC 05
    JSR(underscorefuncunderscorec22b, 0); //  $C02F  20 2B C2
    JSR(underscorefuncunderscorec23b, 1); //  $C032  20 3B C2
    y = 0x00; //  $C035  A0 00
    writeData(PPUunderscoreSCROLL, a); //  $C037  8D 05 20
    writeData(PPUunderscoreSCROLL, a); //  $C03A  8D 05 20
    y = 0x01; //  $C03D  A0 01
    writeData(underscorevarunderscore0024, y); //  $C03F  84 24
    a = 0x0F; //  $C041  A9 0F
    writeData(APUunderscoreSNDunderscoreCHN, a); //  $C043  8D 15 40
    JSR(underscorefuncunderscoref581, 2); //  $C046  20 81 F5
    a = 0x90; //  $C049  A9 90
    writeData(PPUunderscoreCTRL, a); //  $C04B  8D 00 20
    writeData(underscorevarunderscore0008, a); //  $C04E  85 08
    a = 0x02; //  $C050  A9 02
    writeData(underscorevarunderscore0009, a); //  $C052  85 09
    x = 0x0B; //  $C054  A2 0B

underscorelabelunderscorec056:
    a = M(underscoredataunderscoree5dfunderscoreindexed + x); //  $C056  BD DF E5
    writeData(underscorevarunderscore05f0underscoreindexed + x, a); //  $C059  9D F0 05
    --x; //  $C05C  CA
    if (!n)
        goto underscorelabelunderscorec056; //  $C05D  10 F7
    if (n)
        goto underscorelabelunderscorec07c; //  $C05F  30 1B

underscorelabelunderscorec061:
    a = M(underscorevarunderscore0024); //  $C061  A5 24
    if (z)
        goto underscorelabelunderscorec06b; //  $C063  F0 06
    a = M(underscorevarunderscore0026); //  $C065  A5 26
    compare(a, 0x01); //  $C067  C9 01
    if (!z)
        goto underscorelabelunderscorec06e; //  $C069  D0 03

underscorelabelunderscorec06b:
    JSR(underscorefuncunderscoref56c, 3); //  $C06B  20 6C F5

underscorelabelunderscorec06e:
    JSR(underscorefuncunderscorec348, 4); //  $C06E  20 48 C3
    JSR(underscorefuncunderscorec284, 5); //  $C071  20 84 C2
    JSR(underscorefuncunderscorec0b3, 6); //  $C074  20 B3 C0
    ++M(underscorevarunderscore002f); //  $C077  E6 2F
    JSR(underscorefuncunderscorec61e, 7); //  $C079  20 1E C6

underscorelabelunderscorec07c:
    a = M(underscorevarunderscore0020); //  $C07C  A5 20
    if (!z)
        goto underscorelabelunderscorec061; //  $C07E  D0 E1
    JSR(underscorefuncunderscorec588, 8); //  $C080  20 88 C5
    goto underscorelabelunderscorec07c; //  $C083  4C 7C C0

NMI:
    php(); //  $C086  08
    pha(); //  $C087  48
    a = x; //  $C088  8A
    pha(); //  $C089  48
    a = y; //  $C08A  98
    pha(); //  $C08B  48
    a = 0x00; //  $C08C  A9 00
    writeData(OAMunderscoreADDR, a); //  $C08E  8D 03 20
    a = 0x02; //  $C091  A9 02
    writeData(OAMunderscoreDMA, a); //  $C093  8D 14 40
    a = M(underscorevarunderscore0022); //  $C096  A5 22
    if (!z)
        goto underscorelabelunderscorec0a6; //  $C098  D0 0C
    JSR(underscorefuncunderscorec2bf, 9); //  $C09A  20 BF C2
    JSR(underscorefuncunderscorec249, 10); //  $C09D  20 49 C2
    JSR(underscorefuncunderscorec263, 11); //  $C0A0  20 63 C2
    JSR(underscorefuncunderscorec3c1, 12); //  $C0A3  20 C1 C3

underscorelabelunderscorec0a6:
    y = 0x01; //  $C0A6  A0 01
    writeData(underscorevarunderscore0022, y); //  $C0A8  84 22
    writeData(underscorevarunderscore0020, y); //  $C0AA  84 20
    pla(); //  $C0AC  68
    y = a; //  $C0AD  A8
    pla(); //  $C0AE  68
    x = a; //  $C0AF  AA
    pla(); //  $C0B0  68
    plp(); //  $C0B1  28
    return; //  $C0B2  40

underscorefuncunderscorec0b3:
    a = M(underscorevarunderscore0024); //  $C0B3  A5 24
    if (z)
        goto underscorelabelunderscorec0ba; //  $C0B5  F0 03
    goto underscorelabelunderscorec14e; //  $C0B7  4C 4E C1

underscorelabelunderscorec0ba:
    a = M(underscorevarunderscore0016underscoreindexed); //  $C0BA  A5 16
    a &= 0x10; //  $C0BC  29 10
    if (z)
        goto underscorelabelunderscorec11e; //  $C0BE  F0 5E
    y = M(underscorevarunderscore05fc); //  $C0C0  AC FC 05
    if (!z)
        goto underscorelabelunderscorec123; //  $C0C3  D0 5E
    ++y; //  $C0C5  C8
    writeData(underscorevarunderscore05fc, y); //  $C0C6  8C FC 05
    y = M(underscorevarunderscore0025); //  $C0C9  A4 25
    compare(y, 0x10); //  $C0CB  C0 10
    if (z)
        goto underscorelabelunderscorec0ff; //  $C0CD  F0 30
    compare(y, 0x03); //  $C0CF  C0 03
    if (z)
        goto underscorelabelunderscorec0df; //  $C0D1  F0 0C
    compare(y, 0x04); //  $C0D3  C0 04
    if (z)
        goto underscorelabelunderscorec0df; //  $C0D5  F0 08
    compare(y, 0x0B); //  $C0D7  C0 0B
    if (z)
        goto underscorelabelunderscorec0df; //  $C0D9  F0 04
    compare(y, 0x0C); //  $C0DB  C0 0C
    if (!z)
        goto underscorelabelunderscorec123; //  $C0DD  D0 44

underscorelabelunderscorec0df:
    x = 0x05; //  $C0DF  A2 05

underscorelabelunderscorec0e1:
    a = M(underscorevarunderscore002aunderscoreindexed + x); //  $C0E1  B5 2A
    writeData(underscorevarunderscore0430underscoreindexed + x, a); //  $C0E3  9D 30 04
    --x; //  $C0E6  CA
    if (!n)
        goto underscorelabelunderscorec0e1; //  $C0E7  10 F8
    a = M(underscorevarunderscore0009); //  $C0E9  A5 09
    a &= 0x0E; //  $C0EB  29 0E
    writeData(PPUunderscoreMASK, a); //  $C0ED  8D 01 20
    writeData(underscorevarunderscore0009, a); //  $C0F0  85 09
    a = M(underscorevarunderscore0025); //  $C0F2  A5 25
    writeData(underscorevarunderscore001d, a); //  $C0F4  85 1D
    a = 0x10; //  $C0F6  A9 10
    writeData(underscorevarunderscore0025, a); //  $C0F8  85 25
    a = 0x07; //  $C0FA  A9 07
    goto underscorelabelunderscorec112; //  $C0FC  4C 12 C1

underscorelabelunderscorec0ff:
    a = M(underscorevarunderscore0009); //  $C0FF  A5 09
    a |= 0x10; //  $C101  09 10
    writeData(PPUunderscoreMASK, a); //  $C103  8D 01 20
    writeData(underscorevarunderscore0009, a); //  $C106  85 09
    a = 0x11; //  $C108  A9 11
    writeData(underscorevarunderscore0025, a); //  $C10A  85 25
    a = 0x30; //  $C10C  A9 30
    writeData(underscorevarunderscore001cunderscoreindexed, a); //  $C10E  85 1C
    a = 0x00; //  $C110  A9 00

underscorelabelunderscorec112:
    JSR(underscorefuncunderscored464, 13); //  $C112  20 64 D4
    JSR(underscorefuncunderscored4e2, 14); //  $C115  20 E2 D4
    JSR(underscorefuncunderscorec5d9, 15); //  $C118  20 D9 C5
    goto underscorelabelunderscored521; //  $C11B  4C 21 D5

underscorelabelunderscorec11e:
    a = 0x00; //  $C11E  A9 00
    writeData(underscorevarunderscore05fc, a); //  $C120  8D FC 05

underscorelabelunderscorec123:
    a = M(underscorevarunderscore0025); //  $C123  A5 25
    JSR(underscorejumpunderscoreengineunderscorec35e, 16); //  $C125  20 5E C3

underscorelabelunderscorec14e:
    a = 0x00; //  $C14E  A9 00
    writeData(underscorevarunderscore05ff, a); //  $C150  8D FF 05
    a = 0x01; //  $C153  A9 01
    writeData(underscorevarunderscore00b9, a); //  $C155  85 B9
    writeData(underscorevarunderscore00ba, a); //  $C157  85 BA
    a = M(underscorevarunderscore0026); //  $C159  A5 26
    if (z)
        goto underscorelabelunderscorec18d; //  $C15B  F0 30
    JSR(underscorefuncunderscored131, 17); //  $C15D  20 31 D1
    JSR(underscorefuncunderscored160, 18); //  $C160  20 60 D1
    a = M(underscorevarunderscore05ff); //  $C163  AD FF 05
    compare(a, 0x01); //  $C166  C9 01
    if (z)
        goto underscorelabelunderscorec176; //  $C168  F0 0C
    compare(a, 0x02); //  $C16A  C9 02
    if (z)
        goto underscorelabelunderscorec199; //  $C16C  F0 2B
    a = M(underscorevarunderscore0016underscoreindexed); //  $C16E  A5 16
    a &= 0x30; //  $C170  29 30
    compare(a, 0x10); //  $C172  C9 10
    if (!z)
        goto underscorelabelunderscorec189; //  $C174  D0 13

underscorelabelunderscorec176:
    a = 0x00; //  $C176  A9 00
    writeData(underscorevarunderscore0024, a); //  $C178  85 24
    writeData(underscorevarunderscore0025, a); //  $C17A  85 25
    JSR(underscorefuncunderscored4e2, 19); //  $C17C  20 E2 D4
    JSR(underscorefuncunderscorec5e1, 20); //  $C17F  20 E1 C5
    a = 0x02; //  $C182  A9 02
    writeData(underscorevarunderscore002aunderscoreindexed, a); //  $C184  85 2A
    writeData(underscorevarunderscore002d, a); //  $C186  85 2D
    goto Return; //  $C188  60

//------------------------------------------------------------------------

underscorelabelunderscorec189:
    x = M(underscorevarunderscore0026); //  $C189  A6 26
    if (!z)
        goto underscorelabelunderscorec190; //  $C18B  D0 03

underscorelabelunderscorec18d:
    goto underscorelabelunderscorec217; //  $C18D  4C 17 C2

underscorelabelunderscorec190:
    compare(a, 0x20); //  $C190  C9 20
    if (!z)
        goto underscorelabelunderscorec1a9; //  $C192  D0 15
    a = M(underscorevarunderscore05fd); //  $C194  AD FD 05
    if (!z)
        goto underscorelabelunderscorec1b7; //  $C197  D0 1E

underscorelabelunderscorec199:
    y = M(underscorevarunderscore05fe); //  $C199  AC FE 05
    ++y; //  $C19C  C8
    compare(y, 0x03); //  $C19D  C0 03
    if (!z)
        goto underscorelabelunderscorec1a3; //  $C19F  D0 02
    y = 0x00; //  $C1A1  A0 00

underscorelabelunderscorec1a3:
    writeData(underscorevarunderscore05fe, y); //  $C1A3  8C FE 05
    goto underscorelabelunderscorec1b2; //  $C1A6  4C B2 C1

underscorelabelunderscorec1a9:
    compare(a, 0x00); //  $C1A9  C9 00
    if (!z)
        goto underscorelabelunderscorec1b2; //  $C1AB  D0 05
    writeData(underscorevarunderscore05fd, a); //  $C1AD  8D FD 05
    if (z)
        goto underscorelabelunderscorec1bb; //  $C1B0  F0 09

underscorelabelunderscorec1b2:
    a = 0x01; //  $C1B2  A9 01
    writeData(underscorevarunderscore05fd, a); //  $C1B4  8D FD 05

underscorelabelunderscorec1b7:
    a = 0xFF; //  $C1B7  A9 FF
    writeData(underscorevarunderscore002d, a); //  $C1B9  85 2D

underscorelabelunderscorec1bb:
    compare(x, 0x01); //  $C1BB  E0 01
    if (!z)
        goto underscorelabelunderscorec217; //  $C1BD  D0 58
    a = 0x51; //  $C1BF  A9 51
    writeData(underscorevarunderscore0500underscoreindexed, a); //  $C1C1  8D 00 05
    a = 0x24; //  $C1C4  A9 24
    x = 0x04; //  $C1C6  A2 04

underscorelabelunderscorec1c8:
    writeData(underscorevarunderscore0501underscoreindexed + x, a); //  $C1C8  9D 01 05
    --x; //  $C1CB  CA
    if (!n)
        goto underscorelabelunderscorec1c8; //  $C1CC  10 FA
    a = M(underscorevarunderscore05fe); //  $C1CE  AD FE 05
    M(a) <<= 1; //  $C1D1  0A
    x = a; //  $C1D2  AA
    a = 0x26; //  $C1D3  A9 26
    writeData(underscorevarunderscore0501underscoreindexed + x, a); //  $C1D5  9D 01 05
    x = 0x26; //  $C1D8  A2 26
    y = 0x22; //  $C1DA  A0 22
    JSR(underscorefuncunderscorec71d, 21); //  $C1DC  20 1D C7
    a = M(underscorevarunderscore05fe); //  $C1DF  AD FE 05
    M(a) <<= 1; //  $C1E2  0A
    M(a) <<= 1; //  $C1E3  0A
    c = 0; //  $C1E4  18
    a += 0x03; //  $C1E5  69 03
    x = a; //  $C1E7  AA
    y = 0x05; //  $C1E8  A0 05

underscorelabelunderscorec1ea:
    a = M(underscorevarunderscore05f0underscoreindexed + x); //  $C1EA  BD F0 05
    a &= 0x0F; //  $C1ED  29 0F
    writeData(underscorevarunderscore0501underscoreindexed + y, a); //  $C1EF  99 01 05
    --y; //  $C1F2  88
    a = M(underscorevarunderscore05f0underscoreindexed + x); //  $C1F3  BD F0 05
    M(a) >>= 1; //  $C1F6  4A
    M(a) >>= 1; //  $C1F7  4A
    M(a) >>= 1; //  $C1F8  4A
    M(a) >>= 1; //  $C1F9  4A
    writeData(underscorevarunderscore0501underscoreindexed + y, a); //  $C1FA  99 01 05
    --x; //  $C1FD  CA
    --y; //  $C1FE  88
    if (!n)
        goto underscorelabelunderscorec1ea; //  $C1FF  10 E9
    a = M(underscorevarunderscore0501underscoreindexed); //  $C201  AD 01 05
    if (!z)
        goto underscorelabelunderscorec20b; //  $C204  D0 05
    a = 0x24; //  $C206  A9 24
    writeData(underscorevarunderscore0501underscoreindexed, a); //  $C208  8D 01 05

underscorelabelunderscorec20b:
    a = 0x16; //  $C20B  A9 16
    writeData(underscorevarunderscore0500underscoreindexed, a); //  $C20D  8D 00 05
    x = 0x12; //  $C210  A2 12
    y = 0x23; //  $C212  A0 23
    JSR(underscorefuncunderscorec71d, 22); //  $C214  20 1D C7

underscorelabelunderscorec217:
    a = M(underscorevarunderscore002d); //  $C217  A5 2D
    if (!z)
        goto underscorelabelunderscorec222; //  $C219  D0 07
    JSR(underscorefuncunderscored509, 23); //  $C21B  20 09 D5
    a = 0xFF; //  $C21E  A9 FF
    writeData(underscorevarunderscore002d, a); //  $C220  85 2D

underscorelabelunderscorec222:
    a = M(underscorevarunderscore0026); //  $C222  A5 26
    JSR(underscorejumpunderscoreengineunderscorec35e, 24); //  $C224  20 5E C3

underscorefuncunderscorec22b:
    a = 0x02; //  $C22B  A9 02
    JSR(underscorefuncunderscorec232, 25); //  $C22D  20 32 C2

underscorefuncunderscorec230:
    a = 0x01; //  $C230  A9 01

underscorefuncunderscorec232:
    writeData(underscorevarunderscore0001, a); //  $C232  85 01
    a = 0x24; //  $C234  A9 24
    writeData(underscorevarunderscore0000underscoreindexed, a); //  $C236  85 00
    goto underscorefuncunderscorec303; //  $C238  4C 03 C3

underscorefuncunderscorec23b:
    y = 0x00; //  $C23B  A0 00
    a = 0xF4; //  $C23D  A9 F4

underscorelabelunderscorec23f:
    writeData(underscorevarunderscore0200underscoreindexed + y, a); //  $C23F  99 00 02
    ++y; //  $C242  C8
    ++y; //  $C243  C8
    ++y; //  $C244  C8
    ++y; //  $C245  C8
    if (!z)
        goto underscorelabelunderscorec23f; //  $C246  D0 F7
    goto Return; //  $C248  60

//------------------------------------------------------------------------

underscorefuncunderscorec249:
    y = M(underscorevarunderscore0023); //  $C249  A4 23
    if (z)
        goto underscorelabelunderscorec262; //  $C24B  F0 15
    --y; //  $C24D  88
    a = y; //  $C24E  98
    M(a) <<= 1; //  $C24F  0A
    y = a; //  $C250  A8
    a = M(underscoredataunderscoree532underscoreindexed + y); //  $C251  B9 32 E5
    x = M(underscoredataunderscoree533underscoreindexed + y); //  $C254  BE 33 E5
    y = 0x00; //  $C257  A0 00
    writeData(underscorevarunderscore0023, y); //  $C259  84 23

underscorelabelunderscorec25b:
    writeData(underscorevarunderscore0000underscoreindexed, a); //  $C25B  85 00
    writeData(underscorevarunderscore0001, x); //  $C25D  86 01
    JSR(underscorefuncunderscorec3b8, 26); //  $C25F  20 B8 C3

underscorelabelunderscorec262:
    goto Return; //  $C262  60

//------------------------------------------------------------------------

underscorefuncunderscorec263:
    y = M(underscorevarunderscore0027); //  $C263  A4 27
    if (z)
        goto underscorelabelunderscorec262; //  $C265  F0 FB
    y = 0x00; //  $C267  A0 00
    writeData(underscorevarunderscore0027, y); //  $C269  84 27
    a = 0x00; //  $C26B  A9 00
    x = 0x04; //  $C26D  A2 04
    if (!z)
        goto underscorelabelunderscorec25b; //  $C26F  D0 EA

underscorelabelunderscorec271:
    --M(underscorevarunderscore001cunderscoreindexed); //  $C271  C6 1C
    if (!z)
        goto underscorelabelunderscorec283; //  $C273  D0 0E
    x = 0x05; //  $C275  A2 05

underscorelabelunderscorec277:
    a = M(underscorevarunderscore0430underscoreindexed + x); //  $C277  BD 30 04
    writeData(underscorevarunderscore002aunderscoreindexed + x, a); //  $C27A  95 2A
    --x; //  $C27C  CA
    if (!n)
        goto underscorelabelunderscorec277; //  $C27D  10 F8
    a = M(underscorevarunderscore001d); //  $C27F  A5 1D
    writeData(underscorevarunderscore0025, a); //  $C281  85 25

underscorelabelunderscorec283:
    goto Return; //  $C283  60

//------------------------------------------------------------------------

underscorefuncunderscorec284:
    x = 0x01; //  $C284  A2 01
    writeData(JOyPAD1, x); //  $C286  8E 16 40
    --x; //  $C289  CA
    writeData(JOyPAD1, x); //  $C28A  8E 16 40
    JSR(underscorefuncunderscorec291, 27); //  $C28D  20 91 C2
    ++x; //  $C290  E8

underscorefuncunderscorec291:
    y = 0x08; //  $C291  A0 08

underscorelabelunderscorec293:
    pha(); //  $C293  48
    a = M(JOyPAD1 + x); //  $C294  BD 16 40
    writeData(underscorevarunderscore0000underscoreindexed, a); //  $C297  85 00
    M(a) >>= 1; //  $C299  4A
    a |= M(underscorevarunderscore0000underscoreindexed); //  $C29A  05 00
    M(a) >>= 1; //  $C29C  4A
    pla(); //  $C29D  68
    M(a).rol(); //  $C29E  2A
    --y; //  $C29F  88
    if (!z)
        goto underscorelabelunderscorec293; //  $C2A0  D0 F1
    compare(a, M(underscorevarunderscore0440underscoreindexed + x)); //  $C2A2  DD 40 04
    if (!z)
        goto underscorelabelunderscorec2b6; //  $C2A5  D0 0F
    ++M(underscorevarunderscore0442underscoreindexed + x); //  $C2A7  FE 42 04
    y = M(underscorevarunderscore0442underscoreindexed + x); //  $C2AA  BC 42 04
    compare(y, 0x05); //  $C2AD  C0 05
    if (!c)
        goto underscorelabelunderscorec2be; //  $C2AF  90 0D
    writeData(underscorevarunderscore0016underscoreindexed + x, a); //  $C2B1  95 16
    goto underscorelabelunderscorec2b9; //  $C2B3  4C B9 C2

underscorelabelunderscorec2b6:
    writeData(underscorevarunderscore0440underscoreindexed + x, a); //  $C2B6  9D 40 04

underscorelabelunderscorec2b9:
    a = 0x00; //  $C2B9  A9 00
    writeData(underscorevarunderscore0442underscoreindexed + x, a); //  $C2BB  9D 42 04

underscorelabelunderscorec2be:
    goto Return; //  $C2BE  60

//------------------------------------------------------------------------

underscorefuncunderscorec2bf:
    a = M(underscorevarunderscore0021); //  $C2BF  A5 21
    if (z)
        goto underscorelabelunderscorec302; //  $C2C1  F0 3F
    a = 0x61; //  $C2C3  A9 61
    writeData(underscorevarunderscore0000underscoreindexed, a); //  $C2C5  85 00
    a = 0x05; //  $C2C7  A9 05
    writeData(underscorevarunderscore0001, a); //  $C2C9  85 01
    a = M(underscorevarunderscore0008); //  $C2CB  A5 08
    a &= 0xFB; //  $C2CD  29 FB
    writeData(PPUunderscoreCTRL, a); //  $C2CF  8D 00 20
    writeData(underscorevarunderscore0008, a); //  $C2D2  85 08
    x = M(PPUunderscoreSTATUS); //  $C2D4  AE 02 20
    y = 0x00; //  $C2D7  A0 00
    if (z)
        goto underscorelabelunderscorec2f4; //  $C2D9  F0 19

underscorelabelunderscorec2db:
    writeData(PPUunderscoreADDR, a); //  $C2DB  8D 06 20
    ++y; //  $C2DE  C8
    a = M(W(underscorevarunderscore0000underscoreindexed) + y); //  $C2DF  B1 00
    writeData(PPUunderscoreADDR, a); //  $C2E1  8D 06 20
    ++y; //  $C2E4  C8
    a = M(W(underscorevarunderscore0000underscoreindexed) + y); //  $C2E5  B1 00
    a &= 0x3F; //  $C2E7  29 3F
    x = a; //  $C2E9  AA

underscorelabelunderscorec2ea:
    ++y; //  $C2EA  C8
    a = M(W(underscorevarunderscore0000underscoreindexed) + y); //  $C2EB  B1 00
    writeData(PPUunderscoreDATA, a); //  $C2ED  8D 07 20
    --x; //  $C2F0  CA
    if (!z)
        goto underscorelabelunderscorec2ea; //  $C2F1  D0 F7
    ++y; //  $C2F3  C8

underscorelabelunderscorec2f4:
    a = M(W(underscorevarunderscore0000underscoreindexed) + y); //  $C2F4  B1 00
    if (!z)
        goto underscorelabelunderscorec2db; //  $C2F6  D0 E3
    a = 0x00; //  $C2F8  A9 00
    writeData(underscorevarunderscore0560, a); //  $C2FA  8D 60 05
    writeData(underscorevarunderscore0561underscoreindexed, a); //  $C2FD  8D 61 05
    writeData(underscorevarunderscore0021, a); //  $C300  85 21

underscorelabelunderscorec302:
    goto Return; //  $C302  60

//------------------------------------------------------------------------

underscorefuncunderscorec303:
    a = M(PPUunderscoreSTATUS); //  $C303  AD 02 20

underscoredataunderscorec306underscoreindexed:
    a = M(underscorevarunderscore0008); //  $C306  A5 08
    a &= 0xFB; //  $C308  29 FB
    writeData(PPUunderscoreCTRL, a); //  $C30A  8D 00 20
    writeData(underscorevarunderscore0008, a); //  $C30D  85 08
    a = 0x1C; //  $C30F  A9 1C
    c = 0; //  $C311  18

underscorelabelunderscorec312:
    a += 0x04; //  $C312  69 04
    --M(underscorevarunderscore0001); //  $C314  C6 01
    if (!z)
        goto underscorelabelunderscorec312; //  $C316  D0 FA
    writeData(underscorevarunderscore0002underscoreindexed, a); //  $C318  85 02
    writeData(PPUunderscoreADDR, a); //  $C31A  8D 06 20
    a = 0x00; //  $C31D  A9 00
    writeData(PPUunderscoreADDR, a); //  $C31F  8D 06 20
    x = 0x04; //  $C322  A2 04
    y = 0x00; //  $C324  A0 00
    a = M(underscorevarunderscore0000underscoreindexed); //  $C326  A5 00

underscorelabelunderscorec328:
    writeData(PPUunderscoreDATA, a); //  $C328  8D 07 20
    --y; //  $C32B  88
    if (!z)
        goto underscorelabelunderscorec328; //  $C32C  D0 FA
    --x; //  $C32E  CA
    if (!z)
        goto underscorelabelunderscorec328; //  $C32F  D0 F7
    a = M(underscorevarunderscore0002underscoreindexed); //  $C331  A5 02
    a += 0x03; //  $C333  69 03
    writeData(PPUunderscoreADDR, a); //  $C335  8D 06 20
    a = 0xC0; //  $C338  A9 C0
    writeData(PPUunderscoreADDR, a); //  $C33A  8D 06 20
    y = 0x40; //  $C33D  A0 40
    a = 0x00; //  $C33F  A9 00

underscorelabelunderscorec341:
    writeData(PPUunderscoreDATA, a); //  $C341  8D 07 20
    --y; //  $C344  88
    if (!z)
        goto underscorelabelunderscorec341; //  $C345  D0 FA
    goto Return; //  $C347  60

//------------------------------------------------------------------------

underscorefuncunderscorec348:
    x = 0x01; //  $C348  A2 01
    --M(underscorevarunderscore002aunderscoreindexed); //  $C34A  C6 2A
    if (!n)
        goto underscorelabelunderscorec354; //  $C34C  10 06
    a = 0x0A; //  $C34E  A9 0A
    writeData(underscorevarunderscore002aunderscoreindexed, a); //  $C350  85 2A
    x = 0x03; //  $C352  A2 03

underscorelabelunderscorec354:
    a = M(underscorevarunderscore002bunderscoreindexed + x); //  $C354  B5 2B
    if (z)
        goto underscorelabelunderscorec35a; //  $C356  F0 02
    --M(underscorevarunderscore002bunderscoreindexed + x); //  $C358  D6 2B

underscorelabelunderscorec35a:
    --x; //  $C35A  CA
    if (!n)
        goto underscorelabelunderscorec354; //  $C35B  10 F7
    goto Return; //  $C35D  60

//------------------------------------------------------------------------

underscorejumpunderscoreengineunderscorec35e: //  jump engine detected
    writeData(underscorevarunderscore0028, x); //  $C35E  86 28
    writeData(underscorevarunderscore0029, y); //  $C360  84 29
    M(a) <<= 1; //  $C362  0A
    y = a; //  $C363  A8
    ++y; //  $C364  C8
    pla(); //  $C365  68
    writeData(underscorevarunderscore0014underscoreindexed, a); //  $C366  85 14
    pla(); //  $C368  68
    writeData(underscorevarunderscore0015, a); //  $C369  85 15
    a = M(W(underscorevarunderscore0014underscoreindexed) + y); //  $C36B  B1 14
    x = a; //  $C36D  AA
    ++y; //  $C36E  C8
    a = M(W(underscorevarunderscore0014underscoreindexed) + y); //  $C36F  B1 14
    writeData(underscorevarunderscore0015, a); //  $C371  85 15
    writeData(underscorevarunderscore0014underscoreindexed, x); //  $C373  86 14
    x = M(underscorevarunderscore0028); //  $C375  A6 28
    y = M(underscorevarunderscore0029); //  $C377  A4 29
    indirectJumpAddress = W(underscorevarunderscore0014underscoreindexed); goto IndirectJumpResult; //  $C379  6C 14 00

underscorelabelunderscorec37c:
    writeData(PPUunderscoreADDR, a); //  $C37C  8D 06 20
    ++y; //  $C37F  C8
    a = M(W(underscorevarunderscore0000underscoreindexed) + y); //  $C380  B1 00
    writeData(PPUunderscoreADDR, a); //  $C382  8D 06 20
    ++y; //  $C385  C8
    a = M(W(underscorevarunderscore0000underscoreindexed) + y); //  $C386  B1 00
    M(a) <<= 1; //  $C388  0A
    pha(); //  $C389  48
    a = M(underscorevarunderscore0008); //  $C38A  A5 08
    a |= 0x04; //  $C38C  09 04
    if (c)
        goto underscorelabelunderscorec392; //  $C38E  B0 02
    a &= 0xFB; //  $C390  29 FB

underscorelabelunderscorec392:
    writeData(PPUunderscoreCTRL, a); //  $C392  8D 00 20
    writeData(underscorevarunderscore0008, a); //  $C395  85 08
    pla(); //  $C397  68
    M(a) <<= 1; //  $C398  0A
    if (!c)
        goto underscorelabelunderscorec39e; //  $C399  90 03
    a |= 0x02; //  $C39B  09 02
    ++y; //  $C39D  C8

underscorelabelunderscorec39e:
    M(a) >>= 1; //  $C39E  4A
    M(a) >>= 1; //  $C39F  4A
    x = a; //  $C3A0  AA

underscorelabelunderscorec3a1:
    if (c)
        goto underscorelabelunderscorec3a4; //  $C3A1  B0 01
    ++y; //  $C3A3  C8

underscorelabelunderscorec3a4:
    a = M(W(underscorevarunderscore0000underscoreindexed) + y); //  $C3A4  B1 00
    writeData(PPUunderscoreDATA, a); //  $C3A6  8D 07 20
    --x; //  $C3A9  CA
    if (!z)
        goto underscorelabelunderscorec3a1; //  $C3AA  D0 F5
    c = 1; //  $C3AC  38
    a = y; //  $C3AD  98
    a += M(underscorevarunderscore0000underscoreindexed); //  $C3AE  65 00
    writeData(underscorevarunderscore0000underscoreindexed, a); //  $C3B0  85 00
    a = 0x00; //  $C3B2  A9 00
    a += M(underscorevarunderscore0001); //  $C3B4  65 01
    writeData(underscorevarunderscore0001, a); //  $C3B6  85 01

underscorefuncunderscorec3b8:
    x = M(PPUunderscoreSTATUS); //  $C3B8  AE 02 20
    y = 0x00; //  $C3BB  A0 00
    a = M(W(underscorevarunderscore0000underscoreindexed) + y); //  $C3BD  B1 00
    if (!z)
        goto underscorelabelunderscorec37c; //  $C3BF  D0 BB

underscorefuncunderscorec3c1:
    pha(); //  $C3C1  48
    a = M(underscorevarunderscore000a); //  $C3C2  A5 0A
    writeData(PPUunderscoreSCROLL, a); //  $C3C4  8D 05 20
    a = M(0x0B); //  $C3C7  A5 0B
    writeData(PPUunderscoreSCROLL, a); //  $C3C9  8D 05 20
    pla(); //  $C3CC  68
    goto Return; //  $C3CD  60

//------------------------------------------------------------------------

underscorelabelunderscorec3ce:
    a = 0x01; //  $C3CE  A9 01
    writeData(underscorevarunderscore0021, a); //  $C3D0  85 21
    y = 0x00; //  $C3D2  A0 00
    a = M(W(underscorevarunderscore0002underscoreindexed) + y); //  $C3D4  B1 02
    a &= 0x0F; //  $C3D6  29 0F
    writeData(underscorevarunderscore0005, a); //  $C3D8  85 05
    a = M(W(underscorevarunderscore0002underscoreindexed) + y); //  $C3DA  B1 02
    M(a) >>= 1; //  $C3DC  4A
    M(a) >>= 1; //  $C3DD  4A
    M(a) >>= 1; //  $C3DE  4A
    M(a) >>= 1; //  $C3DF  4A
    writeData(underscorevarunderscore0004, a); //  $C3E0  85 04
    x = M(underscorevarunderscore0560); //  $C3E2  AE 60 05

underscorelabelunderscorec3e5:
    a = M(underscorevarunderscore0001); //  $C3E5  A5 01
    writeData(underscorevarunderscore0561underscoreindexed + x, a); //  $C3E7  9D 61 05
    JSR(underscorefuncunderscorec426, 28); //  $C3EA  20 26 C4
    a = M(underscorevarunderscore0000underscoreindexed); //  $C3ED  A5 00
    writeData(underscorevarunderscore0561underscoreindexed + x, a); //  $C3EF  9D 61 05
    JSR(underscorefuncunderscorec426, 29); //  $C3F2  20 26 C4
    a = M(underscorevarunderscore0005); //  $C3F5  A5 05
    writeData(underscorevarunderscore0006, a); //  $C3F7  85 06
    writeData(underscorevarunderscore0561underscoreindexed + x, a); //  $C3F9  9D 61 05

underscorelabelunderscorec3fc:
    JSR(underscorefuncunderscorec426, 30); //  $C3FC  20 26 C4
    ++y; //  $C3FF  C8
    a = M(W(underscorevarunderscore0002underscoreindexed) + y); //  $C400  B1 02
    writeData(underscorevarunderscore0561underscoreindexed + x, a); //  $C402  9D 61 05
    --M(underscorevarunderscore0006); //  $C405  C6 06
    if (!z)
        goto underscorelabelunderscorec3fc; //  $C407  D0 F3
    JSR(underscorefuncunderscorec426, 31); //  $C409  20 26 C4
    writeData(underscorevarunderscore0560, x); //  $C40C  8E 60 05
    c = 0; //  $C40F  18
    a = 0x20; //  $C410  A9 20
    a += M(underscorevarunderscore0000underscoreindexed); //  $C412  65 00
    writeData(underscorevarunderscore0000underscoreindexed, a); //  $C414  85 00
    a = 0x00; //  $C416  A9 00
    a += M(underscorevarunderscore0001); //  $C418  65 01
    writeData(underscorevarunderscore0001, a); //  $C41A  85 01
    --M(underscorevarunderscore0004); //  $C41C  C6 04
    if (!z)
        goto underscorelabelunderscorec3e5; //  $C41E  D0 C5
    a = 0x00; //  $C420  A9 00
    writeData(underscorevarunderscore0561underscoreindexed + x, a); //  $C422  9D 61 05
    goto Return; //  $C425  60

//------------------------------------------------------------------------

underscorefuncunderscorec426:
    ++x; //  $C426  E8
    a = x; //  $C427  8A
    compare(a, 0x4F); //  $C428  C9 4F
    if (!c)
        goto underscorelabelunderscorec436; //  $C42A  90 0A
    x = M(underscorevarunderscore0560); //  $C42C  AE 60 05
    a = 0x00; //  $C42F  A9 00
    writeData(underscorevarunderscore0561underscoreindexed + x, a); //  $C431  9D 61 05
    pla(); //  $C434  68
    pla(); //  $C435  68

underscorelabelunderscorec436:
    goto Return; //  $C436  60

//------------------------------------------------------------------------

underscorefuncunderscorec4bf:
    JSR(underscorefuncunderscorec502, 32); //  $C4BF  20 02 C5
    a += M(underscorevarunderscore0001); //  $C4C2  65 01
    compare(a, 0x0A); //  $C4C4  C9 0A
    if (!c)
        goto underscorelabelunderscorec4ca; //  $C4C6  90 02
    a += 0x05; //  $C4C8  69 05

underscorelabelunderscorec4ca:
    c = 0; //  $C4CA  18
    a += M(underscorevarunderscore0002underscoreindexed); //  $C4CB  65 02
    writeData(underscorevarunderscore0002underscoreindexed, a); //  $C4CD  85 02
    a = M(underscorevarunderscore0003); //  $C4CF  A5 03
    a &= 0xF0; //  $C4D1  29 F0
    a += M(underscorevarunderscore0002underscoreindexed); //  $C4D3  65 02
    if (!c)
        goto underscorelabelunderscorec4db; //  $C4D5  90 04

underscorelabelunderscorec4d7:
    a += 0x5F; //  $C4D7  69 5F
    c = 1; //  $C4D9  38
    goto Return; //  $C4DA  60

//------------------------------------------------------------------------

underscorelabelunderscorec4db:
    compare(a, 0xA0); //  $C4DB  C9 A0
    if (c)
        goto underscorelabelunderscorec4d7; //  $C4DD  B0 F8
    goto Return; //  $C4DF  60

//------------------------------------------------------------------------

underscorefuncunderscorec4e0:
    JSR(underscorefuncunderscorec502, 33); //  $C4E0  20 02 C5
    a -= M(underscorevarunderscore0001); //  $C4E3  E5 01
    writeData(underscorevarunderscore0001, a); //  $C4E5  85 01
    if (c)
        goto underscorelabelunderscorec4f3; //  $C4E7  B0 0A
    a += 0x0A; //  $C4E9  69 0A
    writeData(underscorevarunderscore0001, a); //  $C4EB  85 01
    a = M(underscorevarunderscore0002underscoreindexed); //  $C4ED  A5 02
    a += 0x0F; //  $C4EF  69 0F
    writeData(underscorevarunderscore0002underscoreindexed, a); //  $C4F1  85 02

underscorelabelunderscorec4f3:
    a = M(underscorevarunderscore0003); //  $C4F3  A5 03
    a &= 0xF0; //  $C4F5  29 F0
    c = 1; //  $C4F7  38
    a -= M(underscorevarunderscore0002underscoreindexed); //  $C4F8  E5 02
    if (c)
        goto underscorelabelunderscorec4ff; //  $C4FA  B0 03
    a += 0xA0; //  $C4FC  69 A0
    c = 0; //  $C4FE  18

underscorelabelunderscorec4ff:
    a |= M(underscorevarunderscore0001); //  $C4FF  05 01
    goto Return; //  $C501  60

//------------------------------------------------------------------------

underscorefuncunderscorec502:
    pha(); //  $C502  48
    a &= 0x0F; //  $C503  29 0F
    writeData(underscorevarunderscore0001, a); //  $C505  85 01
    pla(); //  $C507  68
    a &= 0xF0; //  $C508  29 F0
    writeData(underscorevarunderscore0002underscoreindexed, a); //  $C50A  85 02
    a = M(underscorevarunderscore0003); //  $C50C  A5 03
    a &= 0x0F; //  $C50E  29 0F
    goto Return; //  $C510  60

//------------------------------------------------------------------------

underscorefuncunderscorec511:
    a = 0x00; //  $C511  A9 00
    writeData(underscorevarunderscore0004, a); //  $C513  85 04
    c = 0; //  $C515  18
    a = M(underscorevarunderscore0000underscoreindexed); //  $C516  A5 00
    a += 0x10; //  $C518  69 10
    a &= 0xF0; //  $C51A  29 F0
    M(a) >>= 1; //  $C51C  4A
    M(a) >>= 1; //  $C51D  4A
    y = a; //  $C51E  A8
    a = M(underscorevarunderscore0000underscoreindexed); //  $C51F  A5 00
    a &= 0x07; //  $C521  29 07
    M(a) <<= 1; //  $C523  0A
    M(a) <<= 1; //  $C524  0A
    x = a; //  $C525  AA

underscorelabelunderscorec526:
    a = M(underscorevarunderscore00c3underscoreindexed + y); //  $C526  B9 C3 00
    if (z)
        goto underscorelabelunderscorec57c; //  $C529  F0 51
    a = M(underscorevarunderscore00c7underscoreindexed + x); //  $C52B  B5 C7
    if (z)
        goto underscorelabelunderscorec555; //  $C52D  F0 26

underscorelabelunderscorec52f:
    c = 1; //  $C52F  38
    a = M(underscorevarunderscore00c6underscoreindexed + y); //  $C530  B9 C6 00
    writeData(underscorevarunderscore0003, a); //  $C533  85 03
    a = M(underscorevarunderscore00caunderscoreindexed + x); //  $C535  B5 CA
    JSR(underscorefuncunderscorec4e0, 34); //  $C537  20 E0 C4
    a = M(underscorevarunderscore00c5underscoreindexed + y); //  $C53A  B9 C5 00
    writeData(underscorevarunderscore0003, a); //  $C53D  85 03
    a = M(underscorevarunderscore00c9underscoreindexed + x); //  $C53F  B5 C9
    JSR(underscorefuncunderscorec4e0, 35); //  $C541  20 E0 C4
    a = M(underscorevarunderscore00c4underscoreindexed + y); //  $C544  B9 C4 00
    writeData(underscorevarunderscore0003, a); //  $C547  85 03
    a = M(underscorevarunderscore00c8underscoreindexed + x); //  $C549  B5 C8
    JSR(underscorefuncunderscorec4e0, 36); //  $C54B  20 E0 C4
    if (c)
        goto underscorelabelunderscorec580; //  $C54E  B0 30
    a = M(underscorevarunderscore00c3underscoreindexed + y); //  $C550  B9 C3 00
    if (!z)
        goto underscorelabelunderscorec585; //  $C553  D0 30

underscorelabelunderscorec555:
    a = 0xFF; //  $C555  A9 FF
    writeData(underscorevarunderscore0004, a); //  $C557  85 04
    c = 1; //  $C559  38

underscorelabelunderscorec55a:
    a = y; //  $C55A  98
    if (!z)
        goto underscorelabelunderscorec57b; //  $C55B  D0 1E
    if (!c)
        goto underscorelabelunderscorec56f; //  $C55D  90 10
    a = M(underscorevarunderscore00c7underscoreindexed + x); //  $C55F  B5 C7
    writeData(underscorevarunderscore00c3underscoreindexed, a); //  $C561  85 C3
    a = M(underscorevarunderscore00c8underscoreindexed + x); //  $C563  B5 C8
    writeData(underscorevarunderscore00c4underscoreindexed, a); //  $C565  85 C4
    a = M(underscorevarunderscore00c9underscoreindexed + x); //  $C567  B5 C9
    writeData(underscorevarunderscore00c5underscoreindexed, a); //  $C569  85 C5
    a = M(underscorevarunderscore00caunderscoreindexed + x); //  $C56B  B5 CA
    writeData(underscorevarunderscore00c6underscoreindexed, a); //  $C56D  85 C6

underscorelabelunderscorec56f:
    a = M(underscorevarunderscore0000underscoreindexed); //  $C56F  A5 00
    a &= 0x08; //  $C571  29 08
    if (z)
        goto underscorelabelunderscorec57b; //  $C573  F0 06
    --x; //  $C575  CA
    --x; //  $C576  CA
    --x; //  $C577  CA
    --x; //  $C578  CA
    if (!n)
        goto underscorelabelunderscorec526; //  $C579  10 AB

underscorelabelunderscorec57b:
    goto Return; //  $C57B  60

//------------------------------------------------------------------------

underscorelabelunderscorec57c:
    a = M(underscorevarunderscore00c7underscoreindexed + x); //  $C57C  B5 C7
    if (z)
        goto underscorelabelunderscorec52f; //  $C57E  F0 AF

underscorelabelunderscorec580:
    a = M(underscorevarunderscore00c3underscoreindexed + y); //  $C580  B9 C3 00
    if (!z)
        goto underscorelabelunderscorec555; //  $C583  D0 D0

underscorelabelunderscorec585:
    c = 0; //  $C585  18
    if (!c)
        goto underscorelabelunderscorec55a; //  $C586  90 D2

underscorefuncunderscorec588:
    a = M(underscorevarunderscore05ec); //  $C588  AD EC 05
    a &= 0x02; //  $C58B  29 02
    writeData(underscorevarunderscore0007, a); //  $C58D  85 07
    a = M(underscorevarunderscore05ed); //  $C58F  AD ED 05
    a &= 0x02; //  $C592  29 02
    a ^= M(underscorevarunderscore0007); //  $C594  45 07
    c = 0; //  $C596  18
    if (z)
        goto underscorelabelunderscorec59a; //  $C597  F0 01
    c = 1; //  $C599  38

underscorelabelunderscorec59a:
    M(underscorevarunderscore05ec).ror(); //  $C59A  6E EC 05
    M(underscorevarunderscore05ed).ror(); //  $C59D  6E ED 05
    M(underscorevarunderscore05ee).ror(); //  $C5A0  6E EE 05
    M(underscorevarunderscore05ef).ror(); //  $C5A3  6E EF 05
    a = M(underscorevarunderscore05ec); //  $C5A6  AD EC 05
    goto Return; //  $C5A9  60

//------------------------------------------------------------------------

underscorelabelunderscorec5aa:
    JSR(underscorefuncunderscorec5e1, 37); //  $C5AA  20 E1 C5
    JSR(underscorefuncunderscorec230, 38); //  $C5AD  20 30 C2
    JSR(underscorefuncunderscorec5d9, 39); //  $C5B0  20 D9 C5
    a = 0x02; //  $C5B3  A9 02
    writeData(underscorevarunderscore0001, a); //  $C5B5  85 01
    a = 0x50; //  $C5B7  A9 50
    writeData(underscorevarunderscore0000underscoreindexed, a); //  $C5B9  85 00
    JSR(underscorefuncunderscorec303, 40); //  $C5BB  20 03 C3
    JSR(underscorefuncunderscorec23b, 41); //  $C5BE  20 3B C2
    JSR(underscorefuncunderscorec5d9, 42); //  $C5C1  20 D9 C5
    x = 0x04; //  $C5C4  A2 04
    y = 0xE4; //  $C5C6  A0 E4
    JSR(underscorefuncunderscorec617, 43); //  $C5C8  20 17 C6
    a = 0x01; //  $C5CB  A9 01
    writeData(underscorevarunderscore0023, a); //  $C5CD  85 23
    a = 0x01; //  $C5CF  A9 01
    writeData(underscorevarunderscore05fd, a); //  $C5D1  8D FD 05
    ++M(underscorevarunderscore0026); //  $C5D4  E6 26
    goto underscorefuncunderscorec5ee; //  $C5D6  4C EE C5

underscorefuncunderscorec5d9:
    JSR(underscorefuncunderscorec61e, 44); //  $C5D9  20 1E C6

underscorelabelunderscorec5dc:
    a = M(underscorevarunderscore0020); //  $C5DC  A5 20
    if (z)
        goto underscorelabelunderscorec5dc; //  $C5DE  F0 FC

underscorelabelunderscorec5e0:
    goto Return; //  $C5E0  60

//------------------------------------------------------------------------

underscorefuncunderscorec5e1:
    JSR(underscorefuncunderscorec5d9, 45); //  $C5E1  20 D9 C5
    a = M(underscorevarunderscore0009); //  $C5E4  A5 09
    a &= 0xE7; //  $C5E6  29 E7

underscorelabelunderscorec5e8:
    writeData(underscorevarunderscore0009, a); //  $C5E8  85 09
    writeData(PPUunderscoreMASK, a); //  $C5EA  8D 01 20
    goto Return; //  $C5ED  60

//------------------------------------------------------------------------

underscorefuncunderscorec5ee:
    JSR(underscorefuncunderscorec5d9, 46); //  $C5EE  20 D9 C5
    a = M(underscorevarunderscore0009); //  $C5F1  A5 09
    a |= 0x18; //  $C5F3  09 18
    if (!z)
        goto underscorelabelunderscorec5e8; //  $C5F5  D0 F1

underscorefuncunderscorec5f7:
    writeData(underscorevarunderscore00a2underscoreindexed, y); //  $C5F7  84 A2
    x = 0x00; //  $C5F9  A2 00

underscorelabelunderscorec5fb:
    a = M(underscorevarunderscore0300underscoreindexed + y); //  $C5FB  B9 00 03
    writeData(underscorevarunderscore0030underscoreindexed + x, a); //  $C5FE  95 30
    ++y; //  $C600  C8
    ++x; //  $C601  E8
    compare(x, 0x50); //  $C602  E0 50
    if (!z)
        goto underscorelabelunderscorec5fb; //  $C604  D0 F5
    goto Return; //  $C606  60

//------------------------------------------------------------------------

underscorefuncunderscorec607:
    y = M(underscorevarunderscore00a2underscoreindexed); //  $C607  A4 A2
    x = 0x00; //  $C609  A2 00

underscorelabelunderscorec60b:
    a = M(underscorevarunderscore0030underscoreindexed + x); //  $C60B  B5 30
    writeData(underscorevarunderscore0300underscoreindexed + y, a); //  $C60D  99 00 03
    ++y; //  $C610  C8
    ++x; //  $C611  E8
    compare(x, 0x50); //  $C612  E0 50
    if (!z)
        goto underscorelabelunderscorec60b; //  $C614  D0 F5
    goto Return; //  $C616  60

//------------------------------------------------------------------------

underscorefuncunderscorec617:
    writeData(underscorevarunderscore0000underscoreindexed, x); //  $C617  86 00
    writeData(underscorevarunderscore0001, y); //  $C619  84 01
    goto underscorefuncunderscorec3b8; //  $C61B  4C B8 C3

underscorefuncunderscorec61e:
    a = 0x00; //  $C61E  A9 00
    writeData(underscorevarunderscore0020, a); //  $C620  85 20
    writeData(underscorevarunderscore0022, a); //  $C622  85 22
    goto Return; //  $C624  60

//------------------------------------------------------------------------

underscorelabelunderscorec625:
    a = M(underscorevarunderscore002d); //  $C625  A5 2D
    if (!z)
        goto underscorelabelunderscorec62d; //  $C627  D0 04
    a = M(0x1E); //  $C629  A5 1E
    writeData(underscorevarunderscore0025, a); //  $C62B  85 25

underscorelabelunderscorec62d:
    goto Return; //  $C62D  60

//------------------------------------------------------------------------

underscorelabelunderscorec637:
    y = 0x00; //  $C637  A0 00
    a = y; //  $C639  98

underscorelabelunderscorec63a:
    writeData(underscorevarunderscore0300underscoreindexed + y, a); //  $C63A  99 00 03
    ++y; //  $C63D  C8
    if (!z)
        goto underscorelabelunderscorec63a; //  $C63E  D0 FA
    goto Return; //  $C640  60

//------------------------------------------------------------------------

underscorefuncunderscorec641:
    a = 0x00; //  $C641  A9 00
    x = 0x30; //  $C643  A2 30

underscorelabelunderscorec645:
    writeData(underscorevarunderscore0000underscoreindexed + x, a); //  $C645  95 00
    ++x; //  $C647  E8
    if (!z)
        goto underscorelabelunderscorec645; //  $C648  D0 FB
    goto Return; //  $C64A  60

//------------------------------------------------------------------------

underscorefuncunderscorec64b:
    a = 0x00; //  $C64B  A9 00
    x = 0x7F; //  $C64D  A2 7F

underscorelabelunderscorec64f:
    writeData(underscorevarunderscore0040underscoreindexed + x, a); //  $C64F  95 40
    --x; //  $C651  CA
    if (!n)
        goto underscorelabelunderscorec64f; //  $C652  10 FB
    goto Return; //  $C654  60

//------------------------------------------------------------------------

underscorelabelunderscorec67c:
    a = M(underscorevarunderscore000c); //  $C67C  A5 0C
    M(a) <<= 1; //  $C67E  0A
    y = a; //  $C67F  A8
    a = M(underscoredataunderscoreeb30underscoreindexed + y); //  $C680  B9 30 EB
    writeData(underscorevarunderscore0010underscoreindexed, a); //  $C683  85 10
    a = M(underscoredataunderscoreeb31underscoreindexed + y); //  $C685  B9 31 EB
    writeData(0x11, a); //  $C688  85 11
    y = 0x00; //  $C68A  A0 00
    x = 0x00; //  $C68C  A2 00

underscorelabelunderscorec68e:
    a = M(W(underscorevarunderscore0010underscoreindexed) + y); //  $C68E  B1 10
    compare(a, 0xAA); //  $C690  C9 AA
    if (!z)
        goto underscorelabelunderscorec695; //  $C692  D0 01

underscorelabelunderscorec694:
    goto Return; //  $C694  60

//------------------------------------------------------------------------

underscorelabelunderscorec695:
    c = 0; //  $C695  18
    a += M(underscorevarunderscore00b1); //  $C696  65 B1
    compare(a, 0xA8); //  $C698  C9 A8
    if (!c)
        goto underscorelabelunderscorec69e; //  $C69A  90 02
    a = 0xF4; //  $C69C  A9 F4

underscorelabelunderscorec69e:
    writeData(underscorevarunderscore000d, a); //  $C69E  85 0D
    ++y; //  $C6A0  C8
    a = M(W(underscorevarunderscore0010underscoreindexed) + y); //  $C6A1  B1 10
    c = 0; //  $C6A3  18
    a += M(underscorevarunderscore00b2); //  $C6A4  65 B2
    writeData(underscorevarunderscore000e, a); //  $C6A6  85 0E
    ++y; //  $C6A8  C8
    a = M(underscorevarunderscore000d); //  $C6A9  A5 0D
    writeData(underscorevarunderscore0200underscoreindexed + x, a); //  $C6AB  9D 00 02
    ++x; //  $C6AE  E8
    a = 0x56; //  $C6AF  A9 56
    writeData(underscorevarunderscore0200underscoreindexed + x, a); //  $C6B1  9D 00 02
    ++x; //  $C6B4  E8
    a = 0x00; //  $C6B5  A9 00
    writeData(underscorevarunderscore0200underscoreindexed + x, a); //  $C6B7  9D 00 02
    ++x; //  $C6BA  E8
    a = M(underscorevarunderscore000e); //  $C6BB  A5 0E
    writeData(underscorevarunderscore0200underscoreindexed + x, a); //  $C6BD  9D 00 02
    ++x; //  $C6C0  E8
    goto underscorelabelunderscorec68e; //  $C6C1  4C 8E C6

underscorefuncunderscorec6c4:
    a = M(underscorevarunderscore00ad); //  $C6C4  A5 AD
    if (z)
        goto underscorelabelunderscorec694; //  $C6C6  F0 CC
    a = 0x00; //  $C6C8  A9 00
    writeData(underscorevarunderscore00ad, a); //  $C6CA  85 AD

underscorefuncunderscorec6cc:
    a = 0xD6; //  $C6CC  A9 D6
    y = M(underscorevarunderscore001f); //  $C6CE  A4 1F
    compare(y, 0x02); //  $C6D0  C0 02
    if (!z)
        goto underscorelabelunderscorec6d6; //  $C6D2  D0 02
    a = 0xD4; //  $C6D4  A9 D4

underscorelabelunderscorec6d6:
    writeData(underscorevarunderscore000c, a); //  $C6D6  85 0C
    x = 0x09; //  $C6D8  A2 09

underscorelabelunderscorec6da:
    y = M(underscorevarunderscore000c); //  $C6DA  A4 0C
    a = M(underscorevarunderscore03f0underscoreindexed + x); //  $C6DC  BD F0 03
    if (z)
        goto underscorelabelunderscorec6e2; //  $C6DF  F0 01
    --y; //  $C6E1  88

underscorelabelunderscorec6e2:
    a = y; //  $C6E2  98
    writeData(underscorevarunderscore0501underscoreindexed + x, a); //  $C6E3  9D 01 05
    --x; //  $C6E6  CA
    if (!n)
        goto underscorelabelunderscorec6da; //  $C6E7  10 F1
    a = 0x1A; //  $C6E9  A9 1A
    writeData(underscorevarunderscore0500underscoreindexed, a); //  $C6EB  8D 00 05
    x = 0x4C; //  $C6EE  A2 4C
    y = 0x23; //  $C6F0  A0 23
    goto underscorefuncunderscorec71d; //  $C6F2  4C 1D C7

underscorefuncunderscorec6f5:
    a = M(underscorevarunderscore00be); //  $C6F5  A5 BE
    if (z)
        goto underscorelabelunderscorec694; //  $C6F7  F0 9B
    a = 0x00; //  $C6F9  A9 00
    writeData(underscorevarunderscore00be, a); //  $C6FB  85 BE
    x = M(underscorevarunderscore00ba); //  $C6FD  A6 BA
    y = 0x00; //  $C6FF  A0 00

underscorelabelunderscorec701:
    compare(x, 0x00); //  $C701  E0 00
    if (z)
        goto underscorelabelunderscorec70a; //  $C703  F0 05
    --x; //  $C705  CA
    a = 0xD9; //  $C706  A9 D9
    if (!z)
        goto underscorelabelunderscorec70c; //  $C708  D0 02

underscorelabelunderscorec70a:
    a = 0xB7; //  $C70A  A9 B7

underscorelabelunderscorec70c:
    writeData(underscorevarunderscore0501underscoreindexed + y, a); //  $C70C  99 01 05
    ++y; //  $C70F  C8
    compare(y, 0x03); //  $C710  C0 03
    if (!z)
        goto underscorelabelunderscorec701; //  $C712  D0 ED
    a = 0x13; //  $C714  A9 13
    writeData(underscorevarunderscore0500underscoreindexed, a); //  $C716  8D 00 05
    x = 0x43; //  $C719  A2 43
    y = 0x23; //  $C71B  A0 23

underscorefuncunderscorec71d:
    writeData(underscorevarunderscore0000underscoreindexed, x); //  $C71D  86 00
    writeData(underscorevarunderscore0001, y); //  $C71F  84 01
    x = 0x00; //  $C721  A2 00
    y = 0x05; //  $C723  A0 05
    writeData(underscorevarunderscore0002underscoreindexed, x); //  $C725  86 02
    writeData(underscorevarunderscore0003, y); //  $C727  84 03
    goto underscorelabelunderscorec3ce; //  $C729  4C CE C3

underscorelabelunderscorec72c:
    a = M(underscorevarunderscore002d); //  $C72C  A5 2D
    if (z)
        goto underscorelabelunderscorec73a; //  $C72E  F0 0A
    a = M(underscorevarunderscore001f); //  $C730  A5 1F
    compare(a, 0x02); //  $C732  C9 02
    if (z)
        goto underscorelabelunderscorec739; //  $C734  F0 03
    goto underscorefuncunderscorecc94; //  $C736  4C 94 CC

underscorelabelunderscorec739:
    goto Return; //  $C739  60

//------------------------------------------------------------------------

underscorelabelunderscorec73a:
    x = 0x03; //  $C73A  A2 03

underscorelabelunderscorec73c:
    a = M(underscorevarunderscore00c3underscoreindexed + x); //  $C73C  B5 C3
    writeData(underscorevarunderscore00c7underscoreindexed + x, a); //  $C73E  95 C7
    --x; //  $C740  CA
    if (!n)
        goto underscorelabelunderscorec73c; //  $C741  10 F9
    a = M(underscorevarunderscore001f); //  $C743  A5 1F
    M(a) <<= 1; //  $C745  0A
    M(a) <<= 1; //  $C746  0A
    y = a; //  $C747  A8
    writeData(underscorevarunderscore000f, y); //  $C748  84 0F
    x = 0x00; //  $C74A  A2 00

underscorelabelunderscorec74c:
    a = M(underscorevarunderscore05f0underscoreindexed + y); //  $C74C  B9 F0 05
    writeData(underscorevarunderscore00c3underscoreindexed + x, a); //  $C74F  95 C3
    ++y; //  $C751  C8
    ++x; //  $C752  E8
    compare(x, 0x04); //  $C753  E0 04
    if (!z)
        goto underscorelabelunderscorec74c; //  $C755  D0 F5
    a = 0xF0; //  $C757  A9 F0
    writeData(underscorevarunderscore0000underscoreindexed, a); //  $C759  85 00
    JSR(underscorefuncunderscorec511, 47); //  $C75B  20 11 C5
    y = M(underscorevarunderscore000f); //  $C75E  A4 0F
    x = 0x00; //  $C760  A2 00

underscorelabelunderscorec762:
    a = M(underscorevarunderscore00c3underscoreindexed + x); //  $C762  B5 C3
    writeData(underscorevarunderscore05f0underscoreindexed + y, a); //  $C764  99 F0 05
    ++y; //  $C767  C8
    ++x; //  $C768  E8
    compare(x, 0x04); //  $C769  E0 04
    if (!z)
        goto underscorelabelunderscorec762; //  $C76B  D0 F5
    y = 0x00; //  $C76D  A0 00
    writeData(underscorevarunderscore00b5, y); //  $C76F  84 B5
    writeData(underscorevarunderscore0026, y); //  $C771  84 26
    ++y; //  $C773  C8
    writeData(underscorevarunderscore0024, y); //  $C774  84 24
    goto underscorefuncunderscorec5e1; //  $C776  4C E1 C5

underscorelabelunderscorec779:
    JSR(underscorefuncunderscored50d, 48); //  $C779  20 0D D5
    JSR(underscorefuncunderscorec5d9, 49); //  $C77C  20 D9 C5
    JSR(underscorefuncunderscored4fa, 50); //  $C77F  20 FA D4
    a = 0x01; //  $C782  A9 01
    writeData(underscorevarunderscore03a0, a); //  $C784  8D A0 03
    writeData(underscorevarunderscore03a1, a); //  $C787  8D A1 03
    a = 0x07; //  $C78A  A9 07
    writeData(underscorevarunderscore0025, a); //  $C78C  85 25
    a = 0x15; //  $C78E  A9 15
    writeData(underscorevarunderscore002d, a); //  $C790  85 2D
    goto Return; //  $C792  60

//------------------------------------------------------------------------

underscorefuncunderscorec793:
    x = 0x0A; //  $C793  A2 0A

underscorelabelunderscorec795:
    compare(x, M(underscorevarunderscore00ab)); //  $C795  E4 AB
    if (!c)
        goto underscorelabelunderscorec79f; //  $C797  90 06
    if (z)
        goto underscorelabelunderscorec79f; //  $C799  F0 04
    a = 0xB7; //  $C79B  A9 B7
    if (!z)
        goto underscorelabelunderscorec7a1; //  $C79D  D0 02

underscorelabelunderscorec79f:
    a = 0xD7; //  $C79F  A9 D7

underscorelabelunderscorec7a1:
    writeData(underscorevarunderscore0500underscoreindexed + x, a); //  $C7A1  9D 00 05
    --x; //  $C7A4  CA
    if (!z)
        goto underscorelabelunderscorec795; //  $C7A5  D0 EE
    a = 0x1A; //  $C7A7  A9 1A
    writeData(underscorevarunderscore0500underscoreindexed, a); //  $C7A9  8D 00 05
    x = 0x6C; //  $C7AC  A2 6C
    y = 0x23; //  $C7AE  A0 23
    goto underscorefuncunderscorec71d; //  $C7B0  4C 1D C7

underscorefuncunderscorec7b3:
    a = M(underscorevarunderscore00c1); //  $C7B3  A5 C1
    writeData(underscorevarunderscore0003, a); //  $C7B5  85 03
    a = 0x01; //  $C7B7  A9 01
    c = 0; //  $C7B9  18
    JSR(underscorefuncunderscorec4bf, 51); //  $C7BA  20 BF C4
    writeData(underscorevarunderscore00c1, a); //  $C7BD  85 C1
    a = 0x12; //  $C7BF  A9 12
    writeData(underscorevarunderscore0500underscoreindexed, a); //  $C7C1  8D 00 05
    x = 0xDD; //  $C7C4  A2 DD
    a = M(underscorevarunderscore001f); //  $C7C6  A5 1F
    compare(a, 0x02); //  $C7C8  C9 02
    if (z)
        goto underscorelabelunderscorec7ce; //  $C7CA  F0 02
    x = 0x50; //  $C7CC  A2 50

underscorelabelunderscorec7ce:
    writeData(underscorevarunderscore0502, x); //  $C7CE  8E 02 05
    x = 0x00; //  $C7D1  A2 00
    a = M(underscorevarunderscore00c1); //  $C7D3  A5 C1
    a &= 0xF0; //  $C7D5  29 F0
    if (z)
        goto underscorelabelunderscorec7e1; //  $C7D7  F0 08
    M(a) >>= 1; //  $C7D9  4A
    M(a) >>= 1; //  $C7DA  4A
    M(a) >>= 1; //  $C7DB  4A
    M(a) >>= 1; //  $C7DC  4A
    writeData(underscorevarunderscore0501underscoreindexed + x, a); //  $C7DD  9D 01 05
    ++x; //  $C7E0  E8

underscorelabelunderscorec7e1:
    a = M(underscorevarunderscore00c1); //  $C7E1  A5 C1
    a &= 0x0F; //  $C7E3  29 0F
    writeData(underscorevarunderscore0501underscoreindexed + x, a); //  $C7E5  9D 01 05
    x = 0x05; //  $C7E8  A2 05
    y = 0x23; //  $C7EA  A0 23
    goto underscorefuncunderscorec71d; //  $C7EC  4C 1D C7

underscorelabelunderscorec7ef:
    a = M(underscorevarunderscore009d); //  $C7EF  A5 9D
    if (z)
        goto underscorelabelunderscorec7f6; //  $C7F1  F0 03
    goto underscorefuncunderscorec7fb; //  $C7F3  4C FB C7

underscorelabelunderscorec7f6:
    a = 0x0A; //  $C7F6  A9 0A
    writeData(underscorevarunderscore0025, a); //  $C7F8  85 25
    goto Return; //  $C7FA  60

//------------------------------------------------------------------------

underscorefuncunderscorec7fb:
    a = M(underscorevarunderscore002bunderscoreindexed); //  $C7FB  A5 2B
    if (!z)
        goto underscorelabelunderscorec81c; //  $C7FD  D0 1D
    y = M(underscorevarunderscore009d); //  $C7FF  A4 9D
    if (z)
        goto underscorelabelunderscorec81c; //  $C801  F0 19
    a = M(underscoredataunderscoreec1funderscoreindexed + y); //  $C803  B9 1F EC
    compare(a, 0xAA); //  $C806  C9 AA
    if (z)
        goto underscorelabelunderscorec818; //  $C808  F0 0E
    pha(); //  $C80A  48
    ++y; //  $C80B  C8
    a = M(underscoredataunderscoreec1funderscoreindexed + y); //  $C80C  B9 1F EC
    writeData(underscorevarunderscore002bunderscoreindexed, a); //  $C80F  85 2B
    ++y; //  $C811  C8
    writeData(underscorevarunderscore009d, y); //  $C812  84 9D
    pla(); //  $C814  68
    goto underscorelabelunderscored46c; //  $C815  4C 6C D4

underscorelabelunderscorec818:
    a = 0x00; //  $C818  A9 00
    writeData(underscorevarunderscore009d, a); //  $C81A  85 9D

underscorelabelunderscorec81c:
    goto Return; //  $C81C  60

//------------------------------------------------------------------------

underscorelabelunderscorec81d:
    JSR(underscorefuncunderscorec641, 52); //  $C81D  20 41 C6
    JSR(underscorefuncunderscorec5d9, 53); //  $C820  20 D9 C5
    JSR(underscorefuncunderscorec22b, 54); //  $C823  20 2B C2
    JSR(underscorefuncunderscored4d9, 55); //  $C826  20 D9 D4
    x = 0x01; //  $C829  A2 01
    a = M(underscorevarunderscore05fe); //  $C82B  AD FE 05
    writeData(underscorevarunderscore001f, a); //  $C82E  85 1F
    compare(a, 0x02); //  $C830  C9 02
    if (!c)
        goto underscorelabelunderscorec836; //  $C832  90 02
    x = 0x08; //  $C834  A2 08

underscorelabelunderscorec836:
    writeData(underscorevarunderscore0025, x); //  $C836  86 25
    goto Return; //  $C838  60

//------------------------------------------------------------------------

underscorelabelunderscorec839:
    JSR(underscorefuncunderscorec5d9, 56); //  $C839  20 D9 C5
    x = 0x42; //  $C83C  A2 42
    y = 0xE0; //  $C83E  A0 E0
    JSR(underscorefuncunderscorec617, 57); //  $C840  20 17 C6
    a = 0x02; //  $C843  A9 02
    writeData(underscorevarunderscore0023, a); //  $C845  85 23
    a = 0x02; //  $C847  A9 02
    writeData(underscorevarunderscore0025, a); //  $C849  85 25
    JSR(underscorefuncunderscorec3c1, 58); //  $C84B  20 C1 C3
    JSR(underscorefuncunderscorec5ee, 59); //  $C84E  20 EE C5
    goto underscorelabelunderscored515; //  $C851  4C 15 D5

underscorelabelunderscorec854:
    JSR(underscorefuncunderscored4d9, 60); //  $C854  20 D9 D4
    JSR(underscorefuncunderscored2a4, 61); //  $C857  20 A4 D2
    JSR(underscorefuncunderscorec793, 62); //  $C85A  20 93 C7
    JSR(underscorefuncunderscorec7b3, 63); //  $C85D  20 B3 C7
    ; // nop //  $C860  EA
    ; // nop //  $C861  EA
    ; // nop //  $C862  EA
    a = 0x00; //  $C863  A9 00
    writeData(underscorevarunderscore00b5, a); //  $C865  85 B5
    writeData(underscorevarunderscore009d, a); //  $C867  85 9D
    a = 0x03; //  $C869  A9 03
    writeData(underscorevarunderscore0025, a); //  $C86B  85 25
    goto Return; //  $C86D  60

//------------------------------------------------------------------------

underscorelabelunderscorec86e:
    JSR(underscorefuncunderscored131, 64); //  $C86E  20 31 D1
    JSR(underscorefuncunderscored160, 65); //  $C871  20 60 D1
    JSR(underscorefuncunderscorecc94, 66); //  $C874  20 94 CC
    JSR(underscorefuncunderscorec890, 67); //  $C877  20 90 C8
    JSR(underscorefuncunderscorec6f5, 68); //  $C87A  20 F5 C6
    JSR(underscorefuncunderscored3d2, 69); //  $C87D  20 D2 D3
    JSR(underscorefuncunderscorec6c4, 70); //  $C880  20 C4 C6
    JSR(underscorefuncunderscorecfba, 71); //  $C883  20 BA CF
    JSR(underscorefuncunderscored428, 72); //  $C886  20 28 D4
    JSR(underscorefuncunderscorec7fb, 73); //  $C889  20 FB C7
    ; // nop //  $C88C  EA
    ; // nop //  $C88D  EA
    ; // nop //  $C88E  EA
    goto Return; //  $C88F  60

//------------------------------------------------------------------------

underscorefuncunderscorec890:
    a = M(underscorevarunderscore0300underscoreindexed); //  $C890  AD 00 03
    if (z)
        goto underscorelabelunderscorec8a2; //  $C893  F0 0D
    y = 0x00; //  $C895  A0 00
    writeData(underscorevarunderscore00a1, y); //  $C897  84 A1
    JSR(underscorefuncunderscorec5f7, 74); //  $C899  20 F7 C5
    JSR(underscorefuncunderscorec902, 75); //  $C89C  20 02 C9
    JSR(underscorefuncunderscorec607, 76); //  $C89F  20 07 C6

underscorelabelunderscorec8a2:
    a = M(underscorevarunderscore0350); //  $C8A2  AD 50 03
    if (z)
        goto underscorelabelunderscorec8b4; //  $C8A5  F0 0D
    y = 0x50; //  $C8A7  A0 50
    ++M(underscorevarunderscore00a1); //  $C8A9  E6 A1
    JSR(underscorefuncunderscorec5f7, 77); //  $C8AB  20 F7 C5
    JSR(underscorefuncunderscorec902, 78); //  $C8AE  20 02 C9
    JSR(underscorefuncunderscorec607, 79); //  $C8B1  20 07 C6

underscorelabelunderscorec8b4:
    a = M(underscorevarunderscore00b9); //  $C8B4  A5 B9
    if (z)
        goto underscorelabelunderscorec901; //  $C8B6  F0 49
    y = M(underscorevarunderscore009f); //  $C8B8  A4 9F
    if (!z)
        goto underscorelabelunderscorec8c4; //  $C8BA  D0 08
    y = 0x41; //  $C8BC  A0 41
    a = M(underscorevarunderscore00ba); //  $C8BE  A5 BA
    if (!z)
        goto underscorelabelunderscorec8c4; //  $C8C0  D0 02
    y = 0x15; //  $C8C2  A0 15

underscorelabelunderscorec8c4:
    --y; //  $C8C4  88
    writeData(underscorevarunderscore009f, y); //  $C8C5  84 9F
    a = M(underscorevarunderscore00bc); //  $C8C7  A5 BC
    if (!z)
        goto underscorelabelunderscorec8fb; //  $C8C9  D0 30
    a = M(underscorevarunderscore0301underscoreindexed); //  $C8CB  AD 01 03
    if (!z)
        goto underscorelabelunderscorec901; //  $C8CE  D0 31
    a = M(underscorevarunderscore0351); //  $C8D0  AD 51 03
    if (!z)
        goto underscorelabelunderscorec901; //  $C8D3  D0 2C
    a = M(underscorevarunderscore002bunderscoreindexed); //  $C8D5  A5 2B
    if (!z)
        goto underscorelabelunderscorec901; //  $C8D7  D0 28
    a = 0x0A; //  $C8D9  A9 0A
    y = 0x07; //  $C8DB  A0 07
    x = M(underscorevarunderscore00bd); //  $C8DD  A6 BD
    if (z)
        goto underscorelabelunderscorec8e5; //  $C8DF  F0 04
    a = 0x0C; //  $C8E1  A9 0C
    y = 0x02; //  $C8E3  A0 02

underscorelabelunderscorec8e5:
    writeData(underscorevarunderscore03a1, a); //  $C8E5  8D A1 03
    writeData(underscorevarunderscore0023, y); //  $C8E8  84 23
    JSR(underscorefuncunderscorec5d9, 80); //  $C8EA  20 D9 C5
    JSR(underscorefuncunderscored446, 81); //  $C8ED  20 46 D4
    a = 0x40; //  $C8F0  A9 40
    writeData(underscorevarunderscore002bunderscoreindexed, a); //  $C8F2  85 2B
    a = 0x00; //  $C8F4  A9 00
    writeData(underscorevarunderscore00b9, a); //  $C8F6  85 B9
    goto underscorefuncunderscored464; //  $C8F8  4C 64 D4

underscorelabelunderscorec8fb:
    a = M(underscorevarunderscore00a6); //  $C8FB  A5 A6
    if (z)
        goto underscorelabelunderscorec901; //  $C8FD  F0 02
    --M(underscorevarunderscore00a6); //  $C8FF  C6 A6

underscorelabelunderscorec901:
    goto Return; //  $C901  60

//------------------------------------------------------------------------

underscorefuncunderscorec902:
    a = M(underscorevarunderscore0031); //  $C902  A5 31
    JSR(underscorejumpunderscoreengineunderscorec35e, 82); //  $C904  20 5E C3
    compare(x, 0xC5); //  $C907  E0 C5
    a |= M(underscorevarunderscore32c9underscoreindexed + y); //  $C909  19 C9 32
    compare(a, 0x19); //  $C90C  C9 19
    --x; //  $C90E  CA
    { uint8_t temp = M(underscorevarunderscore3dccunderscoreindexed + x); temp <<= 1; writeData(underscorevarunderscore3dccunderscoreindexed + x, temp); a |= temp; } //  $C90F  1F CC 3D
    compare(y, M(underscoredataunderscorecc4f)); //  $C912  CC 4F CC

underscorelabelunderscorec91b:
    a = M(underscoredataunderscoree5ebunderscoreindexed + x); //  $C91B  BD EB E5
    writeData(underscorevarunderscore0030underscoreindexed + x, a); //  $C91E  95 30
    --x; //  $C920  CA
    if (!n)
        goto underscorelabelunderscorec91b; //  $C921  10 F8
    a = M(underscorevarunderscore00a1); //  $C923  A5 A1
    if (z)
        goto underscorelabelunderscorec92f; //  $C925  F0 08
    a = 0x40; //  $C927  A9 40
    writeData(0x36, a); //  $C929  85 36
    a = 0x7F; //  $C92B  A9 7F
    writeData(0x37, a); //  $C92D  85 37

underscorelabelunderscorec92f:
    ++M(underscorevarunderscore0031); //  $C92F  E6 31
    goto Return; //  $C931  60

//------------------------------------------------------------------------

underscoredataunderscorecafa:

underscoredataunderscorecc4f:

underscorefuncunderscorecc94:
    a = M(underscorevarunderscore03a0); //  $CC94  AD A0 03
    if (z)
        goto underscorelabelunderscorecca8; //  $CC97  F0 0F
    a = 0x02; //  $CC99  A9 02
    writeData(underscorevarunderscore00a1, a); //  $CC9B  85 A1
    y = 0xA0; //  $CC9D  A0 A0
    JSR(underscorefuncunderscorec5f7, 83); //  $CC9F  20 F7 C5
    JSR(underscorefuncunderscorecca9, 84); //  $CCA2  20 A9 CC
    JSR(underscorefuncunderscorec607, 85); //  $CCA5  20 07 C6

underscorelabelunderscorecca8:
    goto Return; //  $CCA8  60

//------------------------------------------------------------------------

underscorefuncunderscorecca9:
    a = M(underscorevarunderscore0031); //  $CCA9  A5 31
    JSR(underscorejumpunderscoreengineunderscorec35e, 86); //  $CCAB  20 5E C3
    compare(x, 0xC5); //  $CCAE  E0 C5

underscoredataunderscorece4d:

underscorefuncunderscorecfba:
    x = 0x00; //  $CFBA  A2 00
    y = 0x00; //  $CFBC  A0 00
    JSR(underscorefuncunderscorecfc5, 87); //  $CFBE  20 C5 CF
    x = 0x04; //  $CFC1  A2 04
    y = 0x08; //  $CFC3  A0 08

underscorefuncunderscorecfc5:
    a = M(underscorevarunderscore0080underscoreindexed + x); //  $CFC5  B5 80
    if (z)
        goto underscorelabelunderscorecff8; //  $CFC7  F0 2F
    --M(underscorevarunderscore0080underscoreindexed + x); //  $CFC9  D6 80
    if (!z)
        goto underscorelabelunderscorecfd3; //  $CFCB  D0 06
    a = 0xF4; //  $CFCD  A9 F4
    writeData(underscorevarunderscore0081underscoreindexed + x, a); //  $CFCF  95 81
    writeData(underscorevarunderscore0082underscoreindexed + x, a); //  $CFD1  95 82

underscorelabelunderscorecfd3:
    a = M(underscorevarunderscore0081underscoreindexed + x); //  $CFD3  B5 81
    writeData(underscorevarunderscore02f0underscoreindexed + y, a); //  $CFD5  99 F0 02
    writeData(underscorevarunderscore02f4underscoreindexed + y, a); //  $CFD8  99 F4 02
    a = M(underscorevarunderscore0083underscoreindexed + x); //  $CFDB  B5 83
    writeData(underscorevarunderscore02f1underscoreindexed + y, a); //  $CFDD  99 F1 02
    a = 0xFF; //  $CFE0  A9 FF
    writeData(underscorevarunderscore02f5underscoreindexed + y, a); //  $CFE2  99 F5 02
    a = 0x00; //  $CFE5  A9 00
    writeData(underscorevarunderscore02f2underscoreindexed + y, a); //  $CFE7  99 F2 02
    writeData(underscorevarunderscore02f6underscoreindexed + y, a); //  $CFEA  99 F6 02
    a = M(underscorevarunderscore0082underscoreindexed + x); //  $CFED  B5 82
    writeData(underscorevarunderscore02f3underscoreindexed + y, a); //  $CFEF  99 F3 02
    c = 0; //  $CFF2  18
    a += 0x08; //  $CFF3  69 08
    writeData(underscorevarunderscore02f7underscoreindexed + y, a); //  $CFF5  99 F7 02

underscorelabelunderscorecff8:
    goto Return; //  $CFF8  60

//------------------------------------------------------------------------

underscorefuncunderscored131:
    a = M(JOyPAD2); //  $D131  AD 17 40
    a &= 0x10; //  $D134  29 10
    compare(a, M(underscorevarunderscore00b7)); //  $D136  C5 B7
    if (z)
        goto underscorelabelunderscored141; //  $D138  F0 07
    writeData(underscorevarunderscore00b7, a); //  $D13A  85 B7

underscorelabelunderscored13c:
    a = 0x00; //  $D13C  A9 00
    writeData(underscorevarunderscore00b8, a); //  $D13E  85 B8

underscorelabelunderscored140:
    goto Return; //  $D140  60

//------------------------------------------------------------------------

underscorelabelunderscored141:
    ++M(underscorevarunderscore00b8); //  $D141  E6 B8
    y = M(underscorevarunderscore00b8); //  $D143  A4 B8
    compare(y, 0x01); //  $D145  C0 01
    if (!z)
        goto underscorelabelunderscored140; //  $D147  D0 F7
    a &= 0x10; //  $D149  29 10
    if (z)
        goto underscorelabelunderscored153; //  $D14B  F0 06
    a = 0x01; //  $D14D  A9 01
    writeData(underscorevarunderscore00b6, a); //  $D14F  85 B6
    if (!z)
        goto underscorelabelunderscored13c; //  $D151  D0 E9

underscorelabelunderscored153:
    a = M(underscorevarunderscore00b6); //  $D153  A5 B6
    if (z)
        goto underscorelabelunderscored13c; //  $D155  F0 E5
    y = 0x00; //  $D157  A0 00
    writeData(underscorevarunderscore00b6, y); //  $D159  84 B6
    ++y; //  $D15B  C8
    writeData(underscorevarunderscore00b5, y); //  $D15C  84 B5
    if (!z)
        goto underscorelabelunderscored13c; //  $D15E  D0 DC

underscorefuncunderscored160:
    a = M(underscorevarunderscore00b9); //  $D160  A5 B9
    if (!z)
        goto underscorelabelunderscored169; //  $D162  D0 05

underscorelabelunderscored164:
    a = 0x00; //  $D164  A9 00
    writeData(underscorevarunderscore00b5, a); //  $D166  85 B5

underscorelabelunderscored168:
    goto Return; //  $D168  60

//------------------------------------------------------------------------

underscorelabelunderscored169:
    a = M(underscorevarunderscore00b5); //  $D169  A5 B5
    if (z)
        goto underscorelabelunderscored168; //  $D16B  F0 FB
    a = M(underscorevarunderscore00ba); //  $D16D  A5 BA
    if (z)
        goto underscorelabelunderscored164; //  $D16F  F0 F3
    --M(underscorevarunderscore00ba); //  $D171  C6 BA
    a = 0x01; //  $D173  A9 01
    writeData(underscorevarunderscore00be, a); //  $D175  85 BE
    a = 0x00; //  $D177  A9 00
    writeData(underscorevarunderscore00b5, a); //  $D179  85 B5
    JSR(underscorefuncunderscored4e6, 88); //  $D17B  20 E6 D4
    a = 0x04; //  $D17E  A9 04
    writeData(underscorevarunderscore0023, a); //  $D180  85 23
    JSR(underscorefuncunderscorec23b, 89); //  $D182  20 3B C2
    JSR(underscorefuncunderscorec5e1, 90); //  $D185  20 E1 C5
    a = M(underscorevarunderscore0024); //  $D188  A5 24
    if (z)
        goto underscorelabelunderscored19f; //  $D18A  F0 13
    JSR(underscorefuncunderscored4e2, 91); //  $D18C  20 E2 D4
    JSR(underscorefuncunderscoref56c, 92); //  $D18F  20 6C F5
    JSR(underscorefuncunderscored4e6, 93); //  $D192  20 E6 D4
    a = 0x02; //  $D195  A9 02
    writeData(underscorevarunderscore00b0, a); //  $D197  85 B0
    a = 0xFF; //  $D199  A9 FF
    writeData(underscorevarunderscore000a, a); //  $D19B  85 0A
    if (!z)
        goto underscorelabelunderscored1ca; //  $D19D  D0 2B

underscorelabelunderscored19f:
    a = 0x05; //  $D19F  A9 05
    writeData(underscorevarunderscore0023, a); //  $D1A1  85 23
    a = 0x00; //  $D1A3  A9 00
    writeData(underscorevarunderscore00b0, a); //  $D1A5  85 B0
    y = 0x00; //  $D1A7  A0 00
    a = M(underscorevarunderscore0300underscoreindexed); //  $D1A9  AD 00 03
    if (z)
        goto underscorelabelunderscored1b5; //  $D1AC  F0 07
    a = M(underscorevarunderscore0301underscoreindexed); //  $D1AE  AD 01 03
    compare(a, 0x03); //  $D1B1  C9 03
    if (z)
        goto underscorelabelunderscored1c7; //  $D1B3  F0 12

underscorelabelunderscored1b5:
    a = 0x01; //  $D1B5  A9 01
    writeData(underscorevarunderscore00b0, a); //  $D1B7  85 B0
    y = 0x50; //  $D1B9  A0 50
    a = M(underscorevarunderscore0350); //  $D1BB  AD 50 03
    if (z)
        goto underscorelabelunderscored1dd; //  $D1BE  F0 1D
    a = M(underscorevarunderscore0351); //  $D1C0  AD 51 03
    compare(a, 0x03); //  $D1C3  C9 03
    if (!z)
        goto underscorelabelunderscored1dd; //  $D1C5  D0 16

underscorelabelunderscored1c7:
    JSR(underscorefuncunderscored292, 94); //  $D1C7  20 92 D2

underscorelabelunderscored1ca:
    JSR(underscorefuncunderscorec61e, 95); //  $D1CA  20 1E C6

underscorelabelunderscored1cd:
    a = M(underscorevarunderscore0020); //  $D1CD  A5 20
    if (!z)
        goto underscorelabelunderscored1f4; //  $D1CF  D0 23
    a = M(JOyPAD2); //  $D1D1  AD 17 40
    a &= 0x08; //  $D1D4  29 08
    if (!z)
        goto underscorelabelunderscored1cd; //  $D1D6  D0 F5
    a = M(underscorevarunderscore00b0); //  $D1D8  A5 B0
    goto underscorelabelunderscored28a; //  $D1DA  4C 8A D2

underscorelabelunderscored1dd:
    a = M(underscorevarunderscore001f); //  $D1DD  A5 1F
    compare(a, 0x02); //  $D1DF  C9 02
    if (!z)
        goto underscorelabelunderscored1e6; //  $D1E1  D0 03
    goto underscorelabelunderscored266; //  $D1E3  4C 66 D2

underscorelabelunderscored1e6:
    y = 0x02; //  $D1E6  A0 02
    writeData(underscorevarunderscore0023, y); //  $D1E8  84 23
    JSR(underscorefuncunderscorec5d9, 96); //  $D1EA  20 D9 C5
    y = 0x01; //  $D1ED  A0 01
    writeData(underscorevarunderscore0027, y); //  $D1EF  84 27
    goto underscorelabelunderscored26a; //  $D1F1  4C 6A D2

underscorelabelunderscored1f4:
    JSR(underscorefuncunderscorec61e, 97); //  $D1F4  20 1E C6
    a = M(underscorevarunderscore0009); //  $D1F7  A5 09
    a &= 0xE7; //  $D1F9  29 E7
    writeData(underscorevarunderscore0009, a); //  $D1FB  85 09
    a = 0x08; //  $D1FD  A9 08
    y = M(underscorevarunderscore00b0); //  $D1FF  A4 B0
    compare(y, 0x02); //  $D201  C0 02
    if (z)
        goto underscorelabelunderscored207; //  $D203  F0 02
    a = 0x10; //  $D205  A9 10

underscorelabelunderscored207:
    a |= M(underscorevarunderscore0009); //  $D207  05 09
    writeData(underscorevarunderscore0009, a); //  $D209  85 09
    writeData(PPUunderscoreMASK, a); //  $D20B  8D 01 20
    JSR(underscorefuncunderscorec23b, 98); //  $D20E  20 3B C2
    a = M(underscorevarunderscore0350); //  $D211  AD 50 03
    if (z)
        goto underscorelabelunderscored222; //  $D214  F0 0C
    a = M(underscorevarunderscore0351); //  $D216  AD 51 03
    compare(a, 0x03); //  $D219  C9 03
    if (!z)
        goto underscorelabelunderscored222; //  $D21B  D0 05
    y = 0x50; //  $D21D  A0 50
    JSR(underscorefuncunderscored292, 99); //  $D21F  20 92 D2

underscorelabelunderscored222:
    a = M(underscorevarunderscore0020); //  $D222  A5 20
    if (!z)
        goto underscorelabelunderscored270; //  $D224  D0 4A
    a = M(JOyPAD2); //  $D226  AD 17 40
    a &= 0x08; //  $D229  29 08
    if (!z)
        goto underscorelabelunderscored222; //  $D22B  D0 F5
    a = M(underscorevarunderscore00b0); //  $D22D  A5 B0
    compare(a, 0x02); //  $D22F  C9 02
    if (!z)
        goto underscorelabelunderscored246; //  $D231  D0 13
    a = 0x01; //  $D233  A9 01

underscorelabelunderscored235:
    writeData(underscorevarunderscore05ff, a); //  $D235  8D FF 05
    a = 0x01; //  $D238  A9 01
    writeData(underscorevarunderscore0023, a); //  $D23A  85 23
    a = 0x00; //  $D23C  A9 00
    writeData(underscorevarunderscore000a, a); //  $D23E  85 0A
    JSR(underscorefuncunderscorec5d9, 100); //  $D240  20 D9 C5
    goto underscorefuncunderscorec5ee; //  $D243  4C EE C5

underscorelabelunderscored246:
    ++M(underscorevarunderscore00aa); //  $D246  E6 AA
    ++M(underscorevarunderscore00bd); //  $D248  E6 BD
    x = 0x04; //  $D24A  A2 04
    a = M(underscorevarunderscore00b0); //  $D24C  A5 B0
    if (!z)
        goto underscorelabelunderscored256; //  $D24E  D0 06
    writeData(underscorevarunderscore0301underscoreindexed, x); //  $D250  8E 01 03
    goto underscorelabelunderscored259; //  $D253  4C 59 D2

underscorelabelunderscored256:
    writeData(underscorevarunderscore0351, x); //  $D256  8E 51 03

underscorelabelunderscored259:
    a = M(underscorevarunderscore001f); //  $D259  A5 1F
    compare(a, 0x02); //  $D25B  C9 02

underscorelabelunderscored25e:

underscorelabelunderscored266:
    y = 0x03; //  $D266  A0 03

underscorelabelunderscored268:
    writeData(underscorevarunderscore0023, y); //  $D268  84 23

underscorelabelunderscored26a:
    JSR(underscorefuncunderscorec23b, 101); //  $D26A  20 3B C2
    goto underscorefuncunderscorec5ee; //  $D26D  4C EE C5

underscorelabelunderscored270:
    a = M(underscorevarunderscore00b0); //  $D270  A5 B0
    if (!z)
        goto underscorelabelunderscored28a; //  $D272  D0 16
    a = M(underscorevarunderscore0350); //  $D274  AD 50 03
    if (z)
        goto underscorelabelunderscored259; //  $D277  F0 E0
    a = M(underscorevarunderscore0351); //  $D279  AD 51 03
    compare(a, 0x03); //  $D27C  C9 03
    if (!z)
        goto underscorelabelunderscored259; //  $D27E  D0 D9
    a = 0x01; //  $D280  A9 01
    writeData(underscorevarunderscore00b0, a); //  $D282  85 B0
    JSR(underscorefuncunderscorec61e, 102); //  $D284  20 1E C6
    goto underscorelabelunderscored222; //  $D287  4C 22 D2

underscorelabelunderscored28a:
    compare(a, 0x02); //  $D28A  C9 02
    if (!z)
        goto underscorelabelunderscored259; //  $D28C  D0 CB
    a = 0x02; //  $D28E  A9 02
    if (!z)
        goto underscorelabelunderscored235; //  $D290  D0 A3

underscorefuncunderscored292:
    a = M(underscorevarunderscore0302underscoreindexed + y); //  $D292  B9 02 03
    writeData(underscorevarunderscore00b1, a); //  $D295  85 B1
    a = M(underscorevarunderscore0303underscoreindexed + y); //  $D297  B9 03 03
    writeData(underscorevarunderscore00b2, a); //  $D29A  85 B2
    a = M(underscorevarunderscore030aunderscoreindexed + y); //  $D29C  B9 0A 03
    writeData(underscorevarunderscore000c, a); //  $D29F  85 0C
    goto underscorelabelunderscorec67c; //  $D2A1  4C 7C C6

underscorefuncunderscored2a4:
    y = M(underscorevarunderscore00c2); //  $D2A4  A4 C2

underscorelabelunderscored2a6:
    a = M(underscoredataunderscoreec02underscoreindexed + y); //  $D2A6  B9 02 EC
    compare(a, 0xFF); //  $D2A9  C9 FF
    if (!z)
        goto underscorelabelunderscored2b1; //  $D2AB  D0 04
    y = 0x13; //  $D2AD  A0 13
    if (!z)
        goto underscorelabelunderscored2a6; //  $D2AF  D0 F5

underscorelabelunderscored2b1:
    ++y; //  $D2B1  C8
    writeData(underscorevarunderscore00c2, y); //  $D2B2  84 C2
    writeData(underscorevarunderscore00ab, a); //  $D2B4  85 AB
    a = 0x00; //  $D2B6  A9 00
    writeData(underscorevarunderscore00bb, a); //  $D2B8  85 BB
    writeData(underscorevarunderscore00aa, a); //  $D2BA  85 AA
    a = 0x01; //  $D2BC  A9 01
    writeData(underscorevarunderscore03a0, a); //  $D2BE  8D A0 03
    writeData(underscorevarunderscore03a1, a); //  $D2C1  8D A1 03
    a = 0xFF; //  $D2C4  A9 FF
    writeData(0x9C, a); //  $D2C6  85 9C
    goto Return; //  $D2C8  60

//------------------------------------------------------------------------

underscorelabelunderscored2c9:
    a = M(underscorevarunderscore00a9underscoreindexed); //  $D2C9  A5 A9
    JSR(underscorejumpunderscoreengineunderscorec35e, 103); //  $D2CB  20 5E C3
    --M(underscorevarunderscore00d2underscoreindexed + x); //  $D2CE  D6 D2
    compare(a, M(underscorevarunderscore3dd2underscoreindexed + x)); //  $D2D0  DD D2 3D
    { uint8_t temp = M(W(underscorevarunderscore00c9underscoreindexed) + y) - 1; writeData(W(underscorevarunderscore00c9underscoreindexed) + y, temp); compare(a, temp); } //  $D2D3  D3 C9
    { uint8_t temp = M(W(underscorevarunderscore00a9underscoreindexed) + y) - 1; writeData(W(underscorevarunderscore00a9underscoreindexed) + y, temp); compare(a, temp); } //  $D2D5  D3 A9
    if (!n)
        goto underscorelabelunderscored25e; //  $D2D7  10 85

underscorefuncunderscored3d2:
    a = M(underscorevarunderscore0027); //  $D3D2  A5 27
    if (!z)
        goto underscorelabelunderscored427; //  $D3D4  D0 51
    ++M(underscorevarunderscore009b); //  $D3D6  E6 9B
    y = 0x00; //  $D3D8  A0 00
    JSR(underscorefuncunderscored3df, 104); //  $D3DA  20 DF D3
    y = 0x50; //  $D3DD  A0 50

underscorefuncunderscored3df:
    a = M(underscorevarunderscore0300underscoreindexed + y); //  $D3DF  B9 00 03
    if (z)
        goto underscorelabelunderscored427; //  $D3E2  F0 43
    a = M(underscorevarunderscore0301underscoreindexed + y); //  $D3E4  B9 01 03
    compare(a, 0x03); //  $D3E7  C9 03
    if (z)
        goto underscorelabelunderscored3fb; //  $D3E9  F0 10
    compare(a, 0x08); //  $D3EB  C9 08
    if (!z)
        goto underscorelabelunderscored427; //  $D3ED  D0 38
    x = M(underscorevarunderscore030bunderscoreindexed + y); //  $D3EF  BE 0B 03
    a = M(underscorevarunderscore03efunderscoreindexed + x); //  $D3F2  BD EF 03
    if (z)
        goto underscorelabelunderscored409; //  $D3F5  F0 12
    x = 0xD3; //  $D3F7  A2 D3
    if (!z)
        goto underscorelabelunderscored40b; //  $D3F9  D0 10

underscorelabelunderscored3fb:
    a = M(underscorevarunderscore009b); //  $D3FB  A5 9B
    a &= 0x0F; //  $D3FD  29 0F
    if (!z)
        goto underscorelabelunderscored427; //  $D3FF  D0 26
    x = 0xB7; //  $D401  A2 B7
    a = M(underscorevarunderscore009b); //  $D403  A5 9B
    a &= 0x10; //  $D405  29 10
    if (z)
        goto underscorelabelunderscored413; //  $D407  F0 0A

underscorelabelunderscored409:
    x = 0xD4; //  $D409  A2 D4

underscorelabelunderscored40b:
    a = M(underscorevarunderscore001f); //  $D40B  A5 1F
    compare(a, 0x02); //  $D40D  C9 02
    if (z)
        goto underscorelabelunderscored413; //  $D40F  F0 02
    ++x; //  $D411  E8
    ++x; //  $D412  E8

underscorelabelunderscored413:
    writeData(underscorevarunderscore0501underscoreindexed, x); //  $D413  8E 01 05
    x = 0x11; //  $D416  A2 11
    writeData(underscorevarunderscore0500underscoreindexed, x); //  $D418  8E 00 05
    a = M(underscorevarunderscore030bunderscoreindexed + y); //  $D41B  B9 0B 03
    c = 0; //  $D41E  18
    a += 0x4B; //  $D41F  69 4B
    x = a; //  $D421  AA
    y = 0x23; //  $D422  A0 23
    goto underscorefuncunderscorec71d; //  $D424  4C 1D C7

underscorelabelunderscored427:
    goto Return; //  $D427  60

//------------------------------------------------------------------------

underscorefuncunderscored428:
    a = M(underscorevarunderscore00b9); //  $D428  A5 B9
    if (z)
        goto underscorelabelunderscored427; //  $D42A  F0 FB
    a = M(underscorevarunderscore00ba); //  $D42C  A5 BA
    if (!z)
        goto underscorelabelunderscored427; //  $D42E  D0 F7
    a = M(underscorevarunderscore009a); //  $D430  A5 9A
    a &= 0x07; //  $D432  29 07
    if (!z)
        goto underscorelabelunderscored461; //  $D434  D0 2B
    a = M(underscorevarunderscore0027); //  $D436  A5 27
    if (!z)
        goto underscorelabelunderscored427; //  $D438  D0 ED
    a = M(underscorevarunderscore009a); //  $D43A  A5 9A
    a &= 0x08; //  $D43C  29 08
    if (z)
        goto underscorefuncunderscored446; //  $D43E  F0 06
    a = 0xB7; //  $D440  A9 B7
    x = a; //  $D442  AA
    y = a; //  $D443  A8
    if (!z)
        goto underscorelabelunderscored44c; //  $D444  D0 06

underscorefuncunderscored446:
    a = 0xDA; //  $D446  A9 DA
    x = 0xDB; //  $D448  A2 DB
    y = 0xDC; //  $D44A  A0 DC

underscorelabelunderscored44c:
    writeData(underscorevarunderscore0501underscoreindexed, a); //  $D44C  8D 01 05
    writeData(underscorevarunderscore0502, x); //  $D44F  8E 02 05
    writeData(0x0503, y); //  $D452  8C 03 05
    a = 0x13; //  $D455  A9 13
    writeData(underscorevarunderscore0500underscoreindexed, a); //  $D457  8D 00 05
    x = 0x63; //  $D45A  A2 63
    y = 0x23; //  $D45C  A0 23
    JSR(underscorefuncunderscorec71d, 105); //  $D45E  20 1D C7

underscorelabelunderscored461:
    ++M(underscorevarunderscore009a); //  $D461  E6 9A
    goto Return; //  $D463  60

//------------------------------------------------------------------------

underscorefuncunderscored464:
    pha(); //  $D464  48
    JSR(underscorefuncunderscorec5d9, 106); //  $D465  20 D9 C5
    JSR(underscorefuncunderscoref56c, 107); //  $D468  20 6C F5
    pla(); //  $D46B  68

underscorelabelunderscored46c:
    writeData(underscorevarunderscore001b, a); //  $D46C  85 1B
    if (z)
        goto underscorelabelunderscored4bc; //  $D46E  F0 4C
    M(a) <<= 1; //  $D470  0A
    x = a; //  $D471  AA
    a = M(underscoredataunderscoreec38underscoreindexed + x); //  $D472  BD 38 EC
    writeData(underscorevarunderscore0014underscoreindexed, a); //  $D475  85 14
    a = M(underscoredataunderscoreec39underscoreindexed + x); //  $D477  BD 39 EC
    writeData(underscorevarunderscore0015, a); //  $D47A  85 15
    y = 0x01; //  $D47C  A0 01
    a = M(W(underscorevarunderscore0014underscoreindexed) + y); //  $D47E  B1 14
    writeData(underscorevarunderscore000f, a); //  $D480  85 0F
    x = 0x00; //  $D482  A2 00
    ++y; //  $D484  C8

underscorelabelunderscored485:
    a = M(W(underscorevarunderscore0014underscoreindexed) + y); //  $D485  B1 14
    writeData(underscorevarunderscore0500underscoreindexed + x, a); //  $D487  9D 00 05
    ++y; //  $D48A  C8
    ++x; //  $D48B  E8
    --M(underscorevarunderscore000f); //  $D48C  C6 0F
    if (!z)
        goto underscorelabelunderscored485; //  $D48E  D0 F5
    a = M(underscorevarunderscore001b); //  $D490  A5 1B
    compare(a, 0x01); //  $D492  C9 01
    if (!z)
        goto underscorelabelunderscored4ab; //  $D494  D0 15
    a = M(underscorevarunderscore00c1); //  $D496  A5 C1
    M(a) >>= 1; //  $D498  4A
    M(a) >>= 1; //  $D499  4A
    M(a) >>= 1; //  $D49A  4A
    M(a) >>= 1; //  $D49B  4A
    if (z)
        goto underscorelabelunderscored4a1; //  $D49C  F0 03
    writeData(0x0518, a); //  $D49E  8D 18 05

underscorelabelunderscored4a1:
    a = M(underscorevarunderscore00c1); //  $D4A1  A5 C1
    a &= 0x0F; //  $D4A3  29 0F
    writeData(0x0519, a); //  $D4A5  8D 19 05
    goto underscorelabelunderscored4cf; //  $D4A8  4C CF D4

underscorelabelunderscored4ab:
    compare(a, 0x05); //  $D4AB  C9 05
    if (!z)
        goto underscorelabelunderscored4cf; //  $D4AD  D0 20
    a = M(underscorevarunderscore000c); //  $D4AF  A5 0C
    writeData(0x0521, a); //  $D4B1  8D 21 05
    a = M(underscorevarunderscore000d); //  $D4B4  A5 0D
    writeData(0x0522, a); //  $D4B6  8D 22 05
    goto underscorelabelunderscored4cf; //  $D4B9  4C CF D4

underscorelabelunderscored4bc:
    x = 0x44; //  $D4BC  A2 44
    a = 0x24; //  $D4BE  A9 24

underscorelabelunderscored4c0:
    writeData(underscorevarunderscore0501underscoreindexed + x, a); //  $D4C0  9D 01 05
    --x; //  $D4C3  CA
    if (!n)
        goto underscorelabelunderscored4c0; //  $D4C4  10 FA
    a = 0x6B; //  $D4C6  A9 6B
    writeData(underscorevarunderscore0500underscoreindexed, a); //  $D4C8  8D 00 05
    x = 0xCB; //  $D4CB  A2 CB
    if (!z)
        goto underscorelabelunderscored4d4; //  $D4CD  D0 05

underscorelabelunderscored4cf:
    y = 0x00; //  $D4CF  A0 00
    a = M(W(underscorevarunderscore0014underscoreindexed) + y); //  $D4D1  B1 14
    x = a; //  $D4D3  AA

underscorelabelunderscored4d4:
    y = 0x20; //  $D4D4  A0 20
    goto underscorefuncunderscorec71d; //  $D4D6  4C 1D C7

underscorefuncunderscored4d9:
    JSR(underscorefuncunderscorec23b, 108); //  $D4D9  20 3B C2
    JSR(underscorefuncunderscorec64b, 109); //  $D4DC  20 4B C6
    goto underscorelabelunderscorec637; //  $D4DF  4C 37 C6

underscorefuncunderscored4e2:
    a = 0x01; //  $D4E2  A9 01
    if (!z)
        goto underscorelabelunderscored500; //  $D4E4  D0 1A

underscorefuncunderscored4e6:
    a = 0x02; //  $D4E6  A9 02
    if (!z)
        goto underscorelabelunderscored500; //  $D4E8  D0 16
    a = 0x04; //  $D4EA  A9 04
    if (!z)
        goto underscorelabelunderscored500; //  $D4EC  D0 12
    a = 0x08; //  $D4EE  A9 08
    if (!z)
        goto underscorelabelunderscored500; //  $D4F0  D0 0E
    a = 0x10; //  $D4F2  A9 10
    if (!z)
        goto underscorelabelunderscored500; //  $D4F4  D0 0A
    a = 0x20; //  $D4F6  A9 20
    if (!z)
        goto underscorelabelunderscored500; //  $D4F8  D0 06

underscorefuncunderscored4fa:
    a = 0x40; //  $D4FA  A9 40
    if (!z)
        goto underscorelabelunderscored500; //  $D4FC  D0 02

underscorefuncunderscored4fe:
    a = 0x80; //  $D4FE  A9 80

underscorelabelunderscored500:
    a |= M(underscorevarunderscore00f0); //  $D500  05 F0
    writeData(underscorevarunderscore00f0, a); //  $D502  85 F0
    goto Return; //  $D504  60

//------------------------------------------------------------------------

underscorelabelunderscored505:
    a = 0x01; //  $D505  A9 01
    if (!z)
        goto underscorelabelunderscored523; //  $D507  D0 1A

underscorefuncunderscored509:
    a = 0x02; //  $D509  A9 02
    if (!z)
        goto underscorelabelunderscored523; //  $D50B  D0 16

underscorefuncunderscored50d:
    a = 0x04; //  $D50D  A9 04
    if (!z)
        goto underscorelabelunderscored523; //  $D50F  D0 12
    a = 0x08; //  $D511  A9 08
    if (!z)
        goto underscorelabelunderscored523; //  $D513  D0 0E

underscorelabelunderscored515:
    a = 0x10; //  $D515  A9 10
    if (!z)
        goto underscorelabelunderscored523; //  $D517  D0 0A
    a = 0x20; //  $D519  A9 20
    if (!z)
        goto underscorelabelunderscored523; //  $D51B  D0 06
    a = 0x40; //  $D51D  A9 40
    if (!z)
        goto underscorelabelunderscored523; //  $D51F  D0 02

underscorelabelunderscored521:
    a = 0x80; //  $D521  A9 80

underscorelabelunderscored523:
    a |= M(underscorevarunderscore00f1); //  $D523  05 F1
    writeData(underscorevarunderscore00f1, a); //  $D525  85 F1
    goto Return; //  $D527  60

//------------------------------------------------------------------------

underscorelabelunderscored54b:
    JSR(underscorefuncunderscorec5d9, 110); //  $D54B  20 D9 C5
    x = 0x6C; //  $D54E  A2 6C
    y = 0xE2; //  $D550  A0 E2
    JSR(underscorefuncunderscorec617, 111); //  $D552  20 17 C6
    a = 0x03; //  $D555  A9 03
    writeData(underscorevarunderscore0023, a); //  $D557  85 23
    a = 0x00; //  $D559  A9 00
    writeData(underscorevarunderscore009d, a); //  $D55B  85 9D
    a = 0x09; //  $D55D  A9 09
    writeData(underscorevarunderscore0025, a); //  $D55F  85 25
    JSR(underscorefuncunderscorec3c1, 112); //  $D561  20 C1 C3
    JSR(underscorefuncunderscorec5ee, 113); //  $D564  20 EE C5
    goto underscorelabelunderscored505; //  $D567  4C 05 D5

underscorelabelunderscored56a:
    JSR(underscorefuncunderscored4d9, 114); //  $D56A  20 D9 D4
    JSR(underscorefuncunderscored2a4, 115); //  $D56D  20 A4 D2
    JSR(underscorefuncunderscorec793, 116); //  $D570  20 93 C7
    JSR(underscorefuncunderscorec7b3, 117); //  $D573  20 B3 C7
    JSR(underscorefuncunderscorec5d9, 118); //  $D576  20 D9 C5
    JSR(underscorefuncunderscoref56c, 119); //  $D579  20 6C F5
    a = 0x01; //  $D57C  A9 01
    writeData(underscorevarunderscore00be, a); //  $D57E  85 BE
    a = 0x03; //  $D580  A9 03
    writeData(underscorevarunderscore00ba, a); //  $D582  85 BA
    JSR(underscorefuncunderscorec6f5, 120); //  $D584  20 F5 C6
    JSR(underscorefuncunderscorec6cc, 121); //  $D587  20 CC C6
    a = 0x06; //  $D58A  A9 06
    writeData(underscorevarunderscore009d, a); //  $D58C  85 9D
    a = 0x0D; //  $D58E  A9 0D
    writeData(underscorevarunderscore0025, a); //  $D590  85 25
    goto Return; //  $D592  60

//------------------------------------------------------------------------

underscorelabelunderscored593:
    a = 0x01; //  $D593  A9 01
    writeData(underscorevarunderscore0300underscoreindexed, a); //  $D595  8D 00 03
    writeData(underscorevarunderscore0350, a); //  $D598  8D 50 03
    writeData(underscorevarunderscore0301underscoreindexed, a); //  $D59B  8D 01 03
    writeData(underscorevarunderscore0351, a); //  $D59E  8D 51 03
    a = 0x30; //  $D5A1  A9 30
    x = M(underscorevarunderscore00c1); //  $D5A3  A6 C1
    compare(x, 0x10); //  $D5A5  E0 10
    if (c)
        goto underscorelabelunderscored5ad; //  $D5A7  B0 04
    --x; //  $D5A9  CA
    a = M(underscoredataunderscoreec17underscoreindexed + x); //  $D5AA  BD 17 EC

underscorelabelunderscored5ad:
    writeData(0xA8, a); //  $D5AD  85 A8
    a = 0x80; //  $D5AF  A9 80
    writeData(underscorevarunderscore00a6, a); //  $D5B1  85 A6
    a = 0x01; //  $D5B3  A9 01
    writeData(underscorevarunderscore00be, a); //  $D5B5  85 BE
    a = 0x03; //  $D5B7  A9 03
    writeData(underscorevarunderscore00ba, a); //  $D5B9  85 BA
    a = 0x02; //  $D5BB  A9 02
    writeData(underscorevarunderscore00bc, a); //  $D5BD  85 BC
    a = 0x00; //  $D5BF  A9 00
    writeData(underscorevarunderscore00b5, a); //  $D5C1  85 B5
    writeData(underscorevarunderscore00b9, a); //  $D5C3  85 B9
    writeData(underscorevarunderscore00bd, a); //  $D5C5  85 BD
    JSR(underscorefuncunderscorec6f5, 122); //  $D5C7  20 F5 C6
    JSR(underscorefuncunderscorec6cc, 123); //  $D5CA  20 CC C6
    a = 0x0B; //  $D5CD  A9 0B
    writeData(underscorevarunderscore0025, a); //  $D5CF  85 25
    goto Return; //  $D5D1  60

//------------------------------------------------------------------------

underscorelabelunderscored5d2:
    JSR(underscorefuncunderscored131, 124); //  $D5D2  20 31 D1
    JSR(underscorefuncunderscored160, 125); //  $D5D5  20 60 D1
    JSR(underscorefuncunderscored5ee, 126); //  $D5D8  20 EE D5
    JSR(underscorefuncunderscorec6f5, 127); //  $D5DB  20 F5 C6
    JSR(underscorefuncunderscored3d2, 128); //  $D5DE  20 D2 D3
    JSR(underscorefuncunderscorec6c4, 129); //  $D5E1  20 C4 C6
    JSR(underscorefuncunderscorecfba, 130); //  $D5E4  20 BA CF
    JSR(underscorefuncunderscored428, 131); //  $D5E7  20 28 D4
    ; // nop //  $D5EA  EA
    ; // nop //  $D5EB  EA
    ; // nop //  $D5EC  EA
    goto Return; //  $D5ED  60

//------------------------------------------------------------------------

underscorefuncunderscored5ee:
    a = M(underscorevarunderscore0300underscoreindexed); //  $D5EE  AD 00 03
    if (z)
        goto underscorelabelunderscored600; //  $D5F1  F0 0D
    y = 0x00; //  $D5F3  A0 00
    writeData(underscorevarunderscore00a1, y); //  $D5F5  84 A1
    JSR(underscorefuncunderscorec5f7, 132); //  $D5F7  20 F7 C5
    JSR(underscorefuncunderscored652, 133); //  $D5FA  20 52 D6
    JSR(underscorefuncunderscorec607, 134); //  $D5FD  20 07 C6

underscorelabelunderscored600:
    a = M(underscorevarunderscore0350); //  $D600  AD 50 03
    if (z)
        goto underscorelabelunderscored612; //  $D603  F0 0D
    y = 0x50; //  $D605  A0 50
    ++M(underscorevarunderscore00a1); //  $D607  E6 A1
    JSR(underscorefuncunderscorec5f7, 135); //  $D609  20 F7 C5
    JSR(underscorefuncunderscored652, 136); //  $D60C  20 52 D6
    JSR(underscorefuncunderscorec607, 137); //  $D60F  20 07 C6

underscorelabelunderscored612:
    a = M(underscorevarunderscore00bc); //  $D612  A5 BC
    if (!z)
        goto underscorelabelunderscored64b; //  $D614  D0 35
    x = M(underscorevarunderscore0301underscoreindexed); //  $D616  AE 01 03
    y = M(underscorevarunderscore0351); //  $D619  AC 51 03
    compare(x, 0x03); //  $D61C  E0 03
    if (z)
        goto underscorelabelunderscored627; //  $D61E  F0 07
    compare(y, 0x03); //  $D620  C0 03
    if (z)
        goto underscorelabelunderscored627; //  $D622  F0 03
    JSR(underscorefuncunderscored4fe, 138); //  $D624  20 FE D4

underscorelabelunderscored627:
    compare(x, 0x00); //  $D627  E0 00
    if (!z)
        goto underscorelabelunderscored651; //  $D629  D0 26
    compare(y, 0x00); //  $D62B  C0 00
    if (!z)
        goto underscorelabelunderscored651; //  $D62D  D0 22
    JSR(underscorefuncunderscored446, 139); //  $D62F  20 46 D4
    a = 0x00; //  $D632  A9 00
    writeData(underscorevarunderscore00b9, a); //  $D634  85 B9
    a = M(underscorevarunderscore00bb); //  $D636  A5 BB
    compare(a, 0x0A); //  $D638  C9 0A
    if (z)
        goto underscorelabelunderscored640; //  $D63A  F0 04
    a = 0x0A; //  $D63C  A9 0A
    if (!z)
        goto underscorelabelunderscored646; //  $D63E  D0 06

underscorelabelunderscored640:
    a = 0x00; //  $D640  A9 00
    writeData(underscorevarunderscore00a9underscoreindexed, a); //  $D642  85 A9
    a = 0x0C; //  $D644  A9 0C

underscorelabelunderscored646:
    writeData(underscorevarunderscore0025, a); //  $D646  85 25
    goto underscorefuncunderscorec23b; //  $D648  4C 3B C2

underscorelabelunderscored64b:
    a = M(underscorevarunderscore00a6); //  $D64B  A5 A6
    if (z)
        goto underscorelabelunderscored651; //  $D64D  F0 02
    --M(underscorevarunderscore00a6); //  $D64F  C6 A6

underscorelabelunderscored651:
    goto Return; //  $D651  60

//------------------------------------------------------------------------

underscorefuncunderscored652:
    a = M(underscorevarunderscore0031); //  $D652  A5 31
    JSR(underscorejumpunderscoreengineunderscorec35e, 140); //  $D654  20 5E C3
    compare(x, 0xC5); //  $D657  E0 C5
    a += 0xD6; //  $D659  69 D6
    /* sei */ //  $D65B  78
    --M(underscorevarunderscore00d5underscoreindexed + x); //  $D65C  D6 D5
    --M(underscorevarunderscore0052underscoreindexed + x); //  $D65E  D6 52
    { uint8_t temp = M(underscorevarunderscore008funderscoreindexed + x) - 1; writeData(underscorevarunderscore008funderscoreindexed + x, temp); compare(a, temp); } //  $D660  D7 8F
    { uint8_t temp = M(underscorevarunderscore00e0underscoreindexed + x) - 1; writeData(underscorevarunderscore00e0underscoreindexed + x, temp); compare(a, temp); } //  $D662  D7 E0
    compare(a, M(underscorevarunderscore00e0underscoreindexed)); //  $D664  C5 E0
    compare(a, M(underscorevarunderscore00c5underscoreindexed)); //  $D666  C5 C5
    { uint8_t temp = M(underscorevarunderscore00a2underscoreindexed + x) - 1; writeData(underscorevarunderscore00a2underscoreindexed + x, temp); compare(a, temp); } //  $D668  D7 A2

underscorelabelunderscored66b:

underscoredataunderscoredabd:

underscoredataunderscoree532underscoreindexed:

underscoredataunderscoree533underscoreindexed:

underscoredataunderscoree5dfunderscoreindexed:

underscoredataunderscoree5ebunderscoreindexed:

underscoredataunderscoreeb30underscoreindexed:

underscoredataunderscoreeb31underscoreindexed:

underscoredataunderscoreec02underscoreindexed:

underscoredataunderscoreec17underscoreindexed:

underscoredataunderscoreec1funderscoreindexed:

underscoredataunderscoreec38underscoreindexed:

underscoredataunderscoreec39underscoreindexed:

underscoredataunderscoref300underscoreindexed:

underscoredataunderscoref301underscoreindexed:

underscoredataunderscoref350underscoreindexed:

underscorefuncunderscoref35e:
    a = 0x00; //  $F35E  A9 00
    if (z)
        goto underscorelabelunderscoref36c; //  $F360  F0 0A

underscorefuncunderscoref362:
    a = 0x08; //  $F362  A9 08
    if (!z)
        goto underscorelabelunderscoref36c; //  $F364  D0 06

underscorefuncunderscoref366:
    a = 0x0C; //  $F366  A9 0C
    if (!z)
        goto underscorelabelunderscoref36c; //  $F368  D0 02

underscorefuncunderscoref36a:
    a = 0x04; //  $F36A  A9 04

underscorelabelunderscoref36c:
    writeData(underscorevarunderscore00f4underscoreindexed, a); //  $F36C  85 F4
    a = 0x40; //  $F36E  A9 40
    writeData(0xF5, a); //  $F370  85 F5
    writeData(underscorevarunderscore00f6underscoreindexed, x); //  $F372  86 F6
    writeData(0xF7, y); //  $F374  84 F7
    y = 0x00; //  $F376  A0 00

underscorelabelunderscoref378:
    a = M(W(underscorevarunderscore00f6underscoreindexed) + y); //  $F378  B1 F6
    writeData(W(underscorevarunderscore00f4underscoreindexed) + y, a); //  $F37A  91 F4
    ++y; //  $F37C  C8
    a = y; //  $F37D  98
    compare(a, 0x04); //  $F37E  C9 04
    if (!z)
        goto underscorelabelunderscoref378; //  $F380  D0 F6
    goto Return; //  $F382  60

//------------------------------------------------------------------------

underscorefuncunderscoref383:
    writeData(underscorevarunderscore00e6, a); //  $F383  85 E6
    a = M(underscoredataunderscoref846underscoreindexed + y); //  $F385  B9 46 F8
    y = a; //  $F388  A8
    a = M(underscoredataunderscoref846underscoreindexed + y); //  $F389  B9 46 F8
    writeData(underscorevarunderscore00e5, a); //  $F38C  85 E5
    a = M(underscoredataunderscoref847underscoreindexed + y); //  $F38E  B9 47 F8
    writeData(underscorevarunderscore00f8underscoreindexed, a); //  $F391  85 F8
    a = M(underscoredataunderscoref847underscoreindexed + 1 + y); //  $F393  B9 48 F8
    writeData(underscorevarunderscore00f9underscoreindexed, a); //  $F396  85 F9
    a = M(underscoredataunderscoref849underscoreindexed + y); //  $F398  B9 49 F8
    writeData(underscorevarunderscore00faunderscoreindexed, a); //  $F39B  85 FA
    a = M(underscoredataunderscoref849underscoreindexed + 1 + y); //  $F39D  B9 4A F8
    writeData(underscorevarunderscore00fb, a); //  $F3A0  85 FB
    a = M(underscoredataunderscoref84bunderscoreindexed + y); //  $F3A2  B9 4B F8
    writeData(underscorevarunderscore00fcunderscoreindexed, a); //  $F3A5  85 FC
    a = M(underscoredataunderscoref84bunderscoreindexed + 1 + y); //  $F3A7  B9 4C F8
    writeData(underscorevarunderscore00fd, a); //  $F3AA  85 FD
    a = M(underscoredataunderscoref84dunderscoreindexed + y); //  $F3AC  B9 4D F8
    writeData(underscorevarunderscore00feunderscoreindexed, a); //  $F3AF  85 FE
    a = M(underscoredataunderscoref84dunderscoreindexed + 1 + y); //  $F3B1  B9 4E F8
    writeData(underscorevarunderscore00ff, a); //  $F3B4  85 FF
    a = 0x01; //  $F3B6  A9 01
    writeData(underscorevarunderscore00d8, a); //  $F3B8  85 D8
    writeData(underscorevarunderscore00d9, a); //  $F3BA  85 D9
    writeData(underscorevarunderscore00da, a); //  $F3BC  85 DA
    writeData(underscorevarunderscore00db, a); //  $F3BE  85 DB
    a = 0x00; //  $F3C0  A9 00
    writeData(underscorevarunderscore00f3, a); //  $F3C2  85 F3
    writeData(underscorevarunderscore00d0underscoreindexed, a); //  $F3C4  85 D0
    writeData(underscorevarunderscore00d1, a); //  $F3C6  85 D1
    writeData(underscorevarunderscore00d2underscoreindexed, a); //  $F3C8  85 D2
    writeData(underscorevarunderscore00d3, a); //  $F3CA  85 D3
    writeData(APUunderscoreDMCunderscoreRAW, a); //  $F3CC  8D 11 40
    goto Return; //  $F3CF  60

//------------------------------------------------------------------------

underscorefuncunderscoref3d0:
    a = 0x7F; //  $F3D0  A9 7F
    writeData(APUunderscorePL1underscoreSWEEP, a); //  $F3D2  8D 01 40
    writeData(APUunderscorePL2underscoreSWEEP, a); //  $F3D5  8D 05 40
    writeData(0xE9, x); //  $F3D8  86 E9
    writeData(underscorevarunderscore00ea, y); //  $F3DA  84 EA
    goto Return; //  $F3DC  60

//------------------------------------------------------------------------

underscoredataunderscoref3e1underscoreindexed:

underscorelabelunderscoref40f:
    a = M(underscorevarunderscore00f9underscoreindexed); //  $F40F  A5 F9
    if (z)
        goto underscorelabelunderscoref451; //  $F411  F0 3E
    --M(underscorevarunderscore00d8); //  $F413  C6 D8
    if (!z)
        goto underscorelabelunderscoref451; //  $F415  D0 3A
    x = 0x00; //  $F417  A2 00
    a = 0x23; //  $F419  A9 23
    writeData(underscorevarunderscore0612, a); //  $F41B  8D 12 06
    a = 0x2E; //  $F41E  A9 2E
    writeData(underscorevarunderscore0610, a); //  $F420  8D 10 06
    y = M(underscorevarunderscore00d0underscoreindexed); //  $F423  A4 D0
    ++M(underscorevarunderscore00d0underscoreindexed); //  $F425  E6 D0
    a = M(W(underscorevarunderscore00f8underscoreindexed) + y); //  $F427  B1 F8
    if (z)
        goto underscorelabelunderscoref443; //  $F429  F0 18
    goto underscorelabelunderscoref51c; //  $F42B  4C 1C F5

underscorelabelunderscoref443:
    a = 0x00; //  $F443  A9 00
    goto underscorelabelunderscoref68c; //  $F445  4C 8C F6

underscorelabelunderscoref451:
    a = M(underscorevarunderscore00fb); //  $F451  A5 FB
    if (z)
        goto underscorelabelunderscoref47e; //  $F453  F0 29
    --M(underscorevarunderscore00d9); //  $F455  C6 D9
    if (!z)
        goto underscorelabelunderscoref47e; //  $F457  D0 25
    x = 0x01; //  $F459  A2 01
    y = M(underscorevarunderscore00d1); //  $F45B  A4 D1
    ++M(underscorevarunderscore00d1); //  $F45D  E6 D1
    a = M(W(underscorevarunderscore00faunderscoreindexed) + y); //  $F45F  B1 FA
    if (!n)
        goto underscorelabelunderscoref46c; //  $F461  10 09
    JSR(underscorefuncunderscoref544, 141); //  $F463  20 44 F5
    y = M(underscorevarunderscore00d1); //  $F466  A4 D1
    ++M(underscorevarunderscore00d1); //  $F468  E6 D1
    a = M(W(underscorevarunderscore00faunderscoreindexed) + y); //  $F46A  B1 FA

underscorelabelunderscoref46c:
    JSR(underscorefuncunderscoref564, 142); //  $F46C  20 64 F5
    if (!z)
        goto underscorelabelunderscoref475; //  $F46F  D0 04
    y = 0x10; //  $F471  A0 10
    if (!z)
        goto underscorelabelunderscoref477; //  $F473  D0 02

underscorelabelunderscoref475:
    y = M(underscorevarunderscore00ea); //  $F475  A4 EA

underscorelabelunderscoref477:
    writeData(APUunderscorePL2underscoreVOL, y); //  $F477  8C 04 40
    a = M(0xDD); //  $F47A  A5 DD
    writeData(underscorevarunderscore00d9, a); //  $F47C  85 D9

underscorelabelunderscoref47e:
    a = M(underscorevarunderscore00fd); //  $F47E  A5 FD
    if (z)
        goto underscorelabelunderscoref4d1; //  $F480  F0 4F
    --M(underscorevarunderscore00da); //  $F482  C6 DA
    if (!z)
        goto underscorelabelunderscoref4d1; //  $F484  D0 4B
    x = 0x02; //  $F486  A2 02
    a = 0x9B; //  $F488  A9 9B
    writeData(underscorevarunderscore0610, a); //  $F48A  8D 10 06
    a = 0x92; //  $F48D  A9 92
    writeData(underscorevarunderscore0612, a); //  $F48F  8D 12 06
    y = M(underscorevarunderscore00d2underscoreindexed); //  $F492  A4 D2
    ++M(underscorevarunderscore00d2underscoreindexed); //  $F494  E6 D2
    a = M(W(underscorevarunderscore00fcunderscoreindexed) + y); //  $F496  B1 FC
    goto underscorelabelunderscoref51c; //  $F498  4C 1C F5

underscorelabelunderscoref4d1:
    a = M(underscorevarunderscore00ff); //  $F4D1  A5 FF
    if (z)
        goto underscorelabelunderscoref501; //  $F4D3  F0 2C
    --M(underscorevarunderscore00db); //  $F4D5  C6 DB
    if (!z)
        goto underscorelabelunderscoref501; //  $F4D7  D0 28
    x = 0x03; //  $F4D9  A2 03
    a = 0xEE; //  $F4DB  A9 EE
    writeData(underscorevarunderscore0610, a); //  $F4DD  8D 10 06
    a = 0xE5; //  $F4E0  A9 E5
    writeData(underscorevarunderscore0612, a); //  $F4E2  8D 12 06
    y = M(underscorevarunderscore00d3); //  $F4E5  A4 D3
    ++M(underscorevarunderscore00d3); //  $F4E7  E6 D3
    a = M(W(underscorevarunderscore00feunderscoreindexed) + y); //  $F4E9  B1 FE
    goto underscorelabelunderscoref51c; //  $F4EB  4C 1C F5

underscorelabelunderscoref501:
    goto Return; //  $F501  60

//------------------------------------------------------------------------

underscorelabelunderscoref51c:
    y = a; //  $F51C  A8
    compare(a, 0xFF); //  $F51D  C9 FF
    if (z)
        goto underscorelabelunderscoref52a; //  $F51F  F0 09
    a &= 0xC0; //  $F521  29 C0
    compare(a, 0xC0); //  $F523  C9 C0
    if (z)
        goto underscorelabelunderscoref536; //  $F525  F0 0F
    indirectJumpAddress = W(underscorevarunderscore0610); goto IndirectJumpResult; //  $F527  6C 10 06  jump engine detected

underscorelabelunderscoref52a:
    a = M(underscorevarunderscore00e0underscoreindexed + x); //  $F52A  B5 E0
    if (z)
        goto underscorelabelunderscoref541; //  $F52C  F0 13
    --M(underscorevarunderscore00e0underscoreindexed + x); //  $F52E  D6 E0
    a = M(underscorevarunderscore00d4underscoreindexed + x); //  $F530  B5 D4
    writeData(underscorevarunderscore00d0underscoreindexed + x, a); //  $F532  95 D0
    if (!z)
        goto underscorelabelunderscoref541; //  $F534  D0 0B

underscorelabelunderscoref536:
    a = y; //  $F536  98
    a &= 0x3F; //  $F537  29 3F
    writeData(underscorevarunderscore00e0underscoreindexed + x, a); //  $F539  95 E0
    --M(underscorevarunderscore00e0underscoreindexed + x); //  $F53B  D6 E0
    a = M(underscorevarunderscore00d0underscoreindexed + x); //  $F53D  B5 D0
    writeData(underscorevarunderscore00d4underscoreindexed + x, a); //  $F53F  95 D4

underscorelabelunderscoref541:
    indirectJumpAddress = W(underscorevarunderscore0612); goto IndirectJumpResult; //  $F541  6C 12 06  jump engine detected

underscorefuncunderscoref544:
    a &= 0x07; //  $F544  29 07
    c = 0; //  $F546  18
    a += M(underscorevarunderscore00e5); //  $F547  65 E5
    y = a; //  $F549  A8
    a = M(underscoredataunderscoref350underscoreindexed + y); //  $F54A  B9 50 F3
    writeData(underscorevarunderscore00dcunderscoreindexed + x, a); //  $F54D  95 DC
    goto Return; //  $F54F  60

//------------------------------------------------------------------------

underscorelabelunderscoref552:
    y = a; //  $F552  A8
    a = M(underscoredataunderscoref301underscoreindexed + y); //  $F553  B9 01 F3
    if (z)
        goto underscorelabelunderscoref563; //  $F556  F0 0B
    writeData(APUunderscorePL1underscoreLO + x, a); //  $F558  9D 02 40
    a = M(underscoredataunderscoref300underscoreindexed + y); //  $F55B  B9 00 F3
    a |= 0x08; //  $F55E  09 08
    writeData(APUunderscorePL1underscoreHI + x, a); //  $F560  9D 03 40

underscorelabelunderscoref563:
    goto Return; //  $F563  60

//------------------------------------------------------------------------

underscorefuncunderscoref564:
    x = 0x04; //  $F564  A2 04
    if (!z)
        goto underscorelabelunderscoref552; //  $F566  D0 EA
    x = 0x08; //  $F568  A2 08
    if (!z)
        goto underscorelabelunderscoref552; //  $F56A  D0 E6

underscorefuncunderscoref56c:
    a = 0xC0; //  $F56C  A9 C0
    writeData(APUunderscoreFRAME, a); //  $F56E  8D 17 40
    JSR(underscorefuncunderscoref6cf, 143); //  $F571  20 CF F6
    JSR(underscorefuncunderscoref621, 144); //  $F574  20 21 F6
    JSR(underscorefuncunderscoref7cc, 145); //  $F577  20 CC F7
    JSR(underscorefuncunderscoref591, 146); //  $F57A  20 91 F5
    a = 0x00; //  $F57D  A9 00
    if (z)
        goto underscorelabelunderscoref58a; //  $F57F  F0 09

underscorefuncunderscoref581:
    a = 0xF4; //  $F581  A9 F4
    writeData(0x0613, a); //  $F583  8D 13 06
    writeData(0x0611, a); //  $F586  8D 11 06
    goto Return; //  $F589  60

//------------------------------------------------------------------------

underscorelabelunderscoref58a:
    writeData(underscorevarunderscore00f0, a); //  $F58A  85 F0
    writeData(underscorevarunderscore00f1, a); //  $F58C  85 F1
    writeData(underscorevarunderscore00f2, a); //  $F58E  85 F2
    goto Return; //  $F590  60

//------------------------------------------------------------------------

underscorefuncunderscoref591:
    a = M(underscorevarunderscore00f2); //  $F591  A5 F2
    M(a) >>= 1; //  $F593  4A
    if (c)
        goto underscorelabelunderscoref5a2; //  $F594  B0 0C
    M(a) >>= 1; //  $F596  4A
    if (c)
        goto underscorelabelunderscoref59a; //  $F597  B0 01
    goto Return; //  $F599  60

//------------------------------------------------------------------------

underscorelabelunderscoref59a:
    a = 0x20; //  $F59A  A9 20
    x = 0xF4; //  $F59C  A2 F4
    y = 0x0F; //  $F59E  A0 0F
    if (!z)
        goto underscorelabelunderscoref5a8; //  $F5A0  D0 06

underscorelabelunderscoref5a2:
    a = 0x20; //  $F5A2  A9 20
    x = 0xEC; //  $F5A4  A2 EC
    y = 0x0E; //  $F5A6  A0 0E

underscorelabelunderscoref5a8:
    writeData(APUunderscoreDMCunderscoreLEN, a); //  $F5A8  8D 13 40
    writeData(APUunderscoreDMCunderscoreSTART, x); //  $F5AB  8E 12 40
    writeData(APUunderscoreDMCunderscoreFREQ, y); //  $F5AE  8C 10 40
    a = 0x1F; //  $F5B1  A9 1F
    writeData(APUunderscoreSNDunderscoreCHN, a); //  $F5B3  8D 15 40
    goto Return; //  $F5B6  60

//------------------------------------------------------------------------

underscorelabelunderscoref5bf:
    x = 0xDD; //  $F5BF  A2 DD
    y = 0xF3; //  $F5C1  A0 F3
    JSR(underscorefuncunderscoref362, 147); //  $F5C3  20 62 F3
    a = 0x00; //  $F5C6  A9 00
    writeData(underscorevarunderscore00eb, a); //  $F5C8  85 EB
    writeData(underscorevarunderscore00ed, a); //  $F5CA  85 ED
    writeData(underscorevarunderscore00ee, a); //  $F5CC  85 EE
    a = 0x06; //  $F5CE  A9 06
    writeData(underscorevarunderscore00ef, a); //  $F5D0  85 EF
    a = 0x3E; //  $F5D2  A9 3E
    writeData(underscorevarunderscore00ec, a); //  $F5D4  85 EC
    a = 0x40; //  $F5D6  A9 40
    writeData(underscorevarunderscore00f3, a); //  $F5D8  85 F3

underscorelabelunderscoref5da:
    goto Return; //  $F5DA  60

//------------------------------------------------------------------------

underscorelabelunderscoref5db:
    ++M(underscorevarunderscore00ee); //  $F5DB  E6 EE
    a = M(underscorevarunderscore00ee); //  $F5DD  A5 EE
    compare(a, 0x01); //  $F5DF  C9 01
    if (!z)
        goto underscorelabelunderscoref5da; //  $F5E1  D0 F7
    a = 0x00; //  $F5E3  A9 00
    writeData(underscorevarunderscore00ee, a); //  $F5E5  85 EE
    ++M(underscorevarunderscore00eb); //  $F5E7  E6 EB
    a = M(underscorevarunderscore00eb); //  $F5E9  A5 EB
    compare(a, M(underscorevarunderscore00ef)); //  $F5EB  C5 EF
    if (z)
        goto underscorelabelunderscoref5fb; //  $F5ED  F0 0C
    --M(underscorevarunderscore00ec); //  $F5EF  C6 EC
    --M(underscorevarunderscore00ec); //  $F5F1  C6 EC
    --M(underscorevarunderscore00ec); //  $F5F3  C6 EC
    a = M(underscorevarunderscore00ec); //  $F5F5  A5 EC
    writeData(APUunderscoreTRIunderscoreLO, a); //  $F5F7  8D 0A 40
    goto Return; //  $F5FA  60

//------------------------------------------------------------------------

underscorelabelunderscoref5fb:
    a = M(underscorevarunderscore00ef); //  $F5FB  A5 EF
    c = 0; //  $F5FD  18
    a += 0x06; //  $F5FE  69 06
    writeData(underscorevarunderscore00ef, a); //  $F600  85 EF
    y = M(underscorevarunderscore00ed); //  $F602  A4 ED
    a = M(underscoredataunderscoref3e1underscoreindexed + y); //  $F604  B9 E1 F3
    writeData(APUunderscoreTRIunderscoreLO, a); //  $F607  8D 0A 40
    writeData(underscorevarunderscore00ec, a); //  $F60A  85 EC
    a = 0xF0; //  $F60C  A9 F0
    writeData(APUunderscoreTRIunderscoreHI, a); //  $F60E  8D 0B 40
    ++M(underscorevarunderscore00ed); //  $F611  E6 ED
    a = M(underscorevarunderscore00ed); //  $F613  A5 ED
    compare(a, 0x0E); //  $F615  C9 0E
    if (!z)
        goto underscorelabelunderscoref5da; //  $F617  D0 C1
    a = 0x00; //  $F619  A9 00
    writeData(APUunderscoreTRIunderscoreLINEAR, a); //  $F61B  8D 08 40
    writeData(underscorevarunderscore00f3, a); //  $F61E  85 F3
    goto Return; //  $F620  60

//------------------------------------------------------------------------

underscorefuncunderscoref621:
    a = M(underscorevarunderscore00f0); //  $F621  A5 F0
    M(a) <<= 1; //  $F623  0A
    if (c)
        goto underscorelabelunderscoref669; //  $F624  B0 43
    M(a) <<= 1; //  $F626  0A
    if (c)
        goto underscorelabelunderscoref5bf; //  $F627  B0 96
    M(a) <<= 1; //  $F629  0A
    if (c)
        goto underscorelabelunderscoref641; //  $F62A  B0 15
    M(a) <<= 1; //  $F62C  0A
    if (c)
        goto underscorelabelunderscoref639; //  $F62D  B0 0A
    a = M(underscorevarunderscore00f3); //  $F62F  A5 F3
    M(a) <<= 1; //  $F631  0A
    M(a) <<= 1; //  $F632  0A
    if (c)
        goto underscorelabelunderscoref5db; //  $F633  B0 A6
    M(a) <<= 1; //  $F635  0A
    if (c)
        goto underscorelabelunderscoref655; //  $F636  B0 1D
    goto Return; //  $F638  60

//------------------------------------------------------------------------

underscorelabelunderscoref639:
    x = 0xEF; //  $F639  A2 EF
    y = 0xF3; //  $F63B  A0 F3
    JSR(underscorefuncunderscoref35e, 148); //  $F63D  20 5E F3
    goto Return; //  $F640  60

//------------------------------------------------------------------------

underscorelabelunderscoref641:
    x = 0xF3; //  $F641  A2 F3
    y = 0xF3; //  $F643  A0 F3
    JSR(underscorefuncunderscoref36a, 149); //  $F645  20 6A F3
    a = M(underscorevarunderscore00f3); //  $F648  A5 F3
    a |= 0x20; //  $F64A  09 20
    writeData(underscorevarunderscore00f3, a); //  $F64C  85 F3
    a = 0x00; //  $F64E  A9 00
    writeData(underscorevarunderscore00ef, a); //  $F650  85 EF
    writeData(underscorevarunderscore00ee, a); //  $F652  85 EE

underscorelabelunderscoref654:
    goto Return; //  $F654  60

//------------------------------------------------------------------------

underscorelabelunderscoref655:
    ++M(underscorevarunderscore00ee); //  $F655  E6 EE
    a = M(underscorevarunderscore00ee); //  $F657  A5 EE
    compare(a, 0x02); //  $F659  C9 02
    if (!z)
        goto underscorelabelunderscoref654; //  $F65B  D0 F7
    a = 0x00; //  $F65D  A9 00
    writeData(underscorevarunderscore00ee, a); //  $F65F  85 EE
    ++M(underscorevarunderscore00ef); //  $F661  E6 EF
    a = M(underscorevarunderscore00ef); //  $F663  A5 EF
    compare(a, 0xA0); //  $F665  C9 A0
    if (!z)
        goto underscorelabelunderscoref654; //  $F667  D0 EB

underscorelabelunderscoref669:
    a = 0x10; //  $F669  A9 10
    writeData(APUunderscorePL2underscoreVOL, a); //  $F66B  8D 04 40
    a = M(underscorevarunderscore00f3); //  $F66E  A5 F3
    a &= 0xDF; //  $F670  29 DF
    writeData(underscorevarunderscore00f3, a); //  $F672  85 F3
    goto Return; //  $F674  60

//------------------------------------------------------------------------

underscorelabelunderscoref675:
    x = 0xF7; //  $F675  A2 F7
    y = 0xF3; //  $F677  A0 F3
    JSR(underscorefuncunderscoref366, 150); //  $F679  20 66 F3
    a = 0x10; //  $F67C  A9 10
    writeData(APUunderscorePL1underscoreVOL, a); //  $F67E  8D 00 40
    a = M(underscorevarunderscore00f3); //  $F681  A5 F3
    a &= 0xF0; //  $F683  29 F0
    writeData(underscorevarunderscore00f3, a); //  $F685  85 F3
    goto Return; //  $F687  60

//------------------------------------------------------------------------

underscorelabelunderscoref688:
    a = 0x00; //  $F688  A9 00
    writeData(underscorevarunderscore00f3, a); //  $F68A  85 F3

underscorelabelunderscoref68c:
    writeData(APUunderscoreTRIunderscoreLINEAR, a); //  $F68C  8D 08 40
    writeData(APUunderscoreDMCunderscoreRAW, a); //  $F68F  8D 11 40
    writeData(underscorevarunderscore00e6, a); //  $F692  85 E6
    writeData(underscorevarunderscore00e4, a); //  $F694  85 E4
    a = 0x10; //  $F696  A9 10
    writeData(APUunderscorePL1underscoreVOL, a); //  $F698  8D 00 40
    writeData(APUunderscorePL2underscoreVOL, a); //  $F69B  8D 04 40
    writeData(APUunderscoreNOISEunderscoreVOL, a); //  $F69E  8D 0C 40
    goto Return; //  $F6A1  60

//------------------------------------------------------------------------

underscorelabelunderscoref6a2:
    x = 0xFB; //  $F6A2  A2 FB
    y = 0xF3; //  $F6A4  A0 F3
    JSR(underscorefuncunderscoref366, 151); //  $F6A6  20 66 F3
    a = 0x00; //  $F6A9  A9 00
    writeData(underscorevarunderscore00eb, a); //  $F6AB  85 EB
    a = M(underscorevarunderscore00f3); //  $F6AD  A5 F3
    a |= 0x08; //  $F6AF  09 08
    writeData(underscorevarunderscore00f3, a); //  $F6B1  85 F3

underscorelabelunderscoref6b3:
    goto Return; //  $F6B3  60

//------------------------------------------------------------------------

underscorelabelunderscoref6b4:
    y = M(underscorevarunderscore00eb); //  $F6B4  A4 EB
    a = M(underscoredataunderscoref6cbunderscoreindexed + y); //  $F6B6  B9 CB F6
    writeData(APUunderscoreNOISEunderscoreLO, a); //  $F6B9  8D 0E 40
    ++M(underscorevarunderscore00eb); //  $F6BC  E6 EB
    a = M(underscorevarunderscore00eb); //  $F6BE  A5 EB
    compare(a, 0x04); //  $F6C0  C9 04
    if (!z)
        goto underscorelabelunderscoref6b3; //  $F6C2  D0 EF
    a = M(underscorevarunderscore00f3); //  $F6C4  A5 F3
    a &= 0xFE; //  $F6C6  29 FE
    writeData(underscorevarunderscore00f3, a); //  $F6C8  85 F3
    goto Return; //  $F6CA  60

//------------------------------------------------------------------------

underscoredataunderscoref6cbunderscoreindexed:

underscorefuncunderscoref6cf:
    a = M(underscorevarunderscore00f0); //  $F6CF  A5 F0
    M(a) >>= 1; //  $F6D1  4A
    if (c)
        goto underscorelabelunderscoref688; //  $F6D2  B0 B4
    M(a) >>= 1; //  $F6D4  4A
    if (c)
        goto underscorelabelunderscoref6e8; //  $F6D5  B0 11
    M(a) >>= 1; //  $F6D7  4A
    if (c)
        goto underscorelabelunderscoref675; //  $F6D8  B0 9B
    M(a) >>= 1; //  $F6DA  4A
    if (c)
        goto underscorelabelunderscoref6a2; //  $F6DB  B0 C5
    a = M(underscorevarunderscore00f3); //  $F6DD  A5 F3
    M(a) >>= 1; //  $F6DF  4A
    M(a) >>= 1; //  $F6E0  4A
    if (c)
        goto underscorelabelunderscoref703; //  $F6E1  B0 20
    M(a) >>= 1; //  $F6E3  4A
    M(a) >>= 1; //  $F6E4  4A
    if (c)
        goto underscorelabelunderscoref6b4; //  $F6E5  B0 CD
    goto Return; //  $F6E7  60

//------------------------------------------------------------------------

underscorelabelunderscoref6e8:
    x = 0xFF; //  $F6E8  A2 FF
    y = 0xF6; //  $F6EA  A0 F6
    JSR(underscorefuncunderscoref366, 152); //  $F6EC  20 66 F3
    a = 0x00; //  $F6EF  A9 00
    writeData(underscorevarunderscore00ec, a); //  $F6F1  85 EC
    writeData(underscorevarunderscore00ed, a); //  $F6F3  85 ED
    writeData(APUunderscoreDMCunderscoreRAW, a); //  $F6F5  8D 11 40
    a = M(underscorevarunderscore00f3); //  $F6F8  A5 F3
    a |= 0x02; //  $F6FA  09 02
    writeData(underscorevarunderscore00f3, a); //  $F6FC  85 F3

underscorelabelunderscoref6fe:
    goto Return; //  $F6FE  60

//------------------------------------------------------------------------

underscorelabelunderscoref703:
    ++M(underscorevarunderscore00ec); //  $F703  E6 EC
    a = M(underscorevarunderscore00ec); //  $F705  A5 EC
    compare(a, 0x02); //  $F707  C9 02
    if (!z)
        goto underscorelabelunderscoref6fe; //  $F709  D0 F3
    a = 0x00; //  $F70B  A9 00
    writeData(underscorevarunderscore00ec, a); //  $F70D  85 EC
    y = M(underscorevarunderscore00ed); //  $F70F  A4 ED
    a = M(underscoredataunderscoref731underscoreindexed + y); //  $F711  B9 31 F7
    writeData(APUunderscoreNOISEunderscoreLO, a); //  $F714  8D 0E 40
    a = M(underscoredataunderscoref761underscoreindexed + y); //  $F717  B9 61 F7
    writeData(APUunderscoreNOISEunderscoreVOL, a); //  $F71A  8D 0C 40
    ++M(underscorevarunderscore00ed); //  $F71D  E6 ED
    a = M(underscorevarunderscore00ed); //  $F71F  A5 ED
    compare(a, 0x30); //  $F721  C9 30
    if (!z)
        goto underscorelabelunderscoref730; //  $F723  D0 0B
    a = 0x10; //  $F725  A9 10
    writeData(APUunderscoreNOISEunderscoreVOL, a); //  $F727  8D 0C 40
    a = M(underscorevarunderscore00f3); //  $F72A  A5 F3
    a &= 0xFD; //  $F72C  29 FD
    writeData(underscorevarunderscore00f3, a); //  $F72E  85 F3

underscorelabelunderscoref730:
    goto Return; //  $F730  60

//------------------------------------------------------------------------

underscoredataunderscoref731underscoreindexed:

underscoredataunderscoref761underscoreindexed:

underscorelabelunderscoref791:
    x = 0xB7; //  $F791  A2 B7
    y = 0xF5; //  $F793  A0 F5
    JSR(underscorefuncunderscoref35e, 153); //  $F795  20 5E F3
    x = 0xBB; //  $F798  A2 BB
    y = 0xF5; //  $F79A  A0 F5

underscorelabelunderscoref79c:
    JSR(underscorefuncunderscoref36a, 154); //  $F79C  20 6A F3
    goto Return; //  $F79F  60

//------------------------------------------------------------------------

underscorelabelunderscoref7a8:
    a = 0x00; //  $F7A8  A9 00
    writeData(APUunderscorePL1underscoreVOL, a); //  $F7AA  8D 00 40
    x = 0xA0; //  $F7AD  A2 A0
    y = 0xF7; //  $F7AF  A0 F7
    JSR(underscorefuncunderscoref35e, 155); //  $F7B1  20 5E F3
    x = 0xA4; //  $F7B4  A2 A4
    y = 0xF7; //  $F7B6  A0 F7
    if (!z)
        goto underscorelabelunderscoref79c; //  $F7B8  D0 E2

underscorelabelunderscoref7ba:
    y = 0x06; //  $F7BA  A0 06
    a = 0x80; //  $F7BC  A9 80
    if (!z)
        goto underscorelabelunderscoref82f; //  $F7BE  D0 6F

underscorelabelunderscoref7c0:
    y = 0x04; //  $F7C0  A0 04
    a = 0x04; //  $F7C2  A9 04
    if (!z)
        goto underscorelabelunderscoref826; //  $F7C4  D0 60

underscorelabelunderscoref7c6:
    y = 0x05; //  $F7C6  A0 05
    a = 0x08; //  $F7C8  A9 08
    if (!z)
        goto underscorelabelunderscoref826; //  $F7CA  D0 5A

underscorefuncunderscoref7cc:
    a = M(underscorevarunderscore00f1); //  $F7CC  A5 F1
    M(a) >>= 1; //  $F7CE  4A
    if (c)
        goto underscorelabelunderscoref7fd; //  $F7CF  B0 2C
    M(a) >>= 1; //  $F7D1  4A
    if (c)
        goto underscorelabelunderscoref803; //  $F7D2  B0 2F
    M(a) >>= 1; //  $F7D4  4A
    if (c)
        goto underscorelabelunderscoref7c0; //  $F7D5  B0 E9
    M(a) >>= 1; //  $F7D7  4A
    if (c)
        goto underscorelabelunderscoref7c6; //  $F7D8  B0 EC
    M(a) >>= 1; //  $F7DA  4A
    if (c)
        goto underscorelabelunderscoref809; //  $F7DB  B0 2C
    M(a) >>= 1; //  $F7DD  4A
    if (c)
        goto underscorelabelunderscoref80f; //  $F7DE  B0 2F
    M(a) >>= 1; //  $F7E0  4A
    if (c)
        goto underscorelabelunderscoref815; //  $F7E1  B0 32
    M(a) >>= 1; //  $F7E3  4A
    if (c)
        goto underscorelabelunderscoref7ba; //  $F7E4  B0 D4
    a = M(underscorevarunderscore00f2); //  $F7E6  A5 F2
    M(a) <<= 1; //  $F7E8  0A
    if (c)
        goto underscorelabelunderscoref81b; //  $F7E9  B0 30
    M(a) <<= 1; //  $F7EB  0A
    M(a) <<= 1; //  $F7EC  0A
    if (c)
        goto underscorelabelunderscoref791; //  $F7ED  B0 A2
    M(a) <<= 1; //  $F7EF  0A
    if (c)
        goto underscorelabelunderscoref840; //  $F7F0  B0 4E
    M(a) <<= 1; //  $F7F2  0A
    if (c)
        goto underscorelabelunderscoref7a8; //  $F7F3  B0 B3
    a = M(underscorevarunderscore00e6); //  $F7F5  A5 E6
    if (!z)
        goto underscorelabelunderscoref7fa; //  $F7F7  D0 01
    goto Return; //  $F7F9  60

//------------------------------------------------------------------------

underscorelabelunderscoref7fa:
    goto underscorelabelunderscoref40f; //  $F7FA  4C 0F F4

underscorelabelunderscoref7fd:
    y = 0x00; //  $F7FD  A0 00
    a = 0x01; //  $F7FF  A9 01
    if (!z)
        goto underscorelabelunderscoref826; //  $F801  D0 23

underscorelabelunderscoref803:
    y = 0x03; //  $F803  A0 03
    a = 0x02; //  $F805  A9 02
    if (!z)
        goto underscorelabelunderscoref82f; //  $F807  D0 26

underscorelabelunderscoref809:
    y = 0x01; //  $F809  A0 01
    a = 0x10; //  $F80B  A9 10
    if (!z)
        goto underscorelabelunderscoref826; //  $F80D  D0 17

underscorelabelunderscoref80f:
    y = 0x07; //  $F80F  A0 07
    a = 0x20; //  $F811  A9 20
    if (!z)
        goto underscorelabelunderscoref826; //  $F813  D0 11

underscorelabelunderscoref815:
    y = 0x02; //  $F815  A0 02
    a = 0x40; //  $F817  A9 40
    if (!z)
        goto underscorelabelunderscoref826; //  $F819  D0 0B

underscorelabelunderscoref81b:
    a = 0x10; //  $F81B  A9 10
    writeData(APUunderscoreNOISEunderscoreVOL, a); //  $F81D  8D 0C 40
    y = 0x08; //  $F820  A0 08
    a = 0xEF; //  $F822  A9 EF
    if (!z)
        goto underscorelabelunderscoref82f; //  $F824  D0 09

underscorelabelunderscoref826:
    JSR(underscorefuncunderscoref383, 156); //  $F826  20 83 F3
    x = 0xC0; //  $F829  A2 C0
    y = 0xC0; //  $F82B  A0 C0
    if (!z)
        goto underscorelabelunderscoref836; //  $F82D  D0 07

underscorelabelunderscoref82f:
    JSR(underscorefuncunderscoref383, 157); //  $F82F  20 83 F3
    x = 0x86; //  $F832  A2 86
    y = 0x86; //  $F834  A0 86

underscorelabelunderscoref836:
    JSR(underscorefuncunderscoref3d0, 158); //  $F836  20 D0 F3
    a = 0x00; //  $F839  A9 00
    writeData(underscorevarunderscore00e4, a); //  $F83B  85 E4
    goto underscorelabelunderscoref40f; //  $F83D  4C 0F F4

underscorelabelunderscoref840:
    y = 0x09; //  $F840  A0 09
    a = 0xEF; //  $F842  A9 EF
    if (!z)
        goto underscorelabelunderscoref826; //  $F844  D0 E0

underscoredataunderscoref846underscoreindexed:
    M(a) <<= 1; //  $F846  0A

underscoredataunderscoref847underscoreindexed:
    { uint8_t temp = M(W(underscorevarunderscore001cunderscoreindexed) + y); temp <<= 1; writeData(W(underscorevarunderscore001cunderscoreindexed) + y, temp); a |= temp; } //  $F847  13 1C

underscoredataunderscoref849underscoreindexed:
    a &= M(0x2E); //  $F849  25 2E

underscoredataunderscoref84bunderscoreindexed:
    { uint8_t temp = M(underscorevarunderscore0040underscoreindexed + x); temp = (temp << 1) | (c ? 1 : 0); c = (temp & 0x80) ? 1 : 0; temp &= 0x7F; writeData(underscorevarunderscore0040underscoreindexed + x, temp); a &= temp; } //  $F84B  37 40

underscoredataunderscoref84dunderscoreindexed:
    a ^= 0x52; //  $F84D  49 52
    { uint8_t temp = M(underscoredataunderscorec306underscoreindexed + 1 + y); c = (temp & 0x01) ? 1 : 0; temp >>= 1; writeData(underscoredataunderscorec306underscoreindexed + 1 + y, temp); a ^= temp; } //  $F84F  5B 07 C3
    /* sed */ //  $F852  F8

underscoredataunderscoref91bunderscoreindexed:

underscoredataunderscoref960underscoreindexed:

underscoredataunderscoref9f7underscoreindexed:

underscoredataunderscoreff18underscoreindexed:

// Indirect jump dispatcher
IndirectJumpResult:
    switch (indirectJumpAddress)
    {
    case 0x80b4:
        goto NMI;
    case 0x8000:
        goto Reset;
    case 0x8420:
        goto underscoredataunderscorec306underscoreindexed;
    case 0x8c45:
        goto underscoredataunderscorecafa;
    case 0x8c48:
        goto underscoredataunderscorecc4f;
    case 0x8c6f:
        goto underscoredataunderscorece4d;
    case 0x926f:
        goto underscoredataunderscoredabd;
    case 0x9272:
        goto underscoredataunderscoree532underscoreindexed;
    case 0x9275:
        goto underscoredataunderscoree533underscoreindexed;
    case 0x9278:
        goto underscoredataunderscoree5dfunderscoreindexed;
    case 0x927b:
        goto underscoredataunderscoree5ebunderscoreindexed;
    case 0x927e:
        goto underscoredataunderscoreeb30underscoreindexed;
    case 0x9281:
        goto underscoredataunderscoreeb31underscoreindexed;
    case 0x9284:
        goto underscoredataunderscoreec02underscoreindexed;
    case 0x9287:
        goto underscoredataunderscoreec17underscoreindexed;
    case 0x928a:
        goto underscoredataunderscoreec1funderscoreindexed;
    case 0x928d:
        goto underscoredataunderscoreec38underscoreindexed;
    case 0x9290:
        goto underscoredataunderscoreec39underscoreindexed;
    case 0x9293:
        goto underscoredataunderscoref300underscoreindexed;
    case 0x9296:
        goto underscoredataunderscoref301underscoreindexed;
    case 0x9299:
        goto underscoredataunderscoref350underscoreindexed;
    case 0x9350:
        goto underscoredataunderscoref3e1underscoreindexed;
    case 0x9683:
        goto underscoredataunderscoref6cbunderscoreindexed;
    case 0x9719:
        goto underscoredataunderscoref731underscoreindexed;
    case 0x971c:
        goto underscoredataunderscoref761underscoreindexed;
    case 0x982a:
        goto underscoredataunderscoref846underscoreindexed;
    case 0x982d:
        goto underscoredataunderscoref847underscoreindexed;
    case 0x9830:
        goto underscoredataunderscoref849underscoreindexed;
    case 0x9833:
        goto underscoredataunderscoref84bunderscoreindexed;
    case 0x9836:
        goto underscoredataunderscoref84dunderscoreindexed;
    case 0x983f:
        goto underscoredataunderscoref91bunderscoreindexed;
    case 0x9842:
        goto underscoredataunderscoref960underscoreindexed;
    case 0x9845:
        goto underscoredataunderscoref9f7underscoreindexed;
    case 0x9848:
        goto underscoredataunderscoreff18underscoreindexed;
    case 0x8102:
        goto underscorefuncunderscorec0b3;
    case 0x82d3:
        goto underscorefuncunderscorec22b;
    case 0x82d9:
        goto underscorefuncunderscorec230;
    case 0x82dc:
        goto underscorefuncunderscorec232;
    case 0x82e8:
        goto underscorefuncunderscorec23b;
    case 0x8303:
        goto underscorefuncunderscorec249;
    case 0x832d:
        goto underscorefuncunderscorec263;
    case 0x8360:
        goto underscorefuncunderscorec284;
    case 0x8372:
        goto underscorefuncunderscorec291;
    case 0x83b7:
        goto underscorefuncunderscorec2bf;
    case 0x841d:
        goto underscorefuncunderscorec303;
    case 0x8480:
        goto underscorefuncunderscorec348;
    case 0x8543:
        goto underscorefuncunderscorec3b8;
    case 0x854f:
        goto underscorefuncunderscorec3c1;
    case 0x85e2:
        goto underscorefuncunderscorec426;
    case 0x8600:
        goto underscorefuncunderscorec4bf;
    case 0x8636:
        goto underscorefuncunderscorec4e0;
    case 0x866c:
        goto underscorefuncunderscorec502;
    case 0x8687:
        goto underscorefuncunderscorec511;
    case 0x8744:
        goto underscorefuncunderscorec588;
    case 0x87aa:
        goto underscorefuncunderscorec5d9;
    case 0x87b6:
        goto underscorefuncunderscorec5e1;
    case 0x87c8:
        goto underscorefuncunderscorec5ee;
    case 0x87d4:
        goto underscorefuncunderscorec5f7;
    case 0x87ef:
        goto underscorefuncunderscorec607;
    case 0x880a:
        goto underscorefuncunderscorec617;
    case 0x8813:
        goto underscorefuncunderscorec61e;
    case 0x8840:
        goto underscorefuncunderscorec641;
    case 0x8852:
        goto underscorefuncunderscorec64b;
    case 0x88d6:
        goto underscorefuncunderscorec6c4;
    case 0x88e2:
        goto underscorefuncunderscorec6cc;
    case 0x891e:
        goto underscorefuncunderscorec6f5;
    case 0x895a:
        goto underscorefuncunderscorec71d;
    case 0x8a0b:
        goto underscorefuncunderscorec793;
    case 0x8a38:
        goto underscorefuncunderscorec7b3;
    case 0x8aa4:
        goto underscorefuncunderscorec7fb;
    case 0x8b70:
        goto underscorefuncunderscorec890;
    case 0x8c09:
        goto underscorefuncunderscorec902;
    case 0x8c4b:
        goto underscorefuncunderscorecc94;
    case 0x8c66:
        goto underscorefuncunderscorecca9;
    case 0x8c72:
        goto underscorefuncunderscorecfba;
    case 0x8c81:
        goto underscorefuncunderscorecfc5;
    case 0x8cc6:
        goto underscorefuncunderscored131;
    case 0x8d0e:
        goto underscorefuncunderscored160;
    case 0x8e9a:
        goto underscorefuncunderscored292;
    case 0x8eaf:
        goto underscorefuncunderscored2a4;
    case 0x8efa:
        goto underscorefuncunderscored3d2;
    case 0x8f0c:
        goto underscorefuncunderscored3df;
    case 0x8f75:
        goto underscorefuncunderscored428;
    case 0x8fa5:
        goto underscorefuncunderscored446;
    case 0x8fcc:
        goto underscorefuncunderscored464;
    case 0x907a:
        goto underscorefuncunderscored4d9;
    case 0x9083:
        goto underscorefuncunderscored4e2;
    case 0x9089:
        goto underscorefuncunderscored4e6;
    case 0x90a7:
        goto underscorefuncunderscored4fa;
    case 0x90ad:
        goto underscorefuncunderscored4fe;
    case 0x90bf:
        goto underscorefuncunderscored509;
    case 0x90c5:
        goto underscorefuncunderscored50d;
    case 0x91c4:
        goto underscorefuncunderscored5ee;
    case 0x9248:
        goto underscorefuncunderscored652;
    case 0x929c:
        goto underscorefuncunderscoref35e;
    case 0x92a2:
        goto underscorefuncunderscoref362;
    case 0x92a8:
        goto underscorefuncunderscoref366;
    case 0x92ae:
        goto underscorefuncunderscoref36a;
    case 0x92d8:
        goto underscorefuncunderscoref383;
    case 0x933e:
        goto underscorefuncunderscoref3d0;
    case 0x944f:
        goto underscorefuncunderscoref544;
    case 0x947c:
        goto underscorefuncunderscoref564;
    case 0x9488:
        goto underscorefuncunderscoref56c;
    case 0x94a0:
        goto underscorefuncunderscoref581;
    case 0x94b8:
        goto underscorefuncunderscoref591;
    case 0x9581:
        goto underscorefuncunderscoref621;
    case 0x9686:
        goto underscorefuncunderscoref6cf;
    case 0x9767:
        goto underscorefuncunderscoref7cc;
    case 0x84a4:
        goto underscorejumpunderscoreengineunderscorec35e;
    case 0x8006:
        goto underscorelabelunderscorec002;
    case 0x802d:
        goto underscorelabelunderscorec01e;
    case 0x8045:
        goto underscorelabelunderscorec02c;
    case 0x8078:
        goto underscorelabelunderscorec056;
    case 0x8087:
        goto underscorelabelunderscorec061;
    case 0x8096:
        goto underscorelabelunderscorec06b;
    case 0x8099:
        goto underscorelabelunderscorec06e;
    case 0x80a8:
        goto underscorelabelunderscorec07c;
    case 0x80e4:
        goto underscorelabelunderscorec0a6;
    case 0x810b:
        goto underscorelabelunderscorec0ba;
    case 0x8141:
        goto underscorelabelunderscorec0df;
    case 0x8144:
        goto underscorelabelunderscorec0e1;
    case 0x816e:
        goto underscorelabelunderscorec0ff;
    case 0x8189:
        goto underscorelabelunderscorec112;
    case 0x8195:
        goto underscorelabelunderscorec11e;
    case 0x819b:
        goto underscorelabelunderscorec123;
    case 0x81a1:
        goto underscorelabelunderscorec14e;
    case 0x81d7:
        goto underscorelabelunderscorec176;
    case 0x81f2:
        goto underscorelabelunderscorec189;
    case 0x81f8:
        goto underscorelabelunderscorec18d;
    case 0x81fb:
        goto underscorelabelunderscorec190;
    case 0x8207:
        goto underscorelabelunderscorec199;
    case 0x8216:
        goto underscorelabelunderscorec1a3;
    case 0x821c:
        goto underscorelabelunderscorec1a9;
    case 0x8228:
        goto underscorelabelunderscorec1b2;
    case 0x822e:
        goto underscorelabelunderscorec1b7;
    case 0x8234:
        goto underscorelabelunderscorec1bb;
    case 0x8246:
        goto underscorelabelunderscorec1c8;
    case 0x827c:
        goto underscorelabelunderscorec1ea;
    case 0x82af:
        goto underscorelabelunderscorec20b;
    case 0x82be:
        goto underscorelabelunderscorec217;
    case 0x82cd:
        goto underscorelabelunderscorec222;
    case 0x82ee:
        goto underscorelabelunderscorec23f;
    case 0x8321:
        goto underscorelabelunderscorec25b;
    case 0x832a:
        goto underscorelabelunderscorec262;
    case 0x8342:
        goto underscorelabelunderscorec271;
    case 0x834b:
        goto underscorelabelunderscorec277;
    case 0x835d:
        goto underscorelabelunderscorec283;
    case 0x8375:
        goto underscorelabelunderscorec293;
    case 0x83ab:
        goto underscorelabelunderscorec2b6;
    case 0x83ae:
        goto underscorelabelunderscorec2b9;
    case 0x83b4:
        goto underscorelabelunderscorec2be;
    case 0x83de:
        goto underscorelabelunderscorec2db;
    case 0x83f6:
        goto underscorelabelunderscorec2ea;
    case 0x8408:
        goto underscorelabelunderscorec2f4;
    case 0x841a:
        goto underscorelabelunderscorec302;
    case 0x8432:
        goto underscorelabelunderscorec312;
    case 0x8450:
        goto underscorelabelunderscorec328;
    case 0x8474:
        goto underscorelabelunderscorec341;
    case 0x8492:
        goto underscorelabelunderscorec354;
    case 0x849b:
        goto underscorelabelunderscorec35a;
    case 0x84da:
        goto underscorelabelunderscorec37c;
    case 0x84fe:
        goto underscorelabelunderscorec392;
    case 0x8513:
        goto underscorelabelunderscorec39e;
    case 0x851c:
        goto underscorelabelunderscorec3a1;
    case 0x8522:
        goto underscorelabelunderscorec3a4;
    case 0x8564:
        goto underscorelabelunderscorec3ce;
    case 0x858b:
        goto underscorelabelunderscorec3e5;
    case 0x85a6:
        goto underscorelabelunderscorec3fc;
    case 0x85fd:
        goto underscorelabelunderscorec436;
    case 0x860f:
        goto underscorelabelunderscorec4ca;
    case 0x8624:
        goto underscorelabelunderscorec4d7;
    case 0x862d:
        goto underscorelabelunderscorec4db;
    case 0x8651:
        goto underscorelabelunderscorec4f3;
    case 0x8666:
        goto underscorelabelunderscorec4ff;
    case 0x86b1:
        goto underscorelabelunderscorec526;
    case 0x86bd:
        goto underscorelabelunderscorec52f;
    case 0x86ed:
        goto underscorelabelunderscorec555;
    case 0x86f6:
        goto underscorelabelunderscorec55a;
    case 0x8717:
        goto underscorelabelunderscorec56f;
    case 0x872f:
        goto underscorelabelunderscorec57b;
    case 0x8732:
        goto underscorelabelunderscorec57c;
    case 0x8738:
        goto underscorelabelunderscorec580;
    case 0x873e:
        goto underscorelabelunderscorec585;
    case 0x875f:
        goto underscorelabelunderscorec59a;
    case 0x8771:
        goto underscorelabelunderscorec5aa;
    case 0x87ad:
        goto underscorelabelunderscorec5dc;
    case 0x87b3:
        goto underscorelabelunderscorec5e0;
    case 0x87bf:
        goto underscorelabelunderscorec5e8;
    case 0x87da:
        goto underscorelabelunderscorec5fb;
    case 0x87f5:
        goto underscorelabelunderscorec60b;
    case 0x881f:
        goto underscorelabelunderscorec625;
    case 0x882b:
        goto underscorelabelunderscorec62d;
    case 0x882e:
        goto underscorelabelunderscorec637;
    case 0x8834:
        goto underscorelabelunderscorec63a;
    case 0x8846:
        goto underscorelabelunderscorec645;
    case 0x8858:
        goto underscorelabelunderscorec64f;
    case 0x8864:
        goto underscorelabelunderscorec67c;
    case 0x887f:
        goto underscorelabelunderscorec68e;
    case 0x8888:
        goto underscorelabelunderscorec694;
    case 0x888b:
        goto underscorelabelunderscorec695;
    case 0x889a:
        goto underscorelabelunderscorec69e;
    case 0x88f1:
        goto underscorelabelunderscorec6d6;
    case 0x88f7:
        goto underscorelabelunderscorec6da;
    case 0x8903:
        goto underscorelabelunderscorec6e2;
    case 0x8930:
        goto underscorelabelunderscorec701;
    case 0x893f:
        goto underscorelabelunderscorec70a;
    case 0x8942:
        goto underscorelabelunderscorec70c;
    case 0x896f:
        goto underscorelabelunderscorec72c;
    case 0x8981:
        goto underscorelabelunderscorec739;
    case 0x8984:
        goto underscorelabelunderscorec73a;
    case 0x8987:
        goto underscorelabelunderscorec73c;
    case 0x89a5:
        goto underscorelabelunderscorec74c;
    case 0x89c6:
        goto underscorelabelunderscorec762;
    case 0x89ea:
        goto underscorelabelunderscorec779;
    case 0x8a0e:
        goto underscorelabelunderscorec795;
    case 0x8a1d:
        goto underscorelabelunderscorec79f;
    case 0x8a20:
        goto underscorelabelunderscorec7a1;
    case 0x8a5f:
        goto underscorelabelunderscorec7ce;
    case 0x8a80:
        goto underscorelabelunderscorec7e1;
    case 0x8a92:
        goto underscorelabelunderscorec7ef;
    case 0x8a9b:
        goto underscorelabelunderscorec7f6;
    case 0x8ad1:
        goto underscorelabelunderscorec818;
    case 0x8ad7:
        goto underscorelabelunderscorec81c;
    case 0x8ada:
        goto underscorelabelunderscorec81d;
    case 0x8af8:
        goto underscorelabelunderscorec836;
    case 0x8afe:
        goto underscorelabelunderscorec839;
    case 0x8b1f:
        goto underscorelabelunderscorec854;
    case 0x8b46:
        goto underscorelabelunderscorec86e;
    case 0x8b85:
        goto underscorelabelunderscorec8a2;
    case 0x8b9a:
        goto underscorelabelunderscorec8b4;
    case 0x8bb2:
        goto underscorelabelunderscorec8c4;
    case 0x8be2:
        goto underscorelabelunderscorec8e5;
    case 0x8bfd:
        goto underscorelabelunderscorec8fb;
    case 0x8c06:
        goto underscorelabelunderscorec901;
    case 0x8c21:
        goto underscorelabelunderscorec91b;
    case 0x8c3f:
        goto underscorelabelunderscorec92f;
    case 0x8c63:
        goto underscorelabelunderscorecca8;
    case 0x8c96:
        goto underscorelabelunderscorecfd3;
    case 0x8cc3:
        goto underscorelabelunderscorecff8;
    case 0x8cd5:
        goto underscorelabelunderscored13c;
    case 0x8cdb:
        goto underscorelabelunderscored140;
    case 0x8cde:
        goto underscorelabelunderscored141;
    case 0x8cf9:
        goto underscorelabelunderscored153;
    case 0x8d14:
        goto underscorelabelunderscored164;
    case 0x8d1a:
        goto underscorelabelunderscored168;
    case 0x8d1d:
        goto underscorelabelunderscored169;
    case 0x8d65:
        goto underscorelabelunderscored19f;
    case 0x8d83:
        goto underscorelabelunderscored1b5;
    case 0x8d9b:
        goto underscorelabelunderscored1c7;
    case 0x8d9e:
        goto underscorelabelunderscored1ca;
    case 0x8da1:
        goto underscorelabelunderscored1cd;
    case 0x8db6:
        goto underscorelabelunderscored1dd;
    case 0x8dc2:
        goto underscorelabelunderscored1e6;
    case 0x8dd4:
        goto underscorelabelunderscored1f4;
    case 0x8def:
        goto underscorelabelunderscored207;
    case 0x8e10:
        goto underscorelabelunderscored222;
    case 0x8e2b:
        goto underscorelabelunderscored235;
    case 0x8e40:
        goto underscorelabelunderscored246;
    case 0x8e55:
        goto underscorelabelunderscored256;
    case 0x8e58:
        goto underscorelabelunderscored259;
    case 0x8e5e:
        goto underscorelabelunderscored25e;
    case 0x8e61:
        goto underscorelabelunderscored266;
    case 0x8e64:
        goto underscorelabelunderscored268;
    case 0x8e67:
        goto underscorelabelunderscored26a;
    case 0x8e6d:
        goto underscorelabelunderscored270;
    case 0x8e8e:
        goto underscorelabelunderscored28a;
    case 0x8eb2:
        goto underscorelabelunderscored2a6;
    case 0x8ec1:
        goto underscorelabelunderscored2b1;
    case 0x8ee5:
        goto underscorelabelunderscored2c9;
    case 0x8f30:
        goto underscorelabelunderscored3fb;
    case 0x8f45:
        goto underscorelabelunderscored409;
    case 0x8f48:
        goto underscorelabelunderscored40b;
    case 0x8f57:
        goto underscorelabelunderscored413;
    case 0x8f72:
        goto underscorelabelunderscored427;
    case 0x8fae:
        goto underscorelabelunderscored44c;
    case 0x8fc6:
        goto underscorelabelunderscored461;
    case 0x8fd8:
        goto underscorelabelunderscored46c;
    case 0x8fff:
        goto underscorelabelunderscored485;
    case 0x902f:
        goto underscorelabelunderscored4a1;
    case 0x903b:
        goto underscorelabelunderscored4ab;
    case 0x9050:
        goto underscorelabelunderscored4bc;
    case 0x9056:
        goto underscorelabelunderscored4c0;
    case 0x906b:
        goto underscorelabelunderscored4cf;
    case 0x9074:
        goto underscorelabelunderscored4d4;
    case 0x90b0:
        goto underscorelabelunderscored500;
    case 0x90b9:
        goto underscorelabelunderscored505;
    case 0x90d1:
        goto underscorelabelunderscored515;
    case 0x90e3:
        goto underscorelabelunderscored521;
    case 0x90e6:
        goto underscorelabelunderscored523;
    case 0x90ef:
        goto underscorelabelunderscored54b;
    case 0x9116:
        goto underscorelabelunderscored56a;
    case 0x9149:
        goto underscorelabelunderscored593;
    case 0x916a:
        goto underscorelabelunderscored5ad;
    case 0x91a0:
        goto underscorelabelunderscored5d2;
    case 0x91d9:
        goto underscorelabelunderscored600;
    case 0x91ee:
        goto underscorelabelunderscored612;
    case 0x9209:
        goto underscorelabelunderscored627;
    case 0x922d:
        goto underscorelabelunderscored640;
    case 0x9236:
        goto underscorelabelunderscored646;
    case 0x923c:
        goto underscorelabelunderscored64b;
    case 0x9245:
        goto underscorelabelunderscored651;
    case 0x926c:
        goto underscorelabelunderscored66b;
    case 0x92b1:
        goto underscorelabelunderscoref36c;
    case 0x92c3:
        goto underscorelabelunderscoref378;
    case 0x9353:
        goto underscorelabelunderscoref40f;
    case 0x937d:
        goto underscorelabelunderscoref443;
    case 0x9383:
        goto underscorelabelunderscoref451;
    case 0x93aa:
        goto underscorelabelunderscoref46c;
    case 0x93b6:
        goto underscorelabelunderscoref475;
    case 0x93b9:
        goto underscorelabelunderscoref477;
    case 0x93c2:
        goto underscorelabelunderscoref47e;
    case 0x93e9:
        goto underscorelabelunderscoref4d1;
    case 0x9410:
        goto underscorelabelunderscoref501;
    case 0x9413:
        goto underscorelabelunderscoref51c;
    case 0x9428:
        goto underscorelabelunderscoref52a;
    case 0x943a:
        goto underscorelabelunderscoref536;
    case 0x944c:
        goto underscorelabelunderscoref541;
    case 0x9464:
        goto underscorelabelunderscoref552;
    case 0x9479:
        goto underscorelabelunderscoref563;
    case 0x94ac:
        goto underscorelabelunderscoref58a;
    case 0x94ca:
        goto underscorelabelunderscoref59a;
    case 0x94d6:
        goto underscorelabelunderscoref5a2;
    case 0x94df:
        goto underscorelabelunderscoref5a8;
    case 0x94f1:
        goto underscorelabelunderscoref5bf;
    case 0x9518:
        goto underscorelabelunderscoref5da;
    case 0x951b:
        goto underscorelabelunderscoref5db;
    case 0x954b:
        goto underscorelabelunderscoref5fb;
    case 0x95b1:
        goto underscorelabelunderscoref639;
    case 0x95bd:
        goto underscorelabelunderscoref641;
    case 0x95d8:
        goto underscorelabelunderscoref654;
    case 0x95db:
        goto underscorelabelunderscoref655;
    case 0x95f9:
        goto underscorelabelunderscoref669;
    case 0x960b:
        goto underscorelabelunderscoref675;
    case 0x9626:
        goto underscorelabelunderscoref688;
    case 0x962c:
        goto underscorelabelunderscoref68c;
    case 0x9647:
        goto underscorelabelunderscoref6a2;
    case 0x965f:
        goto underscorelabelunderscoref6b3;
    case 0x9662:
        goto underscorelabelunderscoref6b4;
    case 0x96b9:
        goto underscorelabelunderscoref6e8;
    case 0x96d7:
        goto underscorelabelunderscoref6fe;
    case 0x96da:
        goto underscorelabelunderscoref703;
    case 0x9716:
        goto underscorelabelunderscoref730;
    case 0x971f:
        goto underscorelabelunderscoref791;
    case 0x972e:
        goto underscorelabelunderscoref79c;
    case 0x9734:
        goto underscorelabelunderscoref7a8;
    case 0x974c:
        goto underscorelabelunderscoref7ba;
    case 0x9755:
        goto underscorelabelunderscoref7c0;
    case 0x975e:
        goto underscorelabelunderscoref7c6;
    case 0x97c1:
        goto underscorelabelunderscoref7fa;
    case 0x97c4:
        goto underscorelabelunderscoref7fd;
    case 0x97cd:
        goto underscorelabelunderscoref803;
    case 0x97d6:
        goto underscorelabelunderscoref809;
    case 0x97df:
        goto underscorelabelunderscoref80f;
    case 0x97e8:
        goto underscorelabelunderscoref815;
    case 0x97f1:
        goto underscorelabelunderscoref81b;
    case 0x9800:
        goto underscorelabelunderscoref826;
    case 0x980c:
        goto underscorelabelunderscoref82f;
    case 0x9815:
        goto underscorelabelunderscoref836;
    case 0x9821:
        goto underscorelabelunderscoref840;
    default:
        // Unknown address - could be data or invalid
        return; // or handle error
    }

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
    case 145:
        goto Return_145;
    case 146:
        goto Return_146;
    case 147:
        goto Return_147;
    case 148:
        goto Return_148;
    case 149:
        goto Return_149;
    case 150:
        goto Return_150;
    case 151:
        goto Return_151;
    case 152:
        goto Return_152;
    case 153:
        goto Return_153;
    case 154:
        goto Return_154;
    case 155:
        goto Return_155;
    case 156:
        goto Return_156;
    case 157:
        goto Return_157;
    case 158:
        goto Return_158;
    }
}
