
;----------------------------------------------------
;  Copyright (c) 2003-2013 SONiX Technology Co., Ltd.
;  Sonix SN8 C Compiler - V2.01
;----------------------------------------------------

__INTERRUPT_BACKUP_X EQU 1
__INTERRUPT_BACKUP_Y EQU 1
__INTERRUPT_BACKUP_Z EQU 1
__INTERRUPT_BACKUP_R EQU 1
__INTERRUPT_BACKUP_H EQU 1
__INTERRUPT_BACKUP_L EQU 1
CHIP SN8P2501B

INCLUDE <sncc_macros.h>
EXTERN DATA T
EXTERN DATA I
.CODE
PUBLIC _Sys_Init
PUBLIC _Delayms
PUBLIC _Delayms_arg@0
PUBLIC _TimeDeal
PUBLIC _ZhiJDeal
PUBLIC _KeyeDeal
PUBLIC _AdccDeal
PUBLIC _main
PUBLIC _ISR_isr
PUBLIC _RS_Cnt
_RS_Cnt@segment SEGMENT DATA INBANK
	_RS_Cnt DS 1
PUBLIC _RT_Cnt
_RT_Cnt@segment SEGMENT DATA INBANK
	_RT_Cnt DS 1
PUBLIC _AD_value
_AD_value@segment SEGMENT DATA INBANK
	_AD_value DS 1
PUBLIC _AD_Cnt
_AD_Cnt@segment SEGMENT DATA INBANK
	_AD_Cnt DS 1
PUBLIC _JS1
_JS1@segment SEGMENT DATA INBANK
	_JS1 DS 1
PUBLIC _Funflag1
_Funflag1@segment SEGMENT DATA INBANK
	_Funflag1 DS 1
PUBLIC _Funflag0
_Funflag0@segment SEGMENT DATA INBANK
	_Funflag0 DS 1
PUBLIC _WorkGear
_WorkGear@segment SEGMENT DATA INBANK
	_WorkGear DS 1
PUBLIC _WorkBuff
_WorkBuff@segment SEGMENT DATA INBANK
	_WorkBuff DS 1
PUBLIC _Worktime
_Worktime@segment SEGMENT DATA INBANK
	_Worktime DS 1
PUBLIC _TimerCnt
_TimerCnt@segment SEGMENT DATA INBANK
	_TimerCnt DS 1
PUBLIC _SDian_bz
_SDian_bz@segment BITSEGMENT DATA AT 46 INBANK
	_SDian_bz DSBIT 1
PUBLIC _SDian_Cnt
_SDian_Cnt@segment SEGMENT DATA AT 47 INBANK
	_SDian_Cnt DS 1

_Function_Sys_Init_data SEGMENT DATA INBANK

_Function_Delayms_data SEGMENT DATA INBANK
	_Delayms_arg@0 DS 1
	_Delayms_data@0	DS	1
	_Delayms_data@1	DS	1

_Function_TimeDeal_data SEGMENT DATA INBANK

_Function_ZhiJDeal_data SEGMENT DATA INBANK

_Function_KeyeDeal_data SEGMENT DATA INBANK

_Function_AdccDeal_data SEGMENT DATA INBANK

_Function_main_data SEGMENT DATA INBANK

_DEFINE_ISRBACKUP_DATA 2
_Function_ISR_isr_data SEGMENT DATA INBANK


_VirtualReg SEGMENT DATA BANK 0 INBANK COMMON
	W0 DS 1

