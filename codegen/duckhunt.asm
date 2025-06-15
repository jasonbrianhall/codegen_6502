; PRG CRC32 checksum: 90ca616d
; CHR CRC32 checksum: 4e049e03
; Overall CRC32 checksum: 24598791
; Code base address: $c000

.db "NES", $1a                 ; Magic string that always begins an iNES header
.db $01                        ; Number of 16KB PRG-ROM banks
.db $01                        ; Number of 8KB CHR-ROM banks
.db $01                        ; Control bits 1
.db $00                        ; Control bits 2
.db $00                        ; Number of 8KB PRG-RAM banks
.db $00                        ; Video format NTSC/PAL
.dsb 6                         ; Padding to fill 16 BYTE iNES Header

.base $c000


APU_DMC_FREQ = $4010
APU_DMC_LEN = $4013
APU_DMC_RAW = $4011
APU_DMC_START = $4012
APU_FRAME = $4017
APU_NOISE_LO = $400E
APU_NOISE_VOL = $400C
APU_PL1_HI = $4003
APU_PL1_LO = $4002
APU_PL1_SWEEP = $4001
APU_PL1_VOL = $4000
APU_PL2_SWEEP = $4005
APU_PL2_VOL = $4004
APU_SND_CHN = $4015
APU_TRI_HI = $400B
APU_TRI_LINEAR = $4008
APU_TRI_LO = $400A
JOYPAD1 = $4016
JOYPAD2 = $4017
OAM_ADDR = $2003
OAM_DMA = $4014
PPU_ADDR = $2006
PPU_CTRL = $2000
PPU_DATA = $2007
PPU_MASK = $2001
PPU_SCROLL = $2005
PPU_STATUS = $2002


_var_0000_indexed = $0000
_var_0001 = $0001
_var_0002_indexed = $0002
_var_0003 = $0003
_var_0004 = $0004
_var_0005 = $0005
_var_0006 = $0006
_var_0007 = $0007
_var_0008 = $0008
_var_0009 = $0009
_var_000a = $000A
_var_000c = $000C
_var_000d = $000D
_var_000e = $000E
_var_000f = $000F
_var_0010_indexed = $0010
_var_0014_indexed = $0014
_var_0015 = $0015
_var_0016_indexed = $0016
_var_001b = $001B
_var_001c_indexed = $001C
_var_001d = $001D
_var_001f = $001F
_var_0020 = $0020
_var_0021 = $0021
_var_0022 = $0022
_var_0023 = $0023
_var_0024 = $0024
_var_0025 = $0025
_var_0026 = $0026
_var_0027 = $0027
_var_0028 = $0028
_var_0029 = $0029
_var_002a_indexed = $002A
_var_002b_indexed = $002B
_var_002d = $002D
_var_002f = $002F
_var_0030_indexed = $0030
_var_0031 = $0031
_var_0040_indexed = $0040
_var_0052_indexed = $0052
_var_0080_indexed = $0080
_var_0081_indexed = $0081
_var_0082_indexed = $0082
_var_0083_indexed = $0083
_var_008f_indexed = $008F
_var_0091 = $0091
_var_009a = $009A
_var_009b = $009B
_var_009d = $009D
_var_009f = $009F
_var_00a1 = $00A1
_var_00a2_indexed = $00A2
_var_00a6 = $00A6
_var_00a9_indexed = $00A9
_var_00aa = $00AA
_var_00ab = $00AB
_var_00ad = $00AD
_var_00b0 = $00B0
_var_00b1 = $00B1
_var_00b2 = $00B2
_var_00b5 = $00B5
_var_00b6 = $00B6
_var_00b7 = $00B7
_var_00b8 = $00B8
_var_00b9 = $00B9
_var_00ba = $00BA
_var_00bb = $00BB
_var_00bc = $00BC
_var_00bd = $00BD
_var_00be = $00BE
_var_00c1 = $00C1
_var_00c2 = $00C2
_var_00c3_indexed = $00C3
_var_00c4_indexed = $00C4
_var_00c5_indexed = $00C5
_var_00c6_indexed = $00C6
_var_00c7_indexed = $00C7
_var_00c8_indexed = $00C8
_var_00c9_indexed = $00C9
_var_00ca_indexed = $00CA
_var_00cd_indexed = $00CD
_var_00d0_indexed = $00D0
_var_00d1 = $00D1
_var_00d2_indexed = $00D2
_var_00d3 = $00D3
_var_00d4_indexed = $00D4
_var_00d5_indexed = $00D5
_var_00d8 = $00D8
_var_00d9 = $00D9
_var_00da = $00DA
_var_00db = $00DB
_var_00dc_indexed = $00DC
_var_00e0_indexed = $00E0
_var_00e4 = $00E4
_var_00e5 = $00E5
_var_00e6 = $00E6
_var_00ea = $00EA
_var_00eb = $00EB
_var_00ec = $00EC
_var_00ed = $00ED
_var_00ee = $00EE
_var_00ef = $00EF
_var_00f0 = $00F0
_var_00f1 = $00F1
_var_00f2 = $00F2
_var_00f3 = $00F3
_var_00f4_indexed = $00F4
_var_00f6_indexed = $00F6
_var_00f8_indexed = $00F8
_var_00f9_indexed = $00F9
_var_00fa_indexed = $00FA
_var_00fb = $00FB
_var_00fc_indexed = $00FC
_var_00fd = $00FD
_var_00fe_indexed = $00FE
_var_00ff = $00FF
_var_0200_indexed = $0200
_var_02f0_indexed = $02F0
_var_02f1_indexed = $02F1
_var_02f2_indexed = $02F2
_var_02f3_indexed = $02F3
_var_02f4_indexed = $02F4
_var_02f5_indexed = $02F5
_var_02f6_indexed = $02F6
_var_02f7_indexed = $02F7
_var_0300_indexed = $0300
_var_0301_indexed = $0301
_var_0302_indexed = $0302
_var_0303_indexed = $0303
_var_030a_indexed = $030A
_var_030b_indexed = $030B
_var_0350 = $0350
_var_0351 = $0351
_var_03a0 = $03A0
_var_03a1 = $03A1
_var_03ef_indexed = $03EF
_var_03f0_indexed = $03F0
_var_0430_indexed = $0430
_var_0440_indexed = $0440
_var_0442_indexed = $0442
_var_0500_indexed = $0500
_var_0501_indexed = $0501
_var_0502 = $0502
_var_0560 = $0560
_var_0561_indexed = $0561
_var_05ec = $05EC
_var_05ed = $05ED
_var_05ee = $05EE
_var_05ef = $05EF
_var_05f0_indexed = $05F0
_var_05fc = $05FC
_var_05fd = $05FD
_var_05fe = $05FE
_var_05ff = $05FF
_var_0610 = $0610
_var_0612 = $0612
_var_32c9_indexed = $32C9
_var_3ccd_indexed = $3CCD
_var_3dcc_indexed = $3DCC
_var_3dd2_indexed = $3DD2
_var_64fa_indexed = $64FA

Reset:
  cld                            ; $C000  D8
  sei                            ; $C001  78

_label_c002:
  lda PPU_STATUS                 ; $C002  AD 02 20
  bpl _label_c002                ; $C005  10 FB
  ldx #$00                       ; $C007  A2 00
  stx PPU_CTRL                   ; $C009  8E 00 20
  stx PPU_MASK                   ; $C00C  8E 01 20
  dex                            ; $C00F  CA
  txs                            ; $C010  9A
  ldx a:_var_05ec                ; $C011  AE EC 05
  ldy #$06                       ; $C014  A0 06
  sty _var_0001                  ; $C016  84 01
  ldy #$00                       ; $C018  A0 00
  sty _var_0000_indexed          ; $C01A  84 00
  lda #$00                       ; $C01C  A9 00

_label_c01e:
  sta (_var_0000_indexed),Y      ; $C01E  91 00
  dey                            ; $C020  88
  bne _label_c01e                ; $C021  D0 FB
  dec _var_0001                  ; $C023  C6 01
  bpl _label_c01e                ; $C025  10 F7
  txa                            ; $C027  8A
  bne _label_c02c                ; $C028  D0 02
  ldx #$5F                       ; $C02A  A2 5F

_label_c02c:
  stx a:_var_05ec                ; $C02C  8E EC 05
  jsr _func_c22b                 ; $C02F  20 2B C2
  jsr _func_c23b                 ; $C032  20 3B C2
  ldy #$00                       ; $C035  A0 00
  sta PPU_SCROLL                 ; $C037  8D 05 20
  sta PPU_SCROLL                 ; $C03A  8D 05 20
  ldy #$01                       ; $C03D  A0 01
  sty _var_0024                  ; $C03F  84 24
  lda #$0F                       ; $C041  A9 0F
  sta APU_SND_CHN                ; $C043  8D 15 40
  jsr _func_f581                 ; $C046  20 81 F5
  lda #$90                       ; $C049  A9 90
  sta PPU_CTRL                   ; $C04B  8D 00 20
  sta _var_0008                  ; $C04E  85 08
  lda #$02                       ; $C050  A9 02
  sta _var_0009                  ; $C052  85 09
  ldx #$0B                       ; $C054  A2 0B

_label_c056:
  lda a:_data_e5df_indexed,X     ; $C056  BD DF E5
  sta a:_var_05f0_indexed,X      ; $C059  9D F0 05
  dex                            ; $C05C  CA
  bpl _label_c056                ; $C05D  10 F7
  bmi _label_c07c                ; $C05F  30 1B

_label_c061:
  lda _var_0024                  ; $C061  A5 24
  beq _label_c06b                ; $C063  F0 06
  lda _var_0026                  ; $C065  A5 26
  cmp #$01                       ; $C067  C9 01
  bne _label_c06e                ; $C069  D0 03

_label_c06b:
  jsr _func_f56c                 ; $C06B  20 6C F5

_label_c06e:
  jsr _func_c348                 ; $C06E  20 48 C3
  jsr _func_c284                 ; $C071  20 84 C2
  jsr _func_c0b3                 ; $C074  20 B3 C0
  inc _var_002f                  ; $C077  E6 2F
  jsr _func_c61e                 ; $C079  20 1E C6

_label_c07c:
  lda _var_0020                  ; $C07C  A5 20
  bne _label_c061                ; $C07E  D0 E1
  jsr _func_c588                 ; $C080  20 88 C5
  jmp _label_c07c                ; $C083  4C 7C C0

NMI:
  php                            ; $C086  08
  pha                            ; $C087  48
  txa                            ; $C088  8A
  pha                            ; $C089  48
  tya                            ; $C08A  98
  pha                            ; $C08B  48
  lda #$00                       ; $C08C  A9 00
  sta OAM_ADDR                   ; $C08E  8D 03 20
  lda #$02                       ; $C091  A9 02
  sta OAM_DMA                    ; $C093  8D 14 40
  lda _var_0022                  ; $C096  A5 22
  bne _label_c0a6                ; $C098  D0 0C
  jsr _func_c2bf                 ; $C09A  20 BF C2
  jsr _func_c249                 ; $C09D  20 49 C2
  jsr _func_c263                 ; $C0A0  20 63 C2
  jsr _func_c3c1                 ; $C0A3  20 C1 C3

_label_c0a6:
  ldy #$01                       ; $C0A6  A0 01
  sty _var_0022                  ; $C0A8  84 22
  sty _var_0020                  ; $C0AA  84 20
  pla                            ; $C0AC  68
  tay                            ; $C0AD  A8
  pla                            ; $C0AE  68
  tax                            ; $C0AF  AA
  pla                            ; $C0B0  68
  plp                            ; $C0B1  28
  rti                            ; $C0B2  40

_func_c0b3:
  lda _var_0024                  ; $C0B3  A5 24
  beq _label_c0ba                ; $C0B5  F0 03
  jmp _label_c14e                ; $C0B7  4C 4E C1

_label_c0ba:
  lda _var_0016_indexed          ; $C0BA  A5 16
  and #$10                       ; $C0BC  29 10
  beq _label_c11e                ; $C0BE  F0 5E
  ldy a:_var_05fc                ; $C0C0  AC FC 05
  bne _label_c123                ; $C0C3  D0 5E
  iny                            ; $C0C5  C8
  sty a:_var_05fc                ; $C0C6  8C FC 05
  ldy _var_0025                  ; $C0C9  A4 25
  cpy #$10                       ; $C0CB  C0 10
  beq _label_c0ff                ; $C0CD  F0 30
  cpy #$03                       ; $C0CF  C0 03
  beq _label_c0df                ; $C0D1  F0 0C
  cpy #$04                       ; $C0D3  C0 04
  beq _label_c0df                ; $C0D5  F0 08
  cpy #$0B                       ; $C0D7  C0 0B
  beq _label_c0df                ; $C0D9  F0 04
  cpy #$0C                       ; $C0DB  C0 0C
  bne _label_c123                ; $C0DD  D0 44

_label_c0df:
  ldx #$05                       ; $C0DF  A2 05

_label_c0e1:
  lda _var_002a_indexed,X        ; $C0E1  B5 2A
  sta a:_var_0430_indexed,X      ; $C0E3  9D 30 04
  dex                            ; $C0E6  CA
  bpl _label_c0e1                ; $C0E7  10 F8
  lda _var_0009                  ; $C0E9  A5 09
  and #$0E                       ; $C0EB  29 0E
  sta PPU_MASK                   ; $C0ED  8D 01 20
  sta _var_0009                  ; $C0F0  85 09
  lda _var_0025                  ; $C0F2  A5 25
  sta _var_001d                  ; $C0F4  85 1D
  lda #$10                       ; $C0F6  A9 10
  sta _var_0025                  ; $C0F8  85 25
  lda #$07                       ; $C0FA  A9 07
  jmp _label_c112                ; $C0FC  4C 12 C1

_label_c0ff:
  lda _var_0009                  ; $C0FF  A5 09
  ora #$10                       ; $C101  09 10
  sta PPU_MASK                   ; $C103  8D 01 20
  sta _var_0009                  ; $C106  85 09
  lda #$11                       ; $C108  A9 11
  sta _var_0025                  ; $C10A  85 25
  lda #$30                       ; $C10C  A9 30
  sta _var_001c_indexed          ; $C10E  85 1C
  lda #$00                       ; $C110  A9 00

_label_c112:
  jsr _func_d464                 ; $C112  20 64 D4
  jsr _func_d4e2                 ; $C115  20 E2 D4
  jsr _func_c5d9                 ; $C118  20 D9 C5
  jmp _label_d521                ; $C11B  4C 21 D5

_label_c11e:
  lda #$00                       ; $C11E  A9 00
  sta a:_var_05fc                ; $C120  8D FC 05

_label_c123:
  lda _var_0025                  ; $C123  A5 25
  jsr _jump_engine_c35e          ; $C125  20 5E C3

  .word _label_c81d              ; $C128  1D C8
  .word _label_c839              ; $C12A  39 C8
  .word _label_c854              ; $C12C  54 C8
  .word _label_c86e              ; $C12E  6E C8
  .word _label_d2c9              ; $C130  C9 D2
  .word _label_c5e0              ; $C132  E0 C5
  .word _label_c779              ; $C134  79 C7
  .word _label_c72c              ; $C136  2C C7
  .word _label_d54b              ; $C138  4B D5
  .word _label_d56a              ; $C13A  6A D5
  .word _label_d593              ; $C13C  93 D5
  .word _label_d5d2              ; $C13E  D2 D5
  .word _label_d2c9              ; $C140  C9 D2
  .word _label_c7ef              ; $C142  EF C7
  .word _label_c5e0              ; $C144  E0 C5
  .word _label_c5e0              ; $C146  E0 C5
  .word _label_c5e0              ; $C148  E0 C5
  .word _label_c271              ; $C14A  71 C2
  .word _label_c625              ; $C14C  25 C6

_label_c14e:
  lda #$00                       ; $C14E  A9 00
  sta a:_var_05ff                ; $C150  8D FF 05
  lda #$01                       ; $C153  A9 01
  sta _var_00b9                  ; $C155  85 B9
  sta _var_00ba                  ; $C157  85 BA
  lda _var_0026                  ; $C159  A5 26
  beq _label_c18d                ; $C15B  F0 30
  jsr _func_d131                 ; $C15D  20 31 D1
  jsr _func_d160                 ; $C160  20 60 D1
  lda a:_var_05ff                ; $C163  AD FF 05
  cmp #$01                       ; $C166  C9 01
  beq _label_c176                ; $C168  F0 0C
  cmp #$02                       ; $C16A  C9 02
  beq _label_c199                ; $C16C  F0 2B
  lda _var_0016_indexed          ; $C16E  A5 16
  and #$30                       ; $C170  29 30
  cmp #$10                       ; $C172  C9 10
  bne _label_c189                ; $C174  D0 13

_label_c176:
  lda #$00                       ; $C176  A9 00
  sta _var_0024                  ; $C178  85 24
  sta _var_0025                  ; $C17A  85 25
  jsr _func_d4e2                 ; $C17C  20 E2 D4
  jsr _func_c5e1                 ; $C17F  20 E1 C5
  lda #$02                       ; $C182  A9 02
  sta _var_002a_indexed          ; $C184  85 2A
  sta _var_002d                  ; $C186  85 2D
  rts                            ; $C188  60

_label_c189:
  ldx _var_0026                  ; $C189  A6 26
  bne _label_c190                ; $C18B  D0 03

_label_c18d:
  jmp _label_c217                ; $C18D  4C 17 C2

_label_c190:
  cmp #$20                       ; $C190  C9 20
  bne _label_c1a9                ; $C192  D0 15
  lda a:_var_05fd                ; $C194  AD FD 05
  bne _label_c1b7                ; $C197  D0 1E

_label_c199:
  ldy a:_var_05fe                ; $C199  AC FE 05
  iny                            ; $C19C  C8
  cpy #$03                       ; $C19D  C0 03
  bne _label_c1a3                ; $C19F  D0 02
  ldy #$00                       ; $C1A1  A0 00

_label_c1a3:
  sty a:_var_05fe                ; $C1A3  8C FE 05
  jmp _label_c1b2                ; $C1A6  4C B2 C1

_label_c1a9:
  cmp #$00                       ; $C1A9  C9 00
  bne _label_c1b2                ; $C1AB  D0 05
  sta a:_var_05fd                ; $C1AD  8D FD 05
  beq _label_c1bb                ; $C1B0  F0 09

_label_c1b2:
  lda #$01                       ; $C1B2  A9 01
  sta a:_var_05fd                ; $C1B4  8D FD 05

_label_c1b7:
  lda #$FF                       ; $C1B7  A9 FF
  sta _var_002d                  ; $C1B9  85 2D

_label_c1bb:
  cpx #$01                       ; $C1BB  E0 01
  bne _label_c217                ; $C1BD  D0 58
  lda #$51                       ; $C1BF  A9 51
  sta a:_var_0500_indexed        ; $C1C1  8D 00 05
  lda #$24                       ; $C1C4  A9 24
  ldx #$04                       ; $C1C6  A2 04

_label_c1c8:
  sta a:_var_0501_indexed,X      ; $C1C8  9D 01 05
  dex                            ; $C1CB  CA
  bpl _label_c1c8                ; $C1CC  10 FA
  lda a:_var_05fe                ; $C1CE  AD FE 05
  asl a                          ; $C1D1  0A
  tax                            ; $C1D2  AA
  lda #$26                       ; $C1D3  A9 26
  sta a:_var_0501_indexed,X      ; $C1D5  9D 01 05
  ldx #$26                       ; $C1D8  A2 26
  ldy #$22                       ; $C1DA  A0 22
  jsr _func_c71d                 ; $C1DC  20 1D C7
  lda a:_var_05fe                ; $C1DF  AD FE 05
  asl a                          ; $C1E2  0A
  asl a                          ; $C1E3  0A
  clc                            ; $C1E4  18
  adc #$03                       ; $C1E5  69 03
  tax                            ; $C1E7  AA
  ldy #$05                       ; $C1E8  A0 05

_label_c1ea:
  lda a:_var_05f0_indexed,X      ; $C1EA  BD F0 05
  and #$0F                       ; $C1ED  29 0F
  sta a:_var_0501_indexed,Y      ; $C1EF  99 01 05
  dey                            ; $C1F2  88
  lda a:_var_05f0_indexed,X      ; $C1F3  BD F0 05
  lsr a                          ; $C1F6  4A
  lsr a                          ; $C1F7  4A
  lsr a                          ; $C1F8  4A
  lsr a                          ; $C1F9  4A
  sta a:_var_0501_indexed,Y      ; $C1FA  99 01 05
  dex                            ; $C1FD  CA
  dey                            ; $C1FE  88
  bpl _label_c1ea                ; $C1FF  10 E9
  lda a:_var_0501_indexed        ; $C201  AD 01 05
  bne _label_c20b                ; $C204  D0 05
  lda #$24                       ; $C206  A9 24
  sta a:_var_0501_indexed        ; $C208  8D 01 05

_label_c20b:
  lda #$16                       ; $C20B  A9 16
  sta a:_var_0500_indexed        ; $C20D  8D 00 05
  ldx #$12                       ; $C210  A2 12
  ldy #$23                       ; $C212  A0 23
  jsr _func_c71d                 ; $C214  20 1D C7

_label_c217:
  lda _var_002d                  ; $C217  A5 2D
  bne _label_c222                ; $C219  D0 07
  jsr _func_d509                 ; $C21B  20 09 D5
  lda #$FF                       ; $C21E  A9 FF
  sta _var_002d                  ; $C220  85 2D

_label_c222:
  lda _var_0026                  ; $C222  A5 26
  jsr _jump_engine_c35e          ; $C224  20 5E C3

  .word _label_c5aa              ; $C227  AA C5
  .word _label_c5e0              ; $C229  E0 C5

_func_c22b:
  lda #$02                       ; $C22B  A9 02
  jsr _func_c232                 ; $C22D  20 32 C2

_func_c230:
  lda #$01                       ; $C230  A9 01

_func_c232:
  sta _var_0001                  ; $C232  85 01
  lda #$24                       ; $C234  A9 24
  sta _var_0000_indexed          ; $C236  85 00
  jmp _func_c303                 ; $C238  4C 03 C3

_func_c23b:
  ldy #$00                       ; $C23B  A0 00
  lda #$F4                       ; $C23D  A9 F4

_label_c23f:
  sta a:_var_0200_indexed,Y      ; $C23F  99 00 02
  iny                            ; $C242  C8
  iny                            ; $C243  C8
  iny                            ; $C244  C8
  iny                            ; $C245  C8
  bne _label_c23f                ; $C246  D0 F7
  rts                            ; $C248  60

_func_c249:
  ldy _var_0023                  ; $C249  A4 23
  beq _label_c262                ; $C24B  F0 15
  dey                            ; $C24D  88
  tya                            ; $C24E  98
  asl a                          ; $C24F  0A
  tay                            ; $C250  A8
  lda a:_data_e532_indexed,Y     ; $C251  B9 32 E5
  ldx a:_data_e533_indexed,Y     ; $C254  BE 33 E5
  ldy #$00                       ; $C257  A0 00
  sty _var_0023                  ; $C259  84 23

_label_c25b:
  sta _var_0000_indexed          ; $C25B  85 00
  stx _var_0001                  ; $C25D  86 01
  jsr _func_c3b8                 ; $C25F  20 B8 C3

_label_c262:
  rts                            ; $C262  60

_func_c263:
  ldy _var_0027                  ; $C263  A4 27
  beq _label_c262                ; $C265  F0 FB
  ldy #$00                       ; $C267  A0 00
  sty _var_0027                  ; $C269  84 27
  lda #$00                       ; $C26B  A9 00
  ldx #$04                       ; $C26D  A2 04
  bne _label_c25b                ; $C26F  D0 EA

_label_c271:
  dec _var_001c_indexed          ; $C271  C6 1C
  bne _label_c283                ; $C273  D0 0E
  ldx #$05                       ; $C275  A2 05

_label_c277:
  lda a:_var_0430_indexed,X      ; $C277  BD 30 04
  sta _var_002a_indexed,X        ; $C27A  95 2A
  dex                            ; $C27C  CA
  bpl _label_c277                ; $C27D  10 F8
  lda _var_001d                  ; $C27F  A5 1D
  sta _var_0025                  ; $C281  85 25

_label_c283:
  rts                            ; $C283  60

_func_c284:
  ldx #$01                       ; $C284  A2 01
  stx JOYPAD1                    ; $C286  8E 16 40
  dex                            ; $C289  CA
  stx JOYPAD1                    ; $C28A  8E 16 40
  jsr _func_c291                 ; $C28D  20 91 C2
  inx                            ; $C290  E8

_func_c291:
  ldy #$08                       ; $C291  A0 08

_label_c293:
  pha                            ; $C293  48
  lda JOYPAD1,X                  ; $C294  BD 16 40
  sta _var_0000_indexed          ; $C297  85 00
  lsr a                          ; $C299  4A
  ora _var_0000_indexed          ; $C29A  05 00
  lsr a                          ; $C29C  4A
  pla                            ; $C29D  68
  rol a                          ; $C29E  2A
  dey                            ; $C29F  88
  bne _label_c293                ; $C2A0  D0 F1
  cmp a:_var_0440_indexed,X      ; $C2A2  DD 40 04
  bne _label_c2b6                ; $C2A5  D0 0F
  inc a:_var_0442_indexed,X      ; $C2A7  FE 42 04
  ldy a:_var_0442_indexed,X      ; $C2AA  BC 42 04
  cpy #$05                       ; $C2AD  C0 05
  bcc _label_c2be                ; $C2AF  90 0D
  sta _var_0016_indexed,X        ; $C2B1  95 16
  jmp _label_c2b9                ; $C2B3  4C B9 C2

_label_c2b6:
  sta a:_var_0440_indexed,X      ; $C2B6  9D 40 04

_label_c2b9:
  lda #$00                       ; $C2B9  A9 00
  sta a:_var_0442_indexed,X      ; $C2BB  9D 42 04

_label_c2be:
  rts                            ; $C2BE  60

_func_c2bf:
  lda _var_0021                  ; $C2BF  A5 21
  beq _label_c302                ; $C2C1  F0 3F
  lda #$61                       ; $C2C3  A9 61
  sta _var_0000_indexed          ; $C2C5  85 00
  lda #$05                       ; $C2C7  A9 05
  sta _var_0001                  ; $C2C9  85 01
  lda _var_0008                  ; $C2CB  A5 08
  and #$FB                       ; $C2CD  29 FB
  sta PPU_CTRL                   ; $C2CF  8D 00 20
  sta _var_0008                  ; $C2D2  85 08
  ldx PPU_STATUS                 ; $C2D4  AE 02 20
  ldy #$00                       ; $C2D7  A0 00
  beq _label_c2f4                ; $C2D9  F0 19

_label_c2db:
  sta PPU_ADDR                   ; $C2DB  8D 06 20
  iny                            ; $C2DE  C8
  lda (_var_0000_indexed),Y      ; $C2DF  B1 00
  sta PPU_ADDR                   ; $C2E1  8D 06 20
  iny                            ; $C2E4  C8
  lda (_var_0000_indexed),Y      ; $C2E5  B1 00
  and #$3F                       ; $C2E7  29 3F
  tax                            ; $C2E9  AA

_label_c2ea:
  iny                            ; $C2EA  C8
  lda (_var_0000_indexed),Y      ; $C2EB  B1 00
  sta PPU_DATA                   ; $C2ED  8D 07 20
  dex                            ; $C2F0  CA
  bne _label_c2ea                ; $C2F1  D0 F7
  iny                            ; $C2F3  C8

_label_c2f4:
  lda (_var_0000_indexed),Y      ; $C2F4  B1 00
  bne _label_c2db                ; $C2F6  D0 E3
  lda #$00                       ; $C2F8  A9 00
  sta a:_var_0560                ; $C2FA  8D 60 05
  sta a:_var_0561_indexed        ; $C2FD  8D 61 05
  sta _var_0021                  ; $C300  85 21

_label_c302:
  rts                            ; $C302  60

_func_c303:
  lda PPU_STATUS                 ; $C303  AD 02 20

_data_c306_indexed:
  lda _var_0008                  ; $C306  A5 08
  and #$FB                       ; $C308  29 FB
  sta PPU_CTRL                   ; $C30A  8D 00 20
  sta _var_0008                  ; $C30D  85 08
  lda #$1C                       ; $C30F  A9 1C
  clc                            ; $C311  18

_label_c312:
  adc #$04                       ; $C312  69 04
  dec _var_0001                  ; $C314  C6 01
  bne _label_c312                ; $C316  D0 FA
  sta _var_0002_indexed          ; $C318  85 02
  sta PPU_ADDR                   ; $C31A  8D 06 20
  lda #$00                       ; $C31D  A9 00
  sta PPU_ADDR                   ; $C31F  8D 06 20
  ldx #$04                       ; $C322  A2 04
  ldy #$00                       ; $C324  A0 00
  lda _var_0000_indexed          ; $C326  A5 00

_label_c328:
  sta PPU_DATA                   ; $C328  8D 07 20
  dey                            ; $C32B  88
  bne _label_c328                ; $C32C  D0 FA
  dex                            ; $C32E  CA
  bne _label_c328                ; $C32F  D0 F7
  lda _var_0002_indexed          ; $C331  A5 02
  adc #$03                       ; $C333  69 03
  sta PPU_ADDR                   ; $C335  8D 06 20
  lda #$C0                       ; $C338  A9 C0
  sta PPU_ADDR                   ; $C33A  8D 06 20
  ldy #$40                       ; $C33D  A0 40
  lda #$00                       ; $C33F  A9 00

_label_c341:
  sta PPU_DATA                   ; $C341  8D 07 20
  dey                            ; $C344  88
  bne _label_c341                ; $C345  D0 FA
  rts                            ; $C347  60

_func_c348:
  ldx #$01                       ; $C348  A2 01
  dec _var_002a_indexed          ; $C34A  C6 2A
  bpl _label_c354                ; $C34C  10 06
  lda #$0A                       ; $C34E  A9 0A
  sta _var_002a_indexed          ; $C350  85 2A
  ldx #$03                       ; $C352  A2 03

_label_c354:
  lda _var_002b_indexed,X        ; $C354  B5 2B
  beq _label_c35a                ; $C356  F0 02
  dec _var_002b_indexed,X        ; $C358  D6 2B

_label_c35a:
  dex                            ; $C35A  CA
  bpl _label_c354                ; $C35B  10 F7
  rts                            ; $C35D  60

_jump_engine_c35e:               ; jump engine detected
  stx _var_0028                  ; $C35E  86 28
  sty _var_0029                  ; $C360  84 29
  asl a                          ; $C362  0A
  tay                            ; $C363  A8
  iny                            ; $C364  C8
  pla                            ; $C365  68
  sta _var_0014_indexed          ; $C366  85 14
  pla                            ; $C368  68
  sta _var_0015                  ; $C369  85 15
  lda (_var_0014_indexed),Y      ; $C36B  B1 14
  tax                            ; $C36D  AA
  iny                            ; $C36E  C8
  lda (_var_0014_indexed),Y      ; $C36F  B1 14
  sta _var_0015                  ; $C371  85 15
  stx _var_0014_indexed          ; $C373  86 14
  ldx _var_0028                  ; $C375  A6 28
  ldy _var_0029                  ; $C377  A4 29
  jmp (_var_0014_indexed)        ; $C379  6C 14 00

_label_c37c:
  sta PPU_ADDR                   ; $C37C  8D 06 20
  iny                            ; $C37F  C8
  lda (_var_0000_indexed),Y      ; $C380  B1 00
  sta PPU_ADDR                   ; $C382  8D 06 20
  iny                            ; $C385  C8
  lda (_var_0000_indexed),Y      ; $C386  B1 00
  asl a                          ; $C388  0A
  pha                            ; $C389  48
  lda _var_0008                  ; $C38A  A5 08
  ora #$04                       ; $C38C  09 04
  bcs _label_c392                ; $C38E  B0 02
  and #$FB                       ; $C390  29 FB

_label_c392:
  sta PPU_CTRL                   ; $C392  8D 00 20
  sta _var_0008                  ; $C395  85 08
  pla                            ; $C397  68
  asl a                          ; $C398  0A
  bcc _label_c39e                ; $C399  90 03
  ora #$02                       ; $C39B  09 02
  iny                            ; $C39D  C8

_label_c39e:
  lsr a                          ; $C39E  4A
  lsr a                          ; $C39F  4A
  tax                            ; $C3A0  AA

_label_c3a1:
  bcs _label_c3a4                ; $C3A1  B0 01
  iny                            ; $C3A3  C8

_label_c3a4:
  lda (_var_0000_indexed),Y      ; $C3A4  B1 00
  sta PPU_DATA                   ; $C3A6  8D 07 20
  dex                            ; $C3A9  CA
  bne _label_c3a1                ; $C3AA  D0 F5
  sec                            ; $C3AC  38
  tya                            ; $C3AD  98
  adc _var_0000_indexed          ; $C3AE  65 00
  sta _var_0000_indexed          ; $C3B0  85 00
  lda #$00                       ; $C3B2  A9 00
  adc _var_0001                  ; $C3B4  65 01
  sta _var_0001                  ; $C3B6  85 01

_func_c3b8:
  ldx PPU_STATUS                 ; $C3B8  AE 02 20
  ldy #$00                       ; $C3BB  A0 00
  lda (_var_0000_indexed),Y      ; $C3BD  B1 00
  bne _label_c37c                ; $C3BF  D0 BB

_func_c3c1:
  pha                            ; $C3C1  48
  lda _var_000a                  ; $C3C2  A5 0A
  sta PPU_SCROLL                 ; $C3C4  8D 05 20
  lda $0B                        ; $C3C7  A5 0B
  sta PPU_SCROLL                 ; $C3C9  8D 05 20
  pla                            ; $C3CC  68
  rts                            ; $C3CD  60

_label_c3ce:
  lda #$01                       ; $C3CE  A9 01
  sta _var_0021                  ; $C3D0  85 21
  ldy #$00                       ; $C3D2  A0 00
  lda (_var_0002_indexed),Y      ; $C3D4  B1 02
  and #$0F                       ; $C3D6  29 0F
  sta _var_0005                  ; $C3D8  85 05
  lda (_var_0002_indexed),Y      ; $C3DA  B1 02
  lsr a                          ; $C3DC  4A
  lsr a                          ; $C3DD  4A
  lsr a                          ; $C3DE  4A
  lsr a                          ; $C3DF  4A
  sta _var_0004                  ; $C3E0  85 04
  ldx a:_var_0560                ; $C3E2  AE 60 05

_label_c3e5:
  lda _var_0001                  ; $C3E5  A5 01
  sta a:_var_0561_indexed,X      ; $C3E7  9D 61 05
  jsr _func_c426                 ; $C3EA  20 26 C4
  lda _var_0000_indexed          ; $C3ED  A5 00
  sta a:_var_0561_indexed,X      ; $C3EF  9D 61 05
  jsr _func_c426                 ; $C3F2  20 26 C4
  lda _var_0005                  ; $C3F5  A5 05
  sta _var_0006                  ; $C3F7  85 06
  sta a:_var_0561_indexed,X      ; $C3F9  9D 61 05

_label_c3fc:
  jsr _func_c426                 ; $C3FC  20 26 C4
  iny                            ; $C3FF  C8
  lda (_var_0002_indexed),Y      ; $C400  B1 02
  sta a:_var_0561_indexed,X      ; $C402  9D 61 05
  dec _var_0006                  ; $C405  C6 06
  bne _label_c3fc                ; $C407  D0 F3
  jsr _func_c426                 ; $C409  20 26 C4
  stx a:_var_0560                ; $C40C  8E 60 05
  clc                            ; $C40F  18
  lda #$20                       ; $C410  A9 20
  adc _var_0000_indexed          ; $C412  65 00
  sta _var_0000_indexed          ; $C414  85 00
  lda #$00                       ; $C416  A9 00
  adc _var_0001                  ; $C418  65 01
  sta _var_0001                  ; $C41A  85 01
  dec _var_0004                  ; $C41C  C6 04
  bne _label_c3e5                ; $C41E  D0 C5
  lda #$00                       ; $C420  A9 00
  sta a:_var_0561_indexed,X      ; $C422  9D 61 05
  rts                            ; $C425  60

_func_c426:
  inx                            ; $C426  E8
  txa                            ; $C427  8A
  cmp #$4F                       ; $C428  C9 4F
  bcc _label_c436                ; $C42A  90 0A
  ldx a:_var_0560                ; $C42C  AE 60 05
  lda #$00                       ; $C42F  A9 00
  sta a:_var_0561_indexed,X      ; $C431  9D 61 05
  pla                            ; $C434  68
  pla                            ; $C435  68

_label_c436:
  rts                            ; $C436  60

.byte $18, $69, $01, $29, $0f, $0a, $0a, $aa, $a5, $04, $f0, $27, $b5, $c3, $f0, $27 ; $C437
.byte $18, $b5, $c6, $85, $03, $a5, $07, $20, $bf, $c4, $95, $c6, $b5, $c5, $85, $03 ; $C447
.byte $a5, $06, $20, $bf, $c4, $95, $c5, $b5, $c4, $85, $03, $a5, $05, $20, $bf, $c4 ; $C457
.byte $95, $c4, $60, $b5, $c3, $f0, $d9, $38, $b5, $c6, $85, $03, $a5, $07, $20, $e0 ; $C467
.byte $c4, $95, $c6, $b5, $c5, $85, $03, $a5, $06, $20, $e0, $c4, $95, $c5, $b5, $c4 ; $C477
.byte $85, $03, $a5, $05, $20, $e0, $c4, $95, $c4, $b5, $c4, $d0, $08, $b5, $c5, $d0 ; $C487
.byte $04, $b5, $c6, $f0, $06, $b0, $20, $b5, $c3, $49, $ff, $95, $c3, $38, $a9, $00 ; $C497
.byte $85, $03, $b5, $c6, $20, $e0, $c4, $95, $c6, $b5, $c5, $20, $e0, $c4, $95, $c5 ; $C4A7
.byte $b5, $c4, $20, $e0, $c4, $95, $c4, $60 ; $C4B7

