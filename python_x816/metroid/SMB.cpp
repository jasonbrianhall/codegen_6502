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


MainLoop:
    pushReturnIndex(0);
    goto CheckSwitch;
Return_0:
    pushReturnIndex(1);
    goto UpdateTimer;
Return_1:
    pushReturnIndex(2);
    goto GoMainRoutine;
Return_2:
    ++M(FrameCount);
    a = 0x00;
    writeData(NMIStatus, a);

LC155:
    ++M(MainRoutine);
    goto Return;

//------------------------------------------------------------------------

Exit1:
    goto Return;

//------------------------------------------------------------------------

ReadJoyPads:
    x = 0x00;
    writeData(0x01, x);
    pushReturnIndex(3);
    goto ReadOnePad;
Return_3:
    ++x;
    ++M(0x01);

UpdateTimer:
    x = 0x01;
    --M(TimerDelay);
    if (!n)
        goto DecTimer;
    a = 0x09;
    writeData(TimerDelay, a);
    x = 0x02;

GoRoutine:
    M(a) <<= 1; //  * 2, each ptr is 2 bytes (16-bit)
    writeData(TempY, y); //  temp storage
    writeData(TempX, x); //  temp storage
    y = a;
    ++y;
    pla(); //  lo byte of ptr table address
    writeData(CodePtr, a);
    pla(); //  hi byte of ptr table address
    writeData(CodePtr + 1, a);
    a = M(W(CodePtr) + y); //  lo byte of code ptr
    x = a;
    ++y;
    a = M(W(CodePtr) + y); //  hi byte of code ptr
    writeData(CodePtr + 1, a);
    writeData(CodePtr, x);
    x = M(TempX); //  restore X
    y = M(TempY); //  restore Y
    /* jmp (complex) */

WriteScroll:
    a = M(PPUStatus); //  reset scroll register flip/flop
    a = M(ScrollX);
    writeData(PPUScroll, a);
    a = M(ScrollY);
    writeData(PPUScroll, a);
    goto Return;

//------------------------------------------------------------------------

Adiv32:
    M(a) >>= 1;

Adiv16:
    M(a) >>= 1;

Adiv8:
    M(a) >>= 1;
    M(a) >>= 1;
    M(a) >>= 1;
    goto Return;

//------------------------------------------------------------------------

Amul32:
    M(a) <<= 1;

Amul16:
    M(a) <<= 1;

Amul8:
    M(a) <<= 1;
    M(a) <<= 1;
    M(a) <<= 1;
    goto Return;

//------------------------------------------------------------------------

PPUWrite:
    writeData(PPUAddress, a); //  set high PPU address
    ++y;
    a = M(W(0x00) + y);
    writeData(PPUAddress, a); //  set low PPU address
    ++y;
    a = M(W(0x00) + y); //  get data byte containing rep length & RLE status
    M(a) <<= 1; //  CF = PPU address increment (0 = 1, 1 = 32)
    pushReturnIndex(4);
    goto SetPPUInc;
Return_4: //  update PPUCtrl0 according to CF
    M(a) <<= 1; //  CF = bit 6 of byte at ($00),y (1 = RLE)
    a = M(W(0x00) + y); //  get data byte again
    a &= 0x3F; //  keep lower 6 bits as loop counter
    x = a;
    if (!c)
        goto PPUWriteLoop; //  if CF not set, the data is not RLE
    ++y; //  data is RLE, advance to data byte

ProcessPPUString:
    x = M(PPUStatus); //  reset PPU addr flip/flop
    y = 0x00;
    a = M(W(0x00) + y);
    if (!z)
        goto PPUWrite; //  if A is non-zero, PPU data string follows
    goto WriteScroll; //  otherwise we're done

WritePPUByte:
    writeData(PPUDataString + x, a);

EndPPUString:
    a = 0x00;
    writeData(PPUDataString + x, a);
    pla();
    pla();
    goto Return;

//------------------------------------------------------------------------

LC3C6:
    writeData(0x04, a);
    a &= 0xBF;
    writeData(PPUDataString + x, a);
    a &= 0x3F;
    writeData(0x05, a);
    goto NextPPUByte;

GetAbsolute:
    a ^= 0xFF;
    c = 0;
    a += 0x01;
    goto Return;

//------------------------------------------------------------------------

LC41D:
    pha();
    a &= 0x0F;
    writeData(0x01, a);
    pla();
    a &= 0xF0;
    writeData(0x02, a);
    a = M(0x03);
    a &= 0x0F;
    goto Return;

//------------------------------------------------------------------------

ClearNMIStat:
    a = 0x00;
    writeData(NMIStatus, a);
    goto Return;

//------------------------------------------------------------------------

WritePPUCtrl:
    a = M(PPUCNT0ZP);
    writeData(PPUControl0, a);
    a = M(PPUCNT1ZP);
    writeData(PPUControl1, a);
    a = M(0xFA);
    pushReturnIndex(5);
    goto LC4D9;
Return_5:

ExitSub:
    goto Return;

//------------------------------------------------------------------------

SetTimer:
    writeData(Timer + 2, a);
    writeData(NextRoutine, x);
    a = 0x09; //  WaitTimer
    if (!z)
        goto SetMainRoutine; //  branch always

LC4B2:
    ; // nop
    ; // nop
    a = 0x47;

LC4B6:
    M(a) >>= 1;
    M(a) >>= 1;
    M(a) >>= 1;
    a &= 0x01;
    writeData(0x00, a);
    a = M(0x25);
    a &= 0xFE;
    a |= M(0x00);
    writeData(0x25, a);
    writeData(MMC1Reg0, a);
    M(a) >>= 1;
    writeData(MMC1Reg0, a);
    M(a) >>= 1;
    writeData(MMC1Reg0, a);
    M(a) >>= 1;
    writeData(MMC1Reg0, a);
    M(a) >>= 1;
    writeData(MMC1Reg0, a);
    goto Return;

//------------------------------------------------------------------------

LC4D9:
    a = M(0xFA);
    goto LC4B6;

SwitchOK:
    a = 0x00;
    writeData(SwitchPending, a); //  reset (so that the bank switch won't be
    --y; //  Y now contains the bank to switch to
    writeData(CurrentBank, y);

ROMSwitch:
    a = y;
    writeData(0x00, a);
    a = M(0x28);
    a &= 0x18;
    a |= M(0x00);
    writeData(0x28, a);

GoBankInit:
    M(a) <<= 1;
    y = a;
    a = M(BankInitTable + y);
    writeData(0x0A, a);
    a = M(BankInitTable + 1 + y);
    writeData(0x0B, a);
    /* jmp (complex) */

InitBank2:
    a = modePlay;
    writeData(GameMode, a);
    pushReturnIndex(6);
    goto ScreenNmiOff;
Return_6:
    pushReturnIndex(7);
    goto InitNorfairGFX;