_Function_Sys_Init_code SEGMENT CODE INBANK USING _Function_Sys_Init_data
_Sys_Init:
;Enter line
	;MOVU1 0xCA ,#0
	__SelectBANKCNST 0
	CLR (0xCA & 0xFF)
	;MOVU1 0xC9 ,#0
	__SelectBANKCNST 0
	CLR (0xC9 & 0xFF)
	;MOVU1 0xC8 ,#0
	__SelectBANKCNST 0
	CLR (0xC8 & 0xFF)
	;MOVU1 0xB8 ,#255
	MOV A, #0xff
	B0MOV 0xB8, A
	;MOVU1 0xC2 ,#255
	B0MOV 0xC2, A
	;MOVU1 0xC1 ,#241
	MOV A, #0xf1
	B0MOV 0xC1, A
	;MOVU1 0xC5 ,#255
	MOV A, #0xff
	B0MOV 0xC5, A
	;MOVU1 0xE0 ,#0
	__SelectBANKCNST 0
	CLR (0xE0 & 0xFF)
	;MOVU1 0xE2 ,#0
	__SelectBANKCNST 0
	CLR (0xE2 & 0xFF)
	;MOVU1 0xE1 ,#12
	MOV A, #0x0c
	B0MOV 0xE1, A
	;MOVU1 0xE5 ,#0
	__SelectBANKCNST 0
	CLR (0xE5 & 0xFF)
	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
	;MOVU1 0xD8 ,#16
	MOV A, #0x10
	B0MOV 0xD8, A
	;MOVU1 0xD9 ,#0
	__SelectBANKCNST 0
	CLR (0xD9 & 0xFF)
	;MOVX1 0xC9.4 ,#1
	B0BSET 0xC9.4
	;MOVU1 0xDA ,#64
	MOV A, #0x40
	B0MOV 0xDA, A
	;MOVU1 0xCD ,#6
	MOV A, #0x06
	B0MOV 0xCD, A
	;MOVU1 0xDB ,#6
	B0MOV 0xDB, A
	;MOVX1 0xDA.2 ,#1
	B0BSET 0xDA.2
	;MOVX1 0xC9.5 ,#1
	B0BSET 0xC9.5
	;MOVX1 0xDA.7 ,#1
	B0BSET 0xDA.7
	;MOVX1 0xDF.7 ,#1
	B0BSET 0xDF.7
	;CALLV _ZhiJDeal
	CALL _ZhiJDeal
;Leave line
;Enter line
	;MOVU1 _Worktime ,#100
	MOV A, #0x64
	__SelectBANK _Worktime
	MOV _Worktime, A
	;MOVU1 _WorkBuff ,#0
	__SelectBANK _WorkBuff
	CLR _WorkBuff
	;NEI1 L2 ,_SDian_Cnt ,#2
	__SelectBANK _SDian_Cnt
	MOV A, _SDian_Cnt
	CMPRS A, #0x02
	JMP L2
;Leave line
;Enter line
	;EQ L4 ,_SDian_bz ,#0
	__SelectBANK _SDian_bz
	BTS1 _SDian_bz
	JMP L4
;Leave line
;Enter line
	;MOVU1 _SDian_Cnt ,#2
	MOV A, #0x02
	__SelectBANK _SDian_Cnt
	MOV _SDian_Cnt, A
;Leave line
;Enter line
	JMP L3
;Leave line
;Enter line
L4:
;Leave line
;Enter line
	;MOVU1 _SDian_Cnt ,#1
	MOV A, #0x01
	__SelectBANK _SDian_Cnt
	MOV _SDian_Cnt, A
;Leave line
;Enter line
	JMP L3
;Leave line
;Enter line
L2:
;Leave line
;Enter line
	;NEI1 L6 ,_SDian_Cnt ,#3
	__SelectBANK _SDian_Cnt
	MOV A, _SDian_Cnt
	CMPRS A, #0x03
	JMP L6
;Leave line
;Enter line
	;EQ L8 ,_SDian_bz ,#0
	__SelectBANK _SDian_bz
	BTS1 _SDian_bz
	JMP L8
;Leave line
;Enter line
	;MOVU1 _SDian_Cnt ,#3
	MOV A, #0x03
	__SelectBANK _SDian_Cnt
	MOV _SDian_Cnt, A
;Leave line
;Enter line
	JMP L7
;Leave line
;Enter line
L8:
;Leave line
;Enter line
	;MOVU1 _SDian_Cnt ,#1
	MOV A, #0x01
	__SelectBANK _SDian_Cnt
	MOV _SDian_Cnt, A
;Leave line
;Enter line
	JMP L7
