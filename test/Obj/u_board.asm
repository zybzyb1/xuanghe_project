
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
CHIP SN8P2501D

INCLUDE <sncc_macros.h>
EXTERN DATA T
EXTERN DATA I
.CODE
PUBLIC _IR_time
PUBLIC _btn_value
PUBLIC _IR_count
PUBLIC _Sys_Init
PUBLIC _rdelay_acton_fun_arg@0
PUBLIC _main
PUBLIC _ISR_isr
PUBLIC _IRdata
_IRdata@segment SEGMENT DATA INBANK
	_IRdata DS 1
PUBLIC _IR_bit
_IR_bit@segment SEGMENT DATA INBANK
	_IR_bit DS 1
PUBLIC _Touch_time
_Touch_time@segment SEGMENT DATA INBANK
	_Touch_time DS 1
PUBLIC _IR_data
_IR_data@segment SEGMENT DATA INBANK
	_IR_data DS 1
PUBLIC _sysFlag1
_sysFlag1@segment SEGMENT DATA INBANK
	_sysFlag1 DS 1
PUBLIC _sysFlag
_sysFlag@segment SEGMENT DATA INBANK
	_sysFlag DS 1

_IR_time@segment SEGMENT DATA INBANK
	_IR_time DS 1
_btn_value@segment SEGMENT DATA INBANK
	_btn_value DS 1
_IR_count@segment SEGMENT DATA INBANK
	_IR_count DS 1
_Function_Sys_Init_data SEGMENT DATA INBANK

_Function_touch_check_data SEGMENT DATA INBANK

_Function_touch_deal_data SEGMENT DATA INBANK

_Function_rdelay_acton_fun_data SEGMENT DATA INBANK
	_rdelay_acton_fun_arg@0 DS 1

_Function_main_data SEGMENT DATA INBANK
	_main_data@0	DS	1

_sdata46@segment SEGMENT DATA INBANK
	_sdata46 DS 1
_DEFINE_ISRBACKUP_DATA 2
_Function_ISR_isr_data SEGMENT DATA INBANK


_VirtualReg SEGMENT DATA BANK 0 INBANK COMMON
	W0 DS 1
	W1 DS 1


_VirtualRegIsr SEGMENT DATA BANK 0 INBANK COMMON
	WG DS 1
	WH DS 1

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
	;MOVU1 0xB8 ,#254
	MOV A, #0xfe
	B0MOV 0xB8, A
	;MOVU1 0xC2 ,#239
	MOV A, #0xef
	B0MOV 0xC2, A
	;MOVU1 0xC1 ,#251
	MOV A, #0xfb
	B0MOV 0xC1, A
	;MOVU1 0xC5 ,#255
	MOV A, #0xff
	B0MOV 0xC5, A
	;MOVU1 0xE0 ,#1
	MOV A, #0x01
	B0MOV 0xE0, A
	;MOVU1 0xE2 ,#0
	__SelectBANKCNST 0
	CLR (0xE2 & 0xFF)
	;MOVU1 0xE1 ,#0
	__SelectBANKCNST 0
	CLR (0xE1 & 0xFF)
	;MOVU1 0xE5 ,#0
	__SelectBANKCNST 0
	CLR (0xE5 & 0xFF)
	;MOVX1 0xD1.3 ,#0
	B0BCLR 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
	;MOVX1 0xD2.4 ,#0
	B0BCLR 0xD2.4
	;MOVX1 0xD1.0 ,#1
	B0BSET 0xD1.0
	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
	;MOVU1 0xBF ,#16
	MOV A, #0x10
	B0MOV 0xBF, A
	;MOVX1 0xC8.0 ,#0
	B0BCLR 0xC8.0
	;MOVX1 0xC9.0 ,#1
	B0BSET 0xC9.0
	;MOVX1 _sysFlag1.0 ,#1
	__SelectBANK _sysFlag1
	BSET _sysFlag1.0
	;MOVU1 0xD8 ,#112
	MOV A, #0x70
	B0MOV 0xD8, A
	;MOVU1 0xD9 ,#186
	MOV A, #0xba
	B0MOV 0xD9, A
	;MOVX1 0xC8.4 ,#0
	B0BCLR 0xC8.4
	;MOVX1 0xC9.4 ,#1
	B0BSET 0xC9.4
	;MOVX1 0xD8.7 ,#1
	B0BSET 0xD8.7
	;MOVU1 0xDA ,#112
	MOV A, #0x70
	B0MOV 0xDA, A
	;MOVU1 0xCD ,#131
	MOV A, #0x83
	B0MOV 0xCD, A
	;MOVU1 0xDB ,#131
	B0MOV 0xDB, A
	;MOVX1 0xDA.2 ,#1
	B0BSET 0xDA.2
	;MOVX1 0xDA.1 ,#0
	B0BCLR 0xDA.1
	;MOVX1 0xDA.0 ,#0
	B0BCLR 0xDA.0
	;MOVX1 0xC9.5 ,#1
	B0BSET 0xC9.5
	;MOVX1 0xDA.7 ,#1
	B0BSET 0xDA.7
	;MOVX1 0xDF.7 ,#1
	B0BSET 0xDF.7