Return_7:
    goto NmiOn;

InitBank4:
    a = modePlay;
    writeData(GameMode, a);
    pushReturnIndex(8);
    goto ScreenNmiOff;
Return_8:
    pushReturnIndex(9);
    goto InitKraidGFX;
Return_9:
    goto NmiOn;

InitBank5:
    a = modePlay;
    writeData(GameMode, a);
    pushReturnIndex(10);
    goto ScreenNmiOff;
Return_10:
    pushReturnIndex(11);
    goto InitRidleyGFX;
Return_11:
    goto NmiOn;

LC5D0:
    a = modeTitle;
    writeData(GameMode, a);
    goto InitGFX6;

InitBrinstarGFX:
    y = 0x03;
    pushReturnIndex(12);
    goto LoadGFX;
Return_12:
    y = 0x04;
    pushReturnIndex(13);
    goto LoadGFX;
Return_13:
    y = 0x05;
    pushReturnIndex(14);
    goto LoadGFX;
Return_14:
    y = 0x06;
    pushReturnIndex(15);
    goto LoadGFX;
Return_15:
    y = 0x19;
    pushReturnIndex(16);
    goto LoadGFX;
Return_16:
    y = 0x16;
    goto LoadGFX;

InitNorfairGFX:
    y = 0x04;
    pushReturnIndex(17);
    goto LoadGFX;
Return_17:
    y = 0x05;
    pushReturnIndex(18);
    goto LoadGFX;
Return_18:
    y = 0x07;
    pushReturnIndex(19);
    goto LoadGFX;
Return_19:
    y = 0x08;
    pushReturnIndex(20);
    goto LoadGFX;
Return_20:
    y = 0x09;
    pushReturnIndex(21);
    goto LoadGFX;
Return_21:
    y = 0x19;
    pushReturnIndex(22);
    goto LoadGFX;
Return_22:
    y = 0x16;
    goto LoadGFX;

InitTourianGFX:
    y = 0x05;
    pushReturnIndex(23);
    goto LoadGFX;
Return_23:
    y = 0x0A;
    pushReturnIndex(24);
    goto LoadGFX;
Return_24:
    y = 0x0B;
    pushReturnIndex(25);
    goto LoadGFX;
Return_25:
    y = 0x0C;
    pushReturnIndex(26);
    goto LoadGFX;
Return_26:
    y = 0x0D;
    pushReturnIndex(27);
    goto LoadGFX;
Return_27:
    y = 0x0E;
    pushReturnIndex(28);
    goto LoadGFX;
Return_28:
    y = 0x1A;
    pushReturnIndex(29);
    goto LoadGFX;
Return_29:
    y = 0x1C;
    pushReturnIndex(30);
    goto LoadGFX;
Return_30:
    y = 0x19;
    pushReturnIndex(31);
    goto LoadGFX;
Return_31:
    y = 0x16;
    goto LoadGFX;

InitKraidGFX:
    y = 0x04;
    pushReturnIndex(32);
    goto LoadGFX;
Return_32:
    y = 0x05;
    pushReturnIndex(33);
    goto LoadGFX;
Return_33:
    y = 0x0A;
    pushReturnIndex(34);
    goto LoadGFX;
Return_34:
    y = 0x0F;
    pushReturnIndex(35);
    goto LoadGFX;
Return_35:
    y = 0x10;
    pushReturnIndex(36);
    goto LoadGFX;
Return_36:
    y = 0x11;
    pushReturnIndex(37);
    goto LoadGFX;
Return_37:
    y = 0x19;
    pushReturnIndex(38);
    goto LoadGFX;
Return_38:
    y = 0x16;
    goto LoadGFX;

InitRidleyGFX:
    y = 0x04;
    pushReturnIndex(39);
    goto LoadGFX;
Return_39:
    y = 0x05;
    pushReturnIndex(40);
    goto LoadGFX;
Return_40:
    y = 0x0A;
    pushReturnIndex(41);
    goto LoadGFX;
Return_41:
    y = 0x12;
    pushReturnIndex(42);
    goto LoadGFX;
Return_42:
    y = 0x13;
    pushReturnIndex(43);
    goto LoadGFX;
Return_43:
    y = 0x19;
    pushReturnIndex(44);
    goto LoadGFX;
Return_44:
    y = 0x16;
    goto LoadGFX;

InitGFX6:
    y = 0x01;
    pushReturnIndex(45);
    goto LoadGFX;
Return_45:
    y = 0x02;
    pushReturnIndex(46);
    goto LoadGFX;
Return_46:
    y = 0x19;
    pushReturnIndex(47);
    goto LoadGFX;
Return_47:
    y = 0x16;
    goto LoadGFX;

InitGFX7:
    y = 0x17;
    pushReturnIndex(48);
    goto LoadGFX;
Return_48:
    y = 0x16;
    goto LoadGFX;

CopyGFXBlock:
    a = M(0x05);
    if (!z)
        goto GFXCopyLoop;
    --M(0x06);

AreaInit:
    a = 0x00;
    writeData(ScrollX, a); //  Clear ScrollX
    writeData(ScrollY, a); //  Clear ScrollY
    a = M(PPUCNT0ZP);
    a &= 0xFC; //  nametable address = $2000
    writeData(PPUCNT0ZP, a);
    ++M(MainRoutine);
    a = M(JoyStatus);
    a &= 0xC0;
    writeData(0xF0, a); //  ???
    pushReturnIndex(49);
    goto EraseAllSprites;
Return_49:
    a = 0x10;
    pushReturnIndex(50);
    goto LCA18;
Return_50:

EndGame:
    a = 0x1C;
    writeData(TitleRoutine, a);
    a = 0x01;
    writeData(SwitchPending, a);
    goto ScreenOff;

PauseMode:
    a = M(JoyStatus + 1); //  joypad #2
    a &= 0x88;
    a ^= 0x88; //  both A & UP pressed? (zero result = yes)
    if (!z)
        goto Exit14; //  exit if not
    y = M(EndTimerHi);
    ++y;
    if (!z)
        goto Exit14; //  sorry, can't quit if this is during escape s=ence
    writeData(GamePaused, a);
    ++M(MainRoutine); //  password display

Exit14:
    goto Return;

//------------------------------------------------------------------------

GoPassword:
    a = 0x19;
    writeData(TitleRoutine, a);
    a = 0x01;
    writeData(SwitchPending, a);
    a = M(0x0680);
    a |= 0x01;
    writeData(0x0680, a);
    goto ScreenOff;

LCA96:
    a = M(0x6885);
    M(a) <<= 1;
    M(a) <<= 1;
    M(a) <<= 1;
    M(a) <<= 1;
    writeData(0x6875, a);
    goto Return;

//------------------------------------------------------------------------

LCB1C:
    pushReturnIndex(51);
    goto ScreenOff;