;Leave line
;Enter line
L6:
;Leave line
;Enter line
	;NEI1 L10 ,_SDian_Cnt ,#4
	__SelectBANK _SDian_Cnt
	MOV A, _SDian_Cnt
	CMPRS A, #0x04
	JMP L10
;Leave line
;Enter line
	;EQ L12 ,_SDian_bz ,#0
	__SelectBANK _SDian_bz
	BTS1 _SDian_bz
	JMP L12
;Leave line
;Enter line
	;MOVU1 _SDian_Cnt ,#4
	MOV A, #0x04
	__SelectBANK _SDian_Cnt
	MOV _SDian_Cnt, A
;Leave line
;Enter line
	JMP L11
;Leave line
;Enter line
L12:
;Leave line
;Enter line
	;MOVU1 _SDian_Cnt ,#1
	MOV A, #0x01
	__SelectBANK _SDian_Cnt
	MOV _SDian_Cnt, A
;Leave line
;Enter line
	JMP L11
;Leave line
;Enter line
L10:
;Leave line
;Enter line
	;MOVU1 _SDian_Cnt ,#1
	MOV A, #0x01
	__SelectBANK _SDian_Cnt
	MOV _SDian_Cnt, A
	;MOVX1 _SDian_bz ,#1
	__SelectBANK _SDian_bz
	BSET _SDian_bz
;Leave line
;Enter line
L11:
;Leave line
;Enter line
L7:
;Leave line
;Enter line
L3:
;Leave line
;Enter line
L1:
;Leave line
	RET

CALLTREE _Sys_Init invoke _ZhiJDeal

_Function_Delayms_code SEGMENT CODE INBANK USING _Function_Delayms_data
_Delayms:
;Enter line
	;MOVU1 _Delayms_data@0 ,#0
	__SelectBANK _Delayms_data@0
	CLR _Delayms_data@0
;Leave line
;Enter line
	JMP L18
;Leave line
;Enter line
L15:
;Leave line
;Enter line
	;MOVU1 _Delayms_data@1 ,#100
	MOV A, #0x64
	__SelectBANK _Delayms_data@1
	MOV _Delayms_data@1, A
;Leave line
;Enter line
	JMP L22
;Leave line
;Enter line
L19:
;Leave line
;Enter line
L20:
;Leave line
;Enter line
	;SUBU1 _Delayms_data@1 ,_Delayms_data@1 ,#1
	__SelectBANK _Delayms_data@1
	DECMS _Delayms_data@1
	NOP
;Leave line
;Enter line
L22:
;Leave line
;Enter line
	;NEI1 L19 ,_Delayms_data@1 ,#0
	__SelectBANK _Delayms_data@1
	MOV A, _Delayms_data@1
	CMPRS A, #0x00
	JMP L19
;Leave line
;Enter line
L16:
;Leave line
;Enter line
	;ADDU1 _Delayms_data@0 ,_Delayms_data@0 ,#1
	__SelectBANK _Delayms_data@0
	INCMS _Delayms_data@0
	NOP
;Leave line
;Enter line
L18:
;Leave line
;Enter line
	;LT L15 ,_Delayms_data@0 ,_Delayms_arg@0
	__SelectBANK _Delayms_data@0
	MOV A, _Delayms_data@0
	__SelectBANK _Delayms_arg@0
	SUB A, _Delayms_arg@0
	JLT L15
;Leave line
;Enter line
L14:
;Leave line
	RET
_Function_TimeDeal_code SEGMENT CODE INBANK USING _Function_TimeDeal_data
_TimeDeal:
;Enter line
	;LT L24 ,_WorkBuff ,#40
	__SelectBANK _WorkBuff
	MOV A, _WorkBuff
	SUB A, #0x28
	JLT L24
;Leave line
;Enter line
	;EQ L26 ,_Funflag1.1 ,#0
	__SelectBANK _Funflag1
	BTS1 _Funflag1.1
	JMP L26
;Leave line
;Enter line
	;MOVX1 _Funflag1.2 ,#1
	BSET _Funflag1.2