;Leave line
;Enter line
L1:
;Leave line
	RET
_Function_touch_check_code SEGMENT CODE INBANK USING _Function_touch_check_data
_touch_check:
;Enter line
	;NEX1 L3 ,0xD2.3 ,#0
	B0BTS0 0xD2.3
	JMP L3
;Leave line
;Enter line
	;NEX1 L5 ,_sysFlag.1 ,#1
	__SelectBANK _sysFlag
	BTS1 _sysFlag.1
	JMP L5
;Leave line
;Enter line
	;MOVU1 _Touch_time ,#0
	__SelectBANK _Touch_time
	CLR _Touch_time
;Leave line
;Enter line
	JMP L4
;Leave line
;Enter line
L5:
;Leave line
;Enter line
	;CVUI2 W0:W1 ,_Touch_time
	__SelectBANK _Touch_time
	MOV A, _Touch_time
	__SelectBANKCNST 0
	CLR W1
	;LE L4 ,W0:W1 ,#500
	__SelectBANK __SrcLArg0
	MOV __SrcLArg0, A
	B0MOV A, W1
	__SelectBANK __SrcLArg1
	MOV __SrcLArg1, A
	MOV A, #0xf4
	__SelectBANK __SrcRArg0
	MOV __SrcRArg0, A
	MOV A, #0x01
	__SelectBANK __SrcRArg1
	MOV __SrcRArg1, A
	CALL __CmpLong
	JLE L4
;Leave line
;Enter line
	;MOVU1 _Touch_time ,#0
	__SelectBANK _Touch_time
	CLR _Touch_time
	;MOVX1 _sysFlag.1 ,#1
	__SelectBANK _sysFlag
	BSET _sysFlag.1
	;MOVX1 _sysFlag.4 ,#1
	BSET _sysFlag.4
;Leave line
;Enter line
	JMP L4
;Leave line
;Enter line
L3:
;Leave line
;Enter line
	;NEX1 L9 ,_sysFlag.1 ,#1
	__SelectBANK _sysFlag
	BTS1 _sysFlag.1
	JMP L9
;Leave line
;Enter line
	;CVUI2 W0:W1 ,_Touch_time
	__SelectBANK _Touch_time
	MOV A, _Touch_time
	__SelectBANKCNST 0
	CLR W1
	;LE L10 ,W0:W1 ,#2000
	__SelectBANK __SrcLArg0
	MOV __SrcLArg0, A
	B0MOV A, W1
	__SelectBANK __SrcLArg1
	MOV __SrcLArg1, A
	MOV A, #0xd0
	__SelectBANK __SrcRArg0
	MOV __SrcRArg0, A
	MOV A, #0x07
	__SelectBANK __SrcRArg1
	MOV __SrcRArg1, A
	CALL __CmpLong
	JLE L10
;Leave line
;Enter line
	;MOVU1 _Touch_time ,#0
	__SelectBANK _Touch_time
	CLR _Touch_time
	;MOVX1 _sysFlag.1 ,#0
	__SelectBANK _sysFlag
	BCLR _sysFlag.1
;Leave line
;Enter line
	JMP L10
;Leave line
;Enter line
L9:
;Leave line
;Enter line
	;MOVU1 _Touch_time ,#0
	__SelectBANK _Touch_time
	CLR _Touch_time
;Leave line
;Enter line
L10:
;Leave line
;Enter line
L4:
;Leave line
;Enter line
L2:
;Leave line
	RET

CALLTREE _touch_check invoke __CmpLong

_Function_touch_deal_code SEGMENT CODE INBANK USING _Function_touch_deal_data
_touch_deal:
;Enter line
	;EQ L14 ,_sysFlag.1 ,#0
	__SelectBANK _sysFlag
	BTS1 _sysFlag.1
	JMP L14