Return_51:
    a = 0xFF;
    writeData(0x00, a);
    pushReturnIndex(52);
    goto ClearNameTable;
Return_52:
    goto EraseAllSprites;

SilenceMusic:
    a = 0x01; //  ??? (silence)
    if (!z)
        goto SFX_SetX0;

PauseMusic:
    a = 0x02; //  ??? (silence)
    if (!z)
        goto SFX_SetX0;

SFX_SamusWalk:
    a = 0x08;
    if (!z)
        goto SFX_SetX0;

SFX_BombExplode:
    a = 0x10;
    if (!z)
        goto SFX_SetX0;

SFX_MissileLaunch:
    a = 0x20;

SFX_SetX0:
    x = 0x00;
    if (z)
        goto SFX_SetSoundFlag;

SFX_Zeb:
    a = 0x08;
    if (!z)
        goto SFX_SetX1;

SFX_BombLaunch:
    a = 0x01;
    if (!z)
        goto SFX_SetX3;

SFX_SamusJump:
    a = 0x02;
    if (!z)
        goto SFX_SetX1;

SFX_EnemyHit:
    a = 0x04;
    if (!z)
        goto SFX_SetX1;

SFX_BulletFire:
    a = 0x10;
    if (!z)
        goto SFX_SetX1;

SFX_Metal:
    a = 0x20;
    if (!z)
        goto SFX_SetX1;

SFX_EnergyPickup:
    a = 0x40;
    if (!z)
        goto SFX_SetX1;

SFX_MissilePickup:
    a = 0x80;

SFX_SetX1:
    x = 0x01;
    if (!z)
        goto SFX_SetSoundFlag;

SFX_WaveFire:
    a = 0x01;
    if (!z)
        goto SFX_SetX1;

SFX_ScrewAttack:
    a = 0x40;
    if (!z)
        goto SFX_SetX0;

LCBCE: //  ??? (silence)
    a = 0x04;
    if (!z)
        goto SFX_SetX3;

SFX_MetroidHit:
    a = 0x20;
    if (!z)
        goto SFX_SetX3;

SFX_MBrainHit:
    a = 0x02;
    if (!z)
        goto SFX_SetX4;

LCBDA: //  Door open/close
    a = 0x40;
    if (!z)
        goto SFX_SetX3;

SFX_SamusHit:
    a = 0x04;
    if (!z)
        goto SFX_SetX4;

SFX_SamusDie:
    a = 0x80;
    if (!z)
        goto SFX_SetX3;
    x = 0x02;

SFX_SetSoundFlag:
    a |= M(0x0680 + x);
    writeData(0x0680 + x, a);
    goto Return;

//------------------------------------------------------------------------

SFX_SamusBall:
    a = 0x02; //  Samus --> ball
    if (!z)
        goto SFX_SetX3;

SFX_Beep:
    a = 0x08;

SFX_SetX3:
    x = 0x03;
    if (!z)
        goto SFX_SetSoundFlag;

PowerUpMusic:
    a = 0x40; //  Take power-up
    if (!z)
        goto SFX_SetX4;

IntroMusic:
    a = 0x80; //  Game begin

SFX_SetX4:
    x = 0x04;
    if (!z)
        goto SFX_SetSoundFlag;

LCC01: //  ??? (silence)
    a = 0x02;
    if (!z)
        goto SFX_SetX5;

LCC07: //  Tourian music
    a = 0x40;

SFX_SetX5:
    x = 0x05;
    if (!z)
        goto SFX_SetSoundFlag;

UpdateSamus:
    x = 0x00;
    writeData(PageIndex, x);
    ++x;
    writeData(IsSamus, x); //  signal that Samus is the obj being updated
    pushReturnIndex(53);
    goto GoSamusHandler;
Return_53:
    --M(IsSamus);
    goto Return;

//------------------------------------------------------------------------

GoSamusHandler:
    a = M(ObjAction);
    if (n)
        goto SamusStand;
    pushReturnIndex(54);
    goto GoRoutine;
Return_54:

LCCB7:
    a = M(LCCC0 + x);
    writeData(0x0315, a);
    goto Return;

//------------------------------------------------------------------------

LCCBE:

LCCC0:

LCD6B:
    a = 0x03;

LCD92:
    a = M(SamusDir);
    pushReturnIndex(55);
    goto Amul16;
Return_55: //  * 16
    a |= M(0x6B);
    writeData(0x6B, a);
    goto Return;

//------------------------------------------------------------------------

Exit2:
    goto Return;

//------------------------------------------------------------------------

LCDBF:
    a = M(JoyStatus);
    a &= btn_UP;
    M(a) >>= 1;
    M(a) >>= 1;
    M(a) >>= 1;
    x = a;
    a = M(LCCBE + x);
    compare(a, M(AnimResetIndex));
    if (z)
        goto Exit2;
    pushReturnIndex(56);
    goto SetSamusAnim;
Return_56:
    pla();
    pla();
    goto LCD6B;

IsSamusDead:
    a = M(ObjAction);
    compare(a, sa_Dead);
    if (z)
        goto Exit3;
    compare(a, sa_Dead2);
    if (z)
        goto Exit3;
    compare(a, 0xFF); //  make sure zero flag is NOT set on exit

Exit3:
    goto Return;

//------------------------------------------------------------------------

LCF4C:
    y = 0x00;

LCF55:
    a = M(0x0315);
    if (!z)
        goto LCF5D;
    pushReturnIndex(57);
    goto SFX_SamusWalk;
Return_57:

LCF5D:
    pushReturnIndex(58);
    goto LCF81;
Return_58:
    writeData(ObjAction, y);
    a = M(JoyStatus);
    a &= btn_UP;
    if (!z)
        goto LCF77;
    a = an_SamusStand;

SetSamusAnim:
    writeData(AnimResetIndex, a);

SetSamusNextAnim:
    writeData(AnimIndex, a);
    a = 0x00;
    writeData(AnimDelay, a);
    goto Return;

//------------------------------------------------------------------------

LCF77:
    a = sa_PntUp;
    writeData(ObjAction, a);
    a = an_SamusPntUp;
    pushReturnIndex(59);
    goto SetSamusAnim;
Return_59:

LCF81:
    pushReturnIndex(60);
    goto LCFB7;
Return_60:
    writeData(AnimDelay, y);
    goto Return;

//------------------------------------------------------------------------

LCFBE:
    y = an_SamusJumpPntUp;
    /* jmp (complex) */

LD144:
    goto LCD6D;

LD147:
    y = 0x00;
    writeData(0x0308, y);
    writeData(0x0312, y);
    goto Return;

//------------------------------------------------------------------------

LD1EE:
    a = M(JoyStatus);
    a &= btn_UP;
    if (z)
        goto LD210;
    goto LD275;

LD26B:
    a = y;
    goto SetSamusNextAnim;