;Leave line
;Enter line
L26:
;Leave line
;Enter line
L24:
;Leave line
;Enter line
	;LT L28 ,_WorkBuff ,_Worktime
	__SelectBANK _WorkBuff
	MOV A, _WorkBuff
	__SelectBANK _Worktime
	SUB A, _Worktime
	JLT L28
;Leave line
;Enter line
	;ADDU1 _SDian_Cnt ,_SDian_Cnt ,#1
	__SelectBANK _SDian_Cnt
	INCMS _SDian_Cnt
	NOP
	;LT L30 ,_SDian_Cnt ,#4
	MOV A, _SDian_Cnt
	SUB A, #0x04
	JLT L30
;Leave line
;Enter line
	;MOVU1 _SDian_Cnt ,#4
	MOV A, #0x04
	MOV _SDian_Cnt, A
;Leave line
;Enter line
L30:
;Leave line
;Enter line
	;MOVX1 _Funflag1.2 ,#1
	__SelectBANK _Funflag1
	BSET _Funflag1.2
;Leave line
;Enter line
L28:
;Leave line
;Enter line
L23:
;Leave line
	RET
_Function_ZhiJDeal_code SEGMENT CODE INBANK USING _Function_ZhiJDeal_data
_ZhiJDeal:
;Enter line
	;PUSH _Delayms_arg@0 ,#1
	MOV A, #0x01
	__SelectBANK _Delayms_arg@0
	MOV _Delayms_arg@0, A
	;CALLV _Delayms
	CALL _Delayms
;Leave line
;Enter line
L33:
;Leave line
;Enter line
	;EQ L36 ,0xD1.2 ,#0
	B0BTS1 0xD1.2
	JMP L36
;Leave line
;Enter line
L36:
;Leave line
;Enter line
	;EQ L38 ,0xD1.3 ,#0
	B0BTS1 0xD1.3
	JMP L38
;Leave line
;Enter line
L38:
;Leave line
;Enter line
	;PUSH _Delayms_arg@0 ,#1
	MOV A, #0x01
	__SelectBANK _Delayms_arg@0
	MOV _Delayms_arg@0, A
	;CALLV _Delayms
	CALL _Delayms
;Leave line
;Enter line
	;EQ L40 ,0xD1.2 ,#0
	B0BTS1 0xD1.2
	JMP L40
;Leave line
;Enter line
	JMP L35
;Leave line
;Enter line
L40:
;Leave line
;Enter line
	;EQ L42 ,0xD1.3 ,#0
	B0BTS1 0xD1.3
	JMP L42
;Leave line
;Enter line
	JMP L35
;Leave line
;Enter line
L42:
;Leave line
;Enter line
	;MOVX1 _Funflag0.7 ,#1
	__SelectBANK _Funflag0
	BSET _Funflag0.7
	;MOVX1 0xC1.2 ,#1
	B0BSET 0xC1.2
	;MOVX1 0xC1.3 ,#1
	B0BSET 0xC1.3
;Leave line
;Enter line
	JMP L35
;Leave line
;Enter line
L34:
;Leave line
;Enter line
	JMP L33
;Leave line
;Enter line
L35:
;Leave line
;Enter line
L32:
;Leave line
	RET

CALLTREE _ZhiJDeal invoke _Delayms

_Function_KeyeDeal_code SEGMENT CODE INBANK USING _Function_KeyeDeal_data
_KeyeDeal:
;Enter line
	;ORX1 X.7 ,_Funflag0.5 ,_Funflag1.0
	__SelectBANK _Funflag0
	BTS0 _Funflag0.5
	JMP L129
	__SelectBANK _Funflag1
	BTS0 _Funflag1.0
	JMP L129
	__SelectBANKCNST 0
	BCLR X.7
	JMP L130
L129:
	__SelectBANKCNST 0
	BSET X.7
L130:
	;EQ L45 ,X.7 ,#0
	__SelectBANKCNST 0
	BTS1 X.7
	JMP L45
;Leave line
;Enter line
L45:
;Leave line
;Enter line
L46:
;Leave line
;Enter line
L44:
;Leave line
	RET