;Leave line
;Enter line
	;NEX1 L15 ,_sysFlag.2 ,#0
	BTS0 _sysFlag.2
	JMP L15
;Leave line
;Enter line
	;MOVX1 _sysFlag.2 ,#1
	BSET _sysFlag.2
	;ADDU1 _btn_value ,_btn_value ,#1
	__SelectBANK _btn_value
	INCMS _btn_value
	NOP
	;LT L18 ,_btn_value ,#4
	MOV A, _btn_value
	SUB A, #0x04
	JLT L18
;Leave line
;Enter line
	;MOVU1 _btn_value ,#1
	MOV A, #0x01
	MOV _btn_value, A
;Leave line
;Enter line
L18:
;Leave line
;Enter line
	;PUSH _rdelay_acton_fun_arg@0 ,_btn_value
	__SelectBANK _btn_value
	MOV A, _btn_value
	__SelectBANK _rdelay_acton_fun_arg@0
	MOV _rdelay_acton_fun_arg@0, A
	;CALLV _rdelay_acton_fun
	CALL _rdelay_acton_fun
;Leave line
;Enter line
	JMP L15
;Leave line
;Enter line
L14:
;Leave line
;Enter line
	;MOVX1 _sysFlag.2 ,#0
	__SelectBANK _sysFlag
	BCLR _sysFlag.2
;Leave line
;Enter line
L15:
;Leave line
;Enter line
L13:
;Leave line
	RET

CALLTREE _touch_deal invoke _rdelay_acton_fun

_Function_rdelay_acton_fun_code SEGMENT CODE INBANK USING _Function_rdelay_acton_fun_data
_rdelay_acton_fun:
;Enter line
	;NEI1 L21 ,_rdelay_acton_fun_arg@0 ,#0
	__SelectBANK _rdelay_acton_fun_arg@0
	MOV A, _rdelay_acton_fun_arg@0
	CMPRS A, #0x00
	JMP L21
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#0
	B0BCLR 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
;Leave line
;Enter line
	JMP L22
;Leave line
;Enter line
L21:
;Leave line
;Enter line
	;NEI1 L23 ,_rdelay_acton_fun_arg@0 ,#1
	__SelectBANK _rdelay_acton_fun_arg@0
	DECS _rdelay_acton_fun_arg@0
	JMP L23
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
;Leave line
;Enter line
	JMP L24
;Leave line
;Enter line
L23:
;Leave line
;Enter line
	;NEI1 L25 ,_rdelay_acton_fun_arg@0 ,#2
	__SelectBANK _rdelay_acton_fun_arg@0
	MOV A, _rdelay_acton_fun_arg@0
	CMPRS A, #0x02
	JMP L25
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#0
	B0BCLR 0xD1.3
	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
;Leave line
;Enter line
	JMP L26
;Leave line
;Enter line
L25:
;Leave line
;Enter line
	;NEI1 L27 ,_rdelay_acton_fun_arg@0 ,#3
	__SelectBANK _rdelay_acton_fun_arg@0
	MOV A, _rdelay_acton_fun_arg@0
	CMPRS A, #0x03
	JMP L27
;Leave line
;Enter line
	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
;Leave line
;Enter line
L27:
;Leave line
;Enter line
L26:
;Leave line
;Enter line
L24:
;Leave line
;Enter line
L22:
;Leave line
;Enter line
L20:
;Leave line
	RET
_Function_main_code SEGMENT CODE INBANK USING _Function_main_data
_main:
;Enter line
	;CALLV _Sys_Init
	CALL _Sys_Init
;Leave line
;Enter line
L30:
;Leave line
;Enter line
	;EQ L33 ,_sysFlag.0 ,#0
	__SelectBANK _sysFlag
	BTS1 _sysFlag.0
	JMP L33
	;LE L33 ,_IR_count ,#230
	__SelectBANK _IR_count
	MOV A, _IR_count
	CMPRS A, #0xe6
	JLT L33