LD2EB:
    a = y;
    x = a;
    ++M(ObjAction + x);
    a = 0x02;
    writeData(ObjRadY + y, a);
    writeData(ObjRadX + y, a);
    a = an_Bullet;

SetProjectileAnim:
    writeData(AnimResetIndex + x, a);
    writeData(AnimIndex + x, a);
    a = 0x00;
    writeData(AnimDelay + x, a);
    goto Return;

//------------------------------------------------------------------------

LD306:
    x = 0x00;
    pushReturnIndex(61);
    goto LE8BE;
Return_61:
    a = y;
    x = a;
    pushReturnIndex(62);
    goto LFD8F;
Return_62:
    a = x;
    y = a;
    goto LD638;

CheckMissileLaunch:
    a = M(MissileToggle);
    if (z)
        goto Exit4; //  exit if Samus not in "missile fire" mode
    compare(y, 0xD0);
    if (!z)
        goto Exit4;
    x = M(SamusDir);
    a = M(MissileAnims + x);
    pushReturnIndex(63);
    goto SetBulletAnim;
Return_63:
    pushReturnIndex(64);
    goto SFX_MissileLaunch;
Return_64:
    a = wa_Missile; //  missile handler
    writeData(ObjAction + y, a);
    a = 0xFF;
    writeData(0x030F + y, a); //  # of frames projectile should last
    --M(MissileCount);
    if (!z)
        goto Exit4; //  exit if not the last missile
    --M(MissileToggle); //  put Samus in "regular fire" mode
    goto SelectSamusPal; //  update Samus' palette to reflect this

MissileAnims:

SetBulletAnim:
    writeData(AnimIndex + y, a);
    writeData(AnimResetIndex + y, a);
    a = 0x00;
    writeData(AnimDelay + y, a);

Exit4:
    goto Return;

//------------------------------------------------------------------------

LD38E:
    a = M(MissileToggle);
    if (!z)
        goto Exit4;
    a = M(SamusGear);
    if (!n)
        goto Exit4; //  branch if Samus doesn't have Ice Beam
    a = wa_IceBeam;
    writeData(ObjAction + y, a);
    a = M(0x061F);
    a |= 0x01;
    writeData(0x061F, a);
    goto SFX_BulletFire;

SamusDead:
    a = 0x01;
    goto LCD6D;

SamusDead2:
    --M(0x0304);
    goto Return;

//------------------------------------------------------------------------

UpdateProjectiles:
    x = 0xD0;
    pushReturnIndex(65);
    goto DoOneProjectile;
Return_65:
    x = 0xE0;
    pushReturnIndex(66);
    goto DoOneProjectile;
Return_66:
    x = 0xF0;

DoOneProjectile:
    writeData(PageIndex, x);
    a = M(ObjAction + x);
    pushReturnIndex(67);
    goto GoRoutine;
Return_67:

UpdateBullet:
    a = 0x01;
    writeData(0x71, a);
    pushReturnIndex(68);
    goto LD5FC;
Return_68:
    pushReturnIndex(69);
    goto LD5DA;
Return_69:
    pushReturnIndex(70);
    goto LD609;
Return_70:

DrawBullet:
    a = 0x01;
    pushReturnIndex(71);
    goto AnimDrawObject;
Return_71:
    --M(0x71);
    goto Return;

//------------------------------------------------------------------------
    ++M(0x0500 + x);

UpdateIceBullet:
    a = 0x81;
    writeData(0x6B, a);
    goto UpdateBullet;

LD5DA:
    a = M(0x030A + x);
    if (z)
        goto Exit5;
    a = 0x00;
    writeData(0x030A + x, a);

Exit5:
    goto Return;

//------------------------------------------------------------------------

LD65E:
    a = an_BombTick;
    pushReturnIndex(72);
    goto SetProjectileAnim;
Return_72:
    a = 0x18; //  fuse length :-)
    writeData(0x030F + x, a);
    ++M(ObjAction + x); //  bomb update handler

DrawBomb:
    a = 0x03;
    goto AnimDrawObject;

Exit7:
    goto Return;

//------------------------------------------------------------------------

LD77F:
    c = 0;
    a += M(0x0A);
    writeData(0x04, a);
    a = M(0x0B);
    a += 0x00;
    goto LD798;

LD78B:
    writeData(0x00, a);
    a = M(0x0A);
    c = 1;
    a -= M(0x00);
    writeData(0x04, a);
    a = M(0x0B);
    a -= 0x00;

GetObjCoords:
    x = M(PageIndex);
    a = M(ObjectY + x);
    writeData(0x02, a);
    a = M(ObjectX + x);
    writeData(0x03, a);
    a = M(ObjectHi + x);
    writeData(0x0B, a);
    goto MakeWRAMPtr;

UpdateElevator:
    x = 0x20;
    writeData(PageIndex, x);
    a = M(ObjAction + x);
    pushReturnIndex(73);
    goto GoRoutine;
Return_73:

ElevatorScroll:
    a = M(ScrollY);
    if (!z)
        goto ElevScrollRoom; //  scroll until ScrollY = 0
    a = 0x4E;
    writeData(AnimResetIndex, a);
    a = 0x41;
    writeData(AnimIndex, a);
    a = 0x5D;
    writeData(AnimResetIndex + x, a);
    a = 0x50;
    writeData(AnimIndex + x, a);
    ++M(ObjAction + x);
    a = 0x40;
    writeData(Timer, a);
    goto ShowElevator;

Exit8:
    goto Return;

//------------------------------------------------------------------------

LDA39:

LDA3B:

LDAB0:
    a = M(Table0E + y);
    writeData(0x05C8, a);
    a = M(0x036C);
    M(a) <<= 1;
    M(a) <<= 1;
    a |= M(Table1B + y);
    writeData(0x05C9, a);
    a = 0x09;
    writeData(0x05C3, a);
    a = 0xC0;
    writeData(PageIndex, a);
    pushReturnIndex(74);
    goto DrawTileBlast;
Return_74:
    a = 0x60;
    writeData(PageIndex, a);
    goto Return;

//------------------------------------------------------------------------

Exit0:
    goto Return;

//------------------------------------------------------------------------

CheckMissileToggle:
    a = M(MissileCount);
    if (z)
        goto Exit0; //  exit if Samus has no missiles
    a = M(JoyFirst);
    a |= M(JoyRetrig);
    a &= btn_SELECT;
    if (z)
        goto Exit0; //  exit if SELECT not pressed
    a = M(MissileToggle);
    a ^= 0x01; //  0 = fire bullets, 1 = fire missiles
    writeData(MissileToggle, a);
    goto SelectSamusPal;

UpdateItems:
    a = 0x40;
    writeData(PageIndex, a);
    x = 0x00;
    pushReturnIndex(75);
    goto LDB42;
Return_75:
    x = 0x08;