_Function_AdccDeal_code SEGMENT CODE INBANK USING _Function_AdccDeal_data
_AdccDeal:
;Enter line
	;EQ L48 ,_Funflag1.1 ,#0
	__SelectBANK _Funflag1
	BTS1 _Funflag1.1
	JMP L48
;Leave line
;Enter line
	JMP L47
;Leave line
;Enter line
L48:
;Leave line
;Enter line
	;NEX1 L50 ,_Funflag0.1 ,#0
	__SelectBANK _Funflag0
	BTS0 _Funflag0.1
	JMP L50
;Leave line
;Enter line
	;MOVX1 _Funflag0.1 ,#1
	BSET _Funflag0.1
	;MOVX1 0xB8.0 ,#0
	B0BCLR 0xB8.0
	;MOVX1 0xC1.0 ,#1
	B0BSET 0xC1.0
	;MOVX1 0xD1.0 ,#0
	B0BCLR 0xD1.0
	;PUSH _Delayms_arg@0 ,#2
	MOV A, #0x02
	__SelectBANK _Delayms_arg@0
	MOV _Delayms_arg@0, A
	;CALLV _Delayms
	CALL _Delayms
;Leave line
;Enter line
	JMP L51
;Leave line
;Enter line
L50:
;Leave line
;Enter line
	;NEX1 L52 ,_Funflag0.2 ,#0
	__SelectBANK _Funflag0
	BTS0 _Funflag0.2
	JMP L52
;Leave line
;Enter line
	;MOVU1 0xD9 ,#0
	__SelectBANKCNST 0
	CLR (0xD9 & 0xFF)
	;MOVX1 0xC1.0 ,#0
	B0BCLR 0xC1.0
	;MOVX1 0xB8.0 ,#1
	B0BSET 0xB8.0
	;MOVX1 0xD0.0 ,#1
	B0BSET 0xD0.0
	;MOVX1 0xD8.7 ,#1
	B0BSET 0xD8.7
	_NOP 1 

;Leave line
;Enter line
	_NOP 1 

;Leave line
;Enter line
L54:
;Leave line
;Enter line
	;MOVU1 0xCC ,#90
	MOV A, #0x5a
	B0MOV 0xCC, A
	;LE L57 ,_JS1 ,#20
	__SelectBANK _JS1
	MOV A, _JS1
	CMPRS A, #0x14
	JLT L57
;Leave line
;Enter line
	JMP L56
;Leave line
;Enter line
L57:
;Leave line
;Enter line
	;EQ L59 ,0xD1.0 ,#0
	B0BTS1 0xD1.0
	JMP L59
;Leave line
;Enter line
	JMP L56
;Leave line
;Enter line
L59:
;Leave line
;Enter line
L55:
;Leave line
;Enter line
	JMP L54
;Leave line
;Enter line
L56:
;Leave line
;Enter line
	;MOVX1 0xD8.7 ,#0
	B0BCLR 0xD8.7
	;ADDU1 _RS_Cnt ,_RS_Cnt ,0xD9
	B0MOV A, 0xD9
	__SelectBANK _RS_Cnt
	ADD _RS_Cnt, A
	;MOVU1 0xD9 ,#0
	__SelectBANKCNST 0
	CLR (0xD9 & 0xFF)
	;MOVU1 _JS1 ,#0
	__SelectBANK _JS1
	CLR _JS1
	;MOVX1 0xB8.0 ,#0
	B0BCLR 0xB8.0
	;MOVX1 0xC1.0 ,#1
	B0BSET 0xC1.0
	;MOVX1 0xD1.0 ,#0
	B0BCLR 0xD1.0
	;MOVX1 _Funflag0.2 ,#1
	__SelectBANK _Funflag0
	BSET _Funflag0.2
;Leave line
;Enter line
	JMP L53
;Leave line
;Enter line
L52:
;Leave line
;Enter line
	;NEX1 L61 ,_Funflag0.3 ,#0
	__SelectBANK _Funflag0
	BTS0 _Funflag0.3
	JMP L61