;Leave line
;Enter line
	;MOVX1 _sysFlag.0 ,#0
	__SelectBANK _sysFlag
	BCLR _sysFlag.0
	;MOVU1 _IR_count ,#0
	__SelectBANK _IR_count
	CLR _IR_count
	;ANDU1 _main_data@0 ,_IRdata ,#15
	__SelectBANK _IRdata
	MOV A, _IRdata
	AND A, #0x0f
	__SelectBANK _main_data@0
	MOV _main_data@0, A
	;RSH _IRdata ,_IRdata ,#4
	MOV A, #(_IRdata)$M
	B0MOV H, A
	MOV A, #(_IRdata)$L
	B0MOV L, A
	B0MOV Y, #(_IRdata)$M
	B0MOV Z, #(_IRdata)$L
	MOV A, #0x04
	CALL __Get1ByteRamToLArg
	CALL __SRUInt2Ram
	;LE L35 ,_main_data@0 ,_IRdata
	__SelectBANK _main_data@0
	MOV A, _main_data@0
	__SelectBANK _IRdata
	CMPRS A, _IRdata
	JLT L35
;Leave line
;Enter line
	;NEX1 L36 ,_sysFlag.4 ,#1
	__SelectBANK _sysFlag
	BTS1 _sysFlag.4
	JMP L36
;Leave line
;Enter line
	;ADDU1 _btn_value ,_btn_value ,#1
	__SelectBANK _btn_value
	INCMS _btn_value
	NOP
	;LT L39 ,_btn_value ,#4
	MOV A, _btn_value
	SUB A, #0x04
	JLT L39
;Leave line
;Enter line
	;MOVU1 _btn_value ,#1
	MOV A, #0x01
	MOV _btn_value, A
;Leave line
;Enter line
L39:
;Leave line
;Enter line
	;PUSH _rdelay_acton_fun_arg@0 ,_btn_value
	__SelectBANK _btn_value
	MOV A, _btn_value
	__SelectBANK _rdelay_acton_fun_arg@0
	MOV _rdelay_acton_fun_arg@0, A
	;CALLV _rdelay_acton_fun
	CALL _rdelay_acton_fun
;Leave line
;Enter line
	JMP L36
;Leave line
;Enter line
L35:
;Leave line
;Enter line
	;GE L41 ,_main_data@0 ,_IRdata
	__SelectBANK _main_data@0
	MOV A, _main_data@0
	__SelectBANK _IRdata
	SUB A, _IRdata
	JGE L41
;Leave line
;Enter line
	;NEX1 L43 ,_sysFlag.4 ,#1
	__SelectBANK _sysFlag
	BTS1 _sysFlag.4
	JMP L43
;Leave line
;Enter line
	;MOVX1 _sysFlag.4 ,#0
	BCLR _sysFlag.4
	;MOVU1 _btn_value ,#0
	__SelectBANK _btn_value
	CLR _btn_value
;Leave line
;Enter line
	JMP L44
;Leave line
;Enter line
L43:
;Leave line
;Enter line
	;MOVX1 _sysFlag.4 ,#1
	__SelectBANK _sysFlag
	BSET _sysFlag.4
	;MOVU1 _btn_value ,#1
	MOV A, #0x01
	__SelectBANK _btn_value
	MOV _btn_value, A
;Leave line
;Enter line
L44:
;Leave line
;Enter line
L41:
;Leave line
;Enter line
L36:
;Leave line
;Enter line
L33:
;Leave line
;Enter line
	;CALLV _touch_check
	CALL _touch_check
;Leave line
;Enter line
	;CALLV _touch_deal
	CALL _touch_deal
;Leave line
;Enter line
L31:
;Leave line
;Enter line
	JMP L30
;Leave line
;Enter line
L29:
;Leave line
_main_end:

CALLTREE _main invoke _Sys_Init,__Get1ByteRamToLArg,__SRUInt2Ram,_rdelay_acton_fun,_touch_check,_touch_deal


_interrupt@_ISR_isr SEGMENT CODE AT 0x8 INBANK
_vector_for_ISR_isr:
	JMP _ISR_isr

_Function_ISR_isr_code SEGMENT CODE INBANK USING _Function_ISR_isr_data
_ISR_isr:
	__PUSH_REG 2
;Enter line
	;EQ L47 ,0xC8.0 ,#0
	B0BTS1 0xC8.0
	JMP L47
;Leave line
;Enter line
	;EQ L49 ,_sysFlag1.0 ,#0
	__SelectBANK _sysFlag1
	BTS1 _sysFlag1.0
	JMP L49
;Leave line
;Enter line
	;MOVU1 0xBF ,#8
	MOV A, #0x08
	B0MOV 0xBF, A
	;MOVX1 _sysFlag1.0 ,#0
	BCLR _sysFlag1.0
	;LE L51 ,_IR_time ,#60
	__SelectBANK _IR_time
	MOV A, _IR_time
	CMPRS A, #0x3c
	JLT L51