LDC51:
    pushReturnIndex(76);
    goto LDC67;
Return_76:

LDC54:
    y = M(0x6886);
    a = M(0x06);
    writeData(0x6887 + y, a);
    a = M(0x07);
    writeData(0x6888 + y, a);
    ++y;
    ++y;
    writeData(0x6886, y);
    goto Return;

//------------------------------------------------------------------------

LDC67:
    a = M(0x07);
    pushReturnIndex(77);
    goto Amul32;
Return_77: //  * 32
    a |= M(0x06);
    writeData(0x06, a);
    M(0x07) >>= 1;
    M(0x07) >>= 1;
    M(0x07) >>= 1;
    a = M(0x09);
    M(a) <<= 1;
    M(a) <<= 1;
    a |= M(0x07);
    writeData(0x07, a);
    goto Return;

//------------------------------------------------------------------------

LDC7F:
    pushReturnIndex(78);
    goto LF186;
Return_78:

LDC82:
    pushReturnIndex(79);
    goto LF172;
Return_79:
    pushReturnIndex(80);
    goto LF1A7;
Return_80:
    goto LF1FA;

LDCF5:
    pushReturnIndex(81);
    goto LDF2D;
Return_81:
    pla();
    pla();
    x = M(PageIndex);

LDD75:
    pushReturnIndex(82);
    goto PowerUpMusic;
Return_82:
    a = M(0x74);
    a &= 0x0F;
    writeData(0x0108, a);
    M(a) >>= 1;
    y = a;
    writeData(MaxMissiles + y, a);
    a = 75;
    pushReturnIndex(83);
    goto AddToMaxMissiles;
Return_83:
    if (!z)
        goto LDD5B;

AnimDrawObject:
    pushReturnIndex(84);
    goto UpdateObjAnim;
Return_84:

LDF19: //  get frame data pos
    y = M(0x11);

LE038:
    M(0x6B) >>= 1;
    a = M(W(0x00) + y);
    a &= 0xC0;
    a |= M(0x6B);
    writeData(0x05, a);
    a = M(0x6B);
    a |= 0x80;
    writeData(0x6B, a);
    goto Return;

//------------------------------------------------------------------------

SPRWriteDigit:
    a |= 0xA0;
    writeData(SpriteRAM + 1 + x, a);
    goto Xplus4;

AddOneTank:
    a = 0x17; //  Y coord - 1
    writeData(SpriteRAM + x, a);
    a = y; //  tile value
    writeData(SpriteRAM + 1 + x, a);
    a = 0x01; //  palette #
    writeData(SpriteRAM + 2 + x, a);
    a = M(0x00); //  X coord
    writeData(SpriteRAM + 3 + x, a);
    c = 1;
    a -= 0x0A;
    writeData(0x00, a); //  X coord of next energy tank

Xplus4:
    ++x;
    ++x;
    ++x;
    ++x;
    goto Return;

//------------------------------------------------------------------------

HexToDec:
    y = 100;
    writeData(0x0A, y);
    pushReturnIndex(85);
    goto GetDigit;
Return_85:
    writeData(0x02, y);
    y = 10;
    writeData(0x0A, y);
    pushReturnIndex(86);
    goto GetDigit;
Return_86:
    writeData(0x01, y);
    writeData(0x00, a);
    goto Return;

//------------------------------------------------------------------------

Exit15:
    goto Return;

//------------------------------------------------------------------------

ToggleSamusHi:
    a = M(ObjectHi);
    a ^= 0x01;
    writeData(ObjectHi, a);
    goto Return;

//------------------------------------------------------------------------

ToggleScroll:
    a = M(ScrollDir);
    a ^= 0x03;
    writeData(ScrollDir, a);
    a = M(0xFA);
    a ^= 0x08;
    goto Return;

//------------------------------------------------------------------------

LE25D:
    a = 0x01;
    compare(a, M(ScrollDir));
    if (c)
        goto Exit21;
    a = 0xD8;
    compare(a, M(ObjectY));

Exit21:
    goto Return;

//------------------------------------------------------------------------

Exit10:
    goto Return;

//------------------------------------------------------------------------

LE365:
    if (c)
        goto Exit10;
    a = 0x01;
    writeData(0x65, a);
    a = M(0x0314);
    if (!z)
        goto Exit10;
    a = M(ObjAction);
    compare(a, sa_Roll);
    if (z)
        goto Exit10;
    goto LCF55;

LE449:
    a = 0x00;
    c = 1;
    a -= M(0x00);
    writeData(0x00, a);
    a = 0x00;
    a -= M(0x01);
    writeData(0x01, a);
    goto Return;

//------------------------------------------------------------------------

GetNameAddrs:
    pushReturnIndex(87);
    goto LEB85;
Return_87:
    a &= 0x01; //  A = nametable to update
    y = a;
    a = M(PPUAddrs + y); //  get high PPU addr of nametable (dest)
    x = M(WRAMAddrs + y); //  get high WRAM addr of nametable (src)
    goto Return;

//------------------------------------------------------------------------

LE770:
    x = M(PageIndex);
    a = M(0x6AF5 + x);
    c = 0;
    a += 0x08;
    goto LE783;

LE77B:
    x = M(PageIndex);
    a = 0x00;
    c = 1;
    a -= M(0x6AF5 + x);

LE783:
    writeData(0x02, a);
    a = 0x08;
    writeData(0x04, a);
    pushReturnIndex(88);
    goto LE792;
Return_88:
    a = M(0x6AF6 + x);
    goto LE7BD;

LE792:
    a = M(0x0401 + x);
    writeData(0x09, a); //  X coord
    a = M(0x0400 + x);
    writeData(0x08, a); //  Y coord
    a = M(0x6AFB + x);
    writeData(0x0B, a); //  hi coord
    goto Return;

//------------------------------------------------------------------------

CheckMoveUp:
    x = M(PageIndex);
    a = M(ObjRadY + x);
    c = 0;
    a += 0x08;
    /* jmp (complex) */

CheckMoveDown:
    x = M(PageIndex);
    a = 0x00;
    c = 1;
    a -= M(ObjRadY + x);
    writeData(0x02, a);
    pushReturnIndex(89);
    goto LE8BE;
Return_89:
    a = M(ObjRadX + x);

Exit16:
    goto Return;

//------------------------------------------------------------------------

ClcExit:
    c = 0;
    goto Return;

//------------------------------------------------------------------------

PlaySnd4:
    goto SFX_Metal;

CheckMoveLeft:
    x = M(PageIndex);
    a = M(ObjRadX + x);
    c = 0;
    a += 0x08;
    /* jmp (complex) */

CheckMoveRight:
    x = M(PageIndex);
    a = 0x00;
    c = 1;
    a -= M(ObjRadX + x);
    writeData(0x03, a);
    pushReturnIndex(90);
    goto LE8BE;
