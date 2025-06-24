// This is an automatically generated file.
// Do not edit directly.
//
#ifndef SMBCONSTANTS_HPP
#define SMBCONSTANTS_HPP

#define CodePtr 0x0C
#define JoyFirst 0x12
#define JoyStatus 0x14
#define JoyRetrig 0x16
#define RetrigDelay 0x18
#define NMIStatus 0x1A
#define PPUDataPending 0x1B
#define PalDataPending 0x1C
#define GameMode 0x1D //  0 = Game is playing
#define MainRoutine 0x1E
#define TitleRoutine 0x1F
#define NextRoutine 0x20
#define CurrentBank 0x23
#define SwitchPending 0x24
#define TimerDelay 0x29
#define Timer 0x2A
#define FrameCount 0x2D //  number of CPU frames executed
#define GamePaused 0x31
#define RoomPtr 0x33
#define StructPtr 0x35
#define WRAMWorkPtr 0x37
#define WRAMPtr 0x39
#define RoomPtrTable 0x3B
#define StructPtrTable 0x3D
#define MacroPtr 0x3F
#define EnemyAnimPtr 0x47
#define ScrollDir 0x49 //  0 = Up
#define PageIndex 0x4B
#define SamusDir 0x4D //  0 = Right
#define SamusDoorDir 0x4E //  direction Samus passed through door
#define MapPosY 0x4F
#define MapPosX 0x50
#define SamusScrX 0x51
#define SamusScrY 0x52
#define WalkSoundDelay 0x53
#define IsSamus 0x55
#define DoorStatus 0x56
#define DoorDelay 0x59
#define RoomNumber 0x5A
#define SpritePagePos 0x5B
#define ObjectPal 0x67
#define RoomPal 0x68
#define TempX 0x69
#define TempY 0x6A
#define SamusBlink 0x70
#define PalToggle 0x76
#define ScrollY 0xFC
#define ScrollX 0xFD
#define PPUCNT1ZP 0xFE
#define PPUCNT0ZP 0xFF
#define HealthLo 0x0106 //  lower health digit in upper 4 bits
#define HealthHi 0x0107 //  upper health digit in lower 4 bits
#define EndTimerLo 0x010A
#define EndTimerHi 0x010B
#define MissileToggle 0x010E //  0 = fire bullets, 1 = fire missiles
#define SpriteRAM 0x0200
#define ObjAction 0x0300
#define ObjRadY 0x0301
#define ObjRadX 0x0302
#define AnimFrame 0x0303
#define AnimDelay 0x0304
#define AnimResetIndex 0x0305
#define AnimIndex 0x0306
#define SamusOnElevator 0x0307 //  1 = Samus is standing on elevator
#define ObjectHi 0x030C
#define ObjectY 0x030D
#define ObjectX 0x030E
#define TileRoutine 0x0500
#define TileAnimFrame 0x0503
#define TileAnimDelay 0x0504
#define TileAnimIndex 0x0506
#define TileDelay 0x0507
#define TileWRAMLo 0x0508
#define TileWRAMHi 0x0509
#define TileType 0x050A
#define PPUStrIndex 0x07A0
#define PPUDataString 0x07A1
#define gr_BOMBS BOOST_BINARY(00000001)
#define gr_HIGHJUMP BOOST_BINARY(00000010)
#define gr_LONGBEAM BOOST_BINARY(00000100)
#define gr_SCREWATTACK BOOST_BINARY(00001000)
#define gr_MARUMARI BOOST_BINARY(00010000)
#define gr_VARIA BOOST_BINARY(00100000)
#define gr_WAVEBEAM BOOST_BINARY(01000000)
#define gr_ICEBEAM BOOST_BINARY(10000000)
#define sa_Stand 0
#define sa_Run 1
#define sa_Jump 2
#define sa_Roll 3
#define sa_PntUp 4
#define sa_Door 5
#define sa_PntJump 6
#define sa_Dead 7
#define sa_Dead2 8
#define sa_Elevator 9
#define an_SamusRun 0x00
#define an_SamusFront 0x04
#define an_SamusStand 0x07
#define an_SamusJump 0x0C
#define an_SamusSalto 0x0E
#define an_SamusRunJump 0x13
#define an_SamusRoll 0x16
#define an_Bullet 0x1B
#define an_SamusFireJump 0x20
#define an_SamusFireRun 0x22
#define an_SamusPntUp 0x27
#define an_Explode 0x32
#define an_SamusJumpPntUp 0x35
#define an_SamusRunPntUp 0x37
#define an_WaveBeam 0x7D
#define an_BombTick 0x7F
#define an_BombExplode 0x82
#define an_MissileLeft 0x8B
#define an_MissileRight 0x8D
#define an_MissileExplode 0x91
#define wa_RegularBeam 1
#define wa_WaveBeam 2
#define wa_IceBeam 3
#define wa_BulletExplode 4
#define wa_LayBomb 8
#define wa_BombCount 9
#define wa_BombExplode 10
#define wa_Missile 11
#define TankCount 0x6877 //  number of energy tanks
#define SamusGear 0x6878
#define MissileCount 0x6879
#define MaxMissiles 0x687A
#define SamusAge 0x687D
#define JustInBailey 0x69B3 //  1 = Samus is without suit
#define PPUControl0 0x2000
#define PPUControl1 0x2001
#define PPUStatus 0x2002
#define SPRAddress 0x2003
#define SPRIOReg 0x2004
#define PPUScroll 0x2005
#define PPUAddress 0x2006
#define PPUIOReg 0x2007
#define SPRDMAReg 0x4014
#define CPUJoyPad 0x4016
#define MMC1Reg0 0x8000
#define MMC1Reg1 0xA000
#define MMC1Reg2 0xC000
#define MMC1Reg3 0xE000
#define FramePtrTable 0x860B
#define PlacePtrTable 0x86DF
#define btn_RIGHT BOOST_BINARY(00000001)
#define btn_LEFT BOOST_BINARY(00000010)
#define btn_DOWN BOOST_BINARY(00000100)
#define btn_UP BOOST_BINARY(00001000)
#define btn_START BOOST_BINARY(00010000)
#define btn_SELECT BOOST_BINARY(00100000)
#define btn_B BOOST_BINARY(01000000) //  FIRE
#define btn_A BOOST_BINARY(10000000) //  JUMP
#define modePlay 0
#define modeTitle 1

#endif // SMBCONSTANTS_HPP