_func_c4bf:
  jsr _func_c502                 ; $C4BF  20 02 C5
  adc _var_0001                  ; $C4C2  65 01
  cmp #$0A                       ; $C4C4  C9 0A
  bcc _label_c4ca                ; $C4C6  90 02
  adc #$05                       ; $C4C8  69 05

_label_c4ca:
  clc                            ; $C4CA  18
  adc _var_0002_indexed          ; $C4CB  65 02
  sta _var_0002_indexed          ; $C4CD  85 02
  lda _var_0003                  ; $C4CF  A5 03
  and #$F0                       ; $C4D1  29 F0
  adc _var_0002_indexed          ; $C4D3  65 02
  bcc _label_c4db                ; $C4D5  90 04

_label_c4d7:
  adc #$5F                       ; $C4D7  69 5F
  sec                            ; $C4D9  38
  rts                            ; $C4DA  60

_label_c4db:
  cmp #$A0                       ; $C4DB  C9 A0
  bcs _label_c4d7                ; $C4DD  B0 F8
  rts                            ; $C4DF  60

_func_c4e0:
  jsr _func_c502                 ; $C4E0  20 02 C5
  sbc _var_0001                  ; $C4E3  E5 01
  sta _var_0001                  ; $C4E5  85 01
  bcs _label_c4f3                ; $C4E7  B0 0A
  adc #$0A                       ; $C4E9  69 0A
  sta _var_0001                  ; $C4EB  85 01
  lda _var_0002_indexed          ; $C4ED  A5 02
  adc #$0F                       ; $C4EF  69 0F
  sta _var_0002_indexed          ; $C4F1  85 02

_label_c4f3:
  lda _var_0003                  ; $C4F3  A5 03
  and #$F0                       ; $C4F5  29 F0
  sec                            ; $C4F7  38
  sbc _var_0002_indexed          ; $C4F8  E5 02
  bcs _label_c4ff                ; $C4FA  B0 03
  adc #$A0                       ; $C4FC  69 A0
  clc                            ; $C4FE  18

_label_c4ff:
  ora _var_0001                  ; $C4FF  05 01
  rts                            ; $C501  60

_func_c502:
  pha                            ; $C502  48
  and #$0F                       ; $C503  29 0F
  sta _var_0001                  ; $C505  85 01
  pla                            ; $C507  68
  and #$F0                       ; $C508  29 F0
  sta _var_0002_indexed          ; $C50A  85 02
  lda _var_0003                  ; $C50C  A5 03
  and #$0F                       ; $C50E  29 0F
  rts                            ; $C510  60

_func_c511:
  lda #$00                       ; $C511  A9 00
  sta _var_0004                  ; $C513  85 04
  clc                            ; $C515  18
  lda _var_0000_indexed          ; $C516  A5 00
  adc #$10                       ; $C518  69 10
  and #$F0                       ; $C51A  29 F0
  lsr a                          ; $C51C  4A
  lsr a                          ; $C51D  4A
  tay                            ; $C51E  A8
  lda _var_0000_indexed          ; $C51F  A5 00
  and #$07                       ; $C521  29 07
  asl a                          ; $C523  0A
  asl a                          ; $C524  0A
  tax                            ; $C525  AA

_label_c526:
  lda a:_var_00c3_indexed,Y      ; $C526  B9 C3 00
  beq _label_c57c                ; $C529  F0 51
  lda _var_00c7_indexed,X        ; $C52B  B5 C7
  beq _label_c555                ; $C52D  F0 26

_label_c52f:
  sec                            ; $C52F  38
  lda a:_var_00c6_indexed,Y      ; $C530  B9 C6 00
  sta _var_0003                  ; $C533  85 03
  lda _var_00ca_indexed,X        ; $C535  B5 CA
  jsr _func_c4e0                 ; $C537  20 E0 C4
  lda a:_var_00c5_indexed,Y      ; $C53A  B9 C5 00
  sta _var_0003                  ; $C53D  85 03
  lda _var_00c9_indexed,X        ; $C53F  B5 C9
  jsr _func_c4e0                 ; $C541  20 E0 C4
  lda a:_var_00c4_indexed,Y      ; $C544  B9 C4 00
  sta _var_0003                  ; $C547  85 03
  lda _var_00c8_indexed,X        ; $C549  B5 C8
  jsr _func_c4e0                 ; $C54B  20 E0 C4
  bcs _label_c580                ; $C54E  B0 30
  lda a:_var_00c3_indexed,Y      ; $C550  B9 C3 00
  bne _label_c585                ; $C553  D0 30

_label_c555:
  lda #$FF                       ; $C555  A9 FF
  sta _var_0004                  ; $C557  85 04
  sec                            ; $C559  38

_label_c55a:
  tya                            ; $C55A  98
  bne _label_c57b                ; $C55B  D0 1E
  bcc _label_c56f                ; $C55D  90 10
  lda _var_00c7_indexed,X        ; $C55F  B5 C7
  sta _var_00c3_indexed          ; $C561  85 C3
  lda _var_00c8_indexed,X        ; $C563  B5 C8
  sta _var_00c4_indexed          ; $C565  85 C4
  lda _var_00c9_indexed,X        ; $C567  B5 C9
  sta _var_00c5_indexed          ; $C569  85 C5
  lda _var_00ca_indexed,X        ; $C56B  B5 CA
  sta _var_00c6_indexed          ; $C56D  85 C6

_label_c56f:
  lda _var_0000_indexed          ; $C56F  A5 00
  and #$08                       ; $C571  29 08
  beq _label_c57b                ; $C573  F0 06
  dex                            ; $C575  CA
  dex                            ; $C576  CA
  dex                            ; $C577  CA
  dex                            ; $C578  CA
  bpl _label_c526                ; $C579  10 AB

_label_c57b:
  rts                            ; $C57B  60

_label_c57c:
  lda _var_00c7_indexed,X        ; $C57C  B5 C7
  beq _label_c52f                ; $C57E  F0 AF

_label_c580:
  lda a:_var_00c3_indexed,Y      ; $C580  B9 C3 00
  bne _label_c555                ; $C583  D0 D0

_label_c585:
  clc                            ; $C585  18
  bcc _label_c55a                ; $C586  90 D2

_func_c588:
  lda a:_var_05ec                ; $C588  AD EC 05
  and #$02                       ; $C58B  29 02
  sta _var_0007                  ; $C58D  85 07
  lda a:_var_05ed                ; $C58F  AD ED 05
  and #$02                       ; $C592  29 02
  eor _var_0007                  ; $C594  45 07
  clc                            ; $C596  18
  beq _label_c59a                ; $C597  F0 01
  sec                            ; $C599  38

_label_c59a:
  ror a:_var_05ec                ; $C59A  6E EC 05
  ror a:_var_05ed                ; $C59D  6E ED 05
  ror a:_var_05ee                ; $C5A0  6E EE 05
  ror a:_var_05ef                ; $C5A3  6E EF 05
  lda a:_var_05ec                ; $C5A6  AD EC 05
  rts                            ; $C5A9  60

_label_c5aa:
  jsr _func_c5e1                 ; $C5AA  20 E1 C5
  jsr _func_c230                 ; $C5AD  20 30 C2
  jsr _func_c5d9                 ; $C5B0  20 D9 C5
  lda #$02                       ; $C5B3  A9 02
  sta _var_0001                  ; $C5B5  85 01
  lda #$50                       ; $C5B7  A9 50
  sta _var_0000_indexed          ; $C5B9  85 00
  jsr _func_c303                 ; $C5BB  20 03 C3
  jsr _func_c23b                 ; $C5BE  20 3B C2
  jsr _func_c5d9                 ; $C5C1  20 D9 C5
  ldx #$04                       ; $C5C4  A2 04
  ldy #$E4                       ; $C5C6  A0 E4
  jsr _func_c617                 ; $C5C8  20 17 C6
  lda #$01                       ; $C5CB  A9 01
  sta _var_0023                  ; $C5CD  85 23
  lda #$01                       ; $C5CF  A9 01
  sta a:_var_05fd                ; $C5D1  8D FD 05
  inc _var_0026                  ; $C5D4  E6 26
  jmp _func_c5ee                 ; $C5D6  4C EE C5

_func_c5d9:
  jsr _func_c61e                 ; $C5D9  20 1E C6

_label_c5dc:
  lda _var_0020                  ; $C5DC  A5 20
  beq _label_c5dc                ; $C5DE  F0 FC

_label_c5e0:
  rts                            ; $C5E0  60

_func_c5e1:
  jsr _func_c5d9                 ; $C5E1  20 D9 C5
  lda _var_0009                  ; $C5E4  A5 09
  and #$E7                       ; $C5E6  29 E7

_label_c5e8:
  sta _var_0009                  ; $C5E8  85 09
  sta PPU_MASK                   ; $C5EA  8D 01 20
  rts                            ; $C5ED  60

_func_c5ee:
  jsr _func_c5d9                 ; $C5EE  20 D9 C5
  lda _var_0009                  ; $C5F1  A5 09
  ora #$18                       ; $C5F3  09 18
  bne _label_c5e8                ; $C5F5  D0 F1

_func_c5f7:
  sty _var_00a2_indexed          ; $C5F7  84 A2
  ldx #$00                       ; $C5F9  A2 00

_label_c5fb:
  lda a:_var_0300_indexed,Y      ; $C5FB  B9 00 03
  sta _var_0030_indexed,X        ; $C5FE  95 30
  iny                            ; $C600  C8
  inx                            ; $C601  E8
  cpx #$50                       ; $C602  E0 50
  bne _label_c5fb                ; $C604  D0 F5
  rts                            ; $C606  60

_func_c607:
  ldy _var_00a2_indexed          ; $C607  A4 A2
  ldx #$00                       ; $C609  A2 00

_label_c60b:
  lda _var_0030_indexed,X        ; $C60B  B5 30
  sta a:_var_0300_indexed,Y      ; $C60D  99 00 03
  iny                            ; $C610  C8
  inx                            ; $C611  E8
  cpx #$50                       ; $C612  E0 50
  bne _label_c60b                ; $C614  D0 F5
  rts                            ; $C616  60

_func_c617:
  stx _var_0000_indexed          ; $C617  86 00
  sty _var_0001                  ; $C619  84 01
  jmp _func_c3b8                 ; $C61B  4C B8 C3

_func_c61e:
  lda #$00                       ; $C61E  A9 00
  sta _var_0020                  ; $C620  85 20
  sta _var_0022                  ; $C622  85 22
  rts                            ; $C624  60

_label_c625:
  lda _var_002d                  ; $C625  A5 2D
  bne _label_c62d                ; $C627  D0 04
  lda $1E                        ; $C629  A5 1E
  sta _var_0025                  ; $C62B  85 25

_label_c62d:
  rts                            ; $C62D  60

.byte $86, $1e, $85, $2d, $a9, $12, $85, $25, $60 ; $C62E

_label_c637:
  ldy #$00                       ; $C637  A0 00
  tya                            ; $C639  98

_label_c63a:
  sta a:_var_0300_indexed,Y      ; $C63A  99 00 03
  iny                            ; $C63D  C8
  bne _label_c63a                ; $C63E  D0 FA
  rts                            ; $C640  60

_func_c641:
  lda #$00                       ; $C641  A9 00
  ldx #$30                       ; $C643  A2 30

_label_c645:
  sta _var_0000_indexed,X        ; $C645  95 00
  inx                            ; $C647  E8
  bne _label_c645                ; $C648  D0 FB
  rts                            ; $C64A  60

_func_c64b:
  lda #$00                       ; $C64B  A9 00
  ldx #$7F                       ; $C64D  A2 7F

_label_c64f:
  sta _var_0040_indexed,X        ; $C64F  95 40
  dex                            ; $C651  CA
  bpl _label_c64f                ; $C652  10 FB
  rts                            ; $C654  60

.byte $a2, $03, $a0, $05, $b5, $c3, $29, $0f, $99, $01, $05, $88, $b5, $c3, $4a, $4a ; $C655
.byte $4a, $4a, $99, $01, $05, $ca, $88, $10, $eb, $a9, $16, $8d, $00, $05, $ae, $dc ; $C665
.byte $e5, $ac, $db, $e5, $4c, $1d, $c7 ; $C675

_label_c67c:
  lda _var_000c                  ; $C67C  A5 0C
  asl a                          ; $C67E  0A
  tay                            ; $C67F  A8
  lda a:_data_eb30_indexed,Y     ; $C680  B9 30 EB
  sta _var_0010_indexed          ; $C683  85 10
  lda a:_data_eb31_indexed,Y     ; $C685  B9 31 EB
  sta $11                        ; $C688  85 11
  ldy #$00                       ; $C68A  A0 00
  ldx #$00                       ; $C68C  A2 00

_label_c68e:
  lda (_var_0010_indexed),Y      ; $C68E  B1 10
  cmp #$AA                       ; $C690  C9 AA
  bne _label_c695                ; $C692  D0 01

_label_c694:
  rts                            ; $C694  60

_label_c695:
  clc                            ; $C695  18
  adc _var_00b1                  ; $C696  65 B1
  cmp #$A8                       ; $C698  C9 A8
  bcc _label_c69e                ; $C69A  90 02
  lda #$F4                       ; $C69C  A9 F4

_label_c69e:
  sta _var_000d                  ; $C69E  85 0D
  iny                            ; $C6A0  C8
  lda (_var_0010_indexed),Y      ; $C6A1  B1 10
  clc                            ; $C6A3  18
  adc _var_00b2                  ; $C6A4  65 B2
  sta _var_000e                  ; $C6A6  85 0E
  iny                            ; $C6A8  C8
  lda _var_000d                  ; $C6A9  A5 0D
  sta a:_var_0200_indexed,X      ; $C6AB  9D 00 02
  inx                            ; $C6AE  E8
  lda #$56                       ; $C6AF  A9 56
  sta a:_var_0200_indexed,X      ; $C6B1  9D 00 02
  inx                            ; $C6B4  E8
  lda #$00                       ; $C6B5  A9 00
  sta a:_var_0200_indexed,X      ; $C6B7  9D 00 02
  inx                            ; $C6BA  E8
  lda _var_000e                  ; $C6BB  A5 0E
  sta a:_var_0200_indexed,X      ; $C6BD  9D 00 02
  inx                            ; $C6C0  E8
  jmp _label_c68e                ; $C6C1  4C 8E C6

_func_c6c4:
  lda _var_00ad                  ; $C6C4  A5 AD
  beq _label_c694                ; $C6C6  F0 CC
  lda #$00                       ; $C6C8  A9 00
  sta _var_00ad                  ; $C6CA  85 AD

_func_c6cc:
  lda #$D6                       ; $C6CC  A9 D6
  ldy _var_001f                  ; $C6CE  A4 1F
  cpy #$02                       ; $C6D0  C0 02
  bne _label_c6d6                ; $C6D2  D0 02
  lda #$D4                       ; $C6D4  A9 D4

_label_c6d6:
  sta _var_000c                  ; $C6D6  85 0C
  ldx #$09                       ; $C6D8  A2 09

_label_c6da:
  ldy _var_000c                  ; $C6DA  A4 0C
  lda a:_var_03f0_indexed,X      ; $C6DC  BD F0 03
  beq _label_c6e2                ; $C6DF  F0 01
  dey                            ; $C6E1  88

_label_c6e2:
  tya                            ; $C6E2  98
  sta a:_var_0501_indexed,X      ; $C6E3  9D 01 05
  dex                            ; $C6E6  CA
  bpl _label_c6da                ; $C6E7  10 F1
  lda #$1A                       ; $C6E9  A9 1A
  sta a:_var_0500_indexed        ; $C6EB  8D 00 05
  ldx #$4C                       ; $C6EE  A2 4C
  ldy #$23                       ; $C6F0  A0 23
  jmp _func_c71d                 ; $C6F2  4C 1D C7

_func_c6f5:
  lda _var_00be                  ; $C6F5  A5 BE
  beq _label_c694                ; $C6F7  F0 9B
  lda #$00                       ; $C6F9  A9 00
  sta _var_00be                  ; $C6FB  85 BE
  ldx _var_00ba                  ; $C6FD  A6 BA
  ldy #$00                       ; $C6FF  A0 00

_label_c701:
  cpx #$00                       ; $C701  E0 00
  beq _label_c70a                ; $C703  F0 05
  dex                            ; $C705  CA
  lda #$D9                       ; $C706  A9 D9
  bne _label_c70c                ; $C708  D0 02

_label_c70a:
  lda #$B7                       ; $C70A  A9 B7

_label_c70c:
  sta a:_var_0501_indexed,Y      ; $C70C  99 01 05
  iny                            ; $C70F  C8
  cpy #$03                       ; $C710  C0 03
  bne _label_c701                ; $C712  D0 ED
  lda #$13                       ; $C714  A9 13
  sta a:_var_0500_indexed        ; $C716  8D 00 05
  ldx #$43                       ; $C719  A2 43
  ldy #$23                       ; $C71B  A0 23

_func_c71d:
  stx _var_0000_indexed          ; $C71D  86 00
  sty _var_0001                  ; $C71F  84 01
  ldx #$00                       ; $C721  A2 00
  ldy #$05                       ; $C723  A0 05
  stx _var_0002_indexed          ; $C725  86 02
  sty _var_0003                  ; $C727  84 03
  jmp _label_c3ce                ; $C729  4C CE C3

_label_c72c:
  lda _var_002d                  ; $C72C  A5 2D
  beq _label_c73a                ; $C72E  F0 0A
  lda _var_001f                  ; $C730  A5 1F
  cmp #$02                       ; $C732  C9 02
  beq _label_c739                ; $C734  F0 03
  jmp _func_cc94                 ; $C736  4C 94 CC

_label_c739:
  rts                            ; $C739  60

_label_c73a:
  ldx #$03                       ; $C73A  A2 03

_label_c73c:
  lda _var_00c3_indexed,X        ; $C73C  B5 C3
  sta _var_00c7_indexed,X        ; $C73E  95 C7
  dex                            ; $C740  CA
  bpl _label_c73c                ; $C741  10 F9
  lda _var_001f                  ; $C743  A5 1F
  asl a                          ; $C745  0A
  asl a                          ; $C746  0A
  tay                            ; $C747  A8
  sty _var_000f                  ; $C748  84 0F
  ldx #$00                       ; $C74A  A2 00

_label_c74c:
  lda a:_var_05f0_indexed,Y      ; $C74C  B9 F0 05
  sta _var_00c3_indexed,X        ; $C74F  95 C3
  iny                            ; $C751  C8
  inx                            ; $C752  E8
  cpx #$04                       ; $C753  E0 04
  bne _label_c74c                ; $C755  D0 F5
  lda #$F0                       ; $C757  A9 F0
  sta _var_0000_indexed          ; $C759  85 00
  jsr _func_c511                 ; $C75B  20 11 C5
  ldy _var_000f                  ; $C75E  A4 0F
  ldx #$00                       ; $C760  A2 00

_label_c762:
  lda _var_00c3_indexed,X        ; $C762  B5 C3
  sta a:_var_05f0_indexed,Y      ; $C764  99 F0 05
  iny                            ; $C767  C8
  inx                            ; $C768  E8
  cpx #$04                       ; $C769  E0 04
  bne _label_c762                ; $C76B  D0 F5
  ldy #$00                       ; $C76D  A0 00
  sty _var_00b5                  ; $C76F  84 B5
  sty _var_0026                  ; $C771  84 26
  iny                            ; $C773  C8
  sty _var_0024                  ; $C774  84 24
  jmp _func_c5e1                 ; $C776  4C E1 C5

_label_c779:
  jsr _func_d50d                 ; $C779  20 0D D5
  jsr _func_c5d9                 ; $C77C  20 D9 C5
  jsr _func_d4fa                 ; $C77F  20 FA D4
  lda #$01                       ; $C782  A9 01
  sta a:_var_03a0                ; $C784  8D A0 03
  sta a:_var_03a1                ; $C787  8D A1 03
  lda #$07                       ; $C78A  A9 07
  sta _var_0025                  ; $C78C  85 25
  lda #$15                       ; $C78E  A9 15
  sta _var_002d                  ; $C790  85 2D
  rts                            ; $C792  60

_func_c793:
  ldx #$0A                       ; $C793  A2 0A

_label_c795:
  cpx _var_00ab                  ; $C795  E4 AB
  bcc _label_c79f                ; $C797  90 06
  beq _label_c79f                ; $C799  F0 04
  lda #$B7                       ; $C79B  A9 B7
  bne _label_c7a1                ; $C79D  D0 02

_label_c79f:
  lda #$D7                       ; $C79F  A9 D7

_label_c7a1:
  sta a:_var_0500_indexed,X      ; $C7A1  9D 00 05
  dex                            ; $C7A4  CA
  bne _label_c795                ; $C7A5  D0 EE
  lda #$1A                       ; $C7A7  A9 1A
  sta a:_var_0500_indexed        ; $C7A9  8D 00 05
  ldx #$6C                       ; $C7AC  A2 6C
  ldy #$23                       ; $C7AE  A0 23
  jmp _func_c71d                 ; $C7B0  4C 1D C7

_func_c7b3:
  lda _var_00c1                  ; $C7B3  A5 C1
  sta _var_0003                  ; $C7B5  85 03
  lda #$01                       ; $C7B7  A9 01
  clc                            ; $C7B9  18
  jsr _func_c4bf                 ; $C7BA  20 BF C4
  sta _var_00c1                  ; $C7BD  85 C1
  lda #$12                       ; $C7BF  A9 12
  sta a:_var_0500_indexed        ; $C7C1  8D 00 05
  ldx #$DD                       ; $C7C4  A2 DD
  lda _var_001f                  ; $C7C6  A5 1F
  cmp #$02                       ; $C7C8  C9 02
  beq _label_c7ce                ; $C7CA  F0 02
  ldx #$50                       ; $C7CC  A2 50

_label_c7ce:
  stx a:_var_0502                ; $C7CE  8E 02 05
  ldx #$00                       ; $C7D1  A2 00
  lda _var_00c1                  ; $C7D3  A5 C1
  and #$F0                       ; $C7D5  29 F0
  beq _label_c7e1                ; $C7D7  F0 08
  lsr a                          ; $C7D9  4A
  lsr a                          ; $C7DA  4A
  lsr a                          ; $C7DB  4A
  lsr a                          ; $C7DC  4A
  sta a:_var_0501_indexed,X      ; $C7DD  9D 01 05
  inx                            ; $C7E0  E8

_label_c7e1:
  lda _var_00c1                  ; $C7E1  A5 C1
  and #$0F                       ; $C7E3  29 0F
  sta a:_var_0501_indexed,X      ; $C7E5  9D 01 05
  ldx #$05                       ; $C7E8  A2 05
  ldy #$23                       ; $C7EA  A0 23
  jmp _func_c71d                 ; $C7EC  4C 1D C7

_label_c7ef:
  lda _var_009d                  ; $C7EF  A5 9D
  beq _label_c7f6                ; $C7F1  F0 03
  jmp _func_c7fb                 ; $C7F3  4C FB C7

_label_c7f6:
  lda #$0A                       ; $C7F6  A9 0A
  sta _var_0025                  ; $C7F8  85 25
  rts                            ; $C7FA  60

_func_c7fb:
  lda _var_002b_indexed          ; $C7FB  A5 2B
  bne _label_c81c                ; $C7FD  D0 1D
  ldy _var_009d                  ; $C7FF  A4 9D
  beq _label_c81c                ; $C801  F0 19
  lda a:_data_ec1f_indexed,Y     ; $C803  B9 1F EC
  cmp #$AA                       ; $C806  C9 AA
  beq _label_c818                ; $C808  F0 0E
  pha                            ; $C80A  48
  iny                            ; $C80B  C8
  lda a:_data_ec1f_indexed,Y     ; $C80C  B9 1F EC
  sta _var_002b_indexed          ; $C80F  85 2B
  iny                            ; $C811  C8
  sty _var_009d                  ; $C812  84 9D
  pla                            ; $C814  68
  jmp _label_d46c                ; $C815  4C 6C D4

_label_c818:
  lda #$00                       ; $C818  A9 00
  sta _var_009d                  ; $C81A  85 9D

_label_c81c:
  rts                            ; $C81C  60

_label_c81d:
  jsr _func_c641                 ; $C81D  20 41 C6
  jsr _func_c5d9                 ; $C820  20 D9 C5
  jsr _func_c22b                 ; $C823  20 2B C2
  jsr _func_d4d9                 ; $C826  20 D9 D4
  ldx #$01                       ; $C829  A2 01
  lda a:_var_05fe                ; $C82B  AD FE 05
  sta _var_001f                  ; $C82E  85 1F
  cmp #$02                       ; $C830  C9 02
  bcc _label_c836                ; $C832  90 02
  ldx #$08                       ; $C834  A2 08

_label_c836:
  stx _var_0025                  ; $C836  86 25
  rts                            ; $C838  60

_label_c839:
  jsr _func_c5d9                 ; $C839  20 D9 C5
  ldx #$42                       ; $C83C  A2 42
  ldy #$E0                       ; $C83E  A0 E0
  jsr _func_c617                 ; $C840  20 17 C6
  lda #$02                       ; $C843  A9 02
  sta _var_0023                  ; $C845  85 23
  lda #$02                       ; $C847  A9 02
  sta _var_0025                  ; $C849  85 25
  jsr _func_c3c1                 ; $C84B  20 C1 C3
  jsr _func_c5ee                 ; $C84E  20 EE C5
  jmp _label_d515                ; $C851  4C 15 D5

_label_c854:
  jsr _func_d4d9                 ; $C854  20 D9 D4
  jsr _func_d2a4                 ; $C857  20 A4 D2
  jsr _func_c793                 ; $C85A  20 93 C7
  jsr _func_c7b3                 ; $C85D  20 B3 C7
  nop                            ; $C860  EA
  nop                            ; $C861  EA
  nop                            ; $C862  EA
  lda #$00                       ; $C863  A9 00
  sta _var_00b5                  ; $C865  85 B5
  sta _var_009d                  ; $C867  85 9D
  lda #$03                       ; $C869  A9 03
  sta _var_0025                  ; $C86B  85 25
  rts                            ; $C86D  60

_label_c86e:
  jsr _func_d131                 ; $C86E  20 31 D1
  jsr _func_d160                 ; $C871  20 60 D1
  jsr _func_cc94                 ; $C874  20 94 CC
  jsr _func_c890                 ; $C877  20 90 C8
  jsr _func_c6f5                 ; $C87A  20 F5 C6
  jsr _func_d3d2                 ; $C87D  20 D2 D3
  jsr _func_c6c4                 ; $C880  20 C4 C6
  jsr _func_cfba                 ; $C883  20 BA CF
  jsr _func_d428                 ; $C886  20 28 D4
  jsr _func_c7fb                 ; $C889  20 FB C7
  nop                            ; $C88C  EA
  nop                            ; $C88D  EA
  nop                            ; $C88E  EA
  rts                            ; $C88F  60

_func_c890:
  lda a:_var_0300_indexed        ; $C890  AD 00 03
  beq _label_c8a2                ; $C893  F0 0D
  ldy #$00                       ; $C895  A0 00
  sty _var_00a1                  ; $C897  84 A1
  jsr _func_c5f7                 ; $C899  20 F7 C5
  jsr _func_c902                 ; $C89C  20 02 C9
  jsr _func_c607                 ; $C89F  20 07 C6

_label_c8a2:
  lda a:_var_0350                ; $C8A2  AD 50 03
  beq _label_c8b4                ; $C8A5  F0 0D
  ldy #$50                       ; $C8A7  A0 50
  inc _var_00a1                  ; $C8A9  E6 A1
  jsr _func_c5f7                 ; $C8AB  20 F7 C5
  jsr _func_c902                 ; $C8AE  20 02 C9
  jsr _func_c607                 ; $C8B1  20 07 C6

_label_c8b4:
  lda _var_00b9                  ; $C8B4  A5 B9
  beq _label_c901                ; $C8B6  F0 49
  ldy _var_009f                  ; $C8B8  A4 9F
  bne _label_c8c4                ; $C8BA  D0 08
  ldy #$41                       ; $C8BC  A0 41
  lda _var_00ba                  ; $C8BE  A5 BA
  bne _label_c8c4                ; $C8C0  D0 02
  ldy #$15                       ; $C8C2  A0 15

_label_c8c4:
  dey                            ; $C8C4  88
  sty _var_009f                  ; $C8C5  84 9F
  lda _var_00bc                  ; $C8C7  A5 BC
  bne _label_c8fb                ; $C8C9  D0 30
  lda a:_var_0301_indexed        ; $C8CB  AD 01 03
  bne _label_c901                ; $C8CE  D0 31
  lda a:_var_0351                ; $C8D0  AD 51 03
  bne _label_c901                ; $C8D3  D0 2C
  lda _var_002b_indexed          ; $C8D5  A5 2B
  bne _label_c901                ; $C8D7  D0 28
  lda #$0A                       ; $C8D9  A9 0A
  ldy #$07                       ; $C8DB  A0 07
  ldx _var_00bd                  ; $C8DD  A6 BD
  beq _label_c8e5                ; $C8DF  F0 04
  lda #$0C                       ; $C8E1  A9 0C
  ldy #$02                       ; $C8E3  A0 02

_label_c8e5:
  sta a:_var_03a1                ; $C8E5  8D A1 03
  sty _var_0023                  ; $C8E8  84 23
  jsr _func_c5d9                 ; $C8EA  20 D9 C5
  jsr _func_d446                 ; $C8ED  20 46 D4
  lda #$40                       ; $C8F0  A9 40
  sta _var_002b_indexed          ; $C8F2  85 2B
  lda #$00                       ; $C8F4  A9 00
  sta _var_00b9                  ; $C8F6  85 B9
  jmp _func_d464                 ; $C8F8  4C 64 D4

_label_c8fb:
  lda _var_00a6                  ; $C8FB  A5 A6
  beq _label_c901                ; $C8FD  F0 02
  dec _var_00a6                  ; $C8FF  C6 A6

_label_c901:
  rts                            ; $C901  60

_func_c902:
  lda _var_0031                  ; $C902  A5 31
  jsr _jump_engine_c35e          ; $C904  20 5E C3
  cpx #$C5                       ; $C907  E0 C5
  ora a:_var_32c9_indexed,Y      ; $C909  19 C9 32
  cmp #$19                       ; $C90C  C9 19
  dex                            ; $C90E  CA
  slo a:_var_3dcc_indexed,X      ; $C90F  1F CC 3D
  cpy a:_data_cc4f               ; $C912  CC 4F CC
.byte $7c, $cc, $8b              ; $C915  7C CC 8B  disambiguous instruction: nop a:$8BCC,X
  cpy a:$1FA2                    ; $C918  CC A2 1F

_label_c91b:
  lda a:_data_e5eb_indexed,X     ; $C91B  BD EB E5
  sta _var_0030_indexed,X        ; $C91E  95 30
  dex                            ; $C920  CA
  bpl _label_c91b                ; $C921  10 F8
  lda _var_00a1                  ; $C923  A5 A1
  beq _label_c92f                ; $C925  F0 08
  lda #$40                       ; $C927  A9 40
  sta $36                        ; $C929  85 36
  lda #$7F                       ; $C92B  A9 7F
  sta $37                        ; $C92D  85 37

_label_c92f:
  inc _var_0031                  ; $C92F  E6 31
  rts                            ; $C931  60

.byte $a5, $b9, $f0, $fb, $a5, $a6, $d0, $f7, $20, $88, $c5, $29, $0f, $a4, $1f, $d0 ; $C932
.byte $03, $18, $69, $10, $c5, $9c, $d0, $0e, $18, $69, $01, $c9, $10, $f0, $04, $c9 ; $C942
.byte $20, $d0, $03, $38, $e9, $10, $85, $9c, $0a, $aa, $bd, $0b, $e6, $85, $44, $bd ; $C952
.byte $0c, $e6, $85, $45, $20, $88, $c5, $29, $3f, $a8, $c8, $84, $a6, $a0, $00, $b1 ; $C962
.byte $44, $c8, $84, $47, $85, $33, $a0, $00, $a6, $99, $f0, $02, $a0, $02, $84, $3c ; $C972
.byte $e6, $99, $a6, $98, $bd, $66, $e7, $c0, $00, $f0, $05, $29, $0f, $4c, $96, $c9 ; $C982
.byte $4a, $4a, $4a, $4a, $85, $3f, $a6, $c1, $a5, $1f, $d0, $1b, $a9, $0b, $e0, $12 ; $C992
.byte $b0, $0e, $a9, $0a, $e0, $11, $b0, $08, $a9, $09, $e0, $10, $b0, $02, $ca, $8a ; $C9A2
.byte $aa, $bd, $5a, $e7, $4c, $d0, $c9, $a9, $1b, $a6, $c1, $e0, $10, $b0, $08, $ca ; $C9B2
.byte $8a, $85, $0c, $0a, $18, $65, $0c, $18, $65, $3f, $aa, $bd, $3c, $e7, $85, $5e ; $C9C2
.byte $a6, $c1, $a9, $0b, $e0, $27, $b0, $08, $a9, $0a, $e0, $24, $b0, $02, $a9, $09 ; $C9D2
.byte $85, $3a, $a9, $00, $85, $46, $85, $42, $85, $4e, $85, $4f, $a9, $01, $85, $4b ; $C9E2
.byte $85, $ae, $a5, $1f, $d0, $16, $a6, $c1, $a9, $7d, $e0, $11, $90, $08, $a9, $5d ; $C9F2
.byte $e0, $20, $90, $02, $a9, $3e, $85, $4c, $a9, $00, $85, $af, $e6, $bb, $a5, $bb ; $CA02
.byte $85, $3b, $c6, $bc, $e6, $31, $60, $a5, $2f, $29, $07, $d0, $03, $20, $ee, $d4 ; $CA12
.byte $a5, $9f, $d0, $03, $20, $2c, $d5, $a5, $ba, $d0, $11, $a5, $4e, $d0, $0d, $a9 ; $CA22
.byte $01, $85, $4e, $a9, $f0, $85, $46, $a9, $00, $4c, $77, $cb, $a5, $1f, $f0, $03 ; $CA32
.byte $4c, $59, $cb, $a5, $4b, $f0, $0a, $a5, $32, $c9, $88, $b0, $f3, $a9, $00, $85 ; $CA42
.byte $4b, $a2, $01, $a5, $4c, $f0, $17, $a5, $ba, $d0, $09, $85, $4c, $20, $96, $cf ; $CA52
.byte $a2, $01, $d0, $0a, $ca, $a5, $2f, $4a, $90, $04, $c6, $4c, $f0, $ef, $86, $ae ; $CA62
.byte $e0, $01, $f0, $14, $a5, $16, $29, $0f, $d0, $2c, $a5, $17, $29, $0f, $d0, $26 ; $CA72
.byte $a9, $00, $85, $af, $a5, $ae, $f0, $03, $4c, $16, $cf, $a5, $32, $c9, $20, $90 ; $CA82
.byte $3e, $c9, $90, $b0, $40, $a2, $00, $a5, $33, $c9, $10, $90, $44, $a2, $08, $c9 ; $CA92
.byte $f0, $b0, $44, $4c, $c3, $cb, $c5, $af, $f0, $de, $85, $af, $a2, $35, $4a, $b0 ; $CAA2
.byte $0c, $a2, $db, $4a, $b0, $07, $a2, $79, $4a, $b0, $02, $a2, $1f, $a5, $2f, $4a ; $CAB2
.byte $8a, $90, $05, $29, $0f, $4c, $56, $cb, $4a, $4a, $4a, $4a, $4c, $56, $cb, $e6 ; $CAC2
.byte $32, $a0, $00, $f0, $04, $c6, $32, $a0, $02, $a5, $48, $29, $08, $aa, $4c, $ed ; $CAD2
.byte $ca, $e6, $33, $a0, $04, $d0, $04, $c6, $33, $a0, $02, $86, $0c, $84, $0f, $a5 ; $CAE2
.byte $48, $29, $07, $49, $07, $05, $0c, $85 ; $CAF2