Return_90:
    y = M(ObjRadY + x);

LE8BE:
    a = M(ObjectHi + x);
    writeData(0x0B, a);
    a = M(ObjectY + x);
    writeData(0x08, a);
    a = M(ObjectX + x);
    writeData(0x09, a);
    goto Return;

//------------------------------------------------------------------------

LE8F1:
    x = M(PageIndex);
    a = M(0x6AF6 + x);
    c = 0;
    a += 0x08;
    goto LE904;

LE8FC:
    x = M(PageIndex);
    a = 0x00;
    c = 1;
    a -= M(0x6AF6 + x);

LE904:
    writeData(0x03, a);
    pushReturnIndex(91);
    goto LE792;
Return_91:
    y = M(0x6AF5 + x);
    goto LE89B;

LE95F:
    a = M(0x08);
    c = 1;
    a -= M(0x02);
    x = a;
    a &= 0x07;
    writeData(0x00, a);
    goto Return;

//------------------------------------------------------------------------

MakeWRAMPtr:
    a = 0x18;
    writeData(0x05, a);
    a = M(0x02); //  ObjectY
    a &= 0xF8; //  keep upper 5 bits
    M(a) <<= 1;
    M(0x05).rol();
    M(a) <<= 1;
    M(0x05).rol();
    writeData(0x04, a);
    a = M(0x03); //  ObjectX
    M(a) >>= 1;
    M(a) >>= 1;
    M(a) >>= 1; //  A = ObjectX / 8
    a |= M(0x04);
    writeData(0x04, a);
    a = M(0x0B); //  ObjectYHi
    M(a) <<= 1;
    M(a) <<= 1; //  A = ObjectYHi * 4
    a &= 0x04;
    a |= M(0x05);
    writeData(0x05, a);
    goto Return;

//------------------------------------------------------------------------

LE9B7:
    a = M(PPUCNT0ZP);
    a ^= 0x03;
    writeData(PPUCNT0ZP, a);
    goto Return;

//------------------------------------------------------------------------

IsBlastTile:
    y = M(0x71);
    if (z)
        goto Exit18;

Exit18:
    goto Return;

//------------------------------------------------------------------------

LEA05:
    pushReturnIndex(92);
    goto LEB85;
Return_92:
    M(a) <<= 1;
    M(a) <<= 1;
    a |= 0x60;
    writeData(WRAMPtr + 1, a);
    a = 0x00;
    writeData(WRAMPtr, a);
    goto Return;

//------------------------------------------------------------------------
    a = M(RoomNumber);
    a &= 0x0F;
    ++M(RoomNumber);
    pushReturnIndex(93);
    goto GoRoutine;
Return_93:

EndOfObjs:
    a = M(RoomPtr);
    writeData(0x00, a);
    a = M(RoomPtr + 1);
    writeData(0x01, a);
    a = 0x01;

EnemyLoop:
    pushReturnIndex(94);
    goto AddToPtr00;
Return_94: //  add A to pointer at $00
    y = 0x00;
    a = M(W(0x00) + y);
    compare(a, 0xFF); //  end of enemy/door data?
    if (z)
        goto EndOfRoom; //  if so, branch
    a &= 0x0F;
    pushReturnIndex(95);
    goto GoRoutine;
Return_95:

LoadEnemy:
    pushReturnIndex(96);
    goto LEB0C;
Return_96:
    goto EnemyLoop; //  do next room object

LEB4D:
    y = a;
    a &= 0xF0;
    a |= 0x08;
    writeData(0x0400 + x, a);
    a = y;
    pushReturnIndex(97);
    goto Amul16;
Return_97: //  * 16
    a |= 0x0C;
    writeData(0x0401 + x, a);
    a = 0x01;
    writeData(0x6AF4 + x, a);
    a = 0x00;
    writeData(0x0404 + x, a);
    pushReturnIndex(98);
    goto LEB85;
Return_98:
    writeData(0x6AFB + x, a);
    y = M(0x6B02 + x);
    M(0x0405 + x) <<= 1;
    pushReturnIndex(99);
    goto LFB7B;
Return_99:
    goto LF85A;

LEB85:
    a = M(PPUCNT0ZP);
    a ^= M(ScrollDir);
    a &= 0x01;
    goto Return;

//------------------------------------------------------------------------

LoadDoor:
    pushReturnIndex(100);
    goto LEB92;
Return_100:
    goto EnemyLoop; //  do next room object

LEBFE:

LEC93:
    a = M(PPUCNT0ZP);
    a ^= 0x01;
    a &= 0x01;
    y = a;
    goto Return;

//------------------------------------------------------------------------

LED51:
    a = x;
    a ^= 0x03;
    a &= M(0x006C + y);
    writeData(0x006C + y, a);
    goto Return;

//------------------------------------------------------------------------

LED8C:
    a = y;
    compare(a, M(0x074B + x));
    if (!z)
        goto Exit11;
    a = 0xFF;
    writeData(0x0748 + x, a);

Exit11:
    goto Return;

//------------------------------------------------------------------------

ScanForItems:
    a = M(0x9598); //  lo byte of ptr to 1st item data
    writeData(0x00, a);
    a = M(0x9599); //  hi byte of ptr to 1st item data

LEDD6: //  add A to pointer at $0000
    pushReturnIndex(101);
    goto AddToPtr00;
Return_101:
    y = 0x00;
    a = M(W(0x00) + y); //  object type
    a &= 0x0F;
    pushReturnIndex(102);
    goto GoRoutine;
Return_102: //  GO!

LEDF8:
    pushReturnIndex(103);
    goto LEB0C;
Return_103:
    goto LEDD6;

LEE3D:
    writeData(0x09, a);
    a = M(MapPosX);

LEE41:
    writeData(0x07, a);
    a = M(MapPosY);
    writeData(0x06, a);
    goto LDC67;

LEEF4:
    pushReturnIndex(104);
    goto LEB92;
Return_104:
    goto LEDD6;

LEEFA:
    a = M(ScrollDir);
    writeData(0x91, a);
    if (!z)
        goto LEEC6;

GetItemByte:
    a = M(W(0x00) + y);
    compare(a, 0xFF); //  end of data reached?
    if (!z)
        goto AddToPtr00; //  if not, A is amount to add to ptr
    pla();
    pla();
    goto Return;

//------------------------------------------------------------------------

LF140:
    pushReturnIndex(105);
    goto LF1BF;
Return_105:
    pushReturnIndex(106);
    goto LF186;
Return_106:
    goto LF1FA;

LF149:
    pushReturnIndex(107);
    goto LF186;
Return_107:
    pushReturnIndex(108);
    goto LF1D2;
Return_108:
    goto LF1FA;

LF152:
    a = M(0x0400 + x);
    writeData(0x07, a); //  Y coord
    a = M(0x0401 + x);
    writeData(0x09, a); //  X coord
    a = M(0x6AFB + x); //  hi coord
    goto LF17F;