;Leave line
;Enter line
	;MOVX1 _Funflag0.3 ,#1
	BSET _Funflag0.3
	;MOVX1 0xB8.0 ,#0
	B0BCLR 0xB8.0
	;MOVX1 0xC1.0 ,#1
	B0BSET 0xC1.0
	;MOVX1 0xD1.0 ,#0
	B0BCLR 0xD1.0
	;PUSH _Delayms_arg@0 ,#2
	MOV A, #0x02
	__SelectBANK _Delayms_arg@0
	MOV _Delayms_arg@0, A
	;CALLV _Delayms
	CALL _Delayms
;Leave line
;Enter line
	JMP L62
;Leave line
;Enter line
L61:
;Leave line
;Enter line
	;NEX1 L63 ,_Funflag0.4 ,#0
	__SelectBANK _Funflag0
	BTS0 _Funflag0.4
	JMP L63
;Leave line
;Enter line
	;MOVU1 0xD9 ,#0
	__SelectBANKCNST 0
	CLR (0xD9 & 0xFF)
	;MOVX1 0xC1.0 ,#0
	B0BCLR 0xC1.0
	;MOVX1 0xB8.0 ,#0
	B0BCLR 0xB8.0
	;MOVX1 0xD8.7 ,#1
	B0BSET 0xD8.7
	_NOP 1 

;Leave line
;Enter line
	_NOP 1 

;Leave line
;Enter line
L65:
;Leave line
;Enter line
	;MOVU1 0xCC ,#90
	MOV A, #0x5a
	B0MOV 0xCC, A
	;LE L68 ,_JS1 ,#20
	__SelectBANK _JS1
	MOV A, _JS1
	CMPRS A, #0x14
	JLT L68
;Leave line
;Enter line
	JMP L67
;Leave line
;Enter line
L68:
;Leave line
;Enter line
	;EQ L70 ,0xD1.0 ,#0
	B0BTS1 0xD1.0
	JMP L70
;Leave line
;Enter line
	JMP L67
;Leave line
;Enter line
L70:
;Leave line
;Enter line
L66:
;Leave line
;Enter line
	JMP L65
;Leave line
;Enter line
L67:
;Leave line
;Enter line
	;MOVX1 0xD8.7 ,#0
	B0BCLR 0xD8.7
	;ADDU1 _RT_Cnt ,_RT_Cnt ,0xD9
	B0MOV A, 0xD9
	__SelectBANK _RT_Cnt
	ADD _RT_Cnt, A
	;MOVU1 _JS1 ,#0
	__SelectBANK _JS1
	CLR _JS1
	;MOVU1 0xD9 ,#0
	__SelectBANKCNST 0
	CLR (0xD9 & 0xFF)
	;MOVX1 0xB8.0 ,#0
	B0BCLR 0xB8.0
	;MOVX1 0xC1.0 ,#1
	B0BSET 0xC1.0
	;MOVX1 0xD1.0 ,#0
	B0BCLR 0xD1.0
	;MOVX1 _Funflag0.4 ,#1
	__SelectBANK _Funflag0
	BSET _Funflag0.4
;Leave line
;Enter line
	JMP L64
;Leave line
;Enter line
L63:
;Leave line
;Enter line
	;ADDU1 _AD_Cnt ,_AD_Cnt ,#1
	__SelectBANK _AD_Cnt
	INCMS _AD_Cnt
	NOP
	;NEI1 L72 ,_AD_Cnt ,#8
	MOV A, _AD_Cnt
	CMPRS A, #0x08
	JMP L72