_data_cafa:
.byte $0c, $20, $88, $c5, $29, $03, $c9, $03, $d0, $02, $a9, $02, $18, $65, $0c, $85 ; $CAFA
.byte $0e, $a4, $0f, $c9, $00, $d0, $0a, $c0, $01, $f0, $36, $c0, $02, $f0, $2c, $d0 ; $CB0A
.byte $35, $c9, $04, $d0, $0a, $c0, $00, $f0, $2d, $c0, $02, $f0, $24, $d0, $1c, $c9 ; $CB1A
.byte $08, $d0, $0a, $c0, $00, $f0, $14, $c0, $01, $f0, $1b, $d0, $14, $c9, $0c, $d0 ; $CB2A
.byte $17, $c0, $00, $f0, $0c, $c0, $01, $f0, $02, $d0, $0b, $20, $88, $c5, $0a, $b0 ; $CB3A
.byte $05, $c6, $0e, $4c, $52, $cb, $e6, $0e, $a5, $0e, $29, $0f, $4c, $77, $cb, $a5 ; $CB4A
.byte $46, $d0, $66, $a4, $47, $b1, $44, $c8, $c9, $ff, $d0, $0a, $b1, $44, $c8, $85 ; $CB5A
.byte $31, $b1, $44, $85, $42, $60, $85, $46, $b1, $44, $c8, $84, $47, $85, $48, $aa ; $CB6A
.byte $bd, $4b, $e6, $85, $49, $85, $4a, $a9, $00, $85, $34, $a5, $48, $c9, $11, $90 ; $CB7A
.byte $17, $aa, $a9, $00, $e0, $15, $f0, $2a, $e0, $14, $f0, $1a, $e0, $13, $f0, $0e ; $CB8A
.byte $e6, $34, $e0, $12, $f0, $10, $d0, $1a, $c9, $08, $90, $02, $e6, $34, $a2, $0c ; $CB9A
.byte $a0, $e7, $29, $07, $f0, $10, $a2, $05, $a0, $e7, $c9, $03, $90, $08, $c9, $06 ; $CBAA
.byte $b0, $04, $a2, $1d, $a0, $e7, $20, $0b, $cf, $20, $1b, $d8, $48, $a5, $32, $c9 ; $CBBA
.byte $f0, $90, $04, $68, $4c, $2a, $cf, $a5, $46, $f0, $02, $c6, $46, $a4, $49, $b9 ; $CBCA
.byte $61, $e6, $c8, $c9, $aa, $d0, $05, $a4, $4a, $4c, $d9, $cb, $18, $65, $32, $a6 ; $CBDA
.byte $4b, $d0, $0c, $a6, $ae, $d0, $08, $c9, $1e, $90, $06, $c9, $92, $b0, $02, $85 ; $CBEA
.byte $32, $b9, $61, $e6, $c8, $84, $49, $18, $65, $33, $a6, $4b, $d0, $0c, $a6, $ae ; $CBFA
.byte $d0, $08, $c9, $0e, $90, $06, $c9, $f2, $b0, $02, $85, $33, $68, $38, $e9, $01 ; $CC0A
.byte $d0, $aa, $4c, $4d, $ce, $a6, $3b, $a9, $01, $9d, $ef, $03, $a9, $01, $85, $ad ; $CC1A
.byte $85, $5e, $a9, $12, $85, $4d, $20, $68, $cf, $a2, $13, $a0, $e7, $20, $0b, $cf ; $CC2A
.byte $e6, $31, $60, $a5, $4d, $f0, $0b, $c6, $4d, $29, $0f, $c9, $0a, $d0, $03, $20 ; $CC3A
.byte $2c, $d5, $4c, $4d, $ce    ; $CC4A

_data_cc4f:
.byte $20, $f9, $cf, $20, $f2, $d4, $a5, $33, $a2, $48, $c9, $48, $90, $07, $a2, $a0 ; $CC4F
.byte $c9, $a0, $b0, $01, $aa, $8e, $a3, $03, $a9, $01, $85, $4b, $a2, $10, $86, $48 ; $CC5F
.byte $bd, $4b, $e6, $85, $49, $85, $4a, $a2, $18, $a0, $e7, $d0, $bb, $a5, $32, $c9 ; $CC6F
.byte $b0, $b0, $03, $4c, $c3, $cb, $20, $34, $d5, $e6, $31, $60, $a9, $00, $85, $31 ; $CC7F
.byte $a6, $36, $4c, $42, $d0    ; $CC8F

_func_cc94:
  lda a:_var_03a0                ; $CC94  AD A0 03
  beq _label_cca8                ; $CC97  F0 0F
  lda #$02                       ; $CC99  A9 02
  sta _var_00a1                  ; $CC9B  85 A1
  ldy #$A0                       ; $CC9D  A0 A0
  jsr _func_c5f7                 ; $CC9F  20 F7 C5
  jsr _func_cca9                 ; $CCA2  20 A9 CC
  jsr _func_c607                 ; $CCA5  20 07 C6

_label_cca8:
  rts                            ; $CCA8  60

_func_cca9:
  lda _var_0031                  ; $CCA9  A5 31
  jsr _jump_engine_c35e          ; $CCAB  20 5E C3
  cpx #$C5                       ; $CCAE  E0 C5
.byte $d4, $cc                   ; $CCB0  D4 CC  disambiguous instruction: nop $CC,X
  asl _var_00cd_indexed,X        ; $CCB2  16 CD
  ora a:_var_3ccd_indexed,X      ; $CCB4  1D CD 3C
  cmp a:_data_ce4d               ; $CCB7  CD 4D CE
  jmp a:$4DCD                    ; $CCBA  4C CD 4D

.byte $ce, $52, $cd, $5c, $cd, $6c, $cd, $4d, $ce, $80, $cd, $4d, $ce, $9a, $cd, $18 ; $CCBD
.byte $ce, $2e, $ce, $4d, $ce, $40, $ce, $a2, $1f, $bd, $6e, $e7, $95, $30, $ca, $10 ; $CCCD
.byte $f8, $a9, $03, $85, $ba, $a9, $01, $85, $be, $85, $ad, $a9, $02, $85, $23, $a5 ; $CCDD
.byte $25, $c9, $07, $d0, $05, $a9, $10, $85, $31, $60, $a5, $c1, $a0, $18, $a2, $00 ; $CCED
.byte $c9, $01, $f0, $04, $a0, $50, $a2, $18, $84, $33, $86, $44, $a9, $01, $85, $9d ; $CCFD
.byte $20, $d9, $c5, $20, $6c, $f5, $e6, $31, $60, $a2, $8e, $a0, $e7, $4c, $44, $cd ; $CD0D
.byte $a5, $35, $c9, $0c, $d0, $0b, $e6, $44, $a5, $44, $c9, $20, $90, $03, $e6, $31 ; $CD1D
.byte $60, $20, $4d, $ce, $a5, $33, $c5, $45, $d0, $f6, $a9, $06, $85, $31, $60, $a9 ; $CD2D
.byte $00, $85, $44, $a2, $98, $a0, $e7, $20, $0b, $cf, $e6, $31, $4c, $4d, $ce, $a2 ; $CD3D
.byte $a7, $a0, $e7, $d0, $f2, $a9, $04, $85, $9e, $a2, $ac, $a0, $e7, $d0, $e8, $c6 ; $CD4D
.byte $9e, $a5, $9e, $d0, $07, $a9, $10, $85, $9e, $20, $28, $d5, $4c, $4d, $ce, $a5 ; $CD5D
.byte $2b, $d0, $bd, $20, $fa, $d4, $a9, $80, $85, $33, $20, $39, $cf, $a2, $46, $a0 ; $CD6D
.byte $e8, $d0, $c4, $a5, $2b, $d0, $a9, $20, $11, $d5, $20, $39, $cf, $a2, $94, $a0 ; $CD7D
.byte $e8, $a5, $bd, $c9, $01, $f0, $b0, $a2, $a3, $a0, $e8, $d0, $aa, $a9, $30, $85 ; $CD8D
.byte $a6, $a9, $01, $85, $b9, $a9, $03, $85, $ba, $a9, $01, $85, $be, $a9, $00, $85 ; $CD9D
.byte $bd, $a9, $02, $a0, $01, $a6, $1f, $d0, $04, $a9, $01, $a0, $00, $85, $bc, $8c ; $CDAD
.byte $50, $03, $8c, $51, $03, $a9, $01, $8d, $00, $03, $8d, $01, $03, $20, $88, $c5 ; $CDBD
.byte $85, $0c, $a9, $03, $a4, $c1, $c0, $01, $f0, $02, $a9, $07, $25, $0c, $85, $98 ; $CDCD
.byte $a0, $00, $84, $99, $aa, $bd, $66, $e7, $85, $0c, $29, $f0, $4a, $a0, $00, $20 ; $CDDD
.byte $44, $cf, $a5, $0c, $29, $0f, $0a, $0a, $0a, $20, $44, $cf, $a9, $3f, $8d, $00 ; $CDED
.byte $04, $a9, $10, $8d, $01, $04, $8d, $02, $04, $a9, $00, $8d, $13, $04, $a9, $01 ; $CDFD
.byte $85, $27, $a9, $12, $85, $31, $a9, $00, $85, $42, $60, $a5, $bb, $c9, $0a, $d0 ; $CE0D
.byte $0b, $a9, $00, $85, $a9, $a9, $04, $85, $25, $4c, $3b, $c2, $a9, $0e, $85, $31 ; $CE1D
.byte $60, $a9, $80, $85, $33, $a9, $01, $85, $38, $20, $39, $cf, $a2, $b2, $a0, $e8 ; $CE2D
.byte $4c, $44, $cd, $a5, $42, $d0, $09, $a9, $00, $85, $31, $a6, $36, $4c, $42, $d0 ; $CE3D

_data_ce4d:
.byte $a5, $42, $f0, $05, $c6, $42, $4c, $1b, $d0, $a4, $43, $b1, $40, $c9, $fa, $90 ; $CE4D
.byte $14, $e6, $43, $38, $e9, $fa, $20, $5e, $c3, $e0, $c5, $e0, $c5, $07, $cf, $00 ; $CE5D
.byte $cf, $f9, $ce, $ed, $ce, $a4, $43, $a6, $a1, $e0, $02, $d0, $6c, $a6, $31, $e0 ; $CE6D
.byte $09, $f0, $2d, $e0, $0b, $f0, $08, $e0, $0d, $f0, $04, $e0, $11, $d0, $48, $a6 ; $CE7D
.byte $46, $f0, $0c, $c6, $46, $a5, $47, $18, $65, $32, $85, $32, $4c, $1b, $d0, $85 ; $CE8D
.byte $46, $c8, $b1, $40, $10, $05, $29, $7f, $20, $2b, $d1, $85, $47, $4c, $c9, $ce ; $CE9D
.byte $aa, $10, $05, $29, $7f, $20, $2b, $d1, $18, $65, $32, $85, $32, $c8, $b1, $40 ; $CEAD
.byte $a6, $34, $f0, $03, $20, $2b, $d1, $18, $65, $33, $85, $33, $c8, $b1, $40, $85 ; $CEBD
.byte $35, $c8, $84, $43, $4c, $1b, $d0, $e0, $03, $d0, $0e, $a9, $02, $a6, $34, $f0 ; $CECD
.byte $03, $20, $2b, $d1, $18, $65, $33, $85, $33, $b1, $40, $85, $42, $4c, $c9, $ce ; $CEDD
.byte $a4, $43, $b1, $40, $85, $31, $c8, $b1, $40, $85, $42, $60, $a9, $00, $85, $43 ; $CEED
.byte $4c, $56, $ce, $a9, $01, $85, $38, $4c, $56, $ce, $a9, $1e, $d0, $f0, $86, $40 ; $CEFD
.byte $84, $41, $a9, $00, $85, $43, $85, $42, $60, $a5, $32, $c9, $08, $90, $0e, $c9 ; $CF0D
.byte $90, $b0, $13, $a5, $33, $c9, $0c, $90, $04, $c9, $f4, $90, $0c, $a9, $08, $85 ; $CF1D
.byte $31, $a9, $00, $85, $42, $60, $4c, $d7, $ca, $4c, $a5, $ca, $a9, $00, $85, $46 ; $CF2D
.byte $85, $47, $a9, $ac, $85, $32, $60, $aa, $a9, $08, $85, $0d, $bd, $24, $e7, $99 ; $CF3D
.byte $03, $04, $e8, $c8, $c6, $0d, $d0, $f4, $60, $a5, $c1, $a0, $02, $c9, $06, $90 ; $CF4D
.byte $21, $a0, $03, $c9, $11, $90, $1b, $a0, $05, $d0, $17, $a6, $c1, $a9, $00, $e0 ; $CF5D
.byte $06, $90, $08, $a9, $03, $e0, $11, $90, $02, $a9, $06, $18, $65, $3f, $aa, $bc ; $CF6D
.byte $f1, $eb, $84, $39, $b9, $fa, $eb, $85, $06, $a9, $00, $85, $04, $85, $05, $85 ; $CF7D
.byte $07, $a9, $0f, $20, $37, $c4, $4c, $55, $c6, $a5, $bd, $d0, $1f, $a9, $06, $20 ; $CF8D
.byte $64, $d4, $a9, $30, $85, $2b, $a9, $06, $85, $23, $a9, $01, $85, $27, $a9, $36 ; $CF9D
.byte $8d, $03, $04, $8d, $07, $04, $8d, $0b, $04, $8d, $0f, $04, $60 ; $CFAD

_func_cfba:
  ldx #$00                       ; $CFBA  A2 00
  ldy #$00                       ; $CFBC  A0 00
  jsr _func_cfc5                 ; $CFBE  20 C5 CF
  ldx #$04                       ; $CFC1  A2 04
  ldy #$08                       ; $CFC3  A0 08

_func_cfc5:
  lda _var_0080_indexed,X        ; $CFC5  B5 80
  beq _label_cff8                ; $CFC7  F0 2F
  dec _var_0080_indexed,X        ; $CFC9  D6 80
  bne _label_cfd3                ; $CFCB  D0 06
  lda #$F4                       ; $CFCD  A9 F4
  sta _var_0081_indexed,X        ; $CFCF  95 81
  sta _var_0082_indexed,X        ; $CFD1  95 82

_label_cfd3:
  lda _var_0081_indexed,X        ; $CFD3  B5 81
  sta a:_var_02f0_indexed,Y      ; $CFD5  99 F0 02
  sta a:_var_02f4_indexed,Y      ; $CFD8  99 F4 02
  lda _var_0083_indexed,X        ; $CFDB  B5 83
  sta a:_var_02f1_indexed,Y      ; $CFDD  99 F1 02
  lda #$FF                       ; $CFE0  A9 FF
  sta a:_var_02f5_indexed,Y      ; $CFE2  99 F5 02
  lda #$00                       ; $CFE5  A9 00
  sta a:_var_02f2_indexed,Y      ; $CFE7  99 F2 02
  sta a:_var_02f6_indexed,Y      ; $CFEA  99 F6 02
  lda _var_0082_indexed,X        ; $CFED  B5 82
  sta a:_var_02f3_indexed,Y      ; $CFEF  99 F3 02
  clc                            ; $CFF2  18
  adc #$08                       ; $CFF3  69 08
  sta a:_var_02f7_indexed,Y      ; $CFF5  99 F7 02

_label_cff8:
  rts                            ; $CFF8  60

.byte $a2, $00, $b5, $80, $f0, $02, $a2, $04, $a5, $32, $38, $e9, $04, $95, $81, $a5 ; $CFF9
.byte $33, $38, $e9, $08, $95, $82, $a5, $39, $18, $69, $f7, $95, $83, $a9, $30, $95 ; $D009
.byte $80, $60, $a5, $36, $85, $b4, $a5, $35, $0a, $a8, $a9, $c5, $85, $12, $a9, $da ; $D019
.byte $85, $13, $b1, $12, $85, $10, $c8, $b1, $12, $85, $11, $a0, $00, $84, $1a, $a4 ; $D029
.byte $1a, $b1, $10, $c9, $00, $d0, $10, $a6, $b4, $a9, $f4, $e4, $37, $f0, $07, $9d ; $D039
.byte $00, $02, $e8, $4c, $44, $d0, $60, $85, $13, $c8, $b1, $10, $c8, $85, $12, $b1 ; $D049
.byte $10, $c8, $18, $65, $32, $85, $b1, $b1, $10, $c8, $a6, $34, $f0, $06, $20, $2b ; $D059
.byte $d1, $38, $e9, $08, $18, $65, $33, $85, $b2, $84, $1a, $a0, $00, $b1, $12, $a2 ; $D069
.byte $00, $c9, $00, $f0, $0e, $a2, $10, $c9, $01, $f0, $08, $a2, $38, $c9, $02, $f0 ; $D079
.byte $02, $a2, $44, $86, $1b, $c8, $b1, $12, $c9, $ff, $f0, $a3, $c9, $fe, $d0, $07 ; $D089
.byte $e6, $1b, $e6, $1b, $4c, $8e, $d0, $c9, $fd, $d0, $15, $c8, $b1, $12, $18, $65 ; $D099
.byte $3c, $85, $b3, $a5, $38, $f0, $de, $a5, $b3, $09, $20, $85, $b3, $4c, $8e, $d0 ; $D0A9
.byte $a6, $1b, $bd, $c0, $dc, $e6, $1b, $18, $65, $b1, $20, $0e, $d1, $a6, $b4, $9d ; $D0B9
.byte $00, $02, $e6, $b4, $b1, $12, $c8, $a6, $b4, $9d, $00, $02, $e6, $b4, $a5, $b3 ; $D0C9
.byte $a6, $34, $f0, $0c, $29, $bf, $85, $0c, $a5, $b3, $29, $40, $49, $40, $05, $0c ; $D0D9
.byte $a6, $b4, $9d, $00, $02, $e6, $b4, $a6, $1b, $bd, $c0, $dc, $e6, $1b, $a6, $34 ; $D0E9
.byte $f0, $03, $20, $2b, $d1, $18, $65, $b2, $20, $14, $d1, $a6, $b4, $9d, $00, $02 ; $D0F9
.byte $e6, $b4, $4c, $8f, $d0, $48, $a5, $32, $4c, $17, $d1, $48, $a5, $33, $85, $0f ; $D109
.byte $68, $48, $38, $e5, $0f, $b0, $03, $20, $2b, $d1, $c9, $30, $68, $90, $02, $a9 ; $D119
.byte $ff, $60, $49, $ff, $18, $69, $01, $60 ; $D129

_func_d131:
  lda JOYPAD2                    ; $D131  AD 17 40
  and #$10                       ; $D134  29 10
  cmp _var_00b7                  ; $D136  C5 B7
  beq _label_d141                ; $D138  F0 07
  sta _var_00b7                  ; $D13A  85 B7

_label_d13c:
  lda #$00                       ; $D13C  A9 00
  sta _var_00b8                  ; $D13E  85 B8

_label_d140:
  rts                            ; $D140  60

_label_d141:
  inc _var_00b8                  ; $D141  E6 B8
  ldy _var_00b8                  ; $D143  A4 B8
  cpy #$01                       ; $D145  C0 01
  bne _label_d140                ; $D147  D0 F7
  and #$10                       ; $D149  29 10
  beq _label_d153                ; $D14B  F0 06
  lda #$01                       ; $D14D  A9 01
  sta _var_00b6                  ; $D14F  85 B6
  bne _label_d13c                ; $D151  D0 E9

_label_d153:
  lda _var_00b6                  ; $D153  A5 B6
  beq _label_d13c                ; $D155  F0 E5
  ldy #$00                       ; $D157  A0 00
  sty _var_00b6                  ; $D159  84 B6
  iny                            ; $D15B  C8
  sty _var_00b5                  ; $D15C  84 B5
  bne _label_d13c                ; $D15E  D0 DC

_func_d160:
  lda _var_00b9                  ; $D160  A5 B9
  bne _label_d169                ; $D162  D0 05

_label_d164:
  lda #$00                       ; $D164  A9 00
  sta _var_00b5                  ; $D166  85 B5

_label_d168:
  rts                            ; $D168  60

_label_d169:
  lda _var_00b5                  ; $D169  A5 B5
  beq _label_d168                ; $D16B  F0 FB
  lda _var_00ba                  ; $D16D  A5 BA
  beq _label_d164                ; $D16F  F0 F3
  dec _var_00ba                  ; $D171  C6 BA
  lda #$01                       ; $D173  A9 01
  sta _var_00be                  ; $D175  85 BE
  lda #$00                       ; $D177  A9 00
  sta _var_00b5                  ; $D179  85 B5
  jsr _func_d4e6                 ; $D17B  20 E6 D4
  lda #$04                       ; $D17E  A9 04
  sta _var_0023                  ; $D180  85 23
  jsr _func_c23b                 ; $D182  20 3B C2
  jsr _func_c5e1                 ; $D185  20 E1 C5
  lda _var_0024                  ; $D188  A5 24
  beq _label_d19f                ; $D18A  F0 13
  jsr _func_d4e2                 ; $D18C  20 E2 D4
  jsr _func_f56c                 ; $D18F  20 6C F5
  jsr _func_d4e6                 ; $D192  20 E6 D4
  lda #$02                       ; $D195  A9 02
  sta _var_00b0                  ; $D197  85 B0
  lda #$FF                       ; $D199  A9 FF
  sta _var_000a                  ; $D19B  85 0A
  bne _label_d1ca                ; $D19D  D0 2B

_label_d19f:
  lda #$05                       ; $D19F  A9 05
  sta _var_0023                  ; $D1A1  85 23
  lda #$00                       ; $D1A3  A9 00
  sta _var_00b0                  ; $D1A5  85 B0
  ldy #$00                       ; $D1A7  A0 00
  lda a:_var_0300_indexed        ; $D1A9  AD 00 03
  beq _label_d1b5                ; $D1AC  F0 07
  lda a:_var_0301_indexed        ; $D1AE  AD 01 03
  cmp #$03                       ; $D1B1  C9 03
  beq _label_d1c7                ; $D1B3  F0 12

_label_d1b5:
  lda #$01                       ; $D1B5  A9 01
  sta _var_00b0                  ; $D1B7  85 B0
  ldy #$50                       ; $D1B9  A0 50
  lda a:_var_0350                ; $D1BB  AD 50 03
  beq _label_d1dd                ; $D1BE  F0 1D
  lda a:_var_0351                ; $D1C0  AD 51 03
  cmp #$03                       ; $D1C3  C9 03
  bne _label_d1dd                ; $D1C5  D0 16

_label_d1c7:
  jsr _func_d292                 ; $D1C7  20 92 D2

_label_d1ca:
  jsr _func_c61e                 ; $D1CA  20 1E C6

_label_d1cd:
  lda _var_0020                  ; $D1CD  A5 20
  bne _label_d1f4                ; $D1CF  D0 23
  lda JOYPAD2                    ; $D1D1  AD 17 40
  and #$08                       ; $D1D4  29 08
  bne _label_d1cd                ; $D1D6  D0 F5
  lda _var_00b0                  ; $D1D8  A5 B0
  jmp _label_d28a                ; $D1DA  4C 8A D2

_label_d1dd:
  lda _var_001f                  ; $D1DD  A5 1F
  cmp #$02                       ; $D1DF  C9 02
  bne _label_d1e6                ; $D1E1  D0 03
  jmp _label_d266                ; $D1E3  4C 66 D2

_label_d1e6:
  ldy #$02                       ; $D1E6  A0 02
  sty _var_0023                  ; $D1E8  84 23
  jsr _func_c5d9                 ; $D1EA  20 D9 C5
  ldy #$01                       ; $D1ED  A0 01
  sty _var_0027                  ; $D1EF  84 27
  jmp _label_d26a                ; $D1F1  4C 6A D2

_label_d1f4:
  jsr _func_c61e                 ; $D1F4  20 1E C6
  lda _var_0009                  ; $D1F7  A5 09
  and #$E7                       ; $D1F9  29 E7
  sta _var_0009                  ; $D1FB  85 09
  lda #$08                       ; $D1FD  A9 08
  ldy _var_00b0                  ; $D1FF  A4 B0
  cpy #$02                       ; $D201  C0 02
  beq _label_d207                ; $D203  F0 02
  lda #$10                       ; $D205  A9 10

_label_d207:
  ora _var_0009                  ; $D207  05 09
  sta _var_0009                  ; $D209  85 09
  sta PPU_MASK                   ; $D20B  8D 01 20
  jsr _func_c23b                 ; $D20E  20 3B C2
  lda a:_var_0350                ; $D211  AD 50 03
  beq _label_d222                ; $D214  F0 0C
  lda a:_var_0351                ; $D216  AD 51 03
  cmp #$03                       ; $D219  C9 03
  bne _label_d222                ; $D21B  D0 05
  ldy #$50                       ; $D21D  A0 50
  jsr _func_d292                 ; $D21F  20 92 D2

_label_d222:
  lda _var_0020                  ; $D222  A5 20
  bne _label_d270                ; $D224  D0 4A
  lda JOYPAD2                    ; $D226  AD 17 40
  and #$08                       ; $D229  29 08
  bne _label_d222                ; $D22B  D0 F5
  lda _var_00b0                  ; $D22D  A5 B0
  cmp #$02                       ; $D22F  C9 02
  bne _label_d246                ; $D231  D0 13
  lda #$01                       ; $D233  A9 01

_label_d235:
  sta a:_var_05ff                ; $D235  8D FF 05
  lda #$01                       ; $D238  A9 01
  sta _var_0023                  ; $D23A  85 23
  lda #$00                       ; $D23C  A9 00
  sta _var_000a                  ; $D23E  85 0A
  jsr _func_c5d9                 ; $D240  20 D9 C5
  jmp _func_c5ee                 ; $D243  4C EE C5

_label_d246:
  inc _var_00aa                  ; $D246  E6 AA
  inc _var_00bd                  ; $D248  E6 BD
  ldx #$04                       ; $D24A  A2 04
  lda _var_00b0                  ; $D24C  A5 B0
  bne _label_d256                ; $D24E  D0 06
  stx a:_var_0301_indexed        ; $D250  8E 01 03
  jmp _label_d259                ; $D253  4C 59 D2

_label_d256:
  stx a:_var_0351                ; $D256  8E 51 03

_label_d259:
  lda _var_001f                  ; $D259  A5 1F
  cmp #$02                       ; $D25B  C9 02
.byte $f0                        ; $D25D  F0  branch into instruction detected: beq $D266

_label_d25e:
.byte $07                        ; $D25E  07
  ldy #$01                       ; $D25F  A0 01
  sty _var_0027                  ; $D261  84 27
  iny                            ; $D263  C8
  bne _label_d268                ; $D264  D0 02

_label_d266:
  ldy #$03                       ; $D266  A0 03

_label_d268:
  sty _var_0023                  ; $D268  84 23

_label_d26a:
  jsr _func_c23b                 ; $D26A  20 3B C2
  jmp _func_c5ee                 ; $D26D  4C EE C5

_label_d270:
  lda _var_00b0                  ; $D270  A5 B0
  bne _label_d28a                ; $D272  D0 16
  lda a:_var_0350                ; $D274  AD 50 03
  beq _label_d259                ; $D277  F0 E0
  lda a:_var_0351                ; $D279  AD 51 03
  cmp #$03                       ; $D27C  C9 03
  bne _label_d259                ; $D27E  D0 D9
  lda #$01                       ; $D280  A9 01
  sta _var_00b0                  ; $D282  85 B0
  jsr _func_c61e                 ; $D284  20 1E C6
  jmp _label_d222                ; $D287  4C 22 D2

_label_d28a:
  cmp #$02                       ; $D28A  C9 02
  bne _label_d259                ; $D28C  D0 CB
  lda #$02                       ; $D28E  A9 02
  bne _label_d235                ; $D290  D0 A3

_func_d292:
  lda a:_var_0302_indexed,Y      ; $D292  B9 02 03
  sta _var_00b1                  ; $D295  85 B1
  lda a:_var_0303_indexed,Y      ; $D297  B9 03 03
  sta _var_00b2                  ; $D29A  85 B2
  lda a:_var_030a_indexed,Y      ; $D29C  B9 0A 03
  sta _var_000c                  ; $D29F  85 0C
  jmp _label_c67c                ; $D2A1  4C 7C C6

_func_d2a4:
  ldy _var_00c2                  ; $D2A4  A4 C2

_label_d2a6:
  lda a:_data_ec02_indexed,Y     ; $D2A6  B9 02 EC
  cmp #$FF                       ; $D2A9  C9 FF
  bne _label_d2b1                ; $D2AB  D0 04
  ldy #$13                       ; $D2AD  A0 13
  bne _label_d2a6                ; $D2AF  D0 F5

_label_d2b1:
  iny                            ; $D2B1  C8
  sty _var_00c2                  ; $D2B2  84 C2
  sta _var_00ab                  ; $D2B4  85 AB
  lda #$00                       ; $D2B6  A9 00
  sta _var_00bb                  ; $D2B8  85 BB
  sta _var_00aa                  ; $D2BA  85 AA
  lda #$01                       ; $D2BC  A9 01
  sta a:_var_03a0                ; $D2BE  8D A0 03
  sta a:_var_03a1                ; $D2C1  8D A1 03
  lda #$FF                       ; $D2C4  A9 FF
  sta $9C                        ; $D2C6  85 9C
  rts                            ; $D2C8  60

_label_d2c9:
  lda _var_00a9_indexed          ; $D2C9  A5 A9
  jsr _jump_engine_c35e          ; $D2CB  20 5E C3
  dec _var_00d2_indexed,X        ; $D2CE  D6 D2
  cmp a:_var_3dd2_indexed,X      ; $D2D0  DD D2 3D
  dcp (_var_00c9_indexed),Y      ; $D2D3  D3 C9
  dcp (_var_00a9_indexed),Y      ; $D2D5  D3 A9
  bpl _label_d25e                ; $D2D7  10 85

.byte $2b, $e6, $a9, $60, $a5, $2b, $d0, $49, $a0, $00, $a2, $01, $bd, $f0, $03, $f0 ; $D2D9
.byte $0d, $bd, $ef, $03, $d0, $08, $fe, $ef, $03, $de, $f0, $03, $a0, $01, $e8, $e0 ; $D2E9
.byte $0a, $d0, $e9, $88, $d0, $0a, $a9, $00, $85, $a9, $20, $19, $d5, $4c, $cc, $c6 ; $D2F9
.byte $a5, $aa, $c5, $ab, $90, $1c, $20, $1d, $d5, $a9, $00, $85, $be, $a9, $10, $85 ; $D309
.byte $2b, $e6, $a9, $a5, $c1, $29, $0f, $d0, $08, $20, $3b, $c2, $a9, $04, $4c, $64 ; $D319
.byte $d4, $60, $20, $3b, $c2, $a9, $08, $20, $64, $d4, $20, $44, $d5, $a2, $06, $a9 ; $D329
.byte $0c, $4c, $2e, $c6, $a5, $2b, $d0, $e9, $a9, $10, $85, $2b, $e6, $be, $a5, $be ; $D339
.byte $c9, $0f, $d0, $60, $a5, $aa, $c9, $0a, $d0, $46, $20, $38, $d5, $a5, $c1, $a2 ; $D349
.byte $00, $c9, $11, $90, $0b, $e8, $c9, $16, $90, $06, $e8, $c9, $21, $90, $01, $e8 ; $D359
.byte $bd, $e9, $eb, $85, $05, $85, $0c, $bd, $ed, $eb, $85, $06, $4a, $4a, $4a, $4a ; $D369
.byte $85, $0d, $a9, $00, $85, $04, $85, $07, $a9, $0f, $20, $37, $c4, $20, $55, $c6 ; $D379
.byte $a9, $03, $85, $a9, $a9, $a0, $85, $2b, $20, $3b, $c2, $a9, $05, $4c, $64, $d4 ; $D389
.byte $a9, $00, $a2, $02, $a4, $1f, $c0, $02, $d0, $02, $a2, $09, $20, $2e, $c6, $a9 ; $D399
.byte $00, $4c, $64, $d4, $29, $01, $d0, $03, $4c, $cc, $c6, $a2, $09, $a9, $d6, $a4 ; $D3A9
.byte $1f, $c0, $02, $d0, $02, $a9, $d4, $9d, $01, $05, $ca, $10, $fa, $4c, $e9, $c6 ; $D3B9
.byte $a5, $2b, $d0, $04, $a9, $04, $d0, $ca, $60 ; $D3C9

_func_d3d2:
  lda _var_0027                  ; $D3D2  A5 27
  bne _label_d427                ; $D3D4  D0 51
  inc _var_009b                  ; $D3D6  E6 9B
  ldy #$00                       ; $D3D8  A0 00
  jsr _func_d3df                 ; $D3DA  20 DF D3
  ldy #$50                       ; $D3DD  A0 50

_func_d3df:
  lda a:_var_0300_indexed,Y      ; $D3DF  B9 00 03
  beq _label_d427                ; $D3E2  F0 43
  lda a:_var_0301_indexed,Y      ; $D3E4  B9 01 03
  cmp #$03                       ; $D3E7  C9 03
  beq _label_d3fb                ; $D3E9  F0 10
  cmp #$08                       ; $D3EB  C9 08
  bne _label_d427                ; $D3ED  D0 38
  ldx a:_var_030b_indexed,Y      ; $D3EF  BE 0B 03
  lda a:_var_03ef_indexed,X      ; $D3F2  BD EF 03
  beq _label_d409                ; $D3F5  F0 12
  ldx #$D3                       ; $D3F7  A2 D3
  bne _label_d40b                ; $D3F9  D0 10

_label_d3fb:
  lda _var_009b                  ; $D3FB  A5 9B
  and #$0F                       ; $D3FD  29 0F
  bne _label_d427                ; $D3FF  D0 26
  ldx #$B7                       ; $D401  A2 B7
  lda _var_009b                  ; $D403  A5 9B
  and #$10                       ; $D405  29 10
  beq _label_d413                ; $D407  F0 0A

_label_d409:
  ldx #$D4                       ; $D409  A2 D4

_label_d40b:
  lda _var_001f                  ; $D40B  A5 1F
  cmp #$02                       ; $D40D  C9 02
  beq _label_d413                ; $D40F  F0 02
  inx                            ; $D411  E8
  inx                            ; $D412  E8

_label_d413:
  stx a:_var_0501_indexed        ; $D413  8E 01 05
  ldx #$11                       ; $D416  A2 11
  stx a:_var_0500_indexed        ; $D418  8E 00 05
  lda a:_var_030b_indexed,Y      ; $D41B  B9 0B 03
  clc                            ; $D41E  18
  adc #$4B                       ; $D41F  69 4B
  tax                            ; $D421  AA
  ldy #$23                       ; $D422  A0 23
  jmp _func_c71d                 ; $D424  4C 1D C7

_label_d427:
  rts                            ; $D427  60

_func_d428:
  lda _var_00b9                  ; $D428  A5 B9
  beq _label_d427                ; $D42A  F0 FB
  lda _var_00ba                  ; $D42C  A5 BA
  bne _label_d427                ; $D42E  D0 F7
  lda _var_009a                  ; $D430  A5 9A
  and #$07                       ; $D432  29 07
  bne _label_d461                ; $D434  D0 2B
  lda _var_0027                  ; $D436  A5 27
  bne _label_d427                ; $D438  D0 ED
  lda _var_009a                  ; $D43A  A5 9A
  and #$08                       ; $D43C  29 08
  beq _func_d446                 ; $D43E  F0 06
  lda #$B7                       ; $D440  A9 B7
  tax                            ; $D442  AA
  tay                            ; $D443  A8
  bne _label_d44c                ; $D444  D0 06

_func_d446:
  lda #$DA                       ; $D446  A9 DA
  ldx #$DB                       ; $D448  A2 DB
  ldy #$DC                       ; $D44A  A0 DC

_label_d44c:
  sta a:_var_0501_indexed        ; $D44C  8D 01 05
  stx a:_var_0502                ; $D44F  8E 02 05
  sty a:$0503                    ; $D452  8C 03 05
  lda #$13                       ; $D455  A9 13
  sta a:_var_0500_indexed        ; $D457  8D 00 05
  ldx #$63                       ; $D45A  A2 63
  ldy #$23                       ; $D45C  A0 23
  jsr _func_c71d                 ; $D45E  20 1D C7

_label_d461:
  inc _var_009a                  ; $D461  E6 9A
  rts                            ; $D463  60

_func_d464:
  pha                            ; $D464  48
  jsr _func_c5d9                 ; $D465  20 D9 C5
  jsr _func_f56c                 ; $D468  20 6C F5
  pla                            ; $D46B  68

_label_d46c:
  sta _var_001b                  ; $D46C  85 1B
  beq _label_d4bc                ; $D46E  F0 4C
  asl a                          ; $D470  0A
  tax                            ; $D471  AA
  lda a:_data_ec38_indexed,X     ; $D472  BD 38 EC
  sta _var_0014_indexed          ; $D475  85 14
  lda a:_data_ec39_indexed,X     ; $D477  BD 39 EC
  sta _var_0015                  ; $D47A  85 15
  ldy #$01                       ; $D47C  A0 01
  lda (_var_0014_indexed),Y      ; $D47E  B1 14
  sta _var_000f                  ; $D480  85 0F
  ldx #$00                       ; $D482  A2 00
  iny                            ; $D484  C8

_label_d485:
  lda (_var_0014_indexed),Y      ; $D485  B1 14
  sta a:_var_0500_indexed,X      ; $D487  9D 00 05
  iny                            ; $D48A  C8
  inx                            ; $D48B  E8
  dec _var_000f                  ; $D48C  C6 0F
  bne _label_d485                ; $D48E  D0 F5
  lda _var_001b                  ; $D490  A5 1B
  cmp #$01                       ; $D492  C9 01
  bne _label_d4ab                ; $D494  D0 15
  lda _var_00c1                  ; $D496  A5 C1
  lsr a                          ; $D498  4A
  lsr a                          ; $D499  4A
  lsr a                          ; $D49A  4A
  lsr a                          ; $D49B  4A
  beq _label_d4a1                ; $D49C  F0 03
  sta a:$0518                    ; $D49E  8D 18 05

_label_d4a1:
  lda _var_00c1                  ; $D4A1  A5 C1
  and #$0F                       ; $D4A3  29 0F
  sta a:$0519                    ; $D4A5  8D 19 05
  jmp _label_d4cf                ; $D4A8  4C CF D4