LF162: //  Y coord
    a = M(0x0400 + y);
    writeData(0x06, a);
    a = M(0x0401 + y); //  X coord
    writeData(0x08, a);
    a = M(0x6AFB + y); //  hi coord
    goto LF193;

LF172:
    a = M(ObjectY + x);
    writeData(0x07, a);
    a = M(ObjectX + x);
    writeData(0x09, a);
    a = M(ObjectHi + x);

LF17F:
    a ^= M(PPUCNT0ZP);
    a &= 0x01;
    writeData(0x0B, a);
    goto Return;

//------------------------------------------------------------------------

LF186:
    a = M(ObjectY + y);
    writeData(0x06, a);
    a = M(ObjectX + y);
    writeData(0x08, a);
    a = M(ObjectHi + y);

LF193:
    a ^= M(PPUCNT0ZP);
    a &= 0x01;
    writeData(0x0A, a);
    goto Return;

//------------------------------------------------------------------------

LF19A:
    a = M(0xB1 + x);
    writeData(0x07, a);
    a = M(0xB2 + x);
    writeData(0x09, a);
    a = M(0xB3 + x);
    goto LF17F;

LF1A7:
    a = M(ObjRadY + x);
    pushReturnIndex(109);
    goto LF1E0;
Return_109:
    a = M(ObjRadX + x);
    goto LF1D9;

LF1B3:
    a = M(ObjRadY + x);
    pushReturnIndex(110);
    goto LF1E7;
Return_110:
    a = M(ObjRadX + x);
    goto LF1CB;

LF1BF:
    a = M(0x6AF5 + x);
    pushReturnIndex(111);
    goto LF1E0;
Return_111:
    a = M(0x6AF6 + x);
    goto LF1D9;

LF1CB:
    c = 0;
    a += M(0x6AF6 + y);
    writeData(0x05, a);
    goto Return;

//------------------------------------------------------------------------

LF1D2:
    a = 0x04;
    pushReturnIndex(112);
    goto LF1E0;
Return_112:
    a = 0x08;

LF1D9:
    c = 0;
    a += M(ObjRadX + y);
    writeData(0x05, a);
    goto Return;

//------------------------------------------------------------------------

LF1E0:
    c = 0;
    a += M(ObjRadY + y);
    writeData(0x04, a);
    goto Return;

//------------------------------------------------------------------------

LF1E7:
    c = 0;
    a += M(0x6AF5 + y);
    writeData(0x04, a);
    goto Return;

//------------------------------------------------------------------------

Yplus16:
    a = y;
    c = 0;
    a += 0x10;
    y = a;
    goto Return;

//------------------------------------------------------------------------

Xminus16:
    a = x;
    c = 1;
    a -= 0x10;
    x = a;
    goto Return;

//------------------------------------------------------------------------

LF262:
    a = M(0x0B);
    a -= M(0x0A);

LF270:
    a |= M(0x030A + x);
    writeData(0x030A + x, a);
    goto Return;

//------------------------------------------------------------------------

LF277:
    if (c)
        goto Exit17;

LF279:
    a = M(0x10);

LF27B:
    a |= M(0x030A + y);
    writeData(0x030A + y, a);

Exit17:
    goto Return;

//------------------------------------------------------------------------

LF2BF:
    a = M(0xB6 + x);
    a &= 0xF8;
    a |= M(0x10);
    a ^= 0x03;
    writeData(0xB6 + x, a);
    goto Return;

//------------------------------------------------------------------------

LF2DF:
    a = M(0x10);
    a |= M(0x0404 + y);
    writeData(0x0404 + y, a);
    goto Return;

//------------------------------------------------------------------------

LF323:
    a = 0x00;
    writeData(0x6E, a);
    writeData(0x6F, a);

Exit22:
    goto Return;

//------------------------------------------------------------------------

LF32A:
    if (c)
        goto Exit22;
    pushReturnIndex(113);
    goto LF279;
Return_113:
    goto LF2BF;

LF332:
    pushReturnIndex(114);
    goto LF340;
Return_114:
    goto Amul8; //  * 8

LF338:
    a = M(0x10);
    M(a) <<= 1;
    M(a) <<= 1;
    M(a) <<= 1;
    goto LF27B;

LF340:
    a = M(0x10);
    a ^= 0x03;
    goto Return;

//------------------------------------------------------------------------

LF3AA:
    a = M(0x0405 + x);
    M(a) <<= 1;
    M(a).rol();
    y = a;
    a = x;
    pushReturnIndex(115);
    goto Adiv16;
Return_115: //  / 16
    a ^= M(FrameCount);
    M(a) >>= 1;
    a = y;
    M(a).ror();
    M(a).ror();
    writeData(0x0405 + x, a);
    goto Return;

//------------------------------------------------------------------------

LF42D:
    x = M(PageIndex);
    a = 0x00;
    writeData(0x0404 + x, a);
    writeData(0x040E + x, a);
    goto Return;

//------------------------------------------------------------------------

LF438:
    pushReturnIndex(116);
    goto UpdateEnemyAnim;
Return_116:

LF43B:
    goto LF416;

LF515:
    writeData(0x040C + x, a);

LF518:
    a = 0x04;
    writeData(0x6AF4 + x, a);
    goto Return;

//------------------------------------------------------------------------

GetPageIndex:
    x = M(PageIndex);
    goto Return;

//------------------------------------------------------------------------

LF68D:
    writeData(0x6AF9 + x, a);

LF690:
    writeData(0x6AFA + x, a);

LF693:
    a = 0x00;
    writeData(0x6AF8 + x, a);
    goto Return;

//------------------------------------------------------------------------

Exit12:
    goto Return;

//------------------------------------------------------------------------

LF744:
    a |= M(0x0405 + x);
    writeData(0x0405 + x, a);
    goto Return;

//------------------------------------------------------------------------

LF74B:
    y = M(0x6B02 + x);
    a = M(0x968B + y);
    goto Return;

//------------------------------------------------------------------------

LF752:
    a = M(0x6AFB + x);
    y = a;
    a ^= M(ObjectHi);
    M(a) >>= 1;
    goto Return;

//------------------------------------------------------------------------

LF7B3:
    a &= M(0x0405 + x);
    writeData(0x0405 + x, a);
    goto Return;

//------------------------------------------------------------------------

LF83E:
    a = M(0x0405 + x);

LF841:
    /* jmp (complex) */

LF852:
    a = x;
    M(a) >>= 1;
    M(a) >>= 1;
    M(a) >>= 1;
    a += M(FrameCount);
    M(a) >>= 1;
    goto Return;

//------------------------------------------------------------------------

LF91D:
    x = M(PageIndex);
    pushReturnIndex(117);
    goto LE792;