;Leave line
;Enter line
	;MOVU1 _IR_data ,#0
	__SelectBANK _IR_data
	CLR _IR_data
	;MOVU1 _IR_bit ,#1
	MOV A, #0x01
	__SelectBANK _IR_bit
	MOV _IR_bit, A
	;MOVX1 _sysFlag.5 ,#1
	__SelectBANK _sysFlag
	BSET _sysFlag.5
;Leave line
;Enter line
L51:
;Leave line
;Enter line
	;MOVU1 _IR_time ,#0
	__SelectBANK _IR_time
	CLR _IR_time
;Leave line
;Enter line
	JMP L50
;Leave line
;Enter line
L49:
;Leave line
;Enter line
	;MOVU1 0xBF ,#16
	MOV A, #0x10
	B0MOV 0xBF, A
	;MOVX1 _sysFlag1.0 ,#1
	__SelectBANK _sysFlag1
	BSET _sysFlag1.0
	;EQ L53 ,_sysFlag.5 ,#0
	__SelectBANK _sysFlag
	BTS1 _sysFlag.5
	JMP L53
;Leave line
;Enter line
	;LE L55 ,_IR_time ,#5
	__SelectBANK _IR_time
	MOV A, _IR_time
	CMPRS A, #0x05
	JLT L55
;Leave line
;Enter line
	;ORU1 _IR_data ,_IR_data ,#128
	MOV A, #0x80
	__SelectBANK _IR_data
	OR _IR_data, A
;Leave line
;Enter line
L55:
;Leave line
;Enter line
	;MOVU1 _IR_time ,#0
	__SelectBANK _IR_time
	CLR _IR_time
	;ADDU1 _IR_bit ,_IR_bit ,#1
	__SelectBANK _IR_bit
	INCMS _IR_bit
	NOP
	;NEI1 L57 ,_IR_bit ,#9
	MOV A, _IR_bit
	CMPRS A, #0x09
	JMP L57
;Leave line
;Enter line
	;MOVX1 _sysFlag.0 ,#1
	__SelectBANK _sysFlag
	BSET _sysFlag.0
	;MOVU1 _IR_bit ,#0
	__SelectBANK _IR_bit
	CLR _IR_bit
	;MOVX1 _sysFlag.5 ,#0
	__SelectBANK _sysFlag
	BCLR _sysFlag.5
	;NEI1 L59 ,_IR_data ,#187
	__SelectBANK _IR_data
	MOV A, _IR_data
	CMPRS A, #0xbb
	JMP L59
;Leave line
;Enter line
	;ADDU1 _IRdata ,_IRdata ,#1
	__SelectBANK _IRdata
	INCMS _IRdata
	NOP
;Leave line
;Enter line
	JMP L58
;Leave line
;Enter line
L59:
;Leave line
;Enter line
	;NEI1 L58 ,_IR_data ,#27
	__SelectBANK _IR_data
	MOV A, _IR_data
	CMPRS A, #0x1b
	JMP L58
;Leave line
;Enter line
	;ADDU1 _IRdata ,_IRdata ,#16
	MOV A, #0x10
	__SelectBANK _IRdata
	ADD _IRdata, A
;Leave line
;Enter line
	JMP L58
;Leave line
;Enter line
L57:
;Leave line
;Enter line
	;RSH _IR_data ,_IR_data ,#1
	B0BCLR FC
	__SelectBANK _IR_data
	RRCM _IR_data
;Leave line
;Enter line
L58:
;Leave line
;Enter line
L53:
;Leave line
;Enter line
L50:
;Leave line
;Enter line
	;MOVU1 _IR_count ,#0
	__SelectBANK _IR_count
	CLR _IR_count
	;MOVX1 0xC8.0 ,#0
	B0BCLR 0xC8.0
	;MOVX1 0xC9.0 ,#1
	B0BSET 0xC9.0
;Leave line
;Enter line
	JMP L48
;Leave line
;Enter line
L47:
;Leave line
;Enter line
	;EQ L63 ,0xC8.4 ,#0
	B0BTS1 0xC8.4
	JMP L63
;Leave line
;Enter line
	;GE L65 ,_IR_time ,#240
	__SelectBANK _IR_time
	MOV A, _IR_time
	SUB A, #0xf0
	JGE L65
;Leave line
;Enter line
	;ADDU1 _IR_time ,_IR_time ,#1
	INCMS _IR_time
	NOP