_label_d4ab:
  cmp #$05                       ; $D4AB  C9 05
  bne _label_d4cf                ; $D4AD  D0 20
  lda _var_000c                  ; $D4AF  A5 0C
  sta a:$0521                    ; $D4B1  8D 21 05
  lda _var_000d                  ; $D4B4  A5 0D
  sta a:$0522                    ; $D4B6  8D 22 05
  jmp _label_d4cf                ; $D4B9  4C CF D4

_label_d4bc:
  ldx #$44                       ; $D4BC  A2 44
  lda #$24                       ; $D4BE  A9 24

_label_d4c0:
  sta a:_var_0501_indexed,X      ; $D4C0  9D 01 05
  dex                            ; $D4C3  CA
  bpl _label_d4c0                ; $D4C4  10 FA
  lda #$6B                       ; $D4C6  A9 6B
  sta a:_var_0500_indexed        ; $D4C8  8D 00 05
  ldx #$CB                       ; $D4CB  A2 CB
  bne _label_d4d4                ; $D4CD  D0 05

_label_d4cf:
  ldy #$00                       ; $D4CF  A0 00
  lda (_var_0014_indexed),Y      ; $D4D1  B1 14
  tax                            ; $D4D3  AA

_label_d4d4:
  ldy #$20                       ; $D4D4  A0 20
  jmp _func_c71d                 ; $D4D6  4C 1D C7

_func_d4d9:
  jsr _func_c23b                 ; $D4D9  20 3B C2
  jsr _func_c64b                 ; $D4DC  20 4B C6
  jmp _label_c637                ; $D4DF  4C 37 C6

_func_d4e2:
  lda #$01                       ; $D4E2  A9 01
  bne _label_d500                ; $D4E4  D0 1A

_func_d4e6:
  lda #$02                       ; $D4E6  A9 02
  bne _label_d500                ; $D4E8  D0 16
  lda #$04                       ; $D4EA  A9 04
  bne _label_d500                ; $D4EC  D0 12
  lda #$08                       ; $D4EE  A9 08
  bne _label_d500                ; $D4F0  D0 0E
  lda #$10                       ; $D4F2  A9 10
  bne _label_d500                ; $D4F4  D0 0A
  lda #$20                       ; $D4F6  A9 20
  bne _label_d500                ; $D4F8  D0 06

_func_d4fa:
  lda #$40                       ; $D4FA  A9 40
  bne _label_d500                ; $D4FC  D0 02

_func_d4fe:
  lda #$80                       ; $D4FE  A9 80

_label_d500:
  ora _var_00f0                  ; $D500  05 F0
  sta _var_00f0                  ; $D502  85 F0
  rts                            ; $D504  60

_label_d505:
  lda #$01                       ; $D505  A9 01
  bne _label_d523                ; $D507  D0 1A

_func_d509:
  lda #$02                       ; $D509  A9 02
  bne _label_d523                ; $D50B  D0 16

_func_d50d:
  lda #$04                       ; $D50D  A9 04
  bne _label_d523                ; $D50F  D0 12
  lda #$08                       ; $D511  A9 08
  bne _label_d523                ; $D513  D0 0E

_label_d515:
  lda #$10                       ; $D515  A9 10
  bne _label_d523                ; $D517  D0 0A
  lda #$20                       ; $D519  A9 20
  bne _label_d523                ; $D51B  D0 06
  lda #$40                       ; $D51D  A9 40
  bne _label_d523                ; $D51F  D0 02

_label_d521:
  lda #$80                       ; $D521  A9 80

_label_d523:
  ora _var_00f1                  ; $D523  05 F1
  sta _var_00f1                  ; $D525  85 F1
  rts                            ; $D527  60

.byte $a9, $01, $d0, $1a, $a9, $02, $d0, $16, $a9, $04, $d0, $12, $a9, $08, $d0, $0e ; $D528
.byte $a9, $10, $d0, $0a, $a9, $20, $d0, $06, $a9, $40, $d0, $02, $a9, $80, $05, $f2 ; $D538
.byte $85, $f2, $60              ; $D548

_label_d54b:
  jsr _func_c5d9                 ; $D54B  20 D9 C5
  ldx #$6C                       ; $D54E  A2 6C
  ldy #$E2                       ; $D550  A0 E2
  jsr _func_c617                 ; $D552  20 17 C6
  lda #$03                       ; $D555  A9 03
  sta _var_0023                  ; $D557  85 23
  lda #$00                       ; $D559  A9 00
  sta _var_009d                  ; $D55B  85 9D
  lda #$09                       ; $D55D  A9 09
  sta _var_0025                  ; $D55F  85 25
  jsr _func_c3c1                 ; $D561  20 C1 C3
  jsr _func_c5ee                 ; $D564  20 EE C5
  jmp _label_d505                ; $D567  4C 05 D5

_label_d56a:
  jsr _func_d4d9                 ; $D56A  20 D9 D4
  jsr _func_d2a4                 ; $D56D  20 A4 D2
  jsr _func_c793                 ; $D570  20 93 C7
  jsr _func_c7b3                 ; $D573  20 B3 C7
  jsr _func_c5d9                 ; $D576  20 D9 C5
  jsr _func_f56c                 ; $D579  20 6C F5
  lda #$01                       ; $D57C  A9 01
  sta _var_00be                  ; $D57E  85 BE
  lda #$03                       ; $D580  A9 03
  sta _var_00ba                  ; $D582  85 BA
  jsr _func_c6f5                 ; $D584  20 F5 C6
  jsr _func_c6cc                 ; $D587  20 CC C6
  lda #$06                       ; $D58A  A9 06
  sta _var_009d                  ; $D58C  85 9D
  lda #$0D                       ; $D58E  A9 0D
  sta _var_0025                  ; $D590  85 25
  rts                            ; $D592  60

_label_d593:
  lda #$01                       ; $D593  A9 01
  sta a:_var_0300_indexed        ; $D595  8D 00 03
  sta a:_var_0350                ; $D598  8D 50 03
  sta a:_var_0301_indexed        ; $D59B  8D 01 03
  sta a:_var_0351                ; $D59E  8D 51 03
  lda #$30                       ; $D5A1  A9 30
  ldx _var_00c1                  ; $D5A3  A6 C1
  cpx #$10                       ; $D5A5  E0 10
  bcs _label_d5ad                ; $D5A7  B0 04
  dex                            ; $D5A9  CA
  lda a:_data_ec17_indexed,X     ; $D5AA  BD 17 EC

_label_d5ad:
  sta $A8                        ; $D5AD  85 A8
  lda #$80                       ; $D5AF  A9 80
  sta _var_00a6                  ; $D5B1  85 A6
  lda #$01                       ; $D5B3  A9 01
  sta _var_00be                  ; $D5B5  85 BE
  lda #$03                       ; $D5B7  A9 03
  sta _var_00ba                  ; $D5B9  85 BA
  lda #$02                       ; $D5BB  A9 02
  sta _var_00bc                  ; $D5BD  85 BC
  lda #$00                       ; $D5BF  A9 00
  sta _var_00b5                  ; $D5C1  85 B5
  sta _var_00b9                  ; $D5C3  85 B9
  sta _var_00bd                  ; $D5C5  85 BD
  jsr _func_c6f5                 ; $D5C7  20 F5 C6
  jsr _func_c6cc                 ; $D5CA  20 CC C6
  lda #$0B                       ; $D5CD  A9 0B
  sta _var_0025                  ; $D5CF  85 25
  rts                            ; $D5D1  60

_label_d5d2:
  jsr _func_d131                 ; $D5D2  20 31 D1
  jsr _func_d160                 ; $D5D5  20 60 D1
  jsr _func_d5ee                 ; $D5D8  20 EE D5
  jsr _func_c6f5                 ; $D5DB  20 F5 C6
  jsr _func_d3d2                 ; $D5DE  20 D2 D3
  jsr _func_c6c4                 ; $D5E1  20 C4 C6
  jsr _func_cfba                 ; $D5E4  20 BA CF
  jsr _func_d428                 ; $D5E7  20 28 D4
  nop                            ; $D5EA  EA
  nop                            ; $D5EB  EA
  nop                            ; $D5EC  EA
  rts                            ; $D5ED  60

_func_d5ee:
  lda a:_var_0300_indexed        ; $D5EE  AD 00 03
  beq _label_d600                ; $D5F1  F0 0D
  ldy #$00                       ; $D5F3  A0 00
  sty _var_00a1                  ; $D5F5  84 A1
  jsr _func_c5f7                 ; $D5F7  20 F7 C5
  jsr _func_d652                 ; $D5FA  20 52 D6
  jsr _func_c607                 ; $D5FD  20 07 C6

_label_d600:
  lda a:_var_0350                ; $D600  AD 50 03
  beq _label_d612                ; $D603  F0 0D
  ldy #$50                       ; $D605  A0 50
  inc _var_00a1                  ; $D607  E6 A1
  jsr _func_c5f7                 ; $D609  20 F7 C5
  jsr _func_d652                 ; $D60C  20 52 D6
  jsr _func_c607                 ; $D60F  20 07 C6

_label_d612:
  lda _var_00bc                  ; $D612  A5 BC
  bne _label_d64b                ; $D614  D0 35
  ldx a:_var_0301_indexed        ; $D616  AE 01 03
  ldy a:_var_0351                ; $D619  AC 51 03
  cpx #$03                       ; $D61C  E0 03
  beq _label_d627                ; $D61E  F0 07
  cpy #$03                       ; $D620  C0 03
  beq _label_d627                ; $D622  F0 03
  jsr _func_d4fe                 ; $D624  20 FE D4

_label_d627:
  cpx #$00                       ; $D627  E0 00
  bne _label_d651                ; $D629  D0 26
  cpy #$00                       ; $D62B  C0 00
  bne _label_d651                ; $D62D  D0 22
  jsr _func_d446                 ; $D62F  20 46 D4
  lda #$00                       ; $D632  A9 00
  sta _var_00b9                  ; $D634  85 B9
  lda _var_00bb                  ; $D636  A5 BB
  cmp #$0A                       ; $D638  C9 0A
  beq _label_d640                ; $D63A  F0 04
  lda #$0A                       ; $D63C  A9 0A
  bne _label_d646                ; $D63E  D0 06

_label_d640:
  lda #$00                       ; $D640  A9 00
  sta _var_00a9_indexed          ; $D642  85 A9
  lda #$0C                       ; $D644  A9 0C

_label_d646:
  sta _var_0025                  ; $D646  85 25
  jmp _func_c23b                 ; $D648  4C 3B C2

_label_d64b:
  lda _var_00a6                  ; $D64B  A5 A6
  beq _label_d651                ; $D64D  F0 02
  dec _var_00a6                  ; $D64F  C6 A6

_label_d651:
  rts                            ; $D651  60

_func_d652:
  lda _var_0031                  ; $D652  A5 31
  jsr _jump_engine_c35e          ; $D654  20 5E C3
  cpx #$C5                       ; $D657  E0 C5
  adc #$D6                       ; $D659  69 D6
  sei                            ; $D65B  78
  dec _var_00d5_indexed,X        ; $D65C  D6 D5
  dec _var_0052_indexed,X        ; $D65E  D6 52
  dcp _var_008f_indexed,X        ; $D660  D7 8F
  dcp _var_00e0_indexed,X        ; $D662  D7 E0
  cmp _var_00e0_indexed          ; $D664  C5 E0
  cmp _var_00c5_indexed          ; $D666  C5 C5
  dcp _var_00a2_indexed,X        ; $D668  D7 A2
.byte $4f                        ; $D66A  4F  branch into instruction detected: sre a:_data_dabd

_label_d66b:
.byte $bd, $da                   ; $D66B  BD DA
  inx                            ; $D66D  E8
  sta _var_0030_indexed,X        ; $D66E  95 30
  dex                            ; $D670  CA
  bpl _label_d66b                ; $D671  10 F8
  lda #$01                       ; $D673  A9 01
  sta $A7                        ; $D675  85 A7
  rts                            ; $D677  60

.byte $a5, $a6, $d0, $58, $a9, $01, $85, $b9, $20, $88, $c5, $29, $3f, $a8, $c8, $84 ; $D678
.byte $a6, $20, $88, $c5, $29, $0f, $c5, $9c, $d0, $05, $18, $69, $01, $29, $0f, $85 ; $D688
.byte $9c, $0a, $85, $0c, $0a, $18, $65, $0c, $aa, $bd, $68, $e9, $85, $44, $bd, $69 ; $D698
.byte $e9, $85, $43, $bd, $6a, $e9, $85, $4a, $bd, $6b, $e9, $85, $42, $bd, $6c, $e9 ; $D6A8
.byte $85, $47, $bd, $6d, $e9, $85, $4c, $e6, $bb, $a5, $bb, $85, $3b, $c6, $bc, $a9 ; $D6B8
.byte $ff, $85, $5f, $20, $3c, $d5, $a9, $05, $85, $58, $e6, $31, $60, $a5, $58, $f0 ; $D6C8
.byte $07, $c6, $58, $d0, $03, $20, $f6, $d4, $a5, $4c, $30, $08, $a5, $49, $4a, $4a ; $D6D8
.byte $c9, $07, $90, $02, $a9, $07, $c5, $5f, $f0, $0b, $85, $5f, $18, $65, $a8, $aa ; $D6E8
.byte $bd, $c8, $e9, $85, $5e, $20, $1b, $d8, $48, $20, $ae, $d8, $68, $38, $e9, $01 ; $D6F8
.byte $d0, $f6, $a5, $4e, $30, $3f, $a5, $49, $c9, $30, $b0, $39, $20, $2f, $d8, $a5 ; $D708
.byte $32, $38, $e9, $40, $85, $32, $a5, $49, $4a, $aa, $bd, $2a, $e9, $85, $35, $86 ; $D718
.byte $0c, $38, $e9, $18, $85, $56, $a6, $c1, $a9, $00, $e0, $12, $90, $08, $a9, $03 ; $D728
.byte $e0, $23, $90, $02, $a9, $06, $18, $65, $0c, $aa, $bd, $44, $e9, $85, $3a, $20 ; $D738
.byte $05, $d8, $4c, $1b, $d0, $a9, $08, $85, $31, $60, $a6, $3b, $a9, $01, $9d, $ef ; $D748
.byte $03, $85, $ad, $a5, $56, $0a, $0a, $aa, $a0, $00, $bd, $f2, $ea, $99, $50, $00 ; $D758
.byte $e8, $c8, $c0, $04, $d0, $f4, $a9, $00, $85, $57, $a2, $00, $a5, $32, $20, $a5 ; $D768
.byte $da, $a5, $33, $20, $b5, $da, $e8, $e8, $e0, $20, $d0, $f0, $20, $56, $cf, $a6 ; $D778
.byte $36, $20, $42, $d0, $e6, $31, $60, $20, $05, $d8, $20, $3a, $d9, $a5, $36, $85 ; $D788
.byte $b4, $a4, $50, $c8, $f0, $09, $a2, $00, $a0, $0c, $a5, $54, $20, $ce, $d7, $a4 ; $D798
.byte $53, $c8, $f0, $09, $a2, $10, $a0, $20, $a5, $55, $20, $ce, $d7, $a5, $57, $c9 ; $D7A8
.byte $02, $d0, $03, $20, $ea, $d4, $a9, $00, $85, $54, $85, $55, $60, $a9, $00, $85 ; $D7B8
.byte $31, $a6, $36, $4c, $42, $d0, $85, $0d, $84, $0c, $a4, $b4, $a5, $0d, $d0, $04 ; $D7C8
.byte $b5, $60, $d0, $04, $e8, $4c, $f9, $d7, $99, $00, $02, $c8, $bd, $30, $ea, $99 ; $D7D8
.byte $00, $02, $c8, $e8, $bd, $30, $ea, $99, $00, $02, $c8, $b5, $60, $99, $00, $02 ; $D7E8
.byte $c8, $e8, $e4, $0c, $d0, $d6, $84, $b4, $98, $aa, $4c, $42, $d0, $a5, $a7, $f0 ; $D7F8
.byte $11, $a9, $00, $85, $a7, $a6, $36, $20, $42, $d0, $a9, $50, $85, $36, $a9, $9f ; $D808
.byte $85, $37, $60, $a6, $5e, $bd, $00, $ea, $48, $e8, $8a, $29, $03, $d0, $04, $ca ; $D818
.byte $ca, $ca, $ca, $86, $5e, $68, $60, $a5, $4d, $38, $e9, $00, $a8, $a5, $4e, $e9 ; $D828
.byte $10, $aa, $a9, $3b, $20, $db, $d8, $84, $14, $86, $15, $a5, $4d, $38, $e9, $00 ; $D838
.byte $a8, $a5, $4e, $e9, $10, $aa, $a9, $e7, $20, $db, $d8, $84, $12, $86, $13, $a5 ; $D848
.byte $48, $38, $e9, $00, $a8, $a5, $49, $e9, $18, $aa, $a9, $7f, $20, $db, $d8, $18 ; $D858
.byte $98, $69, $4f, $a8, $8a, $69, $23, $aa, $98, $38, $e5, $14, $85, $93, $8a, $e5 ; $D868
.byte $15, $c9, $50, $6a, $85, $94, $66, $93, $a4, $91, $a6, $92, $a9, $6c, $20, $db ; $D878
.byte $d8, $18, $98, $65, $12, $a8, $8a, $65, $13, $aa, $20, $07, $d9, $e9, $00, $49 ; $D888
.byte $7f, $85, $32, $a5, $43, $38, $e9, $00, $a8, $a5, $44, $e9, $09, $aa, $20, $07 ; $D898
.byte $d9, $49, $80, $85, $33, $60, $a9, $0f, $38, $e9, $05, $aa, $a0, $00, $b5, $40 ; $D8A8
.byte $10, $01, $88, $18, $75, $41, $95, $41, $85, $15, $98, $a0, $00, $75, $42, $95 ; $D8B8
.byte $42, $10, $01, $88, $06, $15, $75, $43, $95, $43, $98, $75, $44, $95, $44, $8a ; $D8C8
.byte $d0, $d6, $60, $84, $10, $86, $11, $85, $95, $a9, $00, $85, $96, $85, $97, $a2 ; $D8D8
.byte $08, $66, $95, $90, $0d, $18, $a5, $96, $65, $10, $85, $96, $a5, $97, $65, $11 ; $D8E8
.byte $85, $97, $0a, $66, $97, $66, $96, $ca, $d0, $e7, $a4, $96, $a6, $97, $60, $84 ; $D8F8
.byte $96, $86, $97, $a9, $00, $85, $95, $a2, $07, $18, $a5, $96, $65, $93, $a8, $a5 ; $D908
.byte $97, $65, $94, $90, $04, $84, $96, $85, $97, $26, $95, $26, $96, $26, $97, $38 ; $D918
.byte $a5, $96, $e5, $93, $a8, $a5, $97, $e5, $94, $ca, $10, $e7, $b0, $01, $ca, $a5 ; $D928
.byte $95, $60, $e6, $57, $a4, $50, $c0, $ff, $f0, $35, $e6, $50, $b9, $50, $ea, $85 ; $D938
.byte $0c, $85, $0f, $c9, $aa, $f0, $64, $c9, $bb, $f0, $67, $a5, $57, $c5, $51, $f0 ; $D948
.byte $6e, $a2, $00, $86, $0d, $bd, $22, $eb, $85, $0e, $8a, $0a, $aa, $b5, $60, $f0 ; $D958
.byte $07, $b5, $61, $f0, $03, $20, $f6, $d9, $a6, $0d, $e8, $e0, $06, $d0, $e4, $a4 ; $D968
.byte $53, $c0, $ff, $f0, $65, $e6, $53, $b9, $8f, $ea, $85, $0c, $c9, $aa, $f0, $46 ; $D978
.byte $c9, $bb, $f0, $49, $b9, $c2, $ea, $85, $0f, $a2, $00, $86, $0d, $bd, $28, $eb ; $D988
.byte $85, $0e, $8a, $0a, $18, $69, $10, $aa, $b5, $60, $f0, $07, $b5, $61, $f0, $03 ; $D998
.byte $20, $f6, $d9, $a6, $0d, $e8, $e0, $08, $d0, $e1, $60, $a9, $ff, $85, $50, $4c ; $D9A8
.byte $77, $d9, $a9, $01, $85, $54, $a9, $00, $85, $0c, $85, $0f, $4c, $59, $d9, $a5 ; $D9B8
.byte $52, $85, $53, $4c, $59, $d9, $a9, $ff, $85, $53, $4c, $e2, $d9, $a9, $01, $85 ; $D9C8
.byte $55, $a9, $00, $85, $0c, $85, $0f, $4c, $91, $d9, $a5, $50, $c9, $ff, $d0, $0d ; $D9D8
.byte $a5, $53, $c9, $ff, $d0, $07, $20, $f9, $cf, $a9, $08, $85, $31, $60, $a5, $57 ; $D9E8
.byte $29, $03, $85, $1b, $a5, $0e, $20, $5e, $c3, $e0, $c5, $21, $da, $2e, $da, $38 ; $D9F8
.byte $da, $40, $da, $45, $da, $4d, $da, $57, $da, $e0, $c5, $61, $da, $6c, $da, $7d ; $DA08
.byte $da, $75, $da, $85, $da, $90, $da, $9a, $da, $a5, $0f, $20, $b5, $da, $a5, $0c ; $DA18
.byte $20, $2b, $d1, $4c, $a5, $da, $a5, $1b, $f0, $f4, $20, $26, $da, $4c, $40, $da ; $DA28
.byte $a5, $0f, $20, $2b, $d1, $20, $a5, $da, $a5, $0c, $4c, $b5, $da, $20, $40, $da ; $DA38
.byte $a5, $0f, $4c, $a5, $da, $a5, $1b, $f0, $f7, $20, $5c, $da, $4c, $40, $da, $a5 ; $DA48
.byte $0f, $20, $b5, $da, $a5, $0c, $4c, $a5, $da, $a5, $0f, $20, $2b, $d1, $20, $b5 ; $DA58
.byte $da, $4c, $5c, $da, $a5, $1b, $f0, $d8, $a5, $0c, $20, $a5, $da, $a5, $0c, $20 ; $DA68
.byte $2b, $d1, $4c, $b5, $da, $a5, $0f, $20, $a5, $da, $4c, $75, $da, $20, $75, $da ; $DA78
.byte $a5, $0f, $20, $2b, $d1, $4c, $a5, $da, $a5, $1b, $f0, $f4, $20, $75, $da, $4c ; $DA88
.byte $26, $da, $a5, $0f, $20, $2b, $d1, $20, $b5, $da, $4c, $26, $da, $18, $75, $60 ; $DA98
.byte $c9, $07, $90, $04, $c9, $c7, $90, $02, $a9, $00, $95, $60, $60, $18, $75, $61 ; $DAA8
.byte $c9, $07, $90, $04, $c9    ; $DAB8

_data_dabd:
.byte $f8, $90, $02, $a9, $00, $95, $61, $60, $0f, $db, $14, $db, $1d, $db, $26, $db ; $DABD
.byte $2f, $db, $38, $db, $41, $db, $4a, $db, $5b, $db, $86, $db, $6c, $db, $79, $db ; $DACD
.byte $8f, $db, $9c, $db, $a9, $db, $b6, $db, $c3, $db, $3a, $dc, $fa, $db, $07, $dc ; $DADD
.byte $0c, $dc, $25, $dc, $d0, $db, $e5, $db, $4b, $dc, $50, $dc, $61, $dc, $72, $dc ; $DAED
.byte $7b, $dc, $88, $dc, $91, $dc, $9a, $dc, $9f, $dc, $a8, $dc, $ad, $dc, $b6, $dc ; $DAFD
.byte $bb, $dc, $dd, $0c, $f0, $f0, $00, $dd, $24, $f0, $f0, $dd, $e1, $ef, $08, $00 ; $DB0D
.byte $dd, $3a, $f0, $f0, $dd, $e1, $ee, $08, $00, $dd, $53, $f0, $f8, $dd, $65, $f4 ; $DB1D
.byte $f0, $00, $dd, $6f, $f0, $f8, $dd, $81, $fc, $f0, $00, $dd, $8a, $f0, $f8, $dd ; $DB2D
.byte $9c, $04, $f0, $00, $dd, $c3, $f0, $f0, $dd, $d7, $fc, $10, $00, $dd, $e6, $f8 ; $DB3D
.byte $f8, $dd, $ef, $ff, $f0, $dd, $f4, $f7, $08, $dd, $dc, $fb, $10, $00, $dd, $fa ; $DB4D
.byte $f8, $f8, $dd, $ef, $fe, $f0, $dd, $f4, $f6, $08, $dd, $d7, $fa, $10, $00, $de ; $DB5D
.byte $04, $f0, $f4, $de, $12, $f4, $04, $de, $17, $08, $04, $00, $de, $1c, $f0, $fc ; $DB6D
.byte $de, $2a, $f4, $f4, $de, $2f, $08, $f4, $00, $dd, $a5, $f0, $f0, $dd, $bd, $08 ; $DB7D
.byte $fa, $00, $de, $90, $f8, $10, $de, $34, $f0, $e8, $df, $ed, $e8, $ea, $00, $de ; $DB8D
.byte $90, $f8, $10, $de, $4b, $f0, $e8, $df, $f2, $e0, $f0, $00, $de, $90, $f8, $10 ; $DB9D
.byte $de, $62, $f0, $e8, $df, $ed, $e8, $ea, $00, $de, $90, $f8, $10, $de, $79, $f0 ; $DBAD
.byte $e8, $df, $f2, $e0, $f0, $00, $de, $9a, $f8, $10, $de, $34, $f0, $e8, $df, $ed ; $DBBD
.byte $e8, $ea, $00, $de, $a4, $f0, $f8, $de, $b8, $10, $f8, $de, $c0, $ed, $f0, $de ; $DBCD
.byte $c6, $f0, $08, $de, $cb, $fe, $f0, $00, $de, $d3, $f0, $f8, $de, $e7, $10, $f8 ; $DBDD
.byte $de, $ef, $ed, $f0, $de, $f5, $f0, $08, $de, $fa, $fe, $f0, $00, $df, $02, $e0 ; $DBED
.byte $00, $df, $0b, $f0, $10, $df, $10, $f0, $f0, $00, $df, $29, $f0, $f0, $00, $df ; $DBFD
.byte $3f, $ed, $f0, $df, $45, $03, $f0, $df, $4b, $f0, $f8, $df, $55, $10, $f8, $df ; $DC0D
.byte $5d, $f0, $00, $df, $80, $04, $18, $00, $df, $85, $f0, $e0, $df, $5d, $f0, $00 ; $DC1D
.byte $df, $ab, $04, $e0, $df, $b0, $04, $18, $df, $55, $10, $f8, $00, $df, $b5, $e0 ; $DC2D
.byte $00, $df, $cb, $00, $00, $df, $da, $f0, $e8, $df, $f8, $e0, $f0, $00, $df, $fe ; $DC3D
.byte $f8, $f4, $00, $e0, $0f, $fc, $f5, $e0, $14, $fc, $03, $e0, $19, $f9, $fc, $e0 ; $DC4D
.byte $1e, $fe, $fc, $00, $e0, $0f, $fc, $f7, $e0, $14, $fc, $01, $e0, $19, $fa, $fc ; $DC5D
.byte $e0, $1e, $fd, $fc, $00, $e0, $0f, $fc, $f8, $e0, $14, $fc, $00, $00, $e0, $23 ; $DC6D
.byte $fc, $f7, $e0, $23, $fc, $f9, $e0, $28, $fc, $01, $00, $e0, $23, $fc, $f8, $e0 ; $DC7D
.byte $28, $fc, $00, $00, $e0, $23, $fc, $f9, $e0, $28, $fc, $ff, $00, $e0, $2d, $fc ; $DC8D
.byte $fc, $00, $e0, $32, $fc, $fc, $e0, $32, $fc, $fb, $00, $e0, $32, $fc, $fc, $00 ; $DC9D
.byte $e0, $37, $fc, $fc, $e0, $37, $fc, $fd, $00, $e0, $37, $fc, $fc, $00, $e0, $3c ; $DCAD
.byte $fc, $f8, $00, $00, $00, $08, $00, $10, $00, $18, $00, $00, $08, $08, $08, $10 ; $DCBD
.byte $08, $18, $08, $00, $00, $00, $08, $00, $10, $00, $18, $08, $00, $08, $08, $08 ; $DCCD
.byte $10, $08, $18, $10, $00, $10, $08, $10, $10, $10, $18, $18, $00, $18, $08, $18 ; $DCDD
.byte $10, $18, $18, $08, $20, $10, $20, $18, $20, $18, $20, $00, $00, $08, $00, $10 ; $DCED
.byte $00, $00, $08, $08, $08, $10, $08, $00, $00, $08, $00, $00, $18, $08, $18, $01 ; $DCFD
.byte $fd, $00, $00, $01, $02, $fd, $01, $03, $fd, $00, $04, $05, $06, $07, $08, $09 ; $DD0D
.byte $0a, $fe, $fd, $01, $0b, $0c, $ff, $01, $fd, $00, $fe, $fe, $0d, $fe, $fd, $00 ; $DD1D
.byte $0f, $10, $11, $fe, $12, $13, $14, $15, $fd, $01, $16, $17, $ff, $01, $fd, $00 ; $DD2D
.byte $fe, $fe, $18, $fe, $fd, $00, $1a, $1b, $1c, $fe, $1d, $1e, $1f, $fe, $fd, $01 ; $DD3D
.byte $20, $21, $fd, $00, $22, $ff, $00, $fd, $00, $25, $26, $27, $fd, $01, $28, $fd ; $DD4D
.byte $40, $25, $26, $27, $fd, $41, $28, $ff, $03, $fd, $00, $23, $24, $fd, $40, $23 ; $DD5D
.byte $24, $ff, $00, $fd, $00, $2a, $2b, $2c, $fd, $01, $2d, $fd, $40, $2a, $2b, $2c ; $DD6D
.byte $fd, $41, $2d, $ff, $03, $fd, $00, $29, $fe, $fd, $40, $29, $ff, $00, $fd, $00 ; $DD7D
.byte $2f, $30, $31, $fd, $01, $32, $fd, $40, $2f, $30, $31, $fd, $41, $32, $ff, $03 ; $DD8D
.byte $fd, $00, $2e, $fe, $fd, $40, $2e, $ff, $01, $fd, $00, $33, $34, $35, $fd, $01 ; $DD9D
.byte $36, $fd, $00, $37, $38, $39, $fd, $01, $3a, $fd, $00, $fe, $3b, $3c, $3d, $ff ; $DDAD
.byte $01, $fd, $01, $3e, $3f, $ff, $01, $fd, $00, $fe, $40, $41, $fe, $fe, $42, $43 ; $DDBD
.byte $44, $45, $46, $47, $48, $fe, $fd, $01, $49, $ff, $00, $fd, $01, $4a, $ff, $00 ; $DDCD
.byte $fd, $01, $f6, $ff, $00, $fd, $01, $03, $ff, $02, $fd, $01, $9f, $a0, $a1, $a2 ; $DDDD
.byte $a3, $ff, $00, $fd, $01, $45, $ff, $00, $fd, $00, $44, $48, $ff, $02, $fd, $01 ; $DDED
.byte $a4, $a5, $a6, $a7, $a8, $a9, $ff, $00, $fd, $01, $ab, $ac, $fe, $fe, $0e, $19 ; $DDFD
.byte $aa, $fd, $80, $e5, $ff, $00, $fd, $81, $ea, $ff, $00, $fd, $81, $e9, $ff, $00 ; $DE0D
.byte $fd, $41, $0e, $19, $aa, $fd, $c0, $e5, $fd, $41, $ab, $ac, $ff, $00, $fd, $c1 ; $DE1D
.byte $ea, $ff, $00, $fd, $c1, $e9, $ff, $01, $fd, $03, $52, $53, $54, $fe, $55, $56 ; $DE2D
.byte $56, $57, $5a, $5b, $5c, $5d, $61, $62, $63, $64, $58, $5e, $65, $ff, $01, $fd ; $DE3D
.byte $03, $52, $6a, $54, $fe, $55, $6b, $56, $57, $6c, $6d, $6e, $6f, $70, $71, $72 ; $DE4D
.byte $73, $58, $5e, $74, $ff, $01, $fd, $03, $75, $53, $54, $fe, $76, $56, $56, $57 ; $DE5D
.byte $77, $78, $79, $7a, $7b, $7c, $7d, $7e, $58, $5e, $7f, $ff, $01, $fd, $03, $52 ; $DE6D
.byte $6a, $54, $fe, $76, $6b, $56, $57, $80, $81, $82, $83, $85, $86, $87, $88, $58 ; $DE7D
.byte $84, $89, $ff, $02, $fd, $02, $59, $5f, $66, $fe, $60, $67, $ff, $02, $fd, $02 ; $DE8D
.byte $4b, $4c, $4d, $4e, $4f, $50, $ff, $00, $fd, $02, $cd, $ce, $cf, $fd, $03, $d0 ; $DE9D
.byte $fd, $42, $cd, $ce, $fd, $02, $d2, $fd, $03, $d3, $ff, $01, $fd, $03, $d1, $fd ; $DEAD
.byte $43, $d1, $ff, $03, $fd, $02, $c9, $ca, $ff, $00, $fd, $02, $d4, $ff, $03, $fd ; $DEBD
.byte $03, $cb, $cc, $d5, $d6, $ff, $00, $fd, $02, $d7, $d8, $d9, $fd, $03, $d0, $fd ; $DECD
.byte $42, $d7, $d8, $fd, $02, $da, $fd, $03, $d3, $ff, $01, $fd, $03, $d1, $fd, $43 ; $DEDD
.byte $d1, $ff, $03, $fd, $02, $c9, $ca, $ff, $00, $fd, $02, $d4, $ff, $03, $fd, $03 ; $DEED
.byte $cb, $cc, $d5, $d6, $ff, $02, $fd, $03, $b3, $b4, $fe, $b9, $ba, $ff, $00, $fd ; $DEFD
.byte $02, $bf, $ff, $01, $fd, $03, $fe, $af, $b5, $fd, $02, $bb, $fd, $03, $fe, $b0 ; $DF0D
.byte $b6, $bc, $ad, $b1, $b7, $bd, $ae, $b2, $b8, $be, $c0, $ff, $01, $fd, $03, $fe ; $DF1D
.byte $fe, $c1, $c2, $c3, $c4, $c5, $c6, $ad, $b1, $b7, $c7, $ae, $b2, $b8, $be, $fe ; $DF2D
.byte $c8, $ff, $00, $fd, $02, $c9, $ca, $ff, $00, $fd, $03, $db, $dc, $ff, $00, $fd ; $DF3D
.byte $02, $dd, $de, $fd, $03, $df, $e0, $ff, $01, $fd, $03, $d1, $fd, $43, $d1, $ff ; $DF4D
.byte $01, $fd, $42, $dd, $fd, $02, $d4, $fd, $00, $e5, $fd, $01, $e9, $fd, $42, $de ; $DF5D
.byte $fd, $03, $e2, $e6, $fe, $e1, $e3, $fd, $01, $e7, $fe, $fd, $43, $e0, $fd, $01 ; $DF6D
.byte $e4, $e8, $ff, $00, $fd, $01, $ea, $ff, $01, $fd, $41, $e9, $fd, $40, $e5, $fd ; $DF7D
.byte $42, $d4, $fd, $02, $dd, $fe, $fd, $43, $e6, $e2, $fd, $02, $de, $fe, $fd, $41 ; $DF8D
.byte $e7, $fd, $43, $e3, $e1, $fe, $fd, $41, $e8, $e4, $fd, $03, $e0, $ff, $00, $fd ; $DF9D
.byte $41, $ea, $ff, $00, $fd, $01, $ea, $ff, $01, $fd, $03, $8a, $8b, $fe, $fe, $8c ; $DFAD
.byte $fd, $02, $8d, $8e, $fe, $8f, $90, $91, $92, $93, $94, $95, $96, $ff, $01, $fd ; $DFBD
.byte $03, $97, $fd, $02, $98, $fd, $03, $99, $fe, $9a, $9b, $9c, $ff, $01, $fd, $03 ; $DFCD
.byte $52, $53, $54, $fe, $55, $56, $56, $fe, $5a, $5b, $5c, $fe, $61, $62, $63, $ff ; $DFDD
.byte $01, $fd, $03, $51, $ff, $02, $fd, $03, $68, $69, $ff, $00, $fd, $03, $9d, $9e ; $DFED
.byte $ff, $01, $fd, $00, $f2, $f3, $fd, $40, $f2, $fe, $fd, $00, $f4, $f5, $fd, $40 ; $DFFD
.byte $f4, $ff, $00, $fd, $00, $eb, $ff, $00, $fd, $40, $eb, $ff, $00, $fd, $00, $f3 ; $E00D
.byte $ff, $00, $fd, $00, $f5, $ff, $01, $fd, $00, $ec, $ff, $01, $fd, $40, $ec, $ff ; $E01D
.byte $01, $fd, $00, $ef, $ff, $00, $fd, $00, $f0, $ff, $00, $fd, $00, $f1, $ff, $01 ; $E02D
.byte $fd, $00, $ed, $ee, $ff, $23, $00, $60, $50, $23, $20, $60, $50, $23, $40, $60 ; $E03D
.byte $50, $23, $60, $60, $50, $23, $80, $60, $50, $23, $a0, $60, $50, $22, $40, $20 ; $E04D
.byte $3d, $3e, $3f, $40, $56, $57, $d1, $d2, $3a, $3b, $3c, $3d, $3e, $3f, $40, $39 ; $E05D
.byte $3a, $3b, $3c, $3d, $3e, $3f, $40, $d2, $30, $31, $32, $33, $39, $3a, $3b, $3c ; $E06D
.byte $22, $60, $20, $95, $96, $97, $98, $58, $59, $5a, $5b, $92, $93, $94, $95, $96 ; $E07D
.byte $97, $98, $91, $92, $93, $94, $95, $96, $97, $98, $5b, $34, $35, $36, $37, $91 ; $E08D
.byte $92, $93, $94, $22, $80, $20, $46, $45, $48, $46, $46, $45, $46, $48, $42, $43 ; $E09D
.byte $44, $46, $45, $48, $46, $41, $42, $43, $44, $46, $45, $48, $46, $48, $38, $45 ; $E0AD
.byte $46, $46, $41, $42, $43, $44, $22, $a0, $60, $46, $22, $a4, $01, $48, $22, $a8 ; $E0BD
.byte $01, $47, $22, $aa, $01, $48, $22, $b0, $01, $47, $22, $b2, $01, $48, $22, $ba ; $E0CD
.byte $01, $48, $22, $c0, $20, $4c, $4d, $4e, $4f, $49, $4a, $4b, $49, $4c, $4d, $4e ; $E0DD
.byte $4f, $4d, $4e, $4f, $49, $4a, $4b, $49, $4c, $4d, $4e, $4f, $49, $49, $4a, $4b ; $E0ED
.byte $49, $4c, $4d, $4e, $4f, $22, $e0, $20, $52, $50, $53, $50, $50, $51, $50, $50 ; $E0FD
.byte $52, $50, $53, $50, $50, $53, $50, $50, $51, $50, $50, $52, $50, $53, $50, $50 ; $E10D
.byte $50, $51, $50, $50, $52, $50, $53, $50, $23, $00, $01, $52, $23, $02, $02, $54 ; $E11D
.byte $52, $23, $0a, $02, $54, $52, $23, $0d, $02, $54, $52, $23, $0f, $02, $54, $52 ; $E12D
.byte $23, $15, $02, $54, $52, $23, $1e, $02, $54, $52, $21, $f9, $03, $28, $29, $2a ; $E13D
.byte $22, $19, $03, $2b, $46, $2c, $22, $38, $04, $2d, $2e, $46, $2f, $20, $81, $04 ; $E14D
.byte $5c, $5d, $5e, $5f, $20, $a1, $05, $60, $61, $46, $62, $63, $20, $c1, $05, $64 ; $E15D
.byte $65, $66, $67, $68, $20, $e3, $05, $69, $74, $75, $76, $6a, $21, $03, $05, $6b ; $E16D
.byte $6c, $7c, $6d, $6e, $21, $23, $05, $6f, $70, $71, $72, $73, $21, $40, $07, $74 ; $E17D
.byte $75, $76, $77, $78, $79, $7a, $21, $60, $09, $7b, $7c, $7d, $7e, $7f, $80, $5d ; $E18D
.byte $5e, $5f, $21, $81, $09, $81, $82, $83, $84, $60, $61, $46, $62, $63, $21, $a3 ; $E19D
.byte $07, $85, $86, $64, $87, $88, $67, $68, $21, $c3, $04, $89, $8a, $8b, $8c, $21 ; $E1AD
.byte $e4, $02, $8d, $8e, $22, $04, $02, $8f, $90, $22, $24, $02, $8f, $55, $23, $03 ; $E1BD
.byte $02, $1b, $27, $23, $23, $5b, $e3, $23, $22, $06, $e2, $e3, $e3, $e3, $e4, $e2 ; $E1CD
.byte $23, $36, $02, $e4, $e2, $23, $3e, $01, $e4, $23, $48, $56, $b7, $23, $42, $06 ; $E1DD
.byte $e5, $d9, $d9, $d9, $e7, $e5, $23, $4c, $4a, $d6, $23, $56, $02, $e7, $e5, $23 ; $E1ED
.byte $5e, $01, $e7, $23, $58, $46, $00, $23, $68, $56, $b7, $23, $62, $06, $e5, $da ; $E1FD
.byte $db, $dc, $e7, $e5, $23, $76, $02, $e7, $e5, $23, $7e, $01, $e7, $23, $79, $05 ; $E20D
.byte $1c, $0c, $18, $1b, $0e, $23, $83, $5b, $e9, $23, $82, $01, $e8, $23, $86, $02 ; $E21D
.byte $ea, $e8, $23, $96, $02, $ea, $e8, $23, $9e, $01, $ea, $23, $c0, $60, $00, $23 ; $E22D
.byte $ca, $04, $cc, $ff, $ff, $ff, $23, $d2, $04, $cc, $ff, $ff, $ff, $23, $e0, $48 ; $E23D
.byte $50, $23, $e1, $01, $40, $23, $e8, $48, $a5, $23, $f0, $08, $aa, $aa, $aa, $fa ; $E24D
.byte $fa, $ba, $fa, $ba, $23, $f8, $48, $0a, $23, $48, $03, $11, $12, $1d, $00, $22 ; $E25D
.byte $20, $60, $b6, $22, $40, $60, $b5, $22, $60, $60, $b5, $22, $80, $60, $b5, $22 ; $E26D
.byte $a0, $60, $b5, $22, $c0, $60, $b5, $22, $e0, $60, $b5, $23, $00, $60, $b5, $21 ; $E27D
.byte $85, $05, $ac, $ad, $ae, $c1, $c2, $21, $a4, $07, $af, $b0, $b5, $b5, $c3, $c4 ; $E28D
.byte $c5, $21, $b0, $04, $ec, $b4, $b8, $b9, $21, $c2, $0b, $b1, $b2, $b5, $b5, $b5 ; $E29D
.byte $b5, $b5, $c6, $c7, $c8, $c9, $21, $ce, $0f, $ca, $b4, $b5, $b5, $b5, $ed, $ba ; $E2AD
.byte $bb, $bc, $b3, $eb, $b0, $be, $bb, $bf, $21, $e2, $59, $b5, $21, $e0, $02, $b3 ; $E2BD
.byte $b4, $21, $eb, $04, $cb, $c4, $cc, $cd, $21, $f5, $01, $bd, $21, $fb, $05, $bd ; $E2CD
.byte $cb, $c4, $c8, $bb, $22, $00, $5d, $b5, $22, $0d, $03, $ce, $cf, $d0, $22, $1d ; $E2DD
.byte $03, $c3, $c0, $c0, $22, $60, $06, $99, $9a, $9b, $9c, $99, $9a, $22, $80, $06 ; $E2ED
.byte $9d, $9e, $9f, $a0, $9d, $9e, $22, $a0, $06, $a1, $a2, $a3, $a4, $a1, $a2, $22 ; $E2FD
.byte $c0, $06, $a5, $a6, $a5, $a7, $a5, $a6, $22, $47, $84, $9b, $9f, $a3, $a5, $22 ; $E30D
.byte $48, $84, $9c, $a0, $a4, $a6, $22, $4a, $02, $a8, $a9, $22, $6a, $02, $aa, $ab ; $E31D
.byte $22, $58, $05, $a8, $a9, $a8, $a8, $a8, $22, $77, $06, $a8, $aa, $ab, $aa, $aa ; $E32D
.byte $aa, $22, $74, $82, $a9, $ab, $22, $97, $01, $aa, $22, $ba, $04, $99, $9a, $9b ; $E33D
.byte $9c, $22, $da, $04, $9d, $9e, $9f, $a0, $22, $fa, $04, $a1, $a2, $a3, $a4, $23 ; $E34D
.byte $20, $60, $c0, $23, $40, $60, $c0, $23, $60, $60, $c0, $23, $80, $60, $c0, $23 ; $E35D
.byte $a0, $60, $c0, $23, $00, $60, $dd, $23, $08, $50, $df, $23, $07, $01, $de, $23 ; $E36D
.byte $18, $01, $e0, $23, $28, $56, $e3, $23, $48, $56, $b7, $23, $68, $56, $b7, $23 ; $E37D
.byte $88, $56, $e9, $23, $58, $46, $00, $23, $22, $06, $e2, $e3, $e3, $e3, $e4, $e2 ; $E38D
.byte $23, $42, $06, $e5, $d9, $d9, $d9, $e7, $e5, $23, $62, $06, $e5, $da, $db, $dc ; $E39D
.byte $e7, $e5, $23, $82, $06, $e8, $e9, $e9, $e9, $ea, $e8, $23, $4c, $4a, $d4, $23 ; $E3AD
.byte $03, $02, $1b, $27, $23, $36, $84, $e4, $e7, $e7, $ea, $23, $37, $84, $e2, $e5 ; $E3BD
.byte $e5, $e8, $23, $3e, $84, $e4, $e7, $e7, $ea, $23, $79, $05, $1c, $0c, $18, $1b ; $E3CD
.byte $0e, $23, $c0, $60, $00, $23, $c8, $50, $ff, $23, $e0, $48, $50, $23, $e8, $48 ; $E3DD
.byte $55, $23, $f0, $08, $aa, $aa, $aa, $fa, $fa, $ba, $fa, $ba, $23, $f8, $48, $0a ; $E3ED
.byte $23, $48, $03, $11, $12, $1d, $00, $20, $64, $53, $b7, $20, $84, $53, $b7, $20 ; $E3FD
.byte $a4, $53, $b7, $20, $c4, $53, $b7, $20, $e4, $53, $b7, $20, $86, $82, $f5, $f4 ; $E40D
.byte $20, $67, $85, $f0, $b7, $b7, $b7, $f1, $20, $68, $c5, $24, $20, $6b, $83, $24 ; $E41D
.byte $24, $f4, $20, $e9, $04, $f3, $b7, $b7, $f1, $20, $6d, $c5, $24, $20, $6e, $04 ; $E42D
.byte $f2, $b7, $b7, $f0, $20, $ee, $04, $f3, $b7, $b7, $f1, $20, $90, $02, $f5, $f6 ; $E43D
.byte $20, $b0, $02, $f4, $f7, $20, $72, $c5, $24, $20, $75, $85, $24, $f8, $b7, $f9 ; $E44D
.byte $24, $20, $96, $82, $f1, $f0, $21, $24, $58, $fb, $21, $49, $53, $b7, $21, $69 ; $E45D
.byte $52, $b7, $21, $89, $52, $b7, $21, $a9, $52, $b7, $21, $c9, $52, $b7, $21, $4b ; $E46D
.byte $85, $24, $fa, $b7, $24, $24, $21, $4d, $c5, $24, $21, $ce, $04, $f3, $b7, $b7 ; $E47D
.byte $f1, $21, $50, $83, $24, $24, $f4, $21, $52, $c5, $24, $21, $55, $85, $24, $f0 ; $E48D
.byte $b7, $f9, $24, $21, $57, $c5, $24, $21, $78, $c4, $24, $21, $7b, $c4, $24, $22 ; $E49D
.byte $28, $0f, $10, $0a, $16, $0e, $24, $0a, $24, $24, $24, $01, $24, $0d, $1e, $0c ; $E4AD
.byte $14, $22, $68, $10, $10, $0a, $16, $0e, $24, $0b, $24, $24, $24, $02, $24, $0d ; $E4BD
.byte $1e, $0c, $14, $1c, $22, $a8, $16, $10, $0a, $16, $0e, $24, $0c, $24, $24, $24 ; $E4CD
.byte $0c, $15, $0a, $22, $24, $1c, $11, $18, $18, $1d, $12, $17, $10, $23, $07, $0b ; $E4DD
.byte $1d, $18, $19, $24, $1c, $0c, $18, $1b, $0e, $24, $27, $23, $45, $16, $25, $01 ; $E4ED
.byte $09, $08, $04, $24, $17, $12, $17, $1d, $0e, $17, $0d, $18, $24, $0c, $18, $ee ; $E4FD
.byte $15, $1d, $0d, $ef, $23, $c0, $60, $00, $23, $e0, $42, $55, $23, $e2, $46, $ff ; $E50D
.byte $23, $ea, $46, $ff, $23, $f0, $48, $5a, $23, $f8, $48, $00, $23, $e1, $01, $55 ; $E51D
.byte $23, $e9, $01, $55, $00    ; $E52D