Return_117:
    a = y;
    x = a;
    pushReturnIndex(118);
    goto LFD8F;
Return_118:
    goto LFA49;

LF92C:
    a = 0x02;
    writeData(0x6AF5 + y, a);
    writeData(0x6AF6 + y, a);
    a |= M(0x0405 + y);
    writeData(0x0405 + y, a);
    goto Return;

//------------------------------------------------------------------------

Exit19:
    goto Return;

//------------------------------------------------------------------------

LF96A:
    pushReturnIndex(119);
    goto LFA5B;
Return_119:
    pushReturnIndex(120);
    goto LFA1E;
Return_120:
    x = M(PageIndex);
    if (c)
        goto LF97C;
    a = M(0x6AF4 + x);
    if (z)
        goto Exit19;
    pushReturnIndex(121);
    goto LFA60;
Return_121:

LF97C:
    a = 0x01;

KillObject:
    a = 0x00;
    writeData(0x6AF4 + x, a);
    goto Return;

//------------------------------------------------------------------------

LFA41:
    pushReturnIndex(122);
    goto LE792;
Return_122:
    pushReturnIndex(123);
    goto LFD8F;
Return_123:
    if (!c)
        goto KillObject;

LFA49:
    a = M(0x08);
    writeData(0x0400 + x, a);
    a = M(0x09);
    writeData(0x0401 + x, a);
    a = M(0x0B);
    a &= 0x01;
    writeData(0x6AFB + x, a);
    goto Return;

//------------------------------------------------------------------------

LFA5B:
    a = M(0x0404 + x);
    if (z)
        goto Exit20;

LFA60:
    a = 0x00;
    writeData(0x0404 + x, a);
    a = 0x05;
    writeData(0x6AF4 + x, a);

Exit20:
    goto Return;

//------------------------------------------------------------------------

LFA7D:
    x = M(PageIndex);
    a = M(0x0400 + x);
    writeData(0x02, a);
    a = M(0x0401 + x);
    writeData(0x03, a);
    a = M(0x6AFB + x);
    writeData(0x0B, a);
    goto MakeWRAMPtr;

LFA91:
    pushReturnIndex(124);
    goto KillObject;
Return_124:
    a = M(0x95DC);
    pushReturnIndex(125);
    goto LF68D;
Return_125:
    goto LF97C;

Exit13:
    goto Return;

//------------------------------------------------------------------------

LFBCA:
    x = M(PageIndex);
    pushReturnIndex(126);
    goto LF844;
Return_126:
    a = M(0x965B + y);
    compare(a, M(0x6AF9 + x));
    if (z)
        goto Exit13;
    writeData(0x6AF9 + x, a);
    goto LF690;

LFC98:
    a = M(0xB0 + x);
    pushReturnIndex(127);
    goto GoRoutine;
Return_127:

LFCA5:
    pushReturnIndex(128);
    goto LFD84;
Return_128:
    pushReturnIndex(129);
    goto LFD08;
Return_129:
    pushReturnIndex(130);
    goto LFD25;
Return_130:
    goto LDD8B;

LFCB1:
    pushReturnIndex(131);
    goto LFD84;
Return_131:
    pushReturnIndex(132);
    goto LFCC1;
Return_132:
    goto LDD8B;

LFCBA:
    a = 0x00;
    writeData(0xB0 + x, a);
    goto SFX_EnemyHit;

LFD5F:
    a = M(0xB3 + x);
    writeData(0x0B, a);
    a = M(0xB1 + x);
    writeData(0x08, a);
    a = M(0xB2 + x);
    writeData(0x09, a);
    goto Return;

//------------------------------------------------------------------------

LFD6C:
    a = M(0x08);
    writeData(0xB1 + x, a);
    writeData(0x04F0, a);
    a = M(0x09);
    writeData(0xB2 + x, a);
    writeData(0x04F1, a);
    a = M(0x0B);
    a &= 0x01;
    writeData(0xB3 + x, a);
    writeData(0x6BEB, a);
    goto Return;

//------------------------------------------------------------------------

SecExit:
    c = 1;
    goto Return;

//------------------------------------------------------------------------

ClcExit2:
    c = 0;
    goto Return;

//------------------------------------------------------------------------

LFE3D:
    ++M(TileRoutine + x);
    a = 0x00;
    pushReturnIndex(133);
    goto SetTileAnim;
Return_133:
    a = 0x50;
    writeData(TileDelay + x, a);
    a = M(TileWRAMLo + x); //  low WRAM addr of blasted tile
    writeData(0x00, a);
    a = M(TileWRAMHi + x); //  high WRAM addr
    writeData(0x01, a);

LFE54:
    a = 0x02;
    goto UpdateTileAnim;

SetTileAnim:
    writeData(TileAnimIndex + x, a);
    writeData(0x0505 + x, a);
    a = 0x00;
    writeData(TileAnimDelay + x, a);
    goto Return;

//------------------------------------------------------------------------

LFE83:
    a = 0x00;
    writeData(TileRoutine + x, a); //  tile = respawned
    a = M(TileWRAMLo + x);
    c = 0;
    a += 0x21;
    writeData(0x00, a);
    a = M(TileWRAMHi + x);
    writeData(0x01, a);
    pushReturnIndex(134);
    goto LFF3C;
Return_134:
    a = M(0x02);
    writeData(0x07, a);
    a = M(0x03);
    writeData(0x09, a);
    a = M(0x01);
    M(a) >>= 1;
    M(a) >>= 1;
    a &= 0x01;
    writeData(0x0B, a);
    y = 0x00;
    pushReturnIndex(135);
    goto LF186;
Return_135:
    a = 0x04;
    c = 0;
    a += M(ObjRadY);
    writeData(0x04, a);
    a = 0x04;
    c = 0;
    a += M(ObjRadX);
    writeData(0x05, a);
    pushReturnIndex(136);
    goto LF1FA;
Return_136:
    if (c)
        goto Exit23;
    pushReturnIndex(137);
    goto LF311;
Return_137:
    a = 0x50;
    writeData(0x6E, a);
    goto LCE92;

GetTileFramePtr:
    a = M(TileAnimFrame + x);
    M(a) <<= 1;
    y = a;
    a = M(0x97AF + y);
    writeData(0x02, a);
    a = M(0x97B0 + y);
    writeData(0x03, a);

Exit23:
    goto Return;

//------------------------------------------------------------------------

LFF3C:
    a = M(0x00);
    y = a;
    a &= 0xE0;
    writeData(0x02, a);
    a = M(0x01);
    M(a) >>= 1;
    M(0x02).ror();
    M(a) >>= 1;
    M(0x02).ror();
    a = y;
    a &= 0x1F;
    pushReturnIndex(138);
    goto Amul8;
Return_138: //  * 8
    writeData(0x03, a);
    goto Return;

//------------------------------------------------------------------------
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
    }
}