;Leave line
;Enter line
L65:
;Leave line
;Enter line
	;ADDU1 _Touch_time ,_Touch_time ,#1
	__SelectBANK _Touch_time
	INCMS _Touch_time
	NOP
	;EQ L67 ,_sysFlag.0 ,#0
	__SelectBANK _sysFlag
	BTS1 _sysFlag.0
	JMP L67
;Leave line
;Enter line
	;ADDU1 _IR_count ,_IR_count ,#1
	__SelectBANK _IR_count
	INCMS _IR_count
	NOP
;Leave line
;Enter line
L67:
;Leave line
;Enter line
	;MOVU1 0xD8 ,#112
	MOV A, #0x70
	B0MOV 0xD8, A
	;MOVU1 0xD9 ,#186
	MOV A, #0xba
	B0MOV 0xD9, A
	;MOVX1 0xC8.4 ,#0
	B0BCLR 0xC8.4
	;MOVX1 0xC9.4 ,#1
	B0BSET 0xC9.4
	;MOVX1 0xD8.7 ,#1
	B0BSET 0xD8.7
;Leave line
;Enter line
	JMP L64
;Leave line
;Enter line
L63:
;Leave line
;Enter line
	;EQ L69 ,0xC8.5 ,#0
	B0BTS1 0xC8.5
	JMP L69
;Leave line
;Enter line
	;MOVX1 0xC8.5 ,#0
	B0BCLR 0xC8.5
	;NEX1 L71 ,_sysFlag.7 ,#0
	__SelectBANK _sysFlag
	BTS0 _sysFlag.7
	JMP L71
;Leave line
;Enter line
	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
;Leave line
;Enter line
	JMP L45
;Leave line
;Enter line
L71:
;Leave line
;Enter line
	;MOVI1 WG ,_sdata46
	__SelectBANK _sdata46
	MOV A, _sdata46
	__SelectBANK __SrcLArg0_isr
	MOV __SrcLArg0_isr, A
	;ADDU1 _sdata46 ,WG ,#1
	ADD A, #0x01
	__SelectBANK _sdata46
	MOV _sdata46, A
	;CVUI2 WG:WH ,WG
	__SelectBANKCNST 0
	CLR WH
	;LE L73 ,WG:WH ,#3000
	B0MOV A, WH
	__SelectBANK __SrcLArg1_isr
	MOV __SrcLArg1_isr, A
	MOV A, #0xb8
	__SelectBANK __SrcRArg0_isr
	MOV __SrcRArg0_isr, A
	MOV A, #0x0b
	__SelectBANK __SrcRArg1_isr
	MOV __SrcRArg1_isr, A
	CALL __CmpLong_isr
	JLE L73
;Leave line
;Enter line
	;MOVX1 _sysFlag.7 ,#0
	__SelectBANK _sysFlag
	BCLR _sysFlag.7
	;MOVU1 _sdata46 ,#0
	__SelectBANK _sdata46
	CLR _sdata46
	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
;Leave line
;Enter line
	JMP L74
;Leave line
;Enter line
L73:
;Leave line
;Enter line
	;EQ L75 ,_sysFlag.6 ,#0
	__SelectBANK _sysFlag
	BTS1 _sysFlag.6
	JMP L75
;Leave line
;Enter line
	;MOVX1 _sysFlag.6 ,#0
	BCLR _sysFlag.6
	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
;Leave line
;Enter line
	JMP L76
;Leave line
;Enter line
L75:
;Leave line
;Enter line
	;MOVX1 _sysFlag.6 ,#1
	__SelectBANK _sysFlag
	BSET _sysFlag.6
	;MOVX1 0xD5.4 ,#0
	B0BCLR 0xD5.4
;Leave line
;Enter line
L76:
;Leave line
;Enter line
L74:
;Leave line
;Enter line
L69:
;Leave line
;Enter line
L64:
;Leave line
;Enter line
L48:
;Leave line
;Enter line
L45:
;Leave line
	__POP_REG 2
	RETI

CALLTREE _ISR_isr invoke __CmpLong_isr

extern data __SrcRArg1_isr
extern data __SrcRArg0_isr
extern data __SrcLArg1_isr
extern data __SrcLArg0_isr
extern data __SrcRArg1
extern data __SrcRArg0
extern data __SrcLArg1
extern data __SrcLArg0
EXTERN CODE __CmpLong_isr
EXTERN CODE __SRUInt2Ram
EXTERN CODE __Get1ByteRamToLArg
EXTERN CODE __CmpLong