_data_e532_indexed:
.byte $40                        ; $E532

_data_e533_indexed:
.byte $e5, $58, $e5, $7c, $e5, $a0, $e5, $a9, $e5, $c7, $e5, $b4, $e5, $3f, $00, $10 ; $E533
.byte $0f, $2c, $27, $0f, $0f, $0f, $30, $30, $0f, $0f, $2a, $2a, $0f, $0f, $27, $27 ; $E543
.byte $3f, $10, $50, $0f, $00, $3f, $00, $20, $21, $07, $29, $0a, $21, $30, $29, $0a ; $E553
.byte $21, $0f, $29, $18, $21, $0f, $30, $16, $21, $30, $0a, $0f, $21, $30, $26, $0f ; $E563
.byte $21, $30, $17, $0f, $21, $07, $17, $0f, $00, $3f, $00, $20, $2c, $29, $19, $09 ; $E573
.byte $2c, $07, $29, $1a, $2c, $0f, $29, $10, $2c, $0f, $30, $16, $2c, $30, $0f, $0f ; $E583
.byte $2c, $30, $16, $07, $2c, $30, $17, $0f, $2c, $07, $17, $0f, $00, $3f, $00, $60 ; $E593
.byte $0f, $3f, $03, $01, $30, $00, $3f, $00, $60, $0f, $3f, $11, $03, $30, $30, $30 ; $E5A3
.byte $00, $3f, $10, $10, $21, $30, $0a, $0f, $21, $30, $26, $0f, $21, $30, $17, $0f ; $E5B3
.byte $21, $07, $17, $0f, $3f, $00, $10, $21, $07, $29, $0a, $21, $30, $29, $0a, $21 ; $E5C3
.byte $0f, $29, $18, $21, $0f, $30, $16, $00, $23, $58, $06, $00 ; $E5D3

_data_e5df_indexed:
.byte $00, $01, $20, $00, $00, $01, $20, $00, $00, $01, $20, $00 ; $E5DF

_data_e5eb_indexed:
.byte $01, $01, $a8, $80, $00, $00, $00, $3f, $01, $00, $03, $00, $00, $00, $00, $00 ; $E5EB
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $03, $00, $00, $00, $00 ; $E5FB
.byte $76, $ed, $98, $ed, $b0, $ed, $bc, $ed, $d4, $ed, $fa, $ed, $1a, $ee, $34, $ee ; $E60B
.byte $4c, $ee, $68, $ee, $82, $ee, $96, $ee, $b8, $ee, $d0, $ee, $f4, $ee, $0e, $ef ; $E61B
.byte $2a, $ef, $2d, $ef, $30, $ef, $33, $ef, $36, $ef, $39, $ef, $3c, $ef, $3f, $ef ; $E62B
.byte $42, $ef, $45, $ef, $48, $ef, $4b, $ef, $4e, $ef, $51, $ef, $54, $ef, $57, $ef ; $E63B
.byte $00, $03, $10, $17, $24, $27, $34, $3b, $48, $4b, $58, $5f, $6c, $6f, $7c, $83 ; $E64B
.byte $90, $95, $98, $9b, $9e, $a1, $ff, $00, $aa, $ff, $01, $ff, $00, $ff, $00, $ff ; $E65B
.byte $01, $ff, $00, $00, $00, $aa, $ff, $01, $ff, $01, $00, $00, $aa, $00, $01, $ff ; $E66B
.byte $01, $00, $01, $ff, $01, $00, $01, $00, $00, $aa, $00, $01, $aa, $00, $01, $01 ; $E67B
.byte $01, $00, $01, $01, $01, $00, $01, $00, $00, $aa, $01, $01, $01, $01, $00, $00 ; $E68B
.byte $aa, $01, $01, $01, $00, $01, $00, $01, $01, $01, $00, $00, $00, $aa, $01, $00 ; $E69B
.byte $aa, $01, $ff, $01, $00, $01, $00, $01, $ff, $01, $00, $00, $00, $aa, $01, $ff ; $E6AB
.byte $01, $ff, $00, $00, $aa, $00, $ff, $01, $ff, $00, $ff, $01, $ff, $00, $ff, $00 ; $E6BB
.byte $00, $aa, $00, $ff, $aa, $00, $ff, $ff, $ff, $00, $ff, $ff, $ff, $00, $ff, $00 ; $E6CB
.byte $00, $aa, $ff, $ff, $ff, $ff, $00, $00, $aa, $ff, $ff, $ff, $00, $ff, $00, $ff ; $E6DB
.byte $ff, $ff, $00, $00, $00, $aa, $02, $01, $02, $ff, $aa, $ff, $fe, $aa, $fe, $ff ; $E6EB
.byte $aa, $fe, $00, $aa, $fe, $01, $aa, $ff, $02, $aa, $02, $00, $02, $01, $04, $02 ; $E6FB
.byte $fe, $02, $03, $02, $04, $04, $05, $fe, $14, $09, $ff, $06, $01, $04, $0a, $04 ; $E70B
.byte $0b, $fe, $02, $06, $02, $07, $04, $08, $fe, $21, $30, $0a, $0f, $21, $30, $26 ; $E71B
.byte $0f, $21, $30, $14, $02, $21, $30, $26, $02, $21, $30, $0f, $05, $21, $30, $26 ; $E72B
.byte $05, $04, $08, $0c, $08, $0c, $10, $08, $0c, $10, $0c, $10, $14, $10, $14, $18 ; $E73B
.byte $10, $14, $18, $14, $18, $1c, $14, $1c, $1c, $18, $1c, $1c, $1c, $1c, $20, $10 ; $E74B
.byte $14, $14, $18, $18, $1c, $1c, $20, $20, $24, $24, $28, $00, $01, $10, $11, $12 ; $E75B
.byte $20, $21, $22, $01, $01, $ac, $18, $00, $00, $00, $bf, $00, $00, $00, $00, $00 ; $E76B
.byte $00, $00, $00, $00, $00, $00, $00, $00, $60, $00, $00, $00, $00, $00, $00, $00 ; $E77B
.byte $00, $00, $00, $06, $0c, $06, $0d, $06, $0e, $06, $0f, $fe, $00, $08, $0c, $08 ; $E78B
.byte $10, $08, $0c, $08, $10, $08, $0c, $08, $10, $ff, $02, $01, $10, $11, $ff, $08 ; $E79B
.byte $01, $90, $03, $12, $83, $01, $12, $83, $01, $12, $83, $01, $12, $83, $01, $12 ; $E7AB
.byte $82, $01, $12, $82, $01, $12, $82, $01, $12, $82, $01, $12, $81, $01, $12, $82 ; $E7BB
.byte $01, $12, $81, $01, $12, $81, $01, $12, $81, $01, $12, $81, $01, $12, $81, $01 ; $E7CB
.byte $12, $81, $01, $12, $84, $01, $13, $00, $01, $13, $81, $01, $13, $00, $01, $13 ; $E7DB
.byte $81, $01, $13, $00, $01, $13, $00, $01, $13, $00, $01, $13, $81, $01, $13, $fd ; $E7EB
.byte $00, $01, $13, $00, $01, $13, $00, $01, $13, $00, $01, $13, $01, $01, $13, $00 ; $E7FB
.byte $01, $13, $01, $01, $13, $00, $01, $13, $01, $01, $13, $01, $01, $13, $01, $01 ; $E80B
.byte $13, $02, $01, $13, $02, $01, $13, $02, $01, $13, $03, $01, $13, $03, $01, $13 ; $E81B
.byte $04, $00, $13, $04, $00, $13, $05, $00, $13, $05, $00, $13, $05, $00, $13, $05 ; $E82B
.byte $00, $13, $05, $00, $13, $05, $00, $13, $ff, $0e, $00, $04, $81, $16, $04, $81 ; $E83B
.byte $17, $04, $81, $16, $04, $81, $17, $04, $81, $16, $04, $81, $17, $04, $81, $16 ; $E84B
.byte $04, $81, $17, $04, $81, $16, $04, $81, $17, $04, $80, $16, $04, $80, $17, $04 ; $E85B
.byte $80, $16, $04, $80, $17, $04, $80, $16, $04, $80, $17, $04, $80, $16, $04, $80 ; $E86B
.byte $17, $04, $02, $16, $04, $02, $17, $04, $02, $16, $04, $02, $17, $04, $02, $16 ; $E87B
.byte $04, $02, $17, $04, $02, $16, $ff, $0f, $20, $14, $82, $14, $10, $00, $14, $14 ; $E88B
.byte $02, $14, $14, $02, $14, $ff, $0f, $20, $14, $82, $15, $10, $00, $15, $14, $02 ; $E89B
.byte $15, $14, $02, $15, $ff, $0f, $20, $04, $81, $16, $04, $81, $17, $04, $81, $16 ; $E8AB
.byte $04, $81, $17, $04, $81, $16, $04, $81, $17, $04, $81, $16, $04, $81, $17, $04 ; $E8BB
.byte $81, $16, $04, $81, $17, $04, $80, $16, $04, $80, $17, $04, $80, $16, $fc, $01 ; $E8CB
.byte $02, $00, $00, $00, $00, $00, $4f, $00, $00, $00, $00, $00, $00, $00, $01, $00 ; $E8DB
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $02, $00, $00 ; $E8EB
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $f9 ; $E8FB
.byte $fe, $fb, $fe, $ff, $fe, $ff, $fa, $fb, $fa, $f9, $fa, $00, $00, $00, $00, $fa ; $E90B
.byte $fd, $fb, $fd, $fb, $fd, $fc, $fd, $fc, $fb, $fb, $fb, $fb, $fb, $fa, $fb, $18 ; $E91B
.byte $18, $19, $1a, $1a, $1b, $1c, $1d, $1e, $1e, $1f, $1f, $20, $20, $21, $21, $22 ; $E92B
.byte $22, $22, $22, $23, $23, $23, $23, $23, $23, $00, $00, $00, $01, $01, $01, $02 ; $E93B
.byte $02, $02, $02, $03, $03, $03, $03, $04, $04, $04, $04, $04, $05, $05, $05, $05 ; $E94B
.byte $05, $05, $05, $05, $05, $05, $05, $05, $05, $05, $05, $05, $05, $00, $00, $c0 ; $E95B
.byte $15, $1e, $2c, $01, $00, $c0, $0a, $1e, $30, $03, $00, $d0, $10, $1e, $25, $04 ; $E96B
.byte $00, $c0, $00, $1c, $30, $06, $00, $c0, $0f, $1c, $30, $08, $00, $c0, $f6, $1c ; $E97B
.byte $30, $09, $00, $c0, $0c, $1c, $30, $0a, $00, $c0, $f4, $1c, $30, $0c, $00, $c0 ; $E98B
.byte $f4, $1e, $2d, $0e, $00, $c0, $08, $1c, $30, $0a, $00, $c0, $00, $1d, $30, $11 ; $E99B
.byte $00, $b8, $ee, $20, $33, $13, $00, $c8, $f0, $1c, $2a, $04, $80, $c8, $f7, $1c ; $E9AB
.byte $2d, $0a, $80, $c8, $0b, $1c, $2d, $0f, $80, $c6, $f3, $21, $26, $14, $14, $10 ; $E9BB
.byte $10, $10, $08, $04, $00, $18, $14, $14, $10, $0c, $08, $04, $00, $1c, $18, $18 ; $E9CB
.byte $14, $10, $0c, $08, $04, $20, $1c, $18, $14, $10, $0c, $08, $04, $24, $20, $1c ; $E9DB
.byte $18, $14, $0c, $08, $04, $28, $24, $20, $1c, $14, $10, $0c, $08, $2c, $28, $24 ; $E9EB
.byte $20, $18, $10, $0c, $08, $01, $01, $01, $01, $02, $01, $01, $01, $02, $01, $02 ; $E9FB
.byte $01, $02, $02, $02, $01, $02, $02, $02, $02, $03, $02, $03, $02, $03, $03, $03 ; $EA0B
.byte $03, $04, $03, $04, $03, $04, $04, $04, $04, $05, $05, $05, $05, $06, $06, $06 ; $EA1B
.byte $06, $07, $07, $07, $07, $ed, $40, $ed, $40, $ed, $c0, $ed, $80, $ed, $00, $ed ; $EA2B
.byte $00, $ed, $00, $ed, $00, $ee, $40, $ee, $40, $ee, $40, $ee, $40, $ee, $00, $ee ; $EA3B
.byte $00, $ee, $00, $ee, $00, $06, $05, $04, $03, $03, $02, $03, $03, $02, $02, $02 ; $EA4B
.byte $02, $02, $01, $01, $02, $01, $01, $01, $01, $01, $01, $01, $00, $01, $01, $01 ; $EA5B
.byte $01, $00, $01, $01, $01, $00, $01, $01, $00, $01, $00, $01, $00, $bb, $01, $00 ; $EA6B
.byte $01, $00, $bb, $01, $00, $01, $00, $bb, $01, $00, $01, $bb, $00, $01, $bb, $00 ; $EA7B
.byte $00, $bb, $00, $aa, $02, $02, $01, $02, $02, $01, $01, $01, $01, $01, $00, $01 ; $EA8B
.byte $00, $01, $00, $01, $00, $01, $bb, $00, $00, $01, $bb, $00, $00, $01, $bb, $00 ; $EA9B
.byte $00, $bb, $01, $00, $00, $bb, $01, $00, $bb, $00, $00, $bb, $bb, $bb, $bb, $bb ; $EAAB
.byte $bb, $bb, $bb, $bb, $bb, $bb, $aa, $01, $01, $00, $01, $01, $01, $00, $01, $00 ; $EABB
.byte $01, $00, $00, $01, $00, $00, $00, $00, $01, $00, $00, $00, $00, $00, $01, $00 ; $EACB
.byte $00, $00, $00, $00, $00, $01, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00 ; $EADB
.byte $00, $00, $00, $00, $00, $00, $00, $00, $06, $00, $ff, $02, $05, $02, $ff, $08 ; $EAEB
.byte $04, $06, $ff, $0e, $04, $07, $ff, $12, $05, $08, $ff, $14, $04, $0a, $ff, $ff ; $EAFB
.byte $00, $00, $02, $ff, $00, $00, $04, $ff, $00, $00, $06, $ff, $00, $00, $0a, $ff ; $EB0B
.byte $00, $00, $10, $ff, $00, $00, $14, $02, $04, $06, $0a, $0c, $0e, $01, $03, $05 ; $EB1B
.byte $07, $09, $0b, $0d, $0f    ; $EB2B

_data_eb30_indexed:
.byte $4a                        ; $EB30

_data_eb31_indexed:
.byte $eb, $5d, $eb, $70, $eb, $7d, $eb, $86, $eb, $8f, $eb, $92, $eb, $92, $eb, $92 ; $EB31
.byte $eb, $95, $eb, $b6, $eb, $c9, $eb, $dc, $eb, $f4, $f4, $f4, $fc, $f4, $04, $fc ; $EB41
.byte $f4, $fc, $fc, $fc, $04, $04, $f4, $04, $fc, $04, $04, $aa, $f7, $f5, $f7, $fd ; $EB51
.byte $f7, $03, $ff, $f5, $ff, $fd, $ff, $03, $01, $f5, $01, $fd, $01, $03, $aa, $f9 ; $EB61
.byte $f7, $f9, $ff, $f9, $01, $ff, $f7, $ff, $ff, $ff, $01, $aa, $fa, $f8, $fa, $00 ; $EB71
.byte $fe, $f8, $fe, $00, $aa, $fa, $fa, $fa, $fe, $fe, $fa, $fe, $fe, $aa, $fc, $fc ; $EB81
.byte $aa, $fc, $fc, $aa, $f0, $f0, $f0, $f8, $f0, $00, $f0, $08, $f8, $f0, $f8, $f8 ; $EB91
.byte $f8, $00, $f8, $08, $00, $f0, $00, $f8, $00, $00, $00, $08, $08, $f0, $08, $f8 ; $EBA1
.byte $08, $00, $08, $08, $aa, $f4, $f5, $f4, $fd, $f4, $03, $fc, $f5, $fc, $fd, $fc ; $EBB1
.byte $03, $04, $f5, $04, $fd, $04, $03, $aa, $f5, $f7, $f5, $ff, $f5, $01, $fd, $f7 ; $EBC1
.byte $fd, $ff, $fd, $01, $03, $f7, $03, $ff, $03, $01, $aa, $f6, $f8, $f6, $00, $fe ; $EBD1
.byte $f8, $fe, $00, $02, $f8, $02, $00, $aa, $01, $01, $02, $03, $00, $50, $00, $00 ; $EBE1
.byte $00, $02, $03, $01, $04, $06, $02, $05, $07, $05, $08, $10, $15, $16, $20, $24 ; $EBF1
.byte $30                        ; $EC01

_data_ec02_indexed:
.byte $06, $06, $06, $06, $06, $06, $06, $06, $06, $06, $07, $07, $08, $08, $09, $09 ; $EC02
.byte $09, $09, $09, $0a, $ff    ; $EC12

_data_ec17_indexed:
.byte $00, $08, $10, $18, $18, $20, $20, $28 ; $EC17

_data_ec1f_indexed:
.byte $28, $01, $80, $00, $00, $aa, $01, $40, $02, $10, $03, $08, $02, $10, $03, $08 ; $EC1F
.byte $02, $10, $03, $08, $02, $10, $03, $08, $00 ; $EC2F

_data_ec38_indexed:
.byte $00                        ; $EC38

_data_ec39_indexed:
.byte $aa, $4a, $ec, $70, $ec, $82, $ec, $8b, $ec, $b1, $ec, $e6, $ec, $07, $ed, $3c ; $EC39
.byte $ed, $cd, $24, $57, $ff, $13, $13, $13, $13, $13, $1a, $d8, $1b, $18, $1e, $17 ; $EC49
.byte $0d, $21, $d8, $b7, $b7, $b7, $b7, $b7, $21, $d8, $b7, $b7, $b7, $b7, $b7, $21 ; $EC59
.byte $23, $fc, $fc, $fc, $fc, $fc, $fd, $ee, $10, $35, $b7, $b7, $b7, $b7, $b7, $b7 ; $EC69
.byte $10, $18, $fe, $b7, $b7, $b7, $b7, $b7, $b7, $ef, $04, $23, $b7, $b7, $b7, $b7 ; $EC79
.byte $b7, $b7, $cd, $24, $57, $ff, $13, $13, $13, $13, $13, $1a, $d8, $b7, $b7, $b7 ; $EC89
.byte $b7, $b7, $21, $d8, $10, $18, $18, $0d, $fe, $21, $d8, $b7, $b7, $b7, $b7, $b7 ; $EC99
.byte $21, $23, $fc, $fc, $fc, $fc, $fc, $fd, $cc, $33, $5a, $ff, $13, $13, $13, $13 ; $ECA9
.byte $13, $13, $13, $13, $1a, $d8, $19, $0e, $1b, $0f, $0e, $0c, $1d, $fe, $21, $d8 ; $ECB9
.byte $b7, $b7, $b7, $b7, $b7, $b7, $b7, $b7, $21, $d8, $b7, $b7, $b7, $00, $00, $00 ; $ECC9
.byte $b7, $b7, $21, $23, $fc, $fc, $fc, $fc, $fc, $fc, $fc, $fc, $fd, $ec, $1f, $3a ; $ECD9
.byte $ff, $13, $13, $13, $13, $13, $13, $13, $13, $1a, $d8, $0f, $15, $22, $b7, $0a ; $ECE9
.byte $20, $0a, $22, $21, $23, $fc, $fc, $fc, $fc, $fc, $fc, $fc, $fc, $fd, $cc, $33 ; $ECF9
.byte $5a, $24, $ff, $13, $13, $13, $13, $13, $1a, $24, $24, $24, $d8, $b7, $b7, $b7 ; $ED09
.byte $b7, $b7, $21, $24, $24, $24, $d8, $19, $0a, $1e, $1c, $0e, $21, $24, $24, $24 ; $ED19
.byte $d8, $b7, $b7, $b7, $b7, $b7, $21, $24, $24, $24, $23, $fc, $fc, $fc, $fc, $fc ; $ED29
.byte $fd, $24, $24, $ab, $38, $5b, $ff, $13, $13, $13, $13, $13, $13, $13, $13, $13 ; $ED39
.byte $1a, $d8, $b7, $b7, $b7, $b7, $b7, $b7, $b7, $b7, $b7, $21, $d8, $10, $0a, $16 ; $ED49
.byte $0e, $b7, $18, $1f, $0e, $1b, $21, $d8, $b7, $b7, $b7, $b7, $b7, $b7, $b7, $b7 ; $ED59
.byte $b7, $21, $23, $fc, $fc, $fc, $fc, $fc, $fc, $fc, $fc, $fc, $fd, $9c, $18, $14 ; $ED69
.byte $10, $01, $10, $02, $20, $03, $08, $02, $08, $01, $18, $00, $10, $0e, $08, $0d ; $ED79
.byte $20, $0c, $08, $0d, $08, $0c, $b0, $0b, $80, $03, $40, $02, $ff, $08, $00, $88 ; $ED89
.byte $10, $12, $28, $0f, $08, $00, $10, $01, $08, $02, $48, $03, $20, $04, $70, $0c ; $ED99
.byte $30, $0d, $30, $0e, $ff, $08, $00, $90, $20, $12, $60, $0d, $90, $03, $78, $02 ; $EDA9
.byte $ff, $08, $00, $78, $20, $13, $40, $0f, $10, $0e, $20, $0d, $18, $0b, $20, $0a ; $EDB9
.byte $50, $06, $28, $04, $38, $03, $78, $02, $ff, $08, $00, $80, $10, $12, $20, $0d ; $EDC9
.byte $08, $0e, $08, $0f, $20, $03, $10, $02, $08, $0e, $20, $0d, $08, $0e, $08, $0f ; $EDD9
.byte $08, $01, $08, $03, $30, $04, $40, $05, $80, $0b, $30, $0e, $60, $0f, $ff, $08 ; $EDE9
.byte $00, $b8, $08, $14, $10, $04, $08, $03, $08, $02, $08, $01, $08, $00, $08, $0e ; $EDF9
.byte $08, $0d, $08, $0c, $50, $0b, $60, $0c, $10, $0d, $40, $02, $70, $01, $ff, $08 ; $EE09
.byte $00, $70, $18, $12, $40, $0d, $10, $0f, $10, $02, $30, $04, $20, $05, $40, $03 ; $EE19
.byte $20, $04, $20, $03, $18, $02, $20, $01, $ff, $08, $00, $b0, $10, $14, $28, $02 ; $EE29
.byte $18, $01, $30, $00, $10, $0f, $50, $0b, $60, $0c, $20, $0b, $70, $04, $80, $05 ; $EE39
.byte $ff, $08, $00, $5a, $08, $13, $10, $02, $20, $0d, $10, $03, $10, $04, $10, $03 ; $EE49
.byte $58, $0d, $28, $03, $48, $04, $10, $03, $48, $0d, $80, $03, $ff, $08, $00, $46 ; $EE59
.byte $20, $12, $20, $0e, $38, $04, $18, $02, $10, $04, $20, $06, $08, $05, $18, $04 ; $EE69
.byte $18, $02, $40, $01, $40, $00, $ff, $08, $00, $d0, $2a, $14, $30, $0c, $20, $0b ; $EE79
.byte $20, $0c, $38, $0b, $48, $0c, $40, $02, $30, $0c, $ff, $08, $00, $70, $10, $12 ; $EE89
.byte $10, $0d, $20, $0e, $10, $0f, $10, $00, $30, $02, $10, $04, $10, $05, $60, $05 ; $EE99
.byte $20, $0b, $40, $0c, $08, $0d, $70, $03, $30, $02, $18, $00, $ff, $08, $00, $c0 ; $EEA9
.byte $18, $12, $10, $0d, $40, $0b, $38, $0d, $08, $0b, $08, $0c, $10, $0d, $70, $03 ; $EEB9
.byte $40, $02, $40, $01, $ff, $08, $00, $90, $18, $14, $20, $02, $28, $0d, $20, $0b ; $EEC9
.byte $20, $0b, $08, $0c, $10, $0d, $20, $03, $20, $05, $20, $04, $10, $02, $10, $03 ; $EED9
.byte $70, $0d, $40, $04, $50, $03, $20, $02, $ff, $08, $00, $58, $1c, $14, $24, $02 ; $EEE9
.byte $08, $00, $48, $0c, $38, $0e, $50, $07, $30, $05, $30, $04, $28, $0d, $20, $02 ; $EEF9
.byte $80, $01, $ff, $08, $00, $50, $20, $12, $20, $0d, $40, $03, $30, $0c, $40, $03 ; $EF09
.byte $30, $04, $38, $05, $08, $0b, $28, $0c, $08, $0d, $40, $03, $4a, $04, $ff, $08 ; $EF19
.byte $00, $40, $e0, $01, $80, $e0, $02, $d0, $e0, $0e, $38, $e0, $01, $a0, $e0, $0d ; $EF29
.byte $30, $e0, $03, $b0, $e0, $0e, $90, $e0, $0f, $40, $e0, $03, $80, $e0, $03, $c8 ; $EF39
.byte $e0, $0e, $50, $e0, $0f, $b8, $e0, $0d, $20, $e0, $03, $48, $e0, $01, $b8, $e0 ; $EF49
.byte $0f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EF59
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EF69
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EF79
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EF89
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EF99
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EFA9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EFB9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EFC9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EFD9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EFE9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $EFF9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F009
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F019
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F029
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F039
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F049
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F059
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F069
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F079
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F089
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F099
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F0A9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F0B9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F0C9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F0D9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F0E9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F0F9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F109
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F119
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F129
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F139
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F149
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F159
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F169
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F179
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F189
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F199
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F1A9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F1B9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F1C9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F1D9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F1E9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F1F9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F209
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F219
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F229
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F239
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F249
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F259
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F269
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F279
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F289
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F299
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F2A9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F2B9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F2C9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F2D9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F2E9
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $F2F9