;Leave line
;Enter line
	;MOVU1 _AD_Cnt ,#0
	CLR _AD_Cnt
	;RSH _RT_Cnt ,_RT_Cnt ,#3
	__SelectBANK _RT_Cnt
	RRCM _RT_Cnt
	RRCM _RT_Cnt
	RRCM _RT_Cnt
	MOV A, #0x1F
	AND _RT_Cnt, A
	;RSH _RS_Cnt ,_RS_Cnt ,#3
	__SelectBANK _RS_Cnt
	RRCM _RS_Cnt
	RRCM _RS_Cnt
	RRCM _RS_Cnt
	AND _RS_Cnt, A
	;MUL W0 ,#230 ,_RS_Cnt
	MOV A, #0xe6
	B0MOV L, A
	MOV A, _RS_Cnt
	CALL __MulInt2Reg
	;DIV _AD_value ,W0 ,_RT_Cnt
	__SelectBANK __SrcLArg0
	MOV __SrcLArg0, A
	__SelectBANK _RT_Cnt
	MOV A, _RT_Cnt
	__SelectBANK __SrcRArg0
	MOV __SrcRArg0, A
	MOV A, #(_AD_value)$M
	B0MOV H, A
	MOV A, #(_AD_value)$L
	B0MOV L, A
	CALL __DivUInt2Ram
	;LT L74 ,_AD_value ,#227
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0xe3
	JLT L74
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#1
	MOV A, #0x01
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L75 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L75
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
;Leave line
;Enter line
	JMP L75
;Leave line
;Enter line
L74:
;Leave line
;Enter line
	;LT L78 ,_AD_value ,#206
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0xce
	JLT L78
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#2
	MOV A, #0x02
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L79 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L79
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
;Leave line
;Enter line
	JMP L79
;Leave line
;Enter line
L78:
;Leave line
;Enter line
	;LT L82 ,_AD_value ,#173
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0xad
	JLT L82
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#3
	MOV A, #0x03
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L83 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L83
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#0
	B0BCLR 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
;Leave line
;Enter line
	JMP L83
;Leave line
;Enter line
L82:
;Leave line
;Enter line
	;LT L86 ,_AD_value ,#155
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0x9b
	JLT L86
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#4
	MOV A, #0x04
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L87 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L87
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
;Leave line
;Enter line
	JMP L87
;Leave line
;Enter line
L86:
;Leave line
;Enter line
	;LT L90 ,_AD_value ,#125
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0x7d
	JLT L90
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#5
	MOV A, #0x05
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L91 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L91
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
;Leave line
;Enter line
	JMP L91
;Leave line
;Enter line
L90:
;Leave line
;Enter line
	;LT L94 ,_AD_value ,#103
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0x67
	JLT L94
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#6
	MOV A, #0x06
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L95 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L95
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#0
	B0BCLR 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
;Leave line
;Enter line
	JMP L95
;Leave line
;Enter line
L94:
;Leave line
;Enter line
	;LT L98 ,_AD_value ,#75
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0x4b
	JLT L98
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#7
	MOV A, #0x07
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L99 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L99
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
;Leave line
;Enter line
	JMP L99
;Leave line
;Enter line
L98:
;Leave line
;Enter line
	;LT L102 ,_AD_value ,#56
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0x38
	JLT L102
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#8
	MOV A, #0x08
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L103 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L103
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
;Leave line
;Enter line
	JMP L103
;Leave line
;Enter line
L102:
;Leave line
;Enter line
	;LT L106 ,_AD_value ,#22
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0x16
	JLT L106
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#9
	MOV A, #0x09
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L107 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L107
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#0
	B0BCLR 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
;Leave line
;Enter line
	JMP L107
;Leave line
;Enter line
L106:
;Leave line
;Enter line
	;LT L110 ,_AD_value ,#5
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0x05
	JLT L110
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#10
	MOV A, #0x0a
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L111 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L111
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
;Leave line
;Enter line
	JMP L111
;Leave line
;Enter line
L110:
;Leave line
;Enter line
	;GE L114 ,_AD_value ,#5
	__SelectBANK _AD_value
	MOV A, _AD_value
	SUB A, #0x05
	JGE L114
