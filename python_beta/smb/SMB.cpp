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


Start:
    s = x;
    x = 0xff; // reset stack pointer
    writeData(PPU_CTRL_REG1, a);
    a = BOOST_BINARY(00010000); // init PPU control register 1 
    /* cld */
    /* sei */ // pretty standard 6502 type init here

VBlank1: // wait two frames
    if (!n)
        goto VBlank1;
    a = M(PPU_STATUS);

VBlank2:
    x = 0x05; // this is where we check for a warm boot
    y = ColdBootOffset; // load default cold boot pointer
    if (!n)
        goto VBlank2;
    a = M(PPU_STATUS);

WBootCheck: // check each score digit in the top score
    y = WarmBootOffset; // if passed both, load warm boot pointer
    if (!z)
        goto ColdBoot;
    compare(a, 0xa5); // another location has a specific value
    a = M(WarmBootValidation); // second checkpoint, check to see if 
    if (!n)
        goto WBootCheck;
    --x;
    if (c)
        goto ColdBoot; // if not, give up and proceed with cold boot
    compare(a, 10); // to see if we have a valid digit
    a = M(TopScoreDisplay + x);

ColdBoot: // clear memory using pointer in Y
    pushReturnIndex(0);
    goto WritePPUReg1;
Return_0:
    a |= BOOST_BINARY(10000000); // enable NMIs
    a = M(Mirror_PPU_CTRL_REG1);
    ++M(DisableScreenFlag); // set flag to disable screen output
    pushReturnIndex(1);
    goto InitializeNameTables;
Return_1: // initialize both name tables
    pushReturnIndex(2);
    goto MoveAllSpritesOffscreen;
Return_2:
    writeData(PPU_CTRL_REG2, a); // turn off clipping for OAM and background
    a = BOOST_BINARY(00000110);
    writeData(SND_MASTERCTRL_REG, a); // enable all sound channels except dmc
    a = BOOST_BINARY(00001111);
    writeData(PseudoRandomBitReg, a); // set seed for pseudorandom register
    writeData(WarmBootValidation, a);
    a = 0xa5; // set warm boot flag
    writeData(OperMode, a); // reset primary mode of operation
    writeData(SND_DELTA_REG + 1, a); // reset delta counter load register
    pushReturnIndex(3);
    goto InitializeMemory;
Return_3:

EndlessLoop: // endless loop, need I say more?
    return;

NonMaskableInterrupt:
    a |= BOOST_BINARY(00011110);
    a = M(Mirror_PPU_CTRL_REG2); // otherwise reenable bits and save them
    if (!z)
        goto ScreenOff; // if set, used bits as-is
    y = M(DisableScreenFlag); // get screen disable flag
    a &= BOOST_BINARY(11100110);
    a = M(Mirror_PPU_CTRL_REG2); // disable OAM and background display by default
    writeData(PPU_CTRL_REG1, a); // (essentially $2000) but save other bits
    a &= BOOST_BINARY(01111110); // alter name table address to be $2800
    writeData(Mirror_PPU_CTRL_REG1, a);
    a &= BOOST_BINARY(01111111); // save all other bits
    a = M(Mirror_PPU_CTRL_REG1); // disable NMIs in mirror reg

ScreenOff: // save bits for later but not in register at the moment
    ++y; // get offset based on usage
    if (!z)
        goto InitBuffer;
    compare(x, 0x06);
    x = M(VRAM_Buffer_AddrCtrl); // check for usage of $0341
    y = 0x00;
    pushReturnIndex(4);
    goto UpdateScreen;
Return_4: // update screen with buffer contents
    writeData(0x01, a);
    a = M(VRAM_AddrTable_High + x);
    writeData(0x00, a);
    a = M(VRAM_AddrTable_Low + x); // set indirect at $00 to pointer
    x = M(VRAM_Buffer_AddrCtrl); // load control for pointer to buffer contents
    writeData(SPR_DMA, a);
    a = 0x02; // perform spr-ram DMA access on $0200-$02ff
    writeData(PPU_SPR_ADDR, a); // reset spr-ram address register
    pushReturnIndex(5);
    goto InitScroll;
Return_5:
    a = 0x00;
    x = M(PPU_STATUS); // reset flip-flop and reset scroll registers to zero
    writeData(PPU_CTRL_REG2, a);
    a &= BOOST_BINARY(11100111); // disable screen for now
    writeData(Mirror_PPU_CTRL_REG2, a);

InitBuffer:
    if (!z)
        goto NoDecTimers;
    --M(TimerControl);
    if (z)
        goto DecTimers; // all frame and interval timers
    a = M(TimerControl); // if master timer control not set, decrement
    if (c)
        goto PauseSkip;
    a >>= 1;
    a = M(GamePauseStatus); // check for pause status
    pushReturnIndex(6);
    goto UpdateTopScore;
Return_6:
    pushReturnIndex(7);
    goto PauseRoutine;
Return_7: // handle pause
    pushReturnIndex(8);
    goto ReadJoypads;
Return_8: // read joypads
    pushReturnIndex(9);
    goto SoundEngine;
Return_9: // play sound
    writeData(PPU_CTRL_REG2, a);
    a = M(Mirror_PPU_CTRL_REG2); // copy mirror of $2001 to register
    writeData(VRAM_Buffer_AddrCtrl, a); // reinit address control to $0301
    writeData(VRAM_Buffer1 + x, a);
    writeData(VRAM_Buffer1_Offset + x, a);
    a = 0x00; // clear buffer header at last location
    x = M(VRAM_Buffer_Offset + y);

DecTimers: // load end offset for end of frame timers
    x = 0x23; // interval timers will decrement along with frame timers
    writeData(IntervalTimerControl, a); // if control for interval timers expired,
    a = 0x14;
    if (!n)
        goto DecTimersLoop; // if not expired, only frame timers will decrement
    --M(IntervalTimerControl); // decrement interval timer control,
    x = 0x14;

DecTimersLoop: // check current timer
    --M(Timers + x); // otherwise decrement the current timer
    if (z)
        goto SkipExpTimer; // if current timer expired, branch to skip,
    a = M(Timers + x);

SkipExpTimer: // move onto next timer
    if (!n)
        goto DecTimersLoop; // do this until all timers are dealt with
    --x;

NoDecTimers: // increment frame counter
    ++M(FrameCounter);

PauseSkip:
    c = 1; // if one or the other is set, carry will be set
    if (z)
        goto RotPRandomBit;
    c = 0; // if neither or both are set, carry will be clear
    a ^= M(0x00); // perform exclusive-OR on d1 from first and second bytes
    a &= BOOST_BINARY(00000010); // mask out all but d1
    a = M(PseudoRandomBitReg + 1); // get second memory location
    writeData(0x00, a); // save here
    a &= BOOST_BINARY(00000010); // mask out all but d1
    a = M(PseudoRandomBitReg); // get first memory location of LSFR bytes
    y = 0x07;
    x = 0x00;

RotPRandomBit: // rotate carry into d7, and rotate last bit into carry
    if (z)
        goto SkipSprite0;
    a = M(Sprite0HitDetectFlag); // check for flag here
    if (!z)
        goto RotPRandomBit;
    --y; // decrement for loop
    ++x; // increment to next byte
    M(PseudoRandomBitReg + x).ror();

Sprite0Clr: // wait for sprite 0 flag to clear, which will
    pushReturnIndex(10);
    goto SpriteShuffler;
Return_10:
    pushReturnIndex(11);
    goto MoveSpritesOffscreen;
Return_11:
    if (c)
        goto Sprite0Hit;
    a >>= 1;
    a = M(GamePauseStatus); // if in pause mode, do not bother with sprites at all
    if (!z)
        goto Sprite0Clr;
    a &= BOOST_BINARY(01000000); // not happen until vblank has ended
    a = M(PPU_STATUS);

Sprite0Hit: // do sprite #0 hit detection
    y = 0x14; // small delay, to wait until we hit horizontal blank time
    if (z)
        goto Sprite0Hit;
    a &= BOOST_BINARY(01000000);
    a = M(PPU_STATUS);

HBlankDelay:
    if (!z)
        goto HBlankDelay;
    --y;

SkipSprite0: // set scroll registers from variables
    pushReturnIndex(12);
    goto OperModeExecutionTree;
Return_12: // otherwise do one of many, many possible subroutines
    if (c)
        goto SkipMainOper;
    a >>= 1;
    a = M(GamePauseStatus); // if in pause mode, do not perform operation mode stuff
    writeData(PPU_CTRL_REG1, a);
    pha();
    a = M(Mirror_PPU_CTRL_REG1); // load saved mirror of $2000
    writeData(PPU_SCROLL_REG, a);
    a = M(VerticalScroll);
    writeData(PPU_SCROLL_REG, a);
    a = M(HorizontalScroll);

SkipMainOper: // reset flip-flop
    return; // we are done until the next frame!
    writeData(PPU_CTRL_REG1, a);
    a |= BOOST_BINARY(10000000); // reactivate NMIs
    pla();
    a = M(PPU_STATUS);

PauseRoutine:
    if (!z)
        goto ExitPause; // if not, leave
    compare(a, 0x03);
    a = M(OperMode_Task); // if we are in game mode, are we running game engine?
    if (!z)
        goto ExitPause; // if not, leave
    compare(a, GameModeValue); // are we in game mode?
    if (z)
        goto ChkPauseTimer;
    compare(a, VictoryModeValue); // if so, go ahead
    a = M(OperMode); // are we in victory mode?

ChkPauseTimer: // check if pause timer is still counting down
    goto Return;

//------------------------------------------------------------------------
    --M(GamePauseTimer); // if so, decrement and leave
    if (z)
        goto ChkStart;
    a = M(GamePauseTimer);

ChkStart: // check to see if start is pressed
    if (!z)
        goto SetPause; // unconditional branch
    a |= BOOST_BINARY(10000000);
    a ^= BOOST_BINARY(00000001); // invert d0 and set d7
    writeData(PauseSoundQueue, y);
    ++y; // set pause sfx queue for next pause mode
    y = a;
    a = M(GamePauseStatus);
    writeData(GamePauseTimer, a);
    a = 0x2b; // set pause timer
    if (!z)
        goto ExitPause; // joypad reading routine makes this unnecessary)
    a &= BOOST_BINARY(10000000); // and if so, do not reset timer (residual,
    a = M(GamePauseStatus); // check to see if timer flag is set
    if (z)
        goto ClrPauseTimer;
    a &= Start_Button; // on controller 1
    a = M(SavedJoypad1Bits);

ClrPauseTimer: // clear timer flag if timer is at zero and start button
    a &= BOOST_BINARY(01111111); // is not pressed
    a = M(GamePauseStatus);

SetPause:
    writeData(GamePauseStatus, a);

ExitPause:
    goto Return;

//------------------------------------------------------------------------

SpriteShuffler:
    x = 0x0e; // start at the end of OAM data offsets
    writeData(0x00, a); // sprite #10
    a = 0x28; // load preset value which will put it at
    y = M(AreaType); // load level type, likely residual code

ShuffleLoop: // check for offset value against
    a += M(0x00); // otherwise add preset value $28 to offset
    c = 0;
    if (!c)
        goto StrSprOffset; // if not exceeded $ff, skip second add
    a += M(SprShuffleAmt + y); // get shuffle amount, add to current sprite offset
    c = 0;
    y = M(SprShuffleAmtOffset); // get current offset to preset value we want to add
    if (!c)
        goto NextSprOffset; // if less, skip this part
    compare(a, M(0x00)); // the preset value
    a = M(SprDataOffset + x);

StrSprOffset: // store new offset here or old one if branched to here
    writeData(SprDataOffset + x, a);

NextSprOffset: // move backwards to next one
    x = 0x00; // otherwise, init to 0
    if (!z)
        goto SetAmtOffset; // if offset + 1 not 3, store
    compare(x, 0x03); // check if offset + 1 goes to 3
    ++x;
    x = M(SprShuffleAmtOffset); // load offset
    if (!n)
        goto ShuffleLoop;
    --x;

SetAmtOffset:
    y = 0x02;
    x = 0x08; // load offsets for values and storage
    writeData(SprShuffleAmtOffset, x);

SetMiscOffset: // load one of three OAM data offsets
    goto Return;

//------------------------------------------------------------------------
    if (!n)
        goto SetMiscOffset; // do this until all misc spr offsets are loaded
    --y;
    --x;
    --x;
    --x;
    writeData(Misc_SprDataOffset + x, a);
    a += 0x08;
    c = 0; // this code loads into the misc sprite offsets
    writeData(Misc_SprDataOffset - 1 + x, a); // note that due to the way X is set up,
    a += 0x08; // more to the third one
    c = 0; // add eight to the second and eight
    writeData(Misc_SprDataOffset - 2 + x, a); // store first one unmodified, but
    a = M(SprDataOffset + 5 + y);

OperModeExecutionTree:
    switch (a)
    {
    } // most of what goes on starts here
    a = M(OperMode); // this is the heart of the entire program,

MoveAllSpritesOffscreen:
    goto Skip_0;
    y = 0x00; // this routine moves all sprites off the screen
Skip_0:

MoveSpritesOffscreen:
    a = 0xf8; // off the screen
    y = 0x04; // this routine moves all but sprite 0

SprInitLoop: // write 248 into OAM data's Y coordinate
    goto Return;

//------------------------------------------------------------------------
    if (!z)
        goto SprInitLoop;
    ++y;
    ++y;
    ++y;
    ++y; // which will move it off the screen
    writeData(Sprite_Y_Position + y, a);

TitleScreenMode:
    switch (a)
    {
    }
    a = M(OperMode_Task);

GameMenuRoutine:
    if (!z)
        goto ChkSelect; // if not, branch to check select button
    compare(a, A_Button + Start_Button); // check to see if A + start was pressed
    if (z)
        goto StartGame;
    compare(a, Start_Button);
    a |= M(SavedJoypad2Bits); // only the start button (either joypad)
    a = M(SavedJoypad1Bits); // check to see if either player pressed
    y = 0x00;

StartGame: // if either start or A + start, execute here
    goto ChkContinue;

ChkSelect: // check to see if the select button was pressed
    goto RunDemo; // otherwise, run game engine for demo
    if (c)
        goto ResetTitle; // if carry flag set, demo over, thus branch
    pushReturnIndex(13);
    goto DemoEngine;
Return_13: // run through the demo actions
    writeData(SelectTimer, a); // set controller bits here if running demo
    if (!z)
        goto ChkWorldSel; // if demo timer not expired, branch to check world selection
    x = M(DemoTimer); // otherwise check demo timer
    if (z)
        goto SelectBLogic; // if so, branch reset demo timer
    compare(a, Select_Button);

ChkWorldSel: // check to see if world selection has been enabled
    ++y; // if so, increment Y and execute same code as select
    if (!z)
        goto NullJoypad;
    compare(a, B_Button); // if so, check to see if the B button was pressed
    if (z)
        goto NullJoypad;
    x = M(WorldSelectEnableFlag);

SelectBLogic: // if select or B pressed, check demo timer one last time
    goto NullJoypad;
    pushReturnIndex(14);
    goto DrawMushroomIcon;
Return_14:
    writeData(NumberOfPlayers, a);
    a ^= BOOST_BINARY(00000001); // change number of players and draw icon accordingly
    a = M(NumberOfPlayers); // if no, must have been the select button, therefore
    if (z)
        goto IncWorldSel; // note this will not be run if world selection is disabled
    compare(y, 0x01); // was the B button pressed earlier?  if so, branch
    writeData(SelectTimer, a);
    a = 0x10; // otherwise reset select button timer
    if (!z)
        goto NullJoypad; // if not expired, branch
    a = M(SelectTimer); // check select/B button timer
    writeData(DemoTimer, a);
    a = 0x18; // otherwise reset demo timer
    if (z)
        goto ResetTitle; // if demo timer expired, branch to reset title screen mode
    a = M(DemoTimer);

IncWorldSel: // increment world select number
    pushReturnIndex(15);
    goto GoContinue;
Return_15:
    writeData(WorldSelectNumber, a); // store as current world select number
    a &= BOOST_BINARY(00000111); // mask out higher bits
    a = x;
    ++x;
    x = M(WorldSelectNumber);

UpdateShroom: // write template for world select in vram buffer
    writeData(VRAM_Buffer1 + 3, y); // null terminator
    ++y; // proper display, and put in blank byte before
    y = M(WorldNumber); // get world number from variable and increment for
    if (n)
        goto UpdateShroom;
    compare(x, 0x06);
    ++x;
    writeData(VRAM_Buffer1 - 1 + x, a); // do this until all bytes are written
    a = M(WSelectBufferTemplate + x);

NullJoypad: // clear joypad bits for player 1
    writeData(SavedJoypad1Bits, a);
    a = 0x00;

RunDemo: // run game engine
    if (!z)
        goto ExitMenu; // if not, do not do all the resetting below
    compare(a, 0x06);
    a = M(GameEngineSubroutine); // check to see if we're running lose life routine
    pushReturnIndex(16);
    goto GameCoreRoutine;
Return_16:

ResetTitle: // reset game modes, disable
    goto Return;

//------------------------------------------------------------------------
    ++M(DisableScreenFlag);
    writeData(Sprite0HitDetectFlag, a);
    writeData(OperMode_Task, a); // screen output
    writeData(OperMode, a); // sprite 0 check and disable
    a = 0x00;

ChkContinue: // if timer for demo has expired, reset modes
    pushReturnIndex(17);
    goto GoContinue;
Return_17: // continue function when pressing A + start
    a = M(ContinueWorld); // load previously saved world number for secret
    if (!c)
        goto StartWorld1; // if not, don't load continue function's world number
    a <<= 1; // check to see if A button was also pushed
    if (z)
        goto ResetTitle;
    y = M(DemoTimer);

StartWorld1:
    a = 0x00;
    x = 0x17;
    writeData(DemoTimer, a);
    writeData(OperMode_Task, a); // set game mode here, and clear demo timer
    a = 0x00;
    writeData(PrimaryHardMode, a); // hard mode must be on as well
    a = M(WorldSelectEnableFlag); // if world select flag is on, then primary
    ++M(OperMode); // set next game mode
    ++M(FetchNewGameTimerFlag); // set fetch new game timer flag
    ++M(OffScr_Hidden1UpFlag);
    ++M(Hidden1UpFlag); // set 1-up box flag for both players
    pushReturnIndex(18);
    goto LoadAreaPointer;
Return_18:

InitScores: // clear player scores and coin displays
    if (!n)
        goto InitScores;
    --x;
    writeData(ScoreAndCoinDisplay + x, a);

ExitMenu:
    goto Return;

//------------------------------------------------------------------------

GoContinue: // start both players at the first area
    goto Return;

//------------------------------------------------------------------------
    writeData(OffScr_AreaNumber, x);
    writeData(AreaNumber, x); // will make no difference
    x = 0x00; // note that on power-up using this function
    writeData(OffScr_WorldNumber, a); // of the previously saved world number
    writeData(WorldNumber, a);

DrawMushroomIcon:
    y = 0x07; // read eight bytes to be read by transfer routine

IconDataRead: // note that the default position is set for a
    writeData(VRAM_Buffer1 + 5, a);
    a = 0xce; // then load shroom icon tile in 2-player position
    writeData(VRAM_Buffer1 + 3, a);
    a = 0x24; // otherwise, load blank tile in 1-player position
    if (z)
        goto ExitIcon; // if set to 1-player game, we're done
    a = M(NumberOfPlayers); // check number of players
    if (!n)
        goto IconDataRead;
    --y;
    writeData(VRAM_Buffer1 - 1 + y, a); // 1-player game
    a = M(MushroomIconData + y);

ExitIcon:
    goto Return;

//------------------------------------------------------------------------

DemoEngine:
    if (z)
        goto DemoOver; // if timer already at zero, skip
    writeData(DemoActionTimer, a); // store as current timer
    a = M(DemoTimingData - 1 + x); // get next timer
    c = 1; // set carry by default for demo over
    ++M(DemoAction); // if expired, increment action, X, and
    ++x;
    if (!z)
        goto DoAction; // if timer still counting down, skip
    a = M(DemoActionTimer); // load current action timer
    x = M(DemoAction); // load current demo action

DoAction: // get and perform action (current or next)
    c = 0; // clear carry if demo still going
    --M(DemoActionTimer); // decrement action timer
    writeData(SavedJoypad1Bits, a);
    a = M(DemoActionData - 1 + x);

DemoOver:
    goto Return;

//------------------------------------------------------------------------

VictoryMode:
    pushReturnIndex(19);
    goto EnemiesAndLoopsCore;
Return_19: // and run enemy code
    writeData(ObjectOffset, x); // otherwise reset enemy object offset 
    x = 0x00;
    if (z)
        goto AutoPlayer; // if on bridge collapse, skip enemy processing
    a = M(OperMode_Task); // get current task of victory mode
    pushReturnIndex(20);
    goto VictoryModeSubroutines;
Return_20: // run victory mode subroutines

AutoPlayer: // get player's relative coordinates
    goto PlayerGfxHandler; // draw the player, then leave
    pushReturnIndex(21);
    goto RelativePlayerPosition;
Return_21:

VictoryModeSubroutines:
    switch (a)
    {
    }
    a = M(OperMode_Task);

SetupVictoryMode:
    goto IncModeTask_B; // jump to set next major task in victory mode
    writeData(EventMusicQueue, a); // play win castle music
    a = EndOfCastleMusic;
    writeData(DestinationPageLoc, x); // store here
    ++x; // increment to next page
    x = M(ScreenRight_PageLoc); // get page location of right side of screen

PlayerVictoryWalk:
    if (c)
        goto DontWalk; // if still on other page, branch ahead
    compare(a, 0x60); // compare with preset horizontal position
    a = M(Player_X_Position); // otherwise get player's horizontal position
    if (!z)
        goto PerformWalk; // if page locations don't match, branch
    compare(a, M(DestinationPageLoc)); // compare with destination page location
    a = M(Player_PageLoc); // get player's page location
    writeData(VictoryWalkControl, y);
    y = 0x00; // set value here to not walk player by default

PerformWalk: // otherwise increment value and Y
    ++y; // note Y will be used to walk the player
    ++M(VictoryWalkControl);

DontWalk: // put contents of Y in A and
    ++M(VictoryWalkControl); // increment value to stay in this routine
    pushReturnIndex(22);
    goto UpdScrollVar;
Return_22: // do another sub to update screen and scroll variables
    pushReturnIndex(23);
    goto ScrollScreen;
Return_23: // do sub to scroll the screen
    y = a; // use as scroll amount
    a += 0x00; // add carry from previous addition
    a = 0x01; // set 1 pixel per frame
    writeData(ScrollFractional, a); // save fractional movement amount
    a += 0x80;
    c = 0; // do fixed point math on fractional part of scroll
    a = M(ScrollFractional);
    if (z)
        goto ExitVWalk; // branch if equal to change modes if necessary
    compare(a, M(DestinationPageLoc)); // against set value here
    a = M(ScreenLeft_PageLoc); // check page location of left side of screen
    pushReturnIndex(24);
    goto AutoControlPlayer;
Return_24: // use A to move player to the right or not
    a = y;

ExitVWalk: // load value set here
    goto Return; // otherwise leave

//------------------------------------------------------------------------
    if (z)
        goto IncModeTask_A; // if zero, branch to change modes
    a = M(VictoryWalkControl);

PrintVictoryMessages:
    goto ThankPlayer; // and skip to next part
    a -= 0x01; // otherwise subtract one
    if (!c)
        goto IncMsgCounter; // if not at 3 yet (world 8 only), branch to increment
    compare(a, 0x03); // check primary message counter again
    if (!z)
        goto MRetainerMsg; // if not at world 8, skip to next part
    compare(y, World8);
    y = M(WorldNumber); // check world number
    if (c)
        goto IncMsgCounter; // is residual code, counter never reaches 9)
    compare(a, 0x09); // if at 9 or above, branch elsewhere (this comparison
    if (z)
        goto ThankPlayer; // if set to zero, branch to print first message
    a = M(PrimaryMsgCounter); // otherwise load primary message counter
    if (!z)
        goto IncMsgCounter; // if set, branch to increment message counters
    a = M(SecondaryMsgCounter); // load secondary message counter

MRetainerMsg: // check primary message counter
    if (!c)
        goto IncMsgCounter; // if not at 2 yet (world 1-7 only), branch
    compare(a, 0x02);

ThankPlayer: // put primary message counter into Y
    if (!z)
        goto EvalForMusic; // do an unconditional branch to the same place
    ++y; // otherwise increment Y once for luigi and
    if (z)
        goto EvalForMusic; // if mario, branch
    a = M(CurrentPlayer); // otherwise get player currently on the screen
    if (!z)
        goto SecondPartMsg; // if counter nonzero, skip this part, do not print first message
    y = a;

SecondPartMsg: // increment Y to do world 8's message
    if (c)
        goto IncMsgCounter; // branch to keep counting
    compare(y, 0x03); // if counter at 3 (world 1-7 only)
    if (c)
        goto SetEndTimer; // branch to set victory end timer
    compare(y, 0x04); // if counter at 4 (world 1-7 only)
    --y; // otherwise decrement Y for world 1-7's message
    if (z)
        goto EvalForMusic; // if at world 8, branch to next part
    compare(a, World8); // check world number
    a = M(WorldNumber);
    ++y;

EvalForMusic: // if counter not yet at 3 (world 8 only), branch
    writeData(EventMusicQueue, a); // otherwise load victory music first (world 8 only)
    a = VictoryMusic; // reach this code if counter = 0, and will always branch)
    if (!z)
        goto PrintMsg; // to print message only (note world 1-7 will only
    compare(y, 0x03);

PrintMsg: // put primary message counter in A
    writeData(VRAM_Buffer_AddrCtrl, a); // write message counter to vram address controller
    a += 0x0c; // ($0c-$0d = first), ($0e = world 1-7's), ($0f-$12 = world 8's)
    c = 0; // add $0c or 12 to counter thus giving an appropriate value,
    a = y;

IncMsgCounter:
    compare(a, 0x07); // check primary counter one more time
    writeData(PrimaryMsgCounter, a);
    a += 0x00; // add carry to primary message counter
    a = M(PrimaryMsgCounter);
    writeData(SecondaryMsgCounter, a);
    a += 0x04; // add four to secondary message counter
    c = 0;
    a = M(SecondaryMsgCounter);

SetEndTimer: // if not reached value yet, branch to leave
    writeData(WorldEndTimer, a); // otherwise set world end timer
    a = 0x06;
    if (!c)
        goto ExitMsgs;

IncModeTask_A: // move onto next task in mode
    ++M(OperMode_Task);

ExitMsgs: // leave
    goto Return;

//------------------------------------------------------------------------

PlayerEndWorld:
    writeData(OperMode, a); // set mode of operation to game mode
    a = GameModeValue;
    ++M(FetchNewGameTimerFlag); // set flag to load game timer from header
    pushReturnIndex(25);
    goto LoadAreaPointer;
Return_25: // get area address offset for the next area
    ++M(WorldNumber); // increment world number to move onto the next world
    writeData(OperMode_Task, a); // initialize secondary mode of operation
    writeData(LevelNumber, a); // and level number control to start at area 1
    writeData(AreaNumber, a); // otherwise initialize area number used as offset
    a = 0x00;
    if (c)
        goto EndChkBButton; // thus branch to read controller
    compare(y, World8); // if on world 8, player is done with game, 
    y = M(WorldNumber); // check world number
    if (!z)
        goto EndExitOne; // branch to leave if not
    a = M(WorldEndTimer); // check to see if world end timer expired

EndExitOne: // and leave
    goto Return;

//------------------------------------------------------------------------

EndChkBButton:
    pushReturnIndex(26);
    goto TerminateGame;
Return_26: // do sub to continue other player or end game
    writeData(NumberofLives, a);
    a = 0xff; // remove onscreen player's lives
    writeData(WorldSelectEnableFlag, a);
    a = 0x01; // otherwise set world selection flag
    if (z)
        goto EndExitTwo; // branch to leave if not
    a &= B_Button; // either controller
    a |= M(SavedJoypad2Bits); // check to see if B button was pressed on
    a = M(SavedJoypad1Bits);

EndExitTwo: // leave
    goto Return;

//------------------------------------------------------------------------

FloateyNumbersRoutine:
    writeData(FloateyNum_Control + x, a); // it in range
    a = 0x0b; // otherwise set to $0b, thus keeping
    if (!c)
        goto ChkNumTimer;
    compare(a, 0x0b); // if less than $0b, branch
    if (z)
        goto EndExitOne; // if zero, branch to leave
    a = M(FloateyNum_Control + x); // load control for floatey number

ChkNumTimer: // use as Y
    goto Return;

//------------------------------------------------------------------------
    writeData(FloateyNum_Control + x, a); // initialize floatey number control and leave
    if (!z)
        goto DecNumTimer; // if nonzero, branch ahead
    a = M(FloateyNum_Timer + x); // check value here
    y = a;

DecNumTimer: // decrement value here
    writeData(Square2SoundQueue, a); // and play the 1-up sound
    a = Sfx_ExtraLife;
    ++M(NumberofLives); // give player one extra life (1-up)
    if (!z)
        goto LoadNumTiles; // branch ahead if not found
    compare(y, 0x0b); // check offset for $0b
    if (!z)
        goto ChkTallEnemy;
    compare(a, 0x2b); // if not reached a certain point, branch  
    --M(FloateyNum_Timer + x);

LoadNumTiles: // load point value here
    pushReturnIndex(27);
    goto AddToScore;
Return_27: // update the score accordingly
    writeData(DigitModifier + x, a); // store as amount to add to the digit
    a &= BOOST_BINARY(00001111); // mask out the high nybble
    a = M(ScoreUpdateData + y); // load again and this time
    x = a; // use as X offset, essentially the digit
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1; // move high nybble to low
    a = M(ScoreUpdateData + y);

ChkTallEnemy: // get OAM data offset for enemy object
    if (c)
        goto FloateyPart; // $02 or greater, branch beyond this part
    compare(a, 0x02); // if enemy state defeated or otherwise
    a = M(Enemy_State + x);
    if (c)
        goto GetAltOffset; // branch elsewhere if enemy object => $09
    compare(a, TallEnemy);
    if (z)
        goto FloateyPart;
    compare(a, RedCheepCheep);
    if (z)
        goto FloateyPart; // branch if cheep-cheep of either color
    compare(a, GreyCheepCheep);
    if (z)
        goto GetAltOffset; // branch elsewhere if hammer bro
    compare(a, HammerBro);
    if (z)
        goto FloateyPart; // branch if piranha plant
    compare(a, PiranhaPlant);
    if (z)
        goto FloateyPart; // branch if spiny
    compare(a, Spiny);
    a = M(Enemy_ID + x); // get enemy object identifier
    y = M(Enemy_SprDataOffset + x);

GetAltOffset: // load some kind of control bit
    x = M(ObjectOffset); // get enemy object offset again
    y = M(Alt_SprDataOffset + x); // get alternate OAM data offset
    x = M(SprDataOffset_Ctrl);

FloateyPart: // get vertical coordinate for
    writeData(FloateyNum_Y_Pos + x, a); // otherwise subtract one and store as new
    a -= 0x01;
    if (!c)
        goto SetupNumSpr; // status bar, branch
    compare(a, 0x18); // floatey number, if coordinate in the
    a = M(FloateyNum_Y_Pos + x);

SetupNumSpr: // get vertical coordinate
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset); // get enemy object offset and leave
    writeData(Sprite_Tilenumber + 4 + y, a); // display the second half
    a = M(FloateyNumTileData + 1 + x);
    writeData(Sprite_Tilenumber + y, a); // display first half of number of points
    a = M(FloateyNumTileData + x);
    x = a; // and use as offset for look-up table
    a <<= 1; // multiply our floatey number control by 2
    a = M(FloateyNum_Control + x);
    writeData(Sprite_Attributes + 4 + y, a); // of left and right sprites
    writeData(Sprite_Attributes + y, a); // set palette control in attribute bytes
    a = 0x02;
    writeData(Sprite_X_Position + 4 + y, a); // coordinate of right sprite
    a += 0x08; // add eight pixels and store into X
    c = 0;
    writeData(Sprite_X_Position + y, a); // store into X coordinate of left sprite
    a = M(FloateyNum_X_Pos + x); // get horizontal coordinate
    pushReturnIndex(28);
    goto DumpTwoSpr;
Return_28: // left and right sprite's Y coordinates
    a -= 0x08; // subtract eight and dump into the
    a = M(FloateyNum_Y_Pos + x);

ScreenRoutines:
    switch (a)
    {
    }
    a = M(ScreenRoutineTask); // run one of the following subroutines

InitScreen:
    goto SetVRAMAddr_A;
    x = 0x03; // into buffer pointer
    if (z)
        goto NextSubtask; // if mode still 0, do not load
    a = M(OperMode);
    pushReturnIndex(29);
    goto InitializeNameTables;
Return_29: // and erase both name and attribute tables
    pushReturnIndex(30);
    goto MoveAllSpritesOffscreen;
Return_30: // initialize all sprites including sprite #0

SetupIntermediate:
    goto IncSubtask; // then move onto the next task
    writeData(BackgroundColorCtrl, a); // color ctrl and player status from stack
    pla(); // and once we're done, we return bg
    writeData(PlayerStatus, a); // the intermediate lives display
    pla(); // we only execute this routine for
    pushReturnIndex(31);
    goto GetPlayerColors;
Return_31:
    writeData(BackgroundColorCtrl, a); // is set to less than 4
    a = 0x02; // this is the ONLY time background color control
    writeData(PlayerStatus, a); // and player status to not fiery
    a = 0x00; // set background color to black
    pha();
    a = M(PlayerStatus);
    pha(); // and player status to stack
    a = M(BackgroundColorCtrl); // save current background color control

GetAreaPalette:
    x = M(AreaPalette + y); // based on area type
    y = M(AreaType); // select appropriate palette to load

SetVRAMAddr_A: // store offset into buffer control
    writeData(VRAM_Buffer_AddrCtrl, x);

NextSubtask: // move onto next task
    goto IncSubtask;

GetBackgroundColor:
    writeData(VRAM_Buffer_AddrCtrl, a); // note that if set to 5-7, $0301 will not be read
    a = M(BGColorCtrl_Addr - 4 + y); // put appropriate palette into vram
    if (z)
        goto NoBGColor; // if not set, increment task and fetch palette
    y = M(BackgroundColorCtrl); // check background color control

NoBGColor: // increment to next subtask and plod on through
    ++M(ScreenRoutineTask);

GetPlayerColors:
    y = 0x04; // load offset for luigi
    if (z)
        goto ChkFiery;
    a = M(CurrentPlayer); // check which player is on the screen
    y = 0x00;
    x = M(VRAM_Buffer1_Offset); // get current buffer offset

ChkFiery: // check player status
    y = 0x08;
    if (!z)
        goto StartClrGet; // if fiery, load alternate offset for fiery player
    compare(a, 0x02);
    a = M(PlayerStatus);

StartClrGet: // do four colors
    writeData(0x00, a);
    a = 0x03;

ClrGetLoop: // fetch player colors and store them
    y = M(AreaType); // otherwise use area type bits from area offset as offset
    if (!z)
        goto SetBGColor; // therefore use it as offset to background color
    y = M(BackgroundColorCtrl); // if this value is four or greater, it will be set
    x = M(VRAM_Buffer1_Offset); // load original offset from before
    if (!n)
        goto ClrGetLoop;
    --M(0x00);
    ++x;
    ++y;
    writeData(VRAM_Buffer1 + 3 + x, a); // in the buffer
    a = M(PlayerColors + y);

SetBGColor: // to background color instead
    a += 0x07;
    c = 0; // in case we want to write anything else later
    a = x; // move the buffer pointer ahead 7 bytes
    writeData(VRAM_Buffer1 + 7 + x, a);
    a = 0x00; // now the null terminator
    writeData(VRAM_Buffer1 + 2 + x, a);
    a = 0x04; // write length byte to buffer
    writeData(VRAM_Buffer1 + 1 + x, a);
    a = 0x10;
    writeData(VRAM_Buffer1 + x, a); // save to buffer
    a = 0x3f; // set for sprite palette address
    writeData(VRAM_Buffer1 + 3 + x, a);
    a = M(BackgroundColors + y);

SetVRAMOffset: // store as new vram buffer offset
    goto Return;

//------------------------------------------------------------------------
    writeData(VRAM_Buffer1_Offset, a);

GetAlternatePalette1:
    a = 0x0b; // if found, load appropriate palette
    if (!z)
        goto NoAltPal;
    compare(a, 0x01);
    a = M(AreaStyle); // check for mushroom level style

SetVRAMAddr_B:
    writeData(VRAM_Buffer_AddrCtrl, a);

NoAltPal: // now onto the next task
    goto IncSubtask;

WriteTopStatusLine:
    goto IncSubtask; // onto the next task
    pushReturnIndex(32);
    goto WriteGameText;
Return_32: // output it
    a = 0x00; // select main status bar

WriteBottomStatusLine:
    goto IncSubtask;
    writeData(VRAM_Buffer1_Offset, a);
    a += 0x06;
    c = 0;
    a = x; // move the buffer offset up by 6 bytes
    writeData(VRAM_Buffer1 + 6 + x, a);
    a = 0x00; // put null terminator on
    writeData(VRAM_Buffer1 + 5 + x, a);
    a = y;
    ++y; // increment for proper number display
    y = M(LevelNumber); // next the level number
    writeData(VRAM_Buffer1 + 4 + x, a);
    a = 0x28; // next the dash
    writeData(VRAM_Buffer1 + 3 + x, a);
    a = y;
    ++y;
    y = M(WorldNumber); // first the world number
    writeData(VRAM_Buffer1 + 2 + x, a);
    a = 0x03; // write length for it
    writeData(VRAM_Buffer1 + 1 + x, a);
    a = 0x73;
    writeData(VRAM_Buffer1 + x, a);
    a = 0x20; // write address for world-area number on screen
    x = M(VRAM_Buffer1_Offset);
    pushReturnIndex(33);
    goto GetSBNybbles;
Return_33: // write player's score and coin tally to screen

DisplayTimeUp:
    goto OutputInter;
    a = 0x02; // output time-up screen to buffer
    writeData(GameTimerExpiredFlag, a); // reset timer expiration flag
    a = 0x00;
    if (z)
        goto NoTimeUp; // control 2 tasks forward, otherwise, stay here
    a = M(GameTimerExpiredFlag); // if game timer not expired, increment task

NoTimeUp: // increment control task 2 tasks forward
    goto IncSubtask;
    ++M(ScreenRoutineTask);

DisplayIntermediate:
    if (!z)
        goto NoInter; // and jump to specific task, otherwise
    a = M(DisableIntermediate); // if this flag is set, skip intermediate lives display
    if (z)
        goto PlayerInter;
    compare(y, 0x03); // and if so, branch (possibly residual)
    y = M(AreaType); // check if we are on castle level
    if (!z)
        goto NoInter; // and branch if found
    a = M(AltEntranceControl); // otherwise check for mode of alternate entry
    if (z)
        goto GameOverInter; // if so, proceed to display game over screen
    compare(a, GameOverModeValue); // are we in game over mode?
    if (z)
        goto NoInter; // if in title screen mode, skip this
    a = M(OperMode); // check primary mode of operation

PlayerInter: // put player in appropriate place for
    a = 0x01; // lives display, then output lives display to buffer
    pushReturnIndex(34);
    goto DrawPlayer_Intermediate;
Return_34:

OutputInter:
    goto Return;

//------------------------------------------------------------------------
    writeData(DisableScreenFlag, a); // reenable screen output
    a = 0x00;
    pushReturnIndex(35);
    goto ResetScreenTimer;
Return_35:
    pushReturnIndex(36);
    goto WriteGameText;
Return_36:

GameOverInter: // set screen timer
    goto IncModeTask_B;
    pushReturnIndex(37);
    goto WriteGameText;
Return_37:
    a = 0x03; // output game over screen to buffer
    writeData(ScreenTimer, a);
    a = 0x12;

NoInter: // set for specific task and leave
    goto Return;

//------------------------------------------------------------------------
    writeData(ScreenRoutineTask, a);
    a = 0x08;

AreaParserTaskControl:
    ++M(DisableScreenFlag); // turn off screen

TaskLoop: // render column set of current area
    ++M(ScreenRoutineTask); // if not, move on to the next task
    if (!n)
        goto OutputCol;
    --M(ColumnSets); // do we need to render more column sets?
    if (!z)
        goto TaskLoop; // if tasks still not all done, do another one
    a = M(AreaParserTaskNum); // check number of tasks
    pushReturnIndex(38);
    goto AreaParserTaskHandler;
Return_38:

OutputCol: // set vram buffer to output rendered column set
    goto Return;

//------------------------------------------------------------------------
    writeData(VRAM_Buffer_AddrCtrl, a); // on next NMI
    a = 0x06;

DrawTitleScreen:
    a = M(PPU_DATA); // do one garbage read
    writeData(0x00, y);
    y = 0x00;
    writeData(0x01, a); // the indirect at $00
    a = 0x03; // put address $0300 into
    writeData(PPU_ADDRESS, a);
    a = LOBYTE(TitleScreenDataOffset);
    writeData(PPU_ADDRESS, a); // the vram address register
    a = HIBYTE(TitleScreenDataOffset); // load address $1ec0 into
    if (!z)
        goto IncModeTask_B; // if not, exit
    a = M(OperMode); // are we in title screen mode?

OutputTScr: // get title screen from chr-rom
    ++M(0x01); // otherwise increment high byte of indirect
    if (!z)
        goto ChkHiByte; // if not past 256 bytes, do not increment
    ++y;
    writeData(W(0x00) + y, a); // store 256 bytes into buffer
    a = M(PPU_DATA);

ChkHiByte: // check high byte?
    goto SetVRAMAddr_B; // increment task and exit
    a = 0x05; // set buffer transfer control to $0300,
    if (!c)
        goto OutputTScr; // if not, loop back and do another
    compare(y, 0x3a); // check if offset points past end of data
    if (!z)
        goto OutputTScr; // if not, loop back and do another
    compare(a, 0x04); // at $0400?
    a = M(0x01);

ClearBuffersDrawIcon:
    x = 0x00; // otherwise, clear buffer space
    if (!z)
        goto IncModeTask_B; // if not title screen mode, leave
    a = M(OperMode); // check game mode

TScrClear:
    pushReturnIndex(39);
    goto DrawMushroomIcon;
Return_39: // draw player select icon
    if (!z)
        goto TScrClear;
    --x;
    writeData(VRAM_Buffer1 - 1 + 0x100 + x, a);
    writeData(VRAM_Buffer1 - 1 + x, a);

IncSubtask: // move onto next task
    goto Return;

//------------------------------------------------------------------------
    ++M(ScreenRoutineTask);

WriteTopScore:
    pushReturnIndex(40);
    goto UpdateNumber;
Return_40:
    a = 0xfa; // run display routine to display top score on title

IncModeTask_B: // move onto next mode
    goto Return;

//------------------------------------------------------------------------
    ++M(OperMode_Task);

WriteGameText:
    y = 0x08; // otherwise warp zone, therefore set offset
    if (!c)
        goto Chk2Players; // branch to check players
    compare(y, 0x08); // if set to do time-up or game over,
    if (!c)
        goto LdGameText; // branch to use current offset as-is
    compare(y, 0x04); // if set to do top status bar or world/lives display,
    y = a; // multiply by 2 and use as offset
    a <<= 1;
    pha(); // save text number to stack

Chk2Players: // check for number of players
    ++y; // otherwise increment offset by one to not print name
    if (!z)
        goto LdGameText; // if there are two, use current offset to also print name
    a = M(NumberOfPlayers);

LdGameText: // get offset to message we want to print
    y = 0x00;
    x = M(GameTextOffsets + y);

GameTextLoop: // load message data
    if (!z)
        goto GameTextLoop; // do this for 256 bytes if no terminator found
    ++y;
    ++x; // and increment increment
    writeData(VRAM_Buffer1 + y, a); // otherwise write data to buffer
    if (z)
        goto EndGameText; // branch to end text if found
    compare(a, 0xff); // check for terminator
    a = M(GameText + x);

EndGameText: // put null terminator at end
    writeData(VRAM_Buffer1 + 7, y); // the number of lives exceeds 19
    y = 0x9f; // next to the difference...strange things happen if
    a -= 10; // if so, subtract 10 and put a crown tile
    if (!c)
        goto PutLives;
    compare(a, 10); // more than 9 lives?
    a += 0x01;
    c = 0; // and increment by one for display
    a = M(NumberofLives); // otherwise, check number of lives
    if (!z)
        goto CheckPlayerName; // if not, branch to check player's name
    --x; // are we printing the world/lives display?
    if (c)
        goto PrintWarpZoneNumbers;
    compare(a, 0x04); // are we printing warp zone?
    x = a;
    pla(); // pull original text number from stack
    writeData(VRAM_Buffer1 + y, a);
    a = 0x00;

PutLives:
    goto Return;

//------------------------------------------------------------------------
    writeData(VRAM_Buffer1 + 21, y); // we're done here
    ++y;
    y = M(LevelNumber);
    writeData(VRAM_Buffer1 + 19, y);
    ++y; // to the buffer in the spaces surrounding the dash
    y = M(WorldNumber); // write world and level numbers (incremented for display)
    writeData(VRAM_Buffer1 + 8, a);

CheckPlayerName:
    a ^= BOOST_BINARY(00000001); // if not, must be time up, invert d0 to do other player
    if (z)
        goto ChkLuigi;
    compare(y, GameOverModeValue);
    y = M(OperMode); // check for game over mode
    if (!z)
        goto ChkLuigi;
    --x; // check to see if current message number is for time up
    a = M(CurrentPlayer); // load current player
    if (z)
        goto ExitChkName; // if only 1 player, leave
    a = M(NumberOfPlayers); // check number of players

ChkLuigi:
    y = 0x04;
    if (!c)
        goto ExitChkName; // if mario is current player, do not change the name
    a >>= 1;

NameLoop: // otherwise, replace "MARIO" with "LUIGI"
    if (!n)
        goto NameLoop; // do this until each letter is replaced
    --y;
    writeData(VRAM_Buffer1 + 3 + y, a);
    a = M(LuigiName + y);

ExitChkName:
    goto Return;

//------------------------------------------------------------------------

PrintWarpZoneNumbers:
    y = 0x00;
    x = a;
    a <<= 1; // offset
    a <<= 1; // twice to get proper warp zone number
    a -= 0x04; // subtract 4 and then shift to the left

WarpNumLoop: // print warp zone numbers into the
    goto SetVRAMOffset;
    a = 0x2c; // load new buffer pointer at end of message
    if (!c)
        goto WarpNumLoop;
    compare(y, 0x0c);
    ++y;
    ++y;
    ++y;
    ++y; // put a number in every fourth space
    ++x;
    writeData(VRAM_Buffer1 + 27 + y, a); // placeholders from earlier
    a = M(WarpZoneNumbers + x);

ResetSpritesAndScreenTimer:
    pushReturnIndex(41);
    goto MoveAllSpritesOffscreen;
Return_41: // otherwise reset sprites now
    if (!z)
        goto NoReset; // if not, branch to leave
    a = M(ScreenTimer); // check if screen timer has expired

ResetScreenTimer:
    ++M(ScreenRoutineTask); // move onto next task
    writeData(ScreenTimer, a);
    a = 0x07; // reset timer again

NoReset:
    goto Return;

//------------------------------------------------------------------------

RenderAreaGraphics:
    x = a;
    writeData(0x04, a);
    a = 0x00; // init attribute row
    writeData(VRAM_Buffer2 + 2 + y, a); // to increment by 32 (in columns)
    a = 0x9a; // store length byte of 26 here with d7 set
    writeData(VRAM_Buffer2 + y, a);
    a = M(CurrentNTAddr_High);
    writeData(VRAM_Buffer2 + 1 + y, a);
    a = M(CurrentNTAddr_Low); // get current name table address we're supposed to render
    writeData(0x00, y);
    y = M(VRAM_Buffer2_Offset); // store vram buffer offset
    writeData(0x05, a);
    a &= 0x01;
    a = M(CurrentColumnPos); // store LSB of where we're at

DrawMTLoop: // store init value of 0 or incremented offset for buffer
    goto SetAttrib;
    M(0x03).rol();
    M(0x03).rol(); // thus in d1-d0, for upper left square
    M(0x03).rol(); // rotate attribute bits 3 to the left
    if (c)
        goto LLeft;
    a >>= 1; // branch if LSB set (clear = top left, set = bottom left)
    a = M(0x01); // get current row we're rendering
    if (!z)
        goto RightCheck; // branch if set (clear = left attrib, set = right)
    a = M(0x05); // get LSB of current column where we're at, and
    y = M(0x04); // get current attribute row
    writeData(VRAM_Buffer2 + 4 + x, a);
    a = M(W(0x06) + y); // now get the second (bottom left or bottom right) and store
    ++y;
    writeData(VRAM_Buffer2 + 3 + x, a); // get first tile number (top left or top right) and store
    a = M(W(0x06) + y);
    x = M(0x00); // use vram buffer offset from before as X
    y = a;
    a += M(0x02); // of the metatiles
    a <<= 1; // then add to the tile offset so we can draw either side
    a ^= BOOST_BINARY(00000001); // to get the correct column position in the metatile,
    a &= BOOST_BINARY(00000001); // mask out all but LSB, then invert LSB, multiply by 2
    a = M(AreaParserTaskNum); // get current task number for level processing and
    writeData(0x02, a);
    a <<= 1;
    a <<= 1; // multiply by 4 and use as tile offset
    a = M(MetatileBuffer + x); // get metatile number again
    writeData(0x07, a);
    a = M(MetatileGraphics_High + y);
    writeData(0x06, a);
    a = M(MetatileGraphics_Low + y); // get address to graphics table from here
    y = a; // rotate bits to d1-d0 and use as offset here
    a.rol(); // %00xxxxxx - metatile number
    a.rol(); // %xx000000 - attribute table bits, 
    a <<= 1; // note that metatile format is:
    writeData(0x03, a); // store attribute table bits here
    a &= BOOST_BINARY(11000000);
    a = M(MetatileBuffer + x); // get first metatile number, and mask out all but 2 MSB
    writeData(0x01, x);

RightCheck: // get LSB of current row we're rendering
    goto SetAttrib;
    M(0x03) >>= 1;
    M(0x03) >>= 1;
    M(0x03) >>= 1; // thus in d3-d2, for upper right square
    M(0x03) >>= 1; // shift attribute bits 4 to the right
    if (c)
        goto NextMTRow;
    a >>= 1; // branch if set (clear = top right, set = bottom right)
    a = M(0x01);

LLeft: // shift attribute bits 2 to the right
    M(0x03) >>= 1; // thus in d5-d4 for lower left square
    M(0x03) >>= 1;

NextMTRow: // move onto next attribute row  
    ++M(0x04);

SetAttrib: // get previously saved bits from before
    writeData(CurrentNTAddr_High, a);
    a ^= BOOST_BINARY(00000100); // to move onto the next appropriate name table
    a = M(CurrentNTAddr_High); // and then invert d2 of the name table address high
    writeData(CurrentNTAddr_Low, a); // just under the status bar
    a = 0x80; // if wraparound occurs, make sure low byte stays
    if (!z)
        goto ExitDrawM;
    a &= BOOST_BINARY(00011111); // if no wraparound, just skip this part
    a = M(CurrentNTAddr_Low); // check current low byte
    ++M(CurrentNTAddr_Low); // increment name table address low
    writeData(VRAM_Buffer2_Offset, y); // store new buffer offset
    writeData(VRAM_Buffer2 + y, a); // put null terminator at end of data for name table
    a = 0x00;
    ++y;
    ++y;
    ++y; // (for name table address and length bytes)
    y = M(0x00); // get current vram buffer offset, increment by 3
    if (!c)
        goto DrawMTLoop; // if not there yet, loop back
    compare(x, 0x0d);
    ++x; // the bottom of the screen
    x = M(0x01); // get current gfx buffer row, and check for
    ++M(0x00);
    ++M(0x00); // increment vram buffer offset by 2
    writeData(AttributeBuffer + y, a); // the old, and store
    a |= M(0x03); // if any, and put new bits, if any, onto
    a = M(AttributeBuffer + y);

ExitDrawM: // jump to set buffer to $0341 and leave
    goto SetVRAMCtrl;

RenderAttributeTables:
    a ^= BOOST_BINARY(00000100); // otherwise invert d2
    if (c)
        goto SetATHigh;
    a = M(CurrentNTAddr_High); // get high byte and branch if borrow not set
    writeData(0x01, a);
    a &= BOOST_BINARY(00011111); // mask out bits again and store
    a -= 0x04;
    c = 1; // subtract four 
    a &= BOOST_BINARY(00011111); // to be written to, mask out all but 5 LSB,
    a = M(CurrentNTAddr_Low); // get low byte of next name table address

SetATHigh: // mask out all other bits
    y = M(VRAM_Buffer2_Offset); // get buffer offset
    x = 0x00;
    writeData(0x01, a); // attribute table in our temp address
    a += 0xc0; // we should now have the appropriate block of
    a >>= 1;
    a >>= 1; // attribute table and store
    a = M(0x01); // get low byte - 4, divide by 4, add offset for
    writeData(0x00, a);
    a |= 0x23; // add $2300 to the high byte and store
    a &= BOOST_BINARY(00000100);

AttribLoop:
    writeData(VRAM_Buffer2_Offset, y); // store offset in case we want to do any more
    writeData(VRAM_Buffer2 + y, a); // put null terminator at the end
    if (!c)
        goto AttribLoop;
    compare(x, 0x07); // if we're at the end yet
    ++x; // increment attribute offset and check to see
    ++y;
    ++y;
    ++y;
    ++y; // increment buffer offset by 4 bytes
    writeData(AttributeBuffer + x, a); // clear current byte in attribute buffer
    a >>= 1;
    writeData(VRAM_Buffer2 + 2 + y, a); // store length of 1 in buffer
    a = 0x01;
    writeData(VRAM_Buffer2 + 3 + y, a); // in the buffer
    a = M(AttributeBuffer + x); // fetch current attribute table byte and store
    writeData(0x01, a); // also store in temp again
    writeData(VRAM_Buffer2 + 1 + y, a);
    a += 0x08; // below the status bar, and store
    c = 0; // get low byte, add 8 because we want to start
    a = M(0x01);
    writeData(VRAM_Buffer2 + y, a); // store high byte of attribute table address
    a = M(0x00);

SetVRAMCtrl:
    goto Return;

//------------------------------------------------------------------------
    writeData(VRAM_Buffer_AddrCtrl, a); // set buffer to $0341 and leave
    a = 0x06;

ColorRotation:
    y = a; // otherwise use frame counter's 3 LSB as offset here
    if (c)
        goto ExitColorRot; // if offset over 48 bytes, branch to leave
    compare(x, 0x31);
    x = M(VRAM_Buffer1_Offset); // check vram buffer offset
    if (!z)
        goto ExitColorRot; // branch if not set to zero to do this every eighth frame
    a &= 0x07; // mask out all but three LSB
    a = M(FrameCounter); // get frame counter

GetBlankPal: // get blank palette for palette 3
    y = a; // save as offset here
    a <<= 1;
    a <<= 1; // multiply by 4 to get proper offset
    a = M(AreaType); // get area type
    writeData(0x00, a); // set counter here
    a = 0x03;
    x = M(VRAM_Buffer1_Offset); // get current vram buffer offset
    if (!c)
        goto GetBlankPal; // do this until all bytes are copied
    compare(y, 0x08);
    ++y;
    ++x; // increment offsets
    writeData(VRAM_Buffer1 + x, a); // store it in the vram buffer
    a = M(BlankPalette + y);

GetAreaPal: // fetch palette to be written based on area type
    writeData(ColorRotateOffset, a); // otherwise, init to keep it in range
    a = 0x00;
    if (!c)
        goto ExitColorRot; // if so, branch to leave
    compare(a, 0x06); // check to see if it's still in range
    a = M(ColorRotateOffset);
    ++M(ColorRotateOffset); // increment color cycling offset
    writeData(VRAM_Buffer1_Offset, a);
    a += 0x07;
    c = 0; // add seven bytes to vram buffer offset
    a = M(VRAM_Buffer1_Offset);
    writeData(VRAM_Buffer1 + 4 + x, a); // get and store current color in second slot of palette
    a = M(ColorRotatePalette + y);
    y = M(ColorRotateOffset); // get color cycling offset
    x = M(VRAM_Buffer1_Offset); // get current vram buffer offset
    if (!n)
        goto GetAreaPal; // do this until the palette is all copied
    --M(0x00); // decrement counter
    ++x;
    ++y;
    writeData(VRAM_Buffer1 + 3 + x, a); // store it to overwrite blank palette in vram buffer
    a = M(Palette3Data + y);

ExitColorRot: // leave
    goto Return;

//------------------------------------------------------------------------

RemoveCoin_Axe:
    a = 0x04; // otherwise load offset for blank metatile used in water
    if (!z)
        goto WriteBlankMT; // if not water type, use offset
    x = M(AreaType); // check area type
    a = 0x03; // load offset for default blank metatile
    y = 0x41; // set low byte so offset points to $0341

WriteBlankMT: // do a sub to write blank metatile to vram buffer
    goto Return;

//------------------------------------------------------------------------
    writeData(VRAM_Buffer_AddrCtrl, a); // set vram address controller to $0341 and leave
    a = 0x06;
    pushReturnIndex(42);
    goto PutBlockMetatile;
Return_42:

ReplaceBlockMetatile:
    goto Return; // leave

//------------------------------------------------------------------------
    --M(Block_RepFlag + x); // decrement flag (residual code)
    ++M(Block_ResidualCounter); // increment unused counter (residual code)
    pushReturnIndex(43);
    goto WriteBlockMetatile;
Return_43: // write metatile to vram buffer to replace block object

DestroyBlockMetatile:
    a = 0x00; // force blank metatile if branched/jumped to this point

WriteBlockMetatile:
    ++y; // if any other metatile, increment offset for empty block
    if (z)
        goto UseBOffset; // use offset if metatile is breakable brick w/o line
    compare(a, 0x52);
    if (z)
        goto UseBOffset; // use offset if metatile is brick with coins (w/o line)
    compare(a, 0x5d);
    ++y; // increment offset for brick metatile w/o line
    if (z)
        goto UseBOffset; // use offset if metatile is breakable brick w/ line
    compare(a, 0x51);
    if (z)
        goto UseBOffset; // use offset if metatile is brick with coins (w/ line)
    compare(a, 0x58);
    y = 0x00; // load offset for brick metatile w/ line
    if (z)
        goto UseBOffset; // branch if found (unconditional if branched from 8a6b)
    compare(a, 0x00); // check contents of A for blank metatile
    y = 0x03; // load offset for blank metatile

UseBOffset: // put Y in A
    pushReturnIndex(44);
    goto PutBlockMetatile;
Return_44: // get appropriate block data and write to vram buffer
    ++y; // move onto next byte
    y = M(VRAM_Buffer1_Offset); // get vram buffer offset
    a = y;

MoveVOffset: // decrement vram buffer offset
    goto SetVRAMOffset; // branch to store as new vram buffer offset
    a += 10;
    c = 0;
    a = y; // add 10 bytes to it
    --y;

PutBlockMetatile:
    y = 0x24; // otherwise load high byte for name table 1
    if (!c)
        goto SaveHAdder; // if not, use current high byte
    compare(a, 0xd0); // check to see if we're on odd-page block buffer
    a = M(0x06); // get low byte of block buffer pointer
    y = 0x20; // load high byte for name table 0
    x = a;
    a <<= 1; // multiply A by four and use as X
    a <<= 1;
    writeData(0x01, y); // store vram buffer offset for next byte
    writeData(0x00, x); // store control bit from SprDataOffset_Ctrl

SaveHAdder: // save high byte here
    y = M(0x01); // get vram buffer offset to be used
    writeData(0x05, a); // store here
    a += M(0x03); // then add high byte of name table
    c = 0;
    a += 0x00; // add carry
    a = M(0x05); // get whatever was in d7 and d6 of vertical high nybble
    writeData(0x04, a); // and store here
    a += M(0x04); // add low byte of name table and carry to vertical high nybble
    M(0x05).rol(); // shift and rotate d6 onto d0 and d5 into carry
    a <<= 1;
    M(0x05).rol(); // shift and rotate d7 onto d0 and d6 into carry
    a <<= 1;
    a += 0x20; // add 32 pixels for the status bar
    c = 0;
    a = M(0x02); // get vertical high nybble offset used in block buffer routine
    writeData(0x05, a); // initialize temp high byte
    a = 0x00;
    writeData(0x04, a); // and then store it here
    a <<= 1; // multiply by 2 to get appropriate name table low byte
    a &= 0x0f; // mask out high nybble of block buffer pointer
    writeData(0x03, y);

RemBridge: // write top left and top right
    goto Return; // and leave

//------------------------------------------------------------------------
    x = M(0x00); // get offset control bit here
    writeData(VRAM_Buffer1 + 9 + y, a); // put null terminator at end
    a = 0x00;
    writeData(VRAM_Buffer1 + 6 + y, a); // both slots
    writeData(VRAM_Buffer1 + 1 + y, a); // put length of 2 in
    a = 0x02;
    writeData(VRAM_Buffer1 + 4 + y, a); // table address to both slots
    writeData(VRAM_Buffer1 - 1 + y, a); // write high byte of name
    a = M(0x05); // plus 32 bytes into second slot
    writeData(VRAM_Buffer1 + 5 + y, a); // write low byte of name table
    a += 0x20; // add 32 bytes to value
    c = 0; // into first slot as read
    writeData(VRAM_Buffer1 + y, a); // write low byte of name table
    a = M(0x04);
    writeData(VRAM_Buffer1 + 8 + y, a);
    a = M(BlockGfxData + 3 + x); // second spot
    writeData(VRAM_Buffer1 + 7 + y, a); // right tiles numbers into
    a = M(BlockGfxData + 2 + x); // write bottom left and bottom
    writeData(VRAM_Buffer1 + 3 + y, a);
    a = M(BlockGfxData + 1 + x);
    writeData(VRAM_Buffer1 + 2 + y, a); // tile numbers into first spot
    a = M(BlockGfxData + x);

JumpEngine:
    /* jmp (complex) */ // jump to the address we loaded
    writeData(0x07, a);
    a = M(W(0x04) + y); // that called this routine
    ++y; // it will return to the execution before the sub
    writeData(0x06, a); // note that if an RTS is performed in next routine
    a = M(W(0x04) + y); // load pointer from indirect
    ++y;
    writeData(0x05, a);
    pla();
    writeData(0x04, a); // save to indirect
    pla(); // pull saved return address from stack
    y = a;
    a <<= 1; // shift bit from contents of A

InitializeNameTables:
    a = 0x20; // and then set it to name table 0
    pushReturnIndex(45);
    goto WriteNTAddr;
Return_45:
    a = 0x24; // set vram address to start of name table 1
    pushReturnIndex(46);
    goto WritePPUReg1;
Return_46:
    a &= BOOST_BINARY(11110000); // clear rest of lower nybble, leave higher alone
    a |= BOOST_BINARY(00010000); // set sprites for first 4k and background for second 4k
    a = M(Mirror_PPU_CTRL_REG1); // load mirror of ppu reg $2000
    a = M(PPU_STATUS); // reset flip-flop

WriteNTAddr:
    a = 0x24;
    y = 0xc0;
    x = 0x04; // clear name table with blank tile #24
    writeData(PPU_ADDRESS, a);
    a = 0x00;
    writeData(PPU_ADDRESS, a);

InitNTLoop: // count out exactly 768 tiles
    writeData(VRAM_Buffer1, a); // init vram buffer 1
    writeData(VRAM_Buffer1_Offset, a); // init vram buffer 1 offset
    a = x;
    y = 64; // now to clear the attribute table (with zero this time)
    if (!z)
        goto InitNTLoop;
    --x;
    if (!z)
        goto InitNTLoop;
    --y;
    writeData(PPU_DATA, a);

InitATLoop:
    goto InitScroll; // initialize scroll registers to zero
    writeData(VerticalScroll, a);
    writeData(HorizontalScroll, a); // reset scroll variables
    if (!z)
        goto InitATLoop;
    --y;
    writeData(PPU_DATA, a);

ReadJoypads:
    ++x; // increment for joypad 2's port
    pushReturnIndex(47);
    goto ReadPortBits;
Return_47:
    writeData(JOYPAD_PORT, a);
    x = a; // start with joypad 1's port
    a >>= 1;
    writeData(JOYPAD_PORT, a);
    a = 0x01; // reset and clear strobe of joypad ports

ReadPortBits:
    y = 0x08;

PortLoop: // push previous bit onto stack
    goto Return;

//------------------------------------------------------------------------
    writeData(SavedJoypadBits + x, a); // or start bits and leave
    a &= BOOST_BINARY(11001111); // otherwise store without select
    pla();
    if (z)
        goto Save8Bits; // have any of these two set, branch
    a &= M(JoypadBitMask + x); // if neither saved state nor current state
    a &= BOOST_BINARY(00110000); // check for select or start
    pha();
    writeData(SavedJoypadBits + x, a); // save controller status here always
    if (!z)
        goto PortLoop; // count down bits left
    --y;
    a.rol(); // rotate bit from carry flag
    pla(); // read bits from stack
    a >>= 1;
    a |= M(0x00); // famicom systems in japan
    a >>= 1; // this is necessary on the old
    writeData(0x00, a); // check d1 and d0 of port output
    a = M(JOYPAD_PORT + x); // read current bit on joypad port
    pha();

Save8Bits:
    goto Return;

//------------------------------------------------------------------------
    writeData(JoypadBitMask + x, a); // save with all bits in another place and leave
    pla();

WriteBufferToScreen:
    a &= BOOST_BINARY(11111011); // only increment by 1
    if (c)
        goto SetupWrites; // if d7 of third byte was clear, ppu will
    a |= BOOST_BINARY(00000100); // set ppu to increment by 32 by default
    a = M(Mirror_PPU_CTRL_REG1); // load mirror of $2000,
    pha();
    a <<= 1; // shift to left and save in stack
    a = M(W(0x00) + y); // load next byte (third)
    ++y;
    writeData(PPU_ADDRESS, a); // store low byte of vram address
    a = M(W(0x00) + y); // load next byte (second)
    ++y;
    writeData(PPU_ADDRESS, a); // store high byte of vram address

SetupWrites: // write to register
    ++y;
    a |= BOOST_BINARY(00000010); // otherwise set d1 and increment Y
    if (!c)
        goto GetLength; // if d6 of third byte was clear, do not repeat byte
    a <<= 1;
    pla(); // pull from stack and shift to left again
    pushReturnIndex(48);
    goto WritePPUReg1;
Return_48:

GetLength: // shift back to the right to get proper length
    x = a;
    a >>= 1; // note that d1 will now be in carry
    a >>= 1;

OutputToVRAM: // if carry set, repeat loading the same byte
    ++y; // otherwise increment Y to load next byte
    if (c)
        goto RepeatByte;

RepeatByte: // load more data from buffer and write to vram
    writeData(PPU_ADDRESS, a);
    writeData(PPU_ADDRESS, a); // then reinitializes it for some reason
    writeData(PPU_ADDRESS, a);
    a = 0x00;
    writeData(PPU_ADDRESS, a);
    a = 0x3f; // sets vram address to $3f00
    writeData(0x01, a);
    a += M(0x01);
    a = 0x00;
    writeData(0x00, a); // to allow this routine to read another set of updates
    a += M(0x00); // add end length plus one to the indirect at $00
    a = y;
    c = 1;
    if (!z)
        goto OutputToVRAM;
    --x; // done writing?
    writeData(PPU_DATA, a);
    a = M(W(0x00) + y);

UpdateScreen: // reset flip-flop
    if (!z)
        goto WriteBufferToScreen; // if byte is zero we have no further updates to make here
    a = M(W(0x00) + y);
    y = 0x00; // load first byte from indirect as a pointer
    x = M(PPU_STATUS);

InitScroll: // store contents of A into scroll registers
    goto Return;

//------------------------------------------------------------------------
    writeData(PPU_SCROLL_REG, a); // and end whatever subroutine led us here
    writeData(PPU_SCROLL_REG, a);

WritePPUReg1:
    goto Return;

//------------------------------------------------------------------------
    writeData(Mirror_PPU_CTRL_REG1, a); // and its mirror
    writeData(PPU_CTRL_REG1, a); // write contents of A to PPU register 1

PrintStatusBarNumbers:
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1; // and print to score display
    a = M(0x00); // move high nybble to low
    pushReturnIndex(49);
    goto OutputNumbers;
Return_49: // use first nybble to print the coin display
    writeData(0x00, a); // store player-specific offset

OutputNumbers:
    a = 0x22; // if so, put further down on the screen
    if (!z)
        goto SetupNums;
    compare(y, 0x00); // are we writing top score on title screen?
    a = 0x20; // put at top of screen by default
    x = M(VRAM_Buffer1_Offset); // get current buffer pointer
    y = a;
    a <<= 1; // shift to left and use as offset
    pha(); // save incremented value to stack for now and
    if (c)
        goto ExitOutputN;
    compare(a, 0x06);
    a &= BOOST_BINARY(00001111); // mask out high nybble
    a += 0x01;
    c = 0; // add 1 to low nybble

SetupNums:
    x = M(0x02);
    y = a; // use value as offset to display digits
    a -= M(StatusBarData + 1 + y); // subtract from length byte we read before
    c = 1;
    a = M(StatusBarOffset + x); // load offset to value we want to write
    x = a;
    pla(); // pull original incremented value from stack
    writeData(0x02, x); // and buffer pointer elsewhere for now
    writeData(0x03, a); // save length byte in counter
    writeData(VRAM_Buffer1 + 2 + x, a);
    a = M(StatusBarData + 1 + y);
    writeData(VRAM_Buffer1 + 1 + x, a); // we're printing to the buffer
    a = M(StatusBarData + y); // write low vram address and length of thing
    writeData(VRAM_Buffer1 + x, a);

DigitPLoop: // write digits to the buffer
    writeData(VRAM_Buffer1_Offset, x); // store it in case we want to use it again
    ++x;
    ++x;
    ++x; // increment buffer pointer by 3
    writeData(VRAM_Buffer1 + 3 + x, a);
    a = 0x00; // put null terminator at end
    if (!z)
        goto DigitPLoop;
    --M(0x03); // do this until all the digits are written
    ++y;
    ++x;
    writeData(VRAM_Buffer1 + 3 + x, a);
    a = M(DisplayDigits + y);

ExitOutputN:
    goto Return;

//------------------------------------------------------------------------

DigitsMathRoutine:
    x = 0x05;
    if (z)
        goto EraseDMods; // if in title screen mode, branch to lock score
    compare(a, TitleScreenModeValue);
    a = M(OperMode); // check mode of operation

AddModLoop: // load digit amount to increment
    if (c)
        goto CarryOne; // if digit greater than $09, branch to add
    compare(a, 10);
    if (n)
        goto BorrowOne; // if result is a negative number, branch to subtract
    a += M(DisplayDigits + y); // add to current digit
    c = 0;
    a = M(DigitModifier + x);

StoreNewD: // store as new score or game timer digit
    if (!n)
        goto AddModLoop; // loop back if we're not done yet
    --x; // and digit amounts to increment
    --y; // move onto next digits in score or game timer
    writeData(DisplayDigits + y, a);

EraseDMods: // store zero here
    x = 0x06; // start with the last digit
    a = 0x00;

EraseMLoop: // initialize the digit amounts to increment
    goto Return;

//------------------------------------------------------------------------
    if (!n)
        goto EraseMLoop; // do this until they're all reset, then leave
    --x;
    writeData(DigitModifier - 1 + x, a);

BorrowOne: // decrement the previous digit, then put $09 in
    if (!z)
        goto StoreNewD; // the one", then do an unconditional branch back
    a = 0x09; // the game timer digit we're currently on to "borrow
    --M(DigitModifier - 1 + x);

CarryOne: // subtract ten from our digit to make it a
    goto StoreNewD; // go back to just after we branched here
    ++M(DigitModifier - 1 + x); // preceding current digit to "carry the one" properly
    a -= 10; // proper BCD number, then increment the digit
    c = 1;

UpdateTopScore:
    x = 0x0b; // now do luigi's score
    pushReturnIndex(50);
    goto TopScoreCheck;
Return_50:
    x = 0x05; // start with mario's score

TopScoreCheck:
    c = 1;
    y = 0x05; // start with the lowest digit

GetScoreDiff: // subtract each player digit from each high score digit
    ++y;
    ++x; // increment X and Y once to the start of the score
    if (!c)
        goto NoTopSc; // check to see if borrow is still set, if so, no new high score
    if (!n)
        goto GetScoreDiff;
    --y; // subtraction clears it (player digit is higher than top)
    --x; // any player digit, borrow will be set until a subsequent
    a -= M(TopScoreDisplay + y); // from lowest to highest, if any top score digit exceeds
    a = M(PlayerScoreDisplay + x);

CopyScore: // store player's score digits into high score memory area
    if (!c)
        goto CopyScore;
    compare(y, 0x06); // do this until we have stored them all
    ++y;
    ++x;
    writeData(TopScoreDisplay + y, a);
    a = M(PlayerScoreDisplay + x);

NoTopSc:
    goto Return;

//------------------------------------------------------------------------

InitializeGame:
    y = 0x1f;
    pushReturnIndex(51);
    goto InitializeMemory;
Return_51: // but this time, clear only as far as $076f
    y = 0x6f; // clear all memory as in initialization procedure,

ClrSndLoop: // clear out memory used
    pushReturnIndex(52);
    goto LoadAreaPointer;
Return_52:
    writeData(DemoTimer, a);
    a = 0x18; // set demo timer
    if (!n)
        goto ClrSndLoop;
    --y; // by the sound engines
    writeData(SoundMemory + y, a);

InitializeArea:
    a = 0x00;
    x = 0x21;
    pushReturnIndex(53);
    goto InitializeMemory;
Return_53: // this is only necessary if branching from
    y = 0x4b; // clear all memory again, only as far as $074b

ClrTimersLoop: // clear out memory between
    a = M(EntrancePage); // otherwise use saved entry page number here
    if (z)
        goto StartPage;
    y = M(AltEntranceControl); // if AltEntranceControl not set, use halfway page, if any found
    a = M(HalfwayPage);
    if (!n)
        goto ClrTimersLoop;
    --x; // $0780 and $07a1
    writeData(Timers + x, a);

StartPage: // set as value here
    y = 0x24;
    if (z)
        goto SetInitNTHigh; // address for rendering of game area
    a &= BOOST_BINARY(00000001); // otherwise use $2080, this address used later as name table
    y = 0x20; // if on odd numbered page, use $2480 as start of rendering
    pushReturnIndex(54);
    goto GetScreenPosition;
Return_54: // get pixel coordinates for screen borders
    writeData(BackloadingFlag, a); // set flag here if halfway page or saved entry page number found
    writeData(CurrentPageLoc, a); // also set as current page
    writeData(ScreenLeft_PageLoc, a);

SetInitNTHigh: // store name table address
    if (!c)
        goto CheckHalfway;
    compare(a, Level3); // if 1 or 2, do not set secondary hard mode flag
    a = M(LevelNumber); // otherwise, world 5, so check level number
    if (!z)
        goto SetSecHard; // if not equal to, then world > 5, thus activate
    if (!c)
        goto CheckHalfway;
    compare(a, World5); // if less than 5, do not activate secondary
    a = M(WorldNumber); // otherwise check world number
    if (!z)
        goto SetSecHard; // if so, activate the secondary no matter where we're at
    a = M(PrimaryHardMode); // check to see if primary hard mode has been activated
    pushReturnIndex(55);
    goto GetAreaDataAddrs;
Return_55: // get enemy and level addresses and load header
    writeData(ColumnSets, a); // 12 column sets = 24 metatile columns = 1 1/2 screens
    a = 0x0b; // set value for renderer to update 12 column sets
    --M(AreaObjectLength + 2);
    --M(AreaObjectLength + 1);
    --M(AreaObjectLength); // set area object lengths for all empty
    writeData(BlockBufferColumnPos, a);
    a <<= 1;
    a <<= 1;
    a <<= 1; // of block buffer column position
    a <<= 1; // store LSB of page number in high nybble
    writeData(CurrentNTAddr_Low, y);
    y = 0x80;
    writeData(CurrentNTAddr_High, y);

SetSecHard: // set secondary hard mode flag for areas 5-3 and beyond
    ++M(SecondaryHardMode);

CheckHalfway:
    writeData(PlayerEntranceCtrl, a);
    a = 0x02; // if halfway page set, overwrite start position from header
    if (z)
        goto DoneInitArea;
    a = M(HalfwayPage);

DoneInitArea: // silence music
    goto Return;

//------------------------------------------------------------------------
    ++M(OperMode_Task); // increment one of the modes
    writeData(DisableScreenFlag, a);
    a = 0x01; // disable screen output
    writeData(AreaMusicQueue, a);
    a = Silence;

PrimaryGameSetup:
    writeData(OffScr_NumberofLives, a);
    writeData(NumberofLives, a); // give each player three lives
    a = 0x02;
    writeData(PlayerSize, a); // set player's size to small
    writeData(FetchNewGameTimerFlag, a); // set flag to load game timer from header
    a = 0x01;

SecondaryGameSetup:
    y = a;
    writeData(DisableScreenFlag, a); // enable screen output
    a = 0x00;

ClearVRLoop: // clear buffer at $0300-$03ff
    x = 0x0e; // load default OAM offsets into $06e4-$06f2
    writeData(SprShuffleAmt, a);
    a = 0x58;
    writeData(SprShuffleAmt + 1, a);
    a = 0x48;
    writeData(SprShuffleAmt + 2, a);
    a = 0x38; // load sprite shuffle amounts to be used later
    pushReturnIndex(56);
    goto GetAreaMusic;
Return_56: // load proper music into queue
    M(Mirror_PPU_CTRL_REG1).rol(); // this is to set the proper PPU name table
    a.ror(); // rotate LSB of page location into carry then onto mirror
    a &= 0x01; // mask out all but LSB of page location
    M(Mirror_PPU_CTRL_REG1) >>= 1; // shift LSB of ppu register #1 mirror out
    a = M(ScreenLeft_PageLoc); // get left side page location
    writeData(BalPlatformAlignment, a); // initialize balance platform assignment flag
    a = 0xff;
    writeData(BackloadingFlag, a); // clear value here
    writeData(DisableIntermediate, a); // clear skip lives display flag
    writeData(GameTimerExpiredFlag, a); // clear game timer exp flag
    if (!z)
        goto ClearVRLoop;
    ++y;
    writeData(VRAM_Buffer1 - 1 + y, a);

ShufAmtLoop:
    y = 0x03; // set up sprite #0
    if (!n)
        goto ShufAmtLoop;
    --x; // do this until they're all set
    writeData(SprDataOffset + x, a);
    a = M(DefaultSprOffsets + x);

ISpr0Loop:
    goto Return;

//------------------------------------------------------------------------
    ++M(OperMode_Task); // increment to next task
    ++M(Sprite0HitDetectFlag); // set sprite #0 check flag
    pushReturnIndex(57);
    goto DoNothing1;
Return_57:
    pushReturnIndex(58);
    goto DoNothing2;
Return_58: // these jsrs doesn't do anything useful
    if (!n)
        goto ISpr0Loop;
    --y;
    writeData(Sprite_Data + y, a);
    a = M(Sprite0Data + y);

InitializeMemory:
    writeData(0x06, a);
    a = 0x00; // set initial low byte to start of page (at $00 of page)
    x = 0x07; // set initial high byte to $0700-$07ff

InitPageLoop:
    writeData(0x07, x);

InitByteLoop: // check to see if we're on the stack ($0100-$01ff)
    if (c)
        goto SkipByte; // if so, skip write
    compare(y, 0x60); // otherwise, check to see if we're at $0160-$01ff
    if (!z)
        goto InitByte; // if not, go ahead anyway
    compare(x, 0x01);

InitByte: // otherwise, initialize byte with current low byte in Y
    writeData(W(0x06) + y, a);

SkipByte:
    goto Return;

//------------------------------------------------------------------------
    if (!n)
        goto InitPageLoop; // do this until all pages of memory have been erased
    --x; // go onto the next page
    if (!z)
        goto InitByteLoop;
    compare(y, 0xff); // do this until all bytes in page have been erased
    --y;

GetAreaMusic:
    if (z)
        goto StoreMusic;
    compare(a, 0x07); // start position either value $06 or $07
    if (z)
        goto StoreMusic; // load music for pipe intro scene if header
    compare(a, 0x06);
    a = M(PlayerEntranceCtrl); // check value from level header for certain values
    y = 0x05; // select music for pipe intro scene by default
    if (z)
        goto ChkAreaType; // from area object data header
    compare(a, 0x02); // if found, branch without checking starting position
    a = M(AltEntranceControl); // check for specific alternate mode of entry
    if (z)
        goto ExitGetM;
    a = M(OperMode); // if in title screen mode, leave

ChkAreaType: // load area type as offset for music bit
    y = 0x04; // select music for cloud type level if found
    if (z)
        goto StoreMusic; // check for cloud type override
    a = M(CloudTypeOverride);
    y = M(AreaType);

StoreMusic: // otherwise select appropriate music for level type
    writeData(AreaMusicQueue, a); // store in queue and leave
    a = M(MusicSelectData + y);

ExitGetM:
    goto Return;

//------------------------------------------------------------------------

Entrance_GameTimerSetup:
    ++y;
    if (!z)
        goto ChkStPos; // if water type, set swimming flag, otherwise do not set
    a = M(AreaType); // check area type
    writeData(HalfwayPage, y);
    y = 0x00; // initialize halfway page
    --M(Player_CollisionBits); // initialize player's collision bits
    writeData(Player_State, a);
    a = 0x00; // set player state to on the ground by default
    writeData(Player_Y_HighPos, a);
    writeData(PlayerFacingDir, a); // set facing direction so that player faces right
    a = 0x01; // set high byte of player position and
    writeData(VerticalForceDown, a); // for fractional movement downwards if necessary
    a = 0x28; // store value here
    writeData(Player_PageLoc, a); // as page location for player
    a = M(ScreenLeft_PageLoc); // set current page for area objects

ChkStPos:
    x = M(AltYPosOffset - 2 + y); // if not 0 or 1, override $0710 with new offset in X
    if (z)
        goto SetStPos;
    compare(y, 0x01);
    if (z)
        goto SetStPos;
    y = M(AltEntranceControl); // check alternate mode of entry flag for 0 or 1
    x = M(PlayerEntranceCtrl); // get starting position loaded from header
    writeData(SwimmingFlag, y);

SetStPos: // load appropriate horizontal position
    writeData(StarInvincibleTimer, a); // clear star mario timer
    writeData(FetchNewGameTimerFlag, a); // clear flag for game timer reset
    writeData(GameTimerDisplay + 1, a); // set second digit of game timer
    a >>= 1;
    writeData(GameTimerDisplay + 2, a); // set last digit of game timer to 1
    a = 0x01;
    writeData(GameTimerDisplay, a); // use value of game timer control for first digit of game timer
    a = M(GameTimerData + y); // if game timer is set and game timer flag is also set,
    if (z)
        goto ChkOverR; // old game timer setting
    a = M(FetchNewGameTimerFlag); // do we need to set the game timer? if not, use 
    if (z)
        goto ChkOverR; // if set to zero, branch (do not use dummy byte for this)
    y = M(GameTimerSetting); // get timer control value from header
    pushReturnIndex(59);
    goto GetPlayerColors;
Return_59: // get appropriate player palette
    writeData(Player_SprAttrib, a); // set player sprite attributes using offset in X
    a = M(PlayerBGPriorityData + x);
    writeData(Player_Y_Position, a); // or value that overwrote $0710 as offset for vertical
    a = M(PlayerStarting_Y_Pos + x); // AltEntranceControl as offset for horizontal and either $0710
    writeData(Player_X_Position, a); // and vertical positions for the player, using
    a = M(PlayerStarting_X_Pos + y);

ChkOverR: // if controller bits not set, branch to skip this part
    pushReturnIndex(60);
    goto Setup_Vine;
Return_60: // do a sub to grow vine
    y = 0x00; // set offset in Y for object coordinates used earlier
    x = 0x05; // set offset in X for last enemy object buffer slot
    writeData(Block_Y_Position, a);
    a = 0xf0; // set vertical coordinate for block object
    pushReturnIndex(61);
    goto InitBlock_XY_Pos;
Return_61:
    x = 0x00; // set offset for first slot, for block object
    writeData(Player_State, a);
    a = 0x03; // set player state to climbing
    if (z)
        goto ChkSwimE;
    y = M(JoypadOverride);

ChkSwimE: // if level not water-type,
    pushReturnIndex(62);
    goto SetupBubble;
Return_62: // otherwise, execute sub to set up air bubbles
    if (!z)
        goto SetPESub; // skip this subroutine
    y = M(AreaType);

SetPESub: // set to run player entrance subroutine
    goto Return;

//------------------------------------------------------------------------
    writeData(GameEngineSubroutine, a); // on the next frame of game engine
    a = 0x07;

PlayerLoseLife:
    goto Return;

//------------------------------------------------------------------------
    writeData(OperMode, a); // and leave
    a = GameOverModeValue; // switch to game over mode
    writeData(OperMode_Task, a); // initialize mode task,
    a = 0x00;
    if (!n)
        goto StillInGame; // if player still has lives, branch
    --M(NumberofLives); // take one life from player
    writeData(EventMusicQueue, a);
    a = Silence; // silence music
    writeData(Sprite0HitDetectFlag, a);
    a = 0x00;
    ++M(DisableScreenFlag); // disable screen and sprite 0 check

StillInGame: // multiply world number by 2 and use
    ++x;
    if (z)
        goto GetHalfway; // leave offset alone
    a &= 0x02; // offset by one byte, otherwise
    a = M(LevelNumber); // if in area -3 or -4, increment
    x = a;
    a <<= 1; // as offset
    a = M(WorldNumber);

GetHalfway: // get halfway page number with offset
    a >>= 1;
    a >>= 1;
    a >>= 1; // number is -1 or -3
    a >>= 1; // move higher nybble to lower if area
    if (c)
        goto MaskHPNyb;
    a = y; // if in area -2 or -4, use lower nybble
    a >>= 1;
    a = M(LevelNumber); // check area number's LSB
    y = M(HalfwayPageNybbles + x);

MaskHPNyb: // mask out all but lower nybble
    a = 0x00; // beginning of the level
    if (!c)
        goto SetHalfway; // otherwise player must start at the
    if (z)
        goto SetHalfway; // left side of screen must be at the halfway page,
    compare(a, M(ScreenLeft_PageLoc));
    a &= BOOST_BINARY(00001111);

SetHalfway: // store as halfway page for player
    goto ContinueGame; // continue the game
    pushReturnIndex(63);
    goto TransposePlayers;
Return_63: // switch players around if 2-player game
    writeData(HalfwayPage, a);

GameOverMode:
    switch (a)
    {
    }
    a = M(OperMode_Task);

SetupGameOver:
    goto Return;

//------------------------------------------------------------------------
    ++M(OperMode_Task); // set secondary mode to 1
    ++M(DisableScreenFlag); // disable screen output
    writeData(EventMusicQueue, a); // put game over music in secondary queue
    a = GameOverMusic;
    writeData(Sprite0HitDetectFlag, a); // disable sprite 0 check
    writeData(ScreenRoutineTask, a); // and game over modes
    a = 0x00; // reset screen routine task control for title screen, game,

RunGameOver:
    if (!z)
        goto GameIsOn; // screen timer to expire
    a = M(ScreenTimer); // if not pressed, wait for
    if (!z)
        goto TerminateGame;
    a &= Start_Button;
    a = M(SavedJoypad1Bits); // check controller for start pressed
    writeData(DisableScreenFlag, a);
    a = 0x00; // reenable screen

TerminateGame:
    goto Return;

//------------------------------------------------------------------------
    writeData(OperMode, a);
    writeData(ScreenTimer, a); // leave
    writeData(OperMode_Task, a); // reset all modes to title screen and
    a <<= 1; // residual ASL instruction
    a = 0x00;
    writeData(ContinueWorld, a); // player into secret continue function variable
    a = M(WorldNumber); // otherwise put world number of current
    if (!c)
        goto ContinueGame; // going, and do so if possible
    pushReturnIndex(64);
    goto TransposePlayers;
Return_64: // check if other player can keep
    writeData(EventMusicQueue, a);
    a = Silence; // silence music

ContinueGame:
    writeData(OperMode, a); // game mode, because game is still on
    a = 0x01; // if in game over mode, switch back to
    writeData(OperMode_Task, a); // set modes and leave
    writeData(GameEngineSubroutine, a); // reset task for game core
    writeData(PlayerStatus, a);
    writeData(TimerControl, a); // also set flag for timers to count again
    a = 0x00; // game timer from header
    ++M(FetchNewGameTimerFlag); // set game timer flag to reload
    writeData(PlayerSize, a); // reset player's size, status, and
    a = 0x01; // actual world and area numbers, then
    pushReturnIndex(65);
    goto LoadAreaPointer;
Return_65: // update level pointer with

GameIsOn:
    goto Return;

//------------------------------------------------------------------------

TransposePlayers:
    x = 0x06;
    writeData(CurrentPlayer, a);
    a ^= BOOST_BINARY(00000001); // which player is on the screen
    a = M(CurrentPlayer); // invert bit to update
    if (n)
        goto ExTrans; // branch if not
    a = M(OffScr_NumberofLives); // does offscreen player have any lives left?
    if (z)
        goto ExTrans;
    a = M(NumberOfPlayers); // if only a 1 player game, leave
    c = 1; // set carry flag by default to end game

TransLoop: // transpose the information
    c = 0; // clear carry flag to get game going
    if (!n)
        goto TransLoop;
    --x;
    writeData(OffscreenPlayerInfo + x, a);
    pla();
    writeData(OnscreenPlayerInfo + x, a);
    a = M(OffscreenPlayerInfo + x); // with that of the offscreen player
    pha(); // of the onscreen player
    a = M(OnscreenPlayerInfo + x);

ExTrans:
    goto Return;

//------------------------------------------------------------------------

DoNothing1:
    writeData(0x06c9, a); // not used anywhere in the program
    a = 0xff; // this is residual code, this value is

DoNothing2:
    goto Return;

//------------------------------------------------------------------------

AreaParserTaskHandler:
    writeData(AreaParserTaskNum, y); // otherwise, set eight by default
    y = 0x08;
    if (!z)
        goto DoAPTasks; // if already set, go ahead
    y = M(AreaParserTaskNum); // check number of tasks here

DoAPTasks:
    pushReturnIndex(66);
    goto RenderAttributeTables;
Return_66:
    if (!z)
        goto SkipATRender; // render attribute table yet
    --M(AreaParserTaskNum); // if all tasks not complete do not
    pushReturnIndex(67);
    goto AreaParserTasks;
Return_67:
    a = y;
    --y;

SkipATRender:
    goto Return;

//------------------------------------------------------------------------

AreaParserTasks:
    switch (a)
    {
    }

IncrementColumnPos:
    ++M(CurrentPageLoc); // and increment page number where we're at
    writeData(CurrentColumnPos, a); // if no bits left set, wrap back to zero (0-f)
    if (!z)
        goto NoColWrap;
    a &= BOOST_BINARY(00001111); // mask out higher nybble
    a = M(CurrentColumnPos);
    ++M(CurrentColumnPos); // increment column where we're at

NoColWrap: // increment column offset where we're at
    goto Return;

//------------------------------------------------------------------------
    writeData(BlockBufferColumnPos, a); // and save
    a &= BOOST_BINARY(00011111); // mask out all but 5 LSB (0-1f)
    a = M(BlockBufferColumnPos);
    ++M(BlockBufferColumnPos);

AreaParserCore:
    pushReturnIndex(68);
    goto ProcessAreaData;
Return_68: // otherwise skip ahead and load level data
    if (z)
        goto RenderSceneryTerrain; // if not, go ahead and render background, foreground and terrain
    a = M(BackloadingFlag); // check to see if we are starting right of start

RenderSceneryTerrain:
    a = 0x00;
    x = 0x0c;

ClrMTBuf: // clear out metatile buffer
    a = M(CurrentPageLoc); // otherwise check for every third page
    if (z)
        goto RendFore; // if not, skip to check the foreground
    y = M(BackgroundScenery); // do we need to render the background scenery?
    if (!n)
        goto ClrMTBuf;
    --x;
    writeData(MetatileBuffer + x, a);

ThirdP:
    if (!n)
        goto ThirdP; // do an unconditional branch
    a -= 0x03; // if 3 or more, subtract 3 and 
    c = 1;
    if (n)
        goto RendBack; // if less than three we're there
    compare(a, 0x03);

RendBack: // move results to higher nybble
    writeData(0x00, a);
    a = 0x03; // use previously saved memory location for counter
    y = a; // use as second offset (used to determine height)
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    pla(); // get high nybble from stack, move low
    x = a; // save as offset for background scenery metatile data
    a += M(0x00); // note that since d7 was nulled, the carry flag is always clear
    a <<= 1; // multiply by three (shift to left and add result to old one)
    writeData(0x00, a); // save low nybble
    a -= 0x01; // subtract one (because low nybble is $01-$0c)
    c = 1;
    a &= 0x0f; // save to stack and clear high nybble
    pha();
    if (z)
        goto RendFore; // if zero, no scenery for that part
    a = M(BackSceneryData + x); // load data from sum of offsets
    x = a;
    a += M(CurrentColumnPos); // add to the result our current column position
    a += M(BSceneDataOffsets - 1 + y); // add to it offset loaded from here
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;

SceLoop1: // load metatile data from offset of (lsb - 1) * 3
    if (!z)
        goto SceLoop1;
    --M(0x00); // decrement until counter expires, barring exception
    if (z)
        goto RendFore;
    compare(y, 0x0b); // if at this location, leave loop
    ++y;
    ++x;
    writeData(MetatileBuffer + y, a); // store into buffer from offset of (msb / 16)
    a = M(BackSceneryMetatiles + x);

RendFore: // check for foreground data needed or not
    x = 0x00; // reinit X
    y = M(FSceneDataOffsets - 1 + x); // load offset from location offset by header value, then
    if (z)
        goto RendTerr; // if not, skip this part
    x = M(ForegroundScenery);

SceLoop2: // load data until counter expires
    writeData(MetatileBuffer + x, a);
    if (z)
        goto NoFore; // do not store if zero found
    a = M(ForeSceneryData + y);

NoFore:
    if (!z)
        goto SceLoop2;
    compare(x, 0x0d); // store up to end of metatile buffer
    ++x;
    ++y;

RendTerr: // check world type for water level
    goto StoreMT; // use castle wall metatile as terrain type
    a = 0x62; // if set as water level and world number eight,
    if (!z)
        goto TerMTile;
    compare(a, World8); // then skip this part
    a = M(WorldNumber); // check world number, if not world number eight
    if (!z)
        goto TerMTile; // if not water level, skip this part
    y = M(AreaType);

TerMTile: // otherwise get appropriate metatile for area type
    a = 0x88; // use cloud block terrain
    if (z)
        goto StoreMT; // if not set, keep value otherwise
    y = M(CloudTypeOverride); // check for cloud type override
    a = M(TerrainMetatiles + y);

StoreMT: // store value here
    y = a;
    a <<= 1; // multiply by 2 and use as yet another offset
    a = M(TerrainControl); // use yet another value from the header
    x = 0x00; // initialize X, use as metatile buffer offset
    writeData(0x07, a);

TerrLoop: // get one of the terrain rendering bit data
    writeData(0x00, a);
    a &= BOOST_BINARY(00001000);
    a = M(0x00); // if not, mask out all but d3
    if (z)
        goto NoCloud2;
    compare(x, 0x00); // otherwise, check if we're doing the ceiling byte
    if (z)
        goto NoCloud2;
    a = M(CloudTypeOverride); // skip if value here is zero
    writeData(0x01, y);
    ++y; // increment Y and use as offset next time around
    writeData(0x00, a);
    a = M(TerrainRenderBits + y);

NoCloud2: // start at beginning of bitmasks
    y = 0x00;

TerrBChk: // load bitmask, then perform AND on contents of first byte
    writeData(MetatileBuffer + x, a); // load terrain type metatile number and store into buffer here
    a = M(0x07);
    if (z)
        goto NextTBit; // if not set, skip this part (do not write terrain to buffer)
    bit(M(0x00));
    a = M(Bitmasks + y);

NextTBit: // continue until end of buffer
    writeData(0x07, a);
    a = 0x54; // old terrain type with ground level terrain type
    if (!z)
        goto EndUChk; // if we're at the bottom of the screen, override
    compare(x, 0x0b);
    if (!z)
        goto EndUChk; // if not underground, skip this part
    compare(a, 0x02);
    a = M(AreaType); // check world type for underground area
    if (z)
        goto RendBBuf; // if we're at the end, break out of this loop
    compare(x, 0x0d);
    ++x;

EndUChk: // increment bitmasks offset in Y
    if (!z)
        goto TerrLoop; // unconditional branch, use Y to load next byte
    y = M(0x01);
    if (!z)
        goto TerrBChk; // if not all bits checked, loop back    
    compare(y, 0x08);
    ++y;

RendBBuf: // do the area data loading routine now
    y = 0x00; // init index regs and start at beginning of smaller buffer
    x = 0x00;
    pushReturnIndex(69);
    goto GetBlockBufferAddr;
Return_69: // get block buffer address from where we're at
    a = M(BlockBufferColumnPos);
    pushReturnIndex(70);
    goto ProcessAreaData;
Return_70:

ChkMTLow:
    a = 0x00; // if less, init value before storing
    if (c)
        goto StrBlock; // if equal or greater, branch
    compare(a, M(BlockBuffLowBounds + y)); // check for certain values depending on bits set
    a = M(MetatileBuffer + x); // reload original unmasked value here
    y = a; // use as offset in Y
    a.rol();
    a.rol(); // make %xx000000 into %000000xx
    a <<= 1;
    a &= BOOST_BINARY(11000000); // mask out all but 2 MSB
    a = M(MetatileBuffer + x); // load stored metatile number
    writeData(0x00, y);

StrBlock: // get offset for block buffer
    goto Return;

//------------------------------------------------------------------------
    if (!c)
        goto ChkMTLow; // continue until we pass last row, then leave
    compare(x, 0x0d);
    ++x; // increment column value
    y = a;
    a += 0x10;
    c = 0; // add 16 (move down one row) to offset
    a = y;
    writeData(W(0x06) + y, a); // store value into block buffer
    y = M(0x00);

ProcessAreaData:
    x = 0x02; // start at the end of area object buffer

ProcADLoop:
    ++M(AreaObjectPageLoc); // and increment page location
    ++M(AreaObjectPageSel); // if not already set, set it now
    if (!z)
        goto Chk1Row13;
    a = M(AreaObjectPageSel); // check page select
    if (!c)
        goto Chk1Row13;
    a <<= 1; // check for page select bit (d7), branch if not set
    a = M(W(AreaData) + y); // get second byte of area object
    ++y;
    if (!n)
        goto RdyDecode; // if buffer not negative, branch, otherwise
    a = M(AreaObjectLength + x); // check area object buffer flag
    if (z)
        goto RdyDecode;
    compare(a, 0xfd); // if end-of-area, skip all this crap
    a = M(W(AreaData) + y); // get first byte of area object
    y = M(AreaDataOffset); // get offset of area data pointer
    writeData(BehindAreaParserFlag, a);
    a = 0x00; // reset flag
    writeData(ObjectOffset, x);

Chk1Row13:
    goto NextAObj;
    ++M(AreaObjectPageSel); // increment page select
    writeData(AreaObjectPageLoc, a);
    a &= BOOST_BINARY(00011111); // mask out all but 5 LSB and store in page control
    a = M(W(AreaData) + y);
    ++y; // if d6 not set, reread second byte
    if (!z)
        goto CheckRear;
    a = M(AreaObjectPageSel); // if page select is set, do not reread
    if (!z)
        goto CheckRear;
    a &= BOOST_BINARY(01000000); // check for d6 set (if not, object is page control)
    --y; // decrement to get ready to read first byte
    a = M(W(AreaData) + y);
    ++y; // if so, reread second byte of level object
    if (!z)
        goto Chk1Row14;
    compare(a, 0x0d); // row 13?
    a &= 0x0f; // mask out high nybble
    a = M(W(AreaData) + y); // reread first byte of level object
    --y;

Chk1Row14: // row 14?
    if (!z)
        goto RdyDecode; // to render the object (otherwise bg might not look right)
    a = M(BackloadingFlag); // check flag for saved page number and branch if set
    if (!z)
        goto CheckRear;
    compare(a, 0x0e);

CheckRear: // check to see if current page of level object is
    if (!c)
        goto SetBehind; // if so branch
    compare(a, M(CurrentPageLoc)); // behind current page of renderer
    a = M(AreaObjectPageLoc);

RdyDecode: // do sub and do not turn on flag
    goto ChkLength;
    pushReturnIndex(71);
    goto DecodeAreaData;
Return_71:

SetBehind: // turn on flag if object is behind renderer
    ++M(BehindAreaParserFlag);

NextAObj: // increment buffer offset and move on
    pushReturnIndex(72);
    goto IncAreaObjOffset;
Return_72:

ChkLength: // get buffer offset
    --M(AreaObjectLength + x); // otherwise decrement length or get rid of it
    if (n)
        goto ProcLoopb; // if not, branch to handle loopback
    a = M(AreaObjectLength + x); // check object length for anything stored here
    x = M(ObjectOffset);

ProcLoopb: // decrement buffer offset
    if (!z)
        goto ProcessAreaData; // branch if true to load more level data, otherwise leave
    a = M(BackloadingFlag); // check for flag set if starting right of page $00
    if (!z)
        goto ProcessAreaData; // branch if true to load more level data, otherwise
    a = M(BehindAreaParserFlag); // check for flag set if objects were behind renderer
    if (!n)
        goto ProcADLoop; // and loopback unless exceeded buffer
    --x;

EndAParse:
    goto Return;

//------------------------------------------------------------------------

IncAreaObjOffset:
    goto Return;

//------------------------------------------------------------------------
    writeData(AreaObjectPageSel, a);
    a = 0x00; // reset page select
    ++M(AreaDataOffset);
    ++M(AreaDataOffset); // increment offset of level pointer

DecodeAreaData:
    y = M(AreaObjOffsetBuffer + x); // if not, get offset from buffer
    if (n)
        goto Chk1stB;
    a = M(AreaObjectLength + x); // check current buffer flag

Chk1stB: // load offset of 16 for special row 15
    x = 0x00; // otherwise nullify value by default
    if (z)
        goto ChkRow14; // if so, keep the offset value of 8
    compare(a, 0x0c); // row 12?
    x = 0x08; // otherwise load offset of 8 for special row 12
    if (z)
        goto ChkRow14; // if so, keep the offset of 16
    compare(a, 0x0f); // row 15?
    a &= 0x0f; // otherwise, mask out low nybble
    if (z)
        goto EndAParse; // if end of level, leave this routine
    compare(a, 0xfd);
    a = M(W(AreaData) + y); // get first byte of level object again
    x = 0x10;

ChkRow14: // store whatever value we just loaded here
    if (!z)
        goto NormObj; // unconditional branch
    a = 0x2e; // and load A with another value
    writeData(0x07, a);
    a = 0x00; // if so, load offset with $00
    if (!z)
        goto ChkRow13;
    compare(a, 0x0e); // row 14?
    x = M(ObjectOffset); // get object offset again
    writeData(0x07, x);

ChkRow13: // row 13?
    ++M(LoopCommand); // if loop command, set loop command flag
    if (!z)
        goto Mask2MSB; // (plus d6 set for object other than page control)
    compare(a, 0x4b); // check for loop command in low nybble
    a &= BOOST_BINARY(01111111); // mask out d7
    a = M(W(AreaData) + y); // otherwise, get byte again
    if (z)
        goto LeavePar; // if d6 clear, branch to leave (we handled this earlier)
    a &= BOOST_BINARY(01000000); // mask out all but d6 (page control obj bit)
    a = M(W(AreaData) + y);
    ++y; // get next byte
    writeData(0x07, a);
    a = 0x22; // if so, load offset with 34
    if (!z)
        goto ChkSRows;
    compare(a, 0x0d);

Mask2MSB: // mask out d7 and d6
    goto NormObj; // and jump
    a &= BOOST_BINARY(00111111);

ChkSRows: // row 12-15?
    goto NormObj;
    a &= BOOST_BINARY(00001111); // mask out higher nybble and jump
    a = M(W(AreaData) + y); // reload second byte of level object
    writeData(0x07, a); // otherwise set offset of 24 for small object
    a = 0x16;
    if (!z)
        goto LrgObj; // if any bits set, branch to handle large object
    a &= BOOST_BINARY(01110000); // mask out all but d6-d4
    a = M(W(AreaData) + y);
    ++y; // if not, get second byte of level object
    if (c)
        goto SpecObj;
    compare(a, 0x0c);

LrgObj: // store value here (branch for large objects)
    writeData(0x00, a);
    a = 0x00; // otherwise, nullify value for warp pipe
    if (z)
        goto NotWPipe; // if d3 clear, branch to get original value
    a &= BOOST_BINARY(00001000); // mask out all but d3 (usage control bit)
    a = M(W(AreaData) + y); // if not, reload second byte
    if (!z)
        goto NotWPipe;
    compare(a, 0x70); // check for vertical pipe object
    writeData(0x00, a);

NotWPipe: // get value and jump ahead
    goto MoveAOId;
    a = M(0x00);

SpecObj: // branch here for rows 12-15
    a &= BOOST_BINARY(01110000); // get next byte and mask out all but d6-d4
    a = M(W(AreaData) + y);
    ++y;

MoveAOId: // move d6-d4 to lower nybble
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;

NormObj: // store value here (branch for small objects and rows 13 and 14)
    if (!z)
        goto StrAObj; // if set, branch to render object, else leave
    a = M(BackloadingFlag); // if so, check backloading flag
    if (!z)
        goto LeavePar;
    compare(a, 0x0e); // row 14?
    a &= BOOST_BINARY(00001111);
    a = M(W(AreaData) + y); // and reload first byte
    y = M(AreaDataOffset); // if not, get old offset of level pointer
    if (z)
        goto InitRear;
    compare(a, M(CurrentPageLoc)); // same page as the renderer, and if so, branch
    a = M(AreaObjectPageLoc); // otherwise check to see if the object we've loaded is on the
    if (!n)
        goto RunAObj; // if so, branch to do its particular sub
    a = M(AreaObjectLength + x); // is there something stored here already?
    writeData(0x00, a);

LeavePar:
    goto Return;

//------------------------------------------------------------------------

InitRear: // check backloading flag to see if it's been initialized
    writeData(ObjectOffset, a);
    writeData(BehindAreaParserFlag, a);
    writeData(BackloadingFlag, a); // behind-renderer flags and leave
    a = 0x00; // if not, initialize both backloading and 
    if (z)
        goto BackColC; // branch to column-wise check
    a = M(BackloadingFlag);

LoopCmdE:
    goto Return;

//------------------------------------------------------------------------

BackColC: // get first byte again
    if (!z)
        goto LeavePar; // if not, branch to leave
    compare(a, M(CurrentColumnPos)); // is this where we're at?
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a &= BOOST_BINARY(11110000); // mask out low nybble and move high to low
    a = M(W(AreaData) + y);
    y = M(AreaDataOffset);

StrAObj: // if so, load area obj offset and store in buffer
    pushReturnIndex(73);
    goto IncAreaObjOffset;
Return_73: // do sub to increment to next object data
    writeData(AreaObjOffsetBuffer + x, a);
    a = M(AreaDataOffset);

RunAObj: // get stored value and add offset to it
    switch (a)
    {
    }
    a += M(0x07);
    c = 0; // then use the jump engine with current contents of A
    a = M(0x00);

AlterAreaAttributes:
    goto Return;

//------------------------------------------------------------------------
    writeData(BackgroundScenery, a); // then leave
    a >>= 1;
    a >>= 1;
    a >>= 1; // as new background scenery bits
    a >>= 1; // move bits to lower nybble and store
    a &= BOOST_BINARY(00110000); // pull and mask out all but d5 and d4
    pla();
    writeData(TerrainControl, a); // new terrain height type bits
    a &= BOOST_BINARY(00001111); // mask out high nybble and store as
    pha(); // pull and push offset to copy to A
    pla();
    if (!z)
        goto Alter2; // branch if d6 is set
    a &= BOOST_BINARY(01000000);
    pha(); // save in stack for now
    a = M(W(AreaData) + y);
    ++y; // load second byte
    y = M(AreaObjOffsetBuffer + x); // load offset for level object data saved in buffer

Alter2:
    a = 0x00;
    writeData(BackgroundColorCtrl, a);
    if (!c)
        goto SetFore; // and nullify foreground scenery bits
    compare(a, 0x04); // if four or greater, set color control bits
    a &= BOOST_BINARY(00000111); // mask out all but 3 LSB
    pla();

SetFore: // otherwise set new foreground scenery bits
    goto Return;

//------------------------------------------------------------------------
    writeData(ForegroundScenery, a);

ScrollLockObject_Warp:
    ++x; // (8-7-6) and move on
    if (!z)
        goto WarpNum; // if ground area type, increment for last warp zone
    --y;
    y = M(AreaType); // check area type
    ++x; // if world number > 1, increment for next warp zone (5)
    if (z)
        goto WarpNum;
    a = M(WorldNumber); // warp zone (4-3-2), then check world number
    x = 0x04; // load value of 4 for game text routine as default

WarpNum:
    pushReturnIndex(74);
    goto KillEnemies;
Return_74: // load identifier for piranha plants and do sub
    a = PiranhaPlant;
    pushReturnIndex(75);
    goto WriteGameText;
Return_75: // print text and warp zone numbers
    writeData(WarpZoneControl, a); // store number here to be used by warp zone routine
    a = x;

ScrollLockObject:
    goto Return;

//------------------------------------------------------------------------
    writeData(ScrollLock, a);
    a ^= BOOST_BINARY(00000001);
    a = M(ScrollLock); // invert scroll lock to turn it on

KillEnemies:
    x = 0x04; // check for identifier in enemy object buffer
    a = 0x00;
    writeData(0x00, a); // store identifier here

KillELoop:
    writeData(Enemy_Flag + x, a); // if found, deactivate enemy object flag
    if (!z)
        goto NoKillE;
    compare(y, M(0x00)); // if not found, branch
    y = M(Enemy_ID + x);

NoKillE: // do this until all slots are checked
    goto Return;

//------------------------------------------------------------------------
    if (!n)
        goto KillELoop;
    --x;

AreaFrenzy: // use area object identifier bit as offset
    y = 0x05;
    a = M(FrenzyIDData - 8 + x); // note that it starts at 8, thus weird address here
    x = M(0x00);

FreCompLoop: // check regular slots of enemy object buffer
    a = 0x00; // if enemy object already present, nullify queue and leave
    if (!z)
        goto FreCompLoop;
    compare(a, M(Enemy_ID + y)); // check for enemy object in buffer versus frenzy object
    if (n)
        goto ExitAFrenzy; // if all slots checked and enemy object not found, branch to store
    --y;

ExitAFrenzy: // store enemy into frenzy queue
    goto Return;

//------------------------------------------------------------------------
    writeData(EnemyFrenzyQueue, a);

AreaStyleObject:
    switch (a)
    {
    }
    a = M(AreaStyle); // load level object style and jump to the right sub

TreeLedge:
    goto NoUnder;
    a = 0x16; // render start of tree ledge
    if (z)
        goto MidTreeL;
    a |= M(CurrentColumnPos); // are we at the start of the level?
    a = M(CurrentPageLoc);
    writeData(AreaObjectLength + x, a); // store lower nybble into buffer flag as length of ledge
    a = y;
    if (!n)
        goto MidTreeL;
    if (z)
        goto EndTreeL;
    a = M(AreaObjectLength + x); // check length counter for expiration
    pushReturnIndex(76);
    goto GetLrgObjAttrib;
Return_76: // get row and length of green ledge

MidTreeL:
    goto AllUnder; // now render the part underneath
    a = 0x4c; // at the start of level for continuous effect
    writeData(MetatileBuffer + x, a); // note that this is also used if ledge position is
    a = 0x17; // render middle of tree ledge
    x = M(0x07);

EndTreeL: // render end of tree ledge
    goto NoUnder;
    a = 0x18;

MushroomLedge:
    goto NoUnder;
    a = 0x19; // render start of mushroom
    writeData(MushroomLedgeHalfLen + x, a);
    a >>= 1;
    a = M(AreaObjectLength + x); // divide length by 2 and store elsewhere
    if (!c)
        goto EndMushL;
    writeData(0x06, y); // store length here for now
    pushReturnIndex(77);
    goto ChkLrgObjLength;
Return_77: // get shroom dimensions

EndMushL: // if at the end, render end of mushroom
    a = 0x50;
    writeData(MetatileBuffer + x, a); // render stem top of mushroom underneath the middle
    a = 0x4f;
    ++x;
    if (!z)
        goto MushLExit; // if not, branch to leave
    compare(y, M(0x06)); // are we smack dab in the center?
    writeData(MetatileBuffer + x, a); // render middle of mushroom
    a = 0x1a;
    x = M(0x07);
    writeData(0x06, a); // was stored originally
    a = M(MushroomLedgeHalfLen + x); // get divided length and store where length
    if (z)
        goto NoUnder;
    y = M(AreaObjectLength + x);
    a = 0x1b;

AllUnder:
    goto RenderUnderPart; // now render the stem of mushroom
    y = 0x0f; // set $0f to render all way down
    ++x;

NoUnder: // load row of ledge
    goto RenderUnderPart;
    y = 0x00; // set 0 for no bottom on this part
    x = M(0x07);

PulleyRopeObject:
    ++y; // otherwise render right pulley
    if (!z)
        goto RenderPul;
    a = M(AreaObjectLength + x); // if not at the end, render rope
    ++y;
    if (c)
        goto RenderPul; // if starting, render left pulley
    y = 0x00; // initialize metatile offset
    pushReturnIndex(78);
    goto ChkLrgObjLength;
Return_78: // get length of pulley/rope object

RenderPul:
    writeData(MetatileBuffer, a); // render at the top of the screen
    a = M(PulleyRopeMetatiles + y);

MushLExit: // and leave
    goto Return;

//------------------------------------------------------------------------

CastleObject:
    writeData(0x06, a); // load upper limit of number of rows to print
    a = 0x0b;
    x = M(0x07); // begin at starting row
    y = M(AreaObjectLength + x); // use current length as offset for castle data
    pha(); // save obj buffer offset to stack
    a = x;
    pushReturnIndex(79);
    goto ChkLrgObjFixedLength;
Return_79: // load length of castle if not already loaded
    y = 0x04;
    writeData(0x07, y); // if starting row is above $0a, game will crash!!!
    pushReturnIndex(80);
    goto GetLrgObjAttrib;
Return_80: // save lower nybble as starting row

CRendLoop: // load current byte using offset
    --M(0x06); // move closer to upper limit
    ++y;
    ++y;
    ++y;
    ++y; // to byte in next row
    ++y; // if not, increment column-wise
    if (z)
        goto ChkCFloor; // have we reached upper limit yet?
    a = M(0x06);
    ++x; // store in buffer and increment buffer offset
    writeData(MetatileBuffer + x, a);
    a = M(CastleMetatiles + y);

ChkCFloor: // have we reached the row just before floor?
    if (z)
        goto PlayerStop;
    compare(a, 0x03); // if found, then check to see if we're at the second column
    if (!z)
        goto NotTall;
    y = M(0x07); // check starting row for tall castle ($00)
    if (z)
        goto PlayerStop;
    compare(a, 0x01); // if length almost about to expire, put brick at floor
    a = M(AreaObjectLength + x); // check length
    if (z)
        goto ExitCastle; // if we're at page 0, we do not need to do anything else
    a = M(CurrentPageLoc);
    x = a; // get obj buffer offset from before
    pla();
    if (!z)
        goto CRendLoop; // if not, go back and do another row
    compare(x, 0x0b);

NotTall: // if not tall castle, check to see if we're at the third column
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_ID + x, a);
    a = StarFlagObject; // set star flag value in buffer itself
    writeData(Enemy_Y_Position + x, a); // set vertical coordinate
    a = 0x90;
    writeData(Enemy_Flag + x, a); // set flag for buffer
    writeData(Enemy_Y_HighPos + x, a); // set vertical high byte
    a = 0x01;
    writeData(Enemy_PageLoc + x, a); // set page location for star flag
    a = M(CurrentPageLoc);
    writeData(Enemy_X_Position + x, a); // then write horizontal coordinate for star flag
    pla();
    pushReturnIndex(81);
    goto FindEmptyEnemySlot;
Return_81: // find an empty place on the enemy object buffer
    pha();
    pushReturnIndex(82);
    goto GetAreaObjXPosition;
Return_82: // otherwise, obtain and save horizontal pixel coordinate
    if (!z)
        goto ExitCastle; // if we aren't and the castle is tall, don't create flag yet
    compare(a, 0x02);

PlayerStop: // put brick at floor to stop player at end of level
    writeData(MetatileBuffer + 10, y); // this is only done if we're on the second column
    y = 0x52;

ExitCastle:
    goto Return;

//------------------------------------------------------------------------

WaterPipe:
    goto Return;

//------------------------------------------------------------------------
    writeData(MetatileBuffer + 1 + x, a);
    a = 0x6c;
    writeData(MetatileBuffer + x, a); // draw something here and below it
    a = 0x6b;
    x = M(0x07); // get row
    y = M(AreaObjectLength + x); // get length (residual code, water pipe is 1 col thick)
    pushReturnIndex(83);
    goto GetLrgObjAttrib;
Return_83: // get row and lower nybble

IntroPipe:
    x = 0x06; // blank everything above the vertical pipe part
    if (c)
        goto NoBlankP; // if carry flag set, not time to draw vertical pipe part
    pushReturnIndex(84);
    goto RenderSidewaysPipe;
Return_84:
    y = 0x0a; // set fixed value and render the sideways part
    pushReturnIndex(85);
    goto ChkLrgObjFixedLength;
Return_85:
    y = 0x03; // check if length set, if not set, set it

VPipeSectLoop: // all the way to the top of the screen
    writeData(MetatileBuffer + 7, a);
    a = M(VerticalPipeData + y); // draw the end of the vertical pipe part
    if (!n)
        goto VPipeSectLoop;
    --x;
    writeData(MetatileBuffer + x, a); // because otherwise it will look like exit pipe
    a = 0x00;

NoBlankP:
    goto Return;

//------------------------------------------------------------------------

ExitPipe:
    pushReturnIndex(86);
    goto GetLrgObjAttrib;
Return_86: // get vertical length, then plow on through RenderSidewaysPipe
    pushReturnIndex(87);
    goto ChkLrgObjFixedLength;
Return_87:
    y = 0x03; // check if length set, if not set, set it

RenderSidewaysPipe:
    c = 0; // clear carry flag to be used by IntroPipe
    pushReturnIndex(88);
    goto RenderUnderPart;
Return_88: // and render vertical shaft using tile number in A
    y = M(0x05); // init buffer offset and get vertical length
    x = 0x00;
    if (z)
        goto DrawSidePart; // if found, do not draw the vertical pipe shaft
    compare(a, 0x00);
    a = M(SidePipeShaftData + y); // check for value $00 based on horizontal offset
    ++x;
    x = M(0x05); // get vertical length plus one, use as buffer offset
    writeData(0x06, y);
    y = M(AreaObjectLength + x); // get length left over and store here
    writeData(0x05, y);
    --y; // and store here for now as vertical length
    --y; // decrement twice to make room for shaft at bottom

DrawSidePart: // render side pipe part at the bottom
    goto Return;

//------------------------------------------------------------------------
    writeData(MetatileBuffer + 1 + x, a);
    a = M(SidePipeBottomPart + y); // backwards horizontally
    writeData(MetatileBuffer + x, a); // note that the pipe parts are stored
    a = M(SidePipeTopPart + y);
    y = M(0x06);

VerticalPipe:
    ++y; // add four if usage control bit was not set
    ++y;
    ++y;
    ++y;
    if (z)
        goto WarpPipe; // (if d3, the usage control bit of second byte, was set)
    a = M(0x00); // check to see if value was nullified earlier
    pushReturnIndex(89);
    goto GetPipeHeight;
Return_89:

WarpPipe: // save value in stack
    pushReturnIndex(90);
    goto InitPiranhaPlant;
Return_90:
    writeData(Enemy_ID + x, a);
    a = PiranhaPlant; // write piranha plant's value into buffer
    writeData(Enemy_Y_Position + x, a);
    pushReturnIndex(91);
    goto GetAreaObjYPosition;
Return_91: // get piranha plant's vertical coordinate and store here
    writeData(Enemy_Flag + x, a); // activate enemy flag
    writeData(Enemy_Y_HighPos + x, a);
    a = 0x01;
    writeData(Enemy_PageLoc + x, a); // store as enemy's page coordinate
    a += 0x00;
    a = M(CurrentPageLoc); // add carry to current page number
    writeData(Enemy_X_Position + x, a); // store as enemy's horizontal coordinate
    a += 0x08; // add eight to put the piranha plant in the center
    c = 0;
    pushReturnIndex(92);
    goto GetAreaObjXPosition;
Return_92: // get horizontal pixel coordinate
    if (c)
        goto DrawPipe; // if not found, too many enemies, thus skip
    pushReturnIndex(93);
    goto FindEmptyEnemySlot;
Return_93: // check for an empty moving data buffer space
    if (z)
        goto DrawPipe; // (because we only need to do this once)
    y = M(AreaObjectLength + x); // if on second column of pipe, branch
    if (z)
        goto DrawPipe;
    a |= M(WorldNumber); // if at world 1-1, do not add piranha plant ever
    a = M(AreaNumber);
    pha();
    a = y;

DrawPipe: // get value saved earlier and use as Y
    goto RenderUnderPart;
    --y;
    y = M(0x06); // subtract one from length and render the part underneath
    a = M(VerticalPipeData + 2 + y); // render the rest of the pipe
    ++x;
    writeData(MetatileBuffer + x, a); // render the top of the pipe
    a = M(VerticalPipeData + y); // draw the appropriate pipe with the Y we loaded earlier
    x = M(0x07); // get buffer offset
    y = a;
    pla();

GetPipeHeight:
    goto Return;

//------------------------------------------------------------------------
    y = M(AreaObjectLength + x); // length left over
    writeData(0x06, a); // vertical length, then load Y with
    a &= 0x07; // save only the three lower bits as
    a = y; // get saved lower nybble as height
    pushReturnIndex(94);
    goto GetLrgObjAttrib;
Return_94:
    pushReturnIndex(95);
    goto ChkLrgObjFixedLength;
Return_95: // pipe length of 2 (horizontal)
    y = 0x01; // check for length loaded, if not, load

FindEmptyEnemySlot:
    x = 0x00; // start at first enemy slot

EmptyChkLoop: // clear carry flag by default
    if (!z)
        goto EmptyChkLoop;
    compare(x, 0x05); // if nonzero, check next value
    ++x;
    if (z)
        goto ExitEmptyChk; // if zero, leave
    a = M(Enemy_Flag + x); // check enemy buffer for nonzero
    c = 0;

ExitEmptyChk: // if all values nonzero, carry flag is set
    goto Return;

//------------------------------------------------------------------------

Hole_Water:
    goto RenderUnderPart;
    a = 0x87;
    y = 0x01; // now render the water underneath
    x = 0x0b;
    writeData(MetatileBuffer + 10, a);
    a = 0x86; // render waves
    pushReturnIndex(96);
    goto ChkLrgObjLength;
Return_96: // get low nybble and save as length

QuestionBlockRow_High:
    goto Skip_1;
    a = 0x03; // start on the fourth row
Skip_1:

QuestionBlockRow_Low:
    goto Return;

//------------------------------------------------------------------------
    writeData(MetatileBuffer + x, a);
    a = 0xc0;
    x = a; // render question boxes with coins
    pla();
    pushReturnIndex(97);
    goto ChkLrgObjLength;
Return_97: // get low nybble and save as length
    pha(); // save whatever row to the stack for now
    a = 0x07; // start on the eighth row

Bridge_High:
    goto Skip_2;
    a = 0x06; // start on the seventh row from top of screen
Skip_2:

Bridge_Middle:
    goto Skip_3;
    a = 0x07; // start on the eighth row
Skip_3:

Bridge_Low:
    goto RenderUnderPart;
    a = 0x63;
    y = 0x00; // now render the bridge itself
    ++x;
    writeData(MetatileBuffer + x, a);
    a = 0x0b;
    x = a; // render bridge railing
    pla();
    pushReturnIndex(98);
    goto ChkLrgObjLength;
Return_98: // get low nybble and save as length
    pha(); // save whatever row to the stack for now
    a = 0x09; // start on the tenth row

FlagBalls_Residual:
    goto RenderUnderPart;
    a = 0x6d; // of screen downwards based on low nybble
    x = 0x02; // render flag balls on third row from top
    pushReturnIndex(99);
    goto GetLrgObjAttrib;
Return_99: // get low nybble from object byte

FlagpoleObject:
    goto Return;

//------------------------------------------------------------------------
    ++M(Enemy_Flag + 5); // use last space in enemy object buffer
    writeData(Enemy_ID + 5, a); // set flag identifier, note that identifier and coordinates
    a = FlagpoleFlagObject;
    writeData(FlagpoleFNum_Y_Pos, a); // set initial vertical coordinate for flagpole's floatey number
    a = 0xb0;
    writeData(Enemy_Y_Position + 5, a); // set vertical coordinate for flag
    a = 0x30;
    writeData(Enemy_PageLoc + 5, a); // page location for the flag
    a -= 0x00; // subtract borrow from page location and use as
    a = M(CurrentPageLoc);
    writeData(Enemy_X_Position + 5, a); // coordinate for the flag
    a -= 0x08; // subtract eight pixels and use as horizontal
    c = 1; // get pixel coordinate of where the flagpole is,
    pushReturnIndex(100);
    goto GetAreaObjXPosition;
Return_100:
    writeData(MetatileBuffer + 10, a);
    a = 0x61; // render solid block at the bottom
    pushReturnIndex(101);
    goto RenderUnderPart;
Return_101:
    a = 0x25;
    y = 0x08;
    x = 0x01; // now render the flagpole shaft
    writeData(MetatileBuffer, a);
    a = 0x24; // render flagpole ball on top

EndlessRope:
    goto DrawRope;
    y = 0x0f;
    x = 0x00; // render rope from the top to the bottom of screen

BalancePlatRope:
    x = 0x01;
    pushReturnIndex(102);
    goto GetLrgObjAttrib;
Return_102: // get vertical length from lower nybble
    x = a;
    pla(); // get back object buffer offset
    pushReturnIndex(103);
    goto RenderUnderPart;
Return_103:
    a = 0x44;
    y = 0x0f; // with blank used for balance platform rope
    x = 0x01; // blank out all from second row to the bottom
    pha();
    a = x; // save object buffer offset for now

DrawRope: // render the actual rope
    goto RenderUnderPart;
    a = 0x40;

RowOfCoins:
    goto GetRow;
    a = M(CoinMetatileData + y); // load appropriate coin metatile
    y = M(AreaType); // get area type

CastleBridgeObj:
    goto ChainObj;
    pushReturnIndex(104);
    goto ChkLrgObjFixedLength;
Return_104:
    y = 0x0c; // load length of 13 columns

AxeObj:
    writeData(VRAM_Buffer_AddrCtrl, a);
    a = 0x08; // load bowser's palette into sprite portion of palette

ChainObj:
    goto ColObj;
    a = M(C_ObjectMetatile - 2 + y);
    x = M(C_ObjectRow - 2 + y); // get appropriate row and metatile for object
    y = M(0x00); // get value loaded earlier from decoder

EmptyBlock:
    a = 0xc4;
    x = M(0x07);
    pushReturnIndex(105);
    goto GetLrgObjAttrib;
Return_105: // get row location

ColObj: // column length of 1
    goto RenderUnderPart;
    y = 0x00;

RowOfBricks:
    y = 0x04; // if cloud type, override area type
    if (z)
        goto DrawBricks;
    a = M(CloudTypeOverride); // check for cloud type override
    y = M(AreaType); // load area type obtained from area offset pointer

DrawBricks: // get appropriate metatile
    goto GetRow; // and go render it
    a = M(BrickMetatiles + y);

RowOfSolidBlocks:
    a = M(SolidBlockMetatiles + y); // get metatile
    y = M(AreaType); // load area type obtained from area offset pointer

GetRow: // store metatile here
    pushReturnIndex(106);
    goto ChkLrgObjLength;
Return_106: // get row number, load length
    pha();

DrawRow:
    goto RenderUnderPart; // render object
    pla();
    y = 0x00; // set vertical height of 1
    x = M(0x07);

ColumnOfBricks:
    goto GetRow2;
    a = M(BrickMetatiles + y); // get metatile (no cloud override as for row)
    y = M(AreaType); // load area type obtained from area offset

ColumnOfSolidBlocks:
    a = M(SolidBlockMetatiles + y); // get metatile
    y = M(AreaType); // load area type obtained from area offset

GetRow2: // save metatile to stack for now
    goto RenderUnderPart; // now render the column
    x = M(0x07); // get starting row
    pla(); // restore metatile
    pushReturnIndex(107);
    goto GetLrgObjAttrib;
Return_107: // get length and row
    pha();

BulletBillCannon:
    pushReturnIndex(108);
    goto RenderUnderPart;
Return_108:
    a = 0x66; // if not, render bottom until length expires
    if (n)
        goto SetupCannon;
    --y; // done yet?
    ++x;
    writeData(MetatileBuffer + x, a);
    a = 0x65; // if not, render middle part
    if (n)
        goto SetupCannon;
    --y; // done yet?
    ++x;
    writeData(MetatileBuffer + x, a);
    a = 0x64; // render bullet bill cannon
    x = M(0x07); // start at first row
    pushReturnIndex(109);
    goto GetLrgObjAttrib;
Return_109: // get row and length of bullet bill cannon

SetupCannon: // get offset for data used by cannons and whirlpools
    x = 0x00; // otherwise initialize it
    if (!c)
        goto StrCOffset; // if not yet reached sixth cannon, branch to save offset
    compare(x, 0x06); // increment and check offset
    ++x;
    writeData(Cannon_X_Position + x, a); // and store it here
    pushReturnIndex(110);
    goto GetAreaObjXPosition;
Return_110: // get proper horizontal coordinate for cannon
    writeData(Cannon_PageLoc + x, a); // store page number for cannon here
    a = M(CurrentPageLoc);
    writeData(Cannon_Y_Position + x, a); // and store it here
    pushReturnIndex(111);
    goto GetAreaObjYPosition;
Return_111: // get proper vertical coordinate for cannon
    x = M(Cannon_Offset);

StrCOffset: // save new offset and leave
    goto Return;

//------------------------------------------------------------------------
    writeData(Cannon_Offset, x);

StaircaseObject:
    writeData(StaircaseControl, a); // of the staircase
    a = 0x09; // start past the end for the bottom
    if (!c)
        goto NextStair; // if length already loaded, skip init part
    pushReturnIndex(112);
    goto ChkLrgObjLength;
Return_112: // check and load length

NextStair: // move onto next step (or first if starting)
    goto RenderUnderPart;
    a = 0x61; // now render solid block staircase
    y = a;
    a = M(StaircaseHeightData + y);
    x = M(StaircaseRowData + y); // get starting row and height to render
    y = M(StaircaseControl);
    --M(StaircaseControl);

Jumpspring:
    goto Return;

//------------------------------------------------------------------------
    writeData(MetatileBuffer + 1 + x, a);
    a = 0x68;
    writeData(MetatileBuffer + x, a);
    a = 0x67; // draw metatiles in two rows where jumpspring is
    x = M(0x07);
    ++M(Enemy_Flag + x); // set flag for enemy object buffer
    writeData(Enemy_Y_HighPos + x, y); // store vertical high byte
    y = 0x01;
    writeData(Enemy_ID + x, a); // write jumpspring object to enemy object buffer
    a = JumpspringObject;
    writeData(Jumpspring_FixedYPos + x, a); // store as permanent coordinate here
    writeData(Enemy_Y_Position + x, a); // and store
    pushReturnIndex(113);
    goto GetAreaObjYPosition;
Return_113: // get vertical coordinate for jumpspring
    writeData(Enemy_PageLoc + x, a);
    a = M(CurrentPageLoc); // store page location of jumpspring
    writeData(Enemy_X_Position + x, a); // and store
    pushReturnIndex(114);
    goto GetAreaObjXPosition;
Return_114: // get horizontal coordinate for jumpspring
    pushReturnIndex(115);
    goto FindEmptyEnemySlot;
Return_115: // find empty space in enemy object buffer
    pushReturnIndex(116);
    goto GetLrgObjAttrib;
Return_116:

Hidden1UpBlock:
    goto BrickWithItem; // jump to code shared with unbreakable bricks
    writeData(Hidden1UpFlag, a);
    a = 0x00; // if set, init for the next one
    if (z)
        goto ExitDecBlock;
    a = M(Hidden1UpFlag); // if flag not set, do not render object

QuestionBlock:
    goto DrawQBlk; // go to render it
    pushReturnIndex(117);
    goto GetAreaObjectID;
Return_117: // get value from level decoder routine

BrickWithCoins:
    writeData(BrickCoinTimerFlag, a);
    a = 0x00; // initialize multi-coin timer flag

BrickWithItem:
    a = 0x05; // otherwise use adder for bricks without lines
    if (z)
        goto BWithL; // if ground type, do not start with 5
    --y;
    y = M(AreaType); // check level type for ground level
    a = 0x00; // load default adder for bricks with lines
    writeData(0x07, y);
    pushReturnIndex(118);
    goto GetAreaObjectID;
Return_118: // save area object ID

BWithL: // add object ID to adder
    y = a; // use as offset for metatile
    a += M(0x07);
    c = 0;

DrawQBlk: // get appropriate metatile for brick (question block
    goto DrawRow; // now render the object
    pushReturnIndex(119);
    goto GetLrgObjAttrib;
Return_119: // get row from location byte
    pha(); // if branched to here from question block routine)
    a = M(BrickQBlockMetatiles + y);

GetAreaObjectID:
    y = a; // save to Y
    a -= 0x00; // possibly residual code
    c = 1;
    a = M(0x00); // get value saved from area parser routine

ExitDecBlock:
    goto Return;

//------------------------------------------------------------------------

Hole_Empty:
    x = 0x00; // otherwise initialize it
    if (!c)
        goto StrWOffset; // if not yet reached fifth whirlpool, branch to save offset
    compare(x, 0x05); // increment and check offset
    ++x;
    writeData(Whirlpool_Length + x, a); // save size of whirlpool here
    a <<= 1; // and extend one block beyond each edge
    a <<= 1; // two blocks bigger than actual size of hole
    a <<= 1; // note that whirlpool will always be
    a <<= 1; // multiply by 16 to get size of whirlpool
    a = y;
    ++y; // increment length by 2
    ++y;
    writeData(Whirlpool_PageLoc + x, a); // save as page location of whirlpool
    a -= 0x00; // subtract borrow
    a = M(CurrentPageLoc); // get page location of where we're at
    writeData(Whirlpool_LeftExtent + x, a); // store as left extent of whirlpool
    a -= 0x10; // subtract 16 pixels
    c = 1;
    pushReturnIndex(120);
    goto GetAreaObjXPosition;
Return_120: // get proper vertical coordinate of where we're at
    x = M(Whirlpool_Offset); // get offset for data used by cannons and whirlpools
    if (!z)
        goto NoWhirlP; // if not water type, skip this part
    a = M(AreaType); // check for water type level
    if (!c)
        goto NoWhirlP; // skip this part if length already loaded
    pushReturnIndex(121);
    goto ChkLrgObjLength;
Return_121: // get lower nybble and save as length

StrWOffset: // save new offset here
    writeData(Whirlpool_Offset, x);

NoWhirlP: // get appropriate metatile, then
    y = 0x0f; // start at ninth row and go to bottom, run RenderUnderPart
    x = 0x08;
    a = M(HoleMetatiles + x); // render the hole proper
    x = M(AreaType);

RenderUnderPart:
    if (z)
        goto WaitOneRow; // if stem top of mushroom, wait until next row
    compare(a, 0x50);
    if (!z)
        goto DrawThisRow; // if cracked rock terrain, overwrite
    compare(y, 0x54);
    if (c)
        goto WaitOneRow; // if any other metatile with palette 3, wait until next row
    compare(y, 0xc0);
    if (z)
        goto DrawThisRow; // if question block w/ coin, overwrite
    compare(y, 0xc0);
    if (z)
        goto WaitOneRow; // if middle part (mushroom ledge), wait until next row
    compare(y, 0x1a);
    if (z)
        goto WaitOneRow; // if middle part (tree ledge), wait until next row
    compare(y, 0x17);
    if (z)
        goto DrawThisRow; // we need to keep, if nothing, go ahead
    y = M(MetatileBuffer + x); // check current spot to see if there's something
    writeData(AreaObjectHeight, y); // store vertical length to render

DrawThisRow: // render contents of A from routine that called this
    writeData(MetatileBuffer + x, a);

WaitOneRow:
    if (!n)
        goto RenderUnderPart;
    --y;
    y = M(AreaObjectHeight); // decrement, and stop rendering if there is no more length
    if (c)
        goto ExitUPartR;
    compare(x, 0x0d); // stop rendering if we're at the bottom of the screen
    ++x;

ExitUPartR:
    goto Return;

//------------------------------------------------------------------------

ChkLrgObjLength:
    pushReturnIndex(122);
    goto GetLrgObjAttrib;
Return_122: // get row location and size (length if branched to from here)

ChkLrgObjFixedLength:
    c = 1; // set carry flag if just starting
    writeData(AreaObjectLength + x, a);
    a = y; // save length into length counter
    if (!n)
        goto LenSet; // if counter not set, load it, otherwise leave alone
    c = 0; // clear carry flag for not just starting
    a = M(AreaObjectLength + x); // check for set length counter

LenSet:
    goto Return;

//------------------------------------------------------------------------

GetLrgObjAttrib:
    goto Return;

//------------------------------------------------------------------------
    y = a;
    a &= BOOST_BINARY(00001111); // as Y, then leave
    a = M(W(AreaData) + y); // get next byte, save lower nybble (length or height)
    ++y;
    writeData(0x07, a); // save row location
    a &= BOOST_BINARY(00001111);
    a = M(W(AreaData) + y); // get first byte of level object
    y = M(AreaObjOffsetBuffer + x); // get offset saved from area obj decoding routine

GetAreaObjXPosition:
    goto Return;

//------------------------------------------------------------------------
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1; // to obtain horizontal pixel coordinate
    a = M(CurrentColumnPos); // multiply current offset where we're at by 16

GetAreaObjYPosition:
    goto Return;

//------------------------------------------------------------------------
    a += 32; // add 32 pixels for the status bar
    c = 0;
    a <<= 1;
    a <<= 1;
    a <<= 1; // this will give us the proper vertical pixel coordinate
    a <<= 1;
    a = M(0x07); // multiply value by 16

GetBlockBufferAddr:
    goto Return;

//------------------------------------------------------------------------
    writeData(0x06, a); // store here and leave
    a += M(BlockBufferAddr + y); // add to low byte
    c = 0;
    a &= BOOST_BINARY(00001111); // pull from stack, mask out high nybble
    pla();
    writeData(0x07, a);
    a = M(BlockBufferAddr + 2 + y); // of indirect here
    y = a; // use nybble as pointer to high byte
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1; // move high nybble to low
    pha(); // take value of A, save

LoadAreaPointer:
    writeData(AreaPointer, a);
    pushReturnIndex(123);
    goto FindAreaPointer;
Return_123: // find it and store it here

GetAreaType: // mask out all but d6 and d5
    goto Return;

//------------------------------------------------------------------------
    writeData(AreaType, a); // save 2 MSB as area type
    a.rol(); // make %0xx00000 into %000000xx
    a.rol();
    a.rol();
    a <<= 1;
    a &= BOOST_BINARY(01100000);

FindAreaPointer:
    goto Return;

//------------------------------------------------------------------------
    a = M(AreaAddrOffsets + y); // from there we have our area pointer
    y = a;
    a += M(AreaNumber);
    c = 0; // add area number used to find data
    a = M(WorldAddrOffsets + y);
    y = M(WorldNumber); // load offset from world variable

GetAreaDataAddrs:
    a = 0x00;
    writeData(BackgroundColorCtrl, a); // if 4 or greater, save value here as bg color control
    if (!c)
        goto StoreFore;
    compare(a, 0x04);
    a &= BOOST_BINARY(00000111); // save 3 LSB for foreground scenery or bg color control
    pha(); // save it to the stack for now
    a = M(W(AreaData) + y);
    y = 0x00; // load first byte of header
    writeData(AreaDataHigh, a);
    a = M(AreaDataAddrHigh + y);
    writeData(AreaDataLow, a);
    a = M(AreaDataAddrLow + y); // use this offset to load another pointer
    y = a;
    a += M(AreaAddrsLOffset);
    c = 0;
    a = M(AreaDataHOffsets + y); // do the same thing but with different base value
    y = M(AreaType); // use area type as offset
    writeData(EnemyDataHigh, a);
    a = M(EnemyDataAddrHigh + y);
    writeData(EnemyDataLow, a);
    a = M(EnemyDataAddrLow + y); // use offset to load pointer
    y = a;
    a += M(AreaAddrsLOffset); // becomes offset for level data
    c = 0; // then add base value to 5 LSB, result
    a = M(EnemyAddrHOffsets + y); // load base value with 2 altered MSB,
    writeData(AreaAddrsLOffset, a); // save as low offset
    a &= BOOST_BINARY(00011111);
    a = M(AreaPointer); // mask out all but 5 LSB
    y = a;
    pushReturnIndex(124);
    goto GetAreaType;
Return_124:
    a = M(AreaPointer); // use 2 MSB for Y

StoreFore: // if less, save value here as foreground scenery
    a = 0x00;
    writeData(CloudTypeOverride, a); // otherwise store value in other place
    if (!z)
        goto StoreStyle; // and nullify other value
    compare(a, BOOST_BINARY(00000011)); // if set to 3, store here
    a.rol();
    a.rol();
    a.rol(); // rotate bits over to LSBs
    c = 0;
    a &= BOOST_BINARY(11000000);
    pla();
    writeData(BackgroundScenery, a); // save as background scenery
    a >>= 1;
    a >>= 1;
    a >>= 1; // shift bits to LSBs
    a >>= 1;
    a &= BOOST_BINARY(00110000); // save 2 MSB for background scenery type
    pha();
    pla(); // pull and push byte to copy it to A
    writeData(TerrainControl, a);
    a &= BOOST_BINARY(00001111); // mask out all but lower nybble
    pha(); // save to stack
    a = M(W(AreaData) + y); // load second byte of header
    ++y;
    writeData(GameTimerSetting, a); // save value here as game timer setting
    a.rol();
    a.rol();
    a.rol(); // rotate bits over to LSBs
    c = 0;
    a &= BOOST_BINARY(11000000); // save 2 MSB for game timer setting
    pla(); // pull byte again but do not push it back
    writeData(PlayerEntranceCtrl, a); // save value here as player entrance control
    a >>= 1;
    a >>= 1;
    a >>= 1; // shift bits over to LSBs
    a &= BOOST_BINARY(00111000); // save player entrance control bits
    pha();
    pla(); // pull byte from stack and push it back
    writeData(ForegroundScenery, a);

StoreStyle:
    goto Return;

//------------------------------------------------------------------------
    writeData(AreaDataHigh, a);
    a += 0x00;
    a = M(AreaDataHigh);
    writeData(AreaDataLow, a);
    a += 0x02;
    c = 0;
    a = M(AreaDataLow); // increment area data address by 2 bytes
    writeData(AreaStyle, a);

World1Areas:

World2Areas:

World3Areas:

World4Areas:

World5Areas:

World6Areas:

World7Areas:

World8Areas:

GameMode:
    switch (a)
    {
    }
    a = M(OperMode_Task);

GameCoreRoutine:
    goto Return;

//------------------------------------------------------------------------
    if (c)
        goto GameEngine; // branch to the game engine itself
    compare(a, 0x03); // if we are supposed to be here,
    a = M(OperMode_Task); // check major task of operating mode
    pushReturnIndex(125);
    goto GameRoutines;
Return_125: // execute one of many possible subs
    writeData(SavedJoypadBits, a); // as the master controller bits
    a = M(SavedJoypadBits + x); // use appropriate player's controller bits
    x = M(CurrentPlayer); // get which player is on the screen

GameEngine:
    x = 0x00;
    pushReturnIndex(126);
    goto ProcFireball_Bubble;
Return_126: // process fireballs and air bubbles

ProcELoop: // put incremented offset in X as enemy object offset
    pushReturnIndex(127);
    goto GetAreaMusic;
Return_127: // to re-attain appropriate level music
    if (!z)
        goto NoChgMus; // branch ahead, don't bother with the music
    a = M(IntervalTimerControl); // if interval timer not yet expired,
    if (!z)
        goto NoChgMus; // if not yet at a certain point, continue
    compare(a, 0x04);
    if (z)
        goto ClrPlrPal; // skip this part
    a = M(StarInvincibleTimer); // if star mario invincibility timer at zero,
    if (!n)
        goto NoChgMus;
    compare(a, 0x02); // if player is below the screen, don't bother with the music
    a = M(Player_Y_HighPos);
    pushReturnIndex(128);
    goto ColorRotation;
Return_128: // cycle one of the background colors
    pushReturnIndex(129);
    goto RunGameTimer;
Return_129: // count down the game timer
    pushReturnIndex(130);
    goto FlagpoleRoutine;
Return_130: // process the flagpole
    pushReturnIndex(131);
    goto ProcessWhirlpools;
Return_131: // process whirlpools
    pushReturnIndex(132);
    goto ProcessCannons;
Return_132: // process bullet bill cannons
    pushReturnIndex(133);
    goto MiscObjectsCore;
Return_133: // process misc objects (hammer, jumping coins)
    pushReturnIndex(134);
    goto BlockObjectsCore;
Return_134: // process first block object
    writeData(ObjectOffset, x); // set offset for first
    --x;
    pushReturnIndex(135);
    goto BlockObjectsCore;
Return_135: // process second block object
    writeData(ObjectOffset, x); // set offset for second
    x = 0x01;
    pushReturnIndex(136);
    goto BlockObjMT_Updater;
Return_136: // replace block objects with metatiles if necessary
    pushReturnIndex(137);
    goto PlayerGfxHandler;
Return_137: // draw the player
    pushReturnIndex(138);
    goto RelativePlayerPosition;
Return_138: // get relative coordinates for player object
    pushReturnIndex(139);
    goto GetPlayerOffscreenBits;
Return_139: // get offscreen bits for player object
    if (!z)
        goto ProcELoop;
    compare(x, 0x06); // do these two subroutines until the whole buffer is done
    ++x;
    pushReturnIndex(140);
    goto FloateyNumbersRoutine;
Return_140: // process floatey numbers
    pushReturnIndex(141);
    goto EnemiesAndLoopsCore;
Return_141: // process enemy objects
    writeData(ObjectOffset, x);

NoChgMus: // get invincibility timer
    a >>= 1;
    a >>= 1; // otherwise, divide by 8 to cycle every eighth frame
    if (c)
        goto CycleTwo; // branch to cycle player's palette quickly
    compare(y, 0x08); // if timer still above certain point,
    a = M(FrameCounter); // get frame counter
    y = M(StarInvincibleTimer);

CycleTwo: // if branched here, divide by 2 to cycle every other frame
    goto SaveAB; // then skip this sub to finish up the game engine
    pushReturnIndex(142);
    goto CyclePlayerPalette;
Return_142: // do sub to cycle the palette (note: shares fire flower code)
    a >>= 1;

ClrPlrPal: // do sub to clear player's palette bits in attributes
    pushReturnIndex(143);
    goto ResetPalStar;
Return_143:

SaveAB: // save current A and B button
    writeData(Left_Right_Buttons, a); // nullify left and right buttons temp variable
    a = 0x00;
    writeData(PreviousA_B_Buttons, a); // into temp variable to be used on next frame
    a = M(A_B_Buttons);

UpdScrollVar:
    writeData(VRAM_Buffer2_Offset, a); // level graphics buffer at $0341-$035f
    a = 0x00; // reset vram buffer offset used in conjunction with
    writeData(ScrollThirtyTwo, a); // and store
    a -= 0x20; // otherwise subtract $20 to set appropriately
    a = M(ScrollThirtyTwo);
    if (n)
        goto ExitEng; // branch to leave if not
    compare(a, 0x20); // check to see if exceeded $21
    a = M(ScrollThirtyTwo); // get horizontal scroll in 0-31 or $00-$20 range
    if (!z)
        goto RunParser;
    a = M(AreaParserTaskNum); // otherwise check number of tasks
    if (z)
        goto ExitEng; // then branch to leave
    compare(a, 0x06); // if vram address controller set to 6 (one of two $0341s)
    a = M(VRAM_Buffer_AddrCtrl);

RunParser: // update the name table with more level graphics
    pushReturnIndex(144);
    goto AreaParserTaskHandler;
Return_144:

ExitEng: // and after all that, we're finally done!
    goto Return;

//------------------------------------------------------------------------

ScrollHandler:
    --y; // otherwise decrement by one
    if (!c)
        goto ChkNearMid;
    compare(y, 0x02); // if value $01, branch and do not decrement
    ++y;
    if (n)
        goto InitScrlAmt; // negative for left movement, branch
    --y; // if value originally set to zero or otherwise
    y = M(Player_X_Scroll); // get value and decrement by one
    if (!z)
        goto InitScrlAmt; // not expired, branch
    a = M(SideCollisionTimer); // if timer related to player's side collision
    if (!c)
        goto InitScrlAmt; // if less than 80 pixels to the right, branch
    compare(a, 0x50); // check player's horizontal screen position
    a = M(Player_Pos_ForScroll);
    if (!z)
        goto InitScrlAmt; // skip a bunch of code here if set
    a = M(ScrollLock); // check scroll lock flag
    writeData(Player_X_Scroll, a); // save as new value here to impose force on scroll
    a += M(Platform_X_Scroll); // add value used by left/right platforms
    c = 0;
    a = M(Player_X_Scroll); // load value saved here

ChkNearMid:
    y = M(Player_X_Scroll); // otherwise get original value undecremented
    if (!c)
        goto ScrollScreen; // if less than 112 pixels to the right, branch
    compare(a, 0x70); // check player's horizontal screen position
    a = M(Player_Pos_ForScroll);

ScrollScreen:
    goto ChkPOffscr; // skip this part
    writeData(ScrollIntervalTimer, a); // set scroll timer (residual, not used elsewhere)
    a = 0x08;
    pushReturnIndex(145);
    goto GetScreenPosition;
Return_145: // figure out where the right side is
    writeData(Mirror_PPU_CTRL_REG1, a); // mirror to be used to set name table later
    a |= M(0x00); // get saved bit here and save in PPU register 1
    a &= BOOST_BINARY(11111110); // save all bits except d0
    a = M(Mirror_PPU_CTRL_REG1); // get PPU register 1 mirror
    writeData(0x00, a); // save as temp variable for PPU register 1 mirror
    a &= 0x01; // get LSB of page location
    writeData(ScreenLeft_PageLoc, a); // side of the screen
    a += 0x00; // add carry to page location for left
    a = M(ScreenLeft_PageLoc);
    writeData(HorizontalScroll, a); // save here also
    writeData(ScreenLeft_X_Pos, a); // save as new left side coordinate
    a += M(ScreenLeft_X_Pos); // add to left side coordinate
    c = 0;
    a = y;
    writeData(ScrollThirtyTwo, a); // save as new value here
    a += M(ScrollThirtyTwo); // add to value already set here
    c = 0;
    writeData(ScrollAmount, a); // save value here
    a = y;

InitScrlAmt:
    writeData(ScrollAmount, a); // initialize value here
    a = 0x00;

ChkPOffscr: // set X for player offset
    if (z)
        goto InitPlatScrl; // if not set, branch ahead of this part
    a &= BOOST_BINARY(00100000); // check offscreen bits for d5 set
    a = M(0x00);
    ++y; // otherwise use different offset (right side)
    if (c)
        goto KeepOnscr; // branch with default offset
    a <<= 1; // if d7 of offscreen bits are set,
    y = 0x00; // load default offset (left side)
    writeData(0x00, a); // save them here
    pushReturnIndex(146);
    goto GetXOffscreenBits;
Return_146: // get horizontal offscreen bits for player
    x = 0x00;

KeepOnscr: // get left or right side coordinate based on offset
    writeData(Player_X_Speed, a); // otherwise nullify horizontal speed of player
    a = 0x00;
    if (z)
        goto InitPlatScrl; // if not equal, branch
    compare(a, M(OffscrJoypadBitsData + y)); // against bits based on offset
    a = M(Left_Right_Buttons); // check saved controller bits
    writeData(Player_PageLoc, a); // save as player's page location
    a -= 0x00; // subtract borrow
    a = M(ScreenEdge_PageLoc + y); // get left or right page location based on offset
    writeData(Player_X_Position, a); // store as player position to prevent movement further
    a -= M(X_SubtracterData + y); // subtract amount based on offset
    c = 1;
    a = M(ScreenEdge_X_Pos + y);

InitPlatScrl: // nullify platform force imposed on scroll
    goto Return;

//------------------------------------------------------------------------
    writeData(Platform_X_Scroll, a);
    a = 0x00;

GetScreenPosition:
    goto Return;

//------------------------------------------------------------------------
    writeData(ScreenRight_PageLoc, a); // store as page number where right boundary is
    a += 0x00; // add carry from before
    a = M(ScreenLeft_PageLoc); // get page number where left boundary is
    writeData(ScreenRight_X_Pos, a); // store as coordinate of screen's right boundary
    a += 0xff; // add 255 pixels
    c = 0;
    a = M(ScreenLeft_X_Pos); // get coordinate of screen's left boundary

GameRoutines:
    switch (a)
    {
    } // merely placeholders as conditions for other routines)
    a = M(GameEngineSubroutine); // run routine based on number (a few of these routines are   

PlayerEntrance:
    if (!z)
        goto PlayerRdy;
    compare(a, 0x07); // otherwise branch to normal entry
    if (z)
        goto ChkBehPipe; // if set to 6 or 7, execute pipe intro code
    compare(a, 0x06);
    a = M(PlayerEntranceCtrl); // check player entry bits from header
    if (!c)
        goto AutoControlPlayer; // with player movement code, do not return
    compare(y, 0x30); // point, nullify controller bits and continue
    y = M(Player_Y_Position); // if vertical position above a certain
    a = 0x00;
    if (z)
        goto EntrMode2; // if found, branch to enter from pipe or with vine
    compare(a, 0x02);
    a = M(AltEntranceControl); // check for mode of alternate entry

ChkBehPipe: // check for sprite attributes
    goto AutoControlPlayer; // force player to walk to the right
    a = 0x01;
    if (!z)
        goto IntroEntr; // branch if found
    a = M(Player_SprAttrib);

IntroEntr: // execute sub to move player to the right
    goto NextArea; // jump to increment to next area and set modes
    ++M(DisableIntermediate); // set flag to skip world and lives display
    if (!z)
        goto ExitEntr; // branch to exit if not yet expired
    --M(ChangeAreaTimer); // decrement timer for change of area
    pushReturnIndex(147);
    goto EnterSidePipe;
Return_147:

EntrMode2: // if controller override bits set here,
    goto Return; // to the last part, otherwise leave

//------------------------------------------------------------------------
    if (!c)
        goto PlayerRdy; // to be at specific height to look/function right) branch
    compare(a, 0x91); // if player risen to a certain point (this requires pipes
    a = M(Player_Y_Position); // check to see if player is at a specific coordinate
    pushReturnIndex(148);
    goto MovePlayerYAxis;
Return_148: // to move player upwards (note $ff = -1)
    a = 0xff; // otherwise, set value here then execute sub
    if (!z)
        goto VineEntr; // branch to enter with vine
    a = M(JoypadOverride);

VineEntr:
    writeData(Block_Buffer_1 + 0xb4, a); // use same value to force player to climb
    a = 0x08; // set block in block buffer to cover hole, then 
    ++y; // increment value in Y
    writeData(Player_State, a); // otherwise set player state to climbing
    a = 0x03;
    if (!c)
        goto OffVine; // if vertical coordinate < preset value, use defaults
    a = 0x01; // this value moves player to the right off the vine
    y = 0x00; // load default values to be written to 
    compare(a, 0x99); // check player's vertical coordinate against preset value
    a = M(Player_Y_Position); // get player's vertical coordinate
    if (!z)
        goto ExitEntr; // if vine not yet reached maximum height, branch to leave
    compare(a, 0x60); // check vine height
    a = M(VineHeight);

OffVine: // set collision detection disable flag
    if (!c)
        goto ExitEntr; // if not far enough to the right, branch to leave
    compare(a, 0x48); // check player's horizontal position
    a = M(Player_X_Position);
    pushReturnIndex(149);
    goto AutoControlPlayer;
Return_149: // use contents of A to move player up or right, execute sub
    writeData(DisableCollisionDet, y);

PlayerRdy: // set routine to be executed by game engine next frame
    writeData(JoypadOverride, a); // nullify controller override bits
    writeData(DisableCollisionDet, a); // init collision detection disable flag
    writeData(AltEntranceControl, a); // init mode of entry
    a >>= 1; // init A
    writeData(PlayerFacingDir, a);
    a = 0x01; // set to face player to the right
    writeData(GameEngineSubroutine, a);
    a = 0x08;

ExitEntr: // leave!
    goto Return;

//------------------------------------------------------------------------

AutoControlPlayer:
    writeData(SavedJoypadBits, a); // override controller bits with contents of A if executing here

PlayerCtrlRoutine:
    if (!c)
        goto SaveJoyp; // not in the vertical area between status bar or bottom,
    compare(a, 0xd0); // if nearing the bottom of the screen or
    a = M(Player_Y_Position);
    if (!z)
        goto DisJoyp; // status bar and bottom, branch
    --y; // if not in vertical area between
    y = M(Player_Y_HighPos);
    if (!z)
        goto SaveJoyp; // if not, branch
    a = M(AreaType); // are we in a water type area?
    if (z)
        goto SizeChk;
    compare(a, 0x0b); // if certain value is set, branch to skip controller bit loading
    a = M(GameEngineSubroutine); // check task here

DisJoyp: // disable controller bits
    writeData(SavedJoypadBits, a);
    a = 0x00;

SaveJoyp: // otherwise store A and B buttons in $0a
    writeData(Up_Down_Buttons, a); // nullify directional bits
    writeData(Left_Right_Buttons, a); // if pressing down while on the ground,
    a = 0x00;
    if (z)
        goto SizeChk; // if neither pressed, branch
    y = M(Left_Right_Buttons); // check left and right
    if (!z)
        goto SizeChk; // if not on the ground, branch
    a = M(Player_State); // check player's state
    if (z)
        goto SizeChk; // if not, branch
    a &= BOOST_BINARY(00000100); // check for pressing down
    writeData(Up_Down_Buttons, a);
    a &= BOOST_BINARY(00001100);
    a = M(SavedJoypadBits); // store up and down buttons in $0b
    writeData(Left_Right_Buttons, a);
    a &= BOOST_BINARY(00000011);
    a = M(SavedJoypadBits); // store left and right buttons in $0c
    writeData(A_B_Buttons, a);
    a &= BOOST_BINARY(11000000);
    a = M(SavedJoypadBits);

SizeChk: // run movement subroutines
    y = 0x02; // if big and crouching, load y with 2
    if (z)
        goto ChkMoveDir; // if not, branch ahead
    a = M(CrouchingFlag);
    y = 0x00; // check for if crouching
    if (!z)
        goto ChkMoveDir;
    a = M(PlayerSize);
    y = 0x01; // is player small?
    pushReturnIndex(150);
    goto PlayerMovementSubs;
Return_150:

ChkMoveDir: // set contents of Y as player's bounding box size control
    a <<= 1; // otherwise change to move to the left
    if (!n)
        goto SetMoveDir; // if moving to the right, use default moving direction
    if (z)
        goto PlayerSubs; // if not moving at all horizontally, skip this part
    y = M(Player_X_Speed); // check player's horizontal speed
    a = 0x01; // set moving direction to right by default
    writeData(Player_BoundBoxCtrl, y);

SetMoveDir: // set moving direction
    writeData(Player_MovingDir, a);

PlayerSubs: // move the screen if necessary
    writeData(Player_SprAttrib, a); // background priority flag
    a &= BOOST_BINARY(11011111); // otherwise nullify player's
    a = M(Player_SprAttrib);
    if (!c)
        goto PlayerHole;
    compare(a, 0x04); // if running routines $00-$03, branch ahead
    if (z)
        goto PlayerHole;
    compare(a, 0x07); // if running player entrance routine, branch ahead
    if (z)
        goto PlayerHole;
    compare(a, 0x05); // if running end-of-level routine, branch ahead
    a = M(GameEngineSubroutine);
    if (!c)
        goto PlayerHole; // if so, branch ahead
    compare(a, 0x40); // check to see if player is higher than 64th pixel
    a = M(Player_Y_Position);
    pushReturnIndex(151);
    goto PlayerBGCollision;
Return_151: // do collision detection and process
    pushReturnIndex(152);
    goto BoundingBoxCore;
Return_152: // get player's bounding box coordinates
    x = 0x00; // set offset for player object
    pushReturnIndex(153);
    goto RelativePlayerPosition;
Return_153: // get coordinates relative to the screen
    pushReturnIndex(154);
    goto GetPlayerOffscreenBits;
Return_154: // get player's offscreen bits
    pushReturnIndex(155);
    goto ScrollHandler;
Return_155:

PlayerHole: // check player's vertical high byte
    if (!z)
        goto ChkHoleX; // skip to last part if found
    y = M(CloudTypeOverride); // check for cloud type override
    if (!z)
        goto HoleDie; // if set, branch
    y = M(GameTimerExpiredFlag); // check game timer expiration flag
    x = 0x00; // use X as flag, and clear for cloud level
    writeData(0x07, y); // set value here
    y = 0x04;
    writeData(ScrollLock, x); // set scroll lock
    x = 0x01;
    if (n)
        goto ExitCtrl; // branch to leave if not that far down
    compare(a, 0x02); // for below the screen
    a = M(Player_Y_HighPos);

HoleDie: // set flag in X for player death
    writeData(DeathMusicLoaded, y); // and set value here
    writeData(EventMusicQueue, y); // otherwise play death music
    ++y;
    if (!z)
        goto HoleBottom; // if already set, branch to next part
    y = M(DeathMusicLoaded); // check value here
    if (z)
        goto ChkHoleX; // if so, branch ahead
    compare(y, 0x0b); // check for some other routine running
    y = M(GameEngineSubroutine);
    ++x;

HoleBottom:
    writeData(0x07, y); // change value here
    y = 0x06;

ChkHoleX: // compare vertical high byte with value set here
    writeData(GameEngineSubroutine, a); // on next frame
    a = 0x06; // otherwise set to run lose life routine
    if (!z)
        goto ExitCtrl; // branch to leave if so
    y = M(EventMusicBuffer); // check to see if music is still playing
    if (n)
        goto CloudExit; // if flag was clear, branch to set modes and other values
    --x; // otherwise decrement flag in X
    if (n)
        goto ExitCtrl; // if less, branch to leave
    compare(a, M(0x07));

ExitCtrl: // leave
    goto Return;

//------------------------------------------------------------------------

CloudExit:
    goto Return;

//------------------------------------------------------------------------
    ++M(AltEntranceControl); // set mode of entry to 3
    pushReturnIndex(156);
    goto SetEntr;
Return_156: // do sub to set secondary mode
    writeData(JoypadOverride, a); // clear controller override bits if any are set
    a = 0x00;

Vine_AutoClimb:
    if (!c)
        goto SetEntr;
    compare(a, 0xe4);
    a = M(Player_Y_Position);
    if (!z)
        goto AutoClimb; // above the status bar yet and if so, set modes
    a = M(Player_Y_HighPos); // check to see whether player reached position

AutoClimb: // set controller bits override to up
    goto AutoControlPlayer;
    writeData(Player_State, y);
    y = 0x03; // set player state to climbing
    writeData(JoypadOverride, a);
    a = BOOST_BINARY(00001000);

SetEntr: // set starting position to override
    goto ChgAreaMode; // set modes
    writeData(AltEntranceControl, a);
    a = 0x02;

VerticalPipeEntry:
    goto ChgAreaPipe; // otherwise use mode 2
    ++y;
    if (!z)
        goto ChgAreaPipe; // if not castle type level, use mode 1
    compare(a, 0x03);
    a = M(AreaType); // check for castle level type
    ++y;
    if (!z)
        goto ChgAreaPipe; // if set, branch to use mode 0
    a = M(WarpZoneControl); // check warp zone control variable/flag
    y = 0x00; // load default mode of entry
    pushReturnIndex(157);
    goto ScrollHandler;
Return_157: // do sub to scroll screen with saved force if necessary
    pushReturnIndex(158);
    goto MovePlayerYAxis;
Return_158: // do sub to move player downwards
    a = 0x01; // set 1 as movement amount

MovePlayerYAxis:
    goto Return;

//------------------------------------------------------------------------
    writeData(Player_Y_Position, a);
    a += M(Player_Y_Position); // add contents of A to player position
    c = 0;

SideExitPipeEntry:
    y = 0x02;
    pushReturnIndex(159);
    goto EnterSidePipe;
Return_159: // execute sub to move player to the right

ChgAreaPipe: // decrement timer for change of area
    writeData(AltEntranceControl, y); // when timer expires set mode of alternate entry
    if (!z)
        goto ExitCAPipe;
    --M(ChangeAreaTimer);

ChgAreaMode: // set flag to disable screen output
    writeData(Sprite0HitDetectFlag, a); // disable sprite 0 check
    writeData(OperMode_Task, a); // set secondary mode of operation
    a = 0x00;
    ++M(DisableScreenFlag);

ExitCAPipe: // leave
    goto Return;

//------------------------------------------------------------------------

EnterSidePipe:
    y = a; // and nullify controller bit override here
    writeData(Player_X_Speed, a); // if lower nybble = 0, set as horizontal speed
    if (!z)
        goto RightPipe;
    a &= BOOST_BINARY(00001111); // horizontal position
    a = M(Player_X_Position); // mask out higher nybble of player's
    y = 0x01; // set controller right button by default
    writeData(Player_X_Speed, a);
    a = 0x08; // set player's horizontal speed

RightPipe: // use contents of Y to
    goto Return;

//------------------------------------------------------------------------
    pushReturnIndex(160);
    goto AutoControlPlayer;
Return_160: // execute player control routine with ctrl bits nulled
    a = y;

PlayerChangeSize:
    goto InitChangeSize; // otherwise run code to get growing/shrinking going
    if (!z)
        goto EndChgSize; // branch if before or after that point
    compare(a, 0xf8); // for specific moment in time
    a = M(TimerControl); // check master timer control

EndChgSize: // check again for another specific moment
    pushReturnIndex(161);
    goto DonePlayerTask;
Return_161: // otherwise do sub to init timer control and set routine
    if (!z)
        goto ExitChgSize; // and branch to leave if before or after that point
    compare(a, 0xc4);

ExitChgSize: // and then leave
    goto Return;

//------------------------------------------------------------------------

PlayerInjuryBlink:
    goto PlayerCtrlRoutine; // otherwise run player control routine
    if (z)
        goto DonePlayerTask; // branch if at that point, and not before or after
    compare(a, 0xc8); // check again for another specific point
    if (c)
        goto ExitBlink; // branch if before that point
    compare(a, 0xf0); // for specific moment in time
    a = M(TimerControl); // check master timer control

ExitBlink: // do unconditional branch to leave
    if (!z)
        goto ExitBoth;

InitChangeSize:
    writeData(PlayerSize, a);
    a ^= 0x01; // invert player's size
    a = M(PlayerSize);
    ++M(PlayerChangeSizeFlag); // set growing/shrinking flag
    writeData(PlayerAnimCtrl, y); // otherwise initialize player's animation frame control
    if (!z)
        goto ExitBoth; // then branch to leave
    y = M(PlayerChangeSizeFlag); // if growing/shrinking flag already set

ExitBoth: // leave
    goto Return;

//------------------------------------------------------------------------

PlayerDeath:
    goto PlayerCtrlRoutine; // otherwise run player control routine
    if (c)
        goto ExitDeath; // branch to leave if before that point
    compare(a, 0xf0); // for specific moment in time
    a = M(TimerControl); // check master timer control

DonePlayerTask:
    goto Return; // leave

//------------------------------------------------------------------------
    writeData(GameEngineSubroutine, a); // set player control routine to run next frame
    a = 0x08;
    writeData(TimerControl, a); // initialize master timer control to continue timers
    a = 0x00;

PlayerFireFlower:
    a >>= 1; // divide by four to change every four frames
    a >>= 1;
    a = M(FrameCounter); // get frame counter
    if (z)
        goto ResetPalFireFlower; // branch if at moment, not before or after
    compare(a, 0xc0); // for specific moment in time
    a = M(TimerControl); // check master timer control

CyclePlayerPalette:
    goto Return; // and leave

//------------------------------------------------------------------------
    writeData(Player_SprAttrib, a); // store as new player attributes
    a |= M(0x00); // add palette bits
    a &= BOOST_BINARY(11111100); // save any other bits but palette bits
    a = M(Player_SprAttrib); // get player attributes
    writeData(0x00, a); // store result here to use as palette bits
    a &= 0x03; // mask out all but d1-d0 (previously d3-d2)

ResetPalFireFlower:
    pushReturnIndex(162);
    goto DonePlayerTask;
Return_162: // do sub to init timer control and run player control routine

ResetPalStar:
    goto Return; // and leave

//------------------------------------------------------------------------
    writeData(Player_SprAttrib, a); // store as new player attributes
    a &= BOOST_BINARY(11111100); // mask out palette bits to force palette 0
    a = M(Player_SprAttrib); // get player attributes

ExitDeath:
    goto Return; // leave from death routine

//------------------------------------------------------------------------

FlagpoleSlide:
    a = 0x04; // otherwise force player to climb down (to slide)
    if (c)
        goto SlidePlayer; // far enough, and if so, branch with no controller bits set
    compare(y, 0x9e); // check to see if player has slid down
    y = M(Player_Y_Position);
    writeData(FlagpoleSoundQueue, a); // init flagpole sound queue
    a = 0x00;
    writeData(Square1SoundQueue, a); // into square 1's sfx queue
    a = M(FlagpoleSoundQueue); // load flagpole sound
    if (!z)
        goto NoFPObj; // if not found, branch to something residual
    compare(a, FlagpoleFlagObject); // for flagpole flag object
    a = M(Enemy_ID + 5); // check special use enemy slot

SlidePlayer: // jump to player control routine
    goto AutoControlPlayer;

NoFPObj: // increment to next routine (this may
    goto Return; // be residual code)

//------------------------------------------------------------------------
    ++M(GameEngineSubroutine);

PlayerEndLevel:
    writeData(ScrollLock, a); // turn off scroll lock to skip this part later
    a = 0x00;
    writeData(EventMusicQueue, a); // load win level music in event music queue
    a = EndOfLevelMusic;
    if (z)
        goto ChkStop; // because we only need to do this part once
    a = M(ScrollLock); // if scroll lock not set, branch ahead to next part
    if (!c)
        goto ChkStop; // if player is not yet off the flagpole, skip this part
    compare(a, 0xae);
    a = M(Player_Y_Position); // check player's vertical position
    pushReturnIndex(163);
    goto AutoControlPlayer;
Return_163:
    a = 0x01; // force player to walk to the right

ChkStop: // get player collision bits
    ++M(StarFlagTaskControl); // otherwise set task control now (this gets ball rolling!)
    if (!z)
        goto InCastle; // go ahead with the rest of the code
    a = M(StarFlagTaskControl); // if star flag task control already set,
    if (c)
        goto RdyNextA; // if d0 set, skip to next part
    a >>= 1; // check for d0 set
    a = M(Player_CollisionBits);

InCastle: // set player's background priority bit to
    writeData(Player_SprAttrib, a); // give illusion of being inside the castle
    a = BOOST_BINARY(00100000);

RdyNextA:
    ++M(Hidden1UpFlag); // otherwise set hidden 1-up box control flag
    if (!c)
        goto NextArea; // at least this number of coins, leave flag clear
    compare(a, M(Hidden1UpCoinAmts + y)); // against minimum value, if player has not collected
    a = M(CoinTallyFor1Ups); // check third area coin tally for bonus 1-ups
    y = M(WorldNumber); // get world number as offset
    if (!z)
        goto NextArea; // and skip this last part here if not
    compare(a, 0x03); // check to see if we have yet reached level -4
    a = M(LevelNumber);
    ++M(LevelNumber); // increment level number used for game logic
    if (!z)
        goto ExitNA; // beyond last valid task number, branch to leave
    compare(a, 0x05); // if star flag task control not yet set
    a = M(StarFlagTaskControl);

NextArea: // increment area number used for address loader
    writeData(EventMusicQueue, a); // silence music and leave
    a = Silence;
    writeData(HalfwayPage, a); // reset halfway page to 0 (beginning)
    pushReturnIndex(164);
    goto ChgAreaMode;
Return_164: // do sub to set secondary mode, disable screen and sprite 0
    ++M(FetchNewGameTimerFlag); // set flag to load new game timer
    pushReturnIndex(165);
    goto LoadAreaPointer;
Return_165: // get new level pointer
    ++M(AreaNumber);

ExitNA:
    goto Return;

//------------------------------------------------------------------------

PlayerMovementSubs:
    a &= BOOST_BINARY(00000100); // single out bit for down button
    a = M(Up_Down_Buttons); // load controller bits for up and down
    if (!z)
        goto ProcMove; // if not on the ground, branch
    a = M(Player_State); // check state of player
    if (!z)
        goto SetCrouch; // if so, branch
    y = M(PlayerSize); // is player small?
    a = 0x00; // set A to init crouch flag by default

SetCrouch: // store value in crouch flag
    writeData(CrouchingFlag, a);

ProcMove: // run sub related to jumping and swimming
    writeData(ClimbSideTimer, y); // otherwise reset timer now
    y = 0x18;
    if (z)
        goto MoveSubs; // if climbing, branch ahead, leave timer unset
    compare(a, 0x03); // get player state
    a = M(Player_State);
    if (!z)
        goto NoMoveSub; // branch to leave
    a = M(PlayerChangeSizeFlag); // if growing/shrinking flag set,
    pushReturnIndex(166);
    goto PlayerPhysicsSub;
Return_166:

NoMoveSub:
    goto Return;

//------------------------------------------------------------------------

OnGroundStateSub:
    writeData(PlayerFacingDir, a); // otherwise set new facing direction
    if (z)
        goto GndMove; // if left/right controller bits not set, skip instruction
    a = M(Left_Right_Buttons);
    pushReturnIndex(167);
    goto GetPlayerAnimSpeed;
Return_167: // do a sub to set animation frame timing

GndMove: // do a sub to impose friction on player's walk/run
    goto Return;

//------------------------------------------------------------------------
    writeData(Player_X_Scroll, a); // set returned value as player's movement speed for scroll
    pushReturnIndex(168);
    goto MovePlayerHorizontally;
Return_168: // do another sub to move player horizontally
    pushReturnIndex(169);
    goto ImposeFriction;
Return_169:

FallingSub:
    goto LRAir; // movement force, then skip ahead to process left/right movement
    writeData(VerticalForce, a); // dump vertical movement force for falling into main one
    a = M(VerticalForceDown);

JumpSwimSub:
    if (!c)
        goto ProcSwim; // or just starting to jump, if just starting, skip ahead
    compare(a, M(DiffToHaltJump)); // compare to value set here to see if player is in mid-jump
    a -= M(Player_Y_Position); // subtract current from original vertical coordinate
    c = 1;
    a = M(JumpOrigin_Y_Position); // get vertical position player jumped from
    if (!z)
        goto ProcSwim; // if so, branch elsewhere
    a &= M(PreviousA_B_Buttons); // and was pressed in previous frame
    a &= A_Button; // check to see if A button is being pressed
    a = M(A_B_Buttons);
    if (!n)
        goto DumpFall; // or moving downwards, branch to falling
    y = M(Player_Y_Speed); // if player's vertical speed zero

DumpFall: // otherwise dump falling into main fractional
    writeData(VerticalForce, a);
    a = M(VerticalForceDown);

ProcSwim: // if swimming flag not set,
    writeData(VerticalForce, a); // otherwise set fractional
    a = 0x18;
    if (c)
        goto LRWater; // if not yet reached a certain position, branch ahead
    compare(a, 0x14); // check vertical position against preset value
    a = M(Player_Y_Position);
    pushReturnIndex(170);
    goto GetPlayerAnimSpeed;
Return_170: // do a sub to get animation frame timing
    if (z)
        goto LRAir; // branch ahead to last part
    a = M(SwimmingFlag);

LRWater: // check left/right controller bits (check for swimming)
    writeData(PlayerFacingDir, a); // otherwise set facing direction accordingly
    if (z)
        goto LRAir; // if not pressing any, skip
    a = M(Left_Right_Buttons);

LRAir: // check left/right controller bits (check for jumping/falling)
    pushReturnIndex(171);
    goto ImposeFriction;
Return_171: // otherwise process horizontal movement
    if (z)
        goto JSMove; // if not pressing any, skip
    a = M(Left_Right_Buttons);

JSMove: // do a sub to move player horizontally
    writeData(VerticalForce, a); // otherwise set fractional
    a = 0x28;
    if (!z)
        goto ExitMov1; // branch if not set to run
    compare(a, 0x0b); // check for specific routine selected
    a = M(GameEngineSubroutine);
    writeData(Player_X_Scroll, a); // set player's speed here, to be used for scroll later
    pushReturnIndex(172);
    goto MovePlayerHorizontally;
Return_172:

ExitMov1: // jump to move player vertically, then leave
    goto MovePlayerVertically;

ClimbingSub:
    --y; // otherwise set adder to $ff
    if (!n)
        goto MoveOnVine; // if not moving upwards, branch
    a = M(Player_Y_Speed); // get player's vertical speed
    y = 0x00; // set default adder here
    writeData(Player_YMF_Dummy, a);
    a += M(Player_Y_MoveForce); // save with carry
    c = 0; // add movement force to dummy variable
    a = M(Player_YMF_Dummy);

MoveOnVine: // store adder here
    ++x; // otherwise increment offset by 2 bytes
    ++x;
    if (c)
        goto ClimbFD; // if controller right pressed, branch ahead
    a >>= 1; // move right button controller bit to carry
    y = M(PlayerFacingDir); // get facing direction
    x = 0x00; // set default offset here
    writeData(ClimbSideTimer, y); // otherwise set timer now
    y = 0x18;
    if (!z)
        goto ExitCSub; // if timer not expired, branch to leave
    y = M(ClimbSideTimer); // otherwise check timer 
    if (z)
        goto InitCSTimer; // if not set, skip to end
    a &= M(Player_CollisionBits); // to collision flag
    a = M(Left_Right_Buttons); // compare left/right controller bits
    writeData(Player_Y_HighPos, a); // and store
    a += M(0x00); // add carry to player's page location
    a = M(Player_Y_HighPos);
    writeData(Player_Y_Position, a); // and store to move player up or down
    a += M(Player_Y_Position); // add carry to player's vertical position
    writeData(0x00, y);

ClimbFD: // check to see if facing right
    ++x; // otherwise increment by 1 byte
    if (z)
        goto CSetFDir; // if so, branch, do not increment
    --y;

CSetFDir:
    writeData(PlayerFacingDir, a); // is on vine to face player in opposite direction
    a ^= BOOST_BINARY(00000011); // invert them and store them while player
    a = M(Left_Right_Buttons); // get left/right controller bits again
    writeData(Player_PageLoc, a);
    a += M(ClimbAdderHigh + x); // from the player's page location
    a = M(Player_PageLoc); // add or subtract carry or borrow using value here
    writeData(Player_X_Position, a);
    a += M(ClimbAdderLow + x); // using value here as adder and X as offset
    c = 0; // add or subtract from player's horizontal position
    a = M(Player_X_Position);

ExitCSub: // then leave
    goto Return;

//------------------------------------------------------------------------

InitCSTimer: // initialize timer here
    goto Return;

//------------------------------------------------------------------------
    writeData(ClimbSideTimer, a);

PlayerPhysicsSub:
    ++y;
    if (!z)
        goto ProcClimb;
    a &= BOOST_BINARY(00001000); // check for pressing up
    ++y;
    if (z)
        goto ProcClimb; // if not pressing up or down, branch
    a &= M(Player_CollisionBits); // check against player's collision detection bits
    a = M(Up_Down_Buttons); // get controller bits for up/down
    y = 0x00;
    if (!z)
        goto CheckForJumping; // if not climbing, branch
    compare(a, 0x03);
    a = M(Player_State); // check player state

ProcClimb: // load value here
    a >>= 1; // otherwise divide timer setting by 2
    if (n)
        goto SetCAnim; // if climbing down, use default animation timing value
    writeData(Player_Y_Speed, x); // store as vertical speed
    x = M(Climb_Y_SpeedData + y); // load some other value here
    a = 0x08; // load default animation timing
    writeData(Player_Y_MoveForce, x); // store as vertical movement force
    x = M(Climb_Y_MForceData + y);

SetCAnim: // store animation timer setting and leave
    goto Return;

//------------------------------------------------------------------------
    writeData(PlayerAnimTimerSet, a);

CheckForJumping:
    if (z)
        goto ProcJumping;
    a &= M(PreviousA_B_Buttons); // if button not pressed in previous frame, branch
    if (z)
        goto NoJump; // if not, branch to something else
    a &= A_Button;
    a = M(A_B_Buttons); // check for A button press
    if (!z)
        goto NoJump; // skip ahead to something else
    a = M(JumpspringAnimCtrl); // if jumpspring animating, 

NoJump: // otherwise, jump to something else
    goto X_Physics;

ProcJumping:
    goto X_Physics; // if timer at zero and player still rising, do not swim
    if (!n)
        goto InitJS; // if player's vertical speed motionless or down, branch
    a = M(Player_Y_Speed); // check player's vertical speed
    if (!z)
        goto InitJS;
    a = M(JumpSwimTimer); // if jump/swim timer nonzero, branch
    if (z)
        goto NoJump; // to prevent midair jumping, otherwise continue
    a = M(SwimmingFlag); // if swimming flag not set, jump to do something else
    if (z)
        goto InitJS; // if on the ground, branch
    a = M(Player_State); // check player state

InitJS: // set jump/swim timer
    ++y;
    if (!c)
        goto ChkWtr; // note that for jumping, range is 0-4 for Y
    compare(a, 0x1c);
    ++y;
    if (!c)
        goto ChkWtr;
    compare(a, 0x19);
    ++y;
    if (!c)
        goto ChkWtr;
    compare(a, 0x10);
    ++y; // for each amount equal or exceeded
    if (!c)
        goto ChkWtr; // branch if below certain values, increment Y
    compare(a, 0x09);
    a = M(Player_XSpeedAbsolute); // check value related to walking/running speed
    writeData(Player_State, a);
    a = 0x01; // set player state to jumping/swimming
    writeData(JumpOrigin_Y_Position, a);
    a = M(Player_Y_Position);
    writeData(JumpOrigin_Y_HighPos, a); // and store them next to each other here
    a = M(Player_Y_HighPos); // get vertical high and low bytes of jump origin
    writeData(Player_Y_MoveForce, y);
    writeData(Player_YMF_Dummy, y);
    y = 0x00; // initialize vertical force and dummy variable
    writeData(JumpSwimTimer, a);
    a = 0x20;

ChkWtr: // set value here (apparently always set to 1)
    ++y; // otherwise increment to 6
    if (z)
        goto GetYPhy;
    a = M(Whirlpool_Flag); // if whirlpool flag not set, branch
    y = 0x05; // otherwise set Y to 5, range is 5-6
    if (z)
        goto GetYPhy;
    a = M(SwimmingFlag); // if swimming flag disabled, branch
    writeData(DiffToHaltJump, a);
    a = 0x01;

GetYPhy: // store appropriate jump/swim
    goto X_Physics; // from swimming above water level
    writeData(Player_Y_Speed, a); // and jump to something else to keep player
    a = 0x00; // otherwise reset player's vertical speed
    if (c)
        goto X_Physics; // if below a certain point, branch
    compare(a, 0x14); // check vertical low byte of player position
    a = M(Player_Y_Position);
    writeData(Square1SoundQueue, a); // square 1's sfx queue
    a = Sfx_EnemyStomp; // load swim/goomba stomp sound into
    if (z)
        goto PJumpSnd;
    a = M(SwimmingFlag); // if swimming flag disabled, branch
    writeData(Player_Y_Speed, a);
    a = M(PlayerYSpdData + y);
    writeData(Player_Y_MoveForce, a);
    a = M(InitMForceData + y);
    writeData(VerticalForceDown, a);
    a = M(FallMForceData + y);
    writeData(VerticalForce, a); // data here
    a = M(JumpMForceData + y);

PJumpSnd: // load big mario's jump sound by default
    a = Sfx_SmallJump; // if not, load small mario's jump sound
    if (z)
        goto SJumpSnd;
    y = M(PlayerSize); // is mario big?
    a = Sfx_BigJump;

SJumpSnd: // store appropriate jump sound in square 1 sfx queue
    writeData(Square1SoundQueue, a);

X_Physics:
    if (!c)
        goto ChkRFast; // if not branch elsewhere
    if (c)
        goto GetXPhy; // if =>$19 branch here
    compare(a, 0x19); // to mario's speed
    a = M(Player_XSpeedAbsolute); // check something that seems to be related
    if (z)
        goto ProcPRun;
    a = M(Player_State); // if mario is on the ground, branch
    writeData(0x00, y); // init value here
    y = 0x00;

ProcPRun: // if mario on the ground, increment Y
    if (!z)
        goto GetXPhy; // if set, branch
    a = M(RunningTimer); // check for running timer set
    if (!z)
        goto SetRTmr; // if pressed, skip ahead to set timer
    a &= B_Button;
    a = M(A_B_Buttons); // check for b button pressed
    if (!z)
        goto ChkRFast; // if controller bits <> moving direction, skip this part
    compare(a, M(Player_MovingDir)); // check against moving direction
    a = M(Left_Right_Buttons); // get left/right controller bits
    --y; // decrement Y by default for non-water type area
    if (z)
        goto ChkRFast; // if water type, branch
    a = M(AreaType); // check area type
    ++y;

ChkRFast: // if running timer not set or level type is water, 
    if (!c)
        goto GetXPhy; // if less than a certain amount, branch ahead
    compare(a, 0x21); // otherwise check player's walking/running speed
    a = M(Player_XSpeedAbsolute);
    if (!z)
        goto FastXSp; // if running speed set here, branch
    a = M(RunningSpeed);
    ++M(0x00); // increment Y again and temp variable in memory
    ++y;

FastXSp: // if running speed set or speed => $21 increment $00
    goto GetXPhy; // and jump ahead
    ++M(0x00);

SetRTmr: // if b button pressed, set running timer
    writeData(RunningTimer, a);
    a = 0x0a;

GetXPhy: // get maximum speed to the left
    y = 0x03; // otherwise set Y to 3
    if (!z)
        goto GetXPhy2; // if not running, skip and use old value of Y
    compare(a, 0x07); // (player entrance)
    a = M(GameEngineSubroutine); // check for specific routine running
    writeData(MaximumLeftSpeed, a);
    a = M(MaxLeftXSpdData + y);

GetXPhy2: // get maximum speed to the right
    M(FrictionAdderHigh).rol(); // then rotate carry onto d0 of friction adder high
    M(FrictionAdderLow) <<= 1; // otherwise shift d7 of friction adder low into carry
    if (z)
        goto ExitPhy; // if the same, branch to leave
    compare(a, M(Player_MovingDir)); // check facing direction against moving direction
    a = M(PlayerFacingDir);
    writeData(FrictionAdderHigh, a); // init something here
    a = 0x00;
    writeData(FrictionAdderLow, a);
    a = M(FrictionData + y); // get value using value in memory as offset
    y = M(0x00); // get other value in memory
    writeData(MaximumRightSpeed, a);
    a = M(MaxRightXSpdData + y);

ExitPhy: // and then leave
    goto Return;

//------------------------------------------------------------------------

GetPlayerAnimSpeed:
    ++y; // otherwise increment Y again
    if (c)
        goto ChkSkid; // if greater than this but not greater than first, skip increment
    compare(a, 0x0e); // compare against lower amount
    ++y; // otherwise increment Y
    if (c)
        goto SetRunSpd; // if greater than a certain amount, branch ahead
    compare(a, 0x1c); // against preset amount
    a = M(Player_XSpeedAbsolute); // check player's walking/running speed
    y = 0x00; // initialize offset in Y

ChkSkid: // get controller bits
    a = 0x00; // otherwise set zero value here
    if (!z)
        goto ProcSkid; // if left/right controller bits <> moving direction, branch
    compare(a, M(Player_MovingDir)); // check against moving direction
    a &= 0x03; // mask out all others except left and right
    if (z)
        goto SetAnimSpd; // if no other buttons pressed, branch ahead of all this
    a &= BOOST_BINARY(01111111); // mask out A button
    a = M(SavedJoypadBits);

SetRunSpd: // store zero or running speed here
    goto SetAnimSpd;
    writeData(RunningSpeed, a);

ProcSkid: // check player's walking/running speed
    writeData(Player_X_MoveForce, a); // and dummy variable for player
    writeData(Player_X_Speed, a); // nullify player's horizontal speed
    a = 0x00;
    writeData(Player_MovingDir, a); // otherwise use facing direction to set moving direction
    a = M(PlayerFacingDir);
    if (c)
        goto SetAnimSpd; // if greater than this amount, branch
    compare(a, 0x0b); // against one last amount
    a = M(Player_XSpeedAbsolute);

SetAnimSpd: // get animation timer setting using Y as offset
    goto Return;

//------------------------------------------------------------------------
    writeData(PlayerAnimTimerSet, a);
    a = M(PlayerAnimTmrData + y);

ImposeFriction:
    if (n)
        goto LeftFrict; // otherwise logic dictates player moving left, branch to slow
    if (!n)
        goto RghtFrict; // if player moving to the right, branch to slow
    if (z)
        goto SetAbsSpd; // if player has no horizontal speed, branch ahead to last part
    a = M(Player_X_Speed);
    if (!z)
        goto JoypFrict; // if any bits set, branch to next part
    compare(a, 0x00); // then compare to zero (this instruction is redundant)
    a &= M(Player_CollisionBits); // perform AND between left/right controller bits and collision flag

JoypFrict: // put right controller bit into carry
    if (!c)
        goto RghtFrict; // if left button pressed, carry = 0, thus branch
    a >>= 1;

LeftFrict: // load value set here
    goto SetAbsSpd; // skip to the end
    writeData(Player_X_Speed, a); // thus slowing the player's left movement down
    a = M(MaximumRightSpeed); // otherwise set preset value as horizontal speed
    if (n)
        goto XSpdSign; // if horizontal speed greater negatively, branch
    compare(a, M(MaximumRightSpeed)); // compare against maximum value for right movement
    writeData(Player_X_Speed, a); // set as new horizontal speed
    a += M(FrictionAdderHigh); // add value plus carry to horizontal speed
    a = M(Player_X_Speed);
    writeData(Player_X_MoveForce, a); // store here
    a += M(FrictionAdderLow); // add to it another value set here
    c = 0;
    a = M(Player_X_MoveForce);

RghtFrict: // load value set here
    writeData(Player_X_Speed, a); // thus slowing the player's right movement down
    a = M(MaximumLeftSpeed); // otherwise set preset value as horizontal speed
    if (!n)
        goto XSpdSign; // if horizontal speed greater positively, branch
    compare(a, M(MaximumLeftSpeed)); // compare against maximum value for left movement
    writeData(Player_X_Speed, a); // set as new horizontal speed
    a -= M(FrictionAdderHigh); // subtract value plus borrow from horizontal speed
    a = M(Player_X_Speed);
    writeData(Player_X_MoveForce, a); // store here
    a -= M(FrictionAdderLow); // subtract from it another value set here
    c = 1;
    a = M(Player_X_MoveForce);

XSpdSign: // if player not moving or moving to the right,
    a += 0x01; // unsigned walking/running speed
    c = 0; // otherwise get two's compliment to get absolute
    a ^= 0xff;
    if (!n)
        goto SetAbsSpd; // branch and leave horizontal speed value unmodified
    compare(a, 0x00);

SetAbsSpd: // store walking/running speed here and leave
    goto Return;

//------------------------------------------------------------------------
    writeData(Player_XSpeedAbsolute, a);

ProcFireball_Bubble:
    ++M(FireballCounter); // increment fireball counter
    writeData(PlayerAnimTimer, y); // decrement and store in player's animation timer
    --y;
    writeData(FireballThrowingTimer, y); // into fireball throwing timer
    y = M(PlayerAnimTimerSet); // copy animation frame timer setting
    writeData(Fireball_State + x, a);
    a = 0x02; // load state
    writeData(Square1SoundQueue, a);
    a = Sfx_Fireball; // play fireball sound effect
    if (z)
        goto ProcFireballs;
    compare(a, 0x03);
    a = M(Player_State); // if player's state = climbing, branch
    if (!z)
        goto ProcFireballs;
    a = M(CrouchingFlag); // if player crouching, branch
    if (!z)
        goto ProcFireballs;
    --y;
    y = M(Player_Y_HighPos); // if player too high or too low, branch
    if (!z)
        goto ProcFireballs; // if not inactive, branch
    a = M(Fireball_State + x); // load fireball state
    x = a;
    a &= BOOST_BINARY(00000001); // get LSB and use as offset for buffer
    a = M(FireballCounter); // load fireball counter
    if (!z)
        goto ProcFireballs; // if button pressed in previous frame, branch
    a &= M(PreviousA_B_Buttons);
    if (z)
        goto ProcFireballs; // branch if not pressed
    a &= B_Button; // check for b button pressed
    a = M(A_B_Buttons);
    if (!c)
        goto ProcAirBubbles; // if not fiery, branch
    compare(a, 0x02);
    a = M(PlayerStatus); // check player's status

ProcFireballs:
    pushReturnIndex(173);
    goto FireballObjCore;
Return_173: // process second fireball object, then do air bubbles
    x = 0x01;
    pushReturnIndex(174);
    goto FireballObjCore;
Return_174: // process first fireball object
    x = 0x00;

ProcAirBubbles:
    x = 0x02; // otherwise load counter and use as offset
    if (!z)
        goto BublExit;
    a = M(AreaType); // if not water type level, skip the rest of this

BublLoop: // store offset
    if (!n)
        goto BublLoop; // do this until all three are handled
    --x;
    pushReturnIndex(175);
    goto DrawBubble;
Return_175: // draw the air bubble
    pushReturnIndex(176);
    goto GetBubbleOffscreenBits;
Return_176: // get offscreen information
    pushReturnIndex(177);
    goto RelativeBubblePosition;
Return_177: // get relative coordinates
    pushReturnIndex(178);
    goto BubbleCheck;
Return_178: // check timers and coordinates, create air bubble
    writeData(ObjectOffset, x);

BublExit: // then leave
    goto Return;

//------------------------------------------------------------------------

FireballObjCore:
    --M(Fireball_State + x); // decrement state to 1 to skip this part from now on
    writeData(Fireball_BoundBoxCtrl + x, a); // set bounding box size control for fireball
    a = 0x07;
    writeData(Fireball_Y_Speed + x, a);
    a = 0x04; // set vertical speed of fireball
    writeData(Fireball_X_Speed + x, a);
    a = M(FireballXSpdData + y); // set horizontal speed of fireball accordingly
    --y; // decrement to use as offset here
    y = M(PlayerFacingDir); // get player's facing direction
    writeData(Fireball_Y_HighPos + x, a);
    a = 0x01; // set high byte of vertical position
    writeData(Fireball_Y_Position + x, a);
    a = M(Player_Y_Position); // get player's vertical position and store
    writeData(Fireball_PageLoc + x, a);
    a += 0x00; // add carry and store as fireball's page location
    a = M(Player_PageLoc); // get player's page location
    writeData(Fireball_X_Position + x, a);
    a += 0x04; // add four pixels and store as fireball's horizontal position
    a = M(Player_X_Position); // get player's horizontal position
    if (z)
        goto RunFB;
    --y; // if fireball state set to 1, skip this part and just run it
    if (z)
        goto NoFBall;
    y = M(Fireball_State + x); // if fireball inactive, branch to leave
    if (c)
        goto FireballExplosion; // if so, branch to get relative coordinates and draw explosion
    a <<= 1;
    a = M(Fireball_State + x); // check for d7 = 1
    writeData(ObjectOffset, x); // store offset as current object

RunFB: // add 7 to offset to use
    goto DrawFireball; // draw fireball appropriately and leave
    pushReturnIndex(179);
    goto FireballEnemyCollision;
Return_179: // do fireball to enemy collision detection and deal with collisions
    if (!z)
        goto EraseFB; // if any bits still set, branch to kill fireball
    a &= BOOST_BINARY(11001100); // mask out certain bits
    a = M(FBall_OffscreenBits); // get fireball offscreen bits
    pushReturnIndex(180);
    goto FireballBGCollision;
Return_180: // do fireball to background collision detection
    pushReturnIndex(181);
    goto GetFireballBoundBox;
Return_181: // get bounding box coordinates
    pushReturnIndex(182);
    goto GetFireballOffscreenBits;
Return_182: // get offscreen information
    pushReturnIndex(183);
    goto RelativeFireballPosition;
Return_183: // get relative coordinates
    x = M(ObjectOffset); // return fireball offset to X
    pushReturnIndex(184);
    goto MoveObjectHorizontally;
Return_184: // do another sub to move it horizontally
    pushReturnIndex(185);
    goto ImposeGravity;
Return_185: // do sub here to impose gravity on fireball and move vertically
    a = 0x00;
    writeData(0x02, a);
    a = 0x03; // set maximum speed here
    writeData(0x00, a);
    a = 0x50; // set downward movement force here
    x = a;
    a += 0x07;
    c = 0; // as fireball offset for next routines
    a = x;

EraseFB: // erase fireball state
    writeData(Fireball_State + x, a);
    a = 0x00;

NoFBall: // leave
    goto Return;

//------------------------------------------------------------------------

FireballExplosion:
    goto DrawExplosion_Fireball;
    pushReturnIndex(186);
    goto RelativeFireballPosition;
Return_186:

BubbleCheck:
    if (!z)
        goto ExitBubl; // branch to leave, otherwise create new air bubble
    a = M(AirBubbleTimer); // if air bubble timer not expired,
    if (!z)
        goto MoveBubl; // branch to move air bubble
    compare(a, 0xf8); // if offscreen coordinate not set,
    a = M(Bubble_Y_Position + x); // get vertical coordinate for air bubble
    writeData(0x07, a); // store pseudorandom bit here
    a &= 0x01;
    a = M(PseudoRandomBitReg + 1 + x); // get part of LSFR

SetupBubble:
    y = 0x08; // otherwise load alternate value here
    if (!c)
        goto PosBubl; // branch to use default value if facing left
    a >>= 1; // move d0 to carry
    a = M(PlayerFacingDir); // get player's facing direction
    y = 0x00; // load default value here

PosBubl: // use value loaded as adder
    writeData(AirBubbleTimer, a); // set air bubble timer
    a = M(BubbleTimerData + y); // get data for air bubble timer
    y = M(0x07); // get pseudorandom bit, use as offset
    writeData(Bubble_Y_HighPos + x, a); // set vertical high byte for air bubble
    a = 0x01;
    writeData(Bubble_Y_Position + x, a); // save as vertical position for air bubble
    a += 0x08;
    c = 0; // add eight pixels to player's vertical position
    a = M(Player_Y_Position);
    writeData(Bubble_PageLoc + x, a); // save as page location for airbubble
    a += 0x00; // add carry to player's page location
    a = M(Player_PageLoc);
    writeData(Bubble_X_Position + x, a); // save as horizontal position for airbubble
    a += M(Player_X_Position); // add to player's horizontal position
    a = y;

MoveBubl: // get pseudorandom bit again, use as offset
    a = 0xf8; // otherwise set offscreen coordinate
    if (c)
        goto Y_Bubl; // branch to go ahead and use to move air bubble upwards
    compare(a, 0x20); // if below the status bar,
    a -= 0x00; // subtract borrow from airbubble's vertical coordinate
    a = M(Bubble_Y_Position + x);
    writeData(Bubble_YMF_Dummy + x, a); // save dummy variable
    a -= M(Bubble_MForceData + y);
    c = 1; // subtract pseudorandom amount from dummy variable
    a = M(Bubble_YMF_Dummy + x);
    y = M(0x07);

Y_Bubl: // store as new vertical coordinate for air bubble
    writeData(Bubble_Y_Position + x, a);

ExitBubl: // leave
    goto Return;

//------------------------------------------------------------------------

RunGameTimer:
    writeData(EventMusicQueue, a); // otherwise load time running out music
    a = TimeRunningOutMusic;
    if (!z)
        goto ResGTCtrl; // if timer not at 100, branch to reset game timer control
    a |= M(GameTimerDisplay + 2);
    a = M(GameTimerDisplay + 1); // otherwise check second and third digits
    if (!z)
        goto ResGTCtrl; // branch to reset game timer control
    --y; // if first digit not on 1,
    y = M(GameTimerDisplay); // otherwise check first digit
    if (z)
        goto TimeUpOn; // if game timer digits at 000, branch to time-up code
    a |= M(GameTimerDisplay + 2);
    a |= M(GameTimerDisplay + 1); // otherwise check game timer digits
    a = M(GameTimerDisplay);
    if (!z)
        goto ExGTimer; // branch to leave
    a = M(GameTimerCtrlTimer); // if game timer control not yet expired,
    if (c)
        goto ExGTimer; // branch to leave regardless of level type
    compare(a, 0x02); // if player below the screen,
    a = M(Player_Y_HighPos);
    if (z)
        goto ExGTimer; // branch to leave
    compare(a, 0x0b); // if running death routine,
    if (!c)
        goto ExGTimer; // branch to leave
    compare(a, 0x08); // if routine number less than eight running,
    a = M(GameEngineSubroutine);
    if (z)
        goto ExGTimer; // branch to leave if in title screen mode
    a = M(OperMode); // get primary mode of operation

ResGTCtrl: // reset game timer control
    goto PrintStatusBarNumbers; // do sub to update the display
    a = 0xa4; // set status nybbles to update game timer display
    pushReturnIndex(187);
    goto DigitsMathRoutine;
Return_187: // do sub to decrement game timer slowly
    writeData(DigitModifier + 5, a);
    a = 0xff; // set value to decrement game timer digit
    y = 0x23; // set offset for last digit
    writeData(GameTimerCtrlTimer, a);
    a = 0x18;

TimeUpOn: // init player status (note A will always be zero here)
    ++M(GameTimerExpiredFlag); // set game timer expiration flag
    pushReturnIndex(188);
    goto ForceInjury;
Return_188: // do sub to kill the player (note player is small here)
    writeData(PlayerStatus, a);

ExGTimer: // leave
    goto Return;

//------------------------------------------------------------------------

WarpZoneObject:
    goto EraseEnemyObject; // kill this object
    ++M(WarpZoneControl); // increment warp zone flag to make warp pipes for warp zone
    writeData(ScrollLock, a); // otherwise nullify scroll lock flag
    if (!z)
        goto ExGTimer; // if so, branch to leave
    a &= M(Player_Y_HighPos); // same bits set as in vertical high byte (why?)
    a = M(Player_Y_Position); // check to see if player's vertical coordinate has
    if (z)
        goto ExGTimer; // branch if not set to leave
    a = M(ScrollLock); // check for scroll lock flag

ProcessWhirlpools:
    y = 0x04; // otherwise start with last whirlpool data
    if (!z)
        goto ExitWh; // branch to leave
    a = M(TimerControl); // if master timer control set,
    writeData(Whirlpool_Flag, a); // otherwise initialize whirlpool flag
    if (!z)
        goto ExitWh; // branch to leave if not found
    a = M(AreaType); // check for water type level

WhLoop: // get left extent of whirlpool
    if (!n)
        goto WhirlpoolActivate; // if player within right extent, branch to whirlpool code
    a -= M(Player_PageLoc); // subtract borrow
    a = M(0x01); // get right extent's page location
    a -= M(Player_X_Position); // subtract player's horizontal coordinate
    c = 1;
    a = M(0x02); // otherwise get right extent
    if (n)
        goto NextWh; // if player too far left, branch to get next data
    a -= M(Whirlpool_PageLoc + y); // subtract borrow
    a = M(Player_PageLoc); // get player's page location
    a -= M(Whirlpool_LeftExtent + y); // subtract left extent
    c = 1;
    a = M(Player_X_Position); // get player's horizontal position
    writeData(0x01, a); // store result as page location of right extent here
    a += 0x00; // add carry
    if (z)
        goto NextWh; // if none or page 0, branch to get next data
    a = M(Whirlpool_PageLoc + y); // get page location
    writeData(0x02, a); // store result as right extent here
    a += M(Whirlpool_Length + y); // add length of whirlpool
    c = 0;
    a = M(Whirlpool_LeftExtent + y);

NextWh: // move onto next whirlpool data
    if (!n)
        goto WhLoop; // do this until all whirlpools are checked
    --y;

ExitWh: // leave
    goto Return;

//------------------------------------------------------------------------

WhirlpoolActivate:
    goto SetPWh; // jump to set player's new page location
    a -= 0x00; // subtract borrow
    a = M(Player_PageLoc);
    writeData(Player_X_Position, a); // set player's new horizontal coordinate
    a -= 0x01; // subtract one pixel
    c = 1;
    a = M(Player_X_Position); // otherwise slowly pull player left, towards the center
    if (!n)
        goto LeftWh; // if player to the left of center, branch
    a -= M(Player_PageLoc); // subtract borrow
    a = M(0x00); // get page location of center
    a -= M(Player_X_Position); // subtract player's horizontal coordinate
    c = 1;
    a = M(0x01); // get center
    if (!c)
        goto WhPull; // if d0 not set, branch to last part of code
    a >>= 1; // shift d0 into carry (to run on every other frame)
    a = M(FrameCounter); // get frame counter
    writeData(0x00, a); // save as page location of whirlpool center
    a += 0x00; // add carry
    a = M(Whirlpool_PageLoc + y); // get page location
    writeData(0x01, a); // save as center of whirlpool
    a += M(0x00); // add length divided by 2
    c = 0;
    a = M(Whirlpool_LeftExtent + y); // get left extent of whirlpool
    writeData(0x00, a); // save here
    a >>= 1; // divide by 2
    a = M(Whirlpool_Length + y); // get length of whirlpool

LeftWh: // get player's collision bits
    a += 0x00; // add carry
    a = M(Player_PageLoc);
    writeData(Player_X_Position, a); // set player's new horizontal coordinate
    a += 0x01; // add one pixel
    c = 0;
    a = M(Player_X_Position); // otherwise slowly pull player right, towards the center
    if (!c)
        goto WhPull; // if d0 not set, branch
    a >>= 1; // shift d0 into carry
    a = M(Player_CollisionBits);

SetPWh: // set player's new page location
    writeData(Player_PageLoc, a);

WhPull:
    goto ImposeGravity; // jump to put whirlpool effect on player vertically, do not return
    x = a; // set X for player offset
    a >>= 1;
    writeData(0x02, a); // also set maximum vertical speed
    writeData(Whirlpool_Flag, a); // set whirlpool flag to be used later
    a = 0x01;
    writeData(0x00, a); // set vertical movement force
    a = 0x10;

FlagpoleRoutine:
    writeData(FlagpoleFNum_Y_Pos, a); // and store vertical coordinate here
    a -= 0x01; // subtract one plus borrow to move floatey number,
    a = M(FlagpoleFNum_Y_Pos);
    writeData(FlagpoleFNum_YMFDummy, a); // save dummy variable
    a -= 0xff;
    c = 1; // subtract movement amount from dummy variable
    a = M(FlagpoleFNum_YMFDummy);
    writeData(Enemy_Y_Position + x, a); // store vertical coordinate
    a += 0x01; // add 1 plus carry to move flag, and
    a = M(Enemy_Y_Position + x); // get flag's vertical coordinate
    writeData(Enemy_YMF_Dummy + x, a); // save dummy variable
    a += 0xff; // add movement amount to dummy variable
    a = M(Enemy_YMF_Dummy + x);
    if (c)
        goto GiveFPScr; // branch to end the level
    compare(a, 0xa2); // if player down to a certain point,
    a = M(Player_Y_Position); // check player's vertical coordinate
    if (c)
        goto GiveFPScr; // branch to end the level
    compare(a, 0xaa); // if flagpole flag down to a certain point,
    a = M(Enemy_Y_Position + x); // check flagpole flag's vertical coordinate
    if (!z)
        goto SkipScore; // branch to near the end of code
    compare(a, 0x03); // if player state not climbing,
    a = M(Player_State);
    if (!z)
        goto SkipScore; // branch to near the end of code
    compare(a, 0x04); // if flagpole slide routine not running,
    a = M(GameEngineSubroutine);
    if (!z)
        goto ExitFlagP; // branch to leave
    compare(a, FlagpoleFlagObject); // if flagpole flag not found,
    a = M(Enemy_ID + x);
    writeData(ObjectOffset, x); // to special use slot
    x = 0x05; // set enemy object offset

SkipScore: // jump to skip ahead and draw flag and floatey number
    goto FPGfx;

GiveFPScr: // get score offset from earlier (when player touched flagpole)
    writeData(GameEngineSubroutine, a); // set to run end-of-level subroutine on next frame
    a = 0x05;
    pushReturnIndex(189);
    goto AddToScore;
Return_189: // do sub to award player points depending on height of collision
    writeData(DigitModifier + x, a); // store in digit modifier
    x = M(FlagpoleScoreDigits + y); // get digit with which to award points
    a = M(FlagpoleScoreMods + y); // get amount to award player points
    y = M(FlagpoleScore);

FPGfx: // get offscreen information
    pushReturnIndex(190);
    goto FlagpoleGfxHandler;
Return_190: // draw flagpole flag and floatey number
    pushReturnIndex(191);
    goto RelativeEnemyPosition;
Return_191: // get relative coordinates
    pushReturnIndex(192);
    goto GetEnemyOffscreenBits;
Return_192:

ExitFlagP:
    goto Return;

//------------------------------------------------------------------------

JumpspringHandler:
    goto PosJSpr; // skip to next part
    ++M(Player_Y_Position); // move player's vertical position down two pixels
    ++M(Player_Y_Position);
    if (!z)
        goto DownJSpr; // if set, branch to move player up
    a &= BOOST_BINARY(00000010); // mask out all but d1, original value still in Y
    a = y; // the only way a poor nmos 6502 can
    --y; // subtract one from frame control,
    y = a;
    if (z)
        goto DrawJSpr; // branch to last section if not set
    a = M(JumpspringAnimCtrl); // check jumpspring frame control
    if (!z)
        goto DrawJSpr; // branch to last section if set
    a = M(TimerControl); // check master timer control
    pushReturnIndex(193);
    goto GetEnemyOffscreenBits;
Return_193: // get offscreen information

DownJSpr: // move player's vertical position up two pixels
    --M(Player_Y_Position);
    --M(Player_Y_Position);

PosJSpr: // get permanent vertical position
    writeData(JumpspringForce, a); // otherwise write new jumpspring force here
    a = 0xf4;
    if (!z)
        goto BounceJS; // skip to next part if so
    a &= M(PreviousA_B_Buttons); // check for A button pressed in previous frame
    if (z)
        goto BounceJS; // skip to next part if A not pressed
    a &= A_Button; // check saved controller bits for A button press
    a = M(A_B_Buttons);
    if (!c)
        goto BounceJS; // if offset not yet at third frame ($01), skip to next part
    compare(y, 0x01); // check frame control offset (second frame is $00)
    writeData(Enemy_Y_Position + x, a); // store as new vertical position
    a += M(Jumpspring_Y_PosData + y); // add value using frame control as offset
    c = 0;
    a = M(Jumpspring_FixedYPos + x);

BounceJS: // check frame control offset again
    writeData(JumpspringAnimCtrl, a); // initialize jumpspring frame control
    a = 0x00;
    writeData(Player_Y_Speed, a); // store jumpspring force as player's new vertical speed
    a = M(JumpspringForce);
    if (!z)
        goto DrawJSpr; // skip to last part if not yet at fifth frame ($03)
    compare(y, 0x03);

DrawJSpr: // get jumpspring's relative coordinates
    ++M(JumpspringAnimCtrl); // increment frame control to animate jumpspring
    writeData(JumpspringTimer, a); // otherwise initialize jumpspring timer
    a = 0x04;
    if (!z)
        goto ExJSpring; // if jumpspring timer not expired yet, leave
    a = M(JumpspringTimer);
    if (z)
        goto ExJSpring; // trying to animate it, just leave
    a = M(JumpspringAnimCtrl); // if frame control at zero, don't bother
    pushReturnIndex(194);
    goto OffscreenBoundsCheck;
Return_194: // check to see if we need to kill it
    pushReturnIndex(195);
    goto EnemyGfxHandler;
Return_195: // draw jumpspring
    pushReturnIndex(196);
    goto RelativeEnemyPosition;
Return_196:

ExJSpring: // leave
    goto Return;

//------------------------------------------------------------------------

Setup_Vine:
    writeData(VineStart_Y_Position, a); // otherwise store vertical coordinate here
    if (!z)
        goto NextVO; // if set at all, don't bother to store vertical
    y = M(VineFlagOffset); // load vine flag/offset to next available vine slot
    writeData(Enemy_Y_Position + x, a); // copy vertical coordinate from previous object
    a = M(Block_Y_Position + y);
    writeData(Enemy_X_Position + x, a); // copy horizontal coordinate from previous object
    a = M(Block_X_Position + y);
    writeData(Enemy_PageLoc + x, a); // copy page location from previous object
    a = M(Block_PageLoc + y);
    writeData(Enemy_Flag + x, a); // set flag for enemy object buffer
    a = 0x01;
    writeData(Enemy_ID + x, a); // store in buffer
    a = VineObject; // load identifier for vine object

NextVO: // store object offset to next available vine slot
    goto Return;

//------------------------------------------------------------------------
    writeData(Square2SoundQueue, a); // load vine grow sound
    a = Sfx_GrowVine;
    ++M(VineFlagOffset); // increment vine flag offset
    writeData(VineObjOffset + y, a); // using vine flag as offset
    a = x;

VineObjectHandler:
    ++M(VineHeight); // increment vine height
    writeData(Enemy_Y_Position + 5, a); // one pixel every frame it's time
    a -= 0x01; // subtract vertical position of vine
    a = M(Enemy_Y_Position + 5);
    if (!c)
        goto RunVSubs; // if d1 not set (2 frames every 4) skip this part
    a >>= 1;
    a >>= 1; // shift d1 into carry
    a = M(FrameCounter); // get frame counter
    if (z)
        goto RunVSubs; // branch ahead to skip this part
    compare(a, M(VineHeightData + y)); // if vine has reached certain height,
    a = M(VineHeight);
    --y; // decrement vine flag in Y, use as offset
    y = M(VineFlagOffset);
    if (!z)
        goto ExitVH; // if not in last slot, branch to leave
    compare(x, 0x05); // check enemy offset for special use slot

RunVSubs: // if vine still very small,
    y = 0x00; // initialize offset used in draw vine sub
    pushReturnIndex(197);
    goto GetEnemyOffscreenBits;
Return_197: // and any offscreen bits
    pushReturnIndex(198);
    goto RelativeEnemyPosition;
Return_198: // get relative coordinates of vine,
    if (!c)
        goto ExitVH;
    compare(a, 0x08); // branch to leave
    a = M(VineHeight);

VDrawLoop: // draw vine
    --y; // otherwise decrement Y to get proper offset again
    if (z)
        goto WrCMTile; // if none of the saved offscreen bits set, skip ahead
    a &= BOOST_BINARY(00001100); // mask offscreen bits
    a = M(Enemy_OffscreenBits);
    if (!z)
        goto VDrawLoop; // do not yet match, loop back to draw more vine
    compare(y, M(VineFlagOffset)); // if offset in Y and offset here
    ++y; // increment offset
    pushReturnIndex(199);
    goto DrawVine;
Return_199:

KillVine: // get enemy object offset for this vine object
    writeData(VineHeight, a); // initialize vine height
    writeData(VineFlagOffset, a); // initialize vine flag/offset
    if (!n)
        goto KillVine; // if any vine objects left, loop back to kill it
    --y; // decrement Y
    pushReturnIndex(200);
    goto EraseEnemyObject;
Return_200: // kill this vine object
    x = M(VineObjOffset + y);

WrCMTile: // check vine height
    writeData(W(0x06) + y, a); // otherwise, write climbing metatile to block buffer
    a = 0x26;
    if (!z)
        goto ExitVH; // current offset, if not empty, branch to leave
    a = M(W(0x06) + y); // otherwise check contents of block buffer at 
    if (c)
        goto ExitVH; // current block buffer, branch to leave, do not write
    compare(y, 0xd0); // if vertical high nybble offset beyond extent of
    y = M(0x02);
    pushReturnIndex(201);
    goto BlockBufferCollision;
Return_201: // do a sub to get block buffer address set, return contents
    y = 0x1b; // set Y to offset to get block at ($04, $10) of coordinates
    a = 0x01; // set A to obtain horizontal in $04, but we don't care
    x = 0x06; // set offset in X to last enemy slot
    if (!c)
        goto ExitVH; // then branch ahead to leave
    compare(a, 0x20); // if vine small (less than 32 pixels tall)
    a = M(VineHeight);

ExitVH: // get enemy object offset and leave
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

ProcessCannons:
    x = 0x02;
    if (z)
        goto ExCannon; // if water type area, branch to leave
    a = M(AreaType); // get area type

ThreeSChk: // start at third enemy slot
    goto Chk_BB; // then jump ahead to check enemy
    writeData(Cannon_Timer + y, a); // to count timer down
    a -= 0x00; // otherwise subtract borrow (note carry will always be clear here)
    if (z)
        goto FireCannon; // if expired, branch to fire cannon
    a = M(Cannon_Timer + y); // get cannon timer
    if (z)
        goto Chk_BB; // if not set or on page 0, branch to check enemy
    a = M(Cannon_PageLoc + y); // get page location
    y = a; // transfer masked contents of LSFR to Y as pseudorandom offset
    if (c)
        goto Chk_BB; // if so, branch to check enemy
    compare(a, 0x06); // check to see if lower nybble is above certain value
    a &= M(CannonBitmasks + y); // mask out bits of LSFR as decided by flag
    y = M(SecondaryHardMode); // get secondary hard mode flag, use as offset
    a = M(PseudoRandomBitReg + 1 + x); // otherwise get part of LSFR
    if (!z)
        goto Chk_BB; // if set, branch to check enemy
    a = M(Enemy_Flag + x); // check enemy buffer flag
    writeData(ObjectOffset, x);

FireCannon:
    goto Next3Slt; // move onto next slot
    writeData(Enemy_ID + x, a); // load identifier for bullet bill (cannon variant)
    a = BulletBill_CannonVar;
    writeData(Enemy_BoundBoxCtrl + x, a); // set bounding box size control for bullet bill
    a = 0x09;
    writeData(Enemy_State + x, a); // then initialize enemy's state
    a >>= 1; // shift right once to init A
    writeData(Enemy_Flag + x, a); // set buffer flag
    writeData(Enemy_Y_HighPos + x, a); // set vertical high byte of bullet bill
    a = 0x01;
    writeData(Enemy_Y_Position + x, a); // save as vertical coordinate of bullet bill
    a -= 0x08; // subtract eight pixels (because enemies are 24 pixels tall)
    c = 1;
    a = M(Cannon_Y_Position + y); // get vertical coordinate of cannon
    writeData(Enemy_X_Position + x, a); // save as horizontal coordinate of bullet bill
    a = M(Cannon_X_Position + y); // get horizontal coordinate of cannon
    writeData(Enemy_PageLoc + x, a); // save as page location of bullet bill
    a = M(Cannon_PageLoc + y); // get page location of cannon
    writeData(Cannon_Timer + y, a); // first, reset cannon timer
    a = 0x0e; // otherwise we start creating one
    if (!z)
        goto Chk_BB; // branch to check enemy
    a = M(TimerControl); // if master timer control set,

Chk_BB: // check enemy identifier for bullet bill (cannon variant)
    pushReturnIndex(202);
    goto BulletBillHandler;
Return_202: // then do sub to handle bullet bill
    pushReturnIndex(203);
    goto GetEnemyOffscreenBits;
Return_203: // otherwise, get offscreen information
    if (z)
        goto Next3Slt; // if not set, branch to get next slot
    a = M(Enemy_Flag + x); // check enemy buffer flag
    pushReturnIndex(204);
    goto OffscreenBoundsCheck;
Return_204: // otherwise, check to see if it went offscreen
    if (!z)
        goto Next3Slt; // if not found, branch to get next slot
    compare(a, BulletBill_CannonVar);
    a = M(Enemy_ID + x);

Next3Slt: // move onto next slot
    if (!n)
        goto ThreeSChk; // do this until first three slots are checked
    --x;

ExCannon: // then leave
    goto Return;

//------------------------------------------------------------------------

BulletBillHandler:
    ++y; // otherwise increment to move left
    if (n)
        goto SetupBB; // if enemy to the left of player, branch
    pushReturnIndex(205);
    goto PlayerEnemyDiff;
Return_205: // get horizontal difference between player and bullet bill
    y = 0x01; // set to move right by default
    if (z)
        goto KillBB; // if so, branch to kill this object
    compare(a, BOOST_BINARY(00001100)); // check to see if all bits are set
    a &= BOOST_BINARY(00001100); // mask out bits
    a = M(Enemy_OffscreenBits); // otherwise load offscreen bits
    if (!z)
        goto ChkDSte; // if bullet bill's state set, branch to check defeated state
    a = M(Enemy_State + x);
    if (!z)
        goto RunBBSubs; // branch to run subroutines except movement sub
    a = M(TimerControl); // if master timer control set,

SetupBB: // set bullet bill's moving direction
    writeData(Square2SoundQueue, a); // play fireworks/gunfire sound
    a = Sfx_Blast;
    writeData(EnemyFrameTimer + x, a); // set enemy frame timer
    a = 0x0a;
    writeData(Enemy_State + x, a); // otherwise set bullet bill's state
    a = 0x01;
    if (!c)
        goto KillBB; // to cannon either on left or right side, thus branch
    compare(a, 0x50); // if less than a certain amount, player is too close
    a += 0x28; // add 40 pixels
    a = M(0x00); // get horizontal difference
    writeData(Enemy_X_Speed + x, a); // and store it
    a = M(BulletBillXSpdData + y); // get horizontal speed based on moving direction
    --y; // decrement to use as offset
    writeData(Enemy_MovingDir + x, y);

ChkDSte: // check enemy state for d5 set
    pushReturnIndex(206);
    goto MoveD_EnemyVertically;
Return_206: // otherwise do sub to move bullet bill vertically
    if (z)
        goto BBFly; // if not set, skip to move horizontally
    a &= BOOST_BINARY(00100000);
    a = M(Enemy_State + x);

BBFly: // do sub to move bullet bill horizontally
    pushReturnIndex(207);
    goto MoveEnemyHorizontally;
Return_207:

RunBBSubs: // get offscreen information
    goto EnemyGfxHandler; // draw the bullet bill and leave
    pushReturnIndex(208);
    goto PlayerEnemyCollision;
Return_208: // handle player to enemy collisions
    pushReturnIndex(209);
    goto GetEnemyBoundBox;
Return_209: // get bounding box coordinates
    pushReturnIndex(210);
    goto RelativeEnemyPosition;
Return_210: // get relative coordinates
    pushReturnIndex(211);
    goto GetEnemyOffscreenBits;
Return_211:

KillBB: // kill bullet bill and leave
    goto Return;

//------------------------------------------------------------------------
    pushReturnIndex(212);
    goto EraseEnemyObject;
Return_212:

SpawnHammerObj:
    a &= BOOST_BINARY(00001000); // get d3 from same part of LSFR
    a = M(PseudoRandomBitReg + 1);
    if (!z)
        goto SetMOfs; // if any bits are set, branch and use as offset
    a &= BOOST_BINARY(00000111); // second part of LSFR
    a = M(PseudoRandomBitReg + 1); // get pseudorandom bits from

SetMOfs: // use either d3 or d2-d0 for offset here
    goto Return;

//------------------------------------------------------------------------
    c = 1; // return with carry set
    writeData(Misc_BoundBoxCtrl + y, a); // set something else entirely, here
    a = 0x07;
    writeData(Misc_State + y, a); // save hammer's state here
    a = 0x90;
    writeData(HammerEnemyOffset + y, a); // save here
    a = x;
    x = M(ObjectOffset); // get original enemy object offset
    if (!z)
        goto NoHammer; // if buffer flag set, branch to leave with carry clear
    a = M(Enemy_Flag + x); // check enemy buffer flag at offset
    x = M(HammerEnemyOfsData + y); // get offset of enemy slot to check using Y as offset
    if (!z)
        goto NoHammer; // $2a-$32 where offset is then leave with carry clear
    a = M(Misc_State + y); // if any values loaded in
    y = a;

NoHammer: // get original enemy object offset
    goto Return;

//------------------------------------------------------------------------
    c = 0; // return with carry clear
    x = M(ObjectOffset);

ProcHammerObj:
    goto RunAllH; // branch to essential subroutines
    x = M(ObjectOffset); // get original misc object offset
    pushReturnIndex(213);
    goto MoveObjectHorizontally;
Return_213: // do sub to move it horizontally
    pushReturnIndex(214);
    goto ImposeGravity;
Return_214: // do sub to impose gravity on hammer and move vertically
    a = 0x00; // set A to impose gravity on hammer
    writeData(0x02, a); // set maximum vertical speed
    a = 0x04;
    writeData(0x01, a); // set upward movement force (not used)
    a = 0x0f;
    writeData(0x00, a); // set downward movement force
    a = 0x10;
    x = a; // return offset to X
    a += 0x0d; // proper misc object
    c = 0; // add 13 bytes to use
    a = x;
    if (c)
        goto SetHPos; // if greater than 2, branch elsewhere
    if (z)
        goto SetHSpd; // if currently at 2, branch
    compare(a, 0x02); // check hammer's state
    y = M(HammerEnemyOffset + x); // get enemy object offset that spawned this hammer
    a &= BOOST_BINARY(01111111); // mask out d7
    a = M(Misc_State + x); // otherwise get hammer's state
    if (!z)
        goto RunHSubs; // skip all of this code and go to last subs at the end
    a = M(TimerControl); // if master timer control set

SetHSpd:
    writeData(Misc_X_Speed + x, a); // set hammer's horizontal speed
    x = M(ObjectOffset); // reobtain hammer's buffer offset
    a = M(HammerXSpdData + x); // get proper speed to use based on moving direction
    --x; // decrement to use as offset
    x = M(Enemy_MovingDir + y); // get enemy's moving direction
    writeData(Enemy_State + y, a); // store new state
    a &= BOOST_BINARY(11110111); // mask out d3
    a = M(Enemy_State + y); // get enemy object state
    writeData(Misc_Y_Speed + x, a); // set hammer's vertical speed
    a = 0xfe;

SetHPos: // decrement hammer's state
    if (!z)
        goto RunHSubs; // unconditional branch to skip first routine
    writeData(Misc_Y_HighPos + x, a); // set hammer's vertical high byte
    a = 0x01;
    writeData(Misc_Y_Position + x, a); // store as hammer's vertical position
    a -= 0x0a; // move position 10 pixels upward
    c = 1;
    a = M(Enemy_Y_Position + y); // get enemy's vertical position
    writeData(Misc_PageLoc + x, a); // store as hammer's page location
    a += 0x00; // add carry
    a = M(Enemy_PageLoc + y); // get enemy's page location
    writeData(Misc_X_Position + x, a); // store as hammer's horizontal position
    a += 0x02; // set position 2 pixels to the right
    c = 0;
    a = M(Enemy_X_Position + y); // get enemy's horizontal position
    --M(Misc_State + x);

RunAllH: // handle collisions
    pushReturnIndex(215);
    goto PlayerHammerCollision;
Return_215:

RunHSubs: // get offscreen information
    goto Return; // and we are done here

//------------------------------------------------------------------------
    pushReturnIndex(216);
    goto DrawHammer;
Return_216: // draw the hammer
    pushReturnIndex(217);
    goto GetMiscBoundBox;
Return_217: // get bounding box coordinates
    pushReturnIndex(218);
    goto RelativeMiscPosition;
Return_218: // get relative coordinates
    pushReturnIndex(219);
    goto GetMiscOffscreenBits;
Return_219:

CoinBlock:
    goto JCoinC; // jump to rest of code as applies to this misc object
    writeData(Misc_Y_Position + y, a); // store as vertical coordinate of misc object
    a -= 0x10; // subtract 16 pixels
    a = M(Block_Y_Position + x); // get vertical coordinate of block object
    writeData(Misc_X_Position + y, a); // store as horizontal coordinate of misc object
    a |= 0x05; // add 5 pixels
    a = M(Block_X_Position + x); // get horizontal coordinate of block object
    writeData(Misc_PageLoc + y, a); // store as page location of misc object
    a = M(Block_PageLoc + x); // get page location of block object
    pushReturnIndex(220);
    goto FindEmptyMiscSlot;
Return_220: // set offset for empty or last misc object buffer slot

SetupJumpCoin:
    writeData(Misc_Y_Position + y, a); // store as vertical coordinate
    a += 0x20; // add 32 pixels for the status bar
    a = M(0x02); // get vertical high nybble offset from earlier
    writeData(Misc_X_Position + y, a); // save as horizontal coordinate for misc object
    a |= 0x05; // add five pixels
    a <<= 1;
    a <<= 1;
    a <<= 1; // multiply by 16 to use lower nybble
    a <<= 1;
    a = M(0x06); // get low byte of block buffer offset
    writeData(Misc_PageLoc + y, a); // and save as page location for misc object
    a = M(Block_PageLoc2 + x); // get page location saved earlier
    pushReturnIndex(221);
    goto FindEmptyMiscSlot;
Return_221: // set offset for empty or last misc object buffer slot

JCoinC:
    goto Return;

//------------------------------------------------------------------------
    ++M(CoinTallyFor1Ups); // increment coin tally used to activate 1-up block flag
    pushReturnIndex(222);
    goto GiveOneCoin;
Return_222: // update coin tally on the screen and coin amount variable
    writeData(ObjectOffset, x); // store current control bit as misc object offset 
    writeData(Square2SoundQueue, a); // load coin grab sound
    writeData(Misc_State + y, a); // set state for misc object
    writeData(Misc_Y_HighPos + y, a); // set vertical high byte
    a = 0x01;
    writeData(Misc_Y_Speed + y, a); // set vertical speed
    a = 0xfb;

FindEmptyMiscSlot:
    y = 0x08; // start at end of misc objects buffer

FMiscLoop: // get misc object state
    y = 0x08; // if no empty slots found, use last slot
    if (!z)
        goto FMiscLoop; // do this until all slots are checked
    compare(y, 0x05); // do this for three slots
    --y; // decrement offset
    if (z)
        goto UseMiscS; // branch if none found to use current offset
    a = M(Misc_State + y);

UseMiscS: // store offset of misc object buffer here (residual)
    goto Return;

//------------------------------------------------------------------------
    writeData(JumpCoinMiscOffset, y);

MiscObjectsCore:
    x = 0x08; // set at end of misc object buffer

MiscLoop: // store misc object offset here
    goto MiscLoopBack; // then check next slot
    pushReturnIndex(223);
    goto ProcHammerObj;
Return_223: // otherwise go to process hammer,
    if (!c)
        goto ProcJumpCoin; // if d7 not set, jumping coin, thus skip to rest of code here
    a <<= 1; // otherwise shift d7 into carry
    if (z)
        goto MiscLoopBack; // branch to check next slot
    a = M(Misc_State + x); // check misc object state
    writeData(ObjectOffset, x);

ProcJumpCoin:
    goto MiscLoopBack; // and move onto next slot
    writeData(Misc_State + x, a); // otherwise nullify object state
    a = 0x00;
    if (!z)
        goto RunJCSubs; // if not yet reached, branch to subroutines
    compare(a, 0x30); // check state of object for preset value
    a = M(Misc_State + x);
    writeData(Misc_PageLoc + x, a); // store as new page location
    a += 0x00; // add carry
    a = M(Misc_PageLoc + x); // get page location
    writeData(Misc_X_Position + x, a); // store as new horizontal coordinate
    a += M(ScrollAmount); // add current scroll speed
    c = 0; // whether its jumping coin (state 0 only) or floatey number
    a = M(Misc_X_Position + x); // get horizontal coordinate for misc object
    ++M(Misc_State + x); // otherwise increment state to either start off or as timer
    if (z)
        goto JCoinRun; // if so, branch to handle jumping coin
    --y; // decrement to see if it's set to 1
    y = M(Misc_State + x); // check misc object state

JCoinRun:
    ++M(Misc_State + x); // otherwise increment state to change to floatey number
    if (!z)
        goto RunJCSubs; // if not moving downward fast enough, keep state as-is
    compare(a, 0x05);
    a = M(Misc_Y_Speed + x); // check vertical speed
    x = M(ObjectOffset); // get original misc object offset
    pushReturnIndex(224);
    goto ImposeGravity;
Return_224: // do sub to move coin vertically and impose gravity on it
    a = 0x00; // set A to impose gravity on jumping coin
    writeData(0x01, a); // as upward movement amount (apparently residual)
    a >>= 1; // divide by 2 and set
    writeData(0x02, a);
    a = 0x06; // set maximum vertical speed
    writeData(0x00, a);
    a = 0x50; // set downward movement amount
    x = a;
    a += 0x0d;
    c = 0; // add 13 bytes to offset for next subroutine
    a = x;

RunJCSubs: // get relative coordinates
    pushReturnIndex(225);
    goto JCoinGfxHandler;
Return_225: // draw the coin or floatey number
    pushReturnIndex(226);
    goto GetMiscBoundBox;
Return_226: // get bounding box coordinates (why?)
    pushReturnIndex(227);
    goto GetMiscOffscreenBits;
Return_227: // get offscreen information
    pushReturnIndex(228);
    goto RelativeMiscPosition;
Return_228:

MiscLoopBack:
    goto Return; // then leave

//------------------------------------------------------------------------
    if (!n)
        goto MiscLoop; // loop back until all misc objects handled
    --x; // decrement misc object offset

GiveOneCoin:
    writeData(Square2SoundQueue, a); // play 1-up sound
    a = Sfx_ExtraLife;
    ++M(NumberofLives); // give the player an extra life
    writeData(CoinTally, a); // otherwise, reinitialize coin amount
    a = 0x00;
    if (!z)
        goto CoinPoints; // if not, skip all of this
    compare(a, 100); // does player have 100 coins yet?
    a = M(CoinTally);
    ++M(CoinTally); // increment onscreen player's coin amount
    pushReturnIndex(229);
    goto DigitsMathRoutine;
Return_229: // update the coin tally
    y = M(CoinTallyOffsets + x); // get offset for player's coin tally
    x = M(CurrentPlayer); // get current player on the screen
    writeData(DigitModifier + 5, a); // to the current player's coin tally
    a = 0x01; // set digit modifier to add 1 coin

CoinPoints:
    writeData(DigitModifier + 4, a); // 200 points to the player
    a = 0x02; // set digit modifier to award

AddToScore:
    pushReturnIndex(230);
    goto DigitsMathRoutine;
Return_230: // update the score internally with value in digit modifier
    y = M(ScoreOffsets + x); // get offset for player's score
    x = M(CurrentPlayer); // get current player

GetSBNybbles:
    a = M(StatusBarNybbles + y); // get nybbles based on player, use to update score and coins
    y = M(CurrentPlayer); // get current player

UpdateNumber:
    writeData(VRAM_Buffer1 - 6 + y, a);
    a = 0x24;
    if (!z)
        goto NoZSup; // if zero, overwrite with space tile for zero suppression
    a = M(VRAM_Buffer1 - 6 + y); // check highest digit of score
    y = M(VRAM_Buffer1_Offset);
    pushReturnIndex(231);
    goto PrintStatusBarNumbers;
Return_231: // print status bar numbers based on nybbles, whatever they be

NoZSup: // get enemy object buffer offset
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

SetupPowerUp:
    writeData(Enemy_Y_Position + 5, a); // and use as vertical coordinate of power-up object
    a -= 0x08; // subtract 8 pixels
    c = 1;
    a = M(Block_Y_Position + x); // get vertical coordinate of block object
    writeData(Enemy_Y_HighPos + 5, a); // set vertical high byte of power-up object
    a = 0x01;
    writeData(Enemy_X_Position + 5, a); // as horizontal coordinate of power-up object
    a = M(Block_X_Position + x); // store horizontal coordinate of block object
    writeData(Enemy_PageLoc + 5, a); // as page location of power-up object
    a = M(Block_PageLoc + x); // store page location of block object
    writeData(Enemy_ID + 5, a); // special use slot of enemy object buffer
    a = PowerUpObject; // load power-up identifier into

PwrUpJmp: // this is a residual jump point in enemy object jump table
    a >>= 1; // otherwise shift right to force fire flower type
    if (!c)
        goto StrType; // if player not fiery, use status as power-up type
    compare(a, 0x02);
    a = M(PlayerStatus); // otherwise check player's current status
    if (c)
        goto PutBehind; // if star or 1-up, branch ahead
    compare(a, 0x02); // check currently loaded power-up type
    a = M(PowerUpType);
    writeData(Enemy_BoundBoxCtrl + 5, a); // set bounding box size control for power-up object
    a = 0x03;
    writeData(Enemy_Flag + 5, a); // set buffer flag
    writeData(Enemy_State + 5, a); // set power-up object's state
    a = 0x01;

StrType: // store type here
    writeData(PowerUpType, a);

PutBehind:
    goto Return;

//------------------------------------------------------------------------
    writeData(Square2SoundQueue, a); // load power-up reveal sound and leave
    a = Sfx_GrowPowerUp;
    writeData(Enemy_SprAttrib + 5, a); // set background priority bit
    a = BOOST_BINARY(00100000);

PowerUpObjHandler:
    goto RunPUSubs; // then jump to other power-up subroutines
    pushReturnIndex(232);
    goto EnemyJump;
Return_232: // note that green paratroopa shares the same code here 
    pushReturnIndex(233);
    goto MoveJumpingEnemy;
Return_233: // otherwise impose gravity on star power-up and make it jump
    if (!z)
        goto RunPUSubs; // if not star, branch elsewhere to skip movement
    compare(a, 0x02);
    if (z)
        goto ShroomM; // if 1-up mushroom, branch ahead to move it
    compare(a, 0x03);
    if (z)
        goto ShroomM; // if normal mushroom, branch ahead to move it
    a = M(PowerUpType); // check power-up type
    if (!z)
        goto RunPUSubs; // branch ahead to enemy object routines
    a = M(TimerControl); // if master timer control set,
    if (!c)
        goto GrowThePowerUp; // if not set, branch ahead to skip this part
    a <<= 1; // shift to check if d7 was set in object state
    if (z)
        goto ExitPUp; // if not set, branch to leave
    a = M(Enemy_State + 5); // check power-up object's state
    writeData(ObjectOffset, x);
    x = 0x05; // set object offset for last slot in enemy object buffer

ShroomM: // do sub to make mushrooms move
    goto RunPUSubs; // run the other subroutines
    pushReturnIndex(234);
    goto EnemyToBGCollisionDet;
Return_234: // deal with collisions
    pushReturnIndex(235);
    goto MoveNormalEnemy;
Return_235:

GrowThePowerUp:
    writeData(Enemy_MovingDir + x, a); // set moving direction
    a.rol(); // rotate A to set right moving direction
    writeData(Enemy_SprAttrib + 5, a); // initialize background priority bit set here
    a <<= 1; // shift once to init A
    writeData(Enemy_State + 5, a); // and then set d7 in power-up object's state
    a = BOOST_BINARY(10000000);
    writeData(Enemy_X_Speed + x, a); // otherwise set horizontal speed
    a = 0x10;
    if (!c)
        goto ChkPUSte; // branch ahead to last part here
    compare(a, 0x11); // if power-up object state not yet past 16th pixel,
    ++M(Enemy_State + 5); // increment state for next frame (to make power-up rise)
    a = M(Enemy_State + 5); // load power-up object state
    --M(Enemy_Y_Position + 5); // otherwise decrement vertical coordinate slowly
    if (!z)
        goto ChkPUSte; // if any bits set here, branch
    a &= 0x03; // mask out all but 2 LSB
    a = M(FrameCounter); // get frame counter

ChkPUSte: // check power-up object's state
    if (!c)
        goto ExitPUp; // if not, don't even bother running these routines
    compare(a, 0x06); // for if power-up has risen enough
    a = M(Enemy_State + 5);

RunPUSubs: // get coordinates relative to screen
    pushReturnIndex(236);
    goto OffscreenBoundsCheck;
Return_236: // check to see if it went offscreen
    pushReturnIndex(237);
    goto PlayerEnemyCollision;
Return_237: // check for collision with player
    pushReturnIndex(238);
    goto DrawPowerUp;
Return_238: // draw the power-up object
    pushReturnIndex(239);
    goto GetEnemyBoundBox;
Return_239: // get bounding box coordinates
    pushReturnIndex(240);
    goto GetEnemyOffscreenBits;
Return_240: // get offscreen bits
    pushReturnIndex(241);
    goto RelativeEnemyPosition;
Return_241:

ExitPUp: // and we're done
    goto Return;

//------------------------------------------------------------------------

PlayerHeadCollision:
    a = 0x12; // otherwise load breakable block object state
    if (!z)
        goto DBlockSte; // if small, branch
    y = M(PlayerSize); // check player's size
    x = M(SprDataOffset_Ctrl); // load offset control bit here
    a = 0x11; // load unbreakable block object state by default
    pha(); // store metatile number to stack

DBlockSte: // store into block object buffer
    a = y; // otherwise init A (note: big = 0)
    if (!z)
        goto ChkBrick; // if small, use metatile itself as contents of A
    y = M(PlayerSize); // check player's size
    writeData(0x00, a); // store metatile here
    pushReturnIndex(242);
    goto BlockBumpedChk;
Return_242: // do a sub to check which block player bumped head on
    a = M(W(0x06) + y); // get contents of block buffer at old address at $06, $07
    writeData(Block_BBuf_Low + x, a); // save as offset here to be used later
    a = M(0x06); // get low byte of block buffer address used in same routine
    y = a;
    writeData(Block_Orig_YPos + x, a); // set as vertical coordinate for block object
    a = M(0x02); // get vertical high nybble offset used in block buffer routine
    x = M(SprDataOffset_Ctrl); // load offset control bit
    pushReturnIndex(243);
    goto DestroyBlockMetatile;
Return_243: // store blank metatile in vram buffer to write to name table
    writeData(Block_State + x, a);

ChkBrick: // if no match was found in previous sub, skip ahead
    if (!z)
        goto PutMTileB; // if not, branch ahead to store empty block metatile
    compare(y, 0x5d); // is it brick with coins (without line)?
    if (z)
        goto StartBTmr; // if so, branch
    compare(y, 0x58); // is it brick with coins (with line)?
    y = M(0x00); // get metatile from before
    a = 0xc4; // load empty block metatile into A for now
    writeData(Block_State + x, y); // note this applies to both player sizes
    y = 0x11; // otherwise load unbreakable state into block object buffer
    if (!c)
        goto PutMTileB;

StartBTmr: // check brick coin timer flag
    ++M(BrickCoinTimerFlag); // and set flag linked to it
    writeData(BrickCoinTimer, a); // if not set, set brick coin timer
    a = 0x0b;
    if (!z)
        goto ContBTmr; // if set, timer expired or counting down, thus branch
    a = M(BrickCoinTimerFlag);

ContBTmr: // check brick coin timer
    y = 0xc4; // otherwise use empty block metatile
    if (!z)
        goto PutOldMT; // if not yet expired, branch to use current metatile
    a = M(BrickCoinTimer);

PutOldMT: // put metatile into A
    a = y;

PutMTileB: // store whatever metatile be appropriate here
    if (z)
        goto BigBP; // if so, branch to use default offset
    a = M(PlayerSize); // is player big?
    if (!z)
        goto SmallBP; // if so, branch to increment offset
    a = M(CrouchingFlag); // is player crouching?
    y = 0x00; // set default offset
    writeData(0x05, a); // and save here
    pla(); // pull original metatile from stack
    writeData(BlockBounceTimer, a); // set block bounce timer
    a = 0x10;
    writeData(W(0x06) + y, a); // write blank metatile $23 to block buffer
    a = 0x23;
    y = M(0x02); // get vertical high nybble offset
    pushReturnIndex(244);
    goto InitBlock_XY_Pos;
Return_244: // get block object horizontal coordinates saved
    writeData(Block_Metatile + x, a);

SmallBP: // increment for small or big and crouching
    ++y;

BigBP: // get player's vertical coordinate
    goto InvOBit; // skip subroutine to do last part of code here
    pushReturnIndex(245);
    goto BrickShatter;
Return_245: // execute code for breakable brick
    if (z)
        goto Unbreak; // if set to value loaded for unbreakable, branch
    compare(y, 0x11);
    y = M(Block_State + x); // get block object state
    writeData(Block_Y_Position + x, a); // save as vertical coordinate for block object
    a &= 0xf0; // mask out low nybble to get 16-pixel correspondence
    a += M(BlockYPosAdderData + y); // add value determined by size
    c = 0;
    a = M(Player_Y_Position);

Unbreak: // execute code for unbreakable brick or question block
    pushReturnIndex(246);
    goto BumpBlock;
Return_246:

InvOBit: // invert control bit used by block objects
    goto Return; // leave!

//------------------------------------------------------------------------
    writeData(SprDataOffset_Ctrl, a);
    a ^= 0x01; // and floatey numbers
    a = M(SprDataOffset_Ctrl);

InitBlock_XY_Pos:
    goto Return; // vertical high byte of block object and leave

//------------------------------------------------------------------------
    writeData(Block_Y_HighPos + x, a); // save vertical high byte of player into
    a = M(Player_Y_HighPos);
    writeData(Block_PageLoc2 + x, a); // save elsewhere to be used later
    writeData(Block_PageLoc + x, a); // save as page location of block object
    a += 0x00; // add carry to page location of player
    a = M(Player_PageLoc);
    writeData(Block_X_Position + x, a); // save as horizontal coordinate for block object
    a &= 0xf0; // mask out low nybble to give 16-pixel correspondence
    a += 0x08; // add eight pixels
    c = 0;
    a = M(Player_X_Position); // get player's horizontal coordinate

BumpBlock:
    a -= 0x05; // otherwise subtract 5 for second set to get proper number
    if (!c)
        goto BlockCode; // branch to use current number
    compare(a, 0x09); // if block number was within 0-8 range,
    a = y; // move block number to A
    if (!c)
        goto ExitBlockChk; // if no match was found, branch to leave
    pushReturnIndex(247);
    goto BlockBumpedChk;
Return_247: // do a sub to check which block player bumped head on
    a = M(0x05); // get original metatile from stack
    writeData(Block_Y_Speed + x, a); // set vertical speed for block object
    a = 0xfe;
    writeData(Player_Y_Speed, a); // init player's vertical speed
    writeData(Block_Y_MoveForce + x, a); // init fractional movement force
    writeData(Block_X_Speed + x, a); // initialize horizontal speed for block object
    a = 0x00;
    writeData(Square1SoundQueue, a); // play bump sound
    a = Sfx_Bump;
    pushReturnIndex(248);
    goto CheckTopOfBlock;
Return_248: // check to see if there's a coin directly above this block

MushFlowerBlock:
    goto Skip_4;
    a = 0x00; // load mushroom/fire flower into power-up type
Skip_4:

StarBlock:
    goto Skip_5;
    a = 0x02; // load star into power-up type
Skip_5:

ExtraLifeMushBlock:
    goto SetupPowerUp;
    writeData(0x39, a); // store correct power-up type
    a = 0x03; // load 1-up mushroom into power-up type

VineBlock:
    pushReturnIndex(249);
    goto Setup_Vine;
Return_249: // set up vine object
    y = M(SprDataOffset_Ctrl); // get control bit
    x = 0x05; // load last slot for enemy object buffer

ExitBlockChk:
    goto Return; // leave

//------------------------------------------------------------------------

BlockBumpedChk:
    y = 0x0d; // start at end of metatile data

BumpChkLoop: // check to see if current metatile matches
    c = 0; // if none match, return with carry clear
    if (!n)
        goto BumpChkLoop; // do this until all metatiles are checked
    --y; // otherwise move onto next metatile
    if (z)
        goto MatchBump; // metatile found in block buffer, branch if so
    compare(a, M(BrickQBlockMetatiles + y));

MatchBump: // note carry is set if found match
    goto Return;

//------------------------------------------------------------------------

BrickShatter:
    goto Return;

//------------------------------------------------------------------------
    x = M(SprDataOffset_Ctrl); // load control bit and leave
    pushReturnIndex(250);
    goto AddToScore;
Return_250: // do sub to update the score
    writeData(DigitModifier + 5, a); // set digit modifier to give player 50 points
    a = 0x05;
    writeData(Player_Y_Speed, a); // set vertical speed for player
    a = 0xfe;
    pushReturnIndex(251);
    goto SpawnBrickChunks;
Return_251: // create brick chunk objects
    writeData(NoiseSoundQueue, a); // load brick shatter sound
    writeData(Block_RepFlag + x, a); // set flag for block object to immediately replace metatile
    a = Sfx_BrickShatter;
    pushReturnIndex(252);
    goto CheckTopOfBlock;
Return_252: // check to see if there's a coin directly above this block

CheckTopOfBlock:
    pushReturnIndex(253);
    goto SetupJumpCoin;
Return_253: // create jumping coin object and update coin variables
    x = M(SprDataOffset_Ctrl); // get control bit
    pushReturnIndex(254);
    goto RemoveCoin_Axe;
Return_254: // write blank metatile to vram buffer
    writeData(W(0x06) + y, a); // otherwise put blank metatile where coin was
    a = 0x00;
    if (!z)
        goto TopEx; // if not, branch to leave
    compare(a, 0xc2); // is it a coin? (not underwater)
    a = M(W(0x06) + y); // get contents of block buffer in same column, one row up
    y = a;
    writeData(0x02, a); // store as new vertical high nybble offset
    a -= 0x10; // subtract $10 to move up one row in the block buffer
    c = 1;
    a = y; // otherwise set to A
    if (z)
        goto TopEx; // branch to leave if set to zero, because we're at the top
    y = M(0x02); // get vertical high nybble offset used in block buffer
    x = M(SprDataOffset_Ctrl); // load control bit

TopEx: // leave!
    goto Return;

//------------------------------------------------------------------------

SpawnBrickChunks:
    goto Return;

//------------------------------------------------------------------------
    writeData(Block_Y_Speed + x, a); // set vertical speed...again??? (redundant)
    a = 0xfa;
    writeData(Block_Y_Position + 2 + x, a);
    a += 0x08; // and save as vertical coordinate for one of them
    c = 0; // add 8 pixels to vertical coordinate
    a = M(Block_Y_Position + x);
    writeData(Block_X_Position + 2 + x, a); // copy horizontal coordinate
    a = M(Block_X_Position + x);
    writeData(Block_PageLoc + 2 + x, a); // copy page location
    a = M(Block_PageLoc + x);
    writeData(Block_Y_MoveForce + 2 + x, a);
    writeData(Block_Y_MoveForce + x, a); // init fractional movement force for both
    a = 0x00;
    writeData(Block_Y_Speed + 2 + x, a); // set lower vertical speed for the other
    a = 0xfc;
    writeData(Block_Y_Speed + x, a); // set vertical speed for one
    a = 0xfa;
    writeData(Block_X_Speed + 2 + x, a);
    writeData(Block_X_Speed + x, a); // set horizontal speed for brick chunk objects
    a = 0xf0;
    writeData(Block_Orig_XPos + x, a); // as original horizontal coordinate here
    a = M(Block_X_Position + x); // set horizontal coordinate of block object

BlockObjectsCore:
    writeData(Block_Y_Position + 2 + x, a); // otherwise set offscreen coordinate
    if (c)
        goto ChkTop; // to the bottom of the screen, and branch if not
    compare(a, M(Block_Y_Position + 2 + x)); // check to see if bottom block object went
    a = 0xf0;
    pha(); // otherwise save state back into stack
    if (z)
        goto UpdSte; // if above the screen, branch to kill it
    y = M(Block_Y_HighPos + x); // check vertical high byte of block object
    pla(); // get lower nybble of saved state
    pushReturnIndex(255);
    goto DrawBrickChunks;
Return_255: // draw the brick chunks
    pushReturnIndex(256);
    goto GetBlockOffscreenBits;
Return_256: // get offscreen information
    pushReturnIndex(257);
    goto RelativeBlockPosition;
Return_257: // get relative coordinates
    x = M(ObjectOffset); // get block object offset used for both
    pushReturnIndex(258);
    goto MoveObjectHorizontally;
Return_258: // do another sub to move horizontally
    pushReturnIndex(259);
    goto ImposeGravityBlock;
Return_259: // do sub to impose gravity on other block object
    x = a;
    a += 0x02;
    c = 0; // move onto next block object
    a = x;
    pushReturnIndex(260);
    goto MoveObjectHorizontally;
Return_260: // do another sub to move horizontally
    pushReturnIndex(261);
    goto ImposeGravityBlock;
Return_261: // do sub to impose gravity on one block object object
    if (z)
        goto BouncingBlockHandler; // branch if found, otherwise continue for brick chunks
    --y; // decrement Y to check for solid block state
    x = a; // when using brick chunks, but only one offset for both)
    a += 0x09; // add 9 bytes to offset (note two block objects are created
    c = 0;
    a = x;
    y = a; // put in Y for now
    pha(); // push to stack
    a &= 0x0f; // mask out high nybble
    if (z)
        goto UpdSte; // if not set, branch to leave
    a = M(Block_State + x); // get state of block object

ChkTop: // get top block object's vertical coordinate
    if (c)
        goto KillBlock; // otherwise do unconditional branch to kill it
    if (!c)
        goto UpdSte; // if not, branch to save state
    pla(); // pull block object state from stack
    compare(a, 0xf0); // see if it went to the bottom of the screen
    a = M(Block_Y_Position + x);

BouncingBlockHandler:
    writeData(Block_RepFlag + x, a); // otherwise set flag to replace metatile
    a = 0x01;
    if (c)
        goto UpdSte; // if still above amount, not time to kill block yet, thus branch
    pla(); // pull state from stack
    compare(a, 0x05); // check to see if low nybble wrapped around
    a &= 0x0f; // mask out high nybble
    a = M(Block_Y_Position + x); // get vertical coordinate
    pushReturnIndex(262);
    goto DrawBlock;
Return_262: // draw the block
    pushReturnIndex(263);
    goto GetBlockOffscreenBits;
Return_263: // get offscreen information
    pushReturnIndex(264);
    goto RelativeBlockPosition;
Return_264: // get relative coordinates
    x = M(ObjectOffset); // get block object offset
    pushReturnIndex(265);
    goto ImposeGravityBlock;
Return_265: // do sub to impose gravity on block object

KillBlock: // if branched here, nullify object state
    a = 0x00;

UpdSte: // store contents of A in block object state
    goto Return;

//------------------------------------------------------------------------
    writeData(Block_State + x, a);

BlockObjMT_Updater:
    x = 0x01; // set offset to start with second block object

UpdateLoop: // set offset here
    writeData(Block_RepFlag + x, a); // clear block object flag
    a = 0x00;
    pushReturnIndex(266);
    goto ReplaceBlockMetatile;
Return_266: // do sub to replace metatile where block object is
    writeData(W(0x06) + y, a); // write it to the block buffer
    a = M(Block_Metatile + x); // get metatile to be written
    y = a;
    writeData(0x02, a); // store here and use as offset to block buffer
    a = M(Block_Orig_YPos + x); // get original vertical coordinate of block object
    writeData(0x07, a); // set high byte of block buffer address
    a = 0x05;
    writeData(0x06, a); // store into block buffer address
    a = M(Block_BBuf_Low + x); // get low byte of block buffer
    if (z)
        goto NextBUpd; // branch to move onto next block object
    a = M(Block_RepFlag + x); // if flag for block object already clear,
    if (!z)
        goto NextBUpd; // branch to move onto next block object
    a = M(VRAM_Buffer1); // if vram buffer already being used here,
    writeData(ObjectOffset, x);

NextBUpd: // decrement block object offset
    goto Return; // then leave

//------------------------------------------------------------------------
    if (!n)
        goto UpdateLoop; // do this until both block objects are dealt with
    --x;

MoveEnemyHorizontally:
    goto Return; // put enemy offset back in X and leave

//------------------------------------------------------------------------
    x = M(ObjectOffset); // counters, return with saved value in A,
    pushReturnIndex(267);
    goto MoveObjectHorizontally;
Return_267: // position object horizontally according to
    ++x; // increment offset for enemy offset

MovePlayerHorizontally:
    x = a; // otherwise set zero for offset to use player's stuff
    if (!z)
        goto ExXMove; // branch to leave
    a = M(JumpspringAnimCtrl); // if jumpspring currently animating,

MoveObjectHorizontally:
    a |= BOOST_BINARY(11110000); // otherwise alter high nybble
    if (!c)
        goto SaveXSpd;
    compare(a, 0x08); // if < 8, branch, do not change
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1; // move high nybble to low
    a = M(SprObject_X_Speed + x); // get saved value again
    writeData(0x01, a); // store result here
    a <<= 1;
    a <<= 1;
    a <<= 1; // and move low nybble to high
    a <<= 1; // speed, secondary counter, whatever)
    a = M(SprObject_X_Speed + x); // get currently saved value (horizontal

SaveXSpd: // save result here
    --y; // otherwise decrement Y
    if (!n)
        goto UseAdder;
    compare(a, 0x00); // if result positive, leave Y alone
    y = 0x00; // load default Y value here
    writeData(0x00, a);

UseAdder: // save Y here
    a += M(0x00); // to high nybble moved to low
    c = 0; // pull old carry from stack and add
    pla();
    writeData(SprObject_PageLoc + x, a); // object's page location and save
    a += M(0x02); // add carry plus other saved value to the
    a = M(SprObject_PageLoc + x);
    writeData(SprObject_X_Position + x, a); // plus $f0 if necessary) to object's horizontal position
    a += M(0x00); // add carry plus saved value (high nybble moved to low
    a = M(SprObject_X_Position + x);
    a.ror(); // rotate d0 back onto carry
    pha(); // push onto stack
    a.rol(); // rotate carry into d0
    a = 0x00; // init A
    writeData(SprObject_X_MoveForce + x, a); // store result here
    a += M(0x01); // add low nybble moved to high
    c = 0;
    a = M(SprObject_X_MoveForce + x); // get whatever number's here
    writeData(0x02, y);

ExXMove: // and leave
    goto Return;

//------------------------------------------------------------------------

MovePlayerVertically:
    if (!z)
        goto ExXMove; // branch to leave if so
    a = M(JumpspringAnimCtrl); // otherwise check to see if jumpspring is animating
    if (!z)
        goto NoJSChk; // if master timer control set, branch ahead
    a = M(TimerControl);
    x = 0x00; // set X for player offset

NoJSChk: // dump vertical force 
    goto ImposeGravitySprObj; // then jump to move player vertically
    a = 0x04; // set maximum vertical speed here
    writeData(0x00, a);
    a = M(VerticalForce);

MoveD_EnemyVertically:
    if (!z)
        goto ContVMove; // and use, otherwise set different movement amount, continue on
    compare(a, 0x05); // if not set to unique state for spiny's egg, go ahead
    a = M(Enemy_State + x); // then check enemy state
    y = 0x3d; // set quick movement amount downwards

MoveFallingPlatform:
    y = 0x20; // set movement amount

ContVMove: // jump to skip the rest of this
    goto SetHiMax;

MoveRedPTroopaDown:
    goto MoveRedPTroopa; // skip to movement routine
    y = 0x00; // set Y to move downwards

MoveRedPTroopaUp:
    y = 0x01; // set Y to move upwards

MoveRedPTroopa:
    goto RedPTroopaGrav; // jump to move this thing
    a = y; // set movement direction in A, and
    writeData(0x02, a); // set maximum speed here
    a = 0x02;
    writeData(0x01, a); // set upward movement amount here
    a = 0x06;
    writeData(0x00, a); // set downward movement amount here
    a = 0x03;
    ++x; // increment X for enemy offset

MoveDropPlatform:
    if (!z)
        goto SetMdMax; // skip ahead of other value set here
    y = 0x7f; // set movement amount for drop platform

MoveEnemySlowVert:
    y = 0x0f; // set movement amount for bowser/other objects

SetMdMax: // set maximum speed in A
    if (!z)
        goto SetXMoveAmt; // unconditional branch
    a = 0x02;

MoveJ_EnemyVertically:
    y = 0x1c; // set movement amount for podoboo/other objects

SetHiMax: // set maximum speed in A
    a = 0x03;

SetXMoveAmt: // set movement amount here
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset); // get enemy object buffer offset and leave
    pushReturnIndex(268);
    goto ImposeGravitySprObj;
Return_268: // do a sub to move enemy object downwards
    ++x; // increment X for enemy offset
    writeData(0x00, y);

ResidualGravityCode:
    goto Skip_6;
    y = 0x00; // this part appears to be residual,
Skip_6:

ImposeGravityBlock:
    a = M(MaxSpdBlockData + y); // get maximum speed
    writeData(0x00, a);
    a = 0x50; // set movement amount here
    y = 0x01; // set offset for maximum speed

ImposeGravitySprObj:
    goto ImposeGravity; // jump to the code that actually moves it
    a = 0x00; // set value to move downwards
    writeData(0x02, a); // set maximum speed here

MovePlatformDown:
    goto Skip_7;
    a = 0x00; // save value to stack (if branching here, execute next
Skip_7:

MovePlatformUp:
    a = 0x09; // residual code
    if (!z)
        goto SetDplSpd; // this code, thus unconditional branch here
    compare(y, 0x29); // residual comparison, object #29 never executes
    a = 0x05; // load default value here
    ++x; // increment offset for enemy object
    y = M(Enemy_ID + x); // get enemy object identifier
    pha();
    a = 0x01; // save value to stack

SetDplSpd: // save downward movement amount here
    y = a; // use as Y, then move onto code shared by red koopa
    pla(); // get value from stack
    writeData(0x02, a);
    a = 0x03; // save maximum vertical speed here
    writeData(0x01, a);
    a = 0x0a; // save upward movement amount here
    writeData(0x00, a);

RedPTroopaGrav:
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset); // get enemy object offset and leave
    pushReturnIndex(269);
    goto ImposeGravity;
Return_269: // do a sub to move object gradually

ImposeGravity:
    --y; // otherwise decrement Y
    if (!n)
        goto AlterYP; // if currently moving downwards, do not decrement Y
    a = M(SprObject_Y_Speed + x); // get current vertical speed
    y = 0x00; // set Y to zero by default
    writeData(SprObject_YMF_Dummy + x, a);
    a += M(SprObject_Y_MoveForce + x);
    c = 0; // add value in movement force to contents of dummy variable
    a = M(SprObject_YMF_Dummy + x);
    pha(); // push value to stack

AlterYP: // store Y here
    writeData(SprObject_Y_MoveForce + x, a); // clear fractional
    a = 0x00;
    writeData(SprObject_Y_Speed + x, a); // keep vertical speed within maximum value
    a = M(0x02);
    if (!c)
        goto ChkUpM;
    compare(a, 0x80); // if less positively than preset maximum, skip this part
    a = M(SprObject_Y_MoveForce + x);
    if (n)
        goto ChkUpM; // if less than preset value, skip this part
    compare(a, M(0x02)); // compare to maximum speed
    writeData(SprObject_Y_Speed + x, a);
    a += 0x00;
    a = M(SprObject_Y_Speed + x); // add carry to vertical speed and store
    writeData(SprObject_Y_MoveForce + x, a);
    a += M(0x00); // add downward movement amount to contents of $0433
    c = 0;
    a = M(SprObject_Y_MoveForce + x);
    writeData(SprObject_Y_HighPos + x, a); // store as new vertical high byte
    a += M(0x07); // add carry plus contents of $07 to vertical high byte
    a = M(SprObject_Y_HighPos + x);
    writeData(SprObject_Y_Position + x, a); // store as new vertical position
    a += M(SprObject_Y_Position + x); // add vertical position to vertical speed plus carry
    writeData(0x07, y);

ChkUpM: // get value from stack
    writeData(SprObject_Y_MoveForce + x, a); // clear fractional
    a = 0xff;
    writeData(SprObject_Y_Speed + x, a); // keep vertical speed within maximum value
    a = M(0x07);
    if (c)
        goto ExVMove; // and if so, branch to leave
    compare(a, 0x80); // check if fractional part is above certain amount,
    a = M(SprObject_Y_MoveForce + x);
    if (!n)
        goto ExVMove; // if less negatively than preset maximum, skip this part
    compare(a, M(0x07)); // compare vertical speed to two's compliment
    writeData(SprObject_Y_Speed + x, a);
    a -= 0x00; // subtract borrow from vertical speed and store
    a = M(SprObject_Y_Speed + x);
    writeData(SprObject_Y_MoveForce + x, a); // thus it effectively undoes add we did earlier
    a -= M(0x01); // of movement force, note that $01 is twice as large as $00,
    c = 1; // subtract upward movement amount from contents
    a = M(SprObject_Y_MoveForce + x);
    writeData(0x07, y); // store two's compliment here
    ++y;
    y = a;
    a ^= BOOST_BINARY(11111111); // otherwise get two's compliment of maximum speed
    a = M(0x02);
    if (z)
        goto ExVMove; // if set to zero, branch to leave
    pla();

ExVMove: // leave!
    goto Return;

//------------------------------------------------------------------------

EnemiesAndLoopsCore:
    goto RunEnemyObjectsCore; // otherwise, jump to run enemy subroutines
    if (z)
        goto ChkAreaTsk; // if data zero, branch
    pla(); // get from stack
    if (c)
        goto ChkBowserF; // if MSB set in enemy flag, branch ahead of jumps
    a <<= 1;
    pha(); // save in stack
    a = M(Enemy_Flag + x); // check data here for MSB set

ChkAreaTsk: // check number of tasks to perform
    goto ProcLoopCommand; // otherwise, jump to process loop command/load enemies
    if (z)
        goto ExitELCore;
    compare(a, 0x07); // if at a specific task, jump and leave
    a &= 0x07;
    a = M(AreaParserTaskNum);

ChkBowserF: // get data from stack
    writeData(Enemy_Flag + x, a); // if second enemy flag not set, also clear first one
    if (!z)
        goto ExitELCore;
    a = M(Enemy_Flag + y); // use as pointer and load same place with different offset
    y = a;
    a &= BOOST_BINARY(00001111); // mask out high nybble
    pla();

ExitELCore:
    goto Return;

//------------------------------------------------------------------------

ExecGameLoopback:
    goto Return;

//------------------------------------------------------------------------
    writeData(AreaDataOffset, a); // which loop command we encountered
    a = M(AreaDataOfsLoopback + y); // adjust area object offset based on
    writeData(EnemyObjectPageLoc, a); // and enemy object page control
    writeData(EnemyDataOffset, a); // initialize enemy object data offset
    writeData(AreaObjectPageSel, a);
    writeData(EnemyObjectPageSel, a); // area and enemy objects
    a = 0x00; // initialize page select for both
    writeData(AreaObjectPageLoc, a);
    a -= 0x04;
    c = 1; // for area objects
    a = M(AreaObjectPageLoc); // subtract four from page control
    writeData(ScreenRight_PageLoc, a);
    a -= 0x04;
    c = 1; // of screen's right border
    a = M(ScreenRight_PageLoc); // do the same for the page location
    writeData(ScreenLeft_PageLoc, a);
    a -= 0x04;
    c = 1; // of screen's left border
    a = M(ScreenLeft_PageLoc); // subtract four from page location
    writeData(CurrentPageLoc, a);
    a -= 0x04;
    c = 1;
    a = M(CurrentPageLoc); // send current page back four pages
    writeData(Player_PageLoc, a);
    a -= 0x04;
    c = 1;
    a = M(Player_PageLoc); // send player back four pages

ProcLoopCommand:
    y = 0x0b; // start at the end of each set of loop data
    if (!z)
        goto ChkEnemyFrenzy; // if not, do not loop yet
    a = M(CurrentColumnPos); // check to see if we're still on the first page
    if (z)
        goto ChkEnemyFrenzy;
    a = M(LoopCommand); // check if loop command was found

FindLoop:
    ++M(MultiLoopCorrectCntr); // increment counter for correct progression
    if (!z)
        goto InitMLp; // if not, initialize flags used there, otherwise
    compare(a, World7); // vertical position and on solid ground)
    a = M(WorldNumber); // are we in world 7? (check performed on correct
    if (!z)
        goto WrongChk; // if not, player fails to pass loop, and loopback
    compare(a, 0x00); // on solid ground (i.e. not jumping or falling)
    a = M(Player_State); // check to see if the player is
    if (!z)
        goto WrongChk;
    compare(a, M(LoopCmdYPosition + y)); // if not, branch to check for world 7
    a = M(Player_Y_Position); // check to see if the player is at the correct position
    if (!z)
        goto FindLoop;
    compare(a, M(LoopCmdPageNumber + y)); // matches the page we're currently on
    a = M(CurrentPageLoc); // check to see if one of the page numbers
    if (!z)
        goto FindLoop;
    compare(a, M(LoopCmdWorldNumber + y)); // matches our current world number
    a = M(WorldNumber); // check to see if one of the world numbers
    if (n)
        goto ChkEnemyFrenzy; // if all data is checked and not match, do not loop
    --y;

IncMLoop: // increment master multi-part counter
    if (!z)
        goto DoLpBack; // unconditional branch if previous branch fails
    if (z)
        goto InitMLp; // if so, branch past unnecessary check here
    compare(a, 0x03);
    a = M(MultiLoopCorrectCntr); // if so, have we done them all correctly?
    if (!z)
        goto InitLCmd; // if not, skip this part
    compare(a, 0x03);
    a = M(MultiLoopPassCntr); // have we done all three parts?
    ++M(MultiLoopPassCntr);

WrongChk: // are we in world 7? (check performed on
    if (z)
        goto IncMLoop;
    compare(a, World7); // incorrect vertical position or not on solid ground)
    a = M(WorldNumber);

DoLpBack: // if player is not in right place, loop back
    pushReturnIndex(270);
    goto KillAllEnemies;
Return_270:
    pushReturnIndex(271);
    goto ExecGameLoopback;
Return_271:

InitMLp: // initialize counters used for multi-part loop commands
    writeData(MultiLoopCorrectCntr, a);
    writeData(MultiLoopPassCntr, a);
    a = 0x00;

InitLCmd: // initialize loop command flag
    writeData(LoopCommand, a);
    a = 0x00;

ChkEnemyFrenzy:
    goto InitEnemyObject; // and then jump to deal with this enemy
    writeData(EnemyFrenzyQueue, a);
    writeData(Enemy_State + x, a); // initialize state and frenzy queue
    a = 0x00;
    writeData(Enemy_Flag + x, a); // activate enemy object flag
    a = 0x01;
    writeData(Enemy_ID + x, a); // store as enemy object identifier here
    if (z)
        goto ProcessEnemyData; // if not, skip this part
    a = M(EnemyFrenzyQueue); // check for enemy object in frenzy queue

ProcessEnemyData:
    goto CheckFrenzyBuffer; // if found, jump to check frenzy buffer, otherwise
    if (!z)
        goto CheckEndofBuffer;
    compare(a, 0xff); // check for EOD terminator
    a = M(W(EnemyData) + y); // load first byte
    y = M(EnemyDataOffset); // get offset of enemy object data

CheckEndofBuffer:
    goto Return; // the sixth slot

//------------------------------------------------------------------------
    if (z)
        goto CheckRightBounds; // but it has the effect of keeping enemies out of
    compare(a, 0x2e); // this part is quite possibly residual code
    a &= BOOST_BINARY(00111111); // not sure what this was intended for, exactly
    a = M(W(EnemyData) + y); // check for specific value here
    ++y;
    if (!c)
        goto CheckRightBounds; // if not at end of buffer, branch
    compare(x, 0x05); // check for end of buffer
    if (z)
        goto CheckRightBounds; // if found, branch, otherwise
    compare(a, 0x0e);
    a &= BOOST_BINARY(00001111); // check for special row $0e

CheckRightBounds:
    ++M(EnemyObjectPageLoc); // and increment page control
    ++M(EnemyObjectPageSel); // otherwise, if MSB is set, set page select 
    if (!z)
        goto CheckPageCtrlRow;
    a = M(EnemyObjectPageSel); // if page select already set, do not set again
    if (!c)
        goto CheckPageCtrlRow;
    a <<= 1;
    a = M(W(EnemyData) + y); // if MSB of enemy object is clear, branch to check for row $0f
    ++y;
    y = M(EnemyDataOffset);
    writeData(0x06, a); // store page location + carry
    a += 0x00;
    a = M(ScreenRight_PageLoc); // add carry to page location of right boundary
    writeData(0x07, a);
    a &= BOOST_BINARY(11110000); // store high nybble
    a += 0x30;
    c = 0;
    a = M(ScreenRight_X_Pos); // add 48 to pixel coordinate of right boundary

CheckPageCtrlRow:
    goto ProcLoopCommand; // jump back to process loop commands again
    ++M(EnemyObjectPageSel); // set page select for enemy object data and 
    ++M(EnemyDataOffset);
    ++M(EnemyDataOffset); // increment enemy object data offset 2 bytes
    writeData(EnemyObjectPageLoc, a); // store as page control for enemy object data
    a &= BOOST_BINARY(00111111);
    a = M(W(EnemyData) + y); // otherwise, get second byte, mask out 2 MSB
    ++y;
    if (!z)
        goto PositionEnemyObj; // branch without reading second byte
    a = M(EnemyObjectPageSel); // if page select set,
    if (!z)
        goto PositionEnemyObj; // if not found, branch to position enemy object
    compare(a, 0x0f); // check for special row $0f
    a &= 0x0f;
    a = M(W(EnemyData) + y); // reread first byte
    --y;

PositionEnemyObj:
    goto CheckThreeBytes; // if not found, unconditional jump
    if (z)
        goto ParseRow0e;
    compare(a, 0x0e); // if found, jump elsewhere
    a &= BOOST_BINARY(00001111); // check for special row $0e
    a = M(W(EnemyData) + y);
    if (c)
        goto CheckRightExtBounds; // if enemy object beyond or at boundary, branch
    a -= M(ScreenRight_PageLoc); // from page location
    a = M(Enemy_PageLoc + x); // without subtracting, then subtract borrow
    compare(a, M(ScreenRight_X_Pos)); // check column position against right boundary
    writeData(Enemy_X_Position + x, a); // store column position
    a &= BOOST_BINARY(11110000);
    a = M(W(EnemyData) + y); // get first byte of enemy object
    writeData(Enemy_PageLoc + x, a); // for enemy object
    a = M(EnemyObjectPageLoc); // store page control as page location

CheckRightExtBounds:
    if (z)
        goto Inc2B; // is on, and if not, branch to skip this object completely
    a = M(SecondaryHardMode); // if set, check to see if secondary hard mode flag
    if (z)
        goto CheckForEnemyGroup; // if not, branch to check for group enemy objects
    a &= BOOST_BINARY(01000000); // check to see if hard mode bit is set
    a = M(W(EnemyData) + y); // get second byte of object
    ++y;
    if (z)
        goto ParseRow0e; // (necessary if branched to $c1cb)
    compare(a, 0xe0); // do one last check for special row $0e
    writeData(Enemy_Y_Position + x, a);
    a <<= 1;
    a <<= 1;
    a <<= 1; // coordinate
    a <<= 1; // multiply by four to get the vertical
    a = M(W(EnemyData) + y); // get first byte again
    writeData(Enemy_Y_HighPos + x, a);
    a = 0x01; // store value in vertical high byte
    if (!c)
        goto CheckFrenzyBuffer; // if enemy object beyond extended boundary, branch
    a -= M(Enemy_PageLoc + x); // plus carry
    a = M(0x06); // then subtract borrow from page control temp
    compare(a, M(Enemy_X_Position + x)); // column position without subtracting,
    a = M(0x07); // check right boundary + 48 against

CheckForEnemyGroup:
    if (!c)
        goto DoGroup; // below $3f, branch if below $3f
    compare(a, 0x3f); // if $37 or greater, check for value
    if (!c)
        goto BuzzyBeetleMutate;
    compare(a, 0x37); // check for value below $37
    a &= BOOST_BINARY(00111111);
    a = M(W(EnemyData) + y); // get second byte and mask out 2 MSB

BuzzyBeetleMutate:
    a = BuzzyBeetle;
    if (z)
        goto StrID; // and if so, change goomba to buzzy beetle
    y = M(PrimaryHardMode); // check if primary hard mode flag is set
    if (!z)
        goto StrID; // value ($3f or more always fails)
    compare(a, Goomba); // if below $37, check for goomba

StrID: // store enemy object number into buffer
    goto Return;

//------------------------------------------------------------------------
    if (!z)
        goto Inc2B; // if not, leave, otherwise branch
    a = M(Enemy_Flag + x); // check to see if flag is set
    pushReturnIndex(272);
    goto InitEnemyObject;
Return_272:
    writeData(Enemy_Flag + x, a); // set flag for enemy in buffer
    a = 0x01;
    writeData(Enemy_ID + x, a);

CheckFrenzyBuffer:
    a = VineObject; // otherwise put vine in enemy identifier
    if (!z)
        goto ExEPar; // if other value <> 1, leave
    compare(a, 0x01);
    a = M(VineFlagOffset); // otherwise check vine flag offset
    if (!z)
        goto StrFre; // then branch ahead to store in enemy object buffer
    a = M(EnemyFrenzyBuffer); // if enemy object stored in frenzy buffer

StrFre: // store contents of frenzy buffer into enemy identifier value
    writeData(Enemy_ID + x, a);

InitEnemyObject:
    pushReturnIndex(273);
    goto CheckpointEnemyID;
Return_273: // jump ahead to run jump engine and subroutines
    writeData(Enemy_State + x, a);
    a = 0x00; // initialize enemy state

ExEPar: // then leave
    goto Return;

//------------------------------------------------------------------------

DoGroup:
    goto HandleGroupEnemies; // handle enemy group objects

ParseRow0e:
    writeData(EntrancePage, a); // used upon entry to area, if area is entered
    a &= BOOST_BINARY(00011111); // the 3 MSB from before, save as page number to be
    a = M(W(EnemyData) + y); // get third byte again, and this time mask out
    ++y;
    writeData(AreaPointer, a); // to addresses for level and enemy object data
    a = M(W(EnemyData) + y); // otherwise, get second byte and use as offset
    --y; // of the same area, like the underground bonus areas)
    if (!z)
        goto NotUse; // if not, do not use (this allows multiple uses
    compare(a, M(WorldNumber)); // is it the same world number as we're on?
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1; // making %xxx00000 into %00000xxx
    a >>= 1; // move 3 MSB to the bottom, effectively
    a = M(W(EnemyData) + y);
    ++y;
    ++y; // increment Y to load third byte of object

NotUse:
    goto Inc3B;

CheckThreeBytes:
    if (!z)
        goto Inc2B;
    compare(a, 0x0e);
    a &= BOOST_BINARY(00001111); // check for special row $0e
    a = M(W(EnemyData) + y); // get first byte
    y = M(EnemyDataOffset); // load current offset for enemy object data

Inc3B: // if row = $0e, increment three bytes
    ++M(EnemyDataOffset);

Inc2B: // otherwise increment two bytes
    goto Return; // and leave

//------------------------------------------------------------------------
    x = M(ObjectOffset); // reload current offset in enemy buffers
    writeData(EnemyObjectPageSel, a);
    a = 0x00; // init page select for enemy objects
    ++M(EnemyDataOffset);
    ++M(EnemyDataOffset);

CheckpointEnemyID:
    a = y; // get identifier back and use as offset for jump engine
    writeData(EnemyOffscrBitsMasked + x, a); // set offscreen masked bit
    a = 0x01;
    writeData(Enemy_Y_Position + x, a); // enemy object's vertical coordinate ($00-$14 only)
    a += 0x08; // add eight pixels to what will eventually be the
    a = M(Enemy_Y_Position + x);
    y = a; // save identifier in Y register for now
    if (c)
        goto InitEnemyRoutines; // and branch straight to the jump engine if found
    compare(a, 0x15); // check enemy object identifier for $15 or greater
    a = M(Enemy_ID + x);

InitEnemyRoutines:
    switch (a)
    {
    }

NoInitCode:
    goto Return; // this executed when enemy object has no init code

//------------------------------------------------------------------------

InitGoomba:
    goto SmallBBox; // set $09 as bounding box control, set other values
    pushReturnIndex(274);
    goto InitNormalEnemy;
Return_274: // set appropriate horizontal speed

InitPodoboo:
    goto SmallBBox; // $09 as bounding box size and set other things
    writeData(Enemy_State + x, a); // initialize enemy state, then jump to use
    a >>= 1;
    writeData(EnemyIntervalTimer + x, a); // set timer for enemy
    a >>= 1;
    writeData(Enemy_Y_Position + x, a);
    writeData(Enemy_Y_HighPos + x, a); // the bottom of the screen
    a = 0x02; // set enemy position to below

InitRetainerObj:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_Y_Position + x, a); // princess/mushroom retainer object
    a = 0xb8; // set fixed vertical position for

InitNormalEnemy:
    --y; // if not set, decrement offset
    if (!z)
        goto GetESpd;
    a = M(PrimaryHardMode); // check for primary hard mode flag set
    y = 0x01; // load offset of 1 by default

GetESpd: // get appropriate horizontal speed
    a = M(NormalXSpdData + y);

SetESpd: // store as speed for enemy object
    goto TallBBox; // branch to set bounding box control and other data
    writeData(Enemy_X_Speed + x, a);

InitRedKoopa:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_State + x, a);
    a = 0x01; // set enemy state for red koopa troopa $03
    pushReturnIndex(275);
    goto InitNormalEnemy;
Return_275: // load appropriate horizontal speed

InitHammerBro:
    goto SetBBox;
    a = 0x0b; // set specific value for bounding box size control
    writeData(EnemyIntervalTimer + x, a); // set value as delay for hammer bro to walk left
    a = M(HBroWalkingTimerData + y);
    y = M(SecondaryHardMode); // get secondary hard mode flag
    writeData(Enemy_X_Speed + x, a);
    writeData(HammerThrowingTimer + x, a); // apparently to time hammer throwing
    a = 0x00; // init horizontal speed and timer used by hammer bro

InitHorizFlySwimEnemy:
    goto SetESpd;
    a = 0x00; // initialize horizontal speed

InitBloober:
    writeData(BlooperMoveSpeed + x, a);
    a = 0x00; // initialize horizontal speed

SmallBBox: // set specific bounding box size control
    if (!z)
        goto SetBBox; // unconditional branch
    a = 0x09;

InitRedPTroopa:
    y = 0xe0; // if => $80, load position adder for 32 pixels up
    if (!n)
        goto GetCent; // if vertical coordinate < $80
    writeData(RedPTroopaOrigXPos + x, a); // be used as original vertical coordinate
    a = M(Enemy_Y_Position + x); // set vertical coordinate into location to
    y = 0x30; // load central position adder for 48 pixels down

GetCent: // send central position adder to A
    writeData(RedPTroopaCenterYPos + x, a); // store as central vertical coordinate
    a += M(Enemy_Y_Position + x); // add to current vertical coordinate
    a = y;

TallBBox: // set specific bounding box size control
    a = 0x03;

SetBBox: // set bounding box control here
    writeData(Enemy_MovingDir + x, a);
    a = 0x02; // set moving direction for left
    writeData(Enemy_BoundBoxCtrl + x, a);

InitVStf: // initialize vertical speed
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_Y_MoveForce + x, a);
    writeData(Enemy_Y_Speed + x, a); // and movement force
    a = 0x00;

InitBulletBill:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_BoundBoxCtrl + x, a);
    a = 0x09; // set bounding box control for $09
    writeData(Enemy_MovingDir + x, a);
    a = 0x02; // set moving direction for left

InitCheepCheep:
    goto Return;

//------------------------------------------------------------------------
    writeData(CheepCheepOrigYPos + x, a); // save original vertical coordinate here
    a = M(Enemy_Y_Position + x);
    writeData(CheepCheepMoveMFlag + x, a); // save as movement flag of some sort
    a &= BOOST_BINARY(00010000); // get d4 from it
    a = M(PseudoRandomBitReg + x); // check one portion of LSFR
    pushReturnIndex(276);
    goto SmallBBox;
Return_276: // set vertical bounding box, speed, init others

InitLakitu:
    if (!z)
        goto KillLakitu; // the frenzy buffer, and branch to kill lakitu if so
    a = M(EnemyFrenzyBuffer); // check to see if an enemy is already in

SetupLakitu:
    goto TallBBox2; // set $03 as bounding box again (not necessary) and leave
    pushReturnIndex(277);
    goto InitHorizFlySwimEnemy;
Return_277: // set $03 as bounding box, set other attributes
    writeData(LakituReappearTimer, a);
    a = 0x00; // erase counter for lakitu's reappearance

KillLakitu:
    goto EraseEnemyObject;

LakituAndSpinyHandler:
    y = 0x04; // start with the last enemy slot
    writeData(FrenzyEnemyTimer, a);
    a = 0x80; // set timer
    if (c)
        goto ExLSHand;
    compare(x, 0x05); // if we are on the special use slot, leave
    if (!z)
        goto ExLSHand;
    a = M(FrenzyEnemyTimer); // if timer here not expired, leave

ChkLak: // check all enemy slots to see
    x = 0x04; // start with the last enemy slot again
    if (!c)
        goto ExLSHand; // if not, leave
    compare(a, 0x07); // check to see if we're up to a certain value yet
    a = M(LakituReappearTimer);
    ++M(LakituReappearTimer); // increment reappearance timer
    if (!n)
        goto ChkLak; // loop until all slots are checked
    --y; // otherwise check another slot
    if (z)
        goto CreateSpiny; // if so, branch out of this loop
    compare(a, Lakitu); // if lakitu is on one of them
    a = M(Enemy_ID + y);

ChkNoEn: // check enemy buffer flag for non-active enemy slot
    if (n)
        goto RetEOfs; // if no empty slots were found, branch to leave
    if (!n)
        goto ChkNoEn; // branch until all slots are checked
    --x; // otherwise check next slot
    if (z)
        goto CreateL; // branch out of loop if found
    a = M(Enemy_Flag + x);

CreateL: // initialize enemy state
    pushReturnIndex(278);
    goto PutAtRightExtent;
Return_278: // finish setting up lakitu
    a = 0x20;
    pushReturnIndex(279);
    goto SetupLakitu;
Return_279: // do a sub to set up lakitu
    writeData(Enemy_ID + x, a);
    a = Lakitu; // create lakitu enemy object
    writeData(Enemy_State + x, a);
    a = 0x00;

RetEOfs: // get enemy object buffer offset again and leave
    x = M(ObjectOffset);

ExLSHand:
    goto Return;

//------------------------------------------------------------------------

CreateSpiny:
    x = 0x02;
    y = a;
    a &= BOOST_BINARY(00000011);
    a = M(PseudoRandomBitReg + x); // get 2 LSB of LSFR and save to Y
    writeData(Enemy_Y_Position + x, a);
    a -= 0x08;
    c = 1;
    a = M(Enemy_Y_Position + y); // put spiny eight pixels above where lakitu is
    writeData(Enemy_Y_HighPos + x, a);
    a = 0x01; // put spiny within vertical screen unit
    writeData(Enemy_X_Position + x, a);
    a = M(Enemy_X_Position + y);
    writeData(Enemy_PageLoc + x, a); // into the coordinates of the spiny we're going to create
    a = M(Enemy_PageLoc + y); // store horizontal coordinates (high and low) of lakitu
    if (!z)
        goto ExLSHand;
    a = M(Enemy_State + y); // if lakitu is not in normal state, branch to leave
    if (!c)
        goto ExLSHand;
    compare(a, 0x2c);
    a = M(Player_Y_Position); // if player above a certain point, branch to leave

DifLoop: // get three values and save them
    ++y;
    y = a;
    a ^= BOOST_BINARY(11111111); // otherwise get two's compliment of Y
    a = y;
    if (z)
        goto UsePosv; // branch if neither bits are set
    a &= BOOST_BINARY(00000011); // get one of the LSFR parts and save the 2 LSB
    a = M(PseudoRandomBitReg + 1 + x);
    y = a; // otherwise save value in A to Y for now
    if (c)
        goto SetSpSpd; // if moving faster than a certain amount, branch elsewhere
    compare(y, 0x08);
    y = M(Player_X_Speed); // check player's horizontal speed
    pushReturnIndex(280);
    goto PlayerLakituDiff;
Return_280: // move enemy, change direction, get value - difference
    x = M(ObjectOffset); // get enemy object buffer offset
    if (!n)
        goto DifLoop; // loop until all three are written
    --x; // decrement X for each one
    ++y;
    ++y;
    ++y; // increment Y four bytes for each value
    ++y;
    writeData(0x01 + x, a); // to $01-$03
    a = M(PRDiffAdjustData + y);

UsePosv: // put value from A in Y back to A (they will be lost anyway)
    a = y;

SetSpSpd: // set bounding box control, init attributes, lose contents of A
    --y;
    if (n)
        goto SpinyRte; // the same reason
    compare(a, 0x00); // of A were lost...branch here will never be taken for
    writeData(Enemy_X_Speed + x, a); // set horizontal speed to zero because previous contents
    y = 0x02;
    pushReturnIndex(281);
    goto SmallBBox;
Return_281:

SpinyRte: // set moving direction to the right
    writeData(Enemy_State + x, a); // put spiny in egg state and leave
    a = 0x05;
    writeData(Enemy_Flag + x, a); // enable enemy object by setting flag
    a = 0x01;
    writeData(Enemy_Y_Speed + x, a); // set vertical speed to move upwards
    a = 0xfd;
    writeData(Enemy_MovingDir + x, y);

ChpChpEx:
    goto Return;

//------------------------------------------------------------------------

InitLongFirebar:
    pushReturnIndex(282);
    goto DuplicateEnemyObj;
Return_282: // create enemy object for long firebar

InitShortFirebar:
    goto TallBBox2; // set bounding box control (not used) and leave
    writeData(Enemy_PageLoc + x, a);
    a += 0x00; // add carry to page location
    a = M(Enemy_PageLoc + x);
    writeData(Enemy_X_Position + x, a);
    a += 0x04;
    c = 0; // add four pixels to horizontal coordinate
    a = M(Enemy_X_Position + x);
    writeData(Enemy_Y_Position + x, a);
    a += 0x04;
    c = 0; // add four pixels to vertical coordinate
    a = M(Enemy_Y_Position + x);
    writeData(FirebarSpinDirection + x, a);
    a = M(FirebarSpinDirData + y); // get spinning direction of firebar
    writeData(FirebarSpinSpeed + x, a);
    a = M(FirebarSpinSpdData + y); // get spinning speed of firebar
    y = a;
    a -= 0x1b;
    c = 1; // to get proper offset for firebar data
    a = M(Enemy_ID + x); // subtract $1b from enemy identifier
    writeData(FirebarSpinState_Low + x, a);
    a = 0x00; // initialize low byte of spin state

InitFlyingCheepCheep:
    ++y; // otherwise, increment Y to allow as many as four onscreen
    if (z)
        goto MaxCC; // if secondary hard mode flag not set, do not increment Y
    a = M(SecondaryHardMode);
    y = 0x03; // load Y with default value
    writeData(FrenzyEnemyTimer, a);
    a = M(FlyCCTimerData + y); // load timer with pseudorandom offset
    y = a;
    a &= BOOST_BINARY(00000011); // set pseudorandom offset here
    a = M(PseudoRandomBitReg + 1 + x);
    pushReturnIndex(283);
    goto SmallBBox;
Return_283: // jump to set bounding box size $09 and init other values
    if (!z)
        goto ChpChpEx;
    a = M(FrenzyEnemyTimer); // if timer here not expired yet, branch to leave

MaxCC: // store whatever pseudorandom bits are in Y
    a <<= 1; // otherwise, multiply A by 2
    if (!c)
        goto GSeed; // do not change A
    compare(y, 0x19); // if moving to the right but not very quickly,
    a = 0x04;
    if (z)
        goto GSeed; // if player not moving left or right, skip this part
    y = M(Player_X_Speed); // check player's horizontal speed
    a = 0x00; // load default value
    writeData(Enemy_Y_Speed + x, a);
    a = 0xfb; // set vertical speed for cheep-cheep
    writeData(0x01, a);
    writeData(0x00, a); // and store in two places
    a &= BOOST_BINARY(00000011); // get last two bits of LSFR, first part
    a = M(PseudoRandomBitReg + x);
    if (c)
        goto ChpChpEx; // if X => Y, branch to leave
    compare(x, M(0x00)); // compare enemy object buffer offset with Y
    writeData(0x00, y);

GSeed: // save to stack
    writeData(0x00, a); // third LSFR part
    a &= BOOST_BINARY(00001111); // otherwise overwrite with lower nybble of
    a = M(PseudoRandomBitReg + 2 + x);
    if (z)
        goto RSeed; // skip this part and save contents of $00
    a &= BOOST_BINARY(00000011); // if neither of the last two bits of second LSFR set,
    a = M(PseudoRandomBitReg + 1 + x);
    writeData(0x00, a); // save it there
    a += M(0x00); // add to last two bits of LSFR we saved earlier
    c = 0;
    pha();

RSeed: // get value from stack we saved earlier
    ++M(Enemy_MovingDir + x); // increment to move towards the left
    writeData(Enemy_X_Speed + x, a);
    a += 0x01; // direction
    c = 0; // into two's compliment, thus moving in the opposite
    a ^= 0xff; // if d1 set, change horizontal speed
    a = M(Enemy_X_Speed + x);
    if (z)
        goto D2XPos1; // if d1 not set, branch
    a &= BOOST_BINARY(00000010);
    a = y; // and check for d1 set
    y = M(0x00); // get first LSFR or third LSFR lower nybble
    if (!z)
        goto D2XPos1;
    a = M(Player_X_Speed); // if player moving left or right, branch ahead of this part
    writeData(Enemy_MovingDir + x, a);
    a = 0x01; // set to move towards the right
    writeData(Enemy_X_Speed + x, a);
    a = M(FlyCCXSpeedData + y); // get horizontal speed using pseudorandom offset
    y = a; // use as pseudorandom offset here
    a += M(0x01); // add to last two bits of LSFR we saved in other place
    c = 0;
    pla();

D2XPos1: // get first LSFR or third LSFR lower nybble again
    goto FinCCSt;
    a += 0x00; // add carry and jump past this part
    a = M(Player_PageLoc); // get player's page location
    writeData(Enemy_X_Position + x, a); // and save as enemy's horizontal position
    a += M(FlyCCXPositionData + y); // if d1 set, add value obtained from pseudorandom offset
    c = 0;
    a = M(Player_X_Position); // get player's horizontal position
    if (z)
        goto D2XPos2; // check for d1 set again, branch again if not set
    a &= BOOST_BINARY(00000010);
    a = y;

D2XPos2: // get player's horizontal position
    a -= 0x00; // subtract borrow
    a = M(Player_PageLoc); // get player's page location
    writeData(Enemy_X_Position + x, a); // offset and save as enemy's horizontal position
    a -= M(FlyCCXPositionData + y); // if d1 not set, subtract value obtained from pseudorandom
    c = 1;
    a = M(Player_X_Position);

FinCCSt: // save as enemy's page location
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_Y_Position + x, a); // put enemy below the screen, and we are done
    a = 0xf8;
    writeData(Enemy_Y_HighPos + x, a); // set enemy's high vertical byte
    writeData(Enemy_Flag + x, a); // set enemy's buffer flag
    a = 0x01;
    writeData(Enemy_PageLoc + x, a);

InitBowser:
    goto Return;

//------------------------------------------------------------------------
    writeData(BowserMovementSpeed, a); // set default movement speed here
    a >>= 1;
    writeData(BowserHitPoints, a); // give bowser 5 hit points
    a = 0x05;
    writeData(EnemyFrameTimer + x, a);
    writeData(BowserFeetCounter, a); // set bowser's feet timer and in enemy timer
    a = 0x20;
    writeData(Enemy_MovingDir + x, a); // and in moving direction
    writeData(BowserFireBreathTimer, a); // store something here
    a = 0xdf;
    writeData(BowserOrigXPos, a); // store original horizontal position here
    a = M(Enemy_X_Position + x);
    writeData(BridgeCollapseOffset, a); // and bridge collapse offset
    writeData(BowserBodyControls, a); // initialize bowser's body controls
    a = 0x00;
    writeData(BowserFront_Offset, x); // save offset of first here
    pushReturnIndex(284);
    goto DuplicateEnemyObj;
Return_284: // jump to create another bowser object

DuplicateEnemyObj:
    y = 0xff; // start at beginning of enemy slots

FSLoop: // increment one slot
    writeData(Enemy_Y_Position + y, a); // copy vertical coordinate from original to new
    a = M(Enemy_Y_Position + x);
    writeData(Enemy_Y_HighPos + y, a); // set high vertical byte for new enemy
    writeData(Enemy_Flag + x, a); // set flag as normal for original enemy
    a = 0x01;
    writeData(Enemy_X_Position + y, a);
    a = M(Enemy_X_Position + x); // from original enemy to new enemy
    writeData(Enemy_PageLoc + y, a); // copy page location and horizontal coordinates
    a = M(Enemy_PageLoc + x);
    writeData(Enemy_Flag + y, a); // slot as well as enemy offset
    a |= BOOST_BINARY(10000000); // store with d7 set as flag in new enemy
    a = x; // transfer original enemy buffer offset
    writeData(DuplicateObj_Offset, y); // otherwise set offset here
    if (!z)
        goto FSLoop; // if set, branch and keep checking
    a = M(Enemy_Flag + y); // check enemy buffer flag for empty slot
    ++y;

FlmEx: // and then leave
    goto Return;

//------------------------------------------------------------------------

InitBowserFlame:
    a -= 0x10; // otherwise subtract 16 frames for secondary hard mode
    c = 1;
    if (z)
        goto SetFrT; // if secondary mode flag not set, use as timer setting
    y = M(SecondaryHardMode);
    a += 0x20; // add 32 frames by default
    c = 0;
    pushReturnIndex(285);
    goto SetFlameTimer;
Return_285: // get timer data based on flame counter
    if (z)
        goto SpawnFromMouth; // branch if found
    compare(a, Bowser);
    a = M(Enemy_ID + y); // check for bowser
    y = M(BowserFront_Offset); // get bowser's buffer offset
    writeData(NoiseSoundQueue, a);
    a |= Sfx_BowserFlame; // load bowser's flame sound into queue
    a = M(NoiseSoundQueue);
    writeData(Enemy_Y_MoveForce + x, a); // reset something here
    if (!z)
        goto FlmEx;
    a = M(FrenzyEnemyTimer); // if timer not expired yet, branch to leave

SetFrT: // set timer accordingly
    a = M(FlameYPosData + y); // load vertical position based on pseudorandom offset
    y = a; // use as offset
    writeData(BowserFlamePRandomOfs + x, a); // set here
    a &= BOOST_BINARY(00000011); // get 2 LSB from first part of LSFR
    a = M(PseudoRandomBitReg + x);
    writeData(FrenzyEnemyTimer, a);

PutAtRightExtent:
    goto FinishFlame; // skip this part to finish setting values
    writeData(Enemy_PageLoc + x, a);
    a += 0x00; // add carry
    a = M(ScreenRight_PageLoc);
    writeData(Enemy_X_Position + x, a);
    a += 0x20; // place enemy 32 pixels beyond right side of screen
    c = 0;
    a = M(ScreenRight_X_Pos);
    writeData(Enemy_Y_Position + x, a); // set vertical position

SpawnFromMouth:
    ++y; // otherwise increment now
    if (!c)
        goto SetMF; // if less, do not increment offset
    compare(a, M(Enemy_Y_Position + x)); // compare value to flame's current vertical position
    y = 0x00; // load default offset
    a = M(FlameYPosData + y); // get value here using bits as offset
    y = a; // use as offset
    writeData(Enemy_YMF_Dummy + x, a); // save here
    a &= BOOST_BINARY(00000011); // get 2 LSB from first part of LSFR
    a = M(PseudoRandomBitReg + x);
    writeData(Enemy_Y_Position + x, a); // save as flame's vertical position
    a += 0x08;
    c = 0; // add 8 pixels to bowser's vertical position
    a = M(Enemy_Y_Position + y);
    writeData(Enemy_PageLoc + x, a); // copy page location from bowser to flame
    a = M(Enemy_PageLoc + y);
    writeData(Enemy_X_Position + x, a); // save as flame's horizontal position
    a -= 0x0e; // subtract 14 pixels
    c = 1;
    a = M(Enemy_X_Position + y); // get bowser's horizontal position

SetMF: // get value here and save
    writeData(EnemyFrenzyBuffer, a); // clear enemy frenzy buffer
    a = 0x00;
    writeData(Enemy_Y_MoveForce + x, a); // to vertical movement force
    a = M(FlameYMFAdderData + y);

FinishFlame:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_State + x, a); // enemy state
    writeData(Enemy_X_MoveForce + x, a); // initialize horizontal movement force, and
    a >>= 1;
    writeData(Enemy_Flag + x, a);
    writeData(Enemy_Y_HighPos + x, a); // enemy buffer flag
    a = 0x01; // set high byte of vertical and
    writeData(Enemy_BoundBoxCtrl + x, a);
    a = 0x08; // set $08 for bounding box control

InitFireworks:
    y = 0x06; // start at last slot
    --M(FireworksCounter); // decrement for each explosion
    writeData(FrenzyEnemyTimer, a);
    a = 0x20; // otherwise reset timer
    if (!z)
        goto ExitFWk;
    a = M(FrenzyEnemyTimer); // if timer not expired yet, branch to leave

StarFChk:
    writeData(ExplosionTimerCounter + x, a); // set explosion timing counter
    a = 0x08;
    writeData(ExplosionGfxCounter + x, a); // initialize explosion counter
    a >>= 1;
    writeData(Enemy_Flag + x, a); // and activate enemy buffer flag
    writeData(Enemy_Y_HighPos + x, a); // store in vertical high byte
    a = 0x01;
    writeData(Enemy_Y_Position + x, a); // and store as vertical coordinate for fireworks object
    a = M(FireworksYPosData + y); // get vertical position using same offset
    writeData(Enemy_PageLoc + x, a); // the fireworks object
    a += 0x00; // add carry and store as page location for
    a = M(0x00);
    writeData(Enemy_X_Position + x, a); // store as the fireworks object horizontal coordinate
    a += M(FireworksXPosData + y); // add number based on offset of fireworks counter
    c = 0;
    pla(); // get saved horizontal coordinate of star flag - 48 pixels
    y = a; // use as offset
    a += M(Enemy_State + y); // add state of star flag object (possibly not necessary)
    c = 0;
    a = M(FireworksCounter); // get fireworks counter
    writeData(0x00, a); // of the star flag object
    a -= 0x00; // subtract the carry from the page location
    a = M(Enemy_PageLoc + y);
    pha(); // the stack
    a -= 0x30; // subtract 48 pixels from it and save to
    c = 1; // get horizontal coordinate of star flag object, then
    a = M(Enemy_X_Position + y);
    if (!z)
        goto StarFChk; // routine goes into infinite loop = crash
    compare(a, StarFlagObject); // if there isn't a star flag object,
    a = M(Enemy_ID + y); // check for presence of star flag object
    --y;

ExitFWk:
    goto Return;

//------------------------------------------------------------------------

BulletBillCheepCheep:
    ++y; // otherwise increment
    if (!c)
        goto ChkW2; // if less than preset, do not increment offset
    compare(a, 0xaa); // check first part of LSFR against preset value
    a = M(PseudoRandomBitReg + x);
    y = 0x00; // load default offset
    if (c)
        goto ExF17; // if so, branch to leave
    compare(x, 0x03); // are we past third enemy slot?
    if (!z)
        goto DoBulletBills; // if not, branch elsewhere
    a = M(AreaType); // are we in a water-type level?
    if (!z)
        goto ExF17;
    a = M(FrenzyEnemyTimer); // if timer not expired yet, branch to leave

ChkW2: // check world number
    ++y; // otherwise increment
    if (z)
        goto Get17ID; // if we're on world 2, do not increment offset
    compare(a, World2);
    a = M(WorldNumber);

Get17ID:
    a = M(SwimCC_IDData + y); // load identifier for cheep-cheeps
    y = a;
    a &= BOOST_BINARY(00000001); // mask out all but last bit of offset
    a = y;

Set17ID: // store whatever's in A as enemy identifier
    writeData(BitMFilter, a);
    a = 0x00; // initialize vertical position filter
    if (!z)
        goto GetRBit;
    compare(a, 0xff); // if not all bits set, skip init part and compare bits
    a = M(BitMFilter);
    writeData(Enemy_ID + x, a);

GetRBit: // get first part of LSFR
    a &= BOOST_BINARY(00000111); // mask out all but 3 LSB
    a = M(PseudoRandomBitReg + x);

ChkRBit: // use as offset
    goto ChkRBit; // do another check
    a &= BOOST_BINARY(00000111); // mask out all but 3 LSB thus keeping it 0-7
    a = y;
    ++y; // increment offset
    if (z)
        goto AddFBit;
    bit(M(BitMFilter)); // perform AND on filter without changing it
    a = M(Bitmasks + y); // load bitmask
    y = a;

AddFBit: // add bit to already set bits in filter
    goto CheckpointEnemyID; // process our new enemy object
    writeData(FrenzyEnemyTimer, a);
    a = 0x20; // set timer
    writeData(Enemy_YMF_Dummy + x, a); // initialize dummy variable
    pushReturnIndex(286);
    goto PutAtRightExtent;
Return_286: // set vertical position and other values
    a = M(Enemy17YPosData + y); // load vertical position using offset
    writeData(BitMFilter, a); // and store
    a |= M(BitMFilter);

DoBulletBills:
    y = 0xff; // start at beginning of enemy slots

BB_SLoop: // move onto the next slot
    if (!z)
        goto BB_SLoop; // bullet bill object (frenzy variant)
    compare(a, BulletBill_FrenzyVar); // check enemy identifier for
    a = M(Enemy_ID + y);
    if (z)
        goto BB_SLoop; // loop back and check another slot
    a = M(Enemy_Flag + y); // if enemy buffer flag not set,
    if (c)
        goto FireBulletBill;
    compare(y, 0x05); // branch to play sound if we've done all slots
    ++y;

ExF17: // if found, leave
    goto Return;

//------------------------------------------------------------------------

FireBulletBill:
    if (!z)
        goto Set17ID; // unconditional branch
    a = BulletBill_FrenzyVar; // load identifier for bullet bill object
    writeData(Square2SoundQueue, a);
    a |= Sfx_Blast; // play fireworks/gunfire sound
    a = M(Square2SoundQueue);

HandleGroupEnemies:
    y = BuzzyBeetle; // for buzzy beetle
    if (z)
        goto PullID; // branch, otherwise change to value
    a = M(PrimaryHardMode); // if primary hard mode flag not set,
    y = Goomba; // load value for goomba enemy
    pha(); // save another copy to stack
    if (c)
        goto SnglID; // if so, branch
    compare(a, 0x04); // was byte in $3b-$3e range?
    pha(); // save result in stack for now
    a -= 0x37; // subtract $37 from second byte read
    c = 1;
    y = 0x00; // load value for green koopa troopa

PullID: // get second copy from stack
    pla();

SnglID: // save enemy id here
    y = 0x70; // otherwise branch and use default
    if (z)
        goto SetYGp; // if so, move y coordinate up,
    a &= 0x02; // check to see if d1 was set
    y = 0xb0; // load default y coordinate
    writeData(0x01, y);

SetYGp: // save y coordinate here
    ++y; // otherwise increment to three enemies
    if (!c)
        goto CntGrp; // if not, use default value
    a >>= 1; // check to see if d0 was set
    pla(); // get first copy from stack
    y = 0x02; // load two enemies by default
    writeData(0x03, a); // save here
    a = M(ScreenRight_X_Pos); // get pixel coordinate of right edge
    writeData(0x02, a); // save here
    a = M(ScreenRight_PageLoc); // get page number of right edge of screen
    writeData(0x00, y);

CntGrp: // save number of enemies here
    writeData(NumberofGroupEnemies, y);

GrLoop: // start at beginning of enemy buffers
    x = 0xff;

GSltLp: // increment and branch if past
    if (!z)
        goto GrLoop;
    --M(NumberofGroupEnemies); // do this until we run out of enemy objects
    pushReturnIndex(287);
    goto CheckpointEnemyID;
Return_287: // process each enemy object separately
    writeData(Enemy_Flag + x, a);
    writeData(Enemy_Y_HighPos + x, a); // put enemy within the screen vertically
    a = 0x01; // activate flag for buffer, and
    writeData(Enemy_Y_Position + x, a);
    a = M(0x00); // store y coordinate for enemy object
    writeData(0x02, a);
    a += 0x00; // next enemy
    a = M(0x02); // add carry to page location for
    writeData(0x03, a);
    a += 0x18; // add 24 pixels for next enemy
    c = 0;
    writeData(Enemy_X_Position + x, a); // store x coordinate for enemy object
    a = M(0x03);
    writeData(Enemy_PageLoc + x, a); // store page location for enemy object
    a = M(0x02);
    writeData(Enemy_ID + x, a); // store enemy object identifier
    a = M(0x01);
    if (!z)
        goto GSltLp; // stored in buffer, and branch if so
    a = M(Enemy_Flag + x); // check to see if enemy is already
    if (c)
        goto NextED;
    compare(x, 0x05); // end of buffers
    ++x;

NextED: // jump to increment data offset and leave
    goto Inc2B;

InitPiranhaPlant:
    goto SetBBox2; // set specific value for bounding box control
    a = 0x09;
    writeData(PiranhaPlantUpYPos + x, a); // save original vertical coordinate - 24 pixels here
    a -= 0x18;
    c = 1;
    writeData(PiranhaPlantDownYPos + x, a); // save original vertical coordinate here
    a = M(Enemy_Y_Position + x);
    writeData(PiranhaPlant_MoveFlag + x, a); // be used as vertical speed, but not in this case
    writeData(Enemy_State + x, a); // initialize enemy state and what would normally
    a >>= 1;
    writeData(PiranhaPlant_Y_Speed + x, a);
    a = 0x01; // set initial speed

InitEnemyFrenzy:
    switch (a)
    {
    }
    a -= 0x12; // subtract 12 and use as offset for jump engine
    c = 1;
    writeData(EnemyFrenzyBuffer, a); // save in enemy frenzy buffer
    a = M(Enemy_ID + x); // load enemy identifier

NoFrenzyCode:
    goto Return;

//------------------------------------------------------------------------

EndFrenzy:
    y = 0x05; // start at last slot

LakituChk: // check enemy identifiers
    writeData(Enemy_State + y, a);
    a = 0x01; // if found, set state
    if (!z)
        goto NextFSlot;
    compare(a, Lakitu); // for lakitu
    a = M(Enemy_ID + y);

NextFSlot: // move onto the next slot
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_Flag + x, a); // disable enemy buffer flag for this object
    writeData(EnemyFrenzyBuffer, a); // empty enemy frenzy buffer
    a = 0x00;
    if (!n)
        goto LakituChk; // do this until all slots are checked
    --y;

InitJumpGPTroopa:
    writeData(Enemy_X_Speed + x, a);
    a = 0xf8; // set horizontal speed
    writeData(Enemy_MovingDir + x, a);
    a = 0x02; // set for movement to the left

TallBBox2: // set specific value for bounding box control
    a = 0x03;

SetBBox2: // set bounding box control then leave
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_BoundBoxCtrl + x, a);

InitBalPlatform:
    pushReturnIndex(288);
    goto PosPlatform;
Return_288: // do a sub to add or subtract pixels
    y = 0x02; // otherwise set value here
    if (!z)
        goto AlignP; // branch ahead
    y = M(SecondaryHardMode); // if secondary hard mode flag not set,
    --M(Enemy_Y_Position + x);
    --M(Enemy_Y_Position + x); // raise vertical position by two pixels

AlignP: // set default value here for now
    y = a; // object offset as alignment to make next positive
    a = x; // if old contents already $ff, put
    if (!n)
        goto SetBPA; // if old alignment $ff, put $ff as alignment for negative
    writeData(Enemy_State + x, a); // set platform alignment to object state here
    a = M(BalPlatformAlignment); // get current balance platform alignment
    y = 0xff;

SetBPA: // store whatever value's in Y here
    pushReturnIndex(289);
    goto PosPlatform;
Return_289: // do a sub to add 8 pixels, then run shared code here
    y = a; // init Y
    writeData(Enemy_MovingDir + x, a); // init moving direction
    a = 0x00;
    writeData(BalPlatformAlignment, y);

InitDropPlatform:
    goto CommonPlatCode; // then jump ahead to execute more code
    writeData(PlatformCollisionFlag + x, a); // set some value here
    a = 0xff;

InitHoriPlatform:
    goto CommonPlatCode; // jump ahead to execute more code
    writeData(XMoveSecondaryCounter + x, a); // init one of the moving counters
    a = 0x00;

InitVertPlatform:
    y = 0xc0; // get alternate value to add to vertical position
    a += 0x01;
    c = 0; // otherwise get two's compliment
    a ^= 0xff;
    if (!n)
        goto SetYO; // if above a certain point, skip this part
    a = M(Enemy_Y_Position + x); // check vertical position
    y = 0x40; // set default value here

SetYO: // save as top vertical position
    writeData(YPlatformCenterYPos + x, a); // save result as central vertical position
    a += M(Enemy_Y_Position + x); // to vertical position
    c = 0; // load value from earlier, add number of pixels 
    a = y;
    writeData(YPlatformTopYPos + x, a);

CommonPlatCode:
    pushReturnIndex(290);
    goto InitVStf;
Return_290: // do a sub to init certain other values 

SPBBox: // set default bounding box size control
    a = 0x06; // use alternate value if not castle or secondary not set
    if (!z)
        goto CasPBB; // if set, use default value
    y = M(SecondaryHardMode); // otherwise check for secondary hard mode flag
    if (z)
        goto CasPBB; // use default value if found
    compare(y, 0x03); // check for castle-type level
    y = M(AreaType);
    a = 0x05;

CasPBB: // set bounding box size control here and leave
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_BoundBoxCtrl + x, a);

LargeLiftUp:
    goto LargeLiftBBox; // overwrite bounding box for large platforms
    pushReturnIndex(291);
    goto PlatLiftUp;
Return_291: // execute code for platforms going up

LargeLiftDown:
    pushReturnIndex(292);
    goto PlatLiftDown;
Return_292: // execute code for platforms going down

LargeLiftBBox:
    goto SPBBox; // jump to overwrite bounding box size control

PlatLiftUp:
    goto CommonSmallLift; // skip ahead to part we should be executing
    writeData(Enemy_Y_Speed + x, a);
    a = 0xff; // set moving speed for platforms going up
    writeData(Enemy_Y_MoveForce + x, a);
    a = 0x10; // set movement amount here

PlatLiftDown:
    writeData(Enemy_Y_Speed + x, a);
    a = 0x00; // set moving speed for platforms going down
    writeData(Enemy_Y_MoveForce + x, a);
    a = 0xf0; // set movement amount here

CommonSmallLift:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_BoundBoxCtrl + x, a); // set bounding box control for small platforms
    a = 0x04;
    pushReturnIndex(293);
    goto PosPlatform;
Return_293: // do a sub to add 12 pixels due to preset value  
    y = 0x01;

PosPlatform:
    goto Return; // and go back

//------------------------------------------------------------------------
    writeData(Enemy_PageLoc + x, a); // store as new page location
    a += M(PlatPosDataHigh + y); // add or subtract page location depending on offset
    a = M(Enemy_PageLoc + x);
    writeData(Enemy_X_Position + x, a); // store as new horizontal coordinate
    a += M(PlatPosDataLow + y); // add or subtract pixels depending on offset
    c = 0;
    a = M(Enemy_X_Position + x); // get horizontal coordinate

EndOfEnemyInitCode:
    goto Return;

//------------------------------------------------------------------------

RunEnemyObjectsCore:
    a -= 0x14; // as value for jump engine
    a = y; // otherwise subtract $14 from the value and use
    if (!c)
        goto JmpEO;
    compare(y, 0x15); // if enemy object < $15, use default value
    y = M(Enemy_ID + x);
    a = 0x00; // load value 0 for jump engine by default
    x = M(ObjectOffset); // get offset for enemy object buffer

NoRunCode:
    goto Return;

//------------------------------------------------------------------------

RunRetainerObj:
    goto EnemyGfxHandler;
    pushReturnIndex(294);
    goto RelativeEnemyPosition;
Return_294:
    pushReturnIndex(295);
    goto GetEnemyOffscreenBits;
Return_295:

RunNormalEnemies:
    pushReturnIndex(296);
    goto EnemyMovementSubs;
Return_296:
    if (!z)
        goto SkipMove;
    y = M(TimerControl); // if master timer control set, skip to last routine
    pushReturnIndex(297);
    goto PlayerEnemyCollision;
Return_297:
    pushReturnIndex(298);
    goto EnemiesCollision;
Return_298:
    pushReturnIndex(299);
    goto EnemyToBGCollisionDet;
Return_299:
    pushReturnIndex(300);
    goto GetEnemyBoundBox;
Return_300:
    pushReturnIndex(301);
    goto EnemyGfxHandler;
Return_301:
    pushReturnIndex(302);
    goto RelativeEnemyPosition;
Return_302:
    pushReturnIndex(303);
    goto GetEnemyOffscreenBits;
Return_303:
    writeData(Enemy_SprAttrib + x, a);
    a = 0x00; // init sprite attributes

SkipMove:
    goto OffscreenBoundsCheck;

EnemyMovementSubs:
    switch (a)
    {
    }
    a = M(Enemy_ID + x);

NoMoveCode:
    goto Return;

//------------------------------------------------------------------------

RunBowserFlame:
    goto OffscreenBoundsCheck;
    pushReturnIndex(304);
    goto PlayerEnemyCollision;
Return_304:
    pushReturnIndex(305);
    goto GetEnemyBoundBox;
Return_305:
    pushReturnIndex(306);
    goto RelativeEnemyPosition;
Return_306:
    pushReturnIndex(307);
    goto GetEnemyOffscreenBits;
Return_307:
    pushReturnIndex(308);
    goto ProcBowserFlame;
Return_308:

RunFirebarObj:
    goto OffscreenBoundsCheck;
    pushReturnIndex(309);
    goto ProcFirebar;
Return_309:

RunSmallPlatform:
    goto OffscreenBoundsCheck;
    pushReturnIndex(310);
    goto MoveSmallPlatform;
Return_310:
    pushReturnIndex(311);
    goto DrawSmallPlatform;
Return_311:
    pushReturnIndex(312);
    goto RelativeEnemyPosition;
Return_312:
    pushReturnIndex(313);
    goto SmallPlatformCollision;
Return_313:
    pushReturnIndex(314);
    goto SmallPlatformBoundBox;
Return_314:
    pushReturnIndex(315);
    goto RelativeEnemyPosition;
Return_315:
    pushReturnIndex(316);
    goto GetEnemyOffscreenBits;
Return_316:

RunLargePlatform:
    pushReturnIndex(317);
    goto LargePlatformSubroutines;
Return_317:
    if (!z)
        goto SkipPT; // skip subroutine tree
    a = M(TimerControl); // if master timer control set,
    pushReturnIndex(318);
    goto LargePlatformCollision;
Return_318:
    pushReturnIndex(319);
    goto LargePlatformBoundBox;
Return_319:
    pushReturnIndex(320);
    goto RelativeEnemyPosition;
Return_320:
    pushReturnIndex(321);
    goto GetEnemyOffscreenBits;
Return_321:

SkipPT:
    goto OffscreenBoundsCheck;
    pushReturnIndex(322);
    goto DrawLargePlatform;
Return_322:
    pushReturnIndex(323);
    goto RelativeEnemyPosition;
Return_323:

LargePlatformSubroutines:
    switch (a)
    {
    }
    a -= 0x24;
    c = 1;
    a = M(Enemy_ID + x); // subtract $24 to get proper offset for jump table

EraseEnemyObject:
    goto Return;

//------------------------------------------------------------------------
    writeData(EnemyFrameTimer + x, a);
    writeData(Enemy_SprAttrib + x, a);
    writeData(ShellChainCounter + x, a);
    writeData(EnemyIntervalTimer + x, a);
    writeData(FloateyNum_Control + x, a);
    writeData(Enemy_State + x, a);
    writeData(Enemy_ID + x, a);
    writeData(Enemy_Flag + x, a);
    a = 0x00; // clear all enemy object variables

MovePodoboo:
    writeData(Enemy_Y_Speed + x, a); // set vertical speed to move podoboo upwards
    a = 0xf9;
    writeData(EnemyIntervalTimer + x, a); // store as new enemy timer
    a |= 0x06; // set for at least six intervals
    a &= BOOST_BINARY(00001111); // mask out high nybble
    writeData(Enemy_Y_MoveForce + x, a); // store as movement force
    a |= BOOST_BINARY(10000000); // set d7
    a = M(PseudoRandomBitReg + 1 + x); // get part of LSFR
    pushReturnIndex(324);
    goto InitPodoboo;
Return_324: // otherwise set up podoboo again
    if (!z)
        goto PdbM; // branch to move enemy if not expired
    a = M(EnemyIntervalTimer + x); // check enemy timer

PdbM: // branch to impose gravity on podoboo
    goto MoveJ_EnemyVertically;

ProcHammerBro:
    goto MoveDefeatedEnemy; // otherwise jump to something else
    if (z)
        goto ChkJH; // if not set, go ahead with code
    a &= BOOST_BINARY(00100000);
    a = M(Enemy_State + x); // check hammer bro's enemy state for d5 set

ChkJH: // check jump timer
    goto MoveHammerBroXDir; // jump to move hammer bro
    writeData(Enemy_State + x, a);
    a |= BOOST_BINARY(00001000); // set d3 in enemy state for hammer throw
    a = M(Enemy_State + x);
    if (!c)
        goto DecHT; // if carry clear, hammer not spawned, skip to decrement timer
    pushReturnIndex(325);
    goto SpawnHammerObj;
Return_325: // do a sub here to spawn hammer object
    writeData(HammerThrowingTimer + x, a); // set as new timer
    a = M(HammerThrowTmrData + y); // get timer data using flag as offset
    y = M(SecondaryHardMode); // otherwise get secondary hard mode flag
    if (!z)
        goto DecHT; // if not expired, skip ahead, do not throw hammer
    a = M(HammerThrowingTimer + x); // check hammer throwing timer
    if (!z)
        goto MoveHammerBroXDir; // if hammer bro a little offscreen, skip to movement code
    a &= BOOST_BINARY(00001100); // check offscreen bits
    a = M(Enemy_OffscreenBits);
    --M(HammerBroJumpTimer + x); // otherwise decrement jump timer
    if (z)
        goto HammerBroJumpCode; // if expired, branch to jump
    a = M(HammerBroJumpTimer + x);

DecHT: // decrement timer
    goto MoveHammerBroXDir; // jump to move hammer bro
    --M(HammerThrowingTimer + x);

HammerBroJumpCode:
    y = 0xfa; // otherwise reset to default vertical speed
    if (!z)
        goto SetHJ; // if d0 of LSFR set, branch and use current speed and $00
    a &= 0x01;
    a = M(PseudoRandomBitReg + 1 + x); // get part of LSFR, mask out all but LSB
    --M(0x00); // otherwise return value to $00
    if (!c)
        goto SetHJ; // if above the middle of the screen, use current speed and $01
    ++M(0x00); // increment preset value to $01
    compare(a, 0x70); // check to see if hammer bro is above the middle of screen
    y = 0xfd; // otherwise set alternate vertical speed
    if (n)
        goto SetHJ; // if on the bottom half of the screen, use current speed
    a = M(Enemy_Y_Position + x); // check hammer bro's vertical coordinate
    y = 0xfa; // set default vertical speed
    writeData(0x00, a); // save into temp variable for now
    a = 0x00; // load default value here
    if (z)
        goto MoveHammerBroXDir; // if set, branch ahead to moving code
    compare(a, 0x01); // check for d0 set (for jumping)
    a &= BOOST_BINARY(00000111); // mask out all but 3 LSB
    a = M(Enemy_State + x); // get hammer bro's enemy state

SetHJ: // set vertical speed for jumping
    y = a; // if secondary hard mode flag clear, set offset to 0
    if (!z)
        goto HJump;
    a = M(SecondaryHardMode); // check secondary hard mode flag
    y = a; // then use as offset
    a &= M(PseudoRandomBitReg + 2 + x); // and do bit-wise comparison with part of LSFR
    a = M(0x00); // load preset value here to use as bitmask
    writeData(Enemy_State + x, a);
    a |= 0x01;
    a = M(Enemy_State + x); // set d0 in enemy state for jumping
    writeData(Enemy_Y_Speed + x, y);

HJump: // get jump length timer data using offset from before
    writeData(HammerBroJumpTimer + x, a); // store in jump timer
    a |= BOOST_BINARY(11000000); // get contents of part of LSFR, set d7 and d6, then
    a = M(PseudoRandomBitReg + 1 + x);
    writeData(EnemyFrameTimer + x, a); // save in enemy timer
    a = M(HammerBroJumpLData + y);

MoveHammerBroXDir:
    y = 0x04; // if d6 set in counter, move him a little to the right
    if (!z)
        goto Shimmy;
    a &= BOOST_BINARY(01000000); // change hammer bro's direction every 64 frames
    a = M(FrameCounter);
    y = 0xfc; // move hammer bro a little to the left

Shimmy: // store horizontal speed
    writeData(Enemy_X_Speed + x, a); // otherwise, make the hammer bro walk left towards player
    a = 0xf8;
    if (!z)
        goto SetShim; // if not yet expired, skip to set moving direction
    a = M(EnemyIntervalTimer + x); // check walking timer
    ++y; // set to face left
    if (n)
        goto SetShim; // if enemy to the left of player, skip this part
    pushReturnIndex(326);
    goto PlayerEnemyDiff;
Return_326: // get horizontal difference between player and hammer bro
    y = 0x01; // set to face right by default
    writeData(Enemy_X_Speed + x, y);

SetShim: // set moving direction
    writeData(Enemy_MovingDir + x, y);

MoveNormalEnemy:
    if (c)
        goto ReviveStunned; // if enemy in states $03 or $04, skip ahead to yet another part
    compare(a, 0x03);
    if (z)
        goto FallE; // if enemy in state used by spiny's egg, go ahead here
    compare(a, 0x05);
    if (z)
        goto SteadM; // if enemy in normal state, branch to move enemy horizontally
    a &= BOOST_BINARY(00000111); // check d2-d0 of enemy state for any set bits
    a = M(Enemy_State + x);
    if (!z)
        goto MoveDefeatedEnemy; // if set, branch to move defeated enemy object
    a &= BOOST_BINARY(00100000); // check enemy state for d5 set
    a = M(Enemy_State + x);
    if (c)
        goto SteadM; // if set, branch to move enemy horizontally
    a <<= 1; // check enemy state for d7 set
    a = M(Enemy_State + x);
    if (!z)
        goto FallE; // to move enemy vertically, then horizontally if necessary
    a &= BOOST_BINARY(01000000); // check enemy state for d6 set, if set skip
    a = M(Enemy_State + x);
    y = 0x00; // init Y to leave horizontal movement as-is 

FallE: // do a sub here to move enemy downwards
    if (!z)
        goto SlowM; // if any other object where d6 set, jump to set Y
    if (z)
        goto SteadM;
    compare(a, PowerUpObject); // check for power-up object
    a = M(Enemy_ID + x);
    if (z)
        goto SteadM; // if not set, branch to something else
    a &= BOOST_BINARY(01000000); // check for d6 set
    if (z)
        goto MEHor; // if found, branch to move enemy horizontally
    compare(a, 0x02);
    a = M(Enemy_State + x); // check for enemy state $02
    y = 0x00;
    pushReturnIndex(327);
    goto MoveD_EnemyVertically;
Return_327:

MEHor: // jump here to move enemy horizontally for <> $2e and d6 set
    goto MoveEnemyHorizontally;

SlowM: // if branched here, increment Y to slow horizontal movement
    y = 0x01;

SteadM: // get current horizontal speed
    ++y; // otherwise increment Y to next data
    ++y;
    if (!n)
        goto AddHS; // if not moving or moving right, skip, leave Y alone
    pha(); // save to stack
    a = M(Enemy_X_Speed + x);

AddHS:
    goto Return; // original memory location, then leave

//------------------------------------------------------------------------
    writeData(Enemy_X_Speed + x, a); // get old horizontal speed from stack and return to
    pla();
    pushReturnIndex(328);
    goto MoveEnemyHorizontally;
Return_328: // then do a sub to move horizontally
    writeData(Enemy_X_Speed + x, a); // save as horizontal speed temporarily
    a += M(XSpeedAdderData + y); // add value here to slow enemy down if necessary
    c = 0;

ReviveStunned:
    ++y; // otherwise increment 2 bytes to next data
    ++y;
    if (z)
        goto SetRSpd; // if not set, use pointer as-is
    a = M(PrimaryHardMode); // check primary hard mode flag
    --y; // decrement for use as pointer
    writeData(Enemy_MovingDir + x, y); // store as pseudorandom movement direction
    ++y;
    y = a; // use as Y and increment for movement direction
    a &= 0x01; // get d0 of frame counter
    a = M(FrameCounter);
    writeData(Enemy_State + x, a); // otherwise initialize enemy state to normal
    if (!z)
        goto ChkKillGoomba; // skip ahead to something else
    a = M(EnemyIntervalTimer + x); // if enemy timer not expired yet,

SetRSpd: // load and store new horizontal speed
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_X_Speed + x, a); // and leave
    a = M(RevivedXSpeed + y);

MoveDefeatedEnemy:
    goto MoveEnemyHorizontally; // now move defeated enemy horizontally
    pushReturnIndex(329);
    goto MoveD_EnemyVertically;
Return_329: // execute sub to move defeated enemy downwards

ChkKillGoomba:
    pushReturnIndex(330);
    goto EraseEnemyObject;
Return_330: // otherwise, kill this goomba object
    if (!z)
        goto NKGmba; // branch if not found
    compare(a, Goomba); // check for goomba object
    a = M(Enemy_ID + x);
    if (!z)
        goto NKGmba; // a certain point, and branch to leave if not
    compare(a, 0x0e); // check to see if enemy timer has reached

NKGmba: // leave!
    goto Return;

//------------------------------------------------------------------------

MoveJumpingEnemy:
    goto MoveEnemyHorizontally; // jump to move enemy horizontally
    pushReturnIndex(331);
    goto MoveJ_EnemyVertically;
Return_331: // do a sub to impose gravity on green paratroopa

ProcMoveRedPTroopa:
    ++M(Enemy_Y_Position + x); // otherwise increment red paratroopa's vertical position
    if (!z)
        goto NoIncPT; // if any bits set, branch to leave
    a &= BOOST_BINARY(00000111); // mask out all but 3 LSB
    a = M(FrameCounter); // get frame counter
    if (c)
        goto MoveRedPTUpOrDown; // if current => original, skip ahead to more code
    compare(a, M(RedPTroopaOrigXPos + x));
    a = M(Enemy_Y_Position + x); // check current vs. original vertical coordinate
    writeData(Enemy_YMF_Dummy + x, a); // initialize something here
    if (!z)
        goto MoveRedPTUpOrDown; // branch if any found
    a |= M(Enemy_Y_MoveForce + x); // check for any vertical force or speed
    a = M(Enemy_Y_Speed + x);

NoIncPT: // leave
    goto Return;

//------------------------------------------------------------------------

MoveRedPTUpOrDown:
    goto MoveRedPTroopaUp; // otherwise jump to move upwards
    if (!c)
        goto MovPTDwn; // if current < central, jump to move downwards
    compare(a, M(RedPTroopaCenterYPos + x));
    a = M(Enemy_Y_Position + x); // check current vs. central vertical coordinate

MovPTDwn: // move downwards
    goto MoveRedPTroopaDown;

MoveFlyGreenPTroopa:
    y = 0xff; // otherwise set Y to move green paratroopa up
    if (!z)
        goto YSway; // branch to move green paratroopa down if set
    a &= BOOST_BINARY(01000000); // check frame counter for d6 set
    a = M(FrameCounter);
    if (!z)
        goto NoMGPT; // branch to leave if set to move up/down every fourth frame
    a &= BOOST_BINARY(00000011); // check frame counter 2 LSB for any bits set
    a = M(FrameCounter);
    y = 0x01; // set Y to move green paratroopa down
    pushReturnIndex(332);
    goto MoveWithXMCntrs;
Return_332: // do sub to move green paratroopa accordingly, and horizontally
    pushReturnIndex(333);
    goto XMoveCntr_GreenPTroopa;
Return_333: // do sub to increment primary and secondary counters

YSway: // store adder here
    writeData(Enemy_Y_Position + x, a);
    a += M(0x00); // to give green paratroopa a wavy flight
    c = 0; // add or subtract from vertical position
    a = M(Enemy_Y_Position + x);
    writeData(0x00, y);

NoMGPT: // leave!
    goto Return;

//------------------------------------------------------------------------

XMoveCntr_GreenPTroopa:
    a = 0x13; // load preset maximum value for secondary counter

XMoveCntr_Platform:
    ++M(XMoveSecondaryCounter + x); // increment secondary counter and leave
    if (z)
        goto IncPXM; // if equal, branch ahead of this part
    compare(y, M(0x01)); // compare secondary counter to preset maximum value
    if (c)
        goto DecSeXM; // if d0 of primary counter set, branch elsewhere
    a >>= 1;
    a = M(XMovePrimaryCounter + x); // get primary counter
    y = M(XMoveSecondaryCounter + x); // get secondary counter
    if (!z)
        goto NoIncXM; // every fourth frame
    a &= BOOST_BINARY(00000011); // branch to leave if not on
    a = M(FrameCounter);
    writeData(0x01, a); // store value here

NoIncXM:
    goto Return;

//------------------------------------------------------------------------

IncPXM: // increment primary counter and leave
    goto Return;

//------------------------------------------------------------------------
    ++M(XMovePrimaryCounter + x);

DecSeXM: // put secondary counter in A
    goto Return;

//------------------------------------------------------------------------
    --M(XMoveSecondaryCounter + x); // otherwise decrement secondary counter and leave
    if (z)
        goto IncPXM; // if secondary counter at zero, branch back
    a = y;

MoveWithXMCntrs:
    y = 0x02; // load alternate value here
    writeData(XMoveSecondaryCounter + x, a);
    a += 0x01;
    c = 0; // counter to two's compliment
    a ^= 0xff; // otherwise change secondary
    a = M(XMoveSecondaryCounter + x);
    if (!z)
        goto XMRight; // set, branch ahead of this part here
    a &= BOOST_BINARY(00000010); // if d1 of primary counter is
    a = M(XMovePrimaryCounter + x);
    y = 0x01; // set value here by default
    pha();
    a = M(XMoveSecondaryCounter + x); // save secondary counter to stack

XMRight: // store as moving direction
    goto Return;

//------------------------------------------------------------------------
    writeData(XMoveSecondaryCounter + x, a); // and return to original place
    pla(); // get secondary counter from stack
    writeData(0x00, a); // save value obtained from sub here
    pushReturnIndex(334);
    goto MoveEnemyHorizontally;
Return_334:
    writeData(Enemy_MovingDir + x, y);

MoveBloober:
    if (c)
        goto SBMDir; // do an unconditional branch to set
    y = M(Player_MovingDir); // otherwise, load player's moving direction and
    if (!c)
        goto FBLeft; // if not, branch to figure out moving direction
    a >>= 1; // check to see if on second or fourth slot (1 or 3)
    a = x;
    if (!z)
        goto BlooberSwim; // if any bits set, skip ahead to make swim
    a &= M(BlooberBitmasks + y); // mask out bits in LSFR using bitmask loaded with offset
    a = M(PseudoRandomBitReg + 1 + x); // get LSFR
    y = M(SecondaryHardMode); // use secondary hard mode flag as offset
    if (!z)
        goto MoveDefeatedBloober; // branch if set to move defeated bloober
    a &= BOOST_BINARY(00100000); // check enemy state for d5 set
    a = M(Enemy_State + x);

FBLeft: // set left moving direction by default
    --y; // otherwise decrement to set right moving direction
    if (!n)
        goto SBMDir; // if enemy to the right of player, keep left
    pushReturnIndex(335);
    goto PlayerEnemyDiff;
Return_335: // get horizontal difference between player and bloober
    y = 0x02;

SBMDir: // set moving direction of bloober, then continue on here
    writeData(Enemy_MovingDir + x, y);

BlooberSwim:
    writeData(Enemy_Y_Position + x, a); // otherwise, set new vertical position, make bloober swim
    if (!c)
        goto SwimX; // if so, don't do it
    compare(a, 0x20); // check to see if position is above edge of status bar
    a -= M(Enemy_Y_MoveForce + x); // subtract movement force
    c = 1;
    a = M(Enemy_Y_Position + x); // get vertical coordinate
    pushReturnIndex(336);
    goto ProcSwimmingB;
Return_336: // execute sub to make bloober swim characteristically

SwimX: // check moving direction
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_PageLoc + x, a); // store as new page location and leave
    a += 0x00; // add carry to page location
    a = M(Enemy_PageLoc + x);
    writeData(Enemy_X_Position + x, a); // store result as new horizontal coordinate
    a += M(BlooperMoveSpeed + x);
    c = 0; // add movement speed to horizontal coordinate
    a = M(Enemy_X_Position + x);
    if (!z)
        goto LeftSwim; // if moving to the left, branch to second part
    --y;
    y = M(Enemy_MovingDir + x);

LeftSwim:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_PageLoc + x, a); // store as new page location and leave
    a -= 0x00; // subtract borrow from page location
    a = M(Enemy_PageLoc + x);
    writeData(Enemy_X_Position + x, a); // store result as new horizontal coordinate
    a -= M(BlooperMoveSpeed + x);
    c = 1; // subtract movement speed from horizontal coordinate
    a = M(Enemy_X_Position + x);

MoveDefeatedBloober:
    goto MoveEnemySlowVert; // jump to move defeated bloober downwards

ProcSwimmingB:
    ++M(BlooperMoveCounter + x); // otherwise increment movement counter
    if (!z)
        goto BSwimE; // if certain horizontal speed, branch to leave
    compare(a, 0x02);
    writeData(BlooperMoveSpeed + x, a); // set as movement speed
    writeData(Enemy_Y_MoveForce + x, a); // set movement force
    a += 0x01;
    c = 0; // add to movement force to speed up swim
    a = M(Enemy_Y_MoveForce + x);
    if (!z)
        goto BSwimE; // branch to leave, execute code only every eighth frame
    pla(); // pull 3 LSB of frame counter from the stack
    if (c)
        goto SlowSwim; // branch if set
    a >>= 1; // check for d0 set
    a = M(BlooperMoveCounter + x); // get enemy's movement counter
    pha(); // and save it to the stack
    a &= BOOST_BINARY(00000111); // get 3 LSB of frame counter
    a = M(FrameCounter);
    if (!z)
        goto ChkForFloatdown; // branch if set
    a &= BOOST_BINARY(00000010); // check for d1 set
    a = M(BlooperMoveCounter + x); // get enemy's movement counter

BSwimE:
    goto Return;

//------------------------------------------------------------------------

SlowSwim:
    writeData(EnemyIntervalTimer + x, a); // set enemy's timer
    a = 0x02;
    ++M(BlooperMoveCounter + x); // otherwise increment movement counter
    if (!z)
        goto NoSSw; // if any speed, branch to leave
    writeData(BlooperMoveSpeed + x, a); // set as movement speed
    writeData(Enemy_Y_MoveForce + x, a); // set movement force
    a -= 0x01;
    c = 1; // subtract from movement force to slow swim
    a = M(Enemy_Y_MoveForce + x);
    if (!z)
        goto NoSSw; // branch to leave, execute code only every eighth frame
    pla(); // pull 3 LSB of frame counter from the stack

NoSSw: // leave
    goto Return;

//------------------------------------------------------------------------

ChkForFloatdown:
    if (z)
        goto ChkNearPlayer; // branch if expired
    a = M(EnemyIntervalTimer + x); // get enemy timer

Floatdown:
    ++M(Enemy_Y_Position + x); // otherwise increment vertical coordinate
    if (c)
        goto NoFD; // branch to leave on every other frame
    a >>= 1; // check for d0 set
    a = M(FrameCounter); // get frame counter

NoFD: // leave
    goto Return;

//------------------------------------------------------------------------

ChkNearPlayer:
    goto Return;

//------------------------------------------------------------------------
    writeData(BlooperMoveCounter + x, a); // otherwise nullify movement counter
    a = 0x00;
    if (!c)
        goto Floatdown; // if modified vertical less than player's, branch
    compare(a, M(Player_Y_Position)); // compare result with player's vertical coordinate
    a += 0x10; // add sixteen pixels
    a = M(Enemy_Y_Position + x); // get vertical coordinate

MoveBulletBill:
    goto MoveJ_EnemyVertically; // otherwise jump to move defeated bullet bill downwards
    if (z)
        goto NotDefB; // if not set, continue with movement code
    a &= BOOST_BINARY(00100000);
    a = M(Enemy_State + x); // check bullet bill's enemy object state for d5 set

NotDefB: // set bullet bill's horizontal speed
    goto MoveEnemyHorizontally; // object occurs in frenzy object $17, not from cannons)
    writeData(Enemy_X_Speed + x, a); // and move it accordingly (note: this bullet bill
    a = 0xe8;

MoveSwimmingCheepCheep:
    goto MoveEnemySlowVert; // otherwise jump to move defeated cheep-cheep downwards
    if (z)
        goto CCSwim; // if not set, continue with movement code
    a &= BOOST_BINARY(00100000); // for d5 set
    a = M(Enemy_State + x); // check cheep-cheep's enemy object state

CCSwim: // save enemy state in $03
    goto ChkSwimYPos; // jump to end of movement code
    a += 0x00; // add carry to page location and
    a = M(Enemy_Y_HighPos + x);
    writeData(Enemy_Y_Position + x, a); // save as new vertical coordinate
    a += M(0x03); // add carry to it plus enemy state to slowly move it downwards
    a = M(Enemy_Y_Position + x); // get vertical coordinate
    writeData(Enemy_YMF_Dummy + x, a); // and save dummy
    a += M(0x02); // add preset value to dummy variable to get carry
    c = 0;
    a = M(Enemy_YMF_Dummy + x);
    if (!c)
        goto CCSwimUpwards; // branch to move upwards
    compare(a, 0x10); // if movement speed set to $00,
    a = M(CheepCheepMoveMFlag + x); // check movement flag
    if (!c)
        goto ExSwCC; // if in first or second slot, branch to leave
    compare(x, 0x02); // check enemy object offset
    writeData(0x02, a); // save new value here
    a = 0x20;
    writeData(Enemy_PageLoc + x, a); // page location, then save
    a -= 0x00; // subtract borrow again, this time from the
    a = M(Enemy_PageLoc + x);
    writeData(Enemy_X_Position + x, a); // and save as new horizontal coordinate
    a -= 0x00; // subtract borrow (thus moving it slowly)
    a = M(Enemy_X_Position + x); // get horizontal coordinate
    writeData(Enemy_X_MoveForce + x, a); // store as new horizontal force
    a -= M(0x02); // subtract preset value from horizontal force
    c = 1;
    a = M(Enemy_X_MoveForce + x); // load horizontal force
    writeData(0x02, a);
    a = M(SwimCCXMoveData + y); // load value here
    y = a; // use as offset
    a -= 0x0a; // subtract ten for cheep-cheep identifiers
    c = 1;
    a = M(Enemy_ID + x); // get enemy identifier
    writeData(0x03, a);

CCSwimUpwards:
    a -= 0x00; // subtract borrow from page location
    a = M(Enemy_Y_HighPos + x);
    writeData(Enemy_Y_Position + x, a); // save as new vertical coordinate
    a -= M(0x03); // subtract borrow to it plus enemy state to slowly move it upwards
    a = M(Enemy_Y_Position + x); // get vertical coordinate
    writeData(Enemy_YMF_Dummy + x, a); // and save dummy
    a -= M(0x02); // subtract preset value to dummy variable to get borrow
    c = 1;
    a = M(Enemy_YMF_Dummy + x);

ChkSwimYPos:
    a += 0x01; // to obtain total difference of original vs. current
    c = 0; // get two's compliment of result
    a ^= 0xff;
    y = 0x10; // otherwise load movement speed to downwards
    if (!n)
        goto YPDiff; // if result positive, skip to next part
    a -= M(CheepCheepOrigYPos + x); // subtract original coordinate from current
    c = 1;
    a = M(Enemy_Y_Position + x); // get vertical coordinate
    y = 0x00; // load movement speed to upwards by default
    writeData(Enemy_Y_HighPos + x, a); // save new page location here

YPDiff: // if difference between original vs. current vertical
    writeData(CheepCheepMoveMFlag + x, a); // otherwise change movement speed
    a = y;
    if (!c)
        goto ExSwCC; // coordinates < 15 pixels, leave movement speed alone
    compare(a, 0x0f);

ExSwCC: // leave
    goto Return;

//------------------------------------------------------------------------

ProcFirebar:
    writeData(FirebarSpinState_High + x, a); // and store as new high byte of spinstate
    a &= BOOST_BINARY(00011111); // mask out all but 5 LSB
    pushReturnIndex(337);
    goto FirebarSpin;
Return_337: // modify current spinstate
    a = M(FirebarSpinSpeed + x); // load spinning speed of firebar
    if (!z)
        goto SusFbar; // ahead of this part
    a = M(TimerControl); // if master timer control set, branch
    if (!z)
        goto SkipFBar;
    a &= BOOST_BINARY(00001000); // if so, branch to leave
    a = M(Enemy_OffscreenBits); // check for d3 set
    pushReturnIndex(338);
    goto GetEnemyOffscreenBits;
Return_338: // get offscreen information

SusFbar: // get high byte of spinstate
    if (!z)
        goto SetupGFB; // if not at twenty-four branch to not change
    compare(a, 0x18);
    if (z)
        goto SkpFSte; // if eight, branch to change
    compare(a, 0x08); // check high byte of spinstate
    if (!c)
        goto SetupGFB; // if < $1f (long firebar), branch
    compare(y, 0x1f);
    y = M(Enemy_ID + x); // check enemy identifier
    a = M(FirebarSpinState_High + x);

SkpFSte:
    writeData(FirebarSpinState_High + x, a);
    a += 0x01; // add one to spinning thing to avoid horizontal state
    c = 0;

SetupGFB: // save high byte of spinning thing, modified or otherwise
    y = 0x0b; // otherwise load value for long firebars
    if (!c)
        goto SetMFbar; // no, branch then
    compare(a, 0x1f); // are we doing a long firebar?
    a = M(Enemy_ID + x);
    y = 0x05; // load value for short firebars by default
    pushReturnIndex(339);
    goto FirebarCollision;
Return_339: // draw fireball part and do collision detection
    writeData(0x00, a); // set $01 value here (not necessary)
    a = 0x01;
    writeData(0x06, a); // also save here
    writeData(Sprite_X_Position + y, a); // store as X in OAM data
    a = M(Enemy_Rel_XPos); // get relative horizontal coordinate
    writeData(0x07, a); // also save here
    writeData(Sprite_Y_Position + y, a); // store as Y in OAM data
    a = M(Enemy_Rel_YPos); // get relative vertical coordinate
    y = M(Enemy_SprDataOffset + x); // get OAM data offset
    pushReturnIndex(340);
    goto GetFirebarPosition;
Return_340: // do a sub here (residual, too early to be used now)
    pushReturnIndex(341);
    goto RelativeEnemyPosition;
Return_341: // get relative coordinates to screen
    writeData(0xef, a);

SetMFbar: // store maximum value for length of firebars
    writeData(0x00, a); // initialize counter here
    a = 0x00;
    writeData(0xed, y);

DrawFbar: // load high byte of spinstate
    writeData(0x06, a); // using long firebar offset, then store as new one here
    a = M(Enemy_SprDataOffset + y); // get offset from long firebar and load OAM data offset
    y = M(DuplicateObj_Offset); // if we arrive at fifth firebar part,
    if (!z)
        goto NextFbar;
    compare(a, 0x04);
    a = M(0x00); // check which firebar part
    pushReturnIndex(342);
    goto DrawFirebar_Collision;
Return_342: // position it properly, draw it and do collision detection
    pushReturnIndex(343);
    goto GetFirebarPosition;
Return_343: // get fireball position data depending on firebar part
    a = M(0xef);

NextFbar: // move onto the next firebar part
    if (!c)
        goto DrawFbar; // otherwise go back and do another
    compare(a, M(0xed)); // if we end up at the maximum part, go on and leave
    a = M(0x00);
    ++M(0x00);

SkipFBar:
    goto Return;

//------------------------------------------------------------------------

DrawFirebar_Collision:
    a += 0x01; // otherwise get two's compliment of horizontal adder
    a ^= 0xff;
    if (c)
        goto AddHA; // if carry was set, skip this part
    M(0x05) >>= 1; // shift LSB of mirror data
    a = M(0x01); // load horizontal adder we got from position loader
    y = M(0x06); // load OAM data offset for firebar
    writeData(0x05, a);
    a = M(0x03); // store mirror data elsewhere

AddHA: // add horizontal coordinate relative to screen to
    goto ChkFOfs;
    a -= M(0x06); // original one and skip this part
    c = 1; // otherwise subtract sprite X from the
    a = M(Enemy_Rel_XPos);
    if (c)
        goto SubtR1; // if sprite coordinate => original coordinate, branch
    compare(a, M(Enemy_Rel_XPos)); // compare X coordinate of sprite to original X of firebar
    writeData(0x06, a); // store here for now, note offset is saved in Y still
    writeData(Sprite_X_Position + y, a); // store as X coordinate here
    a += M(Enemy_Rel_XPos); // horizontal adder, modified or otherwise
    c = 0;

SubtR1: // subtract original X from the
    a -= M(Enemy_Rel_XPos); // current sprite X
    c = 1;

ChkFOfs: // if difference of coordinates within a certain range,
    if (!z)
        goto SetVFbr; // and unconditionally branch to move sprite offscreen
    a = 0xf8; // otherwise, load offscreen Y coordinate
    if (!c)
        goto VAHandl; // continue by handling vertical adder
    compare(a, 0x59);

VAHandl: // if vertical relative coordinate offscreen,
    a += 0x01; // otherwise get two's compliment of second part
    a ^= 0xff;
    if (c)
        goto AddVA; // if carry was set, skip this part
    M(0x05) >>= 1; // shift LSB of mirror data one more time
    a = M(0x02); // load vertical adder we got from position loader
    if (z)
        goto SetVFbr;
    compare(a, 0xf8); // skip ahead of this part and write into sprite Y coordinate
    a = M(Enemy_Rel_YPos);

AddVA: // add vertical coordinate relative to screen to 
    a += M(Enemy_Rel_YPos); // the second data, modified or otherwise
    c = 0;

SetVFbr: // store as Y coordinate here
    writeData(0x07, a); // also store here for now
    writeData(Sprite_Y_Position + y, a);

FirebarCollision:
    if (z)
        goto BigJp; // if player big and not crouching, jump ahead
    a = M(CrouchingFlag);
    if (!z)
        goto AdjSm; // if player small, branch to alter variables
    a = M(PlayerSize); // get player's size
    y = M(Player_Y_Position); // get player's vertical position
    if (!z)
        goto NoColFB; // skip all of this
    --y; // if player's vertical high byte offscreen,
    y = M(Player_Y_HighPos);
    writeData(0x05, a); // otherwise initialize counter
    if (!z)
        goto NoColFB; // then skip all of this
    a |= M(TimerControl); // or master timer controls set
    a = M(StarInvincibleTimer); // if star mario invincibility timer
    pha(); // to the stack for now
    a = y; // return OAM data offset and save
    pushReturnIndex(344);
    goto DrawFirebar;
Return_344: // run sub here to draw current tile of firebar

AdjSm: // if small or big but crouching, execute this part
    y = a;
    a += 0x18; // vertical coordinate
    c = 0; // then add 24 pixels to the player's
    a = y;
    ++M(0x05); // first increment our counter twice (setting $02 as flag)
    ++M(0x05);

BigJp: // get vertical coordinate, altered or otherwise, from Y
    a = y;

FBCLoop: // subtract vertical position of firebar
    a += 0x01;
    c = 0; // otherwise get two's compliment
    a ^= 0xff; // skip two's compliment part
    if (!n)
        goto ChkVFBD; // if player lower on the screen than firebar, 
    a -= M(0x07); // from the vertical coordinate of the player
    c = 1;

ChkVFBD: // if difference => 8 pixels, skip ahead of this part
    a += 0x01;
    c = 0; // otherwise get two's compliment
    a ^= 0xff; // skip two's compliment part
    if (!n)
        goto ChkFBCl; // if modded X coordinate to the right of firebar
    a -= M(0x06); // from the X coordinate of player's sprite 1
    c = 1; // subtract horizontal coordinate of firebar
    writeData(0x04, a); // store here
    a += 0x04; // add four pixels
    c = 0;
    a = M(Sprite_X_Position + 4); // get OAM X coordinate for sprite #1
    if (c)
        goto Chk2Ofs;
    compare(a, 0xf0); // because, really, what's the point?
    a = M(0x06); // if firebar on far right on the screen, skip this,
    if (c)
        goto Chk2Ofs;
    compare(a, 0x08);

ChkFBCl: // if difference < 8 pixels, collision, thus branch
    if (!c)
        goto ChgSDir; // to process
    compare(a, 0x08);

Chk2Ofs: // if value of $02 was set earlier for whatever reason,
    goto FBCLoop;
    ++M(0x05); // then increment temp and jump back
    a += M(FirebarYPos + y); // add value loaded with offset to player's vertical coordinate
    c = 0;
    a = M(Player_Y_Position);
    y = M(0x05); // otherwise get temp here and use as offset
    if (z)
        goto NoColFB;
    compare(a, 0x02); // branch to increment OAM offset and leave, no collision
    a = M(0x05);

ChgSDir: // set movement direction by default
    ++x; // otherwise increment it
    if (c)
        goto SetSDir; // then do not alter movement direction
    compare(a, M(0x06)); // is greater than horizontal coordinate of firebar
    a = M(0x04); // if OAM X coordinate of player's sprite 1
    x = 0x01;

SetSDir: // store movement direction here
    writeData(0x00, a); // get value of $00 from stack
    pla();
    pushReturnIndex(345);
    goto InjurePlayer;
Return_345: // perform sub to hurt or kill player
    pha();
    a = M(0x00); // save value written to $00 to stack
    x = 0x00;
    writeData(Enemy_MovingDir, x);

NoColFB: // get OAM data offset
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset); // get enemy object buffer offset and leave
    writeData(0x06, a);
    a += 0x04;
    c = 0; // add four to it and save
    pla();

GetFirebarPosition:
    a += 0x01;
    c = 0;
    a ^= BOOST_BINARY(00001111); // otherwise get two's compliment to oscillate
    if (!c)
        goto GetHAdder; // if lower than $09, branch ahead
    compare(a, 0x09);
    a &= BOOST_BINARY(00001111); // mask out low nybble
    pha(); // save high byte of spinstate to the stack

GetHAdder: // store result, modified or not, here
    a += 0x01;
    c = 0;
    a ^= BOOST_BINARY(00001111); // otherwise get two's compliment
    if (!c)
        goto GetVAdder;
    compare(a, 0x09); // if lower than $09, branch ahead
    a &= BOOST_BINARY(00001111); // mask out high nybble
    a += 0x08; // add eight this time, to get vertical adder
    c = 0;
    pha(); // save it again because we still need it
    pla(); // pull whatever was in A from the stack
    writeData(0x01, a);
    a = M(FirebarPosLookupTbl + y); // get data here and store as horizontal adder
    y = a; // to offset here and use as new offset
    a += M(0x01); // add oscillated high byte of spinstate
    c = 0;
    a = M(FirebarTblOffsets + y); // load offset to firebar position data
    y = M(0x00); // load number of firebar ball where we're at
    writeData(0x01, a);

GetVAdder: // store result here
    goto Return;

//------------------------------------------------------------------------
    writeData(0x03, a); // store
    a = M(FirebarMirrorData + y); // load mirroring data here
    y = a; // use as offset
    a >>= 1;
    a >>= 1;
    a >>= 1; // divide by eight or shift three to the right
    pla(); // pull out whatever was in A one last time
    writeData(0x02, a);
    a = M(FirebarPosLookupTbl + y); // get data here and store as vertica adder
    y = a;
    a += M(0x02); // this time add value in $02 to offset here and use as offset
    c = 0;
    a = M(FirebarTblOffsets + y); // load offset to firebar position data again
    y = M(0x00);
    writeData(0x02, a);

MoveFlyingCheepCheep:
    goto MoveJ_EnemyVertically; // and jump to move defeated cheep-cheep downwards
    writeData(Enemy_SprAttrib + x, a); // otherwise clear sprite attributes
    a = 0x00;
    if (z)
        goto FlyCC; // branch to continue code if not set
    a &= BOOST_BINARY(00100000); // for d5 set
    a = M(Enemy_State + x); // check cheep-cheep's enemy state

FlyCC: // move cheep-cheep horizontally based on speed and force
    a += 0x01;
    c = 0; // otherwise get two's compliment
    a ^= 0xff;
    if (!n)
        goto AddCCF; // if result within top half of screen, skip this part
    a -= M(PRandomSubtracter + y);
    c = 1; // subtract pseudorandom value based on offset from position
    a = M(Enemy_Y_Position + x); // get vertical position
    y = a; // save as offset (note this tends to go into reach of code)
    a >>= 1;
    a >>= 1;
    a >>= 1; // move high nybble to low
    a >>= 1; // get vertical movement force and
    a = M(Enemy_Y_MoveForce + x);
    pushReturnIndex(346);
    goto SetXMoveAmt;
Return_346: // branch to impose gravity on flying cheep-cheep
    a = 0x05; // set maximum speed
    y = 0x0d; // set vertical movement amount
    pushReturnIndex(347);
    goto MoveEnemyHorizontally;
Return_347:

AddCCF: // if result or two's compliment greater than eight,
    y = a;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1; // move high nybble to low again
    writeData(Enemy_Y_MoveForce + x, a);
    a += 0x10; // otherwise add to it
    c = 0;
    a = M(Enemy_Y_MoveForce + x);
    if (c)
        goto BPGet; // skip to the end without changing movement force
    compare(a, 0x08);

BPGet: // load bg priority data and store (this is very likely
    goto Return; // drawing it next frame), then leave

//------------------------------------------------------------------------
    writeData(Enemy_SprAttrib + x, a); // broken or residual code, value is overwritten before
    a = M(FlyCCBPriority + y);

MoveLakitu:
    goto MoveD_EnemyVertically; // otherwise jump to move defeated lakitu downwards
    if (z)
        goto ChkLS; // if not set, continue with code
    a &= BOOST_BINARY(00100000); // for d5 set
    a = M(Enemy_State + x); // check lakitu's enemy state

ChkLS: // if lakitu's enemy state not set at all,
    if (!z)
        goto SetLSpd; // load horizontal speed and do unconditional branch
    a = 0x10;
    writeData(EnemyFrenzyBuffer, a); // initialize frenzy buffer
    writeData(LakituMoveDirection + x, a); // otherwise initialize moving direction to move to left
    a = 0x00;
    if (z)
        goto Fr12S; // go ahead and continue with code
    a = M(Enemy_State + x);

Fr12S:
    y = 0x02;
    writeData(EnemyFrenzyBuffer, a); // set spiny identifier in frenzy buffer
    a = Spiny;

LdLDa: // load values
    pushReturnIndex(348);
    goto PlayerLakituDiff;
Return_348: // execute sub to set speed and create spinys
    if (!n)
        goto LdLDa; // do this until all values are stired
    --y;
    writeData(0x0001 + y, a); // store in zero page
    a = M(LakituDiffAdj + y);

SetLSpd: // set movement speed returned from sub
    ++y; // increment moving direction to left
    writeData(LakituMoveSpeed + x, a); // store as new moving speed
    a += 0x01;
    c = 0;
    a ^= 0xff; // get two's compliment of moving speed
    a = M(LakituMoveSpeed + x);
    if (!z)
        goto SetLMov; // if set, branch to the end to use moving direction
    a &= 0x01; // get LSB of moving direction
    a = M(LakituMoveDirection + x);
    y = 0x01; // set moving direction to right by default
    writeData(LakituMoveSpeed + x, a);

SetLMov: // store moving direction
    goto MoveEnemyHorizontally; // move lakitu horizontally
    writeData(Enemy_MovingDir + x, y);

PlayerLakituDiff:
    writeData(0x00, a);
    a += 0x01; // store two's compliment as horizontal difference
    c = 0;
    a ^= 0xff; // get two's compliment of low byte of horizontal difference
    a = M(0x00);
    ++y; // increment Y for left of player
    if (!n)
        goto ChkLakDif; // branch if enemy is to the right of the player
    pushReturnIndex(349);
    goto PlayerEnemyDiff;
Return_349: // get horizontal difference between enemy and player
    y = 0x00; // set Y for default value

ChkLakDif: // get low byte of horizontal difference
    if (!z)
        goto ExMoveLak;
    a = M(LakituMoveSpeed + x); // if horizontal speed not yet at zero, branch to leave
    --M(LakituMoveSpeed + x); // decrement horizontal speed
    if (z)
        goto SetLMovD; // branch and alter without delay
    a = M(LakituMoveDirection + x); // if moving to the left beyond maximum distance,
    if (z)
        goto ChkPSpeed; // if moving toward the player, branch, do not alter
    compare(a, M(LakituMoveDirection + x)); // to what is being used as horizontal movement direction
    a = y; // compare contents of Y, now in A
    if (!z)
        goto ChkPSpeed; // if not, branch elsewhere
    compare(a, Lakitu);
    a = M(Enemy_ID + x); // check if lakitu is in our current enemy slot
    writeData(0x00, a);
    a = 0x3c; // otherwise set maximum distance
    if (!c)
        goto ChkPSpeed;
    compare(a, 0x3c); // if within a certain distance of player, branch
    a = M(0x00);

SetLMovD: // set horizontal direction depending on horizontal
    writeData(LakituMoveDirection + x, a); // difference between enemy and player if necessary
    a = y;

ChkPSpeed:
    ++y; // otherwise increment once more
    if (!c)
        goto ChkSpinyO; // to same place
    compare(a, 0x02); // if scroll speed below a certain amount, branch
    a = M(ScrollAmount);
    if (!c)
        goto ChkSpinyO;
    compare(a, 0x19); // if player not running, branch
    a = M(Player_X_Speed);
    ++y; // otherwise increment offset
    if (z)
        goto SubDifAdj; // if scroll speed not set, branch to same place
    a = M(ScrollAmount);
    if (z)
        goto SubDifAdj; // if player not moving horizontally, branch
    a = M(Player_X_Speed);
    y = 0x00; // init offset
    writeData(0x00, a); // store as new value
    a >>= 1;
    a >>= 1; // divide masked difference by four
    a &= BOOST_BINARY(00111100); // mask out all but four bits in the middle
    a = M(0x00);

ChkSpinyO: // check for spiny object
    if (!z)
        goto SubDifAdj;
    a = M(Player_X_Speed); // if player not moving, skip this part
    if (!z)
        goto ChkEmySpd; // branch if not found
    compare(a, Spiny);
    a = M(Enemy_ID + x);

ChkEmySpd: // check vertical speed
    y = 0x00; // otherwise reinit offset
    if (!z)
        goto SubDifAdj; // branch if nonzero
    a = M(Enemy_Y_Speed + x);

SubDifAdj: // get one of three saved values from earlier
    y = M(0x00); // get saved horizontal difference
    a = M(0x0001 + y);

SPixelLak: // subtract one for each pixel of horizontal difference
    if (!n)
        goto SPixelLak; // branch until all pixels are subtracted, to adjust difference
    --y;
    a -= 0x01; // from one of three saved values
    c = 1;

ExMoveLak: // leave!!!
    goto Return;

//------------------------------------------------------------------------

BridgeCollapse:
    if (!c)
        goto MoveD_Bowser;
    compare(a, 0xe0); // if bowser not yet low enough, skip this part ahead
    a = M(Enemy_Y_Position + x); // check bowser's vertical coordinate
    if (z)
        goto SetM2;
    a &= BOOST_BINARY(01000000); // if bowser's state has d6 clear, skip to silence music
    if (z)
        goto RemoveBridge;
    a = M(Enemy_State + x); // if bowser in normal state, skip all of this
    writeData(ObjectOffset, x); // store as enemy offset here
    if (!z)
        goto SetM2; // metatile removal not necessary
    compare(a, Bowser); // if not found, branch ahead,
    a = M(Enemy_ID + x); // check enemy object identifier for bowser
    x = M(BowserFront_Offset); // get enemy offset for bowser

SetM2: // silence music
    goto KillAllEnemies; // jump to empty all enemy slots and then leave  
    ++M(OperMode_Task); // move onto next secondary mode in autoctrl mode
    writeData(EventMusicQueue, a);
    a = Silence;

MoveD_Bowser:
    goto BowserGfxHandler; // jump to draw bowser's front and rear, then leave
    pushReturnIndex(350);
    goto MoveEnemySlowVert;
Return_350: // do a sub to move bowser downwards

RemoveBridge:
    writeData(Square2SoundQueue, a); // play bowser defeat sound
    a = Sfx_BowserFall;
    writeData(Enemy_State + x, a); // set bowser's state to one of defeated states (d6 set)
    a = BOOST_BINARY(01000000);
    pushReturnIndex(351);
    goto InitVStf;
Return_351: // initialize whatever vertical speed bowser has
    if (!z)
        goto NoBFall; // the end, go ahead and skip this part
    compare(a, 0x0f); // if bridge collapse offset has not yet reached
    a = M(BridgeCollapseOffset);
    ++M(BridgeCollapseOffset); // increment bridge collapse offset
    writeData(NoiseSoundQueue, a); // producing the unique sound of the bridge collapsing 
    a = Sfx_BrickShatter; // shatter sound into the noise sfx queue thus
    writeData(Square2SoundQueue, a); // queue while at the same time loading the brick
    a = Sfx_Blast; // load the fireworks/gunfire sound into the square 2 sfx
    pushReturnIndex(352);
    goto MoveVOffset;
Return_352: // set new vram buffer offset
    x = M(ObjectOffset); // get enemy offset
    pushReturnIndex(353);
    goto RemBridge;
Return_353: // do sub here to remove bowser's bridge metatiles
    x = 0x0c; // set offset for tile data for sub to draw blank metatile
    ++y;
    y = M(VRAM_Buffer1_Offset); // increment vram buffer offset
    writeData(0x04, a);
    a = M(BridgeCollapseData + y); // load low byte of name table address and store here
    y = M(BridgeCollapseOffset); // get bridge collapse offset here
    writeData(0x05, a);
    a = 0x22; // put high byte of name table address here for now
    writeData(BowserBodyControls, a);
    a ^= 0x01; // invert bit to control bowser's feet
    a = M(BowserBodyControls);
    writeData(BowserFeetCounter, a); // otherwise, set timer now
    a = 0x04;
    if (!z)
        goto NoBFall; // if not expired, skip all of this
    --M(BowserFeetCounter); // decrement timer to control bowser's feet

NoBFall: // jump to code that draws bowser
    goto BowserGfxHandler;

RunBowser:
    if (!c)
        goto MoveD_Bowser; // otherwise proceed to KillAllEnemies
    compare(a, 0xe0); // if above a certain point, branch to move defeated bowser
    a = M(Enemy_Y_Position + x); // otherwise check vertical position
    if (z)
        goto BowserControl;
    a &= BOOST_BINARY(00100000); // then branch elsewhere to run bowser
    a = M(Enemy_State + x); // if d5 in enemy state is not set

KillAllEnemies:
    x = 0x04; // start with last enemy slot

KillLoop: // branch to kill enemy objects
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset); // get enemy object offset and leave
    writeData(EnemyFrenzyBuffer, a); // empty frenzy buffer
    if (!n)
        goto KillLoop; // do this until all slots are emptied
    --x; // move onto next enemy slot
    pushReturnIndex(354);
    goto EraseEnemyObject;
Return_354:

BowserControl:
    goto SkipToFB; // otherwise, jump over a bunch of code
    if (z)
        goto ChkMouth; // skip jump and execute code here
    a = M(TimerControl); // if master timer control not set,
    writeData(EnemyFrenzyBuffer, a); // empty frenzy buffer
    a = 0x00;

ChkMouth: // check bowser's mouth
    goto HammerChk; // otherwise skip a whole section starting here
    if (!n)
        goto FeetTmr; // if bit clear, go ahead with code here
    a = M(BowserBodyControls);

FeetTmr: // decrement timer to control bowser's feet
    writeData(BowserBodyControls, a);
    a ^= BOOST_BINARY(00000001); // to control bowser's feet
    a = M(BowserBodyControls); // and invert bit used
    writeData(BowserFeetCounter, a);
    a = 0x20; // otherwise, reset timer
    if (!z)
        goto ResetMDr; // if not expired, skip this part
    --M(BowserFeetCounter);

ResetMDr: // check frame counter
    writeData(Enemy_MovingDir + x, a); // sixteen frames
    a = 0x02; // otherwise reset moving/facing direction every
    if (!z)
        goto B_FaceP; // ahead to continue code
    a &= BOOST_BINARY(00001111); // if not on every sixteenth frame, skip
    a = M(FrameCounter);

B_FaceP: // if timer set here expired,
    if (c)
        goto HammerChk; // skip ahead to some other section
    compare(a, 0xc8); // if bowser to the right past a certain point,
    a = M(Enemy_X_Position + x);
    writeData(BowserFireBreathTimer, a); // set timer used for bowser's flame
    writeData(EnemyFrameTimer + x, a); // set timer here
    a = 0x20;
    writeData(BowserMovementSpeed, a); // set movement speed
    a = 0x02;
    writeData(Enemy_MovingDir + x, a); // set bowser to move and face to the right
    a = 0x01;
    if (!n)
        goto GetPRCmp; // and branch if bowser to the right of the player
    pushReturnIndex(355);
    goto PlayerEnemyDiff;
Return_355: // get horizontal difference between player and bowser,
    if (z)
        goto GetPRCmp; // branch to next section
    a = M(EnemyFrameTimer + x);

GetPRCmp: // get frame counter
    writeData(MaxRangeFromOrigin, a); // and store here
    a = M(PRandomRange + y); // load value using pseudorandom offset
    y = a;
    a &= BOOST_BINARY(00000011); // get pseudorandom offset
    a = M(PseudoRandomBitReg + x);
    if (!z)
        goto GetDToO; // branch to skip this part
    compare(a, M(BowserOrigXPos)); // if bowser not at original horizontal position,
    a = M(Enemy_X_Position + x);
    if (!z)
        goto HammerChk; // execute this code every fourth frame, otherwise branch
    a &= BOOST_BINARY(00000011);
    a = M(FrameCounter);

GetDToO:
    y = 0x01; // set alternate movement speed here (move right)
    a += 0x01;
    c = 0; // get two's compliment
    a ^= 0xff;
    if (!n)
        goto CompDToO; // if current position to the right of original, skip ahead
    a -= M(BowserOrigXPos); // horizontal position
    c = 1; // get difference of current vs. original
    y = 0xff; // set default movement speed here (move left)
    if (z)
        goto HammerChk;
    compare(y, 0x01); // if bowser moving and facing to the right, skip ahead
    y = M(Enemy_MovingDir + x);
    writeData(Enemy_X_Position + x, a);
    a += M(BowserMovementSpeed); // coordinate and save as new horizontal position
    c = 0; // add movement speed to bowser's horizontal
    a = M(Enemy_X_Position + x);

CompDToO: // compare difference with pseudorandom value
    writeData(BowserMovementSpeed, y); // otherwise change bowser's movement speed
    if (!c)
        goto HammerChk; // if difference < pseudorandom value, leave speed alone
    compare(a, M(MaxRangeFromOrigin));

HammerChk: // if timer set here not expired yet, skip ahead to
    pushReturnIndex(356);
    goto SpawnHammerObj;
Return_356: // execute sub on every fourth frame to spawn misc object (hammer)
    if (!z)
        goto SetHmrTmr; // if not, skip sub, otherwise
    a &= BOOST_BINARY(00000011); // check to see if it's time to execute sub
    a = M(FrameCounter);
    if (!c)
        goto SetHmrTmr; // if world 1-5, skip this part (not time to throw hammers yet)
    compare(a, World6);
    a = M(WorldNumber); // check world number
    pushReturnIndex(357);
    goto MoveEnemySlowVert;
Return_357: // otherwise start by moving bowser downwards
    if (!z)
        goto MakeBJump; // some other section of code
    a = M(EnemyFrameTimer + x);

SetHmrTmr: // get current vertical position
    writeData(EnemyFrameTimer + x, a); // set for timer here
    a = M(PRandomRange + y); // get value using pseudorandom offset
    y = a;
    a &= BOOST_BINARY(00000011); // get pseudorandom offset
    a = M(PseudoRandomBitReg + x);
    if (!c)
        goto ChkFireB; // then skip to world number check for flames
    compare(a, 0x80); // if still above a certain point
    a = M(Enemy_Y_Position + x);

SkipToFB: // jump to execute flames code
    goto ChkFireB;

MakeBJump: // if timer not yet about to expire,
    writeData(Enemy_Y_Speed + x, a); // set vertical speed to move bowser upwards
    a = 0xfe;
    pushReturnIndex(358);
    goto InitVStf;
Return_358: // initialize movement amount
    --M(Enemy_Y_Position + x); // otherwise decrement vertical coordinate
    if (!z)
        goto ChkFireB; // skip ahead to next part
    compare(a, 0x01);

ChkFireB: // check world number here
    if (c)
        goto BowserGfxHandler; // if so, skip this part here
    compare(a, World6); // world 6-7?
    if (z)
        goto SpawnFBr; // if so, execute this part here
    compare(a, World8); // world 8?
    a = M(WorldNumber);

SpawnFBr: // check timer here
    a -= 0x10; // otherwise subtract from value in A
    c = 1;
    if (z)
        goto SetFBTmr; // if secondary hard mode flag not set, skip this
    y = M(SecondaryHardMode);
    pushReturnIndex(359);
    goto SetFlameTimer;
Return_359: // get timing for bowser's flame
    if (n)
        goto ChkFireB; // if bowser's mouth open, loop back
    writeData(BowserBodyControls, a); // and close bowser's mouth
    a ^= BOOST_BINARY(10000000); // invert bowser's mouth bit to open
    a = M(BowserBodyControls);
    writeData(BowserFireBreathTimer, a); // set timer here
    a = 0x20;
    if (!z)
        goto BowserGfxHandler; // if not expired yet, skip all of this
    a = M(BowserFireBreathTimer);

SetFBTmr: // set value as timer here
    writeData(EnemyFrenzyBuffer, a); // in enemy frenzy buffer
    a = BowserFlame; // put bowser's flame identifier
    writeData(BowserFireBreathTimer, a);

BowserGfxHandler:
    y = 0xf0; // otherwise load alternate positioning value here
    if (!c)
        goto CopyFToR; // if moving left, use default
    a >>= 1;
    a = M(Enemy_MovingDir + x); // check moving direction
    y = 0x10; // load default value here to position bowser's rear
    pushReturnIndex(360);
    goto ProcessBowserHalf;
Return_360: // do a sub here to process bowser's front

CopyFToR: // move bowser's rear object position value to A
    writeData(BowserGfxFlag, a);
    a = 0x00; // nullify bowser's front/rear graphics flag
    x = a;
    writeData(ObjectOffset, a); // get original enemy object offset
    pla();
    pushReturnIndex(361);
    goto ProcessBowserHalf;
Return_361: // do a sub here to process bowser's rear
    writeData(Enemy_ID + x, a); // store in bowser's rear object
    a = Bowser; // set bowser's enemy identifier
    writeData(ObjectOffset, x);
    x = M(DuplicateObj_Offset); // put enemy object offset of rear as current
    pha();
    a = M(ObjectOffset); // save enemy object offset of front to stack
    writeData(Enemy_MovingDir + y, a); // copy moving direction also
    a = M(Enemy_MovingDir + x);
    writeData(Enemy_State + y, a); // copy enemy state directly from front to rear
    a = M(Enemy_State + x);
    writeData(Enemy_Y_Position + y, a); // for bowser's rear
    a += 0x08; // vertical coordinate and store as vertical coordinate
    c = 0; // add eight pixels to bowser's front object
    a = M(Enemy_Y_Position + x);
    writeData(Enemy_X_Position + y, a); // store A as bowser's rear horizontal coordinate
    y = M(DuplicateObj_Offset); // get bowser's rear object offset
    a += M(Enemy_X_Position + x); // add to bowser's front object horizontal coordinate
    c = 0;
    a = y;

ExBGfxH: // leave!
    goto Return;

//------------------------------------------------------------------------

ProcessBowserHalf:
    goto PlayerEnemyCollision; // do player-to-enemy collision detection
    pushReturnIndex(362);
    goto GetEnemyBoundBox;
Return_362: // get bounding box coordinates
    writeData(Enemy_BoundBoxCtrl + x, a); // set bounding box size control
    a = 0x0a;
    if (!z)
        goto ExBGfxH; // if either enemy object not in normal state, branch to leave
    a = M(Enemy_State + x);
    pushReturnIndex(363);
    goto RunRetainerObj;
Return_363: // to get offscreen bits, relative position and draw bowser (finally!)
    ++M(BowserGfxFlag); // increment bowser's graphics flag, then run subroutines

SetFlameTimer:
    a = M(FlameTimerData + y); // load value to be used then leave
    writeData(BowserFlameTimerCtrl, a);
    a &= BOOST_BINARY(00000111); // to keep in range of 0-7
    a = M(BowserFlameTimerCtrl); // mask out all but 3 LSB
    ++M(BowserFlameTimerCtrl); // increment
    y = M(BowserFlameTimerCtrl); // load counter as offset

ExFl:
    goto Return;

//------------------------------------------------------------------------

ProcBowserFlame:
    a = 0x60; // otherwise load alternate movement force to go faster
    if (z)
        goto SFlmX; // if secondary hard mode flag not set, use default
    y = M(SecondaryHardMode);
    a = 0x40; // load default movement force
    if (!z)
        goto SetGfxF; // skip all of this
    a = M(TimerControl); // if master timer control flag set,

SFlmX: // store value here
    writeData(Enemy_Y_Position + x, a); // as new vertical coordinate
    a += M(Enemy_Y_MoveForce + x); // otherwise add value here to coordinate and store
    c = 0;
    if (z)
        goto SetGfxF; // if equal, branch and do not modify coordinate
    compare(a, M(FlameYPosData + y)); // compare against coordinate data using $0417,x as offset
    a = M(Enemy_Y_Position + x); // load vertical coordinate
    y = M(BowserFlamePRandomOfs + x); // get some value here and use as offset
    writeData(Enemy_PageLoc + x, a);
    a -= 0x00; // subtract borrow from page location
    a = M(Enemy_PageLoc + x);
    writeData(Enemy_X_Position + x, a); // to the left
    a -= 0x01; // subtract one from horizontal position to move
    a = M(Enemy_X_Position + x);
    writeData(Enemy_X_MoveForce + x, a); // save new value
    a -= M(0x00);
    c = 1; // subtract value from movement force
    a = M(Enemy_X_MoveForce + x);
    writeData(0x00, a);

SetGfxF: // get new relative coordinates
    y = 0x82; // otherwise write value with vertical flip bit set
    if (z)
        goto FlmeAt; // if d1 not set, write default value
    a &= BOOST_BINARY(00000010); // invert vertical flip bit every 2 frames
    a = M(FrameCounter);
    y = 0x02; // load attributes without vertical flip by default
    writeData(0x00, a); // write first tile number
    a = 0x51; // otherwise, continue
    if (!z)
        goto ExFl; // branch to leave
    a = M(Enemy_State + x); // if bowser's flame not in normal state,
    pushReturnIndex(364);
    goto RelativeEnemyPosition;
Return_364:

FlmeAt: // set bowser's flame sprite attributes here
    x = 0x00;
    y = M(Enemy_SprDataOffset + x); // get OAM data offset
    writeData(0x01, y);

DrawFlameLoop:
    writeData(Sprite_Y_Position + 12 + y, a); // residual since flame is only made of three sprites
    a = 0xf8; // otherwise move sprite offscreen, this part likely
    if (!c)
        goto M3FOfs; // branch if carry not set
    pha();
    a >>= 1; // move d0 to carry and result to stack
    a = M(Enemy_OffscreenBits); // get enemy object offscreen bits
    y = M(Enemy_SprDataOffset + x); // get OAM data offset
    pushReturnIndex(365);
    goto GetEnemyOffscreenBits;
Return_365: // get offscreen information
    x = M(ObjectOffset); // reload original enemy offset
    if (!c)
        goto DrawFlameLoop;
    compare(x, 0x03); // have not yet been done
    ++x; // move onto the next OAM, and branch if three
    ++y; // increment Y four times to move onto the next OAM
    ++y;
    ++y;
    ++y;
    writeData(Enemy_Rel_XPos, a); // then add eight to it and store
    a += 0x08;
    c = 0;
    writeData(Sprite_X_Position + y, a); // write X relative coordinate of current enemy object
    a = M(Enemy_Rel_XPos);
    writeData(Sprite_Attributes + y, a); // write saved attributes into OAM data
    a = M(0x01);
    ++M(0x00); // increment tile number to draw more bowser's flame
    writeData(Sprite_Tilenumber + y, a); // write current tile number into OAM data
    a = M(0x00);
    writeData(Sprite_Y_Position + y, a); // write into Y coordinate of OAM data
    a = M(Enemy_Rel_YPos); // get Y relative coordinate of current enemy object

M3FOfs: // get bits from stack
    writeData(Sprite_Y_Position + 8 + y, a);
    a = 0xf8; // otherwise move third sprite offscreen
    if (!c)
        goto M2FOfs; // branch if carry not set again
    pha();
    a >>= 1; // move d1 to carry and move bits back to stack
    pla();

M2FOfs: // get bits from stack again
    writeData(Sprite_Y_Position + 4 + y, a);
    a = 0xf8; // otherwise move second sprite offscreen
    if (!c)
        goto M1FOfs; // branch if carry not set yet again
    pha();
    a >>= 1; // move d2 to carry and move bits back to stack again
    pla();

M1FOfs: // get bits from stack one last time
    writeData(Sprite_Y_Position + y, a); // otherwise move first sprite offscreen
    a = 0xf8;
    if (!c)
        goto ExFlmeD; // branch if carry not set one last time
    a >>= 1; // move d3 to carry
    pla();

ExFlmeD: // leave
    goto Return;

//------------------------------------------------------------------------

RunFireworks:
    if (c)
        goto FireworksSoundScore; // if at a certain point, branch to kill this object
    compare(a, 0x03); // check explosion graphics counter
    a = M(ExplosionGfxCounter + x);
    ++M(ExplosionGfxCounter + x); // increment explosion graphics counter
    writeData(ExplosionTimerCounter + x, a); // reset counter
    a = 0x08;
    if (!z)
        goto SetupExpl; // if not expired, skip this part
    --M(ExplosionTimerCounter + x); // decrement explosion timing counter here

SetupExpl: // get relative coordinates of explosion
    goto Return;

//------------------------------------------------------------------------
    pushReturnIndex(366);
    goto DrawExplosion_Fireworks;
Return_366: // do a sub to draw the explosion then leave
    a = M(ExplosionGfxCounter + x); // get explosion graphics counter
    y = M(Enemy_SprDataOffset + x); // get OAM data offset
    writeData(Fireball_Rel_XPos, a);
    a = M(Enemy_Rel_XPos); // first vertical, then horizontal
    writeData(Fireball_Rel_YPos, a); // from the enemy object to the fireball object
    a = M(Enemy_Rel_YPos); // copy relative coordinates
    pushReturnIndex(367);
    goto RelativeEnemyPosition;
Return_367:

FireworksSoundScore:
    goto EndAreaPoints; // jump to award points accordingly then leave
    writeData(DigitModifier + 4, a);
    a = 0x05; // set part of score modifier for 500 points
    writeData(Square2SoundQueue, a);
    a = Sfx_Blast; // play fireworks/gunfire sound
    writeData(Enemy_Flag + x, a);
    a = 0x00; // disable enemy buffer flag

RunStarFlagObj:
    switch (a)
    {
    } // otherwise jump to appropriate sub
    if (c)
        goto StarFlagExit;
    compare(a, 0x05); // if greater than 5, branch to exit
    a = M(StarFlagTaskControl); // check star flag object task number here
    writeData(EnemyFrenzyBuffer, a);
    a = 0x00; // initialize enemy frenzy buffer

GameTimerFireworks:
    a = 0xff; // otherwise set value for no fireworks
    if (z)
        goto SetFWC; // if last digit of game timer set to 6, skip ahead
    compare(a, 0x06);
    y = 0x00; // otherwise load one more potential value for state
    if (z)
        goto SetFWC; // if last digit of game timer set to 3, skip ahead
    compare(a, 0x03);
    y = 0x03; // otherwise load new value for state
    if (z)
        goto SetFWC; // if last digit of game timer set to 1, skip ahead
    compare(a, 0x01);
    a = M(GameTimerDisplay + 2); // get game timer's last digit
    y = 0x05; // set default state for star flag object

SetFWC: // set fireworks counter here
    writeData(Enemy_State + x, y); // set whatever state we have in star flag object
    writeData(FireworksCounter, a);

IncrementSFTask1:
    ++M(StarFlagTaskControl); // increment star flag object task number

StarFlagExit:
    goto Return; // leave

//------------------------------------------------------------------------

AwardGameTimerPoints:
    writeData(Square2SoundQueue, a); // load timer tick sound
    a = Sfx_TimerTick;
    if (z)
        goto NoTTick; // for four frames every four frames) branch if not set
    a &= BOOST_BINARY(00000100); // check frame counter for d2 set (skip ahead
    a = M(FrameCounter);
    if (z)
        goto IncrementSFTask1; // if no time left on game timer at all, branch to next task
    a |= M(GameTimerDisplay + 2);
    a |= M(GameTimerDisplay + 1);
    a = M(GameTimerDisplay); // check all game timer digits for any intervals left

NoTTick: // set offset here to subtract from game timer's last digit
    writeData(DigitModifier + 5, a); // per game timer interval subtracted
    a = 0x05; // set now to add 50 points
    pushReturnIndex(368);
    goto DigitsMathRoutine;
Return_368: // subtract digit
    writeData(DigitModifier + 5, a); // from the last digit of the game timer
    a = 0xff; // set adder here to $ff, or -1, to subtract one
    y = 0x23;

EndAreaPoints:
    y = 0x11; // otherwise load offset for luigi's score
    if (z)
        goto ELPGive; // if mario, do not change
    a = M(CurrentPlayer); // check player on the screen
    y = 0x0b; // load offset for mario's score by default

ELPGive: // award 50 points per game timer interval
    goto UpdateNumber; // jump to print the new score and game timer
    a |= BOOST_BINARY(00000100); // add four to set nybble for game timer
    a <<= 1;
    a <<= 1;
    a <<= 1; // shift to high nybble
    a <<= 1; // fireworks explosion if branched here from there)
    a = M(CurrentPlayer); // get player on the screen (or 500 points per
    pushReturnIndex(369);
    goto DigitsMathRoutine;
Return_369:

RaiseFlagSetoffFWorks:
    goto DrawStarFlag; // and skip this part here
    --M(Enemy_Y_Position + x); // otherwise, raise star flag by one pixel
    if (!c)
        goto SetoffF; // if star flag higher vertically, branch to other code
    compare(a, 0x72); // against preset value
    a = M(Enemy_Y_Position + x); // check star flag's vertical position

SetoffF: // check fireworks counter
    writeData(EnemyFrenzyBuffer, a); // otherwise set fireworks object in frenzy queue
    a = Fireworks;
    if (n)
        goto DrawFlagSetTimer; // if no fireworks set to go off, skip this part
    if (z)
        goto DrawFlagSetTimer; // if no fireworks left to go off, skip this part
    a = M(FireworksCounter);

DrawStarFlag:
    x = 0x03; // do four sprites
    y = M(Enemy_SprDataOffset + x); // get OAM data offset
    pushReturnIndex(370);
    goto RelativeEnemyPosition;
Return_370: // get relative coordinates of star flag

DSFLoop: // get relative vertical coordinate
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset); // get enemy object offset and leave
    if (!n)
        goto DSFLoop; // do this until all sprites are done
    --x; // move onto next sprite
    ++y;
    ++y; // for next sprite
    ++y; // increment OAM data offset four bytes
    ++y;
    writeData(Sprite_X_Position + y, a); // store as X coordinate
    a += M(StarFlagXPosAdder + x); // add X coordinate adder data
    c = 0;
    a = M(Enemy_Rel_XPos); // get relative horizontal coordinate
    writeData(Sprite_Attributes + y, a); // store as attributes
    a = 0x22; // set palette and background priority bits
    writeData(Sprite_Tilenumber + y, a); // store as tile number
    a = M(StarFlagTileData + x); // get tile number
    writeData(Sprite_Y_Position + y, a); // store as Y coordinate
    a += M(StarFlagYPosAdder + x); // add Y coordinate adder data
    c = 0;
    a = M(Enemy_Rel_YPos);

DrawFlagSetTimer:
    writeData(EnemyIntervalTimer + x, a); // set interval timer here
    a = 0x06;
    pushReturnIndex(371);
    goto DrawStarFlag;
Return_371: // do sub to draw star flag

IncrementSFTask2:
    goto Return;

//------------------------------------------------------------------------
    ++M(StarFlagTaskControl); // move onto next task

DelayToAreaEnd:
    if (z)
        goto IncrementSFTask2; // branch to increment task
    a = M(EventMusicBuffer); // if event music buffer empty,
    if (!z)
        goto StarFlagExit2; // not yet expired, branch to leave
    a = M(EnemyIntervalTimer + x); // if interval timer set in previous task
    pushReturnIndex(372);
    goto DrawStarFlag;
Return_372: // do sub to draw star flag

StarFlagExit2:
    goto Return; // otherwise leave

//------------------------------------------------------------------------

MovePiranhaPlant:
    writeData(0x00, a); // save as new horizontal difference
    a += 0x01;
    c = 0; // and change to two's compliment
    a ^= 0xff;
    a = M(0x00); // otherwise get saved horizontal difference
    if (!n)
        goto ChkPlayerNearPipe; // piranha plant, and branch if enemy to right of player
    pushReturnIndex(373);
    goto PlayerEnemyDiff;
Return_373: // get horizontal difference between player and
    if (n)
        goto ReversePlantSpeed; // to move enemy upwards out of pipe
    a = M(PiranhaPlant_Y_Speed + x); // if currently rising, branch 
    if (!z)
        goto SetupToMovePPlant; // if moving, skip to part ahead
    a = M(PiranhaPlant_MoveFlag + x); // check movement flag
    if (!z)
        goto PutinPipe; // branch to end if not yet expired
    a = M(EnemyFrameTimer + x); // check enemy's timer here
    if (!z)
        goto PutinPipe; // if set at all, branch to leave
    a = M(Enemy_State + x); // check enemy state

ChkPlayerNearPipe:
    if (!c)
        goto PutinPipe; // if player within a certain distance, branch to leave
    compare(a, 0x21);
    a = M(0x00); // get saved horizontal difference

ReversePlantSpeed:
    ++M(PiranhaPlant_MoveFlag + x); // increment to set movement flag
    writeData(PiranhaPlant_Y_Speed + x, a); // save as new vertical speed
    a += 0x01;
    c = 0; // change to two's compliment
    a ^= 0xff;
    a = M(PiranhaPlant_Y_Speed + x); // get vertical speed

SetupToMovePPlant:
    a = M(PiranhaPlantUpYPos + x); // otherwise get other vertical coordinate (highest point)
    if (!n)
        goto RiseFallPiranhaPlant; // branch if moving downwards
    y = M(PiranhaPlant_Y_Speed + x); // get vertical speed
    a = M(PiranhaPlantDownYPos + x); // get original vertical coordinate (lowest point)

RiseFallPiranhaPlant:
    writeData(EnemyFrameTimer + x, a); // set timer to delay piranha plant movement
    a = 0x40;
    writeData(PiranhaPlant_MoveFlag + x, a); // otherwise clear movement flag
    a = 0x00;
    if (!z)
        goto PutinPipe; // branch to leave if not yet reached
    compare(a, M(0x00)); // compare against low or high coordinate
    writeData(Enemy_Y_Position + x, a); // save as new vertical coordinate
    a += M(PiranhaPlant_Y_Speed + x); // add vertical speed to move up or down
    c = 0;
    a = M(Enemy_Y_Position + x); // get current vertical coordinate
    if (!z)
        goto PutinPipe; // branch to leave if set (likely not necessary)
    a = M(TimerControl); // get master timer control
    if (!c)
        goto PutinPipe; // branch to leave if d0 set (execute code every other frame)
    a >>= 1;
    a = M(FrameCounter); // get frame counter
    writeData(0x00, a); // save vertical coordinate here

PutinPipe:
    goto Return; // then leave

//------------------------------------------------------------------------
    writeData(Enemy_SprAttrib + x, a); // attributes to give illusion of being inside pipe
    a = BOOST_BINARY(00100000); // set background priority bit in sprite

FirebarSpin:
    goto Return;

//------------------------------------------------------------------------
    a += 0x00;
    a = M(FirebarSpinState_High + x); // add carry to what would normally be the vertical speed
    writeData(FirebarSpinState_Low + x, a);
    a += M(0x07); // the horizontal speed
    c = 0; // add spinning speed to what would normally be
    a = M(FirebarSpinState_Low + x);
    y = 0x18; // possibly residual ldy
    if (!z)
        goto SpinCounterClockwise; // if moving counter-clockwise, branch to other part
    a = M(FirebarSpinDirection + x); // check spinning direction
    writeData(0x07, a); // save spinning speed here

SpinCounterClockwise:
    goto Return;

//------------------------------------------------------------------------
    a -= 0x00;
    a = M(FirebarSpinState_High + x); // add carry to what would normally be the vertical speed
    writeData(FirebarSpinState_Low + x, a);
    a -= M(0x07); // the horizontal speed
    c = 1; // subtract spinning speed to what would normally be
    a = M(FirebarSpinState_Low + x);
    y = 0x08; // possibly residual ldy

BalancePlatform:
    goto EraseEnemyObject; // if far below screen, kill the object
    if (!z)
        goto DoBPl;
    compare(a, 0x03);
    a = M(Enemy_Y_HighPos + x); // check high byte of vertical position

DoBPl: // get object's state (set to $ff or other platform offset)
    goto Return;

//------------------------------------------------------------------------
    if (!n)
        goto CheckBalPlatform; // if doing other balance platform, branch to leave
    a = M(Enemy_State + x);

CheckBalPlatform:
    goto PlatformFall; // if set, jump here
    if (z)
        goto ChkForFall;
    a = M(Enemy_MovingDir + x); // get moving direction
    writeData(0x00, a); // store here
    a = M(PlatformCollisionFlag + x); // get collision flag of platform
    y = a; // save offset from state as Y

ChkForFall:
    goto StopPlatforms; // to make platforms stop
    writeData(Enemy_Y_Position + x, a); // of current platform and branch elsewhere
    a += 0x02; // otherwise add 2 pixels to vertical position
    c = 0;
    if (z)
        goto MakePlatformFall; // enemy state, branch to make platforms fall
    compare(y, M(0x00)); // if collision flag is set to same value as
    if (!c)
        goto ChkOtherForFall; // if not, branch elsewhere
    compare(a, M(Enemy_Y_Position + x));
    a = 0x2d; // check if platform is above a certain point

MakePlatformFall:
    goto InitPlatformFall; // make platforms fall

ChkOtherForFall:
    goto StopPlatforms; // jump to stop movement and do not return
    writeData(Enemy_Y_Position + y, a); // of other platform and branch elsewhere
    a += 0x02; // otherwise add 2 pixels to vertical position
    c = 0;
    if (z)
        goto MakePlatformFall; // enemy state, branch to make platforms fall
    compare(x, M(0x00)); // if collision flag is set to same value as
    if (!c)
        goto ChkToMoveBalPlat; // if not, branch elsewhere
    compare(a, M(Enemy_Y_Position + y)); // check if other platform is above a certain point

ChkToMoveBalPlat:
    if (c)
        goto PlatUp; // otherwise keep branch to move upwards
    if (!c)
        goto PlatSt; // if not enough, branch to stop movement
    compare(a, 0x0b); // check if there's still a little force left
    a = M(0x00);
    if (!z)
        goto PlatUp; // branch elsewhere if moving upwards
    if (n)
        goto PlatDn; // branch if moving downwards
    a += 0x00; // add carry to vertical speed
    a = M(Enemy_Y_Speed + x);
    writeData(0x00, a); // store here
    a += 0x05;
    c = 0; // add $05 to contents of moveforce, whatever they be
    a = M(Enemy_Y_MoveForce + x);
    if (!n)
        goto ColFlg; // branch if collision
    a = M(PlatformCollisionFlag + x); // get collision flag
    pha();
    a = M(Enemy_Y_Position + x); // save vertical position to stack

ColFlg: // if collision flag matches
    if (z)
        goto PlatDn; // current enemy object offset, branch
    compare(a, M(ObjectOffset));

PlatUp: // do a sub to move upwards
    goto DoOtherPlatform; // jump ahead to remaining code
    pushReturnIndex(374);
    goto MovePlatformUp;
Return_374:

PlatSt: // do a sub to stop movement
    goto DoOtherPlatform; // jump ahead to remaining code
    pushReturnIndex(375);
    goto StopPlatforms;
Return_375:

PlatDn: // do a sub to move downwards
    pushReturnIndex(376);
    goto MovePlatformDown;
Return_376:

DoOtherPlatform:
    pushReturnIndex(377);
    goto PositionPlayerOnVPlat;
Return_377: // and use it to position player accordingly
    x = a; // put offset which collision occurred here
    if (n)
        goto DrawEraseRope;
    a = M(PlatformCollisionFlag + x); // if no collision, skip this part here
    writeData(Enemy_Y_Position + y, a); // platform to move it in the opposite direction
    a += M(Enemy_Y_Position + y); // add difference to vertical coordinate of other
    c = 0;
    a -= M(Enemy_Y_Position + x); // get difference of old vs. new coordinate
    c = 1;
    pla(); // get old vertical coordinate from stack
    y = M(Enemy_State + x); // get offset of other platform

DrawEraseRope:
    goto OtherRope; // jump to skip this part
    writeData(VRAM_Buffer1 + 4 + x, a);
    a = 0xa3; // and right sides of rope in vram buffer
    writeData(VRAM_Buffer1 + 3 + x, a); // otherwise put tile numbers for left
    a = 0xa2;
    if (n)
        goto EraseR1; // to do something else
    a = M(Enemy_Y_Speed + y); // if platform moving upwards, branch 
    writeData(VRAM_Buffer1 + 2 + x, a);
    a = 0x02; // set length for 2 bytes
    writeData(VRAM_Buffer1 + 1 + x, a);
    a = M(0x00);
    writeData(VRAM_Buffer1 + x, a); // first the high byte, then the low
    a = M(0x01); // write name table address to vram buffer
    pushReturnIndex(378);
    goto SetupPlatformRope;
Return_378: // do a sub to figure out where to put new bg tiles
    pha();
    pha(); // save two copies of vertical speed to stack
    a = M(Enemy_Y_Speed + y);
    if (c)
        goto ExitRp; // and skip this, branch to leave
    compare(x, 0x20); // if offset beyond a certain point, go ahead
    x = M(VRAM_Buffer1_Offset); // get vram buffer offset
    if (z)
        goto ExitRp; // if not, skip all of this and branch to leave
    a |= M(Enemy_Y_MoveForce + y); // moving at all
    a = M(Enemy_Y_Speed + y); // check to see if current platform is
    y = M(ObjectOffset); // get enemy object offset

EraseR1: // put blank tiles in vram buffer
    writeData(VRAM_Buffer1 + 4 + x, a);
    writeData(VRAM_Buffer1 + 3 + x, a); // to erase rope
    a = 0x24;

OtherRope:
    goto EndRp; // jump to skip this part
    writeData(VRAM_Buffer1 + 9 + x, a); // transfer buffer
    a = 0xa3; // and right sides of rope in vram
    writeData(VRAM_Buffer1 + 8 + x, a); // otherwise put tile numbers for left
    a = 0xa2;
    if (!n)
        goto EraseR2; // if moving upwards (note inversion earlier), skip this
    pla(); // pull first copy of vertical speed from stack
    writeData(VRAM_Buffer1 + 7 + x, a); // set length again for 2 bytes
    a = 0x02;
    writeData(VRAM_Buffer1 + 6 + x, a);
    a = M(0x00); // the other platform
    writeData(VRAM_Buffer1 + 5 + x, a); // this time we're doing putting tiles for
    a = M(0x01); // write name table address to vram buffer
    pushReturnIndex(379);
    goto SetupPlatformRope;
Return_379: // do sub again to figure out where to put bg tiles  
    a ^= 0xff; // invert bits to reverse speed
    pla(); // pull second copy of vertical speed from stack
    y = a; // use as Y here
    a = M(Enemy_State + y); // get offset of other platform from state

EraseR2: // put blank tiles in vram buffer
    writeData(VRAM_Buffer1 + 9 + x, a);
    writeData(VRAM_Buffer1 + 8 + x, a); // to erase rope
    a = 0x24;

EndRp: // put null terminator at the end
    writeData(VRAM_Buffer1_Offset, a);
    a += 10;
    c = 0; // and store
    a = M(VRAM_Buffer1_Offset); // add ten bytes to the vram buffer offset
    writeData(VRAM_Buffer1 + 10 + x, a);
    a = 0x00;

ExitRp: // get enemy object buffer offset and leave
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

SetupPlatformRope:
    a += 0x10; // otherwise add sixteen more pixels
    c = 0;
    if (!z)
        goto GetLRp; // use coordinate as-is
    x = M(SecondaryHardMode); // if secondary hard mode flag set,
    a += 0x08; // add eight pixels
    c = 0;
    a = M(Enemy_X_Position + y); // get horizontal coordinate
    pha(); // save second/third copy to stack

GetLRp: // save modified horizontal coordinate to stack
    x = a; // save as X
    a += 0x08; // add eight to vertical coordinate and
    c = 0;
    a = x;
    if (!n)
        goto GetHRp; // skip this part if moving downwards or not at all
    pla(); // get second/third copy of vertical speed from stack
    x = M(Enemy_Y_Position + y); // get vertical coordinate
    writeData(0x00, a); // store result here as part of name table low byte
    a >>= 1;
    a >>= 1;
    a >>= 1; // and shift three bits to the right
    a &= BOOST_BINARY(11110000); // from the stack, mask out low nybble
    pla(); // pull modified horizontal coordinate
    writeData(0x02, a); // and save here
    a += 0x00; // add carry to page location
    a = M(Enemy_PageLoc + y);
    pha();

GetHRp: // move vertical coordinate to A
    writeData(0x00, a);
    a &= BOOST_BINARY(10111111); // mask out d6 of low byte of name table address
    a = M(0x00);
    if (!c)
        goto ExPRp; // bottom of the screen, we're done, branch to leave
    compare(a, 0xe8); // if vertical position not below the
    a = M(Enemy_Y_Position + y);
    writeData(0x00, a); // save as name table low byte
    a += M(0x00); // add to horizontal part saved here
    c = 0;
    a &= BOOST_BINARY(11100000); // mask out low nybble and LSB of high nybble
    pla(); // get modified vertical coordinate from stack
    writeData(0x01, a); // the proper name table and the right place on it
    a |= M(0x01); // rest of the bits of the high byte, to get
    a <<= 1; // shift twice to the left and save with the
    a <<= 1;
    a &= 0x01; // mask out all but LSB
    a = M(0x02); // get saved page location from earlier
    writeData(0x01, a); // address, then store
    a |= BOOST_BINARY(00100000); // d5 to get appropriate high byte of name table
    a &= BOOST_BINARY(00000011); // mask out all bits but d7 and d6, then set
    a.rol(); // rotate carry to d0, thus d7 and d6 are at 2 LSB
    pha(); // save modified vertical coordinate to stack
    a.rol(); // rotate d7 to d0 and d6 into carry
    a <<= 1;
    x = M(VRAM_Buffer1_Offset); // get vram buffer offset
    a = x;

ExPRp: // leave!
    goto Return;

//------------------------------------------------------------------------

InitPlatformFall:
    writeData(Enemy_MovingDir + x, a); // falling platforms
    a = 0x01; // set moving direction as flag for
    writeData(FloateyNum_Y_Pos + x, a);
    a = M(Player_Y_Position);
    writeData(FloateyNum_X_Pos + x, a); // put floatey number coordinates where player is
    a = M(Player_Rel_XPos);
    pushReturnIndex(380);
    goto SetupFloateyNumber;
Return_380: // award 1000 points to player
    a = 0x06;
    pushReturnIndex(381);
    goto GetEnemyOffscreenBits;
Return_381: // get offscreen bits
    x = a;
    a = y; // move offset of other platform from Y to X

StopPlatforms:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_Y_MoveForce + y, a);
    writeData(Enemy_Y_Speed + y, a); // for both platforms and leave
    pushReturnIndex(382);
    goto InitVStf;
Return_382: // initialize vertical speed and low byte

PlatformFall:
    pushReturnIndex(383);
    goto PositionPlayerOnVPlat;
Return_383: // and position player appropriately
    x = a; // transfer collision flag offset as offset to X
    if (n)
        goto ExPF; // skip this part
    a = M(PlatformCollisionFlag + x); // if player not standing on either platform,
    x = M(ObjectOffset);
    pushReturnIndex(384);
    goto MoveFallingPlatform;
Return_384: // make other platform fall
    x = a; // pull offset from stack and save to X
    pla();
    pushReturnIndex(385);
    goto MoveFallingPlatform;
Return_385: // make current platform fall
    pha();
    a = y; // save offset for other platform to stack

ExPF: // get enemy object buffer offset and leave
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

YMovingPlatform:
    ++M(Enemy_Y_Position + x); // increase vertical position every eighth frame
    if (!z)
        goto SkipIY;
    a &= BOOST_BINARY(00000111); // check for every eighth frame
    a = M(FrameCounter);
    if (c)
        goto ChkYCenterPos; // ahead of all this
    compare(a, M(YPlatformTopYPos + x)); // if current vertical position => top position, branch
    a = M(Enemy_Y_Position + x);
    writeData(Enemy_YMF_Dummy + x, a); // initialize dummy variable
    if (!z)
        goto ChkYCenterPos;
    a |= M(Enemy_Y_MoveForce + x); // check on other position
    a = M(Enemy_Y_Speed + x); // if platform moving up or down, skip ahead to

SkipIY: // skip ahead to last part
    goto ChkYPCollision;

ChkYCenterPos:
    goto ChkYPCollision;
    pushReturnIndex(386);
    goto MovePlatformUp;
Return_386: // otherwise start slowing descent/moving upwards
    if (!c)
        goto YMDown;
    compare(a, M(YPlatformCenterYPos + x)); // to slow ascent/move downwards
    a = M(Enemy_Y_Position + x); // if current vertical position < central position, branch

YMDown: // start slowing ascent/moving downwards
    pushReturnIndex(387);
    goto MovePlatformDown;
Return_387:

ChkYPCollision:
    pushReturnIndex(388);
    goto PositionPlayerOnVPlat;
Return_388: // otherwise position player appropriately
    if (n)
        goto ExYPl; // to leave
    a = M(PlatformCollisionFlag + x); // if collision flag not set here, branch

ExYPl: // leave
    goto Return;

//------------------------------------------------------------------------

XMovingPlatform:
    if (n)
        goto ExXMP; // branch ahead to leave
    a = M(PlatformCollisionFlag + x); // if no collision with player,
    pushReturnIndex(389);
    goto MoveWithXMCntrs;
Return_389: // do a sub to move platform accordingly, and return value
    pushReturnIndex(390);
    goto XMoveCntr_Platform;
Return_390: // do a sub to increment counters for movement
    a = 0x0e; // load preset maximum value for secondary counter

PositionPlayerOnHPlat:
    goto SetPVar; // jump to skip subtraction
    a += 0x00; // otherwise add carry to page location
    if (n)
        goto PPHSubt; // if negative, branch to subtract
    y = M(0x00); // check to see if saved value here is positive or negative
    a = M(Player_PageLoc); // get player's page location
    writeData(Player_X_Position, a); // player accordingly in horizontal position
    a += M(0x00); // current player's position to position
    c = 0; // add saved value from second subroutine to
    a = M(Player_X_Position);

PPHSubt: // subtract borrow from page location
    a -= 0x00;

SetPVar: // save result to player's page location
    pushReturnIndex(391);
    goto PositionPlayerOnVPlat;
Return_391: // position player vertically and appropriately
    writeData(Platform_X_Scroll, y); // put saved value from second sub here to be used later
    writeData(Player_PageLoc, a);

ExXMP: // and we are done here
    goto Return;

//------------------------------------------------------------------------

DropPlatform:
    pushReturnIndex(392);
    goto PositionPlayerOnVPlat;
Return_392: // do a sub to position player appropriately
    pushReturnIndex(393);
    goto MoveDropPlatform;
Return_393: // otherwise do a sub to move platform down very quickly
    if (n)
        goto ExDPl; // occurred, just leave without moving anything
    a = M(PlatformCollisionFlag + x); // if no collision between platform and player

ExDPl: // leave
    goto Return;

//------------------------------------------------------------------------

RightPlatform:
    pushReturnIndex(394);
    goto PositionPlayerOnHPlat;
Return_394: // use saved value from earlier sub to position player
    writeData(Enemy_X_Speed + x, a); // otherwise set new speed (gets moving if motionless)
    a = 0x10;
    if (n)
        goto ExRPl; // and platform, branch ahead, leave speed unaltered
    a = M(PlatformCollisionFlag + x); // check collision flag, if no collision between player
    writeData(0x00, a); // store saved value here (residual code)
    pushReturnIndex(395);
    goto MoveEnemyHorizontally;
Return_395: // move platform with current horizontal speed, if any

ExRPl: // then leave
    goto Return;

//------------------------------------------------------------------------

MoveLargeLiftPlat:
    goto ChkYPCollision; // branch to position player correctly
    pushReturnIndex(396);
    goto MoveLiftPlatforms;
Return_396: // execute common to all large and small lift platforms

MoveSmallPlatform:
    goto ChkSmallPlatCollision; // branch to position player correctly
    pushReturnIndex(397);
    goto MoveLiftPlatforms;
Return_397: // execute common to all large and small lift platforms

MoveLiftPlatforms:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_Y_Position + x, a); // and then leave
    a += M(Enemy_Y_Speed + x); // vertical position plus carry to move up or down
    a = M(Enemy_Y_Position + x); // add whatever vertical speed is set to current
    writeData(Enemy_YMF_Dummy + x, a);
    a += M(Enemy_Y_MoveForce + x);
    c = 0; // add contents of movement amount to whatever's here
    a = M(Enemy_YMF_Dummy + x);
    if (!z)
        goto ExLiftP; // and branch to leave
    a = M(TimerControl); // if master timer control set, skip all of this

ChkSmallPlatCollision:
    pushReturnIndex(398);
    goto PositionPlayerOnS_Plat;
Return_398: // use to position player correctly
    if (z)
        goto ExLiftP; // if none found, leave player position alone
    a = M(PlatformCollisionFlag + x); // get bounding box counter saved in collision flag

ExLiftP: // then leave
    goto Return;

//------------------------------------------------------------------------

OffscreenBoundsCheck:
    if (!z)
        goto ExtendLB; // these two will be erased sooner than others if too far left
    compare(y, PiranhaPlant); // check for piranha plant object
    if (z)
        goto LimitB;
    compare(y, HammerBro); // check for hammer bro object
    y = M(Enemy_ID + x);
    a = M(ScreenLeft_X_Pos); // get horizontal coordinate for left side of screen
    if (z)
        goto ExScrnBd;
    compare(a, FlyingCheepCheep); // branch to leave if found
    a = M(Enemy_ID + x); // check for cheep-cheep object

LimitB: // add 56 pixels to coordinate if hammer bro or piranha plant
    a += 0x38;

ExtendLB: // subtract 72 pixels regardless of enemy object
    if (z)
        goto ExScrnBd; // erase all others too far to the right
    compare(y, JumpspringObject); // if jumpspring, do not erase
    if (z)
        goto ExScrnBd;
    compare(y, StarFlagObject); // if star flag, do not erase
    if (z)
        goto ExScrnBd;
    compare(y, FlagpoleFlagObject); // if flagpole flag, do not erase
    if (z)
        goto ExScrnBd;
    compare(y, PiranhaPlant); // if piranha plant, do not erase
    if (z)
        goto ExScrnBd;
    compare(a, HammerBro); // if in state used by spiny's egg, do not erase
    a = M(Enemy_State + x); // if at this point, enemy is offscreen to the right, so check
    if (n)
        goto ExScrnBd; // if enemy object is on the screen, leave, do not erase enemy
    a -= M(0x02); // then subtract it from the page coordinate of the enemy object
    a = M(Enemy_PageLoc + x);
    compare(a, M(0x03)); // to modified horizontal right edge coordinate to get carry
    a = M(Enemy_X_Position + x); // compare horizontal coordinate of the enemy object
    if (n)
        goto TooFar; // if enemy object is too far left, branch to erase it
    a -= M(0x00); // then subtract it from the page coordinate of the enemy object
    a = M(Enemy_PageLoc + x);
    compare(a, M(0x01)); // to modified horizontal left edge coordinate to get carry
    a = M(Enemy_X_Position + x); // compare horizontal coordinate of the enemy object
    writeData(0x02, a); // and store result here
    a += 0x00; // then add the carry to the page location
    a = M(ScreenRight_PageLoc);
    writeData(0x03, a); // store result here
    a += 0x48;
    a = M(ScreenRight_X_Pos); // add 72 pixels to the right side horizontal coordinate
    writeData(0x00, a); // store result here
    a -= 0x00; // subtract borrow from page location of left side
    a = M(ScreenLeft_PageLoc);
    writeData(0x01, a); // store result here
    a -= 0x48;

TooFar: // erase object if necessary
    pushReturnIndex(399);
    goto EraseEnemyObject;
Return_399:

FireballEnemyCollision:
    x = 0x04;
    y = a; // to use fireball's bounding box coordinates 
    a += 0x1c; // then add $1c or 28 bytes to it
    c = 0;
    a <<= 1;
    a <<= 1; // multiply fireball offset by four
    a = x;
    if (c)
        goto ExitFBallEnemy; // branch to leave if set (do routine every other frame)
    a >>= 1; // get LSB of frame counter
    a = M(FrameCounter);
    if (c)
        goto ExitFBallEnemy; // branch to leave also if d7 in state is set
    a <<= 1;
    if (z)
        goto ExitFBallEnemy; // branch to leave if not
    a = M(Fireball_State + x); // check to see if fireball state is set at all

FireballEnemyCDLoop:
    if (!c)
        goto NoFToECol; // if in range $24-$2a, skip to next enemy slot
    compare(a, 0x2b);
    if (!c)
        goto GoombaDie; // if < $24, branch to check further
    compare(a, 0x24);
    a = M(Enemy_ID + x); // check enemy identifier
    if (z)
        goto NoFToECol; // if not, skip to next enemy slot
    a = M(Enemy_Flag + x); // check to see if buffer flag is set
    if (!z)
        goto NoFToECol; // if so, skip to next enemy slot
    a &= BOOST_BINARY(00100000); // check to see if d5 is set in enemy state
    a = M(Enemy_State + x);
    pha(); // push fireball offset to the stack
    a = y;
    writeData(0x01, x); // store enemy object offset here

GoombaDie: // check for goomba identifier
    if (c)
        goto NoFToECol; // skip to next enemy slot
    compare(a, 0x02); // if stomped or otherwise defeated,
    a = M(Enemy_State + x); // otherwise check for defeated state
    if (!z)
        goto NotGoomba; // if not found, continue with code
    compare(a, Goomba);

NotGoomba: // if any masked offscreen bits set,
    pushReturnIndex(400);
    goto HandleEnemyFBallCol;
Return_400: // jump to handle fireball to enemy collision
    x = M(0x01); // get enemy offset
    writeData(Fireball_State + x, a); // set d7 in enemy state
    a = BOOST_BINARY(10000000);
    if (!c)
        goto NoFToECol; // if carry clear, no collision, thus do next enemy slot
    x = M(ObjectOffset); // return fireball's original offset
    pushReturnIndex(401);
    goto SprObjectCollisionCore;
Return_401: // do fireball-to-enemy collision detection
    x = a; // to use enemy's bounding box coordinates
    a += 0x04; // add 4 bytes to it
    c = 0;
    a <<= 1;
    a <<= 1; // otherwise multiply enemy offset by four
    a = x;
    if (!z)
        goto NoFToECol; // skip to next enemy slot
    a = M(EnemyOffscrBitsMasked + x);

NoFToECol: // pull fireball offset from stack
    if (!n)
        goto FireballEnemyCDLoop; // loop back until collision detection done on all enemies
    --x; // decrement it
    x = M(0x01); // get enemy object offset
    y = a; // put it in Y
    pla();

ExitFBallEnemy:
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset); // get original fireball offset and leave

HandleEnemyFBallCol:
    x = M(0x01); // otherwise retrieve current enemy offset
    if (z)
        goto HurtBowser; // branch if found
    compare(a, Bowser); // check enemy identifier for bowser
    a = M(Enemy_ID + x);
    x = a; // use low nybble as enemy offset
    a &= BOOST_BINARY(00001111); // otherwise mask out high nybble and
    if (!n)
        goto ChkBuzzyBeetle; // branch if not set to continue
    a = M(Enemy_Flag + x); // check buffer flag for d7 set
    x = M(0x01); // get current enemy object offset
    pushReturnIndex(402);
    goto RelativeEnemyPosition;
Return_402: // get relative coordinate of enemy

ChkBuzzyBeetle:
    if (!z)
        goto ChkOtherEnemies; // if not found, branch to check other enemies
    compare(a, Bowser); // check for bowser one more time (necessary if d7 of flag was clear)
    if (z)
        goto ExHCF; // branch if found to leave (buzzy beetles fireproof)
    compare(a, BuzzyBeetle); // check for buzzy beetle
    a = M(Enemy_ID + x);

HurtBowser:
    a |= 0x03; // otherwise add 3 to enemy state
    if (c)
        goto SetDBSte; // branch if so
    compare(y, 0x03); // check to see if using offset of 3 or more
    a = 0x20; // set A to use starting value for state
    writeData(Enemy_ID + x, a); // set as new enemy identifier
    a = M(BowserIdentities + y); // get enemy identifier to replace bowser with
    y = M(WorldNumber); // use world number as offset
    writeData(Enemy_Y_Speed + x, a); // set vertical speed to make defeated bowser jump a little
    a = 0xfe;
    writeData(EnemyFrenzyBuffer, a); // init enemy frenzy buffer
    writeData(Enemy_X_Speed + x, a); // initialize horizontal speed
    pushReturnIndex(403);
    goto InitVStf;
Return_403: // otherwise do sub to init vertical speed and movement force
    if (!z)
        goto ExHCF; // if bowser still has hit points, branch to leave
    --M(BowserHitPoints); // decrement bowser's hit points

SetDBSte: // set defeated enemy state
    if (!z)
        goto EnemySmackScore; // unconditional branch to award points
    a = 0x09; // award 5000 points to player for defeating bowser
    x = M(0x01); // get enemy offset
    writeData(Square2SoundQueue, a); // load bowser defeat sound
    a = Sfx_BowserFall;
    writeData(Enemy_State + x, a);

ChkOtherEnemies:
    if (c)
        goto ExHCF; // branch to leave if identifier => $15
    compare(a, 0x15);
    if (z)
        goto ExHCF; // branch to leave if podoboo
    compare(a, Podoboo);
    if (z)
        goto ExHCF; // branch to leave if bullet bill (frenzy variant) 
    compare(a, BulletBill_FrenzyVar);

ShellOrBlockDefeat:
    writeData(Enemy_Y_Position + x, a);
    a += 0x18; // add 24 pixels to enemy object's vertical position
    a = M(Enemy_Y_Position + x);
    if (!z)
        goto StnE; // branch if not found
    compare(a, PiranhaPlant);
    a = M(Enemy_ID + x); // check for piranha plant

StnE: // do yet another sub
    a = 0x06; // award 1000 points for hammer bro
    if (!z)
        goto GoombaPoints; // branch if not found
    compare(y, HammerBro);
    y = M(Enemy_ID + x); // check for hammer bro
    a = 0x02; // award 200 points by default
    writeData(Enemy_State + x, a);
    a |= BOOST_BINARY(00100000); // set d5 to defeat enemy and save as new state
    a &= BOOST_BINARY(00011111); // mask out 2 MSB of enemy object's state
    a = M(Enemy_State + x);
    pushReturnIndex(404);
    goto ChkToStunEnemies;
Return_404:

GoombaPoints:
    a = 0x01; // award 100 points for goomba
    if (!z)
        goto EnemySmackScore; // branch if not found
    compare(y, Goomba); // check for goomba

EnemySmackScore:
    writeData(Square1SoundQueue, a);
    a = Sfx_EnemySmack; // play smack enemy sound
    pushReturnIndex(405);
    goto SetupFloateyNumber;
Return_405: // update necessary score variables

ExHCF: // and now let's leave
    goto Return;

//------------------------------------------------------------------------

PlayerHammerCollision:
    goto InjurePlayer; // otherwise jump to hurt player, do not return
    if (!z)
        goto ExPHC; // branch to leave
    a = M(StarInvincibleTimer); // if star mario invincibility timer set,
    writeData(Misc_X_Speed + x, a); // set to send hammer flying the opposite direction
    a += 0x01;
    c = 0; // hammer's horizontal speed
    a ^= 0xff; // get two's compliment of
    a = M(Misc_X_Speed + x);
    writeData(Misc_Collision_Flag + x, a); // otherwise set collision flag now
    a = 0x01;
    if (!z)
        goto ExPHC; // if collision flag already set, branch to leave
    a = M(Misc_Collision_Flag + x); // otherwise read collision flag
    if (!c)
        goto ClHCol; // if no collision, then branch
    x = M(ObjectOffset); // get misc object offset
    pushReturnIndex(406);
    goto PlayerCollisionCore;
Return_406: // do player-to-hammer collision detection
    y = a; // for misc object bounding box coordinates
    a += 0x24; // add 36 or $24 bytes to get proper offset
    c = 0;
    a <<= 1;
    a <<= 1; // multiply misc object offset by four
    a = x;
    if (!z)
        goto ExPHC; // branch to leave
    a |= M(Misc_OffscreenBits); // or any offscreen bits for hammer are set,
    a = M(TimerControl); // if either master timer control
    if (!c)
        goto ExPHC; // branch to leave if d0 not set to execute every other frame
    a >>= 1; // shift d0 into carry
    a = M(FrameCounter); // get frame counter

ClHCol: // clear collision flag
    writeData(Misc_Collision_Flag + x, a);
    a = 0x00;

ExPHC:
    goto Return;

//------------------------------------------------------------------------

HandlePowerUpCollision:
    goto Return;

//------------------------------------------------------------------------
    writeData(AreaMusicQueue, a);
    a = StarPowerMusic; // into the area music queue, then leave
    writeData(StarInvincibleTimer, a); // timer, and load the star mario music
    a = 0x23; // otherwise set star mario invincibility
    if (z)
        goto SetFor1Up; // if 1-up mushroom, branch
    compare(a, 0x03);
    if (!c)
        goto Shroom_Flower_PUp; // if mushroom or fire flower, branch
    compare(a, 0x02);
    a = M(PowerUpType); // check power-up type
    writeData(Square2SoundQueue, a); // play the power-up sound
    a = Sfx_PowerUpGrab;
    pushReturnIndex(407);
    goto SetupFloateyNumber;
Return_407: // award 1000 points to player by default
    a = 0x06;
    pushReturnIndex(408);
    goto EraseEnemyObject;
Return_408: // erase the power-up object

Shroom_Flower_PUp:
    goto UpToFiery; // jump to set values accordingly
    a = 0x0c; // set value to be used by subroutine tree (fiery)
    x = M(ObjectOffset); // get enemy offset again, and again not necessary
    pushReturnIndex(409);
    goto GetPlayerColors;
Return_409: // run sub to change colors of player
    writeData(PlayerStatus, a);
    a = 0x02; // set player status to fiery
    x = M(ObjectOffset); // get enemy offset, not necessary
    if (!z)
        goto NoPUp;
    compare(a, 0x01); // if player status not super, leave
    if (z)
        goto UpToSuper;
    a = M(PlayerStatus); // if player status = small, branch

SetFor1Up:
    goto Return;

//------------------------------------------------------------------------
    writeData(FloateyNum_Control + x, a); // and then leave
    a = 0x0b; // change 1000 points into 1-up instead

UpToSuper:
    a = 0x09; // set value to be used by subroutine tree (super)
    writeData(PlayerStatus, a);
    a = 0x01; // set player status to super

UpToFiery:
    pushReturnIndex(410);
    goto SetPRout;
Return_410: // set values to stop certain things in motion
    y = 0x00; // set value to be used as new player state

NoPUp:
    goto Return;

//------------------------------------------------------------------------

PlayerEnemyCollision:
    writeData(Enemy_CollisionBits + x, a); // collision bit
    a &= BOOST_BINARY(11111110); // otherwise, clear d0 of current enemy object's
    a = M(Enemy_CollisionBits + x);
    if (c)
        goto CheckForPUpCollision; // if collision, branch past this part here
    x = M(ObjectOffset); // get enemy object buffer offset
    pushReturnIndex(411);
    goto PlayerCollisionCore;
Return_411: // do collision detection on player vs. enemy
    pushReturnIndex(412);
    goto GetEnemyBoundBoxOfs;
Return_412: // get bounding box offset for current enemy object
    if (!z)
        goto NoPECol;
    a &= BOOST_BINARY(00100000); // if enemy state has d5 set, branch to leave
    a = M(Enemy_State + x);
    if (!z)
        goto NoPECol; // on next frame, branch to leave
    compare(a, 0x08); // if not set to run player control routine
    a = M(GameEngineSubroutine);
    if (!z)
        goto NoPECol; // go ahead and branch to leave
    a = M(EnemyOffscrBitsMasked + x); // if current enemy is offscreen by any amount,
    if (c)
        goto NoPECol; // if down past 224th pixel row, branch to leave
    pushReturnIndex(413);
    goto CheckPlayerVertical;
Return_413: // if player object is completely offscreen or
    if (c)
        goto NoPUp; // if set, branch to leave
    a >>= 1;
    a = M(FrameCounter); // check counter for d0 set

NoPECol:
    goto Return;

//------------------------------------------------------------------------

CheckForPUpCollision:
    goto HandlePowerUpCollision; // otherwise, unconditional jump backwards
    if (!z)
        goto EColl; // if not found, branch to next part
    compare(y, PowerUpObject); // check for power-up object
    y = M(Enemy_ID + x);

EColl: // if star mario invincibility timer expired,
    goto ShellOrBlockDefeat; // hit with a shell, or from beneath
    if (z)
        goto HandlePECollisions; // perform task here, otherwise kill enemy like
    a = M(StarInvincibleTimer);

HandlePECollisions:
    a = M(KickedShellPtsData + y); // otherwise, set points based on proximity to timer expiration
    if (c)
        goto KSPts; // data obtained from the stomp counter + 3
    compare(y, 0x03); // if above a certain point, branch using the points
    y = M(EnemyIntervalTimer + x); // check shell enemy's timer
    a += M(StompChainCounter);
    c = 0; // to give points for kicking the shell
    a = 0x03; // add three to whatever the stomp counter contains
    writeData(Enemy_X_Speed + x, a);
    a = M(KickedShellXSpdData + y); // load and set horizontal speed data with offset
    pushReturnIndex(414);
    goto EnemyFacePlayer;
Return_414: // set moving direction and get offset
    writeData(Enemy_State + x, a);
    a |= BOOST_BINARY(10000000);
    a = M(Enemy_State + x); // set d7 in enemy state, thus become moving shell
    writeData(Square1SoundQueue, a);
    a = Sfx_EnemySmack; // play smack enemy sound
    if (z)
        goto ExPEC;
    compare(a, Goomba);
    a = M(Enemy_ID + x); // branch to leave if goomba in defeated state
    if (!c)
        goto ChkForPlayerInjury;
    compare(a, 0x02); // branch if enemy is in normal or falling state
    a &= BOOST_BINARY(00000111);
    a = M(Enemy_State + x); // mask out all but 3 LSB of enemy state
    if (c)
        goto ChkForPlayerInjury;
    a <<= 1;
    a = M(Enemy_State + x); // branch if d7 of enemy state was set
    if (z)
        goto InjurePlayer;
    a = M(AreaType); // branch if water type level
    if (c)
        goto InjurePlayer;
    compare(y, 0x15); // branch if object => $15
    if (z)
        goto ChkForPlayerInjury;
    compare(y, BulletBill_CannonVar); // branch if bullet bill
    if (z)
        goto InjurePlayer;
    compare(y, Podoboo); // branch if podoboo
    if (z)
        goto InjurePlayer;
    compare(y, PiranhaPlant); // branch if piranha plant
    if (z)
        goto ChkForPlayerInjury;
    compare(y, Spiny); // branch if spiny
    writeData(Enemy_CollisionBits + x, a);
    a |= M(Enemy_CollisionBits + x); // otherwise set d0 now
    a = 0x01;
    if (!z)
        goto ExPEC; // branch to leave if either is true
    a |= M(EnemyOffscrBitsMasked + x);
    a &= BOOST_BINARY(00000001); // or for being offscreen at all
    a = M(Enemy_CollisionBits + x); // check enemy collision bits for d0 set

KSPts: // set values for floatey number now
    pushReturnIndex(415);
    goto SetupFloateyNumber;
Return_415:

ExPEC: // leave!!!
    goto Return;

//------------------------------------------------------------------------

ChkForPlayerInjury:
    if (!z)
        goto EnemyStomped; // or not at all, and branch elsewhere if moving downwards
    if (n)
        goto ChkInj; // perform procedure below if player moving upwards
    a = M(Player_Y_Speed); // check player's vertical speed

ChkInj: // branch if enemy object < $07
    if (!c)
        goto EnemyStomped; // branch if this player's position above (less than) enemy's
    compare(a, M(Enemy_Y_Position + x)); // compare modified player's position to enemy's position
    a += 0x0c;
    c = 0;
    a = M(Player_Y_Position); // add 12 pixels to player's vertical position
    if (!c)
        goto ChkETmrs;
    compare(a, Bloober);
    a = M(Enemy_ID + x);

ChkETmrs: // check stomp timer
    goto ChkEnemyFaceRight; // otherwise do a jump here
    if (!c)
        goto TInjE; // relative position, branch here
    compare(a, M(Enemy_Rel_XPos)); // if player's relative position to the left of enemy's
    a = M(Player_Rel_XPos);
    if (!z)
        goto ExInjColRoutines; // counting down, and branch elsewhere to leave if so
    a = M(InjuryTimer); // check to see if injured invincibility timer still
    if (!z)
        goto EnemyStomped; // branch if set
    a = M(StompTimer);

TInjE: // if enemy moving towards the left,
    goto LInj;
    if (!z)
        goto InjurePlayer; // to turn the enemy around
    compare(a, 0x01); // branch, otherwise do a jump here
    a = M(Enemy_MovingDir + x);

InjurePlayer:
    if (!z)
        goto ExInjColRoutines; // at zero, and branch to leave if so
    a = M(InjuryTimer); // check again to see if injured invincibility timer is

ForceInjury:
    a = 0x0a; // set subroutine to run on next frame
    pushReturnIndex(416);
    goto GetPlayerColors;
Return_416: // change player's palette if necessary
    writeData(Square1SoundQueue, a); // play pipedown/injury sound
    a <<= 1;
    writeData(InjuryTimer, a); // set injured invincibility timer
    a = 0x08;
    writeData(PlayerStatus, a); // otherwise set player's status to small
    if (z)
        goto KillPlayer; // branch if small
    x = M(PlayerStatus); // check player's status

SetKRout: // set new player state
    y = 0x01;

SetPRout: // load new value to run subroutine on next frame
    writeData(ScrollAmount, y); // initialize scroll speed
    ++y;
    writeData(TimerControl, y); // set master timer control flag to halt timers
    y = 0xff;
    writeData(Player_State, y); // store new player state
    writeData(GameEngineSubroutine, a);

ExInjColRoutines:
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset); // get enemy offset and leave

KillPlayer:
    if (!z)
        goto SetKRout; // branch to set player's state and other things
    a = 0x0b; // set subroutine to run on next frame
    writeData(Player_Y_Speed, a); // set new vertical speed
    a = 0xfc;
    writeData(EventMusicQueue, x); // set event music queue to death music
    ++x;
    writeData(Player_X_Speed, x); // halt player's horizontal movement by initializing speed

EnemyStomped:
    if (!z)
        goto ChkForDemoteKoopa;
    compare(a, Bloober); // branch if NOT bloober
    ++y; // increment points data offset
    if (z)
        goto EnemyStompedPts;
    compare(a, Lakitu); // branch for lakitu
    ++y; // increment points data offset
    if (z)
        goto EnemyStompedPts;
    compare(a, HammerBro); // branch for hammer bro
    ++y; // increment points data offset
    if (z)
        goto EnemyStompedPts; // for cpu to take due to earlier checking of podoboo)
    compare(a, Podoboo); // branch for podoboo (this branch is logically impossible
    if (z)
        goto EnemyStompedPts;
    compare(a, BulletBill_CannonVar);
    if (z)
        goto EnemyStompedPts;
    compare(a, BulletBill_FrenzyVar); // branch for either bullet bill object
    if (z)
        goto EnemyStompedPts;
    compare(a, FlyingCheepCheep); // branch for cheep-cheep
    y = 0x00; // initialize points data offset for stomped enemies
    a = M(Enemy_ID + x);
    writeData(Square1SoundQueue, a);
    a = Sfx_EnemyStomp; // otherwise play stomp/swim sound
    if (z)
        goto InjurePlayer;
    compare(a, Spiny); // if found
    a = M(Enemy_ID + x); // check for spiny, branch to hurt player

EnemyStompedPts:
    goto Return;

//------------------------------------------------------------------------
    writeData(Player_Y_Speed, a);
    a = 0xfd; // set player's vertical speed, to give bounce
    writeData(Enemy_X_Speed + x, a); // and horizontal speed
    pushReturnIndex(417);
    goto InitVStf;
Return_417: // nullify vertical speed, physics-related thing,
    writeData(Enemy_State + x, a); // set d5 in enemy state
    a = BOOST_BINARY(00100000);
    writeData(Enemy_MovingDir + x, a); // return enemy movement direction from stack
    pla();
    pushReturnIndex(418);
    goto SetStun;
Return_418: // run sub to kill enemy
    pha(); // save enemy movement direction to stack
    a = M(Enemy_MovingDir + x);
    pushReturnIndex(419);
    goto SetupFloateyNumber;
Return_419: // run sub to set floatey number controls
    a = M(StompedEnemyPtsData + y); // load points data using offset in Y

ChkForDemoteKoopa:
    goto SBnce; // then move onto something else
    writeData(Enemy_X_Speed + x, a); // set appropriate moving speed based on direction
    a = M(DemotedKoopaXSpdData + y);
    pushReturnIndex(420);
    goto EnemyFacePlayer;
Return_420: // turn enemy around if necessary
    pushReturnIndex(421);
    goto InitVStf;
Return_421: // nullify physics-related thing and vertical speed
    pushReturnIndex(422);
    goto SetupFloateyNumber;
Return_422:
    a = 0x03; // award 400 points to the player
    writeData(Enemy_State + x, y);
    y = 0x00; // return enemy to normal state
    writeData(Enemy_ID + x, a);
    a &= BOOST_BINARY(00000001); // demote koopa paratroopas to ordinary troopas
    if (!c)
        goto HandleStompedShellE;
    compare(a, 0x09); // branch elsewhere if enemy object < $09

HandleStompedShellE:
    writeData(EnemyIntervalTimer + x, a); // set as enemy timer to revive stomped enemy
    a = M(RevivalRateData + y); // load timer setting according to flag
    y = M(PrimaryHardMode); // check primary hard mode flag
    ++M(StompTimer); // increment stomp timer of some sort
    pushReturnIndex(423);
    goto SetupFloateyNumber;
Return_423: // award points accordingly
    a += M(StompTimer);
    c = 0; // to whatever is in the stomp timer
    a = M(StompChainCounter); // add whatever is in the stomp counter
    ++M(StompChainCounter); // increment the stomp counter
    writeData(Enemy_State + x, a);
    a = 0x04; // set defeated state for enemy

SBnce: // set player's vertical speed for bounce
    goto Return;

//------------------------------------------------------------------------
    writeData(Player_Y_Speed, a); // and then leave!!!
    a = 0xfc;

ChkEnemyFaceRight:
    goto InjurePlayer; // otherwise go back to hurt player
    if (!z)
        goto LInj; // if not, branch
    compare(a, 0x01);
    a = M(Enemy_MovingDir + x); // check to see if enemy is moving to the right

LInj: // turn the enemy around, if necessary
    goto InjurePlayer; // go back to hurt player
    pushReturnIndex(424);
    goto EnemyTurnAround;
Return_424:

EnemyFacePlayer:
    ++y; // otherwise, increment to set to move to the left
    if (!n)
        goto SFcRt; // if enemy is to the right of player, do not increment
    pushReturnIndex(425);
    goto PlayerEnemyDiff;
Return_425: // get horizontal difference between player and enemy
    y = 0x01; // set to move right by default

SFcRt: // set moving direction here
    goto Return;

//------------------------------------------------------------------------
    --y; // then decrement to use as a proper offset
    writeData(Enemy_MovingDir + x, y);

SetupFloateyNumber:
    writeData(FloateyNum_X_Pos + x, a); // set horizontal coordinate and leave
    a = M(Enemy_Rel_XPos);
    writeData(FloateyNum_Y_Pos + x, a); // set vertical coordinate
    a = M(Enemy_Y_Position + x);
    writeData(FloateyNum_Timer + x, a); // set timer for floatey numbers
    a = 0x30;
    writeData(FloateyNum_Control + x, a); // set number of points control for floatey numbers

ExSFN:
    goto Return;

//------------------------------------------------------------------------

EnemiesCollision:
    if (n)
        goto ExitECRoutine; // branch to leave if there are no other enemies
    --x; // first enemy we're going to compare, then decrement for second
    pushReturnIndex(426);
    goto GetEnemyBoundBoxOfs;
Return_426: // otherwise, do sub, get appropriate bounding box offset for
    if (!z)
        goto ExitECRoutine;
    a = M(EnemyOffscrBitsMasked + x); // if masked offscreen bits nonzero, branch to leave
    if (z)
        goto ExitECRoutine;
    compare(a, PiranhaPlant); // if piranha plant, branch to leave
    if (z)
        goto ExitECRoutine;
    compare(a, Lakitu); // if lakitu, branch to leave
    if (c)
        goto ExitECRoutine;
    compare(a, 0x15); // if enemy object => $15, branch to leave
    a = M(Enemy_ID + x);
    if (z)
        goto ExSFN; // if water area type, leave
    a = M(AreaType);
    if (!c)
        goto ExSFN; // if d0 not set, leave
    a >>= 1;
    a = M(FrameCounter); // check counter for d0 set

ECLoop: // save enemy object buffer offset for second enemy here
    writeData(Enemy_CollisionBits + y, a);
    a |= M(SetBitsMask + x); // if the bit is not set, set it now
    a = M(Enemy_CollisionBits + y);
    if (!z)
        goto ReadyNextEnemy; // already set, and move onto next enemy slot if set
    a &= M(SetBitsMask + x); // check to see if bit connected to second enemy is
    a = M(Enemy_CollisionBits + y); // load first enemy's collision-related bits
    if (!z)
        goto YesEC; // branch if at least one of them is set
    a &= BOOST_BINARY(10000000);
    a |= M(Enemy_State + y); // check both enemy states for d7 set
    a = M(Enemy_State + x);
    if (!c)
        goto NoEnemyCollision; // if carry clear, no collision, branch ahead of this
    y = M(0x01); // use second enemy offset for Y
    x = M(ObjectOffset); // use first enemy offset for X
    pushReturnIndex(427);
    goto SprObjectCollisionCore;
Return_427: // do collision detection using the two enemies here
    x = a; // use as new contents of X
    a += 0x04;
    c = 0;
    a <<= 1;
    a <<= 1; // multiply by four, then add four
    a = x; // get second enemy object's bounding box offset
    if (!z)
        goto ReadyNextEnemy; // branch if masked offscreen bits set
    a = M(EnemyOffscrBitsMasked + x);
    if (z)
        goto ReadyNextEnemy; // branch if enemy object is piranha plant
    compare(a, PiranhaPlant);
    if (z)
        goto ReadyNextEnemy; // branch if enemy object is lakitu
    compare(a, Lakitu);
    if (c)
        goto ReadyNextEnemy; // branch if true
    compare(a, 0x15); // check for enemy object => $15
    a = M(Enemy_ID + x);
    if (z)
        goto ReadyNextEnemy; // branch if flag not set
    a = M(Enemy_Flag + x); // check enemy object enable flag
    pha();
    a = y; // save first enemy's bounding box offset to stack
    writeData(0x01, x);

YesEC: // react according to the nature of collision
    goto ReadyNextEnemy; // move onto next enemy slot
    pushReturnIndex(428);
    goto ProcEnemyCollisions;
Return_428:

NoEnemyCollision:
    writeData(Enemy_CollisionBits + y, a); // then move onto next enemy slot
    a &= M(ClearBitsMask + x); // clear bit connected to second enemy
    a = M(Enemy_CollisionBits + y); // load first enemy's collision-related bits

ReadyNextEnemy:
    if (!n)
        goto ECLoop; // loop until all enemy slots have been checked
    --x;
    x = M(0x01); // get and decrement second enemy's object buffer offset
    y = a; // use as Y again
    pla(); // get first enemy's bounding box offset from the stack

ExitECRoutine:
    goto Return; // leave

//------------------------------------------------------------------------
    x = M(ObjectOffset); // get enemy object buffer offset

ProcEnemyCollisions:
    y = M(0x01); // original offset of second enemy
    pushReturnIndex(429);
    goto ShellOrBlockDefeat;
Return_429: // then kill enemy, then load
    pushReturnIndex(430);
    goto SetupFloateyNumber;
Return_430: // award 1000 points for killing enemy
    a = 0x06;
    if (!c)
        goto ShellCollisions; // branch if d7 is clear
    a <<= 1;
    a = M(Enemy_State + y); // check first enemy state for d7 set
    if (z)
        goto ExitProcessEColl;
    compare(a, HammerBro); // if hammer bro found in alt state, branch to leave
    a = M(Enemy_ID + x); // check second enemy identifier for hammer bro
    if (!c)
        goto ProcSecondEnemyColl;
    compare(a, 0x06); // if second enemy state < $06, branch elsewhere
    a = M(Enemy_State + x);
    if (!z)
        goto ExitProcessEColl; // to leave and do nothing else at this point
    a &= BOOST_BINARY(00100000); // if d5 is set in either state, or both, branch
    a |= M(Enemy_State + x);
    a = M(Enemy_State + y); // check both enemy states for d5 set

ShellCollisions:
    ++M(ShellChainCounter + x); // increment chain counter for additional enemies
    x = M(ObjectOffset); // load original offset of first enemy
    pushReturnIndex(431);
    goto SetupFloateyNumber;
Return_431: // award appropriate number of points for second enemy
    x = M(0x01);
    a += 0x04; // add four to get appropriate point offset
    c = 0;
    a = M(ShellChainCounter + x); // get chain counter for shell
    x = M(ObjectOffset);
    pushReturnIndex(432);
    goto ShellOrBlockDefeat;
Return_432: // kill second enemy
    x = a;
    a = y; // move Y to X

ExitProcessEColl:
    goto Return; // leave!!!

//------------------------------------------------------------------------

ProcSecondEnemyColl:
    goto Return; // leave!!!

//------------------------------------------------------------------------
    ++M(ShellChainCounter + x); // increment chain counter for additional enemies
    x = M(0x01); // load original offset of second enemy
    pushReturnIndex(433);
    goto SetupFloateyNumber;
Return_433: // award appropriate number of points for first enemy
    x = M(ObjectOffset);
    a += 0x04; // add four to get appropriate point offset
    c = 0;
    a = M(ShellChainCounter + y); // get chain counter for shell
    y = M(0x01);
    pushReturnIndex(434);
    goto ShellOrBlockDefeat;
Return_434: // otherwise, kill first enemy
    if (z)
        goto ExitProcessEColl;
    compare(a, HammerBro); // if hammer bro found in alt state, branch to leave
    a = M(Enemy_ID + y); // check first enemy identifier for hammer bro
    if (!c)
        goto MoveEOfs;
    compare(a, 0x06);
    a = M(Enemy_State + y); // if first enemy state < $06, branch elsewhere

MoveEOfs:
    x = M(ObjectOffset); // then do it again using value from $08
    pushReturnIndex(435);
    goto EnemyTurnAround;
Return_435: // do the sub here using value from $01
    x = a;
    a = y; // move Y ($01) to X

EnemyTurnAround:
    if (c)
        goto ExTA; // if any OTHER enemy object => $07, leave
    compare(a, 0x07);
    if (z)
        goto RXSpd; // if green paratroopa, turn it around
    compare(a, GreenParatroopaJump);
    if (z)
        goto RXSpd; // if spiny, turn it around
    compare(a, Spiny);
    if (z)
        goto ExTA; // if hammer bro, leave
    compare(a, HammerBro);
    if (z)
        goto ExTA; // if lakitu, leave
    compare(a, Lakitu);
    if (z)
        goto ExTA; // if piranha plant, leave
    compare(a, PiranhaPlant);
    a = M(Enemy_ID + x); // check for specific enemies

RXSpd: // load horizontal speed
    writeData(Enemy_MovingDir + x, a); // thus effectively turning the enemy around
    a ^= BOOST_BINARY(00000011); // invert moving direction and store, then leave
    a = M(Enemy_MovingDir + x);
    writeData(Enemy_X_Speed + x, y); // store as new horizontal speed
    ++y;
    y = a;
    a ^= 0xff; // get two's compliment for horizontal speed
    a = M(Enemy_X_Speed + x);

ExTA: // leave!!!
    goto Return;

//------------------------------------------------------------------------

LargePlatformCollision:
    pushReturnIndex(436);
    goto ChkForPlayerC_LargeP;
Return_436: // perform code with state offset, then original offset, in X
    x = a; // set state as enemy offset here
    a = M(Enemy_State + x);
    if (!z)
        goto ChkForPlayerC_LargeP; // balance platform, branch if not found
    compare(a, 0x24); // check enemy object identifier for
    a = M(Enemy_ID + x);
    if (n)
        goto ExLPC; // branch to leave
    a = M(Enemy_State + x); // if d7 set in object state,
    if (!z)
        goto ExLPC; // if set, branch to leave
    a = M(TimerControl); // check master timer control
    writeData(PlatformCollisionFlag + x, a);
    a = 0xff; // save value here

ChkForPlayerC_LargeP:
    pushReturnIndex(437);
    goto ProcLPlatCollisions;
Return_437: // otherwise collision, perform sub
    if (!c)
        goto ExLPC; // if no collision, branch to leave
    x = a;
    pla(); // retrieve offset from the stack
    pushReturnIndex(438);
    goto PlayerCollisionCore;
Return_438: // do player-to-platform collision detection
    pha();
    a = x; // send offset we're on to the stack
    writeData(0x00, a); // temp variable for now
    a = M(Enemy_Y_Position + x); // store vertical coordinate in
    pushReturnIndex(439);
    goto GetEnemyBoundBoxOfsArg;
Return_439: // get bounding box offset in Y
    a = x;
    if (c)
        goto ExLPC; // or offscreen, branch to leave if true
    pushReturnIndex(440);
    goto CheckPlayerVertical;
Return_440: // figure out if player is below a certain point

ExLPC: // get enemy object buffer offset and leave
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

SmallPlatformCollision:
    writeData(0x00, a); // load counter here for 2 bounding boxes
    a = 0x02;
    if (c)
        goto ExSPC; // or entirely offscreen, and branch to leave if true
    pushReturnIndex(441);
    goto CheckPlayerVertical;
Return_441: // do a sub to see if player is below a certain point
    writeData(PlatformCollisionFlag + x, a); // otherwise initialize collision flag
    if (!z)
        goto ExSPC; // branch to leave
    a = M(TimerControl); // if master timer control set,

ChkSmallPlatLoop:
    if (c)
        goto ProcSPlatCollisions; // skip ahead if collision
    pushReturnIndex(442);
    goto PlayerCollisionCore;
Return_442: // otherwise, perform player-to-platform collision detection
    if (!c)
        goto MoveBoundBox; // if so, branch, don't do collision detection
    compare(a, 0x20); // above a specific point
    a = M(BoundingBox_UL_YPos + y); // check top of platform's bounding box for being
    if (!z)
        goto ExSPC; // then branch to leave
    a &= BOOST_BINARY(00000010); // if d1 of offscreen lower nybble bits was set
    pushReturnIndex(443);
    goto GetEnemyBoundBoxOfs;
Return_443: // get bounding box offset in Y
    x = M(ObjectOffset); // get enemy object offset

MoveBoundBox:
    if (!z)
        goto ChkSmallPlatLoop; // loop back until both bounding boxes are checked
    --M(0x00); // decrement counter we set earlier
    writeData(BoundingBox_DR_YPos + y, a);
    a += 0x80;
    c = 0;
    a = M(BoundingBox_DR_YPos + y);
    writeData(BoundingBox_UL_YPos + y, a);
    a += 0x80;
    c = 0; // 128 pixels downwards
    a = M(BoundingBox_UL_YPos + y); // move bounding box vertical coordinates

ExSPC: // get enemy object buffer offset, then leave
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

ProcSPlatCollisions:
    x = M(ObjectOffset); // return enemy object buffer offset to X, then continue

ProcLPlatCollisions:
    writeData(Player_Y_Speed, a); // speed of player to kill jump
    a = 0x01; // otherwise, set vertical
    if (!n)
        goto ChkForTopCollision; // if so, don't mess with it
    a = M(Player_Y_Speed); // check to see if player's vertical speed is moving down
    if (c)
        goto ChkForTopCollision; // branch, do not alter vertical speed of player
    compare(a, 0x04); // if difference too large or negative,
    a -= M(BoundingBox_UL_YPos); // of the platform's bounding box
    c = 1; // of the player's bounding box from the bottom
    a = M(BoundingBox_DR_YPos + y); // get difference by subtracting the top

ChkForTopCollision:
    a = x; // otherwise use enemy object buffer offset
    if (z)
        goto SetCollisionFlag;
    compare(y, 0x2c); // as contents of collision flag
    if (z)
        goto SetCollisionFlag; // regardless of which one, branch to use bounding box counter
    compare(y, 0x2b); // if either of the two small platform objects are found,
    y = M(Enemy_ID + x);
    a = M(0x00); // get saved bounding box counter from earlier
    if (n)
        goto PlatformSideCollisions; // if player's vertical speed moving upwards, skip this
    a = M(Player_Y_Speed);
    if (c)
        goto PlatformSideCollisions; // if difference not close enough, skip all of this
    compare(a, 0x06);
    a -= M(BoundingBox_UL_YPos + y); // of the player's bounding box
    c = 1; // of the platform's bounding box from the bottom
    a = M(BoundingBox_DR_YPos); // get difference by subtracting the top

SetCollisionFlag:
    goto Return;

//------------------------------------------------------------------------
    writeData(Player_State, a); // set player state to normal then leave
    a = 0x00;
    writeData(PlatformCollisionFlag + x, a); // save either bounding box counter or enemy offset here
    x = M(ObjectOffset); // get enemy object buffer offset

PlatformSideCollisions:
    if (c)
        goto NoSideC; // and instead branch to leave (no collision)
    compare(a, 0x09); // if difference not close enough, skip subroutine
    a -= M(BoundingBox_UL_XPos);
    c = 0; // from platform's right edge
    a = M(BoundingBox_DR_XPos + y); // get difference by subtracting player's left edge
    ++M(0x00); // otherwise increment value set here for right side collision
    if (!c)
        goto SideC;
    compare(a, 0x08); // if difference close enough, skip all of this
    a -= M(BoundingBox_UL_XPos + y);
    c = 1; // from player's right edge
    a = M(BoundingBox_DR_XPos); // get difference by subtracting platform's left edge
    writeData(0x00, a); // collision on left side of platform
    a = 0x01; // set value here to indicate possible horizontal

SideC: // deal with horizontal collision
    pushReturnIndex(444);
    goto ImpedePlayerMove;
Return_444:

NoSideC: // return with enemy object buffer offset
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

PositionPlayerOnS_Plat:
    goto Skip_8;
    a += M(PlayerPosSPlatData - 1 + y); // coordinate
Skip_8:
    c = 0; // add positioning data using offset to the vertical
    a = M(Enemy_Y_Position + x); // for offset
    y = a; // use bounding box counter saved in collision flag

PositionPlayerOnVPlat:
    writeData(Player_Y_MoveForce, a); // and then leave
    writeData(Player_Y_Speed, a); // initialize vertical speed and low byte of force
    a = 0x00;
    writeData(Player_Y_HighPos, a); // new vertical high byte
    a -= 0x00; // subtract borrow and store as player's
    a = y;
    writeData(Player_Y_Position, a); // save as player's new vertical coordinate
    a -= 0x20; // for the player object's height
    c = 1; // subtract 32 pixels from vertical coordinate
    if (!z)
        goto ExPlPos;
    compare(y, 0x01); // if vertical high byte offscreen, skip this
    y = M(Enemy_Y_HighPos + x);
    if (z)
        goto ExPlPos; // skip all of this
    compare(y, 0x0b); // if certain routine being executed on this frame,
    y = M(GameEngineSubroutine);
    a = M(Enemy_Y_Position + x); // get vertical coordinate

ExPlPos:
    goto Return;

//------------------------------------------------------------------------

CheckPlayerVertical:
    compare(a, 0xd0); // the player is vertically
    a = M(Player_Y_Position); // if on the screen, check to see how far down
    if (!z)
        goto ExCPV;
    --y; // within the screen, leave this routine
    y = M(Player_Y_HighPos); // if player high vertical byte is not
    if (c)
        goto ExCPV;
    compare(a, 0xf0); // vertically, leave this routine
    a = M(Player_OffscreenBits); // if player object is completely offscreen

ExCPV:
    goto Return;

//------------------------------------------------------------------------

GetEnemyBoundBoxOfs:
    a = M(ObjectOffset); // get enemy object buffer offset

GetEnemyBoundBoxOfsArg:
    goto Return;

//------------------------------------------------------------------------
    compare(a, BOOST_BINARY(00001111)); // check for all bits set
    a &= BOOST_BINARY(00001111); // save low nybble
    a = M(Enemy_OffscreenBits); // get offscreen bits for enemy object
    y = a; // send to Y
    a += 0x04;
    c = 0;
    a <<= 1; // to skip player's bounding box
    a <<= 1; // multiply A by four, then add four

PlayerBGCollision:
    if (!z)
        goto ChkOnScr; // if in any other state besides climbing, skip to next part
    compare(a, 0x03);
    if (z)
        goto SetFallS; // branch to set default state for falling
    a = M(Player_State); // if player in normal state,
    if (!z)
        goto SetPSte; // branch ahead to set default state
    y = M(SwimmingFlag); // if swimming flag set,
    a = 0x01; // load default player state for swimming
    if (!c)
        goto ExPBGCol; // if running routines $00-$03 branch to leave
    compare(a, 0x04);
    if (z)
        goto ExPBGCol; // branch to leave
    compare(a, 0x0b); // if running routine #11 or $0b
    a = M(GameEngineSubroutine);
    if (!z)
        goto ExPBGCol; // branch to leave
    a = M(DisableCollisionDet); // if collision detection disabled flag set,

SetFallS: // load default player state for falling
    a = 0x02;

SetPSte: // set whatever player state is appropriate
    writeData(Player_State, a);

ChkOnScr:
    if (!c)
        goto ChkCollSize; // if not too close to the bottom of screen, continue
    compare(a, 0xcf); // check player's vertical coordinate
    a = M(Player_Y_Position);
    writeData(Player_CollisionBits, a); // initialize player's collision flag
    a = 0xff;
    if (!z)
        goto ExPBGCol; // branch to leave if not
    compare(a, 0x01); // check player's vertical high byte for still on the screen
    a = M(Player_Y_HighPos);

ExPBGCol: // otherwise leave
    goto Return;

//------------------------------------------------------------------------

ChkCollSize:
    --y; // otherwise decrement offset
    if (!z)
        goto GBBAdr; // if swimming flag set, skip ahead
    a = M(SwimmingFlag);
    --y; // otherwise decrement offset for big player not crouching
    if (!z)
        goto GBBAdr; // if player small, skip ahead
    a = M(PlayerSize);
    if (!z)
        goto GBBAdr; // if player crouching, skip ahead
    a = M(CrouchingFlag);
    y = 0x02; // load default offset

GBBAdr: // get value using offset
    ++x; // otherwise increment size as offset
    if (z)
        goto HeadChk; // if player not crouching, branch ahead
    a = M(CrouchingFlag);
    x = M(PlayerSize); // get player's size as offset
    y = a; // put value into Y, as offset for block buffer routine
    writeData(0xeb, a); // store value here
    a = M(BlockBufferAdderData + y);

HeadChk: // get player's vertical coordinate
    goto DoFootCheck; // jump ahead to skip these other parts here
    pushReturnIndex(445);
    goto PlayerHeadCollision;
Return_445: // otherwise do a sub to process collision
    if (!z)
        goto NYSpd; // branch ahead, do not process collision
    y = M(BlockBounceTimer); // if block bounce timer not expired,
    if (z)
        goto NYSpd; // if water level, branch ahead
    y = M(AreaType); // otherwise check area type
    if (c)
        goto SolidOrClimb; // if player collided with solid metatile, branch
    pushReturnIndex(446);
    goto CheckForSolidMTiles;
Return_446: // check to see what player's head bumped on
    if (!c)
        goto DoFootCheck; // if low nybble < 4, branch
    compare(y, 0x04); // from collision detection routine
    y = M(0x04); // check lower nybble of vertical coordinate returned
    if (!n)
        goto DoFootCheck; // if player not moving upwards, branch elsewhere
    y = M(Player_Y_Speed); // check player's vertical speed
    if (c)
        goto AwardTouchedCoin; // if so, branch to some other part of code
    pushReturnIndex(447);
    goto CheckForCoinMTiles;
Return_447: // check to see if player touched coin with their head
    if (z)
        goto DoFootCheck; // player, and branch if nothing above player's head
    pushReturnIndex(448);
    goto BlockBufferColli_Head;
Return_448: // do player-to-bg collision detection on top of
    if (!c)
        goto DoFootCheck; // if player is too high, skip this part
    compare(a, M(PlayerBGUpperExtent + x)); // compare with upper extent value based on offset
    a = M(Player_Y_Position);

SolidOrClimb:
    writeData(Square1SoundQueue, a); // otherwise load bump sound
    a = Sfx_Bump;
    if (z)
        goto NYSpd; // branch ahead and do not play sound
    compare(a, 0x26); // if climbing metatile,

NYSpd: // set player's vertical speed to nullify
    writeData(Player_Y_Speed, a); // jump or swim
    a = 0x01;

DoFootCheck:
    if (!c)
        goto ChkFootMTile; // if not, skip unconditional jump and continue code
    pushReturnIndex(449);
    goto CheckForCoinMTiles;
Return_449: // check to see if player touched coin with their right foot
    if (z)
        goto DoPlayerSideCheck; // and skip ahead if not
    a = M(0x00); // otherwise check for anything in bottom right metatile
    if (!z)
        goto ChkFootMTile; // if anything here, skip this part
    writeData(0x01, a); // pull bottom left metatile and save here
    pla();
    writeData(0x00, a); // save bottom right metatile here
    pushReturnIndex(450);
    goto BlockBufferColli_Feet;
Return_450: // do player-to-bg collision detection on bottom right of player
    pha(); // save bottom left metatile to stack
    if (c)
        goto AwardTouchedCoin; // if so, branch to some other part of code
    pushReturnIndex(451);
    goto CheckForCoinMTiles;
Return_451: // check to see if player touched coin with their left foot
    pushReturnIndex(452);
    goto BlockBufferColli_Feet;
Return_452: // do player-to-bg collision detection on bottom left of player
    if (c)
        goto DoPlayerSideCheck; // if player is too far down on screen, skip all of this
    compare(a, 0xcf); // check to see how low player is
    a = M(Player_Y_Position);
    y = M(0xeb); // get block buffer adder offset

AwardTouchedCoin:
    goto HandleCoinMetatile; // follow the code to erase coin and award to player 1 coin

ChkFootMTile:
    goto HandleAxeMetatile; // otherwise jump to set modes of operation
    if (!z)
        goto ContChk; // if player did not touch axe, skip ahead
    compare(a, 0xc5);
    if (n)
        goto DoPlayerSideCheck; // if player moving upwards, branch
    y = M(Player_Y_Speed); // check player's vertical speed
    if (c)
        goto DoPlayerSideCheck; // if so, branch
    pushReturnIndex(453);
    goto CheckForClimbMTiles;
Return_453: // check to see if player landed on climbable metatiles

ContChk: // do sub to check for hidden coin or 1-up blocks
    goto ImpedePlayerMove; // jump to impede player's movement in that direction
    writeData(0x00, a); // use player's moving direction as temp variable
    a = M(Player_MovingDir);
    if (!c)
        goto LandPlyr; // if lower nybble < 5, branch
    compare(y, 0x05); // from collision detection routine
    y = M(0x04); // check lower nybble of vertical coordinate returned
    if (!z)
        goto InitSteP; // branch ahead
    y = M(JumpspringAnimCtrl); // if jumpspring animating right now,
    if (z)
        goto DoPlayerSideCheck; // if either found, branch
    pushReturnIndex(454);
    goto ChkInvisibleMTiles;
Return_454:

LandPlyr: // do sub to check for jumpspring metatiles and deal with it
    writeData(StompChainCounter, a); // initialize enemy stomp counter
    writeData(Player_Y_MoveForce, a); // movement force to stop player's vertical movement
    writeData(Player_Y_Speed, a); // initialize vertical speed and fractional
    a = 0x00;
    pushReturnIndex(455);
    goto HandlePipeEntry;
Return_455: // do sub to process potential pipe entry
    writeData(Player_Y_Position, a); // and store as new vertical position to land player properly
    a &= M(Player_Y_Position); // mask out lower nybble of player's vertical position
    a = 0xf0;
    pushReturnIndex(456);
    goto ChkForLandJumpSpring;
Return_456:

InitSteP:
    writeData(Player_State, a); // set player's state to normal
    a = 0x00;

DoPlayerSideCheck:
    writeData(0x00, a);
    a = 0x02; // set value here to be used as counter
    ++y; // increment offset 2 bytes to use adders for side collisions
    ++y;
    y = M(0xeb); // get block buffer adder offset

SideCheckLoop:
    if (!c)
        goto CheckSideMTiles; // if not, branch to alternate section of code
    pushReturnIndex(457);
    goto CheckForClimbMTiles;
Return_457: // do sub to see if player bumped into anything climbable
    if (z)
        goto BHalf; // if collided with water pipe (top), branch ahead
    compare(a, 0x6b);
    if (z)
        goto BHalf; // if collided with sideways pipe (top), branch ahead
    compare(a, 0x1c); // otherwise check for pipe metatiles
    if (z)
        goto BHalf; // branch ahead if nothing found
    pushReturnIndex(458);
    goto BlockBufferColli_Side;
Return_458: // do player-to-bg collision detection on one half of player
    if (c)
        goto ExSCH; // branch to leave if player is too far down
    compare(a, 0xe4);
    if (!c)
        goto BHalf; // if player is in status bar area, branch ahead to skip this part
    compare(a, 0x20); // check player's vertical position
    a = M(Player_Y_Position);
    writeData(0xeb, y); // store it
    ++y; // move onto the next one

BHalf: // load block adder offset
    if (!z)
        goto SideCheckLoop; // run code until both sides of player are checked
    --M(0x00); // otherwise decrement counter
    if (!z)
        goto CheckSideMTiles; // if something found, branch
    pushReturnIndex(459);
    goto BlockBufferColli_Side;
Return_459: // do player-to-bg collision detection on other half of player
    if (c)
        goto ExSCH; // if too low, branch to leave
    compare(a, 0xd0);
    if (!c)
        goto ExSCH; // if too high, branch to leave
    compare(a, 0x08);
    a = M(Player_Y_Position); // get player's vertical position
    ++y; // increment it
    y = M(0xeb);

ExSCH: // leave
    goto Return;

//------------------------------------------------------------------------

CheckSideMTiles:
    goto HandleClimbing; // otherwise jump to handle climbing
    if (!c)
        goto ContSChk; // if not found, skip and continue with code
    pushReturnIndex(460);
    goto CheckForClimbMTiles;
Return_460: // check for climbable metatiles
    if (z)
        goto ExCSM; // branch to leave if either found
    pushReturnIndex(461);
    goto ChkInvisibleMTiles;
Return_461: // check for hidden or coin 1-up blocks

ContSChk: // check to see if player touched coin
    goto StopPlayerMove; // otherwise jump to impede player's movement
    if (!z)
        goto ExCSM; // branch to leave if set
    a = M(JumpspringAnimCtrl); // otherwise check jumpspring animation control
    if (!c)
        goto ChkPBtm; // if not found, branch ahead to continue cude
    pushReturnIndex(462);
    goto ChkJumpspringMetatiles;
Return_462: // check for jumpspring metatiles
    if (c)
        goto HandleCoinMetatile; // if so, execute code to erase coin and award to player 1 coin
    pushReturnIndex(463);
    goto CheckForCoinMTiles;
Return_463:

ChkPBtm: // get player's state
    if (!z)
        goto StopPlayerMove; // otherwise branch to impede player's movement
    compare(a, 0x1f); // if collided with water pipe (bottom), continue
    if (z)
        goto PipeDwnS; // if collided with sideways pipe (bottom), branch
    compare(a, 0x6c); // otherwise check for pipe metatiles
    if (!z)
        goto StopPlayerMove; // if facing left, branch to impede movement
    --y;
    y = M(PlayerFacingDir); // get player's facing direction
    if (!z)
        goto StopPlayerMove; // if not, branch to impede player's movement
    compare(y, 0x00); // check for player's state set to normal
    y = M(Player_State);

PipeDwnS: // check player's attributes
    writeData(Square1SoundQueue, y); // otherwise load pipedown/injury sound
    y = Sfx_PipeDown_Injury;
    if (!z)
        goto PlyrPipe; // if already set, branch, do not play sound again
    a = M(Player_SprAttrib);

PlyrPipe:
    ++y; // otherwise increment offset
    if (z)
        goto SetCATmr; // if at page zero, use default offset
    a = M(ScreenLeft_PageLoc); // load page location for left side of screen
    y = 0x00; // set default offset for timer setting data
    if (z)
        goto ChkGERtn; // if at zero, branch ahead to skip this part
    a &= BOOST_BINARY(00001111); // get lower nybble of player's horizontal coordinate
    a = M(Player_X_Position);
    writeData(Player_SprAttrib, a); // set background priority bit in player attributes
    a |= BOOST_BINARY(00100000);

SetCATmr: // set timer for change of area as appropriate
    writeData(ChangeAreaTimer, a);
    a = M(AreaChangeTimerData + y);

ChkGERtn: // get number of game engine routine running
    goto Return; // and leave

//------------------------------------------------------------------------
    writeData(GameEngineSubroutine, a); // otherwise set sideways pipe entry routine to run
    a = 0x02;
    if (!z)
        goto ExCSM;
    compare(a, 0x08); // player control routine, go ahead and branch to leave
    if (z)
        goto ExCSM; // if running player entrance routine or
    compare(a, 0x07);
    a = M(GameEngineSubroutine);

StopPlayerMove:
    pushReturnIndex(464);
    goto ImpedePlayerMove;
Return_464: // stop player's movement

ExCSM: // leave
    goto Return;

//------------------------------------------------------------------------

HandleCoinMetatile:
    goto GiveOneCoin; // update coin amount and tally on the screen
    ++M(CoinTallyFor1Ups); // increment coin tally used for 1-up blocks
    pushReturnIndex(465);
    goto ErACM;
Return_465: // do sub to erase coin metatile from block buffer

HandleAxeMetatile:
    writeData(Player_X_Speed, a); // set horizontal speed and continue to erase axe metatile
    a = 0x18;
    writeData(OperMode, a); // set primary mode to autoctrl mode
    a = 0x02;
    writeData(OperMode_Task, a); // reset secondary mode
    a = 0x00;

ErACM: // load vertical high nybble offset for block buffer
    goto RemoveCoin_Axe; // update the screen accordingly
    writeData(W(0x06) + y, a); // store to remove old contents from block buffer
    a = 0x00; // load blank metatile
    y = M(0x02);

HandleClimbing:
    if (!c)
        goto ChkForFlagpole;
    compare(y, 0x0a); // than 16 pixels
    if (!c)
        goto ExHC; // makes actual physical part of vine or flagpole thinner
    compare(y, 0x06); // collision detection routine against certain values, this
    y = M(0x04); // check low nybble of horizontal coordinate returned from

ExHC: // leave if too far left or too far right
    goto Return;

//------------------------------------------------------------------------

ChkForFlagpole:
    if (!z)
        goto VineCollision; // branch to alternate code if flagpole shaft not found
    compare(a, 0x25);
    if (z)
        goto FlagpoleCollision; // branch if flagpole ball found
    compare(a, 0x24); // check climbing metatiles

FlagpoleCollision:
    writeData(FlagpoleCollisionYPos, a); // store player's vertical coordinate here to be used later
    a = M(Player_Y_Position);
    x = 0x04; // start at end of vertical coordinate data
    writeData(FlagpoleSoundQueue, a); // load flagpole sound into flagpole sound queue
    a >>= 1;
    writeData(EventMusicQueue, a); // silence music
    a = Silence;
    pushReturnIndex(466);
    goto KillEnemies;
Return_466: // get rid of them
    a = BulletBill_CannonVar; // load identifier for bullet bills (cannon variant)
    if (z)
        goto RunFR; // if running, branch to end of flagpole code here
    compare(a, 0x04); // check for flagpole slide routine running
    a = M(GameEngineSubroutine);
    ++M(ScrollLock); // set scroll lock flag
    writeData(PlayerFacingDir, a); // set player's facing direction to right
    a = 0x01;
    if (z)
        goto PutPlayerOnVine; // if running, branch to end of climbing code
    compare(a, 0x05); // check for end-of-level routine running
    a = M(GameEngineSubroutine);

ChkFlagpoleYPosLoop:
    if (!z)
        goto ChkFlagpoleYPosLoop; // do this until all data is checked (use last one if all checked)
    --x; // otherwise decrement offset to use 
    if (c)
        goto MtchF; // if player's => current, branch to use current offset
    compare(a, M(FlagpoleYPosData + x)); // compare with current vertical coordinate data

MtchF: // store offset here to be used later
    writeData(FlagpoleScore, x);

RunFR:
    goto PutPlayerOnVine; // jump to end of climbing code
    writeData(GameEngineSubroutine, a); // set value to run flagpole slide routine
    a = 0x04;

VineCollision:
    writeData(GameEngineSubroutine, a); // otherwise set to run autoclimb routine next frame
    a = 0x01;
    if (c)
        goto PutPlayerOnVine; // branch if not that far up
    compare(a, 0x20); // for being in status bar area
    a = M(Player_Y_Position); // check player's vertical coordinate
    if (!z)
        goto PutPlayerOnVine;
    compare(a, 0x26); // check for climbing metatile used on vines

PutPlayerOnVine:
    writeData(PlayerFacingDir, a); // otherwise force player to face left
    a = 0x02;
    if (c)
        goto SetVXPl; // if 16 or more pixels difference, do not alter facing direction
    compare(a, 0x10);
    a -= M(ScreenLeft_X_Pos); // subtract from left side horizontal coordinate
    c = 1;
    a = M(Player_X_Position); // get player's horizontal coordinate
    writeData(Player_X_MoveForce, a);
    writeData(Player_X_Speed, a); // and fractional horizontal movement force
    a = 0x00; // nullify player's horizontal speed
    writeData(Player_State, a);
    a = 0x03; // set player state to climbing

SetVXPl: // get current facing direction, use as offset
    writeData(Player_PageLoc, a); // store as player's page location
    a += M(ClimbPLocAdder - 1 + y); // add depending on facing location
    c = 0;
    a = M(ScreenRight_PageLoc); // load page location of right side of screen
    if (!z)
        goto ExPVne; // if not zero, branch
    a = M(0x06); // get low byte of block buffer address again
    writeData(Player_X_Position, a); // store as player's horizontal coordinate
    a += M(ClimbXPosAdder - 1 + y); // add pixels depending on facing direction
    c = 0;
    a <<= 1;
    a <<= 1;
    a <<= 1; // move low nybble to high
    a <<= 1;
    a = M(0x06); // get low byte of block buffer address
    y = M(PlayerFacingDir);

ExPVne: // finally, we're done!
    goto Return;

//------------------------------------------------------------------------

ChkInvisibleMTiles:
    compare(a, 0x60); // check for hidden 1-up block
    if (z)
        goto ExCInvT; // branch to leave if found
    compare(a, 0x5f); // check for hidden coin block

ExCInvT: // leave with zero flag set if either found
    goto Return;

//------------------------------------------------------------------------

ChkForLandJumpSpring:
    writeData(JumpspringAnimCtrl, a); // set jumpspring animation control to start animating
    a >>= 1;
    writeData(JumpspringTimer, a); // set jumpspring timer to be used later
    a = 0x03;
    writeData(JumpspringForce, a); // set default jumpspring force
    a = 0xf9;
    writeData(VerticalForce, a); // otherwise set vertical movement force for player
    a = 0x70;
    if (!c)
        goto ExCJSp; // if carry not set, jumpspring not found, therefore leave
    pushReturnIndex(467);
    goto ChkJumpspringMetatiles;
Return_467: // do sub to check if player landed on jumpspring

ExCJSp: // and leave
    goto Return;

//------------------------------------------------------------------------

ChkJumpspringMetatiles:
    if (!z)
        goto NoJSFnd; // branch to use cleared carry if not found
    c = 0; // clear carry flag
    compare(a, 0x68); // check for bottom jumpspring metatile
    if (z)
        goto JSFnd; // branch to set carry if found
    compare(a, 0x67); // check for top jumpspring metatile

JSFnd: // set carry if found
    c = 1;

NoJSFnd: // leave
    goto Return;

//------------------------------------------------------------------------

HandlePipeEntry:
    ++x; // otherwise increment for last pipe
    if (!c)
        goto GetWNum; // if player at middle, but not too far right, use offset and skip
    compare(a, 0xa0);
    ++x; // otherwise increment for middle pipe
    if (!c)
        goto GetWNum; // if player at left, not near middle, use offset and skip ahead
    compare(a, 0x60);
    a = M(Player_X_Position); // get player's horizontal position
    x = a; // save as offset to warp zone numbers (starts at left pipe)
    a <<= 1; // multiply by four
    a <<= 1;
    a &= BOOST_BINARY(00000011); // mask out all but 2 LSB
    if (z)
        goto ExPipeE; // branch to leave if none found
    a = M(WarpZoneControl); // check warp zone control
    writeData(Player_SprAttrib, a); // set background priority bit in player's attributes
    a = BOOST_BINARY(00100000);
    writeData(Square1SoundQueue, a); // load pipedown/injury sound
    a = Sfx_PipeDown_Injury;
    writeData(GameEngineSubroutine, a); // set to run vertical pipe entry routine on next frame
    a = 0x03;
    writeData(ChangeAreaTimer, a); // set timer for change of area
    a = 0x30;
    if (!z)
        goto ExPipeE; // branch to leave if not found
    compare(a, 0x10); // check left foot metatile for warp pipe left metatile
    a = M(0x01);
    if (!z)
        goto ExPipeE; // branch to leave if not found
    compare(a, 0x11); // check right foot metatile for warp pipe right metatile
    a = M(0x00);
    if (z)
        goto ExPipeE; // if not pressing down, branch to leave
    a &= BOOST_BINARY(00000100); // for pressing down
    a = M(Up_Down_Buttons); // check saved controller bits from earlier

GetWNum: // get warp zone numbers
    ++M(FetchNewGameTimerFlag); // set flag to load new game timer
    ++M(Hidden1UpFlag); // set flag for hidden 1-up blocks
    writeData(AltEntranceControl, a); // initialize mode of entry
    writeData(LevelNumber, a); // initialize level number used for world display
    writeData(AreaNumber, a); // initialize area number used for area address offset
    writeData(EntrancePage, a); // initialize starting page number
    a = 0x00;
    writeData(EventMusicQueue, a); // silence music
    a = Silence;
    writeData(AreaPointer, a); // store area offset here to be used to change areas
    a = M(AreaAddrOffsets + x); // get area offset based on world offset
    x = M(WorldAddrOffsets + y); // get offset to where this world's area offsets are
    writeData(WorldNumber, y); // store as world number and offset
    --y; // decrement for use as world number
    y = M(WarpZoneNumbers + x);

ExPipeE: // leave!!!
    goto Return;

//------------------------------------------------------------------------

ImpedePlayerMove:
    goto NXSpd; // and jump to affect movement
    a = 0xff; // otherwise load A with value to be used later
    if (n)
        goto ExIPM; // branch to invert bit and leave
    compare(y, 0x00); // if player moving to the left,
    ++x; // return value to X
    if (!z)
        goto RImpd; // if right side collision, skip this part
    --x; // left side collision
    x = M(0x00); // check value set earlier for
    y = M(Player_X_Speed); // get player's horizontal speed
    a = 0x00; // initialize value here

RImpd: // return $02 to X
    a = 0x01; // otherwise load A with value to be used here
    if (!n)
        goto ExIPM; // branch to invert bit and leave
    compare(y, 0x01); // if player moving to the right,
    x = 0x02;

NXSpd:
    --y; // otherwise decrement Y now
    if (!n)
        goto PlatF; // branch ahead, do not decrement Y
    compare(a, 0x00); // if value set in A not set to $ff,
    writeData(Player_X_Speed, y); // nullify player's horizontal speed
    y = 0x00;
    writeData(SideCollisionTimer, y); // set timer of some sort
    y = 0x10;

PlatF: // store Y as high bits of horizontal adder
    writeData(Player_PageLoc, a); // page location if necessary
    a += M(0x00); // add high bits and carry to
    a = M(Player_PageLoc);
    writeData(Player_X_Position, a); // position to move player left or right
    a += M(Player_X_Position); // add contents of A to player's horizontal
    c = 0;
    writeData(0x00, y);

ExIPM: // invert contents of X
    goto Return;

//------------------------------------------------------------------------
    writeData(Player_CollisionBits, a); // store to clear bit
    a &= M(Player_CollisionBits); // mask out bit that was set here
    a ^= 0xff;
    a = x;

CheckForSolidMTiles:
    goto Return;

//------------------------------------------------------------------------
    compare(a, M(SolidMTileUpperExt + x)); // compare current metatile with solid metatiles
    pushReturnIndex(468);
    goto GetMTileAttrib;
Return_468: // find appropriate offset based on metatile's 2 MSB

CheckForClimbMTiles:
    goto Return;

//------------------------------------------------------------------------
    compare(a, M(ClimbMTileUpperExt + x)); // compare current metatile with climbable metatiles
    pushReturnIndex(469);
    goto GetMTileAttrib;
Return_469: // find appropriate offset based on metatile's 2 MSB

CheckForCoinMTiles:
    goto Return;

//------------------------------------------------------------------------
    c = 0; // otherwise clear carry and leave
    if (z)
        goto CoinSd; // branch if found
    compare(a, 0xc3); // check for underwater coin
    if (z)
        goto CoinSd; // branch if found
    compare(a, 0xc2); // check for regular coin

CoinSd:
    goto Return;

//------------------------------------------------------------------------
    writeData(Square2SoundQueue, a); // load coin grab sound and leave
    a = Sfx_CoinGrab;

GetMTileAttrib:
    a = y; // get original metatile value back
    x = a; // use as offset for metatile data
    a.rol();
    a.rol(); // shift and rotate d7-d6 to d1-d0
    a <<= 1;
    a &= BOOST_BINARY(11000000); // mask out all but 2 MSB
    y = a; // save metatile value into Y

ExEBG: // leave
    goto Return;

//------------------------------------------------------------------------

EnemyToBGCollisionDet:
    if (!c)
        goto ExEBG;
    compare(a, 0x25); // if enemy vertical coordinate < 36 branch to leave
    a = M(Enemy_Y_Position + x);
    if (!z)
        goto DoIDCheckBGColl;
    compare(y, Spiny); // if enemy object is not spiny, branch elsewhere
    y = M(Enemy_ID + x);
    if (!c)
        goto ExEBG; // if enemy vertical coord + 62 < 68, branch to leave
    pushReturnIndex(470);
    goto SubtEnemyYPos;
Return_470: // otherwise, do a subroutine here
    if (!z)
        goto ExEBG; // if set, branch to leave
    a &= BOOST_BINARY(00100000);
    a = M(Enemy_State + x); // check enemy state for d6 set

DoIDCheckBGColl:
    goto EnemyJump; // otherwise jump elsewhere
    if (!z)
        goto HBChk; // branch if not found
    compare(y, GreenParatroopaJump); // check for some other enemy object

HBChk: // check for hammer bro
    goto HammerBroBGColl; // otherwise jump elsewhere
    if (!z)
        goto CInvu; // branch if not found
    compare(y, HammerBro);

CInvu: // if enemy object is spiny, branch
    if (c)
        goto ExEBGChk;
    compare(y, 0x07); // if enemy object =>$07, branch to leave
    if (z)
        goto YesIn;
    compare(y, PowerUpObject); // if special power-up object, branch
    if (z)
        goto YesIn;
    compare(y, Spiny);

YesIn: // if enemy object < $07, or = $12 or $2e, do this sub
    if (!z)
        goto HandleEToBGCollision; // if block underneath enemy, branch
    pushReturnIndex(471);
    goto ChkUnderEnemy;
Return_471:

NoEToBGCollision:
    goto ChkForRedKoopa; // otherwise skip and do something else

HandleEToBGCollision:
    pushReturnIndex(472);
    goto KillEnemyAboveBlock;
Return_472: // if enemy object IS goomba, do this sub
    if (!z)
        goto GiveOEPoints;
    compare(a, Goomba); // if enemy object not goomba, branch ahead of this routine
    if (c)
        goto ChkToStunEnemies;
    compare(a, 0x15); // if enemy object => $15, branch ahead
    a = M(Enemy_ID + x);
    writeData(W(0x06) + y, a); // trigger this routine accidentally again
    a = 0x00; // store default blank metatile in that spot so we won't
    y = M(0x02); // get vertical coordinate used to find block
    if (!z)
        goto LandEnemyProperly; // check for blank metatile $23 and branch if not found
    compare(a, 0x23);
    if (z)
        goto NoEToBGCollision; // if blank $26, coins, or hidden blocks, jump, enemy falls through
    pushReturnIndex(473);
    goto ChkForNonSolids;
Return_473: // if something is underneath enemy, find out what

GiveOEPoints:
    pushReturnIndex(474);
    goto SetupFloateyNumber;
Return_474:
    a = 0x01; // award 100 points for hitting block beneath enemy

ChkToStunEnemies:
    if (!c)
        goto SetStun; // are only necessary if branching from $d7a1
    compare(a, PiranhaPlant); // coordinate from previous addition, also these comparisons
    if (!c)
        goto Demote; // always fail this test because A will still have vertical
    compare(a, 0x0a); // modified if not any of those values, note that piranha plant will
    if (c)
        goto SetStun; // $09, $0e, $0f or $10, it will be modified, and not
    compare(a, 0x11); // if the enemy object identifier is equal to the values
    if (!c)
        goto SetStun;
    compare(a, 0x09); // perform many comparisons on enemy object identifier

Demote: // erase all but LSB, essentially turning enemy object
    writeData(Enemy_ID + x, a); // into green or red koopa troopa to demote them
    a &= BOOST_BINARY(00000001);

SetStun: // load enemy state
    if (!z)
        goto SetNotW; // if area type not water, set as speed, otherwise
    y = M(AreaType);
    a = 0xfd; // set default vertical speed
    if (z)
        goto SetWYSpd;
    compare(a, Bloober); // check for bloober object
    a = M(Enemy_ID + x);
    --M(Enemy_Y_Position + x); // subtract two pixels from enemy's vertical position
    --M(Enemy_Y_Position + x);
    writeData(Enemy_State + x, a); // set d1 of enemy state
    a |= BOOST_BINARY(00000010);
    a &= BOOST_BINARY(11110000); // save high nybble
    a = M(Enemy_State + x);

SetWYSpd: // change the vertical speed
    a = 0xff;

SetNotW: // set vertical speed now
    ++y; // increment Y if not
    if (!n)
        goto ChkBBill; // branch if enemy is to the right of player
    pushReturnIndex(475);
    goto PlayerEnemyDiff;
Return_475: // get horizontal difference between player and enemy object
    y = 0x01;
    writeData(Enemy_Y_Speed + x, a);

ChkBBill:
    writeData(Enemy_MovingDir + x, y); // store as moving direction
    if (z)
        goto NoCDirF; // branch if either found, direction does not change
    compare(a, BulletBill_FrenzyVar); // check for bullet bill (frenzy variant)
    if (z)
        goto NoCDirF;
    compare(a, BulletBill_CannonVar); // check for bullet bill (cannon variant)
    a = M(Enemy_ID + x);

NoCDirF: // decrement and use as offset
    writeData(Enemy_X_Speed + x, a); // and store, then leave
    a = M(EnemyBGCXSpdData + y); // get proper horizontal speed
    --y;

ExEBGChk:
    goto Return;

//------------------------------------------------------------------------

LandEnemyProperly:
    if (!c)
        goto ChkLandedEnemyState;
    a <<= 1; // branch if d7 in enemy state is not set
    a = M(Enemy_State + x);
    if (!z)
        goto LandEnemyInitState;
    a &= BOOST_BINARY(01000000); // branch if d6 in enemy state is set
    a = M(Enemy_State + x);
    if (c)
        goto ChkForRedKoopa; // branch if lower nybble in range of $0d-$0f before subtract
    compare(a, 0x05); // used to determine whether enemy landed from falling
    a -= 0x08; // subtract eight pixels
    c = 1;
    a = M(0x04); // check lower nybble of vertical coordinate saved earlier

SChkA: // if lower nybble < $0d, d7 set but d6 not set, jump here
    goto DoEnemySideCheck;

ChkLandedEnemyState:
    a = 0x00; // set timer for $00 if spiny
    if (!z)
        goto SetForStn; // branch if not found
    compare(y, Spiny);
    y = M(Enemy_ID + x); // check enemy identifier for spiny
    a = 0x10; // load default timer here
    if (!z)
        goto ProcEnemyDirection; // then branch elsewhere
    compare(a, 0x02); // if not in $02 state (used by koopas and buzzy beetles)
    a = M(Enemy_State + x); // load enemy state again (why?)
    if (c)
        goto ExSteChk; // or in higher numbered state, branch to leave
    compare(a, 0x03); // if already in state used by koopas and buzzy beetles
    if (z)
        goto ProcEnemyDirection; // then branch elsewhere
    compare(a, 0x05); // if in state used by spiny's egg
    if (z)
        goto SChkA;
    a = M(Enemy_State + x); // if enemy in normal state, branch back to jump here

SetForStn: // set timer here
    pushReturnIndex(476);
    goto EnemyLanding;
Return_476: // then land it properly
    writeData(Enemy_State + x, a); // upside-down koopas and buzzy beetles
    a = 0x03; // set state here, apparently used to render
    writeData(EnemyIntervalTimer + x, a);

ExSteChk: // then leave
    goto Return;

//------------------------------------------------------------------------

ProcEnemyDirection:
    if (z)
        goto LandEnemyInitState; // trying to face the player
    a &= BOOST_BINARY(00000111); // if timed appropriately, spiny will skip over
    a = M(FrameCounter);
    writeData(Enemy_X_Speed + x, a); // set horizontal speed accordingly
    a = 0x08;
    writeData(Enemy_MovingDir + x, a); // send enemy moving to the right by default
    a = 0x01;
    if (!z)
        goto InvtD; // branch if not found
    compare(a, Spiny); // check for spiny
    if (z)
        goto LandEnemyInitState;
    compare(a, Goomba); // branch if found
    a = M(Enemy_ID + x); // check enemy identifier for goomba

InvtD: // load 1 for enemy to face the left (inverted here)
    ++y; // if to the left, increment by one for enemy to face right (inverted)
    if (!n)
        goto CNwCDir; // if enemy to the right of player, branch
    pushReturnIndex(477);
    goto PlayerEnemyDiff;
Return_477: // get horizontal difference between player and enemy
    y = 0x01;

CNwCDir:
    pushReturnIndex(478);
    goto ChkForBump_HammerBroJ;
Return_478: // if equal, not facing in correct dir, do sub to turn around
    if (!z)
        goto LandEnemyInitState;
    compare(a, M(Enemy_MovingDir + x)); // compare direction in A with current direction in memory
    a = y;

LandEnemyInitState:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_State + x, a); // note this will also turn spiny's egg into spiny
    a = 0x00; // otherwise initialize enemy state and leave
    if (!z)
        goto NMovShellFallBit;
    a &= BOOST_BINARY(10000000); // if d7 of enemy state is set, branch
    a = M(Enemy_State + x);
    pushReturnIndex(479);
    goto EnemyLanding;
Return_479: // land enemy properly

NMovShellFallBit:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_State + x, a);
    a &= BOOST_BINARY(10111111); // and store, then leave
    a = M(Enemy_State + x); // nullify d6 of enemy state, save other bits

ChkForRedKoopa:
    if (z)
        goto ChkForBump_HammerBroJ; // if enemy found and in normal state, branch
    a = M(Enemy_State + x);
    if (!z)
        goto Chk2MSBSt; // branch if not found
    compare(a, RedKoopa);
    a = M(Enemy_ID + x); // check for red koopa troopa $03

Chk2MSBSt: // save enemy state into Y
    goto SetD6Ste; // jump ahead of this part
    a |= BOOST_BINARY(01000000); // set d6
    a = M(Enemy_State + x);
    if (!c)
        goto GetSteFromD; // branch if not set
    a <<= 1; // check for d7 set
    y = a;
    a = M(Enemy_State + x);

GetSteFromD: // load new enemy state with old as offset
    a = M(EnemyBGCStateData + y);

SetD6Ste: // set as new state
    writeData(Enemy_State + x, a);

DoEnemySideCheck:
    writeData(0xeb, a); // OAM data offset
    a = 0x02; // set value here in what is also used as
    y = 0x16; // start by finding block to the left of enemy ($00,$14)
    if (!c)
        goto ExESdeC;
    compare(a, 0x20); // because there's nothing there that impedes movement
    a = M(Enemy_Y_Position + x); // if enemy within status bar, branch to leave

SdeCLoop: // check value
    if (!z)
        goto ChkForBump_HammerBroJ; // branch if not found
    pushReturnIndex(480);
    goto ChkForNonSolids;
Return_480: // check for non-solid blocks
    if (z)
        goto NextSdeC; // if nothing found, branch
    pushReturnIndex(481);
    goto BlockBufferChk_Enemy;
Return_481: // find block to left or right of enemy object
    a = 0x01; // set flag in A for save horizontal coordinate 
    if (!z)
        goto NextSdeC; // branch if different and do not seek block there
    compare(a, M(Enemy_MovingDir + x)); // compare value against moving direction
    a = M(0xeb);

NextSdeC: // move to the next direction
    if (!c)
        goto SdeCLoop; // enemy ($00, $14) and ($10, $14) pixel coordinates
    compare(y, 0x18); // increment Y, loop only if Y < $18, thus we check
    ++y;
    --M(0xeb);

ExESdeC:
    goto Return;

//------------------------------------------------------------------------

ChkForBump_HammerBroJ:
    writeData(Square1SoundQueue, a); // sound will never be played if branching from ChkForRedKoopa
    a = Sfx_Bump; // otherwise, play bump sound
    if (!c)
        goto NoBump;
    a <<= 1; // ahead and do not play sound
    a = M(Enemy_State + x); // if enemy state d7 not set, branch
    if (z)
        goto NoBump; // and if so, branch ahead and do not play sound
    compare(x, 0x05); // check if we're on the special use slot

NoBump: // check for hammer bro
    goto SetHJ; // jump to code that makes hammer bro jump
    y = 0xfa; // load default vertical speed for jumping
    writeData(0x00, a); // initialize value here for bitmask  
    a = 0x00;
    if (!z)
        goto InvEnemyDir; // branch if not found
    compare(a, 0x05);
    a = M(Enemy_ID + x);

InvEnemyDir:
    goto RXSpd; // jump to turn the enemy around

PlayerEnemyDiff:
    goto Return;

//------------------------------------------------------------------------
    a -= M(Player_PageLoc); // subtract borrow, then leave
    a = M(Enemy_PageLoc + x);
    writeData(0x00, a); // and store here
    a -= M(Player_X_Position); // horizontal coordinate
    c = 1; // horizontal coordinate and the player's
    a = M(Enemy_X_Position + x); // get distance between enemy object's

EnemyLanding:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_Y_Position + x, a); // neatly on whatever it's landing on
    a |= BOOST_BINARY(00001000); // set d3, then store, probably used to set enemy object
    a &= BOOST_BINARY(11110000); // save high nybble of vertical coordinate, and
    a = M(Enemy_Y_Position + x);
    pushReturnIndex(482);
    goto InitVStf;
Return_482: // do something here to vertical speed and something else

SubtEnemyYPos:
    goto Return; // and leave with flags set for conditional branch

//------------------------------------------------------------------------
    compare(a, 0x44); // compare against a certain range
    a += 0x3e;
    c = 0; // vertical coordinate
    a = M(Enemy_Y_Position + x); // add 62 pixels to enemy object's

EnemyJump:
    writeData(Enemy_Y_Speed + x, a); // make the paratroopa jump again
    a = 0xfd;
    pushReturnIndex(483);
    goto EnemyLanding;
Return_483: // change vertical coordinate and speed
    if (z)
        goto DoSide; // branch if found
    pushReturnIndex(484);
    goto ChkForNonSolids;
Return_484: // check for non-solid blocks
    if (z)
        goto DoSide; // standing on anything, then branch to same place if not
    pushReturnIndex(485);
    goto ChkUnderEnemy;
Return_485: // otherwise, check to see if green paratroopa is 
    if (!c)
        goto DoSide;
    compare(a, 0x03); // if green paratroopa not falling, branch ahead
    a += 0x02;
    c = 0; // add two to vertical speed
    a = M(Enemy_Y_Speed + x);
    if (!c)
        goto DoSide; // if enemy vertical coord + 62 < 68, branch to leave
    pushReturnIndex(486);
    goto SubtEnemyYPos;
Return_486: // do a sub here

DoSide: // check for horizontal blockage, then leave
    goto DoEnemySideCheck;

HammerBroBGColl:
    if (!z)
        goto UnderHammerBro;
    compare(a, 0x23); // check for blank metatile $23 and branch if not found
    if (z)
        goto NoUnderHammerBro;
    pushReturnIndex(487);
    goto ChkUnderEnemy;
Return_487: // check to see if hammer bro is standing on anything

KillEnemyAboveBlock:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_Y_Speed + x, a);
    a = 0xfc; // alter vertical speed of enemy and leave
    pushReturnIndex(488);
    goto ShellOrBlockDefeat;
Return_488: // do this sub to kill enemy

UnderHammerBro:
    goto DoEnemySideCheck; // then check for horizontal blockage and leave
    pushReturnIndex(489);
    goto EnemyLanding;
Return_489: // modify vertical coordinate, speed and something else
    writeData(Enemy_State + x, a); // and store
    a &= BOOST_BINARY(10001000); // save d7 and d3 from enemy state, nullify other bits
    a = M(Enemy_State + x);
    if (!z)
        goto NoUnderHammerBro; // branch if not expired
    a = M(EnemyFrameTimer + x); // check timer used by hammer bro

NoUnderHammerBro:
    goto Return;

//------------------------------------------------------------------------
    writeData(Enemy_State + x, a);
    a |= 0x01; // in the enemy state to indicate jumping or falling, then leave
    a = M(Enemy_State + x); // if hammer bro is not standing on anything, set d0

ChkUnderEnemy:
    goto BlockBufferChk_Enemy; // hop to it!
    y = 0x15; // set Y to check the bottom middle (8,18) of enemy object
    a = 0x00; // set flag in A for save vertical coordinate

ChkForNonSolids:
    compare(a, 0x60); // hidden 1-up block?
    if (z)
        goto NSFnd;
    compare(a, 0x5f); // hidden coin block?
    if (z)
        goto NSFnd;
    compare(a, 0xc3); // underwater coin?
    if (z)
        goto NSFnd;
    compare(a, 0xc2); // regular coin?
    if (z)
        goto NSFnd;
    compare(a, 0x26); // blank metatile used for vines?

NSFnd:
    goto Return;

//------------------------------------------------------------------------

FireballBGCollision:
    goto Return; // leave

//------------------------------------------------------------------------
    writeData(Fireball_Y_Position + x, a); // store as new vertical coordinate
    a &= 0xf8; // modify vertical coordinate to land it properly
    a = M(Fireball_Y_Position + x);
    writeData(FireballBouncingFlag + x, a); // set bouncing flag
    a = 0x01;
    writeData(Fireball_Y_Speed + x, a); // otherwise set vertical speed to move upwards (give it bounce)
    a = 0xfd;
    if (!z)
        goto InitFireballExplode; // branch to set exploding bit in fireball's state
    a = M(FireballBouncingFlag + x); // if bouncing flag already set,
    if (n)
        goto InitFireballExplode; // branch to set exploding bit in fireball's state
    a = M(Fireball_Y_Speed + x); // if fireball's vertical speed set to move upwards,
    if (z)
        goto ClearBounceFlag; // branch if any found
    pushReturnIndex(490);
    goto ChkForNonSolids;
Return_490: // check for non-solid metatiles
    if (z)
        goto ClearBounceFlag; // if nothing underneath fireball, branch
    pushReturnIndex(491);
    goto BlockBufferChk_FBall;
Return_491: // do fireball to background collision detection on bottom of it
    if (!c)
        goto ClearBounceFlag; // if within the status bar area of the screen, branch ahead
    compare(a, 0x18);
    a = M(Fireball_Y_Position + x); // check fireball's vertical coordinate

ClearBounceFlag:
    goto Return; // leave

//------------------------------------------------------------------------
    writeData(FireballBouncingFlag + x, a); // clear bouncing flag by default
    a = 0x00;

InitFireballExplode:
    goto Return; // leave

//------------------------------------------------------------------------
    writeData(Square1SoundQueue, a); // load bump sound
    a = Sfx_Bump;
    writeData(Fireball_State + x, a); // set exploding flag in fireball's state
    a = 0x80;

GetFireballBoundBox:
    if (!z)
        goto FBallB; // unconditional branch
    y = 0x02; // set offset for relative coordinates
    x = a;
    a += 0x07;
    c = 0; // to use in routines as offset for fireball
    a = x; // add seven bytes to offset

GetMiscBoundBox:
    y = 0x06; // set offset for relative coordinates
    x = a;
    a += 0x09;
    c = 0; // to use in routines as offset for misc object
    a = x; // add nine bytes to offset

FBallB: // get bounding box coordinates
    goto CheckRightScreenBBox; // jump to handle any offscreen coordinates
    pushReturnIndex(492);
    goto BoundingBoxCore;
Return_492:

GetEnemyBoundBox:
    goto GetMaskedOffScrBits;
    y = 0x44; // store another bitmask here for now and jump
    writeData(0x00, y);
    y = 0x48; // store bitmask here for now

SmallPlatformBoundBox:
    y = 0x04; // store another bitmask here for now
    writeData(0x00, y);
    y = 0x08; // store bitmask here for now

GetMaskedOffScrBits:
    y = M(0x00); // if to the right of left edge, use value in $00 for A
    if (z)
        goto CMBits; // if precisely at the left edge, branch
    a |= M(0x01);
    if (n)
        goto CMBits; // if enemy object is beyond left edge, branch
    a -= M(ScreenLeft_PageLoc); // of left side
    a = M(Enemy_PageLoc + x); // subtract borrow from current page location
    writeData(0x01, a); // store here
    a -= M(ScreenLeft_X_Pos);
    c = 1; // to the left side of the screen
    a = M(Enemy_X_Position + x); // get enemy object position relative

CMBits: // otherwise use contents of Y
    goto SetupEOffsetFBBox; // otherwise, do something else
    if (!z)
        goto MoveBoundBoxOffscreen; // if anything set here, branch
    writeData(EnemyOffscrBitsMasked + x, a); // save masked offscreen bits here
    a &= M(Enemy_OffscreenBits); // preserve bitwise whatever's in here
    a = y;

LargePlatformBoundBox:
    if (c)
        goto MoveBoundBoxOffscreen; // box offscreen, otherwise start getting coordinates
    compare(a, 0xfe); // if completely offscreen, branch to put entire bounding
    --x; // decrement to return to original offset
    pushReturnIndex(493);
    goto GetXOffscreenBits;
Return_493: // then jump directly to the sub for horizontal offscreen bits
    ++x; // increment X to get the proper offset

SetupEOffsetFBBox:
    goto CheckRightScreenBBox; // jump to handle offscreen coordinates of bounding box
    pushReturnIndex(494);
    goto BoundingBoxCore;
Return_494: // do a sub to get the coordinates of the bounding box
    y = 0x01; // load 1 as offset here, same reason
    x = a;
    a += 0x01;
    c = 0; // the enemy object memory locations
    a = x; // add 1 to offset to properly address

MoveBoundBoxOffscreen:
    goto Return;

//------------------------------------------------------------------------
    writeData(EnemyBoundingBoxCoord + 3 + y, a);
    writeData(EnemyBoundingBoxCoord + 2 + y, a);
    writeData(EnemyBoundingBoxCoord + 1 + y, a);
    writeData(EnemyBoundingBoxCoord + y, a); // load value into four locations here and leave
    a = 0xff;
    y = a; // use as offset here
    a <<= 1;
    a <<= 1;
    a = x; // multiply offset by 4

BoundingBoxCore:
    goto Return;

//------------------------------------------------------------------------
    x = M(0x00); // get original offset and use as X again
    y = a; // use as Y
    pla(); // get original offset loaded into $00 * y from stack
    writeData(BoundingBox_LR_Corner + y, a); // and store
    a += M(BoundBoxCtrlData + 2 + x); // add the fourth number to the relative vertical coordinate
    c = 0;
    a = M(0x02);
    writeData(BoundingBox_UL_Corner + y, a);
    a += M(BoundBoxCtrlData + x); // incremented offset
    c = 0; // using incremented offset and store using the other
    a = M(0x02); // add the second number to the relative vertical coordinate
    ++y;
    ++x; // increment both offsets
    writeData(BoundingBox_LR_Corner + y, a); // relative horizontal coordinate and store
    a += M(BoundBoxCtrlData + 2 + x); // add the third number in the bounding box data to the
    c = 0;
    a = M(0x01);
    writeData(BoundingBox_UL_Corner + y, a); // store here
    a += M(BoundBoxCtrlData + x); // and store somewhere using same offset * 4
    c = 0; // relative horizontal coordinate using enemy object offset
    a = M(0x01); // add the first number in the bounding box data to the
    x = a;
    a <<= 1;
    a <<= 1; // multiply that by four and use as X
    a = M(SprObj_BoundBoxCtrl + x); // load value here to be used as offset for X
    y = a; // use as offset for Y, X is left alone
    pha();
    a <<= 1;
    a <<= 1;
    a = x; // multiply offset by four and save to stack
    writeData(0x01, a);
    a = M(SprObject_Rel_XPos + y);
    writeData(0x02, a); // vertically and horizontally, respectively
    a = M(SprObject_Rel_YPos + y); // store object coordinates relative to screen
    writeData(0x00, x); // save offset here

CheckRightScreenBBox:
    writeData(BoundingBox_UL_XPos + y, a); // store offscreen value for left side
    if (n)
        goto SORte; // coordinates, and branch if still on the screen
    x = M(BoundingBox_UL_XPos + y); // check left-side edge of bounding box for offscreen
    a = 0xff; // load offscreen value here to use on one or both horizontal sides
    if (n)
        goto NoOfs; // coordinates, branch if still on the screen
    a = M(BoundingBox_DR_XPos + y); // check right-side edge of bounding box for offscreen
    if (!c)
        goto CheckLeftScreenBBox; // if object is on the left side of the screen, branch
    a -= M(0x01); // subtract from middle page location
    a = M(SprObject_PageLoc + x); // get page location
    compare(a, M(0x02)); // compare against middle horizontal coordinate
    a = M(SprObject_X_Position + x); // get horizontal coordinate
    writeData(0x01, a);
    a += 0x00; // and store as page location of middle
    a = M(ScreenLeft_PageLoc); // add carry to page location of left side of screen
    writeData(0x02, a);
    a += 0x80;
    c = 0; // and store as horizontal coordinate of middle
    a = M(ScreenLeft_X_Pos); // add 128 pixels to left side of screen

SORte: // store offscreen value for right side
    writeData(BoundingBox_DR_XPos + y, a);

NoOfs: // get object offset and leave
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

CheckLeftScreenBBox:
    writeData(BoundingBox_DR_XPos + y, a); // store offscreen value for right side
    if (!n)
        goto SOLft; // coordinates, branch if still onscreen
    x = M(BoundingBox_DR_XPos + y); // check right-side edge of bounding box for offscreen
    a = 0x00;
    if (!c)
        goto NoOfs2; // screen or really offscreen, and branch if still on
    compare(a, 0xa0); // check to see if left-side edge is in the middle of the
    if (!n)
        goto NoOfs2; // coordinates, and branch if still on the screen
    a = M(BoundingBox_UL_XPos + y); // check left-side edge of bounding box for offscreen

SOLft: // store offscreen value for left side
    writeData(BoundingBox_UL_XPos + y, a);

NoOfs2: // get object offset and leave
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

PlayerCollisionCore:
    x = 0x00; // initialize X to use player's bounding box for comparison

SprObjectCollisionCore:
    writeData(0x07, a); // save value 1 here as counter, compare horizontal coordinates first
    a = 0x01;
    writeData(0x06, y); // save contents of Y here

CollisionCoreLoop:
    goto Return; // note horizontal wrapping never occurs

//------------------------------------------------------------------------
    y = M(0x06); // otherwise return with carry clear and Y = $0006
    if (c)
        goto CollisionFound; // of second box, and if equal or greater, collision, thus branch
    compare(a, M(BoundingBox_UL_Corner + x)); // otherwise compare bottom of first bounding box to the top
    if (!c)
        goto CollisionFound; // if somehow less, vertical wrap collision, thus branch
    compare(a, M(BoundingBox_UL_Corner + y)); // first object's bounding box is greater than its top
    a = M(BoundingBox_LR_Corner + y); // if somehow greater, check to see if bottom of
    if (z)
        goto CollisionFound; // if somehow equal, collision, thus branch
    if (!c)
        goto SecondBoxVerticalChk; // if first left/top < second right/bottom, branch elsewhere
    compare(a, M(BoundingBox_LR_Corner + x)); // otherwise compare to right/bottom of second
    if (c)
        goto FirstBoxGreater; // if first left/top => second, branch
    compare(a, M(BoundingBox_UL_Corner + x)); // of first and second objects' bounding boxes
    a = M(BoundingBox_UL_Corner + y); // compare left/top coordinates

SecondBoxVerticalChk:
    goto Return;

//------------------------------------------------------------------------
    y = M(0x06); // otherwise return with carry clear and Y = $0006
    if (c)
        goto CollisionFound; // if equal or greater, collision, thus branch
    compare(a, M(BoundingBox_UL_Corner + x)); // of first box with horizontal left or vertical top of second box
    a = M(BoundingBox_LR_Corner + y); // otherwise compare horizontal right or vertical bottom
    if (!c)
        goto CollisionFound; // if somehow less, vertical wrap collision, thus branch
    compare(a, M(BoundingBox_UL_Corner + x)); // is greater than the vertical top
    a = M(BoundingBox_LR_Corner + x); // check to see if the vertical bottom of the box

FirstBoxGreater:
    if (c)
        goto CollisionFound; // collision, and branch, otherwise, proceed onwards here
    compare(a, M(BoundingBox_UL_Corner + x)); // if bottom of first is greater than top of second, vertical wrap
    a = M(BoundingBox_LR_Corner + y); // otherwise compare bottom of first to top of second
    if (z)
        goto NoCollisionFound;
    if (!c)
        goto NoCollisionFound; // if less than or equal, no collision, branch to end
    compare(a, M(BoundingBox_LR_Corner + y)); // otherwise check to see if top of first box is greater than bottom
    if (z)
        goto CollisionFound; // then collision, thus branch
    if (!c)
        goto CollisionFound; // if left/top of first less than or equal to right/bottom of second
    compare(a, M(BoundingBox_LR_Corner + x)); // if not, compare with second object right or bottom edge
    if (z)
        goto CollisionFound; // if first coordinate = second, collision, thus branch
    compare(a, M(BoundingBox_UL_Corner + x)); // compare first and second box horizontal left/vertical top again

NoCollisionFound:
    goto Return; // not bother checking vertical ones, because what's the point?

//------------------------------------------------------------------------
    y = M(0x06); // like previous ones, if horizontal coordinates do not collide, we do
    c = 0; // clear carry, then load value set earlier, then leave

CollisionFound:
    goto Return;

//------------------------------------------------------------------------
    y = M(0x06); // load original value set here earlier, then leave
    c = 1; // otherwise we already did both sets, therefore collision, so set carry
    if (!n)
        goto CollisionCoreLoop; // if counter not expired, branch to loop
    --M(0x07); // decrement counter to reflect this
    ++y; // the vertical coordinates
    ++x; // increment offsets on both objects to check

BlockBufferChk_Enemy:
    goto BBChk_E;
    pla(); // pull A from stack and jump elsewhere
    x = a;
    a += 0x01;
    c = 0; // add 1 to X to run sub with enemy offset in mind
    a = x;
    pha(); // save contents of A to stack

ResidualMiscObjectCode:
    goto ResJmpM; // probably used in early stages to do misc to bg collision detection
    y = 0x1b; // supposedly used once to set offset for block buffer data
    x = a;
    a += 0x0d; // miscellaneous objects
    c = 0; // supposedly used once to set offset for
    a = x;

BlockBufferChk_FBall:
    x = a;
    a += 0x07; // add seven bytes to use
    c = 0;
    a = x;
    y = 0x1a; // set offset for block buffer adder data

ResJmpM: // set A to return vertical coordinate
    a = 0x00;

BBChk_E: // do collision detection subroutine for sprite object
    goto Return;

//------------------------------------------------------------------------
    compare(a, 0x00); // check to see if object bumped into anything
    x = M(ObjectOffset); // get object offset
    pushReturnIndex(495);
    goto BlockBufferCollision;
Return_495:

BlockBufferColli_Feet:
    ++y; // if branched here, increment to next set of adders

BlockBufferColli_Head:
    goto Skip_9;
    a = 0x00; // set flag to return vertical coordinate
Skip_9:

BlockBufferColli_Side:
    x = 0x00; // set offset for player object
    a = 0x01; // set flag to return horizontal coordinate

BlockBufferCollision:
    goto RetYC; // and jump
    a = M(SprObject_Y_Position + x); // if A = 0, load vertical coordinate
    if (!z)
        goto RetXC; // if A = 1, branch
    pla(); // pull A from stack
    y = M(0x04); // get old contents of Y again
    writeData(0x03, a); // and store here
    a = M(W(0x06) + y); // check current content of block buffer
    y = a; // use as offset for block buffer
    writeData(0x02, a); // store result here
    a -= 0x20; // subtract 32 pixels for the status bar
    c = 1;
    a &= BOOST_BINARY(11110000); // mask out low nybble
    a += M(BlockBuffer_Y_Adder + y); // add it to value obtained using Y as offset
    c = 0;
    a = M(SprObject_Y_Position + x); // get vertical coordinate of object
    y = M(0x04); // get old contents of Y
    pushReturnIndex(496);
    goto GetBlockBufferAddr;
Return_496: // get address of block buffer into $06, $07
    a >>= 1; // d4 at this point
    a >>= 1; // lower, LSB which became MSB will be
    a >>= 1; // and effectively move high nybble to
    a.ror(); // rotate carry to MSB of A
    a |= M(0x05); // get stored value
    a >>= 1; // move to carry
    a &= 0x01; // get LSB, mask out all other bits
    a += 0x00; // add carry to page location
    a = M(SprObject_PageLoc + x);
    writeData(0x05, a); // store here
    a += M(SprObject_X_Position + x);
    c = 0; // of object to value obtained using Y as offset
    a = M(BlockBuffer_X_Adder + y); // add horizontal coordinate
    writeData(0x04, y); // save contents of Y here
    pha(); // save contents of A to stack

RetXC: // otherwise load horizontal coordinate
    a = M(SprObject_X_Position + x);

RetYC: // and mask out high nybble
    goto Return; // and leave

//------------------------------------------------------------------------
    a = M(0x03); // get saved content of block buffer
    writeData(0x04, a); // store masked out result here
    a &= BOOST_BINARY(00001111);

DrawVine:
    x = 0x05; // set tiles for six sprites
    writeData(Sprite_Attributes + 20 + y, a);
    writeData(Sprite_Attributes + 12 + y, a);
    writeData(Sprite_Attributes + 4 + y, a); // for second, fourth and sixth sprites
    a |= BOOST_BINARY(01000000); // additionally, set horizontal flip bit
    writeData(Sprite_Attributes + 16 + y, a);
    writeData(Sprite_Attributes + 8 + y, a);
    writeData(Sprite_Attributes + y, a); // set in first, third and fifth sprites
    a = BOOST_BINARY(00100001); // set bg priority and palette attribute bits
    writeData(Sprite_X_Position + 20 + y, a);
    writeData(Sprite_X_Position + 12 + y, a); // our vertical stack of sprites
    writeData(Sprite_X_Position + 4 + y, a); // to give characteristic staggered vine shape to
    a += 0x06; // add six pixels to second, fourth and sixth sprites
    c = 0;
    writeData(Sprite_X_Position + 16 + y, a);
    writeData(Sprite_X_Position + 8 + y, a);
    writeData(Sprite_X_Position + y, a); // store in first, third and fifth sprites
    a = M(Enemy_Rel_XPos); // get relative horizontal coordinate
    pushReturnIndex(497);
    goto SixSpriteStacker;
Return_497: // stack six sprites on top of each other vertically
    writeData(0x02, y); // store sprite data offset here
    y = M(Enemy_SprDataOffset + x); // get sprite data offset
    x = M(VineObjOffset + y); // get offset to vine
    a += M(VineYPosAdder + y); // add value using offset in Y to get value
    c = 0;
    a = M(Enemy_Rel_YPos); // get relative vertical coordinate
    writeData(0x00, y); // save offset here

VineTL: // set tile number for sprite
    writeData(Sprite_Tilenumber + y, a); // set other tile number for top of vine
    a = 0xe0;
    if (!z)
        goto SkpVTop; // if offset not zero, skip this part
    a = M(0x00); // get offset to vine adding data
    y = M(0x02); // get original offset
    if (!n)
        goto VineTL; // loop until all sprites are done
    --x; // move onto next sprite
    ++y;
    ++y;
    ++y;
    ++y; // move offset to next sprite data
    writeData(Sprite_Tilenumber + y, a);
    a = 0xe1;

SkpVTop: // start with the first sprite again
    x = 0x00;

ChkFTop: // get original starting vertical coordinate
    writeData(Sprite_Y_Position + y, a); // otherwise move sprite offscreen
    a = 0xf8;
    if (!c)
        goto NextVSp; // apart, skip this to leave sprite alone
    compare(a, 0x64); // if two coordinates are less than 100/$64 pixels
    a -= M(Sprite_Y_Position + y); // subtract top-most sprite's Y coordinate
    c = 1;
    a = M(VineStart_Y_Position);

NextVSp: // move offset to next OAM data
    goto Return;

//------------------------------------------------------------------------
    y = M(0x00); // return offset set earlier
    if (!z)
        goto ChkFTop;
    compare(x, 0x06); // do this until all sprites are checked
    ++x; // move onto next sprite
    ++y;
    ++y;
    ++y;
    ++y;

SixSpriteStacker:
    x = 0x06; // do six sprites

StkLp: // store X or Y coordinate into OAM data
    goto Return;

//------------------------------------------------------------------------
    y = M(0x02); // get saved OAM data offset and leave
    if (!z)
        goto StkLp; // do this until all sprites are done
    --x; // do another sprite
    ++y;
    ++y;
    ++y; // move offset four bytes forward
    ++y;
    a += 0x08; // add eight pixels
    c = 0;
    writeData(Sprite_Data + y, a);

DrawHammer:
    if (z)
        goto GetHPose; // if so, branch
    compare(a, 0x01); // check to see if set to 1 yet
    a &= BOOST_BINARY(01111111); // mask out d7
    a = M(Misc_State + x); // otherwise get hammer's state
    if (!z)
        goto ForceHPose; // if master timer control set, skip this part
    a = M(TimerControl);
    y = M(Misc_SprDataOffset + x); // get misc object OAM data offset

ForceHPose: // reset offset here
    if (z)
        goto RenderH; // do unconditional branch to rendering part
    x = 0x00;

GetHPose: // get frame counter
    x = a; // use as timing offset
    a &= BOOST_BINARY(00000011); // mask out all but d1-d0 (changes every four frames)
    a >>= 1;
    a >>= 1; // move d3-d2 to d1-d0
    a = M(FrameCounter);

RenderH: // get relative vertical coordinate
    pushReturnIndex(498);
    goto DumpTwoSpr;
Return_498: // do sub to move hammer sprites offscreen
    a = 0xf8;
    writeData(Misc_State + x, a); // otherwise nullify misc object state
    a = 0x00;
    if (z)
        goto NoHOffscr; // if all bits clear, leave object alone
    a &= BOOST_BINARY(11111100); // check offscreen bits
    a = M(Misc_OffscreenBits);
    x = M(ObjectOffset); // get misc object offset
    writeData(Sprite_Attributes + 4 + y, a); // note in this case they use the same data
    writeData(Sprite_Attributes + y, a); // get and store attribute bytes for both
    a = M(HammerSprAttrib + x);
    writeData(Sprite_Tilenumber + 4 + y, a); // get and store tile number of second sprite
    a = M(SecondSprTilenum + x);
    writeData(Sprite_Tilenumber + y, a); // get and store tile number of first sprite
    a = M(FirstSprTilenum + x);
    writeData(Sprite_X_Position + 4 + y, a); // store as sprite X coordinate for second sprite
    a += M(SecondSprXPos + x); // add second sprite horizontal adder based on offset
    c = 0;
    writeData(Sprite_X_Position + y, a); // store as sprite X coordinate for first sprite
    a += M(FirstSprXPos + x); // add first sprite horizontal adder based on offset
    c = 0;
    a = M(Misc_Rel_XPos); // get relative horizontal coordinate
    writeData(Sprite_Y_Position + 4 + y, a); // store as sprite Y coordinate for second sprite
    a += M(SecondSprYPos + x); // add second sprite vertical adder based on offset
    c = 0;
    writeData(Sprite_Y_Position + y, a); // store as sprite Y coordinate for first sprite
    a += M(FirstSprYPos + x); // add first sprite vertical adder based on offset
    c = 0;
    a = M(Misc_Rel_YPos);

NoHOffscr: // leave
    goto Return;

//------------------------------------------------------------------------

FlagpoleGfxHandler:
    pushReturnIndex(499);
    goto DrawOneSpriteRow;
Return_499: // use it to render floatey number
    a = M(FlagpoleScoreNumTiles + 1 + x);
    writeData(0x00, a);
    a = M(FlagpoleScoreNumTiles + x); // get appropriate tile data
    x = a;
    a <<= 1; // multiply by 2 to get proper offset here
    a = M(FlagpoleScore); // get offset used to award points for touching flagpole
    y = a; // put back in Y
    a += 0x0c;
    c = 0; // add 12 bytes to sprite data offset
    a = y;
    if (z)
        goto ChkFlagOffscreen; // if zero, branch ahead
    a = M(FlagpoleCollisionYPos); // get vertical coordinate at time of collision
    writeData(Sprite_Tilenumber + 4 + y, a); // put skull tile into second sprite
    a = 0x7f;
    writeData(Sprite_Tilenumber + 8 + y, a); // into first and third sprites
    writeData(Sprite_Tilenumber + y, a); // put triangle shaped tile
    a = 0x7e;
    writeData(Sprite_Attributes + 8 + y, a);
    writeData(Sprite_Attributes + 4 + y, a);
    writeData(Sprite_Attributes + y, a); // set attribute bytes for all three sprites
    writeData(0x04, a); // attribute byte for floatey number
    writeData(0x03, a); // set value for flip which will not be used, and
    a = 0x01;
    writeData(0x02, a); // store it here
    a = M(FlagpoleFNum_Y_Pos); // get vertical coordinate for floatey number
    writeData(Sprite_Y_Position + 8 + y, a); // and store into third sprite
    a += 0x08; // add eight pixels
    pushReturnIndex(500);
    goto DumpTwoSpr;
Return_500: // and do sub to dump into first and second sprites
    a = M(Enemy_Y_Position + x); // get vertical coordinate
    writeData(0x05, a); // store here to be used later by floatey number
    a += 0x0c; // add twelve more pixels and
    c = 0;
    writeData(Sprite_X_Position + 8 + y, a);
    writeData(Sprite_X_Position + 4 + y, a); // as X coordinate for second and third sprites
    a += 0x08; // add eight pixels and store
    c = 0;
    writeData(Sprite_X_Position + y, a); // store as X coordinate for first sprite
    a = M(Enemy_Rel_XPos); // get relative horizontal coordinate
    y = M(Enemy_SprDataOffset + x); // get sprite data offset for flagpole flag

ChkFlagOffscreen:
    if (z)
        goto ExitDumpSpr; // if none of these bits set, branch to leave
    a &= BOOST_BINARY(00001110); // mask out all but d3-d1
    a = M(Enemy_OffscreenBits); // get offscreen bits
    y = M(Enemy_SprDataOffset + x); // get OAM data offset
    x = M(ObjectOffset); // get object offset for flag

MoveSixSpritesOffscreen:
    a = 0xf8; // set offscreen coordinate if jumping here

DumpSixSpr:
    writeData(Sprite_Data + 16 + y, a); // into third row sprites
    writeData(Sprite_Data + 20 + y, a); // dump A contents

DumpFourSpr:
    writeData(Sprite_Data + 12 + y, a); // into second row sprites

DumpThreeSpr:
    writeData(Sprite_Data + 8 + y, a);

DumpTwoSpr:
    writeData(Sprite_Data + y, a);
    writeData(Sprite_Data + 4 + y, a); // and into first row sprites

ExitDumpSpr:
    goto Return;

//------------------------------------------------------------------------

DrawLargePlatform:
    if (z)
        goto SetLast2Platform; // branch if not set elsewhere
    y = M(SecondaryHardMode); // check for secondary hard mode flag set
    if (z)
        goto ShrinkPlatform;
    compare(y, 0x03); // check for castle-type level
    y = M(AreaType);
    pushReturnIndex(501);
    goto DumpFourSpr;
Return_501: // dump into first four sprites as Y coordinate
    a = M(Enemy_Y_Position + x); // get vertical coordinate
    x = M(ObjectOffset);
    pushReturnIndex(502);
    goto SixSpriteStacker;
Return_502: // store X coordinates using A as base, stack horizontally
    a = M(Enemy_Rel_XPos); // get horizontal relative coordinate
    ++y;
    ++y; // to X coordinate
    ++y; // add 3 to it for offset
    writeData(0x02, y); // store here
    y = M(Enemy_SprDataOffset + x); // get OAM data offset

ShrinkPlatform:
    a = 0xf8; // load offscreen coordinate if flag set or castle-type level

SetLast2Platform:
    a = 0x75; // otherwise load other tile for platform (puff)
    if (z)
        goto SetPlatformTilenum; // if cloud level override flag not set, use
    x = M(CloudTypeOverride);
    a = 0x5b; // load default tile for platform (girder)
    writeData(Sprite_Y_Position + 20 + y, a); // coordinate into last two sprites as Y coordinate
    writeData(Sprite_Y_Position + 16 + y, a); // store vertical coordinate or offscreen
    y = M(Enemy_SprDataOffset + x); // get OAM data offset

SetPlatformTilenum:
    writeData(Sprite_Y_Position + y, a);
    a = 0xf8; // if d7 was set, move first sprite offscreen
    if (!c)
        goto SChk2;
    pha(); // bits to the stack
    a <<= 1; // rotate d7 into carry, save remaining
    y = M(Enemy_SprDataOffset + x); // get OAM data offset
    --x;
    pushReturnIndex(503);
    goto GetXOffscreenBits;
Return_503: // get offscreen bits again
    ++x; // increment X for enemy objects
    pushReturnIndex(504);
    goto DumpSixSpr;
Return_504: // dump attributes into all six sprites
    ++y; // increment Y for sprite attributes
    a = 0x02; // set palette controls
    pushReturnIndex(505);
    goto DumpSixSpr;
Return_505: // dump tile number into all six sprites
    ++y; // increment Y for tile offset
    x = M(ObjectOffset); // get enemy object buffer offset

SChk2: // get bits from stack
    writeData(Sprite_Y_Position + 4 + y, a);
    a = 0xf8; // if d6 was set, move second sprite offscreen
    if (!c)
        goto SChk3;
    pha(); // save to stack
    a <<= 1; // rotate d6 into carry
    pla();

SChk3: // get bits from stack
    writeData(Sprite_Y_Position + 8 + y, a);
    a = 0xf8; // if d5 was set, move third sprite offscreen
    if (!c)
        goto SChk4;
    pha(); // save to stack
    a <<= 1; // rotate d5 into carry
    pla();

SChk4: // get bits from stack
    writeData(Sprite_Y_Position + 12 + y, a);
    a = 0xf8; // if d4 was set, move fourth sprite offscreen
    if (!c)
        goto SChk5;
    pha(); // save to stack
    a <<= 1; // rotate d4 into carry
    pla();

SChk5: // get bits from stack
    writeData(Sprite_Y_Position + 16 + y, a);
    a = 0xf8; // if d3 was set, move fifth sprite offscreen
    if (!c)
        goto SChk6;
    pha(); // save to stack
    a <<= 1; // rotate d3 into carry
    pla();

SChk6: // get bits from stack
    writeData(Sprite_Y_Position + 20 + y, a); // if d2 was set, move sixth sprite offscreen
    a = 0xf8;
    if (!c)
        goto SLChk; // save to stack
    a <<= 1; // rotate d2 into carry
    pla();

SLChk: // check d7 of offscreen bits
    pushReturnIndex(506);
    goto MoveSixSpritesOffscreen;
Return_506: // otherwise branch to move all sprites offscreen
    if (!c)
        goto ExDLPl;
    a <<= 1; // and if d7 is not set, skip sub
    a = M(Enemy_OffscreenBits);

ExDLPl:
    goto Return;

//------------------------------------------------------------------------

DrawFloateyNumber_Coin:
    --M(Misc_Y_Position + x); // otherwise, decrement vertical coordinate
    if (c)
        goto NotRsNum; // branch if d0 not set to raise number every other frame
    a >>= 1; // divide by 2
    a = M(FrameCounter); // get frame counter

NotRsNum: // get vertical coordinate
    goto ExJCGfx; // then jump to leave (why not an rts here instead?)
    writeData(Sprite_Tilenumber + 4 + y, a);
    a = 0xfb; // that resemble "200"
    writeData(Sprite_Tilenumber + y, a); // put tile numbers into both sprites
    a = 0xf7;
    writeData(Sprite_Attributes + 4 + y, a);
    writeData(Sprite_Attributes + y, a); // store attribute byte in both sprites
    a = 0x02;
    writeData(Sprite_X_Position + 4 + y, a); // store as X coordinate for second sprite
    a += 0x08; // add eight pixels
    c = 0;
    writeData(Sprite_X_Position + y, a); // store as X coordinate for first sprite
    a = M(Misc_Rel_XPos); // get relative horizontal coordinate
    pushReturnIndex(507);
    goto DumpTwoSpr;
Return_507: // dump into both sprites
    a = M(Misc_Y_Position + x);

JCoinGfxHandler:
    x = M(ObjectOffset); // get misc object offset
    writeData(Sprite_Attributes + 4 + y, a); // set attribute byte with vertical flip in second sprite
    a = 0x82;
    writeData(Sprite_Attributes + y, a); // set attribute byte in first sprite
    a = 0x02;
    --y; // decrement to get old offset
    pushReturnIndex(508);
    goto DumpTwoSpr;
Return_508: // do sub to dump tile number into both sprites
    ++y; // increment OAM data offset to write tile numbers
    a = M(JumpingCoinTiles + x); // load tile number
    x = a; // use as graphical offset
    a &= BOOST_BINARY(00000011); // mask out d2-d1
    a >>= 1; // divide by 2 to alter every other frame
    a = M(FrameCounter); // get frame counter
    writeData(Sprite_X_Position + 4 + y, a); // store as X coordinate for first and second sprites
    writeData(Sprite_X_Position + y, a);
    a = M(Misc_Rel_XPos); // get relative horizontal coordinate
    writeData(Sprite_Y_Position + 4 + y, a); // store as Y coordinate for second sprite
    a += 0x08; // add eight pixels
    c = 0;
    writeData(Sprite_Y_Position + y, a); // Y coordinate for first sprite
    a = M(Misc_Y_Position + x); // store vertical coordinate as
    if (c)
        goto DrawFloateyNumber_Coin; // branch to draw floatey number
    compare(a, 0x02); // if 2 or greater, 
    a = M(Misc_State + x); // get state of misc object
    y = M(Misc_SprDataOffset + x); // get coin/floatey number's OAM data offset

ExJCGfx: // leave
    goto Return;

//------------------------------------------------------------------------

DrawPowerUp:
    writeData(0x03, a); // init d1 of flip control
    writeData(0x07, a); // set counter here to draw two rows of sprite object
    a = 0x01;
    x = a; // use as X
    a <<= 1; // multiply by four to get proper offset
    a <<= 1;
    pha(); // save power-up type to the stack
    a = x;
    writeData(0x04, a); // store attributes here
    a |= M(Enemy_SprAttrib + 5); // add background priority bit if set
    a = M(PowerUpAttributes + x); // get attribute data for power-up type
    x = M(PowerUpType); // get power-up type
    writeData(0x05, a); // store here
    a = M(Enemy_Rel_XPos); // get relative horizontal coordinate
    writeData(0x02, a); // store result here
    a += 0x08; // add eight pixels
    c = 0;
    a = M(Enemy_Rel_YPos); // get relative vertical coordinate
    y = M(Enemy_SprDataOffset + 5); // get power-up's sprite data offset

PUpDrawLoop:
    writeData(Sprite_Attributes + 12 + y, a); // and bottom right sprites as well for star only
    writeData(Sprite_Attributes + 8 + y, a); // otherwise set new palette bits  for bottom left
    if (z)
        goto FlipPUpRightSide; // if found, skip this part
    --x; // check power-up type for fire flower
    x = M(0x00);
    writeData(Sprite_Attributes + 4 + y, a); // top right sprites for fire flower and star
    writeData(Sprite_Attributes + y, a); // set as new palette bits for top left and
    a |= M(Enemy_SprAttrib + 5); // add background priority bit if any set
    a &= BOOST_BINARY(00000011); // mask out all but d1 and d0 (previously d2 and d1)
    a >>= 1; // divide by 2 to change colors every two frames
    a = M(FrameCounter); // get frame counter
    writeData(0x00, a); // store power-up type here now
    if (z)
        goto PUpOfs; // if 1-up mushroom, branch, do not change colors or flip
    compare(a, 0x03);
    if (z)
        goto PUpOfs; // if regular mushroom, branch, do not change colors or flip
    pla(); // pull saved power-up type from the stack
    y = M(Enemy_SprDataOffset + 5); // get sprite data offset again
    if (!n)
        goto PUpDrawLoop; // branch until two rows are drawn
    --M(0x07); // decrement counter
    pushReturnIndex(509);
    goto DrawOneSpriteRow;
Return_509: // branch to draw one row of our power-up object
    a = M(PowerUpGfxTable + 1 + x); // load right tile
    writeData(0x00, a);
    a = M(PowerUpGfxTable + x); // load left tile of power-up object

FlipPUpRightSide:
    writeData(Sprite_Attributes + 12 + y, a); // note these are only done for fire flower and star power-ups
    a |= BOOST_BINARY(01000000); // set horizontal flip bit for bottom right sprite
    a = M(Sprite_Attributes + 12 + y);
    writeData(Sprite_Attributes + 4 + y, a);
    a |= BOOST_BINARY(01000000); // set horizontal flip bit for top right sprite
    a = M(Sprite_Attributes + 4 + y);

PUpOfs: // jump to check to see if power-up is offscreen at all, then leave
    goto SprObjectOffscrChk;

EnemyGfxHandler:
    goto Return; // if all conditions fail, leave

//------------------------------------------------------------------------
    if (z)
        goto CheckForRetainerObj; // if timer for movement expired, branch
    y = M(EnemyFrameTimer + x);
    if (n)
        goto CheckForRetainerObj; // if piranha plant moving upwards, branch
    y = M(PiranhaPlant_Y_Speed + x);
    if (!z)
        goto CheckForRetainerObj; // if not, branch
    compare(a, PiranhaPlant); // is enemy object piranha plant?
    a = M(Enemy_ID + x);
    writeData(0x04, a); // get enemy object sprite attributes
    a = M(Enemy_SprAttrib + x);
    writeData(0x03, a); // get enemy object moving direction
    a = M(Enemy_MovingDir + x);
    writeData(VerticalFlipFlag, a); // initialize vertical flip flag by default
    a = 0x00;
    writeData(0xeb, y); // get sprite data offset
    y = M(Enemy_SprDataOffset + x);
    writeData(0x05, a); // relative to screen
    a = M(Enemy_Rel_XPos); // get enemy object horizontal position
    writeData(0x02, a);
    a = M(Enemy_Y_Position + x); // get enemy object vertical position

CheckForRetainerObj:
    a = 0x15; // set value $15 as code for mushroom retainer/princess object
    writeData(0x03, a);
    a = 0x01; // set value that will not be used
    y = 0x00; // if found, nullify saved state in Y
    if (!z)
        goto CheckForBulletBillCV; // if not found, branch
    compare(a, RetainerObject);
    a = M(Enemy_ID + x); // check for mushroom retainer/princess object
    y = a;
    a &= BOOST_BINARY(00011111); // nullify all but 5 LSB and use as Y
    writeData(0xed, a);
    a = M(Enemy_State + x); // store enemy state

CheckForBulletBillCV:
    a |= BOOST_BINARY(00100000); // otherwise do so
    if (z)
        goto SBBAt; // if expired, do not set priority bit
    y = M(EnemyFrameTimer + x); // get timer for enemy object
    a = 0x03;
    --M(0x02); // decrement saved vertical position
    if (!z)
        goto CheckForJumpspring; // if not found, branch again
    compare(a, BulletBill_CannonVar); // otherwise check for bullet bill object

SBBAt: // set new sprite attributes
    a = 0x08; // set specific value to unconditionally branch once
    writeData(0xed, y); // memory location here
    y = 0x00; // nullify saved enemy state both in Y and in
    writeData(0x04, a);

CheckForJumpspring:
    a = M(JumpspringFrameOffsets + x); // load data using frame number as offset
    x = M(JumpspringAnimCtrl); // get current frame number for jumpspring object
    y = 0x03; // set enemy state -2 MSB here for jumpspring object
    if (!z)
        goto CheckForPodoboo;
    compare(a, JumpspringObject); // check for jumpspring object

CheckForPodoboo:
    ++M(VerticalFlipFlag); // otherwise, set flag for vertical flip
    if (n)
        goto CheckBowserGfxFlag;
    a = M(Enemy_Y_Speed + x); // if moving upwards, branch
    if (!z)
        goto CheckBowserGfxFlag; // branch if not found
    compare(a, 0x0c); // check for podoboo object
    x = M(ObjectOffset); // get enemy object offset
    writeData(0xec, y); // and Y here (enemy state -2 MSB if not changed)
    writeData(0xef, a); // store saved enemy object value here

CheckBowserGfxFlag:
    ++y; // otherwise draw bowser's rear
    if (z)
        goto SBwsrGfxOfs;
    compare(a, 0x01);
    y = 0x16; // if set to 1, draw bowser's front
    if (z)
        goto CheckForGoomba;
    a = M(BowserGfxFlag); // if not drawing bowser at all, skip to something else

SBwsrGfxOfs:
    writeData(0xef, y);

CheckForGoomba:
    writeData(0xec, x);
    x = 0x04; // if defeated, write new value here
    if (!c)
        goto GmbaAnim; // if not defeated, go ahead and animate
    compare(a, 0x02); // check for defeated state
    a = M(Enemy_State + x);
    if (!z)
        goto CheckBowserFront; // branch if not found
    compare(y, Goomba);
    y = M(0xef); // check value for goomba object

GmbaAnim: // check for d5 set in enemy object state 
    writeData(0x03, a); // leave alone otherwise
    a ^= BOOST_BINARY(00000011); // invert bits to flip horizontally every eight frames
    a = M(0x03);
    if (!z)
        goto CheckBowserFront;
    a &= BOOST_BINARY(00001000); // check for every eighth frame
    a = M(FrameCounter);
    if (!z)
        goto CheckBowserFront; // if either condition true, do not animate goomba
    a |= M(TimerControl); // or timer disable flag set
    a &= BOOST_BINARY(00100000);

CheckBowserFront:
    x = 0xde; // otherwise load offset for second frame
    if (!n)
        goto ChkFrontSte; // branch if d7 not set (control's bowser's mouth)      
    a = M(BowserBodyControls); // check bowser's body control bits
    if (!z)
        goto CheckBowserRear; // if not drawing front part, branch to draw the rear part
    compare(a, 0x01);
    if (z)
        goto CheckForSpiny; // if not drawing bowser object at all, skip all of this
    a = M(BowserGfxFlag);
    y = M(0xec); // get previously saved value
    x = a; // save as X
    a = M(EnemyGfxTableOffsets + y); // load value based on enemy object as offset
    writeData(0x04, a);
    a |= M(0x04); // as offset, and add to bits already loaded
    a = M(EnemyAttributeData + y); // load sprite attribute using enemy object

ChkFrontSte: // check saved enemy state
    if (z)
        goto DrawBowser;
    a &= BOOST_BINARY(00100000); // if bowser not defeated, do not set flag
    a = M(0xed);

FlipBowserOver:
    writeData(VerticalFlipFlag, x); // set vertical flip flag to nonzero

DrawBowser:
    goto DrawEnemyObject; // draw bowser's graphics now

CheckBowserRear:
    x = 0xe4; // otherwise load offset for second frame
    if (z)
        goto ChkRearSte; // branch if d0 not set (control's bowser's feet)
    a &= 0x01;
    a = M(BowserBodyControls); // check bowser's body control bits

ChkRearSte: // check saved enemy state
    goto FlipBowserOver; // jump to set vertical flip flag
    writeData(0x02, a);
    a -= 0x10;
    c = 1; // saved vertical coordinate
    a = M(0x02); // subtract 16 pixels from
    if (z)
        goto DrawBowser;
    a &= BOOST_BINARY(00100000); // if bowser not defeated, do not set flag
    a = M(0xed);

CheckForSpiny:
    writeData(0xec, a); // set enemy state
    a = 0x05;
    writeData(0x03, a); // set enemy direction to reverse sprites horizontally
    a = 0x02;
    x = 0x30; // set to spiny egg offset
    if (!z)
        goto NotEgg; // otherwise branch
    compare(y, 0x05); // if enemy state set to $05, do this,
    if (!z)
        goto CheckForLakitu; // if not found, branch
    compare(x, 0x24); // check if value loaded is for spiny

NotEgg: // skip a big chunk of this if we found spiny but not in egg
    goto CheckForHammerBro;

CheckForLakitu:
    x = 0x96; // if d6 not set and timer in range, load alt frame for lakitu
    if (c)
        goto NoLAFr; // branch if not
    compare(a, 0x10); // check timer to see if we've reached a certain range
    a = M(FrenzyEnemyTimer);
    if (!z)
        goto NoLAFr; // branch if set
    a &= BOOST_BINARY(00100000); // check for d5 set in enemy state
    a = M(0xed);
    if (!z)
        goto CheckUpsideDownShell; // branch if not loaded
    compare(x, 0x90); // check value for lakitu's offset loaded

NoLAFr: // skip this next part if we found lakitu but alt frame not needed
    goto CheckDefeatedState;

CheckUpsideDownShell:
    ++M(0x02); // increment vertical position by one pixel
    x = 0x7e; // set for upside-down buzzy beetle shell if found
    if (!z)
        goto CheckRightSideUpShell;
    compare(y, BuzzyBeetle); // check for buzzy beetle object
    y = M(0xef);
    x = 0x5a; // set for upside-down koopa shell by default
    if (!c)
        goto CheckRightSideUpShell; // branch if enemy state < $02
    compare(y, 0x02);
    if (c)
        goto CheckRightSideUpShell; // branch if true
    compare(a, 0x04);
    a = M(0xef); // check for enemy object => $04

CheckRightSideUpShell:
    ++M(0x02); // and increment saved vertical position again
    x = 0x66; // change to right-side up koopa shell if not found
    if (z)
        goto CheckForDefdGoomba; // branch if found
    compare(y, BuzzyBeetle); // check for buzzy beetle object
    y = M(0xef);
    ++M(0x02); // increment saved vertical position by one pixel
    x = 0x72; // set right-side up buzzy beetle shell by default
    if (!z)
        goto CheckForHammerBro; // enemy state => $02 but not = $04, leave shell upside-down
    compare(a, 0x04); // if enemy state < $02, do not change to shell, if
    a = M(0xec); // check for value set here

CheckForDefdGoomba:
    --M(0x02); // set different value and decrement saved vertical position
    x = 0x8a; // load offset for defeated goomba
    if (!z)
        goto CheckForHammerBro; // branch if set
    a &= BOOST_BINARY(00100000); // check saved enemy state for d5 set
    a = M(0xed); // note that this only gets performed if enemy state => $02
    x = 0x54; // load for regular goomba
    if (!z)
        goto CheckForHammerBro; // failed buzzy beetle object test)
    compare(y, Goomba); // check for goomba object (necessary if previously

CheckForHammerBro:
    if (!z)
        goto CheckToAnimateEnemy; // unconditional branch
    x = 0xb4; // otherwise load offset for different frame
    if (z)
        goto CheckDefeatedState; // if d3 not set, branch further away
    a &= BOOST_BINARY(00001000);
    if (z)
        goto CheckToAnimateEnemy; // branch if not in normal enemy state
    a = M(0xed);
    if (!z)
        goto CheckForBloober; // branch if not found
    compare(a, HammerBro);
    a = M(0xef); // check for hammer bro object
    y = M(ObjectOffset);

CheckForBloober:
    goto CheckAnimationStop; // and do something else
    ++M(0x02);
    ++M(0x02);
    ++M(0x02); // increment saved vertical coordinate three pixels
    if (z)
        goto CheckDefeatedState; // branch if timer is set to certain point
    compare(a, 0x01);
    if (!z)
        goto CheckToAnimateEnemy; // branch if not found this time
    compare(x, 0x3c); // check for bloober offset loaded
    if (c)
        goto CheckDefeatedState; // branch if some timer is above a certain point
    compare(a, 0x05);
    a = M(EnemyIntervalTimer + y);
    if (z)
        goto CheckToAnimateEnemy; // branch if found
    compare(x, 0x48); // check for cheep-cheep offset loaded

CheckToAnimateEnemy:
    if (!z)
        goto CheckDefeatedState; // unconditional branch
    writeData(0xec, a);
    a = 0x03; // set alternate state here
    x = 0xa2; // otherwise, set for mushroom retainer object instead
    if (c)
        goto CheckDefeatedState; // if so, leave the offset alone (use princess)
    compare(a, World8);
    a = M(WorldNumber); // are we on world 8?
    ++y; // residual instruction
    if (!z)
        goto CheckForSecondFrame; // which uses different code here, branch if not found
    compare(a, 0x15); // check for mushroom retainer/princess object
    y = 0x00;
    if (c)
        goto CheckDefeatedState;
    compare(a, 0x18); // branch if => $18
    if (z)
        goto CheckDefeatedState; // branch if podoboo
    compare(a, Podoboo);
    if (z)
        goto CheckDefeatedState; // branch if bullet bill (note both variants use $08 here)
    compare(a, 0x08);
    if (z)
        goto CheckDefeatedState; // branch if goomba
    compare(a, Goomba);
    a = M(0xef); // check for specific enemy objects

CheckForSecondFrame:
    if (!z)
        goto CheckDefeatedState; // branch if timing is off
    a &= M(EnemyAnimTimingBMask + y); // mask it (partly residual, one byte not ever used)
    a = M(FrameCounter); // load frame counter

CheckAnimationStop:
    x = a; // to animate various enemy objects
    a += 0x06; // add $06 to current enemy offset
    c = 0;
    a = x;
    if (!z)
        goto CheckDefeatedState; // if either condition true, branch
    a |= M(TimerControl);
    a &= BOOST_BINARY(10100000); // for d7 or d5, or check for timers stopped
    a = M(0xed); // check saved enemy state

CheckDefeatedState:
    writeData(0xec, y); // init saved value here
    --y;
    writeData(VerticalFlipFlag, y); // set vertical flip flag
    y = 0x01;
    if (!c)
        goto DrawEnemyObject; // branch if less
    compare(a, 0x04); // check for saved enemy object => $04
    a = M(0xef);
    if (z)
        goto DrawEnemyObject; // branch if not set
    a &= BOOST_BINARY(00100000); // for d5 set
    a = M(0xed); // check saved enemy state

DrawEnemyObject:
    if (!z)
        goto CheckForVerticalFlip; // for bullet bill, branch if not found
    compare(a, 0x08); // get saved enemy object and check
    a = M(0xef);
    y = M(Enemy_SprDataOffset + x); // get sprite data offset
    x = M(ObjectOffset); // get enemy object offset
    pushReturnIndex(510);
    goto DrawEnemyObjRow;
Return_510:
    pushReturnIndex(511);
    goto DrawEnemyObjRow;
Return_511: // into sprite data
    pushReturnIndex(512);
    goto DrawEnemyObjRow;
Return_512: // draw six tiles of data
    y = M(0xeb); // load sprite data offset

SkipToOffScrChk:
    goto SprObjectOffscrChk; // jump if found

CheckForVerticalFlip:
    x = a; // offset in X for next row
    a += 0x08; // if not selected objects or => $15, set
    c = 0;
    a = x;
    if (c)
        goto FlipEnemyVertically; // also branch if enemy object => $15
    compare(a, 0x15);
    if (z)
        goto FlipEnemyVertically; // branch for hammer bro or lakitu
    compare(a, Lakitu); // check saved enemy object for lakitu
    if (z)
        goto FlipEnemyVertically;
    compare(a, HammerBro); // check saved enemy object for hammer bro
    a = M(0xef);
    x = a; // give offset to X
    a = y;
    --y; // now go back to the Y coordinate offset
    --y;
    pushReturnIndex(513);
    goto DumpSixSpr;
Return_513: // in attribute bytes of enemy obj sprite data
    ++y; // increment two bytes so that we store the vertical flip
    ++y;
    a |= BOOST_BINARY(10000000); // set bit for vertical flip
    a = M(Sprite_Attributes + y); // get attributes of first sprite we dealt with
    if (z)
        goto CheckForESymmetry; // branch if not
    a = M(VerticalFlipFlag); // check if vertical flip flag is set here

FlipEnemyVertically:
    writeData(Sprite_Tilenumber + 16 + y, a);
    pla();
    writeData(Sprite_Tilenumber + 20 + y, a); // and save in third row
    pla(); // pull first or second row tiles from stack
    writeData(Sprite_Tilenumber + 4 + x, a);
    a = M(Sprite_Tilenumber + 20 + y);
    writeData(Sprite_Tilenumber + x, a); // with first or second row tiles
    a = M(Sprite_Tilenumber + 16 + y); // exchange third row tiles
    pha();
    a = M(Sprite_Tilenumber + 4 + x);
    pha(); // and save tiles to the stack
    a = M(Sprite_Tilenumber + x); // load first or second row tiles

CheckForESymmetry:
    goto SprObjectOffscrChk; // jump if found
    if (!z)
        goto ContES;
    compare(a, 0x05); // check for hammer bro object
    x = M(0xec); // get alternate enemy state
    a = M(0xef);
    if (!z)
        goto SkipToOffScrChk; // branch if so
    a = M(BowserGfxFlag); // are we drawing bowser at all?

ContES: // check for bloober object
    if (!z)
        goto CheckToMirrorLakitu; // branch if not an egg, otherwise
    compare(x, 0x05); // check spiny's state
    if (!z)
        goto ESRtnr; // branch closer if not found
    compare(a, Spiny); // check for spiny object
    if (z)
        goto MirrorEnemyGfx; // branch if either of three are found
    compare(a, Podoboo); // check for podoboo object
    if (z)
        goto MirrorEnemyGfx;
    compare(a, PiranhaPlant); // check for piranha plant object
    if (z)
        goto MirrorEnemyGfx;
    compare(a, Bloober);

ESRtnr: // check for princess/mushroom retainer object
    writeData(Sprite_Attributes + 20 + y, a); // note that palette bits were already set earlier
    a = 0x42; // set horizontal flip on bottom right sprite
    if (!z)
        goto SpnySC;
    compare(a, 0x15);

SpnySC: // if alternate enemy state set to 1 or 0, branch
    if (!c)
        goto CheckToMirrorLakitu;
    compare(x, 0x02);

MirrorEnemyGfx:
    a |= BOOST_BINARY(10000000); // otherwise set vertical flip
    if (!z)
        goto EggExc; // if alternate state not set to $05, branch
    compare(x, 0x05); // check for state used by spiny's egg
    a |= BOOST_BINARY(01000000); // set horizontal flip
    writeData(Sprite_Attributes + 16 + y, a);
    writeData(Sprite_Attributes + 8 + y, a); // in left sprite column of enemy object OAM data
    writeData(Sprite_Attributes + y, a); // save vertical flip, priority, and palette bits
    a &= BOOST_BINARY(10100011);
    a = M(Sprite_Attributes + y); // load attribute bits of first sprite
    if (!z)
        goto CheckToMirrorLakitu;
    a = M(BowserGfxFlag); // if enemy object is bowser, skip all of this

EggExc: // set bits of right sprite column
    writeData(Sprite_Attributes + 20 + y, a); // second and third row right sprites
    writeData(Sprite_Attributes + 12 + y, a); // store with horizontal and vertical flip in
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 16 + y, a); // second and third row left sprites
    writeData(Sprite_Attributes + 8 + y, a); // store bits with vertical flip in
    a |= BOOST_BINARY(10000000);
    a = M(Sprite_Attributes + 8 + y); // get second row left sprite attributes
    if (!z)
        goto CheckToMirrorLakitu; // branch if not $04
    compare(x, 0x04); // check alternate enemy state
    writeData(Sprite_Attributes + 20 + y, a);
    writeData(Sprite_Attributes + 12 + y, a); // of enemy object sprite data
    writeData(Sprite_Attributes + 4 + y, a);

CheckToMirrorLakitu:
    if (!c)
        goto SprObjectOffscrChk; // unconditional branch
    writeData(Sprite_Attributes + 8 + y, a); // preserve vertical flip and palette bits for left sprite
    a &= BOOST_BINARY(10000001);
    writeData(Sprite_Attributes + 12 + y, a); // otherwise set same for second row right sprite
    if (c)
        goto SprObjectOffscrChk; // branch if timer has not reached a certain range
    compare(x, 0x10);
    x = M(FrenzyEnemyTimer); // check timer
    writeData(Sprite_Attributes + 20 + y, a);
    a |= BOOST_BINARY(01000001); // in third row right sprite
    a = M(Sprite_Attributes + 20 + y); // set horizontal flip and palette bits
    writeData(Sprite_Attributes + 16 + y, a);
    a &= BOOST_BINARY(10000001); // in third row left sprite
    a = M(Sprite_Attributes + 16 + y); // save vertical flip and palette bits
    if (!z)
        goto NVFLak; // branch if vertical flip flag not set
    a = M(VerticalFlipFlag);
    if (!z)
        goto CheckToMirrorJSpring; // branch if not found
    compare(a, Lakitu);
    a = M(0xef); // check for lakitu enemy object

NVFLak: // get first row left sprite attributes
    writeData(Sprite_Attributes + 4 + y, a); // note that vertical flip is left as-is
    a |= BOOST_BINARY(01000001); // set horizontal flip and palette bits
    a = M(Sprite_Attributes + 4 + y); // get first row right sprite attributes
    writeData(Sprite_Attributes + y, a); // save vertical flip and palette bits
    a &= BOOST_BINARY(10000001);
    a = M(Sprite_Attributes + y);

CheckToMirrorJSpring:
    writeData(Sprite_Attributes + 20 + y, a); // for second and third row right sprites
    writeData(Sprite_Attributes + 12 + y, a); // set, in addition to those, horizontal flip
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 16 + y, a); // second and third row left sprites
    writeData(Sprite_Attributes + 8 + y, a); // set vertical flip and palette bits of 
    a = 0x82;
    if (!c)
        goto SprObjectOffscrChk; // branch if not jumpspring object at all
    compare(a, 0x18);
    a = M(0xef); // check for jumpspring object (any frame)

SprObjectOffscrChk:
    pushReturnIndex(514);
    goto MoveESprColOffscreen;
Return_514: // and move them offscreen
    a = 0x04; // set for right column sprites
    if (!c)
        goto LcChk; // branch if not set
    pha(); // save to stack
    a >>= 1; // which puts d2 into carry
    a >>= 1; // shift three times to the right
    a >>= 1;
    a = M(Enemy_OffscreenBits); // check offscreen information
    x = M(ObjectOffset); // get enemy buffer offset

LcChk: // get from stack
    pushReturnIndex(515);
    goto MoveESprColOffscreen;
Return_515: // move them offscreen
    a = 0x00; // set for left column sprites,
    if (!c)
        goto Row3C; // branch if not set
    pha(); // save to stack
    a >>= 1; // move d3 to carry
    pla();

Row3C: // get from stack again
    pushReturnIndex(516);
    goto MoveESprRowOffscreen;
Return_516: // and move them offscreen
    a = 0x10; // set for third row of sprites
    if (!c)
        goto Row23C; // branch if carry not set
    pha(); // save to stack again
    a >>= 1;
    a >>= 1; // move d5 to carry this time
    pla();

Row23C: // get from stack
    pushReturnIndex(517);
    goto MoveESprRowOffscreen;
Return_517: // move them offscreen
    a = 0x08; // set for second and third rows
    if (!c)
        goto AllRowC;
    pha(); // save to stack
    a >>= 1; // move d6 into carry
    pla();

AllRowC: // get from stack once more
    pushReturnIndex(518);
    goto EraseEnemyObject;
Return_518: // what it says
    if (!z)
        goto ExEGHandler;
    compare(a, 0x02); // if not yet past the bottom of the screen, branch
    a = M(Enemy_Y_HighPos + x); // check high byte of vertical position
    if (z)
        goto ExEGHandler; // skip this part if found, we do not want to erase podoboo!
    compare(a, Podoboo); // check enemy identifier for podoboo
    a = M(Enemy_ID + x);
    pushReturnIndex(519);
    goto MoveESprRowOffscreen;
Return_519: // move all sprites offscreen (A should be 0 by now)
    if (!c)
        goto ExEGHandler;
    a >>= 1; // move d7 into carry
    pla();

ExEGHandler:
    goto Return;

//------------------------------------------------------------------------

DrawEnemyObjRow:
    a = M(EnemyGraphicsTable + 1 + x);
    writeData(0x00, a);
    a = M(EnemyGraphicsTable + x); // load two tiles of enemy graphics

DrawOneSpriteRow:
    goto DrawSpriteObject; // draw them
    writeData(0x01, a);

MoveESprRowOffscreen:
    goto DumpTwoSpr; // move first row of sprites offscreen
    a = 0xf8;
    y = a; // use as offset
    a += M(Enemy_SprDataOffset + x);
    c = 0; // add A to enemy object OAM data offset

MoveESprColOffscreen:
    goto Return;

//------------------------------------------------------------------------
    writeData(Sprite_Data + 16 + y, a); // move third row sprite in column offscreen
    pushReturnIndex(520);
    goto MoveColOffscreen;
Return_520: // move first and second row sprites in column offscreen
    y = a; // use as offset
    a += M(Enemy_SprDataOffset + x);
    c = 0; // add A to enemy object OAM data offset

DrawBlock:
    x = 0x00; // reset X for use as offset to tile data
    y = M(Block_SprDataOffset + x); // get sprite data offset
    writeData(0x03, a); // set horizontal flip bit here (will not be used)
    a >>= 1;
    writeData(0x04, a); // set attribute byte here
    a = 0x03;
    writeData(0x05, a); // store here
    a = M(Block_Rel_XPos); // get relative horizontal coordinate of block object
    writeData(0x02, a); // store here
    a = M(Block_Rel_YPos); // get relative vertical coordinate of block object

DBlkLoop: // get left tile number
    writeData(Sprite_Tilenumber + 4 + y, a); // and replace then with lineless brick tiles
    writeData(Sprite_Tilenumber + y, a); // otherwise remove brick tiles with lines
    a = 0x86;
    if (z)
        goto ChkRep; // if found, branch to next part
    compare(a, 0x01); // check for ground level type area
    a = M(AreaType);
    y = M(Block_SprDataOffset + x); // get sprite data offset
    x = M(ObjectOffset); // get block object offset
    if (!z)
        goto DBlkLoop; // and loop back until all four sprites are done
    compare(x, 0x04); // check incremented offset
    pushReturnIndex(521);
    goto DrawOneSpriteRow;
Return_521: // do sub to write tile numbers to first row of sprites
    a = M(DefaultBlockObjTiles + 1 + x); // get right tile number
    writeData(0x00, a); // set here
    a = M(DefaultBlockObjTiles + x);

ChkRep: // check replacement metatile
    a >>= 1; // otherwise set to $01
    if (z)
        goto SetBFlip; // if found, use current palette bits
    --x; // check for ground level type area again
    x = M(AreaType);
    a = 0x03; // set palette bits
    --y; // return Y to original offset
    pushReturnIndex(522);
    goto DumpFourSpr;
Return_522: // do sub to dump into all four sprites
    ++y; // increment Y to write to tile bytes
    a = 0x87; // set A for used block tile
    if (!z)
        goto BlkOffscr; // branch ahead to use current graphics
    compare(a, 0xc4); // if not used block metatile, then
    a = M(Block_Metatile + x);

SetBFlip: // put block object offset back in X
    writeData(Sprite_Attributes + 8 + y, a); // set vertical flip bit for third sprite
    a &= BOOST_BINARY(10000011);
    writeData(Sprite_Attributes + 12 + y, a); // set both flip bits for fourth sprite
    a |= BOOST_BINARY(10000000);
    writeData(Sprite_Attributes + 4 + y, a); // set horizontal flip bit for second sprite
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + y, a); // store attribute byte as-is in first sprite
    x = M(ObjectOffset);

BlkOffscr: // get offscreen bits for block object
    writeData(Sprite_Y_Position + 12 + y, a);
    writeData(Sprite_Y_Position + 4 + y, a); // on the right side
    a = 0xf8; // move offscreen two OAMs
    if (z)
        goto PullOfsB; // if not set, branch, otherwise move sprites offscreen
    a &= BOOST_BINARY(00000100); // check to see if d2 in offscreen bits are set
    pha(); // save to stack
    a = M(Block_OffscreenBits);

PullOfsB: // pull offscreen bits from stack
    pla();

ChkLeftCo: // check to see if d3 in offscreen bits are set
    if (z)
        goto ExDBlk; // if not set, branch, otherwise move sprites offscreen
    a &= BOOST_BINARY(00001000);

MoveColOffscreen:
    writeData(Sprite_Y_Position + 8 + y, a); // if branched here from enemy graphics handler)
    writeData(Sprite_Y_Position + y, a); // on the left side (or two rows of enemy on either side
    a = 0xf8; // move offscreen two OAMs

ExDBlk:
    goto Return;

//------------------------------------------------------------------------

DrawBrickChunks:
    a = 0x84; // and set tile number for brick chunks
    writeData(0x00, a);
    a = 0x03; // otherwise set different palette bits
    if (z)
        goto DChunks; // use palette and tile number assigned
    compare(y, 0x05); // if end-of-level routine running,
    y = M(GameEngineSubroutine);
    a = 0x75; // set tile number for ball (something residual, likely)
    writeData(0x00, a);
    a = 0x02; // set palette bits here

DChunks: // get OAM data offset
    pushReturnIndex(523);
    goto DumpTwoSpr;
Return_523: // otherwise move top sprites offscreen
    a = 0xf8;
    if (!c)
        goto ChnkOfs; // if d7 not set, branch to last part
    a <<= 1; // shift d7 into carry
    a = M(Block_OffscreenBits); // get offscreen bits again
    pushReturnIndex(524);
    goto ChkLeftCo;
Return_524: // do sub to move left half of sprites offscreen if necessary
    a = M(Block_OffscreenBits); // get offscreen bits for block object
    writeData(Sprite_X_Position + 12 + y, a); // save into X coordinate of fourth sprite
    a += 0x06; // plus 6 pixels to position fourth brick chunk correctly
    a += M(0x00); // add original relative position to result
    a -= M(Block_Rel_XPos + 1); // get difference of relative positions of original - current
    c = 1;
    a = M(0x00); // use original relative horizontal position
    writeData(Sprite_X_Position + 8 + y, a); // save into X coordinate of third sprite
    a = M(Block_Rel_XPos + 1); // get second block object's relative horizontal coordinate
    writeData(Sprite_Y_Position + 12 + y, a); // dump into Y coordinates of third and fourth sprites
    writeData(Sprite_Y_Position + 8 + y, a);
    a = M(Block_Rel_YPos + 1); // get second block object's relative vertical coordinate
    writeData(Sprite_X_Position + 4 + y, a); // save into X coordinate of second sprite
    a += 0x06; // plus 6 pixels to position second brick chunk correctly
    a += M(0x00); // add original relative position to result
    a -= M(Block_Rel_XPos); // get difference of relative positions of original - current
    c = 1;
    writeData(0x00, a); // store result as relative horizontal coordinate of original
    a -= M(ScreenLeft_X_Pos); // subtract coordinate of left side from original coordinate
    c = 1;
    a = M(Block_Orig_XPos + x); // get original horizontal coordinate
    writeData(Sprite_X_Position + y, a); // save into X coordinate of first sprite
    a = M(Block_Rel_XPos); // get first block object's relative horizontal coordinate
    pushReturnIndex(525);
    goto DumpTwoSpr;
Return_525: // do sub to dump current Y coordinate into two sprites
    a = M(Block_Rel_YPos); // get first block object's relative vertical coordinate
    --y; // decrement offset to Y coordinate
    --y;
    pushReturnIndex(526);
    goto DumpFourSpr;
Return_526: // do sub to dump attribute data into all four sprites
    ++y; // increment offset for attribute bytes
    a |= M(0x00); // add palette bits
    a &= 0xc0; // get what was originally d3-d2 of low nybble
    a <<= 1;
    a <<= 1; // move low nybble to high
    a <<= 1;
    a <<= 1;
    a = M(FrameCounter); // get frame counter
    pushReturnIndex(527);
    goto DumpFourSpr;
Return_527: // do sub to dump tile number into all four sprites
    ++y; // increment to start with tile bytes in OAM
    y = M(Block_SprDataOffset + x);

ChnkOfs: // if relative position on left side of screen,
    writeData(Sprite_Y_Position + 12 + y, a);
    writeData(Sprite_Y_Position + 4 + y, a);
    a = 0xf8; // otherwise move right half of sprites offscreen
    if (!c)
        goto ExBCDr; // branch to leave if less
    compare(a, M(Sprite_X_Position + 4 + y)); // to right-side X coordinate
    a = M(Sprite_X_Position + y); // otherwise compare left-side X coordinate
    if (!n)
        goto ExBCDr; // go ahead and leave
    a = M(0x00);

ExBCDr: // leave
    goto Return;

//------------------------------------------------------------------------

DrawFireball:
    writeData(Sprite_X_Position + y, a); // store as sprite X coordinate, then do shared code
    a = M(Fireball_Rel_XPos); // get relative horizontal coordinate
    writeData(Sprite_Y_Position + y, a); // store as sprite Y coordinate
    a = M(Fireball_Rel_YPos); // get relative vertical coordinate
    y = M(FBall_SprDataOffset + x); // get fireball's sprite data offset

DrawFirebar:
    a |= BOOST_BINARY(11000000); // otherwise flip both ways every eight frames
    if (!c)
        goto FireA; // if last bit shifted out was not set, skip this
    a = 0x02; // load value $02 to set palette in attrib byte
    a >>= 1;
    a >>= 1; // divide by four again
    pla(); // get from stack
    writeData(Sprite_Tilenumber + y, a); // thus tile changes every four frames
    a ^= 0x64; // set either tile $64 or $65 as fireball tile
    a &= 0x01; // mask out all but last bit
    pha(); // save result to stack
    a >>= 1;
    a >>= 1; // divide by four
    a = M(FrameCounter); // get frame counter

FireA: // store attribute byte and leave
    goto Return;

//------------------------------------------------------------------------
    writeData(Sprite_Attributes + y, a);

DrawExplosion_Fireball:
    if (c)
        goto KillFireBall; // branch if so, otherwise continue to draw explosion
    compare(a, 0x03); // check to see if time to kill fireball
    a &= BOOST_BINARY(00000111); // mask out all but d3-d1
    a >>= 1; // divide by 2
    ++M(Fireball_State + x); // increment state for next frame
    a = M(Fireball_State + x); // load fireball state
    y = M(Alt_SprDataOffset + x); // get OAM data offset of alternate sort for fireball's explosion

DrawExplosion_Fireworks:
    goto Return; // we are done

//------------------------------------------------------------------------
    writeData(Sprite_Attributes + 12 + y, a); // set both flips for fourth sprite
    a = 0xc2;
    writeData(Sprite_Attributes + 8 + y, a); // set horizontal flip for third sprite
    a = 0x42;
    writeData(Sprite_Attributes + 4 + y, a); // set vertical flip for second sprite
    a = 0x82;
    writeData(Sprite_Attributes + y, a); // set no flip at all for first sprite
    a = 0x02; // set palette attributes for all sprites, but
    writeData(Sprite_X_Position + 12 + y, a);
    writeData(Sprite_X_Position + 8 + y, a);
    a += 0x08; // for third and fourth sprites
    c = 0; // add eight pixels horizontally
    writeData(Sprite_X_Position + 4 + y, a);
    writeData(Sprite_X_Position + y, a);
    a -= 0x04; // for first and second sprites
    c = 1; // subtract four pixels horizontally
    a = M(Fireball_Rel_XPos); // get relative horizontal coordinate
    writeData(Sprite_Y_Position + 12 + y, a);
    writeData(Sprite_Y_Position + 4 + y, a);
    a += 0x08; // for second and fourth sprites
    c = 0; // add eight pixels vertically
    writeData(Sprite_Y_Position + 8 + y, a);
    writeData(Sprite_Y_Position + y, a);
    a -= 0x04; // for first and third sprites
    c = 1; // subtract four pixels vertically
    a = M(Fireball_Rel_YPos); // get relative vertical coordinate
    x = M(ObjectOffset); // return enemy object buffer offset to X
    --y; // decrement Y so we have the proper offset again
    pushReturnIndex(528);
    goto DumpFourSpr;
Return_528: // and dump into tile number part of sprite data
    ++y; // increment Y (contains sprite data offset)
    a = M(ExplosionTiles + x); // get tile number using offset
    x = a; // use whatever's in A for offset

KillFireBall:
    goto Return;

//------------------------------------------------------------------------
    writeData(Fireball_State + x, a);
    a = 0x00; // clear fireball state to kill it

DrawSmallPlatform:
    a = 0xf8; // otherwise move first three sprites offscreen
    if (c)
        goto TopSP; // do not mess with it
    compare(x, 0x20); // if vertical coordinate below status bar,
    pha(); // save to stack
    x = a;
    a = M(Enemy_Y_Position + x); // get vertical coordinate
    writeData(Sprite_X_Position + 20 + y, a);
    writeData(Sprite_X_Position + 8 + y, a); // dump into third and sixth sprites
    a += 0x08; // add eight more pixels
    c = 0;
    writeData(Sprite_X_Position + 16 + y, a);
    writeData(Sprite_X_Position + 4 + y, a); // dump into second and fifth sprites
    a += 0x08; // add eight pixels
    c = 0;
    writeData(Sprite_X_Position + 12 + y, a); // dump as X coordinate into first and fourth sprites
    writeData(Sprite_X_Position + y, a);
    a = M(Enemy_Rel_XPos); // get relative horizontal coordinate
    --y;
    --y; // decrement for original offset
    pushReturnIndex(529);
    goto DumpSixSpr;
Return_529: // dump attributes into all six sprites
    a = 0x02; // load palette controls
    ++y; // increment offset for attributes
    pushReturnIndex(530);
    goto DumpSixSpr;
Return_530: // dump tile number into all six sprites
    ++y; // increment offset for tile numbers
    a = 0x5b; // load tile number for small platforms
    y = M(Enemy_SprDataOffset + x); // get OAM data offset

TopSP: // dump vertical coordinate into Y coordinates
    a = 0xf8; // otherwise move last three sprites offscreen
    if (c)
        goto BotSP; // then do not change altered coordinate
    compare(x, 0x20); // if below status bar (taking wrap into account)
    x = a;
    a += 0x80; // add 128 pixels
    c = 0;
    pla(); // pull from stack
    pushReturnIndex(531);
    goto DumpThreeSpr;
Return_531:

BotSP: // dump vertical coordinate + 128 pixels
    writeData(Sprite_Y_Position + 12 + y, a);
    writeData(Sprite_Y_Position + y, a); // fourth sprites offscreen
    a = 0xf8; // if d3 was set, move first and
    if (z)
        goto SOfs;
    a &= BOOST_BINARY(00001000); // check d3
    pha(); // save to stack
    a = M(Enemy_OffscreenBits); // get offscreen bits
    writeData(Sprite_Y_Position + 20 + y, a);
    writeData(Sprite_Y_Position + 16 + y, a); // into Y coordinates
    writeData(Sprite_Y_Position + 12 + y, a);

SOfs: // move out and back into stack
    writeData(Sprite_Y_Position + 16 + y, a);
    writeData(Sprite_Y_Position + 4 + y, a); // fifth sprites offscreen
    a = 0xf8; // if d2 was set, move second and
    if (z)
        goto SOfs2;
    a &= BOOST_BINARY(00000100); // check d2
    pha();
    pla();

SOfs2: // get from stack
    writeData(Sprite_Y_Position + 20 + y, a);
    writeData(Sprite_Y_Position + 8 + y, a); // sixth sprites offscreen
    a = 0xf8; // if d1 was set, move third and
    if (z)
        goto ExSPl;
    a &= BOOST_BINARY(00000010); // check d1
    pla();

ExSPl: // get enemy object offset and leave
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);

DrawBubble:
    writeData(Sprite_Attributes + y, a); // set attribute byte
    a = 0x02;
    writeData(Sprite_Tilenumber + y, a); // put air bubble tile into OAM data
    a = 0x74;
    writeData(Sprite_Y_Position + y, a); // store as Y coordinate here
    a = M(Bubble_Rel_YPos); // get relative vertical coordinate
    writeData(Sprite_X_Position + y, a); // store as X coordinate here
    a = M(Bubble_Rel_XPos); // get relative horizontal coordinate
    y = M(Bubble_SprDataOffset + x); // get air bubble's OAM data offset
    if (!z)
        goto ExDBub; // if bit set, branch to leave
    a &= BOOST_BINARY(00001000);
    a = M(Bubble_OffscreenBits); // check air bubble's offscreen bits
    if (!z)
        goto ExDBub;
    --y; // not within screen, skip all of this
    y = M(Player_Y_HighPos); // if player's vertical high position

ExDBub: // leave
    goto Return;

//------------------------------------------------------------------------

PlayerGfxHandler:
    if (c)
        goto ExPGH; // to leave on every other frame (when d0 is set)
    a >>= 1; // otherwise check frame counter and branch
    a = M(FrameCounter);
    if (z)
        goto CntPl; // not set, skip checkpoint and continue code
    a = M(InjuryTimer); // if player's injured invincibility timer

CntPl: // if executing specific game engine routine,
    ++y;
    ++y;
    ++y; // otherwise move to next OAM data
    ++y;
    if (c)
        goto SwimKT; // if player facing to the right, use current offset
    a >>= 1;
    a = M(PlayerFacingDir); // get player's facing direction
    y = M(Player_SprDataOffset); // get player sprite data offset
    x = a; // initialize X to zero
    if (!z)
        goto ExPGH; // eighth frame), and branch if set to leave
    a &= BOOST_BINARY(00000100); // check frame counter for d2 set (8 frames every
    a = M(FrameCounter);
    pushReturnIndex(532);
    goto FindPlayerAction;
Return_532: // otherwise jump and return
    if (z)
        goto FindPlayerAction; // branch and do not return
    compare(a, 0x00); // if player status normal,
    a = M(Player_State);
    if (z)
        goto FindPlayerAction; // different part, do not return
    y = M(SwimmingFlag); // if swimming flag set, branch to
    if (!z)
        goto DoChangeSize; // then branch to some other code
    a = M(PlayerChangeSizeFlag); // if grow/shrink flag set
    if (z)
        goto PlayerKilled;
    compare(a, 0x0b); // branch ahead to some other part
    a = M(GameEngineSubroutine);

SwimKT: // check player's size
    ++x; // otherwise increment X for second tile
    if (z)
        goto ExPGH; // if spr7/spr8 tile number = value, branch to leave
    compare(a, M(SwimTileRepOffset)); // against tile number in player graphics table
    a = M(Sprite_Tilenumber + 24 + y); // check tile number of seventh/eighth sprite
    if (z)
        goto BigKTS; // if big, use first tile
    a = M(PlayerSize);

BigKTS: // overwrite tile number in sprite 7/8
    writeData(Sprite_Tilenumber + 24 + y, a); // to animate player's feet when swimming
    a = M(SwimKickTileNum + x);

ExPGH: // then leave
    goto Return;

//------------------------------------------------------------------------

FindPlayerAction:
    goto PlayerGfxProcessing; // draw player, then process for fireball throwing
    pushReturnIndex(533);
    goto ProcessPlayerAction;
Return_533: // find proper offset to graphics table by player's actions

DoChangeSize:
    goto PlayerGfxProcessing; // draw player, then process for fireball throwing
    pushReturnIndex(534);
    goto HandleChangeSize;
Return_534: // find proper offset to graphics table for grow/shrink

PlayerKilled:
    a = M(PlayerGfxTblOffsets + y); // get offset to graphics table
    y = 0x0e; // load offset for player killed

PlayerGfxProcessing:
    --y; // otherwise set to update only three sprite rows
    if (z)
        goto SUpdR; // if no speed or button press, branch using set value in Y
    a |= M(Left_Right_Buttons); // check for horizontal speed or left/right button press
    a = M(Player_X_Speed);
    y = 0x04; // set to update four sprite rows by default
    writeData(PlayerGfxOffset, a); // store it for use later
    a = M(PlayerGfxTblOffsets + y); // get offset to graphics table
    y = 0x07; // load offset for throwing
    writeData(FireballThrowingTimer, a); // otherwise store animation timer into fireball throw timer
    if (c)
        goto PlayerOffscreenChk; // if animation frame timer => fireball throw timer skip to end
    writeData(FireballThrowingTimer, y); // initialize fireball throw timer
    compare(a, M(FireballThrowingTimer)); // compare to fireball throw timer
    a = M(PlayerAnimTimer); // get animation frame timer
    y = 0x00; // set value to initialize by default
    if (z)
        goto PlayerOffscreenChk; // if fireball throw timer not set, skip to the end
    a = M(FireballThrowingTimer);
    pushReturnIndex(535);
    goto ChkForPlayerAttrib;
Return_535: // set horizontal flip bits as necessary
    pushReturnIndex(536);
    goto RenderPlayerSub;
Return_536: // draw player based on offset loaded
    a = 0x04;
    writeData(PlayerGfxOffset, a); // store offset to graphics table here

SUpdR: // save in A for use
    pushReturnIndex(537);
    goto RenderPlayerSub;
Return_537: // in sub, draw player object again
    a = y;

PlayerOffscreenChk:
    y = a; // set as offset here
    a += 0x18; // add 24 bytes to start at bottom row
    c = 0;
    a = M(Player_SprDataOffset); // get player's sprite data offset
    x = 0x03; // check all four rows of player sprites
    writeData(0x00, a); // store here
    a >>= 1;
    a >>= 1;
    a >>= 1; // move vertical bits to low nybble
    a >>= 1;
    a = M(Player_OffscreenBits); // get player's offscreen bits

PROfsLoop: // load offscreen Y coordinate just in case
    pushReturnIndex(538);
    goto DumpTwoSpr;
Return_538: // otherwise dump offscreen Y coordinate into sprite data
    if (!c)
        goto NPROffscr; // if bit not set, skip, do not move sprites
    M(0x00) >>= 1; // shift bit into carry
    a = 0xf8;

NPROffscr:
    goto Return; // then we are done!

//------------------------------------------------------------------------
    if (!n)
        goto PROfsLoop; // do this until all sprite rows are checked
    --x; // decrement row counter
    y = a;
    a -= 0x08; // next row up
    c = 1; // subtract eight bytes to do
    a = y;

DrawPlayer_Intermediate:
    x = 0x05; // store data into zero page memory

PIntLoop: // load data to display player as he always
    goto Return;

//------------------------------------------------------------------------
    writeData(Sprite_Attributes + 32, a); // store and leave
    a |= BOOST_BINARY(01000000); // set horizontal flip bit for bottom-right sprite
    a = M(Sprite_Attributes + 36); // get empty sprite attributes
    pushReturnIndex(539);
    goto DrawPlayerLoop;
Return_539: // draw player accordingly
    y = 0x04; // load sprite data offset
    x = 0xb8; // load offset for small standing
    if (!n)
        goto PIntLoop; // do this until all data is loaded
    --x;
    writeData(0x02 + x, a); // appears on world/lives display
    a = M(IntermediatePlayerData + x);

RenderPlayerSub:
    y = M(Player_SprDataOffset); // get player's sprite data offset
    x = M(PlayerGfxOffset); // load graphics table offset
    writeData(0x04, a); // store player's sprite attributes
    a = M(Player_SprAttrib);
    writeData(0x03, a); // store player's facing direction
    a = M(PlayerFacingDir);
    writeData(0x02, a); // store player's vertical position
    a = M(Player_Rel_YPos);
    writeData(0x05, a); // store it here also
    writeData(Player_Pos_ForScroll, a); // store player's relative horizontal position
    a = M(Player_Rel_XPos);
    writeData(0x07, a); // store number of rows of sprites to draw

DrawPlayerLoop:
    goto Return;

//------------------------------------------------------------------------
    if (!z)
        goto DrawPlayerLoop; // do this until all rows are drawn
    --M(0x07); // decrement rows of sprites to draw
    pushReturnIndex(540);
    goto DrawOneSpriteRow;
Return_540:
    a = M(PlayerGraphicsTable + 1 + x); // now load right side
    writeData(0x00, a);
    a = M(PlayerGraphicsTable + x); // load player's left side

ProcessPlayerAction:
    goto NonAnimatedActs; // go to get offset to graphics table
    y = 0x00; // otherwise load offset for jumping
    if (!z)
        goto NonAnimatedActs; // if set, branch to get offset for graphics table
    a = M(CrouchingFlag); // get crouching flag
    y = 0x06; // load offset for crouching
    if (!z)
        goto ActionSwimming; // if swimming flag set, branch elsewhere
    a = M(SwimmingFlag);
    if (!z)
        goto ProcOnGroundActs; // if not jumping, branch here
    compare(a, 0x01);
    if (z)
        goto ActionFalling; // if falling, branch here
    compare(a, 0x02);
    if (z)
        goto ActionClimbing; // if climbing, branch here
    compare(a, 0x03);
    a = M(Player_State); // get player's state

ProcOnGroundActs:
    ++y; // otherwise increment to skid offset ($03)
    if (!z)
        goto ActionWalkRun; // if moving direction = facing direction, branch, don't skid
    a &= M(PlayerFacingDir); // and facing direction are the same
    a = M(Player_MovingDir); // otherwise check to see if moving direction
    if (!c)
        goto ActionWalkRun; // if less than a certain amount, branch, too slow to skid
    compare(a, 0x09);
    a = M(Player_XSpeedAbsolute); // load walking/running speed
    if (z)
        goto NonAnimatedActs; // if no speed or buttons pressed, use standing offset
    a |= M(Left_Right_Buttons); // and left/right controller bits
    a = M(Player_X_Speed); // check player's horizontal speed
    y = 0x02; // load offset for standing
    if (!z)
        goto NonAnimatedActs; // if set, branch to get offset for graphics table
    a = M(CrouchingFlag); // get crouching flag
    y = 0x06; // load offset for crouching

NonAnimatedActs:
    goto Return;

//------------------------------------------------------------------------
    a = M(PlayerGfxTblOffsets + y); // load offset to graphics table using size as offset
    writeData(PlayerAnimCtrl, a); // initialize animation frame control
    a = 0x00;
    pushReturnIndex(541);
    goto GetGfxOffsetAdder;
Return_541: // do a sub here to get offset adder for graphics table

ActionFalling:
    goto GetCurrentAnimOffset; // execute instructions for falling state
    pushReturnIndex(542);
    goto GetGfxOffsetAdder;
Return_542: // get offset to graphics table
    y = 0x04; // load offset for walking/running

ActionWalkRun:
    goto FourFrameExtent; // execute instructions for normal state
    pushReturnIndex(543);
    goto GetGfxOffsetAdder;
Return_543: // get offset to graphics table
    y = 0x04; // load offset for walking/running

ActionClimbing:
    goto ThreeFrameExtent; // then skip ahead to more code
    pushReturnIndex(544);
    goto GetGfxOffsetAdder;
Return_544: // otherwise get offset for graphics table
    if (z)
        goto NonAnimatedActs; // if no speed, branch, use offset as-is
    a = M(Player_Y_Speed); // check player's vertical speed
    y = 0x05; // load offset for climbing

ActionSwimming:
    if (c)
        goto FourFrameExtent; // branch to same place if A button pressed
    a <<= 1; // check for A button pressed
    a = M(A_B_Buttons);
    if (!z)
        goto FourFrameExtent; // if any one of these set, branch ahead
    a |= M(PlayerAnimCtrl); // and animation frame control
    a = M(JumpSwimTimer); // check jump/swim timer
    pushReturnIndex(545);
    goto GetGfxOffsetAdder;
Return_545:
    y = 0x01; // load offset for swimming

GetCurrentAnimOffset:
    goto GetOffsetFromAnimCtrl; // jump to get proper offset to graphics table
    a = M(PlayerAnimCtrl); // get animation frame control

FourFrameExtent:
    goto AnimationControl; // jump to get offset and animate player object
    a = 0x03; // load upper extent for frame control

ThreeFrameExtent:
    a = 0x02; // load upper extent for frame control for climbing

AnimationControl:
    a = 0x00; // otherwise initialize frame control
    if (!c)
        goto SetAnimC; // if frame control + 1 < upper extent, use as next
    compare(a, M(0x00)); // compare to upper extent
    a += 0x01;
    c = 0; // add one to animation frame control
    a = M(PlayerAnimCtrl);
    writeData(PlayerAnimTimer, a); // and set timer accordingly
    a = M(PlayerAnimTimerSet); // get animation frame timer amount
    if (!z)
        goto ExAnimC; // branch if not expired
    a = M(PlayerAnimTimer); // load animation frame timer
    pha(); // save offset to stack
    pushReturnIndex(546);
    goto GetCurrentAnimOffset;
Return_546: // get proper offset to graphics table
    writeData(0x00, a); // store upper extent here

SetAnimC: // store as new animation frame control
    writeData(PlayerAnimCtrl, a);

ExAnimC: // get offset to graphics table from stack and leave
    goto Return;

//------------------------------------------------------------------------
    pla();

GetGfxOffsetAdder:
    y = a;
    a += 0x08; // for small player
    c = 0; // otherwise add eight bytes to offset
    a = y; // for big player
    if (z)
        goto SzOfs; // if player big, use current offset as-is
    a = M(PlayerSize); // get player's size

SzOfs: // go back
    goto Return;

//------------------------------------------------------------------------

HandleChangeSize:
    writeData(PlayerChangeSizeFlag, y); // and animation frame control
    y = 0x00; // otherwise initialize both grow/shrink flag
    if (!c)
        goto CSzNext; // if not there yet, skip ahead to use
    compare(y, 0x0a); // check for preset upper extent
    ++y; // increment frame control
    if (!z)
        goto GorSLog; // fourth frame, otherwise branch ahead
    a &= BOOST_BINARY(00000011); // get frame counter and execute this code every
    a = M(FrameCounter);
    y = M(PlayerAnimCtrl); // get animation frame control

CSzNext: // store proper frame control
    writeData(PlayerAnimCtrl, y);

GorSLog: // get player's size
    y = 0x0f; // load offset for player growing
    a = M(ChangeSizeOffsetAdder + y); // get offset adder based on frame control as offset
    if (!z)
        goto ShrinkPlayer; // if player small, skip ahead to next part
    a = M(PlayerSize);

GetOffsetFromAnimCtrl:
    goto Return; // and return with result in A

//------------------------------------------------------------------------
    a += M(PlayerGfxTblOffsets + y); // add to offset to graphics table
    a <<= 1; // to add to our offset
    a <<= 1; // by eight to get proper amount
    a <<= 1; // multiply animation frame control

ShrinkPlayer:
    y = 0x01; // otherwise load offset for big player swimming
    if (!z)
        goto ShrPlF; // and branch to use offset if nonzero
    a = M(ChangeSizeOffsetAdder + x); // get what would normally be offset adder
    y = 0x09; // load offset for small player swimming
    x = a; // to draw the player shrinking
    a += 0x0a; // this thing apparently uses two of the swimming frames
    c = 0;
    a = y; // add ten bytes to frame control as offset

ShrPlF: // get offset to graphics table based on offset loaded
    goto Return; // and leave

//------------------------------------------------------------------------
    a = M(PlayerGfxTblOffsets + y);

ChkForPlayerAttrib:
    if (!z)
        goto ExPlyrAt; // if none of these, branch to leave
    compare(a, 0xc8);
    if (z)
        goto C_S_IGAtt;
    compare(a, 0xc0); // fourth row OAM attributes only
    if (z)
        goto C_S_IGAtt; // go ahead and execute code to change 
    compare(a, 0xb8); // or intermediate growing offset,
    if (z)
        goto C_S_IGAtt; // if crouch offset, either standing offset,
    compare(a, 0x50);
    a = M(PlayerGfxOffset); // get graphics table offset
    if (z)
        goto KilledAtt; // branch to change third and fourth row OAM attributes
    compare(a, 0x0b); // if executing specific game engine routine,
    a = M(GameEngineSubroutine);
    y = M(Player_SprDataOffset); // get sprite data offset

KilledAtt:
    writeData(Sprite_Attributes + 20 + y, a); // sprite in the third row
    a |= BOOST_BINARY(01000000); // set horizontal flip bit for second
    a &= BOOST_BINARY(00111111);
    a = M(Sprite_Attributes + 20 + y);
    writeData(Sprite_Attributes + 16 + y, a); // for third row sprites and save
    a &= BOOST_BINARY(00111111); // mask out horizontal and vertical flip bits
    a = M(Sprite_Attributes + 16 + y);

C_S_IGAtt:
    writeData(Sprite_Attributes + 28 + y, a); // sprite in the fourth row
    a |= BOOST_BINARY(01000000); // set horizontal flip bit for second
    a &= BOOST_BINARY(00111111);
    a = M(Sprite_Attributes + 28 + y);
    writeData(Sprite_Attributes + 24 + y, a); // for fourth row sprites and save
    a &= BOOST_BINARY(00111111); // mask out horizontal and vertical flip bits
    a = M(Sprite_Attributes + 24 + y);

ExPlyrAt: // leave
    goto Return;

//------------------------------------------------------------------------

RelativePlayerPosition:
    goto RelWOfs; // get the coordinates
    y = 0x00; // routine to correspond to player object
    x = 0x00; // set offsets for relative cooordinates

RelativeBubblePosition:
    goto RelWOfs; // get the coordinates
    y = 0x03;
    pushReturnIndex(547);
    goto GetProperObjOffset;
Return_547: // modify X to get proper air bubble offset
    y = 0x01; // set for air bubble offsets

RelativeFireballPosition:
    y = 0x02;
    pushReturnIndex(548);
    goto GetProperObjOffset;
Return_548: // modify X to get proper fireball offset
    y = 0x00; // set for fireball offsets

RelWOfs: // get the coordinates
    goto Return; // leave

//------------------------------------------------------------------------
    x = M(ObjectOffset); // return original offset
    pushReturnIndex(549);
    goto GetObjRelativePosition;
Return_549:

RelativeMiscPosition:
    goto RelWOfs; // get the coordinates
    y = 0x06;
    pushReturnIndex(550);
    goto GetProperObjOffset;
Return_550: // modify X to get proper misc object offset
    y = 0x02; // set for misc object offsets

RelativeEnemyPosition:
    goto VariableObjOfsRelPos;
    y = 0x01; // relative to the screen
    a = 0x01; // get coordinates of enemy object 

RelativeBlockPosition:
    ++y; // adjust other and get coordinates for other one
    a = 0x09;
    ++x;
    ++x; // adjust offset for other block object if any
    pushReturnIndex(551);
    goto VariableObjOfsRelPos;
Return_551:
    y = 0x04; // relative to the screen
    a = 0x09; // get coordinates of one block object

VariableObjOfsRelPos:
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset); // reload old object offset and leave
    pushReturnIndex(552);
    goto GetObjRelativePosition;
Return_552:
    x = a; // use as enemy offset
    a += M(0x00); // add A to value stored
    c = 0;
    writeData(0x00, x); // store value to add to A here

GetObjRelativePosition:
    goto Return;

//------------------------------------------------------------------------
    writeData(SprObject_Rel_XPos + y, a); // store result here
    a -= M(ScreenLeft_X_Pos);
    c = 1; // subtract left edge coordinate
    a = M(SprObject_X_Position + x); // load horizontal coordinate
    writeData(SprObject_Rel_YPos + y, a); // store here
    a = M(SprObject_Y_Position + x); // load vertical coordinate low

GetPlayerOffscreenBits:
    goto GetOffScreenBitsSet;
    y = 0x00; // and get offscreen information about player
    x = 0x00; // set offsets for player-specific variables

GetFireballOffscreenBits:
    goto GetOffScreenBitsSet; // and get offscreen information about fireball
    y = 0x02; // set other offset for fireball's offscreen bits
    pushReturnIndex(553);
    goto GetProperObjOffset;
Return_553: // modify X to get proper fireball offset
    y = 0x00; // set for fireball offsets

GetBubbleOffscreenBits:
    goto GetOffScreenBitsSet; // and get offscreen information about air bubble
    y = 0x03; // set other offset for airbubble's offscreen bits
    pushReturnIndex(554);
    goto GetProperObjOffset;
Return_554: // modify X to get proper air bubble offset
    y = 0x01; // set for air bubble offsets

GetMiscOffscreenBits:
    goto GetOffScreenBitsSet; // and get offscreen information about misc object
    y = 0x06; // set other offset for misc object's offscreen bits
    pushReturnIndex(555);
    goto GetProperObjOffset;
Return_555: // modify X to get proper misc object offset
    y = 0x02; // set for misc object offsets

GetProperObjOffset:
    goto Return;

//------------------------------------------------------------------------
    x = a; // put back in X and leave
    a += M(ObjOffsetData + y); // add amount of bytes to offset depending on setting in Y
    c = 0;
    a = x; // move offset to A

GetEnemyOffscreenBits:
    goto SetOffscrBitsOffset;
    y = 0x01; // set Y to put offscreen bits in Enemy_OffscreenBits
    a = 0x01; // set A to add 1 byte in order to get enemy offset

GetBlockOffscreenBits:
    y = 0x04; // set Y to put offscreen bits in Block_OffscreenBits
    a = 0x09; // set A to add 9 bytes in order to get block obj offset

SetOffscrBitsOffset:
    x = a;
    a += M(0x00); // appropriate offset, then give back to X
    c = 0; // add contents of X to A to get
    writeData(0x00, x);

GetOffScreenBitsSet:
    goto Return;

//------------------------------------------------------------------------
    x = M(ObjectOffset);
    writeData(SprObject_OffscrBits + y, a);
    a = M(0x00); // get value here and store elsewhere
    y = a;
    pla(); // get offscreen bits offset from stack
    writeData(0x00, a); // store both here
    a |= M(0x00); // mask together with previously saved low nybble
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1; // move low nybble to high nybble
    pushReturnIndex(556);
    goto RunOffscrBitsSubs;
Return_556:
    pha();
    a = y; // save offscreen bits offset to stack for now

RunOffscrBitsSubs:
    goto GetYOffscreenBits;
    writeData(0x00, a); // store here
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1; // move high nybble to low
    pushReturnIndex(557);
    goto GetXOffscreenBits;
Return_557: // do subroutine here

GetXOffscreenBits:
    y = 0x01; // start with right side of screen
    writeData(0x04, x); // save position in buffer to here

XOfsLoop: // get pixel coordinate of edge
    pushReturnIndex(558);
    goto DividePDiff;
Return_558:
    a = 0x08; // load some other value and execute subroutine
    writeData(0x06, a);
    a = 0x38; // if no branching, load value here and store
    if (!n)
        goto XLdBData; // if one page or more to the left of either edge, branch
    compare(a, 0x01);
    x = M(DefaultXOnscreenOfs + 1 + y); // if not, load alternate offset value here
    if (n)
        goto XLdBData; // if beyond right edge or in front of left edge, branch
    compare(a, 0x00);
    x = M(DefaultXOnscreenOfs + y); // load offset value here
    a -= M(SprObject_PageLoc + x); // subtract from page location of object position
    a = M(ScreenEdge_PageLoc + y); // get page location of edge
    writeData(0x07, a); // store here
    a -= M(SprObject_X_Position + x); // and pixel coordinate of object position
    c = 1; // get difference between pixel coordinate of edge
    a = M(ScreenEdge_X_Pos + y);

XLdBData: // get bits here
    if (!n)
        goto XOfsLoop; // branch if not already done with left side
    --y; // otherwise, do left side of screen now
    if (!z)
        goto ExXOfsBS;
    compare(a, 0x00); // if bits not zero, branch to leave
    x = M(0x04); // reobtain position in buffer
    a = M(XOffscreenBitsData + x);

ExXOfsBS:
    goto Return;

//------------------------------------------------------------------------

GetYOffscreenBits:
    y = 0x01; // start with top of screen
    writeData(0x04, x); // save position in buffer to here

YOfsLoop: // load coordinate for edge of vertical unit
    pushReturnIndex(559);
    goto DividePDiff;
Return_559:
    a = 0x04; // load some other value and execute subroutine
    writeData(0x06, a);
    a = 0x20; // if no branching, load value here and store
    if (!n)
        goto YLdBData; // if one vertical unit or more above the screen, branch
    compare(a, 0x01);
    x = M(DefaultYOnscreenOfs + 1 + y); // if not, load alternate offset value here
    if (n)
        goto YLdBData; // if under top of the screen or beyond bottom, branch
    compare(a, 0x00);
    x = M(DefaultYOnscreenOfs + y); // load offset value here
    a -= M(SprObject_Y_HighPos + x);
    a = 0x01; // subtract one from vertical high byte of object
    writeData(0x07, a); // store here
    a -= M(SprObject_Y_Position + x); // subtract from vertical coordinate of object
    c = 1;
    a = M(HighPosUnitData + y);

YLdBData: // get offscreen data bits using offset
    if (!n)
        goto YOfsLoop;
    --y; // otherwise, do bottom of the screen now
    if (!z)
        goto ExYOfsBS; // if bits not zero, branch to leave
    compare(a, 0x00);
    x = M(0x04); // reobtain position in buffer
    a = M(YOffscreenBitsData + x);

ExYOfsBS:
    goto Return;

//------------------------------------------------------------------------

DividePDiff:
    a += M(0x05); // if not, add value to difference / 8
    if (c)
        goto SetOscrO; // if so, branch, use difference / 8 as offset
    compare(y, 0x01); // right side of the screen or top?
    a &= 0x07; // mask out all but 3 LSB
    a >>= 1;
    a >>= 1;
    a >>= 1; // divide by eight
    if (c)
        goto ExDivPD; // if pixel difference >= preset value, branch
    compare(a, M(0x06)); // compare to preset value
    a = M(0x07); // get pixel difference
    writeData(0x05, a); // store current value in A here

SetOscrO: // use as offset
    x = a;

ExDivPD: // leave
    goto Return;

//------------------------------------------------------------------------

DrawSpriteObject:
    if (!z)
        goto SetHFAt; // and unconditionally branch
    a = 0x40; // activate horizontal flip OAM attribute
    writeData(Sprite_Tilenumber + y, a);
    a = M(0x01); // and second into first sprite
    writeData(Sprite_Tilenumber + 4 + y, a); // store first tile into second sprite
    if (!c)
        goto NoHFlip; // if d1 not set, branch
    a = M(0x00);
    a >>= 1; // move d1 into carry
    a >>= 1;
    a = M(0x03); // get saved flip control bits

NoHFlip: // store first tile into first sprite
    a = 0x00; // clear bit for horizontal flip
    writeData(Sprite_Tilenumber + 4 + y, a);
    a = M(0x01); // and second into second sprite
    writeData(Sprite_Tilenumber + y, a);

SetHFAt: // add other OAM attributes if necessary
    goto Return;

//------------------------------------------------------------------------
    ++x; // routine that called this subroutine
    ++x; // increment offset to return it to the
    y = a;
    a += 0x08;
    c = 0; // move to the next two sprites
    a = y; // add eight to the offset in Y to
    writeData(0x02, a);
    a += 0x08;
    c = 0; // coordinate
    a = M(0x02); // add eight pixels to the next y
    writeData(Sprite_X_Position + 4 + y, a);
    a += 0x08; // put them side by side
    c = 0; // add 8 pixels and store another to
    writeData(Sprite_X_Position + y, a); // store x coordinate, then
    a = M(0x05);
    writeData(Sprite_Y_Position + 4 + y, a); // side by side, they are the same
    writeData(Sprite_Y_Position + y, a); // note because they are
    a = M(0x02); // now the y coordinates
    writeData(Sprite_Attributes + 4 + y, a);
    writeData(Sprite_Attributes + y, a); // store sprite attributes
    a |= M(0x04);

SoundEngine:
    goto Return;

//------------------------------------------------------------------------
    writeData(SND_MASTERCTRL_REG, a); // if so, disable sound and leave
    if (!z)
        goto SndOn;
    a = M(OperMode); // are we in title screen mode?

SndOn:
    if (!z)
        goto RunSoundSubroutines; // if queue is empty, skip pause mode routine
    compare(a, 0x01);
    a = M(PauseSoundQueue); // if not, check pause sfx queue    
    if (!z)
        goto InPause;
    a = M(PauseModeFlag); // is sound already in pause mode?
    writeData(SND_MASTERCTRL_REG, a); // enable first four channels
    a = 0x0f;
    writeData(JOYPAD_PORT2, a); // disable irqs and set frame counter mode???
    a = 0xff;

InPause: // check pause sfx buffer
    writeData(Squ1_SfxLenCounter, a);
    a = 0x2a; // store length of sound in pause counter
    writeData(SND_MASTERCTRL_REG, a); // enable sound again
    a = 0x0f;
    writeData(NoiseSoundBuffer, a);
    writeData(Square2SoundBuffer, a);
    writeData(Square1SoundBuffer, a);
    writeData(SND_MASTERCTRL_REG, a);
    a = 0x00; // disable sound and clear sfx buffers
    writeData(PauseModeFlag, a); // pause mode to interrupt game sounds
    writeData(PauseSoundBuffer, a); // if queue full, store in buffer and activate
    if (z)
        goto SkipSoundSubroutines;
    a = M(PauseSoundQueue); // check pause queue
    if (!z)
        goto ContPau;
    a = M(PauseSoundBuffer);

PTone1F: // play first tone
    if (!z)
        goto PTRegC; // unconditional branch
    a = 0x44;

ContPau: // check pause length left
    if (!z)
        goto DecPauC; // only load regs during times, otherwise skip
    compare(a, 0x18); // time to play second again?
    if (z)
        goto PTone1F;
    compare(a, 0x1e); // time to play first again?
    if (z)
        goto PTone2F;
    compare(a, 0x24); // time to play second?
    a = M(Squ1_SfxLenCounter);

PTone2F: // store reg contents and play the pause sfx
    a = 0x64;

PTRegC:
    pushReturnIndex(560);
    goto PlaySqu1Sfx;
Return_560:
    y = 0x7f;
    x = 0x84;

DecPauC: // decrement pause sfx counter
    writeData(PauseModeFlag, a);
    a = 0x00; // clear pause mode to allow game sounds again
    if (!z)
        goto SkipPIn;
    compare(a, 0x02); // if we need to be playing sound again
    a = M(PauseSoundBuffer); // if no longer playing pause sfx, check to see
    writeData(SND_MASTERCTRL_REG, a); // not currently playing the pause sfx
    a = 0x00; // disable sound if in pause mode and
    if (!z)
        goto SkipSoundSubroutines;
    --M(Squ1_SfxLenCounter);

SkipPIn: // clear pause sfx buffer
    if (z)
        goto SkipSoundSubroutines;
    writeData(PauseSoundBuffer, a);
    a = 0x00;

RunSoundSubroutines:
    writeData(EventMusicQueue, a);
    writeData(AreaMusicQueue, a);
    a = 0x00; // clear the music queues
    pushReturnIndex(561);
    goto MusicHandler;
Return_561: // play music on all channels
    pushReturnIndex(562);
    goto NoiseSfxHandler;
Return_562: //  ''  ''  '' noise channel
    pushReturnIndex(563);
    goto Square2SfxHandler;
Return_563: //  ''  ''  '' square channel 2
    pushReturnIndex(564);
    goto Square1SfxHandler;
Return_564: // play sfx on square channel 1

SkipSoundSubroutines:
    if (!c)
        goto StrWave; // if not there yet, just store it
    compare(y, 0x30);
    ++M(DAC_Counter); // increment and check counter
    if (z)
        goto NoIncDAC;
    a &= BOOST_BINARY(00000011); // check for specific music
    a = M(AreaMusicBuffer);
    y = M(DAC_Counter); // load some sort of counter 
    writeData(PauseSoundQueue, a);
    writeData(NoiseSoundQueue, a);
    writeData(Square2SoundQueue, a);
    writeData(Square1SoundQueue, a);
    a = 0x00; // clear the sound effects queues

NoIncDAC:
    --M(DAC_Counter); // decrement counter
    if (z)
        goto StrWave; // if we are at zero, do not decrement 
    a = y;

StrWave: // store into DMC load register (??)
    goto Return; // we are done here

//------------------------------------------------------------------------
    writeData(SND_DELTA_REG + 1, y);

Dump_Squ1_Regs:
    goto Return;

//------------------------------------------------------------------------
    writeData(SND_SQUARE1_REG, x);
    writeData(SND_SQUARE1_REG + 1, y); // dump the contents of X and Y into square 1's control regs

PlaySqu1Sfx:
    pushReturnIndex(565);
    goto Dump_Squ1_Regs;
Return_565: // do sub to set ctrl regs for square 1, then set frequency regs

SetFreq_Squ1:
    x = 0x00; // set frequency reg offset for square 1 sound channel

Dump_Freq_Regs:
    writeData(SND_REGISTER + 3 + x, a);
    a |= BOOST_BINARY(00001000); // length counter
    a = M(FreqRegLookupTbl + y); // second byte goes into 3 MSB plus extra bit for 
    writeData(SND_REGISTER + 2 + x, a); // first byte goes into LSB of frequency divider
    if (z)
        goto NoTone; // if zero, then do not load
    a = M(FreqRegLookupTbl + 1 + y); // use previous contents of A for sound reg offset
    y = a;

NoTone:
    goto Return;

//------------------------------------------------------------------------

Dump_Sq2_Regs:
    goto Return;

//------------------------------------------------------------------------
    writeData(SND_SQUARE2_REG + 1, y);
    writeData(SND_SQUARE2_REG, x); // dump the contents of X and Y into square 2's control regs

PlaySqu2Sfx:
    pushReturnIndex(566);
    goto Dump_Sq2_Regs;
Return_566: // do sub to set ctrl regs for square 2, then set frequency regs

SetFreq_Squ2:
    if (!z)
        goto Dump_Freq_Regs; // unconditional branch
    x = 0x04; // set frequency reg offset for square 2 sound channel

SetFreq_Tri:
    if (!z)
        goto Dump_Freq_Regs; // unconditional branch
    x = 0x08; // set frequency reg offset for triangle sound channel

PlayFlagpoleSlide:
    if (!z)
        goto FPS2nd;
    x = 0x99; // now load the rest
    pushReturnIndex(567);
    goto SetFreq_Squ1;
Return_567:
    a = 0x62; // load part of reg contents for flagpole sound
    writeData(Squ1_SfxLenCounter, a);
    a = 0x40; // store length of flagpole sound

PlaySmallJump:
    if (!z)
        goto JumpRegContents;
    a = 0x26; // branch here for small mario jumping sound

PlayBigJump:
    a = 0x18; // branch here for big mario jumping sound

JumpRegContents:
    writeData(Squ1_SfxLenCounter, a); // then continue on here
    a = 0x28; // store length of sfx for both jumping sounds
    pushReturnIndex(568);
    goto PlaySqu1Sfx;
Return_568:
    y = 0xa7; // anyway, this loads the first part of mario's jumping sound
    x = 0x82; // note that small and big jump borrow each others' reg contents

ContinueSndJump:
    if (!z)
        goto DmpJpFPS; // unconditional branch
    y = 0xf6;
    x = 0x5f; // load second part
    if (!z)
        goto N2Prt;
    compare(a, 0x25); // check for time to play second part yet
    a = M(Squ1_SfxLenCounter); // jumping sounds seem to be composed of three parts

N2Prt: // check for third part
    x = 0x48; // load third part
    if (!z)
        goto DecJpFPS;
    compare(a, 0x20);

FPS2nd: // the flagpole slide sound shares part of third part
    y = 0xbc;

DmpJpFPS:
    if (!z)
        goto DecJpFPS; // unconditional branch outta here
    pushReturnIndex(569);
    goto Dump_Squ1_Regs;
Return_569:

PlayFireballThrow:
    if (!z)
        goto Fthrow; // unconditional branch
    y = 0x99; // load reg contents for fireball throw sound
    a = 0x05;

PlayBump:
    y = 0x93;
    a = 0x0a; // load length of sfx and reg contents for bump sound

Fthrow: // the fireball sound shares reg contents with the bump sound
    pushReturnIndex(570);
    goto PlaySqu1Sfx;
Return_570:
    a = 0x0c; // load offset for bump sound
    writeData(Squ1_SfxLenCounter, a);
    x = 0x9e;

ContinueBumpThrow:
    writeData(SND_SQUARE1_REG + 1, a);
    a = 0xbb; // load second part directly
    if (!z)
        goto DecJpFPS;
    compare(a, 0x06);
    a = M(Squ1_SfxLenCounter); // check for second part of bump sound

DecJpFPS: // unconditional branch
    if (!z)
        goto BranchToDecLength1;

Square1SfxHandler:
    if (c)
        goto PlayFlagpoleSlide; // slide flagpole
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlayFireballThrow; // fireball throw
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlayPipeDownInj; // pipedown/injury
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlaySmackEnemy; // smack enemy
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlaySwimStomp; // swim/stomp
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlayBump; // bump
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlayBigJump; // big jump
    M(Square1SoundQueue) >>= 1;
    if (n)
        goto PlaySmallJump; // small jump
    writeData(Square1SoundBuffer, y); // if found, put in buffer
    if (z)
        goto CheckSfx1Buffer;
    y = M(Square1SoundQueue); // check for sfx in queue

CheckSfx1Buffer:
    if (c)
        goto DecrementSfx1Length; // slide flagpole
    a >>= 1;
    if (c)
        goto ContinueBumpThrow; // fireball throw
    a >>= 1;
    if (c)
        goto ContinuePipeDownInj; // pipedown/injury
    a >>= 1;
    if (c)
        goto ContinueSmackEnemy; // smack enemy
    a >>= 1;
    if (c)
        goto ContinueSwimStomp; // swim/stomp
    a >>= 1;
    if (c)
        goto ContinueBumpThrow; // bump
    a >>= 1;
    if (c)
        goto ContinueSndJump; // big mario jump 
    a >>= 1;
    if (n)
        goto ContinueSndJump; // small mario jump 
    if (z)
        goto ExS1H; // if not found, exit sub
    a = M(Square1SoundBuffer); // check for sfx in buffer 

ExS1H:
    goto Return;

//------------------------------------------------------------------------

PlaySwimStomp:
    pushReturnIndex(571);
    goto PlaySqu1Sfx;
Return_571:
    a = 0x26;
    x = 0x9e;
    y = 0x9c; // store reg contents for swim/stomp sound
    writeData(Squ1_SfxLenCounter, a);
    a = 0x0e; // store length of swim/stomp sound

ContinueSwimStomp:
    writeData(SND_SQUARE1_REG + 2, a); // directly into the LSB of square 1's frequency divider
    a = 0x9e; // when the length counts down to a certain point, put this
    if (!z)
        goto BranchToDecLength1;
    compare(y, 0x06);
    writeData(SND_SQUARE1_REG, a); // envelope
    a = M(SwimStompEnvelopeData - 1 + y); // length of sound left, used to control sound's
    y = M(Squ1_SfxLenCounter); // look up reg contents in data section based on

BranchToDecLength1:
    if (!z)
        goto DecrementSfx1Length; // unconditional branch (regardless of how we got here)

PlaySmackEnemy:
    if (!z)
        goto DecrementSfx1Length; // unconditional branch
    pushReturnIndex(572);
    goto PlaySqu1Sfx;
Return_572:
    a = 0x28; // store reg contents for smack enemy sound
    writeData(Squ1_SfxLenCounter, a);
    x = 0x9f;
    y = 0xcb;
    a = 0x0e; // store length of smack enemy sound

ContinueSmackEnemy:
    if (!z)
        goto SmTick;
    a = 0x9f;
    writeData(SND_SQUARE1_REG + 2, a); // in the smack enemy sound
    a = 0xa0; // if we're at the about-halfway point, make the second tone
    if (!z)
        goto SmSpc;
    compare(y, 0x08);
    y = M(Squ1_SfxLenCounter); // check about halfway through

SmSpc: // this creates spaces in the sound, giving it its distinct noise
    a = 0x90;

SmTick:
    writeData(SND_SQUARE1_REG, a);

DecrementSfx1Length:
    if (!z)
        goto ExSfx1;
    --M(Squ1_SfxLenCounter); // decrement length of sfx

StopSquare1Sfx:
    writeData(SND_MASTERCTRL_REG, x);
    x = 0x0f;
    writeData(SND_MASTERCTRL_REG, x);
    x = 0x0e;
    writeData(0xf1, x); // and stop making the sfx
    x = 0x00; // if end of sfx reached, clear buffer

ExSfx1:
    goto Return;

//------------------------------------------------------------------------

PlayPipeDownInj:
    writeData(Squ1_SfxLenCounter, a);
    a = 0x2f; // load length of pipedown sound

ContinuePipeDownInj:
    pushReturnIndex(573);
    goto PlaySqu1Sfx;
Return_573:
    a = 0x44;
    x = 0x9a;
    y = 0x91; // and this is where it actually gets written in
    if (z)
        goto NoPDwnL;
    a &= BOOST_BINARY(00000010);
    if (c)
        goto NoPDwnL;
    a >>= 1;
    if (c)
        goto NoPDwnL; // during which d3 must be set and d1-0 must be clear
    a >>= 1; // to be written to only during six specific times
    a = M(Squ1_SfxLenCounter); // some bitwise logic, forces the regs

NoPDwnL:
    goto DecrementSfx1Length;

PlayCoinGrab:
    if (!z)
        goto CGrab_TTickRegL;
    x = 0x8d; // and part of reg contents
    a = 0x35; // load length of coin grab sound

PlayTimerTick:
    x = 0x98; // and part of reg contents
    a = 0x06; // load length of timer tick sound

CGrab_TTickRegL:
    pushReturnIndex(574);
    goto PlaySqu2Sfx;
Return_574:
    a = 0x42; // of coin grab and timer tick sound
    y = 0x7f; // load the rest of reg contents 
    writeData(Squ2_SfxLenCounter, a);

ContinueCGrabTTick:
    writeData(SND_SQUARE2_REG + 2, a);
    a = 0x54; // if so, load the tone directly into the reg
    if (!z)
        goto N2Tone;
    compare(a, 0x30); // timer tick sound also executes this, not sure why
    a = M(Squ2_SfxLenCounter); // check for time to play second tone yet

N2Tone:
    if (!z)
        goto DecrementSfx2Length;

PlayBlast:
    if (!z)
        goto SBlasJ;
    a = 0x5e;
    y = 0x94; // load reg contents of fireworks/gunfire sound
    writeData(Squ2_SfxLenCounter, a);
    a = 0x20; // load length of fireworks/gunfire sound

ContinueBlast:
    a = 0x18;
    y = 0x93; // load second part reg contents then
    if (!z)
        goto DecrementSfx2Length;
    compare(a, 0x18);
    a = M(Squ2_SfxLenCounter); // check for time to play second part

SBlasJ: // unconditional branch to load rest of reg contents
    if (!z)
        goto BlstSJp;

PlayPowerUpGrab:
    writeData(Squ2_SfxLenCounter, a);
    a = 0x36; // load length of power-up grab sound

ContinuePowerUpGrab:
    y = 0x7f;
    x = 0x5d; // store reg contents of power-up grab sound
    a = M(PowerUpGrabFreqData - 1 + y); // use length left over / 2 for frequency offset
    y = a;
    if (c)
        goto DecrementSfx2Length; // alter frequency every other frame
    a >>= 1; // divide by 2
    a = M(Squ2_SfxLenCounter); // load frequency reg based on length left over

LoadSqu2Regs:
    pushReturnIndex(575);
    goto PlaySqu2Sfx;
Return_575:

DecrementSfx2Length:
    if (!z)
        goto ExSfx2;
    --M(Squ2_SfxLenCounter); // decrement length of sfx

EmptySfx2Buffer:
    writeData(Square2SoundBuffer, x);
    x = 0x00; // initialize square 2's sound effects buffer

StopSquare2Sfx:
    writeData(SND_MASTERCTRL_REG, x);
    x = 0x0f;
    writeData(SND_MASTERCTRL_REG, x);
    x = 0x0d; // stop playing the sfx

ExSfx2:
    goto Return;

//------------------------------------------------------------------------

Square2SfxHandler:
    if (c)
        goto PlayExtraLife; // 1-up
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayPowerUpGrab; // power-up grab
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayTimerTick; // timer tick
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayBlast; // fireworks/gunfire
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayGrowVine; // vine grow
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayGrowPowerUp; // power-up reveal
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayCoinGrab; // coin grab
    M(Square2SoundQueue) >>= 1;
    if (n)
        goto PlayBowserFall; // bowser fall
    writeData(Square2SoundBuffer, y); // if found, put in buffer and check for the following
    if (z)
        goto CheckSfx2Buffer;
    y = M(Square2SoundQueue); // check for sfx in queue
    if (!z)
        goto ContinueExtraLife;
    a &= Sfx_ExtraLife; // from being interrupted by other sounds on square 2
    a = M(Square2SoundBuffer); // special handling for the 1-up sound to keep it

CheckSfx2Buffer:
    if (c)
        goto ContinueExtraLife; // 1-up
    a >>= 1;
    if (c)
        goto ContinuePowerUpGrab; // power-up grab
    a >>= 1;
    if (c)
        goto Cont_CGrab_TTick; // timer tick
    a >>= 1;
    if (c)
        goto ContinueBlast; // fireworks/gunfire
    a >>= 1;
    if (c)
        goto ContinueGrowItems; // vine grow
    a >>= 1;
    if (c)
        goto ContinueGrowItems; // power-up reveal
    a >>= 1;
    if (c)
        goto Cont_CGrab_TTick; // coin grab
    a >>= 1;
    if (n)
        goto ContinueBowserFall; // bowser fall
    if (z)
        goto ExS2H; // if not found, exit sub
    a = M(Square2SoundBuffer); // check for sfx in buffer

ExS2H:
    goto Return;

//------------------------------------------------------------------------

Cont_CGrab_TTick:
    goto ContinueCGrabTTick;

JumpToDecLength2:
    goto DecrementSfx2Length;

PlayBowserFall:
    a = 0x18;
    y = 0xc4; // load contents of reg for bowser defeat sound
    writeData(Squ2_SfxLenCounter, a);
    a = 0x38; // load length of bowser defeat sound

BlstSJp:
    if (!z)
        goto PBFRegs;

ContinueBowserFall:
    a = 0x5a;
    y = 0xa4; // if so, load the rest of reg contents for bowser defeat sound
    if (!z)
        goto DecrementSfx2Length;
    compare(a, 0x08);
    a = M(Squ2_SfxLenCounter); // check for almost near the end

PBFRegs: // the fireworks/gunfire sound shares part of reg contents here
    x = 0x9f;

EL_LRegs: // this is an unconditional branch outta here
    if (!z)
        goto LoadSqu2Regs;

PlayExtraLife:
    writeData(Squ2_SfxLenCounter, a);
    a = 0x30; // load length of 1-up sound

ContinueExtraLife:
    x = 0x03; // load new tones only every eight frames
    a = M(Squ2_SfxLenCounter);

DivLLoop:
    if (!z)
        goto EL_LRegs; // unconditional branch
    y = 0x7f;
    x = 0x82;
    a = M(ExtraLifeFreqData - 1 + y); // load our reg contents
    y = a;
    if (!z)
        goto DivLLoop; // do this until all bits checked, if none set, continue
    --x;
    if (c)
        goto JumpToDecLength2; // if any bits set here, branch to dec the length
    a >>= 1;

PlayGrowPowerUp:
    if (!z)
        goto GrowItemRegs;
    a = 0x10; // load length of power-up reveal sound

PlayGrowVine:
    a = 0x20; // load length of vine grow sound

GrowItemRegs:
    writeData(Sfx_SecondaryCounter, a);
    a = 0x00; // start secondary counter for both sounds
    writeData(SND_SQUARE2_REG + 1, a);
    a = 0x7f; // load contents of reg for both sounds directly
    writeData(Squ2_SfxLenCounter, a);

ContinueGrowItems:
    goto Return;

//------------------------------------------------------------------------
    pushReturnIndex(576);
    goto SetFreq_Squ2;
Return_576:
    a = M(PUp_VGrow_FreqData + y); // use secondary counter / 2 as offset for frequency regs
    writeData(SND_SQUARE2_REG, a);
    a = 0x9d; // load contents of other reg directly
    if (z)
        goto StopGrowItems; // if so, branch to jump, and stop playing sounds
    compare(y, M(Squ2_SfxLenCounter)); // have we reached the end yet?
    y = a;
    a >>= 1; // divide by 2 to get the offset
    a = M(Sfx_SecondaryCounter); // this sound doesn't decrement the usual counter
    ++M(Sfx_SecondaryCounter); // increment secondary counter for both sounds

StopGrowItems:
    goto EmptySfx2Buffer; // branch to stop playing sounds

PlayBrickShatter:
    writeData(Noise_SfxLenCounter, a);
    a = 0x20; // load length of brick shatter sound

ContinueBrickShatter:
    a = M(BrickShatterEnvData + y);
    x = M(BrickShatterFreqData + y); // load reg contents of brick shatter sound
    y = a;
    if (!c)
        goto DecrementSfx3Length;
    a >>= 1; // divide by 2 and check for bit set to use offset
    a = M(Noise_SfxLenCounter);

PlayNoiseSfx:
    writeData(SND_NOISE_REG + 3, a);
    a = 0x18;
    writeData(SND_NOISE_REG + 2, x);
    writeData(SND_NOISE_REG, a); // play the sfx

DecrementSfx3Length:
    writeData(NoiseSoundBuffer, a);
    a = 0x00;
    writeData(SND_NOISE_REG, a);
    a = 0xf0; // if done, stop playing the sfx
    if (!z)
        goto ExSfx3;
    --M(Noise_SfxLenCounter); // decrement length of sfx

ExSfx3:
    goto Return;

//------------------------------------------------------------------------

NoiseSfxHandler:
    if (c)
        goto PlayBowserFlame; // bowser flame
    M(NoiseSoundQueue) >>= 1;
    if (c)
        goto PlayBrickShatter; // brick shatter
    M(NoiseSoundQueue) >>= 1;
    writeData(NoiseSoundBuffer, y); // if found, put in buffer
    if (z)
        goto CheckNoiseBuffer;
    y = M(NoiseSoundQueue); // check for sfx in queue

CheckNoiseBuffer:
    if (c)
        goto ContinueBowserFlame; // bowser flame
    a >>= 1;
    if (c)
        goto ContinueBrickShatter; // brick shatter
    a >>= 1;
    if (z)
        goto ExNH; // if not found, exit sub
    a = M(NoiseSoundBuffer); // check for sfx in buffer

ExNH:
    goto Return;

//------------------------------------------------------------------------

PlayBowserFlame:
    writeData(Noise_SfxLenCounter, a);
    a = 0x40; // load length of bowser flame sound

ContinueBowserFlame:
    if (!z)
        goto PlayNoiseSfx; // unconditional branch here
    a = M(BowserFlameEnvData - 1 + y);
    x = 0x0f; // load reg contents of bowser flame sound
    y = a;
    a >>= 1;
    a = M(Noise_SfxLenCounter);

ContinueMusic:
    goto HandleSquare2Music; // if we have music, start with square 2 channel

MusicHandler:
    goto Return; // no music, then leave

//------------------------------------------------------------------------
    if (!z)
        goto ContinueMusic;
    a |= M(AreaMusicBuffer);
    a = M(EventMusicBuffer); // check both buffers
    if (!z)
        goto LoadAreaMusic;
    a = M(AreaMusicQueue); // check area music queue
    if (!z)
        goto LoadEventMusic;
    a = M(EventMusicQueue); // check event music queue

LoadEventMusic:
    pushReturnIndex(577);
    goto StopSquare2Sfx;
Return_577: // but clear only square 1's sfx buffer
    pushReturnIndex(578);
    goto StopSquare1Sfx;
Return_578: // stop sfx in square 1 and 2
    if (!z)
        goto NoStopSfx; // if not, jump elsewhere
    compare(a, DeathMusic); // is it death music?
    writeData(EventMusicBuffer, a); // copy event music queue contents to buffer

NoStopSfx:
    if (!z)
        goto FindEventMusicHeader; // unconditional branch
    writeData(NoteLengthTblAdder, x);
    x = 0x08; // load offset to be added to length byte of header
    if (!z)
        goto FindEventMusicHeader;
    compare(a, TimeRunningOutMusic); // is it time running out music?
    writeData(AreaMusicBuffer, y); // clear area music buffer
    writeData(NoteLengthTblAdder, y); // default value for additional length byte offset
    y = 0x00;
    writeData(AreaMusicBuffer_Alt, x); // save current area music buffer to be re-obtained later
    x = M(AreaMusicBuffer);

LoadAreaMusic:
    pushReturnIndex(579);
    goto StopSquare1Sfx;
Return_579:
    if (!z)
        goto NoStop1; // no, do not stop square 1 sfx
    compare(a, 0x04); // is it underground music?

NoStop1: // start counter used only by ground level music
    y = 0x10;

GMLoopB:
    writeData(GroundMusicHeaderOfs, y);

HandleAreaMusicLoopB:
    if (!z)
        goto GMLoopB; // unconditional branch
    y = 0x11;
    if (!z)
        goto LoadHeader; // branch ahead with alternate offset
    compare(y, 0x32);
    y = M(GroundMusicHeaderOfs); // is it time to loopback ground level music?
    ++M(GroundMusicHeaderOfs); // increment but only if playing ground level music
    if (!z)
        goto FindAreaMusicHeader;
    compare(a, 0x01); // is it ground level music?
    writeData(AreaMusicBuffer, a); // copy area music queue contents to buffer
    writeData(EventMusicBuffer, y);
    y = 0x00; // clear event music buffer

FindAreaMusicHeader:
    writeData(MusicOffset_Square2, y); // residual instruction here
    y = 0x08; // load Y for offset of area music

FindEventMusicHeader:
    if (!c)
        goto FindEventMusicHeader;
    a >>= 1; // bit shift and increment until we find a set bit for music
    ++y; // increment Y pointer based on previously loaded queue contents

LoadHeader:
    writeData(SND_MASTERCTRL_REG, a);
    a = 0x0f;
    writeData(SND_MASTERCTRL_REG, a);
    a = 0x0b; // disable triangle channel and reenable it
    writeData(AltRegContentFlag, a); // initialize alternate control reg data used by square 1
    writeData(MusicOffset_Square2, a);
    a = 0x00; // initialize music data offset for square 2
    writeData(Noise_BeatLenCounter, a);
    writeData(Tri_NoteLenCounter, a);
    writeData(Squ1_NoteLenCounter, a);
    writeData(Squ2_NoteLenCounter, a);
    a = 0x01; // initialize music note counters
    writeData(NoiseDataLoopbackOfs, a);
    writeData(MusicOffset_Noise, a);
    a = M(MusicHeaderData + 5 + y);
    writeData(MusicOffset_Square1, a);
    a = M(MusicHeaderData + 4 + y);
    writeData(MusicOffset_Triangle, a);
    a = M(MusicHeaderData + 3 + y);
    writeData(MusicDataHigh, a);
    a = M(MusicHeaderData + 2 + y);
    writeData(MusicDataLow, a);
    a = M(MusicHeaderData + 1 + y);
    writeData(NoteLenLookupTblOfs, a);
    a = M(MusicHeaderData + y); // now load the header
    y = a;
    a = M(MusicHeaderOffsetData + y); // load offset for header

HandleSquare2Music:
    if (!z)
        goto Squ2LengthHandler; // otherwise it is length data
    if (!n)
        goto Squ2NoteHandler; // if non-negative, data is a note
    if (z)
        goto EndOfMusicData; // if zero, the data is a null terminator
    a = M(W(MusicData) + y);
    ++M(MusicOffset_Square2);
    y = M(MusicOffset_Square2); // increment square 2 music offset and fetch data
    if (!z)
        goto MiscSqu2MusicTasks; // is it time for more data?  if not, branch to end tasks
    --M(Squ2_NoteLenCounter); // decrement square 2 note length

EndOfMusicData:
    if (!z)
        goto MusicLoopBack; // and start playing the song again if there is one
    a = M(AreaMusicBuffer_Alt); // load previously saved contents of primary buffer
    if (!z)
        goto NotTRO;
    compare(a, TimeRunningOutMusic);
    a = M(EventMusicBuffer); // check secondary buffer for time running out music

NotTRO: // check for victory music (the only secondary that loops)
    goto Return;

//------------------------------------------------------------------------
    writeData(SND_SQUARE2_REG, a);
    writeData(SND_SQUARE1_REG, a);
    a = 0x90;
    writeData(SND_TRIANGLE_REG, a);
    writeData(EventMusicBuffer, a);
    writeData(AreaMusicBuffer, a); // control regs of square and triangle channels
    a = 0x00; // clear primary and secondary buffers and initialize
    if (!z)
        goto MusicLoopBack; // if any area music except pipe intro, music loops
    a &= BOOST_BINARY(01011111);
    a = M(AreaMusicBuffer); // check primary buffer for any music except pipe intro
    if (!z)
        goto VictoryMLoopBack;
    a &= VictoryMusic;

MusicLoopBack:
    goto HandleAreaMusicLoopB;

VictoryMLoopBack:
    goto LoadEventMusic;

Squ2LengthHandler:
    a = M(W(MusicData) + y);
    ++M(MusicOffset_Square2);
    y = M(MusicOffset_Square2); // fetch another byte (MUST NOT BE LENGTH BYTE!)
    writeData(Squ2_NoteLenBuffer, a);
    pushReturnIndex(580);
    goto ProcessLengthData;
Return_580: // store length of note

Squ2NoteHandler:
    pushReturnIndex(581);
    goto LoadControlRegs;
Return_581: // if not, load control regs for square 2
    if (z)
        goto Rest; // check to see if note is rest
    pushReturnIndex(582);
    goto SetFreq_Squ2;
Return_582: // no, then play the note
    if (!z)
        goto SkipFqL1;
    x = M(Square2SoundBuffer); // is there a sound playing on this channel?

Rest: // save contents of A
    pushReturnIndex(583);
    goto Dump_Sq2_Regs;
Return_583: // dump X and Y into square 2 control regs
    writeData(Squ2_EnvelopeDataCtrl, a);

SkipFqL1: // save length in square 2 note counter
    writeData(Squ2_NoteLenCounter, a);
    a = M(Squ2_NoteLenBuffer);

MiscSqu2MusicTasks:
    --M(Squ2_EnvelopeDataCtrl); // decrement unless already zero
    if (z)
        goto NoDecEnv1;
    y = M(Squ2_EnvelopeDataCtrl); // check for contents saved from LoadControlRegs
    if (!z)
        goto HandleSquare1Music;
    a &= BOOST_BINARY(10010001); // note that regs for death music or d4 are loaded by default
    a = M(EventMusicBuffer); // check for death music or d4 set on secondary buffer
    if (!z)
        goto HandleSquare1Music;
    a = M(Square2SoundBuffer); // is there a sound playing on square 2?

NoDecEnv1: // do a load of envelope data to replace default
    writeData(SND_SQUARE2_REG + 1, x);
    x = 0x7f; // death music or d4 set on secondary buffer
    writeData(SND_SQUARE2_REG, a); // based on offset set by first load unless playing
    pushReturnIndex(584);
    goto LoadEnvelopeData;
Return_584:

HandleSquare1Music:
    if (!z)
        goto MiscSqu1MusicTasks; // is it time for more data?
    --M(Squ1_NoteLenCounter); // decrement square 1 note length
    if (z)
        goto HandleTriangleMusic; // if not, skip ahead to the triangle channel
    y = M(MusicOffset_Square1); // is there a nonzero offset here?

FetchSqu1MusicData:
    if (!z)
        goto FetchSqu1MusicData; // unconditional branch
    writeData(AltRegContentFlag, a);
    writeData(SND_SQUARE1_REG + 1, a); // death music its unique sound
    a = 0x94; // and fetch another byte of data, used to give
    writeData(SND_SQUARE1_REG, a); // store some data into control regs for square 1
    a = 0x83;
    if (!z)
        goto Squ1NoteHandler; // if nonzero, then skip this part
    a = M(W(MusicData) + y);
    ++M(MusicOffset_Square1);
    y = M(MusicOffset_Square1); // increment square 1 music offset and fetch data

Squ1NoteHandler:
    pushReturnIndex(585);
    goto LoadControlRegs;
Return_585:
    if (z)
        goto SkipCtrlL;
    pushReturnIndex(586);
    goto SetFreq_Squ1;
Return_586: // play the note
    a &= BOOST_BINARY(00111110); // change saved data to appropriate note format
    a = x;
    if (!z)
        goto HandleTriangleMusic;
    y = M(Square1SoundBuffer); // is there a sound playing on square 1?
    writeData(Squ1_NoteLenCounter, a); // save contents of A in square 1 note counter
    pushReturnIndex(587);
    goto AlternateLengthHandler;
Return_587:

SkipCtrlL: // save envelope offset
    pushReturnIndex(588);
    goto Dump_Squ1_Regs;
Return_588:
    writeData(Squ1_EnvelopeDataCtrl, a);

MiscSqu1MusicTasks:
    --M(Squ1_EnvelopeDataCtrl); // decrement unless already zero
    if (z)
        goto NoDecEnv2;
    y = M(Squ1_EnvelopeDataCtrl); // check saved envelope offset
    if (!z)
        goto DeathMAltReg;
    a &= BOOST_BINARY(10010001);
    a = M(EventMusicBuffer); // check for death music or d4 set on secondary buffer
    if (!z)
        goto HandleTriangleMusic;
    a = M(Square1SoundBuffer); // is there a sound playing on square 1?

NoDecEnv2: // do a load of envelope data
    writeData(SND_SQUARE1_REG, a); // based on offset set by first load
    pushReturnIndex(589);
    goto LoadEnvelopeData;
Return_589:

DeathMAltReg: // check for alternate control reg data
    a = 0x7f; // load this value if zero, the alternate value
    if (!z)
        goto DoAltLoad;
    a = M(AltRegContentFlag);

DoAltLoad: // if nonzero, and let's move on
    writeData(SND_SQUARE1_REG + 1, a);

HandleTriangleMusic:
    if (z)
        goto LoadTriCtrlReg; // check once more for nonzero data
    a = M(W(MusicData) + y);
    ++M(MusicOffset_Triangle);
    y = M(MusicOffset_Triangle); // fetch another byte
    writeData(SND_TRIANGLE_REG, a); // load some default data for triangle control reg
    a = 0x1f;
    writeData(Tri_NoteLenBuffer, a); // save contents of A
    pushReturnIndex(590);
    goto ProcessLengthData;
Return_590: // otherwise, it is length data
    if (!n)
        goto TriNoteHandler; // if non-negative, data is note
    if (z)
        goto LoadTriCtrlReg; // if zero, skip all this and move on to noise 
    a = M(W(MusicData) + y);
    ++M(MusicOffset_Triangle);
    y = M(MusicOffset_Triangle); // increment square 1 music offset and fetch data
    if (!z)
        goto HandleNoiseMusic; // is it time for more data?
    --M(Tri_NoteLenCounter); // decrement triangle note length
    a = M(MusicOffset_Triangle);

TriNoteHandler:
    if (z)
        goto HandleNoiseMusic; // if playing any other primary, or death or d4, go on to noise routine
    a &= BOOST_BINARY(00001010);
    a = M(AreaMusicBuffer); // check primary buffer for water or castle level music
    if (!z)
        goto NotDOrD4; // if playing any other secondary, skip primary buffer check
    a &= BOOST_BINARY(01101110); // check for death music or d4 set on secondary buffer
    a = M(EventMusicBuffer);
    writeData(Tri_NoteLenCounter, x);
    x = M(Tri_NoteLenBuffer); // save length in triangle note counter
    pushReturnIndex(591);
    goto SetFreq_Tri;
Return_591:

NotDOrD4: // if playing water or castle music or any secondary
    if (!z)
        goto LoadTriCtrlReg; // note, load value $1f if playing water or castle level music or any
    a = 0x0f; // load value $0f if playing the win castle music and playing a short
    if (z)
        goto MediN;
    a &= EndOfCastleMusic;
    a = M(EventMusicBuffer); // check for win castle music again if not playing a long note
    if (c)
        goto LongN;
    compare(a, 0x12); // besides death music or d4 set, check length of note
    a = x;

MediN: // secondary besides death and d4 except win castle or win castle and playing
    if (!z)
        goto LoadTriCtrlReg; // a short note, and load value $ff if playing a long note on water, castle
    a = 0x1f;

LongN: // or any secondary (including win castle) except death and d4
    a = 0xff;

LoadTriCtrlReg:
    writeData(SND_TRIANGLE_REG, a); // save final contents of A into control reg for triangle

HandleNoiseMusic:
    if (!z)
        goto ExitMusicHandler; // is it time for more data?
    --M(Noise_BeatLenCounter); // decrement noise beat length
    if (z)
        goto ExitMusicHandler; // if so, skip the noise routine
    a &= BOOST_BINARY(11110011);
    a = M(AreaMusicBuffer); // check if playing underground or castle music

FetchNoiseBeatData:
    if (!z)
        goto FetchNoiseBeatData; // unconditional branch
    writeData(MusicOffset_Noise, a); // and loopback next time around
    a = M(NoiseDataLoopbackOfs); // if data is zero, reload original noise beat offset
    if (!z)
        goto NoiseBeatHandler;
    a = M(W(MusicData) + y); // get noise beat data, if nonzero, branch to handle
    ++M(MusicOffset_Noise);
    y = M(MusicOffset_Noise); // increment noise beat offset and fetch data

NoiseBeatHandler:
    if (!z)
        goto PlayBeat;
    y = 0x18;
    x = 0x03;
    a = 0x1c; // short beat data
    if (z)
        goto SilentBeat;
    a &= BOOST_BINARY(00010000);
    if (z)
        goto StrongBeat;
    compare(a, 0x20);
    if (z)
        goto LongBeat; // noise accordingly
    compare(a, 0x30); // check the beat data and play the appropriate
    if (z)
        goto SilentBeat; // if no beat data, silence
    a &= BOOST_BINARY(00111110); // reload data and erase length bits
    a = x;
    writeData(Noise_BeatLenCounter, a); // store length in noise beat counter
    pushReturnIndex(592);
    goto AlternateLengthHandler;
Return_592:

StrongBeat:
    if (!z)
        goto PlayBeat;
    y = 0x18;
    x = 0x0c;
    a = 0x1c; // strong beat data

LongBeat:
    if (!z)
        goto PlayBeat;
    y = 0x58;
    x = 0x03;
    a = 0x1c; // long beat data

SilentBeat:
    a = 0x10; // silence

PlayBeat:
    writeData(SND_NOISE_REG + 3, y);
    writeData(SND_NOISE_REG + 2, x);
    writeData(SND_NOISE_REG, a); // load beat data into noise regs

ExitMusicHandler:
    goto Return;

//------------------------------------------------------------------------

AlternateLengthHandler:
    a.rol();
    a.rol(); // bit in carry as the MSB here
    a.rol(); // turning xx00000x into 00000xxx, with the
    a = x; // reload original byte and rotate three times
    a.ror(); // save LSB from original byte into carry
    x = a; // save a copy of original byte into X

ProcessLengthData:
    goto Return;

//------------------------------------------------------------------------
    a = M(MusicLengthLookupTbl + y); // load length
    y = a;
    a += M(NoteLengthTblAdder); // add extra if time running out music
    a += M(0xf0); // add offset loaded from first header byte
    c = 0;
    a &= BOOST_BINARY(00000111); // clear all but the three LSBs

LoadControlRegs:
    if (!z)
        goto AllMus; // unconditional branch
    a = 0x04; // this value is only used for win castle music
    if (z)
        goto NotECstlM;
    a &= EndOfCastleMusic;
    a = M(EventMusicBuffer); // check secondary buffer for win castle music

NotECstlM:
    if (!z)
        goto AllMus;
    a = 0x08; // this is the default value for all other music
    if (z)
        goto WaterMus;
    a &= BOOST_BINARY(01111101); // check primary buffer for water music
    a = M(AreaMusicBuffer);

WaterMus: // this value is used for water music and all other event music
    a = 0x28;

AllMus: // load contents of other sound regs for square 2
    goto Return;

//------------------------------------------------------------------------
    y = 0x7f;
    x = 0x82;

LoadEnvelopeData:
    goto Return;

//------------------------------------------------------------------------
    a = M(EndOfCastleMusicEnvData + y); // load data from offset for win castle music
    if (z)
        goto LoadUsualEnvData;
    a &= EndOfCastleMusic;
    a = M(EventMusicBuffer); // check secondary buffer for win castle music

LoadUsualEnvData:
    goto Return;

//------------------------------------------------------------------------
    a = M(AreaMusicEnvData + y); // load default data from offset for all other music
    if (z)
        goto LoadWaterEventMusEnvData;
    a &= BOOST_BINARY(01111101);
    a = M(AreaMusicBuffer); // check primary buffer for water music

LoadWaterEventMusEnvData:
    goto Return;

//------------------------------------------------------------------------
    a = M(WaterEventMusEnvData + y); // load data from offset for water music and all other event music

TimeRunningOutHdr:

Star_CloudHdr:

EndOfLevelMusHdr:

ResidualHeaderData:

UndergroundMusHdr:

SilenceHdr:

CastleMusHdr:

VictoryMusHdr:

GameOverMusHdr:

WaterMusHdr:

WinCastleMusHdr:

GroundLevelPart1Hdr:

GroundLevelPart2AHdr:

GroundLevelPart2BHdr:

GroundLevelPart2CHdr:

GroundLevelPart3AHdr:

GroundLevelPart3BHdr:

GroundLevelLeadInHdr:

GroundLevelPart4AHdr:

GroundLevelPart4BHdr:

GroundLevelPart4CHdr:

DeathMusHdr:
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
    case 159:
        goto Return_159;
    case 160:
        goto Return_160;
    case 161:
        goto Return_161;
    case 162:
        goto Return_162;
    case 163:
        goto Return_163;
    case 164:
        goto Return_164;
    case 165:
        goto Return_165;
    case 166:
        goto Return_166;
    case 167:
        goto Return_167;
    case 168:
        goto Return_168;
    case 169:
        goto Return_169;
    case 170:
        goto Return_170;
    case 171:
        goto Return_171;
    case 172:
        goto Return_172;
    case 173:
        goto Return_173;
    case 174:
        goto Return_174;
    case 175:
        goto Return_175;
    case 176:
        goto Return_176;
    case 177:
        goto Return_177;
    case 178:
        goto Return_178;
    case 179:
        goto Return_179;
    case 180:
        goto Return_180;
    case 181:
        goto Return_181;
    case 182:
        goto Return_182;
    case 183:
        goto Return_183;
    case 184:
        goto Return_184;
    case 185:
        goto Return_185;
    case 186:
        goto Return_186;
    case 187:
        goto Return_187;
    case 188:
        goto Return_188;
    case 189:
        goto Return_189;
    case 190:
        goto Return_190;
    case 191:
        goto Return_191;
    case 192:
        goto Return_192;
    case 193:
        goto Return_193;
    case 194:
        goto Return_194;
    case 195:
        goto Return_195;
    case 196:
        goto Return_196;
    case 197:
        goto Return_197;
    case 198:
        goto Return_198;
    case 199:
        goto Return_199;
    case 200:
        goto Return_200;
    case 201:
        goto Return_201;
    case 202:
        goto Return_202;
    case 203:
        goto Return_203;
    case 204:
        goto Return_204;
    case 205:
        goto Return_205;
    case 206:
        goto Return_206;
    case 207:
        goto Return_207;
    case 208:
        goto Return_208;
    case 209:
        goto Return_209;
    case 210:
        goto Return_210;
    case 211:
        goto Return_211;
    case 212:
        goto Return_212;
    case 213:
        goto Return_213;
    case 214:
        goto Return_214;
    case 215:
        goto Return_215;
    case 216:
        goto Return_216;
    case 217:
        goto Return_217;
    case 218:
        goto Return_218;
    case 219:
        goto Return_219;
    case 220:
        goto Return_220;
    case 221:
        goto Return_221;
    case 222:
        goto Return_222;
    case 223:
        goto Return_223;
    case 224:
        goto Return_224;
    case 225:
        goto Return_225;
    case 226:
        goto Return_226;
    case 227:
        goto Return_227;
    case 228:
        goto Return_228;
    case 229:
        goto Return_229;
    case 230:
        goto Return_230;
    case 231:
        goto Return_231;
    case 232:
        goto Return_232;
    case 233:
        goto Return_233;
    case 234:
        goto Return_234;
    case 235:
        goto Return_235;
    case 236:
        goto Return_236;
    case 237:
        goto Return_237;
    case 238:
        goto Return_238;
    case 239:
        goto Return_239;
    case 240:
        goto Return_240;
    case 241:
        goto Return_241;
    case 242:
        goto Return_242;
    case 243:
        goto Return_243;
    case 244:
        goto Return_244;
    case 245:
        goto Return_245;
    case 246:
        goto Return_246;
    case 247:
        goto Return_247;
    case 248:
        goto Return_248;
    case 249:
        goto Return_249;
    case 250:
        goto Return_250;
    case 251:
        goto Return_251;
    case 252:
        goto Return_252;
    case 253:
        goto Return_253;
    case 254:
        goto Return_254;
    case 255:
        goto Return_255;
    case 256:
        goto Return_256;
    case 257:
        goto Return_257;
    case 258:
        goto Return_258;
    case 259:
        goto Return_259;
    case 260:
        goto Return_260;
    case 261:
        goto Return_261;
    case 262:
        goto Return_262;
    case 263:
        goto Return_263;
    case 264:
        goto Return_264;
    case 265:
        goto Return_265;
    case 266:
        goto Return_266;
    case 267:
        goto Return_267;
    case 268:
        goto Return_268;
    case 269:
        goto Return_269;
    case 270:
        goto Return_270;
    case 271:
        goto Return_271;
    case 272:
        goto Return_272;
    case 273:
        goto Return_273;
    case 274:
        goto Return_274;
    case 275:
        goto Return_275;
    case 276:
        goto Return_276;
    case 277:
        goto Return_277;
    case 278:
        goto Return_278;
    case 279:
        goto Return_279;
    case 280:
        goto Return_280;
    case 281:
        goto Return_281;
    case 282:
        goto Return_282;
    case 283:
        goto Return_283;
    case 284:
        goto Return_284;
    case 285:
        goto Return_285;
    case 286:
        goto Return_286;
    case 287:
        goto Return_287;
    case 288:
        goto Return_288;
    case 289:
        goto Return_289;
    case 290:
        goto Return_290;
    case 291:
        goto Return_291;
    case 292:
        goto Return_292;
    case 293:
        goto Return_293;
    case 294:
        goto Return_294;
    case 295:
        goto Return_295;
    case 296:
        goto Return_296;
    case 297:
        goto Return_297;
    case 298:
        goto Return_298;
    case 299:
        goto Return_299;
    case 300:
        goto Return_300;
    case 301:
        goto Return_301;
    case 302:
        goto Return_302;
    case 303:
        goto Return_303;
    case 304:
        goto Return_304;
    case 305:
        goto Return_305;
    case 306:
        goto Return_306;
    case 307:
        goto Return_307;
    case 308:
        goto Return_308;
    case 309:
        goto Return_309;
    case 310:
        goto Return_310;
    case 311:
        goto Return_311;
    case 312:
        goto Return_312;
    case 313:
        goto Return_313;
    case 314:
        goto Return_314;
    case 315:
        goto Return_315;
    case 316:
        goto Return_316;
    case 317:
        goto Return_317;
    case 318:
        goto Return_318;
    case 319:
        goto Return_319;
    case 320:
        goto Return_320;
    case 321:
        goto Return_321;
    case 322:
        goto Return_322;
    case 323:
        goto Return_323;
    case 324:
        goto Return_324;
    case 325:
        goto Return_325;
    case 326:
        goto Return_326;
    case 327:
        goto Return_327;
    case 328:
        goto Return_328;
    case 329:
        goto Return_329;
    case 330:
        goto Return_330;
    case 331:
        goto Return_331;
    case 332:
        goto Return_332;
    case 333:
        goto Return_333;
    case 334:
        goto Return_334;
    case 335:
        goto Return_335;
    case 336:
        goto Return_336;
    case 337:
        goto Return_337;
    case 338:
        goto Return_338;
    case 339:
        goto Return_339;
    case 340:
        goto Return_340;
    case 341:
        goto Return_341;
    case 342:
        goto Return_342;
    case 343:
        goto Return_343;
    case 344:
        goto Return_344;
    case 345:
        goto Return_345;
    case 346:
        goto Return_346;
    case 347:
        goto Return_347;
    case 348:
        goto Return_348;
    case 349:
        goto Return_349;
    case 350:
        goto Return_350;
    case 351:
        goto Return_351;
    case 352:
        goto Return_352;
    case 353:
        goto Return_353;
    case 354:
        goto Return_354;
    case 355:
        goto Return_355;
    case 356:
        goto Return_356;
    case 357:
        goto Return_357;
    case 358:
        goto Return_358;
    case 359:
        goto Return_359;
    case 360:
        goto Return_360;
    case 361:
        goto Return_361;
    case 362:
        goto Return_362;
    case 363:
        goto Return_363;
    case 364:
        goto Return_364;
    case 365:
        goto Return_365;
    case 366:
        goto Return_366;
    case 367:
        goto Return_367;
    case 368:
        goto Return_368;
    case 369:
        goto Return_369;
    case 370:
        goto Return_370;
    case 371:
        goto Return_371;
    case 372:
        goto Return_372;
    case 373:
        goto Return_373;
    case 374:
        goto Return_374;
    case 375:
        goto Return_375;
    case 376:
        goto Return_376;
    case 377:
        goto Return_377;
    case 378:
        goto Return_378;
    case 379:
        goto Return_379;
    case 380:
        goto Return_380;
    case 381:
        goto Return_381;
    case 382:
        goto Return_382;
    case 383:
        goto Return_383;
    case 384:
        goto Return_384;
    case 385:
        goto Return_385;
    case 386:
        goto Return_386;
    case 387:
        goto Return_387;
    case 388:
        goto Return_388;
    case 389:
        goto Return_389;
    case 390:
        goto Return_390;
    case 391:
        goto Return_391;
    case 392:
        goto Return_392;
    case 393:
        goto Return_393;
    case 394:
        goto Return_394;
    case 395:
        goto Return_395;
    case 396:
        goto Return_396;
    case 397:
        goto Return_397;
    case 398:
        goto Return_398;
    case 399:
        goto Return_399;
    case 400:
        goto Return_400;
    case 401:
        goto Return_401;
    case 402:
        goto Return_402;
    case 403:
        goto Return_403;
    case 404:
        goto Return_404;
    case 405:
        goto Return_405;
    case 406:
        goto Return_406;
    case 407:
        goto Return_407;
    case 408:
        goto Return_408;
    case 409:
        goto Return_409;
    case 410:
        goto Return_410;
    case 411:
        goto Return_411;
    case 412:
        goto Return_412;
    case 413:
        goto Return_413;
    case 414:
        goto Return_414;
    case 415:
        goto Return_415;
    case 416:
        goto Return_416;
    case 417:
        goto Return_417;
    case 418:
        goto Return_418;
    case 419:
        goto Return_419;
    case 420:
        goto Return_420;
    case 421:
        goto Return_421;
    case 422:
        goto Return_422;
    case 423:
        goto Return_423;
    case 424:
        goto Return_424;
    case 425:
        goto Return_425;
    case 426:
        goto Return_426;
    case 427:
        goto Return_427;
    case 428:
        goto Return_428;
    case 429:
        goto Return_429;
    case 430:
        goto Return_430;
    case 431:
        goto Return_431;
    case 432:
        goto Return_432;
    case 433:
        goto Return_433;
    case 434:
        goto Return_434;
    case 435:
        goto Return_435;
    case 436:
        goto Return_436;
    case 437:
        goto Return_437;
    case 438:
        goto Return_438;
    case 439:
        goto Return_439;
    case 440:
        goto Return_440;
    case 441:
        goto Return_441;
    case 442:
        goto Return_442;
    case 443:
        goto Return_443;
    case 444:
        goto Return_444;
    case 445:
        goto Return_445;
    case 446:
        goto Return_446;
    case 447:
        goto Return_447;
    case 448:
        goto Return_448;
    case 449:
        goto Return_449;
    case 450:
        goto Return_450;
    case 451:
        goto Return_451;
    case 452:
        goto Return_452;
    case 453:
        goto Return_453;
    case 454:
        goto Return_454;
    case 455:
        goto Return_455;
    case 456:
        goto Return_456;
    case 457:
        goto Return_457;
    case 458:
        goto Return_458;
    case 459:
        goto Return_459;
    case 460:
        goto Return_460;
    case 461:
        goto Return_461;
    case 462:
        goto Return_462;
    case 463:
        goto Return_463;
    case 464:
        goto Return_464;
    case 465:
        goto Return_465;
    case 466:
        goto Return_466;
    case 467:
        goto Return_467;
    case 468:
        goto Return_468;
    case 469:
        goto Return_469;
    case 470:
        goto Return_470;
    case 471:
        goto Return_471;
    case 472:
        goto Return_472;
    case 473:
        goto Return_473;
    case 474:
        goto Return_474;
    case 475:
        goto Return_475;
    case 476:
        goto Return_476;
    case 477:
        goto Return_477;
    case 478:
        goto Return_478;
    case 479:
        goto Return_479;
    case 480:
        goto Return_480;
    case 481:
        goto Return_481;
    case 482:
        goto Return_482;
    case 483:
        goto Return_483;
    case 484:
        goto Return_484;
    case 485:
        goto Return_485;
    case 486:
        goto Return_486;
    case 487:
        goto Return_487;
    case 488:
        goto Return_488;
    case 489:
        goto Return_489;
    case 490:
        goto Return_490;
    case 491:
        goto Return_491;
    case 492:
        goto Return_492;
    case 493:
        goto Return_493;
    case 494:
        goto Return_494;
    case 495:
        goto Return_495;
    case 496:
        goto Return_496;
    case 497:
        goto Return_497;
    case 498:
        goto Return_498;
    case 499:
        goto Return_499;
    case 500:
        goto Return_500;
    case 501:
        goto Return_501;
    case 502:
        goto Return_502;
    case 503:
        goto Return_503;
    case 504:
        goto Return_504;
    case 505:
        goto Return_505;
    case 506:
        goto Return_506;
    case 507:
        goto Return_507;
    case 508:
        goto Return_508;
    case 509:
        goto Return_509;
    case 510:
        goto Return_510;
    case 511:
        goto Return_511;
    case 512:
        goto Return_512;
    case 513:
        goto Return_513;
    case 514:
        goto Return_514;
    case 515:
        goto Return_515;
    case 516:
        goto Return_516;
    case 517:
        goto Return_517;
    case 518:
        goto Return_518;
    case 519:
        goto Return_519;
    case 520:
        goto Return_520;
    case 521:
        goto Return_521;
    case 522:
        goto Return_522;
    case 523:
        goto Return_523;
    case 524:
        goto Return_524;
    case 525:
        goto Return_525;
    case 526:
        goto Return_526;
    case 527:
        goto Return_527;
    case 528:
        goto Return_528;
    case 529:
        goto Return_529;
    case 530:
        goto Return_530;
    case 531:
        goto Return_531;
    case 532:
        goto Return_532;
    case 533:
        goto Return_533;
    case 534:
        goto Return_534;
    case 535:
        goto Return_535;
    case 536:
        goto Return_536;
    case 537:
        goto Return_537;
    case 538:
        goto Return_538;
    case 539:
        goto Return_539;
    case 540:
        goto Return_540;
    case 541:
        goto Return_541;
    case 542:
        goto Return_542;
    case 543:
        goto Return_543;
    case 544:
        goto Return_544;
    case 545:
        goto Return_545;
    case 546:
        goto Return_546;
    case 547:
        goto Return_547;
    case 548:
        goto Return_548;
    case 549:
        goto Return_549;
    case 550:
        goto Return_550;
    case 551:
        goto Return_551;
    case 552:
        goto Return_552;
    case 553:
        goto Return_553;
    case 554:
        goto Return_554;
    case 555:
        goto Return_555;
    case 556:
        goto Return_556;
    case 557:
        goto Return_557;
    case 558:
        goto Return_558;
    case 559:
        goto Return_559;
    case 560:
        goto Return_560;
    case 561:
        goto Return_561;
    case 562:
        goto Return_562;
    case 563:
        goto Return_563;
    case 564:
        goto Return_564;
    case 565:
        goto Return_565;
    case 566:
        goto Return_566;
    case 567:
        goto Return_567;
    case 568:
        goto Return_568;
    case 569:
        goto Return_569;
    case 570:
        goto Return_570;
    case 571:
        goto Return_571;
    case 572:
        goto Return_572;
    case 573:
        goto Return_573;
    case 574:
        goto Return_574;
    case 575:
        goto Return_575;
    case 576:
        goto Return_576;
    case 577:
        goto Return_577;
    case 578:
        goto Return_578;
    case 579:
        goto Return_579;
    case 580:
        goto Return_580;
    case 581:
        goto Return_581;
    case 582:
        goto Return_582;
    case 583:
        goto Return_583;
    case 584:
        goto Return_584;
    case 585:
        goto Return_585;
    case 586:
        goto Return_586;
    case 587:
        goto Return_587;
    case 588:
        goto Return_588;
    case 589:
        goto Return_589;
    case 590:
        goto Return_590;
    case 591:
        goto Return_591;
    case 592:
        goto Return_592;
    }
}