_data_f300_indexed:
.byte $07                        ; $F300

_data_f301_indexed:
.byte $f0, $00, $00, $00, $d4, $00, $c8, $00, $bd, $00, $b2, $00, $a8, $00, $9f, $00 ; $F301
.byte $96, $00, $8d, $00, $85, $00, $7e, $00, $70, $01, $ab, $01, $93, $01, $7c, $01 ; $F311
.byte $67, $01, $52, $01, $3f, $01, $2d, $01, $1c, $01, $0c, $00, $fd, $00, $ee, $00 ; $F321
.byte $e1, $03, $57, $02, $f9, $02, $cf, $02, $a6, $02, $80, $02, $5c, $02, $3a, $02 ; $F331
.byte $1a, $01, $fc, $01, $df, $01, $c4, $00, $69, $00, $63, $00, $53, $00, $4a ; $F341

_data_f350_indexed:
.byte $03, $06, $0c, $18, $30, $12, $24, $04, $08, $10, $20, $40, $18, $30 ; $F350

_func_f35e:
  lda #$00                       ; $F35E  A9 00
  beq _label_f36c                ; $F360  F0 0A

_func_f362:
  lda #$08                       ; $F362  A9 08
  bne _label_f36c                ; $F364  D0 06

_func_f366:
  lda #$0C                       ; $F366  A9 0C
  bne _label_f36c                ; $F368  D0 02

_func_f36a:
  lda #$04                       ; $F36A  A9 04

_label_f36c:
  sta _var_00f4_indexed          ; $F36C  85 F4
  lda #$40                       ; $F36E  A9 40
  sta $F5                        ; $F370  85 F5
  stx _var_00f6_indexed          ; $F372  86 F6
  sty $F7                        ; $F374  84 F7
  ldy #$00                       ; $F376  A0 00

_label_f378:
  lda (_var_00f6_indexed),Y      ; $F378  B1 F6
  sta (_var_00f4_indexed),Y      ; $F37A  91 F4
  iny                            ; $F37C  C8
  tya                            ; $F37D  98
  cmp #$04                       ; $F37E  C9 04
  bne _label_f378                ; $F380  D0 F6
  rts                            ; $F382  60

_func_f383:
  sta _var_00e6                  ; $F383  85 E6
  lda a:_data_f846_indexed,Y     ; $F385  B9 46 F8
  tay                            ; $F388  A8
  lda a:_data_f846_indexed,Y     ; $F389  B9 46 F8
  sta _var_00e5                  ; $F38C  85 E5
  lda a:_data_f847_indexed,Y     ; $F38E  B9 47 F8
  sta _var_00f8_indexed          ; $F391  85 F8
  lda a:_data_f847_indexed+1,Y   ; $F393  B9 48 F8
  sta _var_00f9_indexed          ; $F396  85 F9
  lda a:_data_f849_indexed,Y     ; $F398  B9 49 F8
  sta _var_00fa_indexed          ; $F39B  85 FA
  lda a:_data_f849_indexed+1,Y   ; $F39D  B9 4A F8
  sta _var_00fb                  ; $F3A0  85 FB
  lda a:_data_f84b_indexed,Y     ; $F3A2  B9 4B F8
  sta _var_00fc_indexed          ; $F3A5  85 FC
  lda a:_data_f84b_indexed+1,Y   ; $F3A7  B9 4C F8
  sta _var_00fd                  ; $F3AA  85 FD
  lda a:_data_f84d_indexed,Y     ; $F3AC  B9 4D F8
  sta _var_00fe_indexed          ; $F3AF  85 FE
  lda a:_data_f84d_indexed+1,Y   ; $F3B1  B9 4E F8
  sta _var_00ff                  ; $F3B4  85 FF
  lda #$01                       ; $F3B6  A9 01
  sta _var_00d8                  ; $F3B8  85 D8
  sta _var_00d9                  ; $F3BA  85 D9
  sta _var_00da                  ; $F3BC  85 DA
  sta _var_00db                  ; $F3BE  85 DB
  lda #$00                       ; $F3C0  A9 00
  sta _var_00f3                  ; $F3C2  85 F3
  sta _var_00d0_indexed          ; $F3C4  85 D0
  sta _var_00d1                  ; $F3C6  85 D1
  sta _var_00d2_indexed          ; $F3C8  85 D2
  sta _var_00d3                  ; $F3CA  85 D3
  sta APU_DMC_RAW                ; $F3CC  8D 11 40
  rts                            ; $F3CF  60

_func_f3d0:
  lda #$7F                       ; $F3D0  A9 7F
  sta APU_PL1_SWEEP              ; $F3D2  8D 01 40
  sta APU_PL2_SWEEP              ; $F3D5  8D 05 40
  stx $E9                        ; $F3D8  86 E9
  sty _var_00ea                  ; $F3DA  84 EA
  rts                            ; $F3DC  60

.byte $13, $7f, $3e, $f0         ; $F3DD

_data_f3e1_indexed:
.byte $4f, $53, $58, $5e, $63, $69, $70, $76, $7e, $85, $8d, $90, $92, $93, $92, $d5 ; $F3E1
.byte $40, $c0, $b2, $df, $ff, $80, $02, $7f, $0f, $08, $00, $7f, $03, $08, $ff, $10 ; $F3F1
.byte $00, $18, $10, $01, $18, $00, $01, $88, $06, $02, $40, $05, $02, $c0 ; $F401

_label_f40f:
  lda _var_00f9_indexed          ; $F40F  A5 F9
  beq _label_f451                ; $F411  F0 3E
  dec _var_00d8                  ; $F413  C6 D8
  bne _label_f451                ; $F415  D0 3A
  ldx #$00                       ; $F417  A2 00
  lda #$23                       ; $F419  A9 23
  sta a:_var_0612                ; $F41B  8D 12 06
  lda #$2E                       ; $F41E  A9 2E
  sta a:_var_0610                ; $F420  8D 10 06
  ldy _var_00d0_indexed          ; $F423  A4 D0
  inc _var_00d0_indexed          ; $F425  E6 D0
  lda (_var_00f8_indexed),Y      ; $F427  B1 F8
  beq _label_f443                ; $F429  F0 18
  jmp _label_f51c                ; $F42B  4C 1C F5

.byte $98, $10, $09, $20, $44, $f5, $a4, $d0, $e6, $d0, $b1, $f8, $20, $50, $f5, $d0 ; $F42E
.byte $09, $a0, $10, $d0, $07    ; $F43E

_label_f443:
  lda #$00                       ; $F443  A9 00
  jmp _label_f68c                ; $F445  4C 8C F6

.byte $a4, $e9, $8c, $00, $40, $a5, $dc, $85, $d8 ; $F448

_label_f451:
  lda _var_00fb                  ; $F451  A5 FB
  beq _label_f47e                ; $F453  F0 29
  dec _var_00d9                  ; $F455  C6 D9
  bne _label_f47e                ; $F457  D0 25
  ldx #$01                       ; $F459  A2 01
  ldy _var_00d1                  ; $F45B  A4 D1
  inc _var_00d1                  ; $F45D  E6 D1
  lda (_var_00fa_indexed),Y      ; $F45F  B1 FA
  bpl _label_f46c                ; $F461  10 09
  jsr _func_f544                 ; $F463  20 44 F5
  ldy _var_00d1                  ; $F466  A4 D1
  inc _var_00d1                  ; $F468  E6 D1
  lda (_var_00fa_indexed),Y      ; $F46A  B1 FA

_label_f46c:
  jsr _func_f564                 ; $F46C  20 64 F5
  bne _label_f475                ; $F46F  D0 04
  ldy #$10                       ; $F471  A0 10
  bne _label_f477                ; $F473  D0 02

_label_f475:
  ldy _var_00ea                  ; $F475  A4 EA

_label_f477:
  sty APU_PL2_VOL                ; $F477  8C 04 40
  lda $DD                        ; $F47A  A5 DD
  sta _var_00d9                  ; $F47C  85 D9

_label_f47e:
  lda _var_00fd                  ; $F47E  A5 FD
  beq _label_f4d1                ; $F480  F0 4F
  dec _var_00da                  ; $F482  C6 DA
  bne _label_f4d1                ; $F484  D0 4B
  ldx #$02                       ; $F486  A2 02
  lda #$9B                       ; $F488  A9 9B
  sta a:_var_0610                ; $F48A  8D 10 06
  lda #$92                       ; $F48D  A9 92
  sta a:_var_0612                ; $F48F  8D 12 06
  ldy _var_00d2_indexed          ; $F492  A4 D2
  inc _var_00d2_indexed          ; $F494  E6 D2
  lda (_var_00fc_indexed),Y      ; $F496  B1 FC
  jmp _label_f51c                ; $F498  4C 1C F5

.byte $98, $10, $21, $20, $44, $f5, $a4, $e4, $f0, $04, $a9, $ff, $d0, $0b, $18, $69 ; $F49B
.byte $fe, $0a, $0a, $c9, $3c, $90, $02, $a9, $3c, $8d, $08, $40, $85, $e7, $a4, $d2 ; $F4AB
.byte $e6, $d2, $b1, $fc, $20, $68, $f5, $d0, $04, $a0, $00, $f0, $02, $a4, $e7, $8c ; $F4BB
.byte $08, $40, $a5, $de, $85, $da ; $F4CB

_label_f4d1:
  lda _var_00ff                  ; $F4D1  A5 FF
  beq _label_f501                ; $F4D3  F0 2C
  dec _var_00db                  ; $F4D5  C6 DB
  bne _label_f501                ; $F4D7  D0 28
  ldx #$03                       ; $F4D9  A2 03
  lda #$EE                       ; $F4DB  A9 EE
  sta a:_var_0610                ; $F4DD  8D 10 06
  lda #$E5                       ; $F4E0  A9 E5
  sta a:_var_0612                ; $F4E2  8D 12 06
  ldy _var_00d3                  ; $F4E5  A4 D3
  inc _var_00d3                  ; $F4E7  E6 D3
  lda (_var_00fe_indexed),Y      ; $F4E9  B1 FE
  jmp _label_f51c                ; $F4EB  4C 1C F5

.byte $98, $10, $09, $20, $44, $f5, $a4, $d3, $e6, $d3, $b1, $fe, $20, $02, $f5, $a5 ; $F4EE
.byte $df, $85, $db              ; $F4FE

_label_f501:
  rts                            ; $F501  60

.byte $a8, $a5, $f3, $c9, $02, $f0, $12, $b9, $00, $f4, $8d, $0c, $40, $b9, $01, $f4 ; $F502
.byte $8d, $0e, $40, $b9, $02, $f4, $8d, $0f, $40, $60 ; $F512

_label_f51c:
  tay                            ; $F51C  A8
  cmp #$FF                       ; $F51D  C9 FF
  beq _label_f52a                ; $F51F  F0 09
  and #$C0                       ; $F521  29 C0
  cmp #$C0                       ; $F523  C9 C0
  beq _label_f536                ; $F525  F0 0F
  jmp (_var_0610)                ; $F527  6C 10 06  jump engine detected

_label_f52a:
  lda _var_00e0_indexed,X        ; $F52A  B5 E0
  beq _label_f541                ; $F52C  F0 13
  dec _var_00e0_indexed,X        ; $F52E  D6 E0
  lda _var_00d4_indexed,X        ; $F530  B5 D4
  sta _var_00d0_indexed,X        ; $F532  95 D0
  bne _label_f541                ; $F534  D0 0B

_label_f536:
  tya                            ; $F536  98
  and #$3F                       ; $F537  29 3F
  sta _var_00e0_indexed,X        ; $F539  95 E0
  dec _var_00e0_indexed,X        ; $F53B  D6 E0
  lda _var_00d0_indexed,X        ; $F53D  B5 D0
  sta _var_00d4_indexed,X        ; $F53F  95 D4

_label_f541:
  jmp (_var_0612)                ; $F541  6C 12 06  jump engine detected

_func_f544:
  and #$07                       ; $F544  29 07
  clc                            ; $F546  18
  adc _var_00e5                  ; $F547  65 E5
  tay                            ; $F549  A8
  lda a:_data_f350_indexed,Y     ; $F54A  B9 50 F3
  sta _var_00dc_indexed,X        ; $F54D  95 DC
  rts                            ; $F54F  60

.byte $a2, $00                   ; $F550

_label_f552:
  tay                            ; $F552  A8
  lda a:_data_f301_indexed,Y     ; $F553  B9 01 F3
  beq _label_f563                ; $F556  F0 0B
  sta APU_PL1_LO,X               ; $F558  9D 02 40
  lda a:_data_f300_indexed,Y     ; $F55B  B9 00 F3
  ora #$08                       ; $F55E  09 08
  sta APU_PL1_HI,X               ; $F560  9D 03 40

_label_f563:
  rts                            ; $F563  60

_func_f564:
  ldx #$04                       ; $F564  A2 04
  bne _label_f552                ; $F566  D0 EA
  ldx #$08                       ; $F568  A2 08
  bne _label_f552                ; $F56A  D0 E6

_func_f56c:
  lda #$C0                       ; $F56C  A9 C0
  sta APU_FRAME                  ; $F56E  8D 17 40
  jsr _func_f6cf                 ; $F571  20 CF F6
  jsr _func_f621                 ; $F574  20 21 F6
  jsr _func_f7cc                 ; $F577  20 CC F7
  jsr _func_f591                 ; $F57A  20 91 F5
  lda #$00                       ; $F57D  A9 00
  beq _label_f58a                ; $F57F  F0 09

_func_f581:
  lda #$F4                       ; $F581  A9 F4
  sta a:$0613                    ; $F583  8D 13 06
  sta a:$0611                    ; $F586  8D 11 06
  rts                            ; $F589  60

_label_f58a:
  sta _var_00f0                  ; $F58A  85 F0
  sta _var_00f1                  ; $F58C  85 F1
  sta _var_00f2                  ; $F58E  85 F2
  rts                            ; $F590  60

_func_f591:
  lda _var_00f2                  ; $F591  A5 F2
  lsr a                          ; $F593  4A
  bcs _label_f5a2                ; $F594  B0 0C
  lsr a                          ; $F596  4A
  bcs _label_f59a                ; $F597  B0 01
  rts                            ; $F599  60

_label_f59a:
  lda #$20                       ; $F59A  A9 20
  ldx #$F4                       ; $F59C  A2 F4
  ldy #$0F                       ; $F59E  A0 0F
  bne _label_f5a8                ; $F5A0  D0 06

_label_f5a2:
  lda #$20                       ; $F5A2  A9 20
  ldx #$EC                       ; $F5A4  A2 EC
  ldy #$0E                       ; $F5A6  A0 0E

_label_f5a8:
  sta APU_DMC_LEN                ; $F5A8  8D 13 40
  stx APU_DMC_START              ; $F5AB  8E 12 40
  sty APU_DMC_FREQ               ; $F5AE  8C 10 40
  lda #$1F                       ; $F5B1  A9 1F
  sta APU_SND_CHN                ; $F5B3  8D 15 40
  rts                            ; $F5B6  60

.byte $9f, $7f, $60, $00, $9f, $7f, $61, $00 ; $F5B7

_label_f5bf:
  ldx #$DD                       ; $F5BF  A2 DD
  ldy #$F3                       ; $F5C1  A0 F3
  jsr _func_f362                 ; $F5C3  20 62 F3
  lda #$00                       ; $F5C6  A9 00
  sta _var_00eb                  ; $F5C8  85 EB
  sta _var_00ed                  ; $F5CA  85 ED
  sta _var_00ee                  ; $F5CC  85 EE
  lda #$06                       ; $F5CE  A9 06
  sta _var_00ef                  ; $F5D0  85 EF
  lda #$3E                       ; $F5D2  A9 3E
  sta _var_00ec                  ; $F5D4  85 EC
  lda #$40                       ; $F5D6  A9 40
  sta _var_00f3                  ; $F5D8  85 F3

_label_f5da:
  rts                            ; $F5DA  60

_label_f5db:
  inc _var_00ee                  ; $F5DB  E6 EE
  lda _var_00ee                  ; $F5DD  A5 EE
  cmp #$01                       ; $F5DF  C9 01
  bne _label_f5da                ; $F5E1  D0 F7
  lda #$00                       ; $F5E3  A9 00
  sta _var_00ee                  ; $F5E5  85 EE
  inc _var_00eb                  ; $F5E7  E6 EB
  lda _var_00eb                  ; $F5E9  A5 EB
  cmp _var_00ef                  ; $F5EB  C5 EF
  beq _label_f5fb                ; $F5ED  F0 0C
  dec _var_00ec                  ; $F5EF  C6 EC
  dec _var_00ec                  ; $F5F1  C6 EC
  dec _var_00ec                  ; $F5F3  C6 EC
  lda _var_00ec                  ; $F5F5  A5 EC
  sta APU_TRI_LO                 ; $F5F7  8D 0A 40
  rts                            ; $F5FA  60

_label_f5fb:
  lda _var_00ef                  ; $F5FB  A5 EF
  clc                            ; $F5FD  18
  adc #$06                       ; $F5FE  69 06
  sta _var_00ef                  ; $F600  85 EF
  ldy _var_00ed                  ; $F602  A4 ED
  lda a:_data_f3e1_indexed,Y     ; $F604  B9 E1 F3
  sta APU_TRI_LO                 ; $F607  8D 0A 40
  sta _var_00ec                  ; $F60A  85 EC
  lda #$F0                       ; $F60C  A9 F0
  sta APU_TRI_HI                 ; $F60E  8D 0B 40
  inc _var_00ed                  ; $F611  E6 ED
  lda _var_00ed                  ; $F613  A5 ED
  cmp #$0E                       ; $F615  C9 0E
  bne _label_f5da                ; $F617  D0 C1
  lda #$00                       ; $F619  A9 00
  sta APU_TRI_LINEAR             ; $F61B  8D 08 40
  sta _var_00f3                  ; $F61E  85 F3
  rts                            ; $F620  60

_func_f621:
  lda _var_00f0                  ; $F621  A5 F0
  asl a                          ; $F623  0A
  bcs _label_f669                ; $F624  B0 43
  asl a                          ; $F626  0A
  bcs _label_f5bf                ; $F627  B0 96
  asl a                          ; $F629  0A
  bcs _label_f641                ; $F62A  B0 15
  asl a                          ; $F62C  0A
  bcs _label_f639                ; $F62D  B0 0A
  lda _var_00f3                  ; $F62F  A5 F3
  asl a                          ; $F631  0A
  asl a                          ; $F632  0A
  bcs _label_f5db                ; $F633  B0 A6
  asl a                          ; $F635  0A
  bcs _label_f655                ; $F636  B0 1D
  rts                            ; $F638  60

_label_f639:
  ldx #$EF                       ; $F639  A2 EF
  ldy #$F3                       ; $F63B  A0 F3
  jsr _func_f35e                 ; $F63D  20 5E F3
  rts                            ; $F640  60

_label_f641:
  ldx #$F3                       ; $F641  A2 F3
  ldy #$F3                       ; $F643  A0 F3
  jsr _func_f36a                 ; $F645  20 6A F3
  lda _var_00f3                  ; $F648  A5 F3
  ora #$20                       ; $F64A  09 20
  sta _var_00f3                  ; $F64C  85 F3
  lda #$00                       ; $F64E  A9 00
  sta _var_00ef                  ; $F650  85 EF
  sta _var_00ee                  ; $F652  85 EE

_label_f654:
  rts                            ; $F654  60

_label_f655:
  inc _var_00ee                  ; $F655  E6 EE
  lda _var_00ee                  ; $F657  A5 EE
  cmp #$02                       ; $F659  C9 02
  bne _label_f654                ; $F65B  D0 F7
  lda #$00                       ; $F65D  A9 00
  sta _var_00ee                  ; $F65F  85 EE
  inc _var_00ef                  ; $F661  E6 EF
  lda _var_00ef                  ; $F663  A5 EF
  cmp #$A0                       ; $F665  C9 A0
  bne _label_f654                ; $F667  D0 EB

_label_f669:
  lda #$10                       ; $F669  A9 10
  sta APU_PL2_VOL                ; $F66B  8D 04 40
  lda _var_00f3                  ; $F66E  A5 F3
  and #$DF                       ; $F670  29 DF
  sta _var_00f3                  ; $F672  85 F3
  rts                            ; $F674  60

_label_f675:
  ldx #$F7                       ; $F675  A2 F7
  ldy #$F3                       ; $F677  A0 F3
  jsr _func_f366                 ; $F679  20 66 F3
  lda #$10                       ; $F67C  A9 10
  sta APU_PL1_VOL                ; $F67E  8D 00 40
  lda _var_00f3                  ; $F681  A5 F3
  and #$F0                       ; $F683  29 F0
  sta _var_00f3                  ; $F685  85 F3
  rts                            ; $F687  60

_label_f688:
  lda #$00                       ; $F688  A9 00
  sta _var_00f3                  ; $F68A  85 F3

_label_f68c:
  sta APU_TRI_LINEAR             ; $F68C  8D 08 40
  sta APU_DMC_RAW                ; $F68F  8D 11 40
  sta _var_00e6                  ; $F692  85 E6
  sta _var_00e4                  ; $F694  85 E4
  lda #$10                       ; $F696  A9 10
  sta APU_PL1_VOL                ; $F698  8D 00 40
  sta APU_PL2_VOL                ; $F69B  8D 04 40
  sta APU_NOISE_VOL              ; $F69E  8D 0C 40
  rts                            ; $F6A1  60

_label_f6a2:
  ldx #$FB                       ; $F6A2  A2 FB
  ldy #$F3                       ; $F6A4  A0 F3
  jsr _func_f366                 ; $F6A6  20 66 F3
  lda #$00                       ; $F6A9  A9 00
  sta _var_00eb                  ; $F6AB  85 EB
  lda _var_00f3                  ; $F6AD  A5 F3
  ora #$08                       ; $F6AF  09 08
  sta _var_00f3                  ; $F6B1  85 F3

_label_f6b3:
  rts                            ; $F6B3  60

_label_f6b4:
  ldy _var_00eb                  ; $F6B4  A4 EB
  lda a:_data_f6cb_indexed,Y     ; $F6B6  B9 CB F6
  sta APU_NOISE_LO               ; $F6B9  8D 0E 40
  inc _var_00eb                  ; $F6BC  E6 EB
  lda _var_00eb                  ; $F6BE  A5 EB
  cmp #$04                       ; $F6C0  C9 04
  bne _label_f6b3                ; $F6C2  D0 EF
  lda _var_00f3                  ; $F6C4  A5 F3
  and #$FE                       ; $F6C6  29 FE
  sta _var_00f3                  ; $F6C8  85 F3
  rts                            ; $F6CA  60

_data_f6cb_indexed:
.byte $00, $02, $01, $00         ; $F6CB

_func_f6cf:
  lda _var_00f0                  ; $F6CF  A5 F0
  lsr a                          ; $F6D1  4A
  bcs _label_f688                ; $F6D2  B0 B4
  lsr a                          ; $F6D4  4A
  bcs _label_f6e8                ; $F6D5  B0 11
  lsr a                          ; $F6D7  4A
  bcs _label_f675                ; $F6D8  B0 9B
  lsr a                          ; $F6DA  4A
  bcs _label_f6a2                ; $F6DB  B0 C5
  lda _var_00f3                  ; $F6DD  A5 F3
  lsr a                          ; $F6DF  4A
  lsr a                          ; $F6E0  4A
  bcs _label_f703                ; $F6E1  B0 20
  lsr a                          ; $F6E3  4A
  lsr a                          ; $F6E4  4A
  bcs _label_f6b4                ; $F6E5  B0 CD
  rts                            ; $F6E7  60

_label_f6e8:
  ldx #$FF                       ; $F6E8  A2 FF
  ldy #$F6                       ; $F6EA  A0 F6
  jsr _func_f366                 ; $F6EC  20 66 F3
  lda #$00                       ; $F6EF  A9 00
  sta _var_00ec                  ; $F6F1  85 EC
  sta _var_00ed                  ; $F6F3  85 ED
  sta APU_DMC_RAW                ; $F6F5  8D 11 40
  lda _var_00f3                  ; $F6F8  A5 F3
  ora #$02                       ; $F6FA  09 02
  sta _var_00f3                  ; $F6FC  85 F3

_label_f6fe:
  rts                            ; $F6FE  60

.byte $3f, $7f, $0f, $08         ; $F6FF

_label_f703:
  inc _var_00ec                  ; $F703  E6 EC
  lda _var_00ec                  ; $F705  A5 EC
  cmp #$02                       ; $F707  C9 02
  bne _label_f6fe                ; $F709  D0 F3
  lda #$00                       ; $F70B  A9 00
  sta _var_00ec                  ; $F70D  85 EC
  ldy _var_00ed                  ; $F70F  A4 ED
  lda a:_data_f731_indexed,Y     ; $F711  B9 31 F7
  sta APU_NOISE_LO               ; $F714  8D 0E 40
  lda a:_data_f761_indexed,Y     ; $F717  B9 61 F7
  sta APU_NOISE_VOL              ; $F71A  8D 0C 40
  inc _var_00ed                  ; $F71D  E6 ED
  lda _var_00ed                  ; $F71F  A5 ED
  cmp #$30                       ; $F721  C9 30
  bne _label_f730                ; $F723  D0 0B
  lda #$10                       ; $F725  A9 10
  sta APU_NOISE_VOL              ; $F727  8D 0C 40
  lda _var_00f3                  ; $F72A  A5 F3
  and #$FD                       ; $F72C  29 FD
  sta _var_00f3                  ; $F72E  85 F3

_label_f730:
  rts                            ; $F730  60

_data_f731_indexed:
.byte $0e, $0b, $05, $05, $05, $05, $05, $05, $05, $05, $05, $05, $04, $04, $04, $04 ; $F731
.byte $04, $04, $03, $03, $03, $03, $03, $04, $03, $02, $02, $02, $02, $02, $02, $02 ; $F741
.byte $02, $01, $01, $01, $02, $02, $01, $01, $00, $00, $00, $00, $00, $00, $00, $00 ; $F751

_data_f761_indexed:
.byte $3f, $3f, $3f, $3f, $3f, $3f, $3d, $3c, $38, $38, $38, $37, $37, $37, $36, $36 ; $F761
.byte $34, $34, $34, $34, $34, $34, $34, $34, $33, $33, $33, $33, $33, $33, $33, $33 ; $F771
.byte $32, $32, $32, $32, $32, $32, $32, $32, $32, $32, $32, $32, $32, $32, $32, $32 ; $F781

_label_f791:
  ldx #$B7                       ; $F791  A2 B7
  ldy #$F5                       ; $F793  A0 F5
  jsr _func_f35e                 ; $F795  20 5E F3
  ldx #$BB                       ; $F798  A2 BB
  ldy #$F5                       ; $F79A  A0 F5

_label_f79c:
  jsr _func_f36a                 ; $F79C  20 6A F3
  rts                            ; $F79F  60

.byte $84, $93, $70, $e3, $84, $93, $72, $e3 ; $F7A0

_label_f7a8:
  lda #$00                       ; $F7A8  A9 00
  sta APU_PL1_VOL                ; $F7AA  8D 00 40
  ldx #$A0                       ; $F7AD  A2 A0
  ldy #$F7                       ; $F7AF  A0 F7
  jsr _func_f35e                 ; $F7B1  20 5E F3
  ldx #$A4                       ; $F7B4  A2 A4
  ldy #$F7                       ; $F7B6  A0 F7
  bne _label_f79c                ; $F7B8  D0 E2

_label_f7ba:
  ldy #$06                       ; $F7BA  A0 06
  lda #$80                       ; $F7BC  A9 80
  bne _label_f82f                ; $F7BE  D0 6F

_label_f7c0:
  ldy #$04                       ; $F7C0  A0 04
  lda #$04                       ; $F7C2  A9 04
  bne _label_f826                ; $F7C4  D0 60

_label_f7c6:
  ldy #$05                       ; $F7C6  A0 05
  lda #$08                       ; $F7C8  A9 08
  bne _label_f826                ; $F7CA  D0 5A

_func_f7cc:
  lda _var_00f1                  ; $F7CC  A5 F1
  lsr a                          ; $F7CE  4A
  bcs _label_f7fd                ; $F7CF  B0 2C
  lsr a                          ; $F7D1  4A
  bcs _label_f803                ; $F7D2  B0 2F
  lsr a                          ; $F7D4  4A
  bcs _label_f7c0                ; $F7D5  B0 E9
  lsr a                          ; $F7D7  4A
  bcs _label_f7c6                ; $F7D8  B0 EC
  lsr a                          ; $F7DA  4A
  bcs _label_f809                ; $F7DB  B0 2C
  lsr a                          ; $F7DD  4A
  bcs _label_f80f                ; $F7DE  B0 2F
  lsr a                          ; $F7E0  4A
  bcs _label_f815                ; $F7E1  B0 32
  lsr a                          ; $F7E3  4A
  bcs _label_f7ba                ; $F7E4  B0 D4
  lda _var_00f2                  ; $F7E6  A5 F2
  asl a                          ; $F7E8  0A
  bcs _label_f81b                ; $F7E9  B0 30
  asl a                          ; $F7EB  0A
  asl a                          ; $F7EC  0A
  bcs _label_f791                ; $F7ED  B0 A2
  asl a                          ; $F7EF  0A
  bcs _label_f840                ; $F7F0  B0 4E
  asl a                          ; $F7F2  0A
  bcs _label_f7a8                ; $F7F3  B0 B3
  lda _var_00e6                  ; $F7F5  A5 E6
  bne _label_f7fa                ; $F7F7  D0 01
  rts                            ; $F7F9  60

_label_f7fa:
  jmp _label_f40f                ; $F7FA  4C 0F F4

_label_f7fd:
  ldy #$00                       ; $F7FD  A0 00
  lda #$01                       ; $F7FF  A9 01
  bne _label_f826                ; $F801  D0 23

_label_f803:
  ldy #$03                       ; $F803  A0 03
  lda #$02                       ; $F805  A9 02
  bne _label_f82f                ; $F807  D0 26

_label_f809:
  ldy #$01                       ; $F809  A0 01
  lda #$10                       ; $F80B  A9 10
  bne _label_f826                ; $F80D  D0 17

_label_f80f:
  ldy #$07                       ; $F80F  A0 07
  lda #$20                       ; $F811  A9 20
  bne _label_f826                ; $F813  D0 11

_label_f815:
  ldy #$02                       ; $F815  A0 02
  lda #$40                       ; $F817  A9 40
  bne _label_f826                ; $F819  D0 0B

_label_f81b:
  lda #$10                       ; $F81B  A9 10
  sta APU_NOISE_VOL              ; $F81D  8D 0C 40
  ldy #$08                       ; $F820  A0 08
  lda #$EF                       ; $F822  A9 EF
  bne _label_f82f                ; $F824  D0 09

_label_f826:
  jsr _func_f383                 ; $F826  20 83 F3
  ldx #$C0                       ; $F829  A2 C0
  ldy #$C0                       ; $F82B  A0 C0
  bne _label_f836                ; $F82D  D0 07

_label_f82f:
  jsr _func_f383                 ; $F82F  20 83 F3
  ldx #$86                       ; $F832  A2 86
  ldy #$86                       ; $F834  A0 86

_label_f836:
  jsr _func_f3d0                 ; $F836  20 D0 F3
  lda #$00                       ; $F839  A9 00
  sta _var_00e4                  ; $F83B  85 E4
  jmp _label_f40f                ; $F83D  4C 0F F4

_label_f840:
  ldy #$09                       ; $F840  A0 09
  lda #$EF                       ; $F842  A9 EF
  bne _label_f826                ; $F844  D0 E0

_data_f846_indexed:
  asl a                          ; $F846  0A

_data_f847_indexed:
  slo (_var_001c_indexed),Y      ; $F847  13 1C

_data_f849_indexed:
  and $2E                        ; $F849  25 2E

_data_f84b_indexed:
  rla _var_0040_indexed,X        ; $F84B  37 40

_data_f84d_indexed:
  eor #$52                       ; $F84D  49 52
  sre a:_data_c306_indexed+1,Y   ; $F84F  5B 07 C3
  sed                            ; $F852  F8
.byte $e2, $f8                   ; $F853  E2 F8  disambiguous instruction: nop #$F8
  php                            ; $F855  08
  sbc a:_data_f91b_indexed,Y     ; $F856  F9 1B F9
  slo _var_002f                  ; $F859  07 2F
  sbc a:_data_f960_indexed,Y     ; $F85B  F9 60 F9
  lda (_var_00f9_indexed,X)      ; $F85E  A1 F9
  cpy a:$07F9                    ; $F860  CC F9 07
  lax a:_data_cafa               ; $F863  AF FA CA
.byte $fa                        ; $F866  FA  disambiguous instruction: nop
  cpx _var_00fa_indexed          ; $F867  E4 FA
  sbc _var_00fa_indexed,X        ; $F869  F5 FA
  slo _var_00da                  ; $F86B  07 DA
  sbc a:_data_f9f7_indexed,Y     ; $F86D  F9 F7 F9
  slo (_var_00fa_indexed),Y      ; $F870  13 FA
  plp                            ; $F872  28
.byte $fa                        ; $F873  FA  disambiguous instruction: nop
  slo _var_002f                  ; $F874  07 2F
.byte $fa                        ; $F876  FA  disambiguous instruction: nop
  rla a:_var_64fa_indexed,X      ; $F877  3F FA 64
.byte $fa                        ; $F87A  FA  disambiguous instruction: nop
.byte $80, $fa                   ; $F87B  80 FA  disambiguous instruction: nop #$FA
  slo _var_0091                  ; $F87D  07 91
.byte $fa                        ; $F87F  FA  disambiguous instruction: nop
  txs                            ; $F880  9A
.byte $fa                        ; $F881  FA  disambiguous instruction: nop
  lax _var_00fa_indexed          ; $F882  A7 FA
  brk                            ; $F884  00
  brk                            ; $F885  00
  slo _var_00bd                  ; $F886  07 BD
  sed                            ; $F888  F8
  brk                            ; $F889  00
  brk                            ; $F88A  00
  brk                            ; $F88B  00
  brk                            ; $F88C  00
  brk                            ; $F88D  00
  brk                            ; $F88E  00
  brk                            ; $F88F  00
  rol _var_00f9_indexed          ; $F890  26 F9
  rol a                          ; $F892  2A
  sbc a:_var_0000_indexed,Y      ; $F893  F9 00 00
  brk                            ; $F896  00
  brk                            ; $F897  00
  brk                            ; $F898  00
  tax                            ; $F899  AA
  sed                            ; $F89A  F8
  lda (_var_00f8_indexed),Y      ; $F89B  B1 F8
  lax _var_00f8_indexed,Y        ; $F89D  B7 F8
  brk                            ; $F89F  00
  brk                            ; $F8A0  00
  brk                            ; $F8A1  00
  brk                            ; $F8A2  00
  isc a:_data_ff18_indexed,X     ; $F8A3  FF 18 FF
  brk                            ; $F8A6  00
  brk                            ; $F8A7  00
  brk                            ; $F8A8  00
  brk                            ; $F8A9  00
  sta $3E                        ; $F8AA  85 3E
.byte $3c, $3a, $38              ; $F8AC  3C 3A 38  disambiguous instruction: nop a:$383A,X
  rol _var_0000_indexed,X        ; $F8AF  36 00
  sta $44                        ; $F8B1  85 44

.byte $42, $40, $3e, $3c, $85, $3e, $3c, $3a, $38, $36, $c3, $80, $10, $4e, $ff, $00 ; $F8B3
.byte $84, $02, $81, $02, $2a, $2a, $02, $2c, $02, $2c, $02, $2e, $30, $02, $22, $83 ; $F8C3
.byte $02, $81, $02, $08, $02, $02, $06, $02, $06, $02, $28, $2a, $02, $22, $00, $84 ; $F8D3
.byte $02, $81, $02, $80, $46, $46, $81, $46, $02, $1c, $1e, $20, $22, $80, $28, $28 ; $F8E3
.byte $81, $2a, $02, $40, $83, $02, $81, $02, $30, $02, $02, $80, $2c, $2c, $81, $1e ; $F8F3
.byte $20, $22, $30, $83, $02, $c6, $80, $0c, $02, $0c, $02, $18, $02, $18, $02, $4c ; $F903
.byte $02, $4c, $02, $18, $02, $18, $02, $ff ; $F913

_data_f91b_indexed:
.byte $c6, $81, $03, $03, $06, $06, $03, $03, $06, $03, $ff, $81, $16, $4a, $00, $80 ; $F91B
.byte $02, $81, $16, $4a, $81, $0c, $0c, $12, $02, $0c, $02, $12, $02, $0e, $0e, $16 ; $F92B
.byte $02, $0e, $02, $16, $02, $0c, $0c, $12, $02, $0c, $02, $12, $02, $12, $10, $0e ; $F93B
.byte $0c, $08, $04, $30, $02, $80, $04, $04, $81, $08, $0a, $0c, $80, $0e, $0e, $81 ; $F94B
.byte $12, $16, $18, $48, $00    ; $F95B