;Leave line
;Enter line
	;MOVU1 _WorkGear ,#11
	MOV A, #0x0b
	__SelectBANK _WorkGear
	MOV _WorkGear, A
	;EQ L116 ,_Funflag0.7 ,#0
	__SelectBANK _Funflag0
	BTS1 _Funflag0.7
	JMP L116
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
;Leave line
;Enter line
L116:
;Leave line
;Enter line
L114:
;Leave line
;Enter line
L111:
;Leave line
;Enter line
L107:
;Leave line
;Enter line
L103:
;Leave line
;Enter line
L99:
;Leave line
;Enter line
L95:
;Leave line
;Enter line
L91:
;Leave line
;Enter line
L87:
;Leave line
;Enter line
L83:
;Leave line
;Enter line
L79:
;Leave line
;Enter line
L75:
;Leave line
;Enter line
L72:
;Leave line
;Enter line
	;MOVX1 _Funflag0.1 ,#0
	__SelectBANK _Funflag0
	BCLR _Funflag0.1
	;MOVX1 _Funflag0.2 ,#0
	BCLR _Funflag0.2
	;MOVX1 _Funflag0.3 ,#0
	BCLR _Funflag0.3
	;MOVX1 _Funflag0.4 ,#0
	BCLR _Funflag0.4
;Leave line
;Enter line
L64:
;Leave line
;Enter line
L62:
;Leave line
;Enter line
L53:
;Leave line
;Enter line
L51:
;Leave line
;Enter line
L47:
;Leave line
	RET

CALLTREE _AdccDeal invoke _Delayms,__MulInt2Reg,__DivUInt2Ram

_Function_main_code SEGMENT CODE INBANK USING _Function_main_data
_main:
;Enter line
	;CALLV _Sys_Init
	CALL _Sys_Init
;Leave line
;Enter line
L119:
;Leave line
;Enter line
	;MOVU1 0xCC ,#90
	MOV A, #0x5a
	B0MOV 0xCC, A
	;EQ L122 ,_Funflag1.2 ,#0
	__SelectBANK _Funflag1
	BTS1 _Funflag1.2
	JMP L122
;Leave line
;Enter line
	;MOVX1 0xD5.4 ,#0
	B0BCLR 0xD5.4
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
;Leave line
;Enter line
	JMP L123
;Leave line
;Enter line
L122:
;Leave line
;Enter line
	;CALLV _TimeDeal
	CALL _TimeDeal
;Leave line
;Enter line
	;CALLV _AdccDeal
	CALL _AdccDeal
;Leave line
;Enter line
	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
;Leave line
;Enter line
L123:
;Leave line
;Enter line
L120:
;Leave line
;Enter line
	JMP L119
;Leave line
;Enter line
L118:
;Leave line
_main_end:

CALLTREE _main invoke _Sys_Init,_TimeDeal,_AdccDeal


_interrupt@_ISR_isr SEGMENT CODE AT 0x8 INBANK
_vector_for_ISR_isr:
	JMP _ISR_isr

_Function_ISR_isr_code SEGMENT CODE INBANK USING _Function_ISR_isr_data
_ISR_isr:
	__PUSH_REG 2
;Enter line
	;EQ L125 ,0xC8.5 ,#0
	B0BTS1 0xC8.5
	JMP L125
;Leave line
;Enter line
	;MOVX1 0xC8.5 ,#0
	B0BCLR 0xC8.5
	;ADDU1 _JS1 ,_JS1 ,#1
	__SelectBANK _JS1
	INCMS _JS1
	NOP
	;ADDU1 _TimerCnt ,_TimerCnt ,#1
	__SelectBANK _TimerCnt
	INCMS _TimerCnt
	NOP
	;LE L127 ,_TimerCnt ,#249
	MOV A, _TimerCnt
	CMPRS A, #0xf9
	JLT L127
;Leave line
;Enter line
	;MOVU1 _TimerCnt ,#0
	CLR _TimerCnt
	;ADDU1 _WorkBuff ,_WorkBuff ,#1
	__SelectBANK _WorkBuff
	INCMS _WorkBuff
	NOP
;Leave line
;Enter line
L127:
;Leave line
;Enter line
L125:
;Leave line
;Enter line
L124:
;Leave line
	__POP_REG 2
	RETI
extern data __SrcRArg0
extern data __SrcLArg0
EXTERN CODE __DivUInt2Ram
EXTERN CODE __MulInt2Reg