_data_f960_indexed:
.byte $80, $04, $04, $81, $04, $22, $28, $04, $22, $24, $28, $80, $2c, $2c, $81, $2c ; $F960
.byte $24, $2c, $04, $2c, $80, $04, $30, $2c, $28, $80, $04, $04, $81, $22, $24, $10 ; $F970
.byte $28, $2a, $2c, $2e, $80, $30, $30, $81, $2e, $2c, $28, $80, $24, $24, $81, $22 ; $F980
.byte $1e, $02, $80, $22, $22, $81, $24, $26, $28, $80, $2c, $2c, $81, $30, $04, $08 ; $F990
.byte $0c, $81, $1a, $1a, $02, $20, $22, $02, $3e, $02, $3a, $3a, $02, $40, $42, $02 ; $F9A0
.byte $1a, $42, $1a, $32, $02, $34, $36, $38, $3a, $02, $3e, $82, $3e, $81, $42, $44 ; $F9B0
.byte $46, $3e, $02, $1a, $1a, $02, $38, $3a, $3a, $02, $3a, $1a, $c8, $81, $06, $03 ; $F9C0
.byte $06, $80, $09, $03, $81, $03, $03, $82, $0c, $ff, $81, $2a, $2a, $28, $02, $26 ; $F9D0
.byte $02, $24, $02, $85, $22, $81, $24, $83, $02, $81, $02, $0e, $06, $2a, $2a, $28 ; $F9E0
.byte $26, $24, $85, $22, $81, $24, $00 ; $F9F0

_data_f9f7_indexed:
.byte $81, $24, $24, $22, $02, $20, $02, $1e, $02, $85, $3e, $81, $40, $83, $02, $81 ; $F9F7
.byte $02, $2a, $24, $1c, $1a, $46, $44, $40, $85, $3e, $81, $40, $84, $02, $85, $1a ; $FA07
.byte $81, $1c, $83, $02, $81, $02, $4a, $14, $0e, $0a, $08, $06, $04, $85, $1a, $81 ; $FA17
.byte $1c, $cc, $81, $06, $06, $09, $03, $ff, $82, $08, $10, $16, $48, $18, $02, $12 ; $FA27
.byte $02, $10, $0c, $08, $06, $81, $08, $00, $81, $26, $26, $82, $2c, $81, $08, $0c ; $FA37
.byte $10, $16, $80, $12, $12, $81, $28, $10, $0c, $30, $2e, $30, $04, $80, $2c, $2c ; $FA47
.byte $81, $08, $28, $30, $80, $26, $26, $81, $2c, $22, $2c, $82, $26, $85, $1e, $81 ; $FA57
.byte $1e, $82, $3c, $3c, $85, $3e, $81, $3e, $85, $3e, $81, $3e, $85, $42, $81, $42 ; $FA67
.byte $85, $42, $81, $42, $82, $1e, $81, $1e, $1e, $c4, $81, $06, $82, $0c, $81, $06 ; $FA77
.byte $80, $09, $03, $03, $03, $09, $03, $03, $03, $ff, $81, $0a, $24, $26, $28, $2e ; $FA87
.byte $0a, $04, $00, $80, $12, $12, $81, $0a, $0a, $80, $20, $20, $81, $28, $2e, $2a ; $FA97
.byte $81, $20, $02, $20, $28, $02, $28, $2a, $82, $02, $81, $0e, $08, $04, $2c, $2a ; $FAA7
.byte $28, $24, $1e, $1c, $1a, $1e, $24, $2e, $24, $2c, $04, $28, $2e, $08, $28, $30 ; $FAB7
.byte $0e, $0c, $00, $82, $02, $81, $2c, $2c, $02, $02, $1e, $02, $02, $02, $02, $02 ; $FAC7
.byte $44, $1e, $24, $42, $1a, $2c, $44, $1e, $24, $46, $1e, $1e, $28, $82, $1e, $81 ; $FAD7
.byte $1e, $85, $22, $24, $3c, $82, $3e, $81, $3e, $85, $42, $44, $46, $1a, $c5, $81 ; $FAE7
.byte $06, $06, $06, $09, $03, $06, $ff, $ff, $ff, $55, $ad, $4a, $55, $d5, $aa, $52 ; $FAF7
.byte $55, $ad, $2a, $55, $b5, $2a, $49, $bb, $55, $45, $a9, $6e, $53, $44, $b5, $6b ; $FB07
.byte $15, $a5, $da, $56, $49, $a4, $fb, $96, $10, $d5, $fa, $4a, $50, $b6, $5b, $45 ; $FB17
.byte $b2, $b6, $4b, $01, $e9, $ff, $45, $00, $ba, $ff, $01, $90, $fe, $57, $04, $b5 ; $FB27
.byte $2f, $01, $b5, $ff, $01, $44, $fe, $1f, $01, $b0, $ff, $17, $00, $e8, $ff, $17 ; $FB37
.byte $00, $fa, $7f, $01, $50, $fb, $1b, $41, $ea, $bf, $04, $50, $fb, $2f, $01, $d2 ; $FB47
.byte $fe, $4b, $00, $f8, $ff, $05, $40, $fb, $4f, $40, $ea, $2b, $55, $b5, $2b, $11 ; $FB57
.byte $d1, $fe, $45, $44, $6d, $55, $d5, $6a, $45, $d4, $fa, $2a, $49, $45, $51, $ff ; $FB67
.byte $6e, $04, $a0, $fe, $1f, $01, $11, $fb, $bf, $12, $10, $b5, $ff, $4a, $04, $c0 ; $FB77
.byte $fe, $7f, $00, $a8, $ff, $15, $95, $04, $b8, $ff, $4b, $04, $e4, $fe, $17, $00 ; $FB87
.byte $f8, $ff, $03, $00, $ee, $ff, $07, $00, $e8, $ff, $17, $00, $e8, $ff, $1f, $00 ; $FB97
.byte $f0, $ff, $03, $00, $fe, $ff, $00, $80, $ff, $1f, $00, $f0, $ff, $1f, $00, $e0 ; $FBA7
.byte $ff, $0f, $00, $e8, $ff, $07, $00, $fe, $ff, $01, $00, $ff, $7f, $00, $a0, $ff ; $FBB7
.byte $0f, $00, $f8, $ff, $03, $00, $fe, $7f, $00, $e0, $ff, $0f, $00, $f8, $ff, $01 ; $FBC7
.byte $80, $ff, $1f, $00, $f8, $ff, $03, $00, $fe, $1f, $00, $fe, $7f, $01, $80, $ff ; $FBD7
.byte $07, $c0, $fe, $3f, $00, $d8, $7f, $00, $f8, $ff, $17, $00, $f8, $0f, $80, $ff ; $FBE7
.byte $7f, $01, $80, $7f, $40, $b5, $fe, $3f, $00, $e8, $03, $f4, $bf, $e4, $5e, $01 ; $FBF7
.byte $10, $ee, $bf, $90, $ff, $05, $00, $fc, $7f, $00, $f8, $7f, $00, $f0, $ff, $01 ; $FC07
.byte $e0, $ff, $04, $a0, $ff, $07, $80, $fe, $0f, $00, $ff, $1f, $00, $f8, $ff, $00 ; $FC17
.byte $e0, $ff, $05, $a0, $ff, $07, $00, $fe, $3f, $00, $fa, $3f, $00, $f8, $ff, $00 ; $FC27
.byte $ed, $17, $00, $fb, $5f, $a0, $fb, $13, $00, $fc, $3f, $00, $fb, $3f, $00, $e8 ; $FC37
.byte $ff, $00, $e0, $ff, $07, $00, $ff, $0f, $00, $ff, $7f, $00, $e0, $7f, $01, $f0 ; $FC47
.byte $ff, $07, $00, $fe, $1f, $00, $f8, $ff, $01, $80, $ff, $07, $80, $ff, $7f, $00 ; $FC57
.byte $e0, $ff, $01, $a0, $ff, $0f, $00, $fa, $7f, $00, $e8, $ff, $01, $80, $ff, $1f ; $FC67
.byte $00, $f8, $ff, $01, $80, $ff, $1f, $00, $f8, $ff, $01, $a0, $ff, $0f, $00, $f8 ; $FC77
.byte $ff, $01, $a0, $ff, $1f, $00, $f0, $ff, $05, $e0, $bf, $12, $00, $f8, $ff, $07 ; $FC87
.byte $80, $fe, $3f, $00, $11, $ea, $fe, $17, $e8, $aa, $ee, $04, $a9, $15, $81, $fb ; $FC97
.byte $5f, $51, $a4, $fb, $01, $a0, $ff, $03, $40, $fe, $ff, $00, $c0, $ff, $47, $00 ; $FCA7
.byte $eb, $5f, $00, $b4, $ff, $0f, $00, $ec, $ff, $05, $80, $ee, $57, $11, $d5, $be ; $FCB7
.byte $45, $a4, $d6, $aa, $54, $55, $d5, $54, $aa, $ba, $52, $d5, $b6, $54, $4a, $a9 ; $FCC7
.byte $2a, $55, $bb, $4d, $a5, $94, $6a, $ab, $4a, $55, $ad, $2b, $11, $a9, $ae, $b7 ; $FCD7
.byte $44, $da, $56, $15, $91, $fa, $ab, $14, $a5, $ad, $4a, $a4, $be, $ab, $14, $49 ; $FCE7
.byte $eb, $56, $25, $d1, $6e, $4b, $91, $54, $eb, $aa, $52, $55, $55, $53, $55, $55 ; $FCF7
.byte $55, $ab, $aa, $54, $55, $55, $ab, $aa, $54, $55, $d5, $52, $a9, $ae, $2b, $45 ; $FD07
.byte $52, $6b, $ab, $aa, $aa, $52, $55, $55, $b5, $aa, $52, $d5, $52, $55, $55, $ad ; $FD17
.byte $a6, $52, $55, $55, $d5, $aa, $2a, $55, $95, $aa, $ed, $4a, $91, $d4, $6a, $ab ; $FD27
.byte $aa, $2a, $55, $55, $55, $55, $55, $d5, $aa, $54, $59, $ab, $2a, $55, $55, $55 ; $FD37
.byte $55, $ad, $aa, $14, $b5, $bb, $46, $44, $d5, $ba, $aa, $aa, $52, $a5, $6a, $d5 ; $FD47
.byte $2a, $55, $55, $2b, $55, $d5, $aa, $52, $95, $6a, $b5, $aa, $2a, $45, $ea, $7b ; $FD57
.byte $15, $41, $aa, $db, $5a, $95, $52, $a5, $55, $d5, $54, $55, $b5, $aa, $aa, $aa ; $FD67
.byte $54, $aa, $da, $5a, $a9, $54, $a9, $d4, $ee, $55, $04, $a9, $eb, $5a, $4a, $55 ; $FD77
.byte $b5, $52, $55, $5a, $55, $ad, $56, $15, $91, $ba, $6b, $55, $49, $a9, $b6, $44 ; $FD87
.byte $b9, $bf, $44, $a0, $ba, $6b, $52, $d5, $aa, $4a, $a9, $aa, $ad, $aa, $2b, $11 ; $FD97
.byte $a9, $be, $2e, $45, $69, $6b, $49, $90, $fe, $5f, $00, $e8, $3f, $05, $b5, $af ; $FDA7
.byte $12, $51, $6d, $ab, $54, $db, $12, $91, $fa, $56, $52, $6d, $53, $44, $c4, $ff ; $FDB7
.byte $17, $00, $fd, $13, $a4, $ef, $46, $a8, $56, $95, $d5, $aa, $aa, $4a, $b2, $b6 ; $FDC7
.byte $52, $b5, $2d, $11, $91, $fe, $1f, $80, $be, $12, $ed, $4e, $52, $ad, $44, $ed ; $FDD7
.byte $47, $50, $6f, $05, $ed, $2a, $a5, $db, $12, $41, $fa, $3f, $c0, $2e, $91, $be ; $FDE7
.byte $15, $b5, $13, $94, $fb, $12, $65, $4b, $a9, $ad, $aa, $52, $b5, $16, $01, $ff ; $FDF7
.byte $0f, $f0, $03, $f4, $17, $ea, $17, $c4, $5a, $b5, $15, $a9, $55, $a5, $6d, $45 ; $FE07
.byte $ec, $5a, $04, $f9, $5f, $a0, $17, $e0, $1f, $f8, $17, $e8, $12, $f9, $47, $e8 ; $FE17
.byte $12, $bb, $aa, $2a, $a9, $5b, $01, $fa, $1f, $f8, $04, $f8, $07, $fe, $44, $5b ; $FE27
.byte $90, $7b, $51, $4b, $b4, $1b, $ea, $96, $5a, $11, $e0, $ff, $c1, $16, $d0, $4f ; $FE37
.byte $ec, $93, $5a, $44, $ed, $56, $94, $aa, $5a, $ab, $aa, $49, $a9, $80, $ff, $87 ; $FE47
.byte $16, $d0, $5e, $ba, $aa, $96, $94, $aa, $5b, $54, $aa, $6a, $ab, $55, $49, $15 ; $FE57
.byte $e0, $ff, $45, $05, $aa, $57, $ad, $5a, $49, $95, $ea, $55, $94, $b4, $da, $56 ; $FE67
.byte $a5, $b4, $04, $f8, $7f, $52, $90, $ba, $56, $ab, $95, $52, $a9, $6e, $25, $49 ; $FE77
.byte $6d, $b5, $56, $aa, $12, $a0, $ff, $17, $11, $69, $6b, $b5, $56, $49, $a5, $ea ; $FE87
.byte $4d, $11, $d5, $d6, $5a, $a9, $26, $01, $fe, $5f, $44, $a4, $b6, $b5, $56, $25 ; $FE97
.byte $a5, $ea, $36, $45, $54, $6b, $ab, $55, $55, $00, $fe, $3f, $41, $92, $b6, $d6 ; $FEA7
.byte $5a, $55, $14, $b5, $bb, $14, $91, $ee, $aa, $55, $aa, $04, $f8, $ff, $10, $52 ; $FEB7
.byte $da, $da, $5a, $55, $94, $b4, $bb, $14, $54, $eb, $aa, $5a, $55, $00, $fe, $3f ; $FEC7
.byte $41, $51, $b6, $da, $6a, $95, $94, $b4, $bb, $12, $54, $ed, $aa, $56, $55, $00 ; $FED7
.byte $fe, $5f, $44, $52, $ad, $b6, $6a, $95, $94, $aa, $5b, $15, $51, $eb, $aa, $aa ; $FEE7
.byte $55, $01, $fa, $5f, $44, $4a, $ab, $d6, $aa, $87, $04, $28, $04, $28, $04, $0c ; $FEF7
.byte $04, $0c, $04, $0c, $12, $0c, $12, $0c, $12, $48, $12, $48, $12, $48, $80, $02 ; $FF07
.byte $00                        ; $FF17

_data_ff18_indexed:
.byte $80, $02, $87, $04, $28, $04, $28, $04, $0c, $04, $0c, $04, $0c, $12, $0c, $12 ; $FF18
.byte $0c, $12, $48, $12, $48, $12, $48, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FF28
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FF38
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FF48
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FF58
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FF68
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FF78
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FF88
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FF98
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FFA8
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FFB8
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FFC8
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FFD8
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff ; $FFE8
.byte $ff, $ff                   ; $FFF8

.pad $FFFA

.base $FFFA

.dw NMI, Reset, Reset

.byte $00, $00, $00, $01, $02, $03, $03, $05, $00, $00, $00, $00, $00, $01, $01, $00
.byte $00, $60, $e0, $e0, $e0, $e0, $e0, $e0, $00, $20, $60, $e0, $60, $e0, $e0, $e0
.byte $00, $00, $00, $04, $0e, $0e, $0e, $0e, $00, $00, $00, $1a, $31, $71, $75, $75
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $60, $e0, $e0, $c0, $80
.byte $07, $07, $07, $03, $03, $01, $01, $00, $03, $03, $03, $01, $01, $00, $00, $00
.byte $f0, $f0, $f0, $f9, $fb, $f7, $cf, $bf, $f0, $f0, $f0, $f8, $fb, $ff, $ff, $ff
.byte $04, $00, $00, $c1, $e3, $ef, $df, $fe, $7b, $7f, $fe, $3d, $93, $ce, $dc, $f8
.byte $1e, $7c, $f0, $e0, $c0, $80, $00, $00, $1e, $60, $c0, $80, $00, $00, $00, $00
.byte $00, $00, $00, $01, $01, $01, $03, $0f, $00, $00, $00, $01, $01, $01, $03, $0f
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $fe, $ff, $ff, $ff, $ff, $ff, $ff, $fe, $f8
.byte $fc, $fc, $f8, $f0, $e0, $c0, $00, $00, $f8, $f0, $f0, $e0, $c0, $80, $00, $00
.byte $07, $03, $01, $00, $00, $00, $00, $00, $02, $00, $06, $0e, $0e, $04, $00, $00
.byte $fe, $fc, $f0, $00, $00, $00, $00, $00, $e0, $00, $08, $38, $70, $f0, $f0, $60
.byte $00, $00, $04, $0e, $0e, $0e, $0e, $04, $00, $00, $1a, $31, $71, $75, $75, $7b
.byte $00, $50, $70, $38, $3c, $7c, $78, $f8, $00, $50, $70, $30, $21, $63, $67, $e7
.byte $00, $00, $00, $1f, $ff, $7f, $0f, $07, $00, $00, $00, $1f, $3f, $07, $03, $03
.byte $00, $00, $01, $03, $c7, $ef, $df, $bf, $00, $00, $00, $03, $c7, $ff, $ff, $ff
.byte $00, $00, $c0, $e0, $e0, $c0, $e0, $ff, $7f, $fe, $3c, $90, $c0, $c0, $e0, $ff
.byte $03, $03, $01, $01, $01, $03, $0f, $07, $01, $01, $01, $01, $01, $03, $0f, $02
.byte $7f, $ff, $ff, $ff, $ff, $ff, $fe, $fe, $ff, $ff, $ff, $ff, $ff, $ff, $f8, $e0
.byte $ff, $ff, $ff, $ff, $ff, $c7, $03, $00, $ff, $ff, $ff, $ff, $c7, $01, $00, $00
.byte $c0, $f0, $f8, $fc, $ff, $ee, $b0, $c0, $c0, $f0, $f8, $fc, $ee, $a0, $00, $00
.byte $03, $01, $00, $00, $00, $00, $00, $00, $00, $06, $0e, $0e, $04, $00, $00, $00
.byte $fc, $f0, $00, $00, $00, $00, $00, $00, $00, $08, $38, $70, $f0, $f0, $60, $00
.byte $00, $04, $0e, $0e, $0e, $0e, $04, $00, $00, $1a, $31, $71, $75, $75, $7b, $7f
.byte $f8, $fc, $ff, $ff, $ff, $ff, $ff, $ff, $67, $b3, $b0, $d0, $f0, $f8, $f8, $f8
.byte $00, $00, $00, $00, $00, $00, $01, $03, $00, $00, $00, $00, $00, $00, $01, $03
.byte $00, $01, $03, $07, $0f, $bf, $7f, $ff, $00, $00, $03, $07, $3f, $ff, $ff, $ff
.byte $00, $c0, $e0, $e0, $c0, $c0, $80, $80, $fe, $3c, $90, $c0, $c0, $c0, $80, $80
.byte $07, $07, $0d, $1d, $33, $0f, $07, $03, $06, $05, $09, $11, $03, $0f, $02, $00
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $fb, $f3, $e5, $01
.byte $c0, $c0, $e0, $e0, $f0, $f0, $f0, $f0, $c0, $c0, $e0, $e0, $f0, $f0, $f0, $f0
.byte $01, $00, $00, $00, $00, $00, $00, $00, $06, $0e, $0e, $04, $00, $00, $00, $00
.byte $f3, $01, $01, $01, $00, $00, $00, $00, $09, $38, $70, $f0, $f0, $60, $00, $00
.byte $f0, $f8, $f8, $f8, $fc, $fc, $7e, $1e, $f0, $f8, $f8, $78, $7c, $3c, $0e, $02
.byte $18, $38, $3c, $3c, $3e, $5e, $7f, $7f, $18, $18, $1c, $1c, $1e, $0e, $3f, $3f
.byte $3f, $3f, $3f, $1f, $0f, $07, $03, $01, $1f, $1f, $0f, $07, $07, $03, $01, $00
.byte $00, $00, $01, $03, $04, $00, $00, $00, $00, $00, $00, $00, $03, $07, $0f, $0f
.byte $00, $00, $03, $03, $83, $c3, $e7, $ff, $0f, $0f, $04, $01, $83, $c3, $e7, $ff
.byte $ff, $ff, $ff, $ff, $ff, $2f, $1f, $1f, $ff, $ff, $ff, $ff, $3f, $0f, $1f, $1f
.byte $1f, $1f, $1f, $0f, $07, $03, $00, $00, $1f, $0e, $04, $00, $08, $1c, $1c, $0c
.byte $00, $0f, $3f, $ff, $ff, $bf, $7f, $19, $00, $0f, $3f, $ff, $7f, $3f, $19, $00
.byte $00, $01, $03, $04, $00, $00, $00, $00, $00, $00, $00, $03, $07, $0f, $0f, $0f
.byte $00, $03, $03, $03, $03, $83, $e7, $ff, $0f, $04, $01, $03, $03, $83, $e7, $ff
.byte $ff, $ff, $ff, $ff, $6f, $1f, $1f, $1f, $ff, $ff, $ff, $7f, $0f, $1f, $1f, $1f
.byte $1f, $1f, $0f, $07, $03, $00, $00, $00, $0e, $04, $00, $08, $1c, $1c, $1c, $0c
.byte $00, $00, $01, $01, $03, $07, $0f, $00, $00, $00, $01, $01, $03, $06, $08, $00
.byte $01, $03, $04, $00, $00, $00, $00, $01, $00, $00, $03, $07, $0f, $0f, $0f, $0e
.byte $03, $03, $03, $03, $03, $07, $0f, $1f, $04, $01, $03, $03, $03, $07, $0f, $1f
.byte $3f, $3f, $77, $6f, $ff, $ff, $ff, $ff, $3f, $3f, $7f, $7f, $ff, $df, $df, $8e
.byte $df, $8f, $07, $03, $00, $00, $00, $00, $04, $00, $08, $1c, $1c, $1c, $0c, $00
.byte $00, $40, $60, $30, $00, $00, $00, $01, $00, $40, $60, $30, $00, $00, $00, $01
.byte $80, $00, $00, $00, $00, $00, $c0, $f0, $80, $00, $00, $00, $00, $00, $c0, $f1
.byte $0c, $1e, $1f, $3f, $3f, $3f, $3e, $1e, $00, $00, $00, $00, $0c, $4c, $c1, $e1
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $38, $3c, $7c, $f8, $e0
.byte $03, $07, $0f, $0f, $1f, $1f, $1d, $18, $03, $07, $0f, $0f, $1d, $1c, $10, $00
.byte $f8, $fc, $fc, $fc, $fe, $be, $1e, $0f, $f9, $fd, $fd, $bc, $3e, $1e, $0e, $07
.byte $0c, $00, $00, $00, $00, $40, $f8, $f0, $f3, $ff, $ff, $ff, $7e, $3c, $80, $c0
.byte $00, $00, $00, $00, $00, $00, $00, $00, $80, $80, $e0, $70, $10, $00, $00, $00
.byte $07, $07, $43, $c3, $87, $07, $07, $07, $03, $03, $43, $c3, $87, $06, $04, $04
.byte $fb, $ff, $ff, $ff, $ff, $fc, $fc, $fc, $fb, $ff, $ff, $c7, $04, $00, $00, $00
.byte $e1, $f3, $f8, $fc, $fc, $7c, $1c, $18, $e1, $f3, $f8, $fc, $7c, $1c, $08, $00
.byte $1f, $03, $07, $07, $06, $00, $00, $00, $f0, $ec, $f8, $70, $36, $00, $00, $00
.byte $e0, $80, $80, $00, $00, $00, $00, $00, $06, $6f, $3e, $1c, $18, $00, $00, $00
.byte $00, $00, $00, $00, $00, $01, $03, $03, $00, $00, $00, $00, $00, $00, $02, $02
.byte $00, $03, $17, $3f, $7f, $fe, $fe, $fc, $00, $03, $17, $3b, $53, $86, $06, $04
.byte $03, $03, $03, $07, $07, $07, $07, $1f, $00, $00, $00, $00, $00, $00, $00, $18
.byte $fc, $f8, $f8, $f8, $f8, $f0, $f3, $ff, $0c, $08, $08, $08, $18, $10, $12, $1e
.byte $00, $00, $04, $0e, $0e, $0e, $0e, $04, $00, $00, $1a, $31, $73, $f3, $f1, $fb
.byte $00, $17, $0f, $07, $03, $01, $01, $00, $00, $17, $0f, $03, $01, $00, $00, $00
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $f8, $f8, $f8, $f8, $f8, $70, $00, $00
.byte $ff, $ff, $ff, $ff, $fc, $f8, $f0, $c0, $3e, $3e, $3f, $0f, $00, $00, $00, $00
.byte $00, $80, $80, $00, $00, $00, $00, $00, $ff, $7e, $40, $00, $00, $00, $00, $00
.byte $7f, $0c, $00, $00, $00, $00, $00, $00, $00, $10, $f8, $f0, $e0, $40, $00, $00
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $80, $f0, $f8, $f8, $00, $00, $00
.byte $00, $80, $00, $18, $20, $22, $24, $3c, $00, $e0, $f0, $f8, $f8, $fe, $fc, $f8
.byte $7c, $3d, $3b, $27, $2f, $1f, $1f, $1f, $c8, $c4, $dc, $f9, $f0, $e4, $e0, $e0
.byte $3f, $3f, $3f, $3f, $3c, $00, $ff, $f8, $cc, $ca, $c8, $c0, $40, $00, $ff, $f8
.byte $00, $00, $00, $00, $00, $30, $78, $78, $00, $00, $00, $00, $00, $30, $68, $70
.byte $f8, $f0, $f8, $f8, $f8, $f8, $f8, $f0, $78, $70, $30, $00, $00, $90, $00, $00
.byte $f0, $e0, $c0, $00, $00, $00, $e0, $00, $00, $00, $00, $00, $00, $00, $e0, $00
.byte $00, $00, $80, $40, $30, $08, $04, $04, $e0, $f0, $78, $3c, $0e, $07, $03, $03
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01, $03, $03, $07, $07
.byte $80, $80, $00, $00, $00, $00, $00, $00, $60, $60, $70, $fe, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $80, $c0, $e0, $f8
.byte $00, $00, $00, $00, $00, $00, $00, $00, $0f, $0f, $0f, $0f, $0f, $07, $07, $07
.byte $00, $00, $00, $00, $00, $00, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $01, $02, $02, $00, $e0, $f8, $fc, $fe, $ff, $ff, $ff
.byte $00, $07, $0f, $0f, $1f, $1f, $1f, $3f, $00, $07, $0f, $0f, $1f, $3f, $ff, $ff
.byte $00, $80, $00, $18, $20, $20, $22, $3c, $00, $e0, $f0, $f8, $f8, $f8, $fe, $fc
.byte $00, $00, $00, $00, $00, $00, $00, $00, $0f, $1f, $3f, $7f, $7f, $7f, $7c, $78
.byte $01, $02, $04, $0f, $3f, $1f, $1f, $0f, $fe, $fd, $fb, $f0, $c0, $00, $00, $00
.byte $00, $00, $00, $00, $80, $c0, $64, $34, $ff, $ff, $ff, $ff, $7f, $3f, $1b, $0b
.byte $04, $04, $04, $04, $04, $04, $06, $06, $ff, $ff, $ff, $ff, $ff, $ff, $fb, $fb
.byte $3e, $3e, $3e, $7e, $7e, $7e, $7e, $7e, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $7c, $3c, $3d, $13, $2f, $0f, $1f, $1f, $c8, $c0, $ce, $fc, $f0, $f0, $e2, $e0
.byte $0c, $1e, $fe, $fe, $fc, $fc, $fc, $fc, $0c, $1a, $3c, $3e, $9c, $00, $40, $10
.byte $00, $00, $00, $00, $20, $c0, $00, $ff, $78, $78, $f8, $f8, $f8, $f0, $e0, $ff
.byte $0e, $0f, $0f, $0f, $07, $07, $3f, $ff, $00, $00, $00, $00, $00, $00, $3c, $ff
.byte $1e, $06, $87, $e7, $f7, $f7, $f1, $ff, $01, $01, $00, $00, $40, $20, $21, $ff
.byte $02, $00, $00, $80, $c0, $e0, $e0, $fe, $ff, $fc, $fe, $7f, $3f, $1f, $9f, $ff
.byte $7e, $7e, $3e, $06, $00, $10, $08, $08, $ff, $7f, $3f, $fe, $fc, $fe, $fe, $fe
.byte $3f, $3f, $3f, $3f, $3f, $3c, $ff, $fc, $c1, $c0, $cc, $ce, $4c, $00, $ff, $fc
.byte $f8, $f8, $f0, $e0, $00, $00, $f0, $00, $00, $00, $00, $00, $00, $00, $f0, $00
.byte $00, $00, $00, $00, $00, $00, $08, $08, $00, $00, $00, $00, $00, $0c, $06, $06
.byte $04, $04, $00, $00, $00, $00, $00, $00, $02, $02, $0e, $1e, $3c, $78, $70, $70
.byte $00, $00, $00, $00, $00, $00, $00, $00, $60, $60, $fc, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $01, $01, $ff, $ff, $ff, $ff, $ff, $ff, $fe, $fe
.byte $00, $00, $00, $00, $00, $00, $00, $03, $07, $07, $0f, $0f, $0f, $07, $03, $00
.byte $02, $0c, $3e, $3b, $01, $00, $00, $00, $fd, $f3, $c1, $c0, $e0, $f0, $f0, $f8
.byte $00, $00, $00, $00, $80, $c4, $64, $34, $ff, $ff, $ff, $ff, $7f, $3b, $1b, $0b
.byte $04, $04, $04, $04, $04, $04, $02, $0a, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $f7
.byte $01, $01, $01, $00, $00, $00, $01, $07, $00, $00, $00, $00, $00, $00, $01, $07
.byte $00, $90, $90, $a6, $cf, $7f, $ff, $ff, $f8, $78, $78, $78, $34, $02, $82, $ff
.byte $1c, $06, $02, $02, $02, $00, $0f, $ff, $03, $01, $01, $01, $01, $01, $0f, $ff
.byte $0a, $0f, $07, $00, $00, $00, $00, $f0, $f7, $f0, $f8, $ff, $ff, $ff, $ff, $ff
.byte $7e, $fe, $fe, $3e, $1c, $40, $2f, $2f, $ff, $7f, $3f, $fe, $fc, $f0, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01, $03, $03, $07
.byte $00, $00, $00, $00, $00, $00, $00, $00, $07, $07, $07, $07, $03, $03, $03, $03
.byte $02, $07, $07, $07, $07, $07, $07, $07, $01, $00, $00, $00, $00, $00, $00, $00
.byte $00, $00, $80, $81, $81, $81, $00, $00, $ff, $ff, $7f, $7e, $7e, $7c, $7c, $3e
.byte $40, $40, $80, $02, $02, $c2, $64, $34, $bf, $bf, $7f, $fd, $fd, $3d, $1b, $0b
.byte $04, $04, $04, $04, $04, $04, $12, $12, $ff, $ff, $ff, $ff, $ff, $ff, $ef, $ef
.byte $0f, $1f, $1f, $1f, $1e, $0c, $00, $0f, $00, $00, $00, $04, $08, $00, $00, $0f
.byte $00, $00, $00, $00, $00, $00, $38, $fc, $3e, $1e, $1f, $0f, $0f, $07, $3f, $ff
.byte $1c, $00, $00, $00, $00, $40, $2e, $2f, $03, $07, $07, $07, $e7, $f3, $ff, $ff
.byte $12, $26, $3f, $0f, $00, $04, $02, $c2, $ef, $d8, $c0, $f0, $ff, $ff, $ff, $ff
.byte $7e, $7e, $3e, $fe, $ff, $ff, $ff, $ff, $ff, $7f, $3f, $3e, $1c, $82, $82, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $03, $03, $07, $1f, $1f, $1f, $1f, $1f
.byte $01, $01, $02, $03, $01, $18, $7e, $7f, $fe, $fe, $fd, $fc, $f8, $e0, $80, $00
.byte $00, $00, $00, $00, $80, $c0, $62, $32, $ff, $ff, $ff, $ff, $7f, $3f, $1d, $0d
.byte $04, $04, $04, $04, $04, $04, $0a, $0f, $ff, $ff, $ff, $ff, $ff, $ff, $f7, $f2
.byte $3e, $3e, $3e, $7e, $7e, $7e, $7e, $1e, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $0c, $0f, $0f, $0f, $0f, $07, $07, $03, $0f
.byte $1f, $0f, $07, $06, $00, $20, $17, $17, $02, $02, $04, $80, $f0, $f8, $ff, $ff
.byte $1e, $06, $00, $00, $00, $00, $03, $ff, $01, $01, $01, $01, $00, $00, $03, $ff
.byte $00, $08, $00, $00, $00, $01, $87, $ff, $f9, $f7, $ff, $ff, $ff, $fe, $f8, $fe
.byte $0e, $26, $16, $0e, $3e, $ff, $ff, $ff, $ff, $ff, $ff, $fe, $dc, $00, $02, $02
.byte $0f, $1f, $13, $27, $26, $2e, $4e, $4c, $0f, $1f, $1f, $3b, $3a, $36, $76, $74
.byte $00, $00, $1e, $3f, $3f, $7e, $78, $70, $00, $00, $1e, $3f, $3f, $7e, $78, $70
.byte $4c, $4c, $4e, $2e, $1f, $17, $0b, $07, $74, $74, $76, $36, $13, $18, $0d, $07
.byte $70, $20, $03, $67, $e7, $cf, $cf, $8f, $70, $3e, $3f, $7c, $fc, $f8, $f9, $f9
.byte $00, $00, $00, $00, $80, $80, $c0, $c0, $00, $00, $00, $00, $00, $80, $40, $40
.byte $00, $00, $00, $00, $00, $04, $04, $04, $01, $01, $01, $01, $03, $07, $0f, $3f
.byte $0f, $0f, $0f, $07, $07, $03, $05, $03, $f8, $f8, $f8, $fc, $fd, $fe, $fe, $fc
.byte $c0, $c1, $cf, $bf, $7f, $ff, $ff, $ff, $80, $01, $41, $c0, $88, $02, $10, $00
.byte $f0, $f8, $f8, $f0, $f0, $f0, $f0, $f0, $f0, $c8, $e8, $f0, $00, $00, $00, $80
.byte $04, $04, $04, $06, $02, $02, $03, $01, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $07, $0f, $0f, $1f, $1f, $1f, $0f, $4f, $f8, $f0, $f3, $e3, $e3, $e3, $f3, $c1
.byte $ff, $ff, $ff, $ef, $c0, $80, $80, $80, $04, $00, $00, $e0, $c0, $80, $80, $80
.byte $f0, $e0, $c0, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
.byte $01, $09, $0a, $0c, $08, $00, $00, $00, $ff, $f6, $f4, $f0, $f0, $f8, $f8, $fc
.byte $ce, $87, $07, $03, $00, $00, $00, $00, $c1, $81, $01, $00, $00, $00, $00, $00
.byte $c0, $e0, $f0, $f8, $f8, $f8, $f8, $70, $00, $40, $20, $10, $10, $10, $00, $00
.byte $00, $00, $00, $80, $c0, $e0, $e0, $fe, $fc, $fe, $fe, $7f, $3f, $1f, $9f, $ff
.byte $00, $00, $00, $00, $00, $08, $05, $05, $00, $00, $00, $f8, $fc, $fe, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $ff, $f0, $00, $00, $00, $00, $00, $00, $ff, $f0
.byte $00, $00, $00, $00, $00, $80, $80, $80, $00, $00, $00, $00, $40, $60, $60, $60
.byte $80, $80, $80, $80, $80, $80, $80, $80, $60, $60, $60, $60, $60, $60, $60, $60
.byte $00, $00, $00, $07, $0f, $1f, $1f, $ff, $00, $00, $00, $07, $03, $00, $00, $e0
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $7f, $f0, $f8, $f8, $f8, $70, $00, $00, $00
.byte $0c, $00, $00, $00, $00, $00, $00, $00, $10, $f8, $f0, $e0, $40, $00, $00, $00
.byte $00, $00, $f0, $f8, $f8, $f3, $ff, $ff, $00, $00, $f0, $f8, $f8, $d2, $1e, $1e
.byte $ff, $ff, $ff, $fc, $f8, $f0, $c0, $00, $3e, $3f, $3f, $0c, $00, $00, $00, $00
.byte $00, $00, $00, $00, $00, $0f, $7f, $ff, $00, $00, $00, $00, $00, $0f, $7f, $ff
.byte $ff, $ff, $ff, $ff, $ff, $ff, $7f, $0f, $ff, $ff, $ff, $ff, $37, $07, $03, $13
.byte $03, $03, $03, $01, $01, $00, $00, $00, $fb, $f1, $e1, $40, $00, $00, $00, $00
.byte $00, $00, $00, $00, $e3, $ff, $ff, $ff, $00, $00, $00, $00, $e2, $fe, $fe, $fe
.byte $ff, $ff, $fc, $f8, $f0, $f0, $f0, $f8, $ff, $ff, $fc, $f0, $f0, $f0, $f0, $f8
.byte $f8, $f8, $f8, $fc, $fc, $fc, $3e, $0e, $f8, $f8, $f8, $fc, $bc, $2c, $0e, $06
.byte $fe, $fe, $7e, $7c, $3c, $38, $38, $38, $f8, $f8, $7a, $7c, $3c, $38, $38, $00
.byte $00, $00, $00, $00, $20, $3a, $3e, $3f, $00, $00, $00, $00, $20, $30, $38, $3a
.byte $3f, $1f, $1f, $0f, $0f, $07, $03, $01, $3f, $1f, $1f, $0f, $0f, $07, $03, $01
.byte $00, $03, $07, $05, $01, $0b, $0f, $0f, $03, $00, $00, $02, $06, $04, $00, $00
.byte $1e, $1e, $1e, $3e, $3c, $18, $00, $00, $01, $01, $01, $05, $0b, $2e, $18, $00
.byte $20, $60, $40, $40, $40, $20, $20, $20, $10, $18, $38, $38, $38, $1c, $1c, $1e
.byte $11, $10, $08, $04, $02, $01, $00, $00, $0e, $0f, $07, $0b, $0d, $1e, $1f, $1f
.byte $04, $05, $06, $07, $03, $00, $00, $40, $9b, $da, $d9, $f8, $fc, $ff, $ff, $bf
.byte $41, $62, $3c, $00, $00, $00, $00, $00, $be, $9c, $00, $00, $00, $00, $00, $00
.byte $00, $00, $00, $00, $00, $30, $78, $7c, $00, $00, $00, $00, $00, $30, $78, $7c
.byte $7c, $1c, $0e, $0e, $06, $04, $00, $00, $7c, $1c, $0e, $0e, $07, $07, $03, $07
.byte $00, $00, $07, $08, $00, $00, $00, $3c, $07, $07, $07, $0f, $0f, $1f, $3f, $43
.byte $03, $80, $00, $00, $00, $00, $00, $03, $fc, $7f, $ff, $ff, $ff, $ff, $ff, $fc
.byte $04, $58, $cb, $fb, $fa, $fa, $02, $07, $fb, $a7, $34, $04, $05, $05, $05, $00
.byte $07, $07, $07, $0f, $0f, $07, $03, $00, $00, $00, $00, $00, $00, $0d, $05, $03
.byte $00, $00, $38, $3c, $3a, $18, $1c, $0c, $00, $00, $38, $34, $36, $16, $1a, $0b
.byte $0e, $06, $06, $07, $0f, $1e, $0c, $00, $0d, $05, $05, $f4, $fd, $fe, $fe, $fe
.byte $01, $00, $e0, $18, $04, $02, $02, $01, $fe, $ff, $ff, $ff, $ff, $ff, $ff, $fe
.byte $00, $80, $00, $00, $10, $1c, $0e, $1b, $fe, $7f, $ff, $ff, $ef, $e3, $f1, $e0
.byte $80, $40, $20, $a0, $a0, $80, $88, $88, $70, $b8, $d8, $58, $58, $78, $70, $70
.byte $90, $90, $a0, $80, $80, $00, $00, $00, $60, $60, $40, $40, $c0, $c0, $80, $00
.byte $80, $c0, $c0, $c0, $c0, $c0, $c0, $80, $80, $40, $00, $00, $00, $00, $00, $00
.byte $00, $00, $80, $80, $10, $18, $20, $c0, $00, $70, $78, $78, $e8, $e0, $c0, $00
.byte $00, $00, $1c, $3e, $7f, $07, $03, $07, $00, $00, $1c, $3e, $7f, $07, $03, $f7
.byte $1c, $3e, $3e, $0f, $07, $07, $07, $c6, $1c, $3e, $3e, $0f, $07, $07, $ff, $fe
.byte $00, $00, $00, $00, $0c, $07, $00, $00, $00, $01, $0f, $0f, $03, $00, $00, $00
.byte $00, $01, $00, $3c, $c3, $00, $00, $00, $39, $fe, $ff, $c3, $0c, $1f, $1f, $1f
.byte $03, $00, $00, $00, $00, $80, $00, $03, $fc, $ff, $ff, $ff, $ff, $7f, $ff, $fc
.byte $32, $ca, $24, $02, $01, $01, $00, $00, $fe, $3e, $de, $ff, $ff, $ff, $ff, $ff
.byte $88, $44, $24, $a4, $a6, $8b, $89, $88, $77, $bb, $db, $5b, $59, $70, $70, $70
.byte $00, $00, $00, $00, $00, $00, $a0, $c0, $80, $80, $80, $c0, $e0, $e0, $40, $00
.byte $00, $00, $00, $01, $07, $0f, $1f, $1f, $00, $00, $00, $01, $07, $0f, $1f, $1f
.byte $3e, $3e, $3e, $3c, $1c, $1c, $0c, $00, $3e, $3e, $3e, $3c, $1c, $1c, $0c, $00
.byte $00, $00, $00, $00, $01, $01, $01, $10, $03, $07, $0f, $0f, $1f, $1f, $1f, $0f
.byte $10, $10, $08, $08, $08, $04, $03, $00, $0f, $0f, $07, $07, $07, $03, $00, $00
.byte $c0, $f0, $f6, $2e, $1e, $1e, $1e, $1e, $c6, $ff, $ff, $39, $31, $35, $33, $31
.byte $0f, $77, $ff, $ff, $ff, $ff, $ff, $ff, $3b, $0f, $02, $49, $00, $04, $91, $42
.byte $ff, $ff, $7f, $3f, $9f, $c7, $70, $1f, $3c, $44, $ee, $c4, $e0, $f8, $ff, $ff
.byte $0e, $01, $00, $01, $00, $e8, $b5, $9e, $f1, $fe, $ff, $ff, $ff, $1f, $4e, $63
.byte $80, $80, $c0, $40, $40, $40, $40, $40, $7f, $7f, $3f, $3f, $3f, $3f, $3f, $3f
.byte $ff, $ff, $f3, $c9, $c1, $a1, $10, $80, $3c, $22, $7f, $3f, $3f, $7f, $ff, $ff
.byte $60, $18, $84, $82, $83, $81, $01, $01, $9f, $e7, $7b, $7d, $fc, $7e, $fe, $fe
.byte $80, $c6, $fe, $fe, $fe, $7c, $18, $00, $80, $c6, $fe, $fe, $fe, $7c, $18, $00
.byte $00, $00, $00, $00, $80, $80, $00, $00, $c0, $e0, $f0, $f0, $f8, $f8, $f8, $fc
.byte $c0, $20, $04, $04, $0c, $08, $98, $70, $fc, $fc, $f8, $f8, $f0, $f0, $60, $00
.byte $00, $c0, $e0, $f0, $76, $2e, $1e, $1e, $00, $c0, $e6, $ff, $7f, $39, $31, $35
.byte $1e, $1e, $0f, $77, $ff, $ff, $ff, $ff, $33, $31, $3b, $0f, $02, $49, $00, $04
.byte $ff, $ff, $ff, $7f, $3f, $8f, $60, $1f, $91, $42, $3c, $c4, $c4, $f0, $ff, $ff
.byte $ff, $ff, $f3, $c9, $c1, $a1, $10, $00, $89, $42, $3e, $7f, $7f, $7f, $ff, $ff
.byte $00, $00, $00, $00, $00, $01, $03, $02, $01, $03, $07, $0f, $1f, $1e, $3c, $3c
.byte $0e, $00, $02, $0e, $06, $44, $3c, $00, $70, $7c, $7c, $78, $7c, $38, $10, $00
.byte $c0, $f0, $f6, $2e, $1e, $1e, $1e, $1e, $c6, $ff, $ff, $39, $31, $33, $33, $31
.byte $0f, $77, $ff, $ff, $ff, $ff, $7f, $3f, $3b, $0f, $02, $49, $00, $04, $11, $43
.byte $3f, $1f, $5f, $4f, $27, $10, $4f, $c0, $7f, $7f, $fd, $f8, $f8, $ff, $bf, $3f
.byte $c0, $80, $80, $80, $80, $80, $80, $80, $3f, $7f, $7f, $7f, $7f, $7f, $7f, $7f
.byte $fd, $f9, $fa, $f2, $e4, $08, $f1, $03, $ff, $ff, $3f, $9f, $1f, $ff, $fe, $fc
.byte $00, $00, $00, $00, $00, $00, $00, $01, $00, $00, $01, $03, $0f, $1f, $7f, $fe
.byte $02, $04, $08, $30, $61, $c1, $81, $83, $fc, $f8, $f0, $c0, $81, $01, $01, $03
.byte $03, $07, $07, $0d, $00, $00, $00, $00, $03, $06, $04, $08, $00, $00, $00, $00
.byte $0c, $1e, $1e, $1e, $0c, $00, $00, $00, $3c, $7e, $ff, $e9, $f3, $7f, $7e, $38
.byte $08, $08, $48, $30, $28, $00, $24, $7e, $74, $f6, $be, $de, $dc, $fc, $fc, $7e
.byte $7e, $ff, $ff, $ff, $ff, $ff, $fc, $f8, $7e, $fd, $fc, $fc, $ec, $d8, $db, $b7
.byte $f8, $f8, $7c, $3c, $38, $70, $50, $00, $37, $77, $63, $21, $30, $70, $50, $00
.byte $00, $00, $00, $00, $00, $00, $00, $00, $60, $f0, $e0, $80, $c0, $40, $00, $00
.byte $80, $80, $80, $80, $80, $00, $00, $00, $20, $30, $30, $30, $f0, $20, $00, $00
.byte $07, $3f, $7f, $ff, $ff, $7f, $1f, $03, $00, $00, $00, $00, $80, $60, $1c, $03
.byte $00, $00, $07, $1f, $3f, $3f, $1f, $07, $00, $00, $00, $00, $00, $20, $18, $07
.byte $00, $00, $00, $00, $04, $0c, $00, $00, $00, $00, $00, $00, $00, $04, $00, $00
.byte $00, $00, $00, $00, $08, $08, $00, $00, $00, $00, $00, $00, $00, $08, $00, $00
.byte $00, $00, $7e, $ff, $ff, $3c, $00, $00, $00, $00, $00, $00, $c3, $3c, $00, $00
.byte $00, $00, $38, $7c, $7c, $00, $00, $00, $00, $00, $00, $00, $7c, $00, $00, $00
.byte $00, $00, $00, $38, $38, $00, $00, $00, $00, $00, $00, $00, $38, $00, $00, $00
.byte $00, $00, $00, $07, $1f, $3f, $7f, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $ff, $7f, $1f, $07, $00, $00, $00, $00, $80, $60, $1c, $07, $00, $00
.byte $ff, $ff, $ff, $ff, $ff, $ff, $7e, $00, $00, $00, $00, $00, $00, $c3, $7e, $00
.byte $00, $00, $00, $00, $00, $00, $00, $00, $78, $f8, $e0, $80, $80, $c0, $60, $00
.byte $00, $07, $04, $04, $07, $01, $05, $07, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $07, $05, $05, $02, $05, $05, $07, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $27, $25, $25, $25, $25, $25, $27, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $27, $24, $24, $27, $21, $25, $27, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $27, $24, $24, $27, $25, $25, $27, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $77, $55, $15, $35, $65, $45, $77, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $75, $55, $15, $37, $61, $41, $71, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $77, $15, $15, $75, $15, $15, $77, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $77, $55, $55, $55, $55, $55, $77, $00, $00, $00, $00, $00, $00, $00, $00
.byte $c7, $b3, $39, $39, $39, $9b, $c7, $ff, $38, $4c, $c6, $c6, $c6, $64, $38, $00
.byte $e7, $c7, $e7, $e7, $e7, $e7, $81, $ff, $18, $38, $18, $18, $18, $18, $7e, $00
.byte $83, $39, $f1, $c3, $87, $1f, $01, $ff, $7c, $c6, $0e, $3c, $78, $e0, $fe, $00
.byte $81, $f3, $e7, $c3, $f9, $39, $83, $ff, $7e, $0c, $18, $3c, $06, $c6, $7c, $00
.byte $e3, $c3, $93, $33, $01, $f3, $f3, $ff, $1c, $3c, $6c, $cc, $fe, $0c, $0c, $00
.byte $03, $3f, $03, $f9, $f9, $39, $83, $ff, $fc, $c0, $fc, $06, $06, $c6, $7c, $00
.byte $c3, $9f, $3f, $03, $39, $39, $83, $ff, $3c, $60, $c0, $fc, $c6, $c6, $7c, $00
.byte $01, $39, $f3, $e7, $cf, $cf, $cf, $ff, $fe, $c6, $0c, $18, $30, $30, $30, $00
.byte $83, $39, $39, $83, $39, $39, $83, $ff, $7c, $c6, $c6, $7c, $c6, $c6, $7c, $00
.byte $83, $39, $39, $81, $f9, $f3, $87, $ff, $7c, $c6, $c6, $7e, $06, $0c, $78, $00
.byte $c7, $93, $39, $39, $01, $39, $39, $ff, $38, $6c, $c6, $c6, $fe, $c6, $c6, $00
.byte $03, $39, $39, $03, $39, $39, $03, $ff, $fc, $c6, $c6, $fc, $c6, $c6, $fc, $00
.byte $c3, $99, $3f, $3f, $3f, $99, $c3, $ff, $3c, $66, $c0, $c0, $c0, $66, $3c, $00
.byte $07, $33, $39, $39, $39, $33, $07, $ff, $f8, $cc, $c6, $c6, $c6, $cc, $f8, $00
.byte $01, $3f, $3f, $03, $3f, $3f, $01, $ff, $fe, $c0, $c0, $fc, $c0, $c0, $fe, $00
.byte $01, $3f, $3f, $03, $3f, $3f, $3f, $ff, $fe, $c0, $c0, $fc, $c0, $c0, $c0, $00
.byte $c1, $9f, $3f, $31, $39, $99, $c1, $ff, $3e, $60, $c0, $ce, $c6, $66, $3e, $00
.byte $39, $39, $39, $01, $39, $39, $39, $ff, $c6, $c6, $c6, $fe, $c6, $c6, $c6, $00
.byte $81, $e7, $e7, $e7, $e7, $e7, $81, $ff, $7e, $18, $18, $18, $18, $18, $7e, $00
.byte $00, $00, $00, $00, $ff, $ff, $ff, $ff, $00, $00, $00, $ff, $00, $00, $00, $00
.byte $39, $33, $27, $0f, $07, $23, $31, $ff, $c6, $cc, $d8, $f0, $f8, $dc, $ce, $00
.byte $9f, $9f, $9f, $9f, $9f, $9f, $81, $ff, $60, $60, $60, $60, $60, $60, $7e, $00
.byte $39, $11, $01, $01, $29, $39, $39, $ff, $c6, $ee, $fe, $fe, $d6, $c6, $c6, $00
.byte $39, $19, $09, $01, $21, $31, $39, $ff, $c6, $e6, $f6, $fe, $de, $ce, $c6, $00
.byte $83, $39, $39, $39, $39, $39, $83, $ff, $7c, $c6, $c6, $c6, $c6, $c6, $7c, $00
.byte $03, $39, $39, $39, $03, $3f, $3f, $ff, $fc, $c6, $c6, $c6, $fc, $c0, $c0, $00
.byte $00, $00, $00, $00, $80, $c0, $e0, $e0, $00, $00, $00, $c0, $60, $30, $10, $10
.byte $03, $39, $39, $31, $07, $23, $31, $ff, $fc, $c6, $c6, $ce, $f8, $dc, $ce, $00
.byte $87, $33, $3f, $83, $f9, $39, $83, $ff, $78, $cc, $c0, $7c, $06, $c6, $7c, $00
.byte $81, $e7, $e7, $e7, $e7, $e7, $e7, $ff, $7e, $18, $18, $18, $18, $18, $18, $00
.byte $39, $39, $39, $39, $39, $39, $83, $ff, $c6, $c6, $c6, $c6, $c6, $c6, $7c, $00
.byte $39, $39, $39, $11, $83, $c7, $ef, $ff, $c6, $c6, $c6, $ee, $7c, $38, $10, $00
.byte $39, $39, $29, $01, $01, $11, $39, $ff, $c6, $c6, $d6, $fe, $fe, $ee, $c6, $00
.byte $e0, $e0, $e0, $e0, $e0, $e0, $e0, $e0, $10, $10, $10, $10, $10, $10, $10, $10
.byte $99, $99, $81, $c3, $e7, $e7, $e7, $ff, $66, $66, $7e, $3c, $18, $18, $18, $00
.byte $0f, $07, $03, $00, $00, $00, $00, $00, $10, $18, $0c, $07, $00, $00, $00, $00
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
.byte $c3, $bd, $66, $5e, $5e, $66, $bd, $c3, $3c, $42, $99, $a1, $a1, $99, $42, $3c
.byte $ff, $df, $cf, $07, $03, $01, $00, $ff, $00, $20, $30, $f8, $fc, $fe, $ff, $00
.byte $ff, $83, $83, $ff, $83, $83, $ff, $ff, $00, $7c, $7c, $00, $7c, $7c, $00, $00
.byte $00, $00, $00, $00, $04, $18, $30, $1c, $00, $00, $00, $00, $06, $1f, $3f, $1f
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $40, $ec, $fe, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $80, $c0, $e0, $e0
.byte $38, $70, $70, $38, $fc, $f8, $7c, $e6, $3f, $7f, $7f, $3f, $ff, $ff, $7f, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $c0, $f0, $f8, $f8, $f0, $f8, $f0, $f8
.byte $01, $07, $0f, $0c, $1e, $1f, $0f, $1f, $01, $07, $0f, $0f, $1f, $1f, $0f, $1f
.byte $c1, $c0, $e0, $f0, $60, $c4, $06, $82, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $10, $60, $00, $fc, $fe, $fc, $fe, $fe, $fc, $fe, $fe
.byte $3f, $1f, $0f, $1f, $3f, $1f, $3f, $7f, $3f, $1f, $0f, $1f, $3f, $1f, $3f, $7f
.byte $c8, $f8, $f0, $f9, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $02, $01, $00, $91, $f3, $fb, $7f, $ff, $ff, $ff, $ff, $ff, $ff, $bf, $bf
.byte $42, $c4, $82, $17, $3e, $ff, $ff, $bf, $fe, $fc, $fe, $ff, $fe, $ff, $bf, $df
.byte $7f, $ff, $ff, $ff, $ee, $6e, $76, $30, $7f, $ff, $7f, $6f, $77, $b7, $bb, $df
.byte $f6, $f6, $e4, $e4, $c4, $40, $40, $00, $bf, $7f, $7f, $7f, $7f, $ff, $ff, $ff
.byte $ff, $ff, $db, $9b, $99, $89, $00, $00, $7d, $7d, $7d, $fd, $fe, $fe, $ff, $ff
.byte $de, $dd, $4c, $a4, $a4, $80, $80, $00, $ec, $ee, $f7, $ff, $ff, $ff, $ff, $ff
.byte $10, $14, $14, $08, $08, $08, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $08, $0c, $24, $00, $00, $00, $00, $00, $08, $0c, $24
.byte $00, $00, $00, $00, $00, $01, $22, $62, $00, $00, $00, $00, $00, $02, $24, $6c
.byte $00, $00, $00, $00, $00, $00, $08, $0c, $00, $00, $00, $00, $00, $00, $08, $0c
.byte $00, $00, $00, $00, $00, $80, $84, $cc, $00, $00, $00, $00, $00, $80, $84, $cc
.byte $00, $00, $00, $00, $40, $20, $10, $08, $00, $00, $00, $00, $00, $00, $20, $30
.byte $00, $00, $00, $00, $00, $40, $51, $51, $00, $00, $00, $00, $01, $01, $02, $82
.byte $00, $00, $00, $80, $80, $80, $00, $20, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $00, $00, $00, $00, $00, $40, $30, $00, $00, $00, $00, $00, $00, $00, $00
.byte $33, $31, $31, $10, $10, $00, $00, $00, $dd, $de, $de, $ef, $ef, $ff, $ff, $ff
.byte $80, $80, $80, $80, $04, $04, $04, $04, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $09, $00, $00, $00, $00, $00, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $10, $10, $10, $00, $00, $00, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $40, $80, $80, $88, $88, $08, $08, $08, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $22, $22, $12, $12, $12, $10, $10, $10, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $08, $08, $08, $08, $04, $04, $04, $04, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $10, $1f, $ff, $ff, $ff, $ff, $ff, $ff, $ef, $e0, $0f
.byte $00, $00, $00, $00, $00, $1c, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $e3, $00, $ff
.byte $00, $00, $00, $00, $00, $26, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $d9, $00, $ff
.byte $00, $00, $00, $00, $40, $40, $e0, $ff, $ff, $ff, $ff, $ff, $bf, $bf, $1f, $c0
.byte $00, $00, $00, $00, $00, $00, $4c, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $b3, $40
.byte $00, $00, $00, $00, $00, $00, $08, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $f7, $00
.byte $00, $00, $00, $00, $00, $10, $38, $ff, $ff, $ff, $ff, $ff, $ff, $ef, $c7, $18
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $fd, $ff, $ff, $cf, $ff, $ff, $ff, $ff
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $f7, $fd, $ff, $ff, $ff
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $cf, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $f7, $fb, $e6, $ff, $ff
.byte $c0, $c0, $c0, $c0, $c0, $c0, $c0, $c0, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $ff, $ff, $fd, $f9, $f3, $f3, $00, $40, $48, $08, $22, $26, $4d, $6f
.byte $c0, $c0, $e0, $e0, $e0, $e0, $a2, $24, $00, $00, $00, $00, $00, $00, $42, $d4
.byte $e2, $62, $22, $20, $20, $00, $00, $00, $7f, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $2c, $64, $64, $60, $40, $40, $00, $00, $de, $9f, $bf, $ff, $ff, $ff, $ff, $ff
.byte $bb, $9b, $99, $18, $10, $00, $00, $00, $dd, $ed, $ef, $ef, $ef, $ff, $ff, $ff
.byte $17, $06, $06, $06, $04, $04, $00, $00, $fb, $fb, $fb, $fb, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $01, $02, $00, $00, $00, $00, $00, $00, $01, $03
.byte $00, $00, $00, $00, $00, $c0, $00, $00, $00, $01, $1d, $3f, $1f, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $19, $bb, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $02, $01, $01, $80, $80, $60, $f8, $f8, $f6, $ff, $ff
.byte $03, $02, $06, $07, $01, $02, $07, $06, $03, $03, $07, $07, $01, $03, $07, $06
.byte $00, $00, $00, $80, $00, $00, $c0, $88, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $01, $03, $00, $00, $00, $01, $00, $04, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $80, $c0, $60, $e0, $c0, $80, $c0, $00, $80, $c0, $e0, $e0, $c0, $80, $c0
.byte $01, $01, $00, $00, $00, $00, $00, $00, $01, $01, $00, $00, $00, $00, $00, $00
.byte $90, $f0, $b9, $7f, $6f, $0e, $04, $00, $ff, $ff, $bf, $7f, $6f, $0e, $04, $00
.byte $00, $81, $91, $bb, $ef, $ef, $66, $26, $ff, $ff, $ff, $ff, $ef, $ef, $46, $00
.byte $03, $02, $8a, $cf, $7b, $30, $10, $00, $ff, $fe, $fe, $ff, $7b, $30, $10, $00
.byte $c0, $c0, $00, $00, $00, $00, $00, $00, $c0, $c0, $00, $00, $00, $00, $00, $00
.byte $36, $16, $1e, $0e, $0e, $0f, $0f, $c7, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $00, $00, $00, $00, $02, $01, $01, $00, $40, $e0, $e8, $fc, $fe, $ff, $ff
.byte $7f, $3f, $07, $07, $03, $03, $03, $03, $00, $00, $00, $00, $00, $00, $00, $00
.byte $03, $80, $81, $82, $c3, $c1, $c0, $c0, $03, $00, $01, $03, $03, $01, $00, $00
.byte $00, $00, $00, $00, $00, $00, $00, $22, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $02, $01, $03, $0e, $04, $06, $1e, $24, $fe, $ff, $ff, $fe, $fc, $fe, $fe, $f4
.byte $01, $01, $01, $01, $01, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
.byte $e0, $e0, $e0, $e0, $c0, $20, $00, $80, $00, $00, $06, $1f, $3f, $df, $ff, $7f
.byte $0f, $07, $06, $06, $03, $04, $00, $00, $0f, $05, $c0, $d8, $fc, $fb, $ff, $ff
.byte $77, $ff, $fe, $ec, $80, $00, $00, $00, $ff, $ff, $de, $0c, $00, $00, $80, $80
.byte $70, $c0, $c0, $00, $00, $00, $00, $00, $f0, $c0, $c0, $00, $00, $00, $00, $00
.byte $00, $00, $00, $00, $01, $00, $01, $02, $00, $00, $00, $00, $01, $00, $01, $03
.byte $00, $00, $00, $00, $00, $80, $00, $00, $03, $1b, $3f, $df, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $18, $bb, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $02, $01, $40, $21, $61, $10, $18, $01, $83, $01, $c0, $e1, $e1, $d0, $f8
.byte $00, $00, $80, $00, $20, $e4, $ff, $7f, $ff, $ff, $ff, $ff, $ff, $ff, $bf, $37
.byte $00, $00, $00, $00, $82, $89, $de, $f6, $ff, $ff, $ff, $ff, $ff, $ff, $fe, $76
.byte $00, $00, $00, $40, $80, $00, $00, $00, $00, $80, $c0, $c0, $80, $00, $00, $00
.byte $03, $00, $01, $02, $03, $01, $00, $00, $03, $00, $01, $03, $03, $01, $00, $00
.byte $80, $80, $00, $20, $c0, $88, $79, $6f, $ff, $ff, $ff, $ff, $ff, $bf, $7f, $6f
.byte $00, $00, $00, $00, $00, $02, $11, $39, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $38, $10, $18, $58, $38, $20, $f0, $a0, $f8, $f0, $f8, $f8, $f8, $e0, $f0, $a0
.byte $7b, $79, $79, $7b, $7b, $7b, $7f, $7f, $02, $00, $00, $00, $00, $00, $00, $00
.byte $e0, $c0, $c0, $c0, $c0, $80, $80, $80, $20, $00, $00, $00, $00, $00, $00, $00
.byte $0f, $05, $00, $00, $00, $00, $00, $00, $0f, $05, $00, $00, $00, $00, $00, $00
.byte $fe, $ef, $e5, $39, $0f, $03, $00, $00, $fe, $ee, $c4, $00, $00, $00, $00, $00
.byte $c0, $c0, $80, $80, $c0, $c0, $e0, $e0, $c0, $c0, $00, $00, $00, $00, $00, $00
.byte $7f, $7f, $7f, $7f, $7e, $7e, $7e, $7e, $00, $00, $00, $00, $20, $00, $00, $00
.byte $70, $78, $38, $3c, $1e, $1f, $0f, $0f, $00, $00, $00, $00, $00, $00, $00, $00
.byte $7e, $7e, $7e, $fe, $fe, $ff, $ff, $ff, $00, $20, $20, $00, $40, $40, $00, $00
.byte $90, $f0, $b9, $7f, $6f, $0f, $1f, $3e, $ff, $ff, $bf, $7f, $6f, $0e, $04, $00
.byte $00, $81, $91, $bb, $ef, $ef, $46, $00, $ff, $ff, $ff, $ff, $ef, $ef, $46, $00
.byte $07, $07, $03, $03, $01, $01, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $00, $00, $00, $00, $40, $40, $00, $10
.byte $00, $00, $01, $03, $07, $0f, $9f, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $78, $f0, $fc, $ff, $e0, $c0, $80, $80, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $7f, $7f, $7f, $7f, $7f, $7f, $10, $00, $20, $20, $00, $00, $00, $08
.byte $ff, $fe, $fe, $fc, $f8, $f8, $f0, $f0, $00, $00, $00, $00, $00, $00, $00, $00
.byte $7f, $7f, $7f, $7f, $7f, $7f, $7f, $7f, $00, $20, $20, $00, $00, $00, $10, $10
.byte $f0, $e0, $e0, $c0, $c0, $c0, $c0, $c0, $00, $00, $00, $00, $00, $00, $00, $00
.byte $66, $fe, $ce, $ce, $e7, $77, $73, $73, $66, $ee, $56, $56, $7b, $fb, $bd, $bd
.byte $e5, $c7, $c7, $c6, $c6, $c4, $84, $84, $e9, $db, $db, $fb, $ff, $ff, $ff, $ff
.byte $2e, $46, $4f, $4f, $4f, $5e, $4c, $08, $4e, $86, $87, $d7, $f7, $ef, $ff, $ff
.byte $dd, $7d, $6f, $66, $b6, $b2, $90, $90, $cd, $6d, $77, $fb, $fb, $ff, $ff, $ff
.byte $08, $00, $20, $62, $22, $20, $00, $00, $90, $99, $bd, $ff, $ff, $ff, $ff, $ff
.byte $11, $10, $08, $08, $01, $01, $41, $41, $a2, $a7, $bf, $ff, $ff, $ff, $ff, $ff
.byte $20, $a8, $88, $84, $0a, $02, $00, $00, $01, $c1, $e1, $e9, $ff, $ff, $ff, $ff
.byte $08, $84, $84, $60, $20, $20, $10, $10, $31, $19, $19, $bd, $ff, $ff, $ff, $ff
.byte $01, $03, $05, $07, $0b, $1f, $37, $3b, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $80, $80, $e0, $d0, $f0, $f0, $f8, $ec, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $03, $06, $0b, $1f, $1d, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $80, $c0, $e0, $c0, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $1f, $2f, $7f, $3d, $df, $f7, $7f, $5f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $fc, $f8, $f4, $fe, $fe, $fc, $fe, $fb, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $0b, $1f, $2f, $3f, $5b, $ef, $fe, $7f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $e0, $d0, $f8, $f0, $f8, $f4, $fc, $ee, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $bf, $ef, $ff, $7f, $5b, $2f, $3b, $0f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $fe, $ee, $fa, $fc, $f4, $f8, $ec, $f8, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $5f, $f7, $7f, $3f, $6f, $5b, $3e, $17, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $fe, $f4, $f8, $fc, $b4, $d8, $f8, $d0, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $03, $01, $01, $01, $01, $01, $01, $01, $ff, $fe, $fe, $fe, $fe, $fe, $fe, $fe
.byte $e0, $80, $80, $80, $80, $80, $80, $c0, $7f, $7f, $7f, $7f, $7f, $7f, $7f, $7f
.byte $e0, $c0, $80, $80, $80, $80, $80, $80, $ff, $ff, $7f, $7f, $7f, $7f, $7f, $7f
.byte $08, $0c, $14, $3e, $5e, $7d, $3e, $5f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $10, $38, $5c, $7c, $fa, $5e, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $3d, $2e, $7e, $2c, $08, $08, $08, $08, $ff, $ff, $ff, $ff, $f7, $f7, $f7, $f7
.byte $ff, $ed, $be, $7c, $38, $10, $10, $10, $ff, $ff, $ff, $ff, $ff, $ef, $ef, $ef
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01, $07, $0f, $0f, $1f
.byte $00, $00, $00, $00, $00, $00, $00, $00, $07, $0f, $3f, $ff, $ff, $ff, $ff, $ff
.byte $60, $38, $0e, $0f, $1f, $03, $01, $00, $e0, $f8, $fe, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01, $07, $0f, $3f, $7f, $7f
.byte $00, $00, $00, $00, $00, $00, $00, $00, $3f, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $03, $07, $1f, $3f, $7f
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $03, $07, $ef, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $03, $3f, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $03, $07, $1f, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $ff, $00, $ff, $ff, $00, $ff, $ff, $ff, $00, $ff, $00, $00, $ff, $00, $00, $00
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $18, $0c, $07, $07, $0f, $1f, $03, $00, $f8, $fc, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $80, $f0, $fc, $fe, $ff, $00, $00, $00, $80, $f0, $fc, $fe, $ff
.byte $80, $f0, $f8, $fe, $ff, $0f, $03, $00, $80, $f0, $f8, $fe, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $f0, $fc, $ff, $ff, $00, $00, $00, $00, $f0, $fc, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $c0, $f0, $00, $00, $00, $00, $00, $00, $c0, $ff
.byte $7f, $38, $00, $00, $00, $00, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $e0, $38, $0f, $07, $07, $0f, $03, $00, $e0, $f8, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $f8, $ff, $00, $00, $00, $00, $00, $00, $f8, $ff
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $e0, $f0, $f8, $ff, $ff, $00, $00, $00, $e0, $f0, $f8, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $38, $fe, $00, $00, $00, $00, $00, $00, $38, $fe
.byte $1f, $07, $07, $0f, $1f, $03, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $ff, $ff, $ff, $ff, $ff, $ff, $7f, $1f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $80, $c0, $e0, $f0, $f8, $fc, $ff, $00, $80, $c0, $e0, $f0, $f8, $fc, $ff
.byte $03, $01, $03, $1f, $0f, $00, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $ff, $ff, $ff, $ff, $ff, $3f, $07, $01, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $80, $f0, $f8, $fe, $ff, $ff, $ff, $ff, $80, $f0, $f8, $fe, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $c0, $f0, $f8, $fe, $00, $00, $00, $00, $c0, $f0, $f8, $fe
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $03, $07, $1f
.byte $ff, $3f, $1f, $07, $07, $0f, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $80, $e0, $f0, $fc, $ff, $ff, $ff, $ff, $80, $e0, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $80, $c0, $e0, $3f, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $ff, $7f, $3f, $3f, $1f, $1f, $1f, $3f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $f8, $fc, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $c0, $f0, $fc, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $01, $51, $31, $00, $00, $00, $00, $00, $00, $12, $52
.byte $00, $00, $00, $00, $10, $22, $2b, $9b, $00, $00, $00, $00, $00, $02, $49, $dd
.byte $ff, $ff, $df, $bf, $bf, $ff, $ff, $ff, $00, $38, $7c, $fe, $fe, $fe, $7c, $38
.byte $ff, $c7, $83, $01, $01, $01, $83, $c7, $00, $38, $7c, $fe, $fe, $fe, $7c, $38
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $00, $70, $f0, $30, $76, $fe, $fc, $78
.byte $ff, $8f, $0f, $cf, $89, $01, $03, $87, $00, $70, $f0, $30, $76, $fe, $fc, $78
.byte $ff, $ff, $55, $55, $55, $55, $55, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $10, $10, $10, $10, $10, $10, $10, $10
.byte $ff, $ef, $ef, $ef, $ef, $ff, $ef, $ff, $18, $2c, $2c, $2c, $2c, $00, $2c, $00
.byte $ff, $84, $9c, $84, $e4, $e4, $84, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $90, $92, $12, $92, $92, $90, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $43, $67, $67, $67, $67, $67, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $c0, $e0, $f0, $f8, $fc, $fe, $ff, $ff, $3f, $9f, $cf, $e7, $f3, $f9, $fc, $fe
.byte $00, $00, $00, $00, $00, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $00
.byte $03, $07, $0f, $1f, $3f, $7f, $ff, $ff, $fc, $f9, $f3, $e7, $cf, $9f, $3f, $7f
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $ff, $ff, $ff, $fc, $f9, $fb, $ff, $ff, $ff, $ff, $ff, $ff, $fe, $fc
.byte $ff, $ff, $ff, $ff, $ff, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $00, $00
.byte $ff, $ff, $ff, $ff, $ff, $7f, $3f, $bf, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $7f
.byte $fb, $fb, $fb, $fb, $fb, $fb, $fb, $fb, $fc, $fc, $fc, $fc, $fc, $fc, $fc, $fc
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
.byte $bf, $bf, $bf, $bf, $bf, $bf, $bf, $bf, $7f, $7f, $7f, $7f, $7f, $7f, $7f, $7f
.byte $f9, $fc, $ff, $ff, $ff, $ff, $ff, $ff, $fe, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $ff, $00, $ff, $ff, $ff, $ff, $ff, $ff, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $3f, $7f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $03, $1f, $ff, $ff, $ff, $ff
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01, $07, $1f
.byte $1f, $0f, $0f, $1f, $01, $00, $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff
.byte $ff, $ff, $ff, $ff, $93, $93, $f7, $ff, $00, $00, $00, $00, $6c, $6c, $08, $00
.byte $ff, $ff, $ff, $ff, $9f, $9f, $ff, $ff, $00, $00, $00, $00, $60, $60, $00, $00
.byte $e0, $f8, $fc, $fe, $fe, $ff, $ff, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $ff, $fe, $fe, $fc, $f8, $e0, $00, $00, $00, $00, $00, $00, $00, $00
.byte $07, $1f, $3f, $7f, $7f, $ff, $ff, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $ff, $7f, $7f, $3f, $1f, $07, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $00, $00, $00, $00, $81, $81, $c3, $00, $00, $00, $00, $00, $00, $00, $00
.byte $c3, $81, $81, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $ff, $ff, $ff, $ff, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $00, $ff, $ff, $ff, $ff, $ff, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $00, $01, $01, $03, $03, $07, $1f, $00, $00, $00, $00, $00, $00, $00, $00
.byte $1f, $07, $03, $01, $01, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $00, $00, $00, $ff, $ff, $ff, $ff, $00, $00, $00, $00, $00, $00, $00, $00
.byte $00, $00, $00, $00, $00, $00, $00, $00, $ff, $ff, $00, $00, $00, $00, $00, $00
.byte $ff, $ff, $ff, $00, $00, $00, $00, $00, $00, $00, $00, $ff, $00, $00, $00, $00
.byte $e0, $c0, $80, $00, $00, $00, $00, $00, $10, $30, $60, $c0, $00, $00, $00, $00
.byte $99, $99, $99, $bb, $ff, $33, $33, $ff, $66, $66, $66, $44, $00, $cc, $cc, $00
.byte $00, $00, $00, $00, $03, $07, $0f, $0f, $00, $00, $00, $07, $0c, $18, $10, $10
