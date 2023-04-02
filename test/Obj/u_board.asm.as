CHIP SN8P2501D
EXTERN DATA X
EXTERN DATA H
EXTERN DATA L
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
_InterruptBackupData SEGMENT DATA BANK 0 INBANK COMMON
	_bufT ds 1
	_bufI ds 1
	_bufY ds 1
	_bufZ ds 1
	_bufR ds 1
_Function_ISR_isr_data SEGMENT DATA INBANK
_VirtualReg SEGMENT DATA BANK 0 INBANK COMMON
	W0 DS 1
	W1 DS 1
_VirtualRegIsr SEGMENT DATA BANK 0 INBANK COMMON
	WG DS 1
	WH DS 1
_Function_Sys_Init_code SEGMENT CODE INBANK USING _Function_Sys_Init_data
_Sys_Init:
	CLR (0xCA &  0xFF)
	CLR (0xC9 &  0xFF)
	CLR (0xC8 &  0xFF)
	MOV A, #0xfe
	B0MOV 0xB8, A
	MOV A, #0xef
	B0MOV 0xC2, A
	MOV A, #0xfb
	B0MOV 0xC1, A
	MOV A, #0xff
	B0MOV 0xC5, A
	MOV A, #0x01
	B0MOV 0xE0, A
	CLR (0xE2 &  0xFF)
	CLR (0xE1 &  0xFF)
	CLR (0xE5 &  0xFF)
	B0BCLR 0xD1.3
	B0BCLR 0xD1.2
	B0BCLR 0xD2.4
	B0BSET 0xD1.0
	B0BSET 0xD5.4
	MOV A, #0x10
	B0MOV 0xBF, A
	B0BCLR 0xC8.0
	B0BSET 0xC9.0
	BSET _sysFlag1.0
	MOV A, #0x70
	B0MOV 0xD8, A
	MOV A, #0xba
	B0MOV 0xD9, A
	B0BCLR 0xC8.4
	B0BSET 0xC9.4
	B0BSET 0xD8.7
	MOV A, #0x70
	B0MOV 0xDA, A
	MOV A, #0x83
	B0MOV 0xCD, A
	B0MOV 0xDB, A
	B0BSET 0xDA.2
	B0BCLR 0xDA.1
	B0BCLR 0xDA.0
	B0BSET 0xC9.5
	B0BSET 0xDA.7
	B0BSET 0xDF.7
L1:
	RET
_Function_touch_check_code SEGMENT CODE INBANK USING _Function_touch_check_data
_touch_check:
	B0BTS0 0xD2.3
	JMP L3
	BTS1 _sysFlag.1
	JMP L5
	CLR _Touch_time
	JMP L4
L5:
	MOV A, _Touch_time
	CLR W1
	MOV __SrcLArg0, A
	B0MOV A, W1
	MOV __SrcLArg1, A
	MOV A, #0xf4
	MOV __SrcRArg0, A
	MOV A, #0x01
	MOV __SrcRArg1, A
	CALL __CmpLong
	B0BTS0	134.0
	JMP	L4
	B0BTS1	134.2
	JMP	L4
	CLR _Touch_time
	BSET _sysFlag.1
	BSET _sysFlag.4
	JMP L4
L3:
	BTS1 _sysFlag.1
	JMP L9
	MOV A, _Touch_time
	CLR W1
	MOV __SrcLArg0, A
	B0MOV A, W1
	MOV __SrcLArg1, A
	MOV A, #0xd0
	MOV __SrcRArg0, A
	MOV A, #0x07
	MOV __SrcRArg1, A
	CALL __CmpLong
	B0BTS0	134.0
	JMP	L10
	B0BTS1	134.2
	JMP	L10
	CLR _Touch_time
	BCLR _sysFlag.1
	JMP L10
L9:
	CLR _Touch_time
L10:
L4:
L2:
	RET
CALLTREE _touch_check invoke __CmpLong
_Function_touch_deal_code SEGMENT CODE INBANK USING _Function_touch_deal_data
_touch_deal:
	BTS1 _sysFlag.1
	JMP L14
	BTS0 _sysFlag.2
	JMP L15
	BSET _sysFlag.2
	INCMS _btn_value
	NOP
	MOV A, _btn_value
	SUB A, #0x04
	B0BTS1	134.2
	JMP	L18
	MOV A, #0x01
	MOV _btn_value, A
L18:
	MOV A, _btn_value
	MOV _rdelay_acton_fun_arg@0, A
	CALL _rdelay_acton_fun
	JMP L15
L14:
	BCLR _sysFlag.2
L15:
L13:
	RET
CALLTREE _touch_deal invoke _rdelay_acton_fun
_Function_rdelay_acton_fun_code SEGMENT CODE INBANK USING _Function_rdelay_acton_fun_data
_rdelay_acton_fun:
	MOV A, _rdelay_acton_fun_arg@0
	CMPRS A, #0x00
	JMP L21
	B0BCLR 0xD1.3
	B0BCLR 0xD1.2
	JMP L22
L21:
	DECS _rdelay_acton_fun_arg@0
	JMP L23
	B0BSET 0xD1.3
	B0BCLR 0xD1.2
	JMP L24
L23:
	MOV A, _rdelay_acton_fun_arg@0
	CMPRS A, #0x02
	JMP L25
	B0BCLR 0xD1.3
	B0BSET 0xD1.2
	JMP L26
L25:
	MOV A, _rdelay_acton_fun_arg@0
	CMPRS A, #0x03
	JMP L27
	B0BSET 0xD1.3
	B0BSET 0xD1.2
L27:
L26:
L24:
L22:
L20:
	RET
_Function_main_code SEGMENT CODE INBANK USING _Function_main_data
_main:
	CALL _Sys_Init
L30:
	BTS1 _sysFlag.0
	JMP L33
	MOV A, _IR_count
	CMPRS A, #0xe6
	B0BTS1	134.2
	JMP	L33
	BCLR _sysFlag.0
	CLR _IR_count
	MOV A, _IRdata
	AND A, #0x0f
	MOV _main_data@0, A
	MOV A, #(_IRdata)$M
	B0MOV H, A
	MOV A, #(_IRdata)$L
	B0MOV L, A
	B0MOV 132, #(_IRdata)$M
	B0MOV 131, #(_IRdata)$L
	MOV A, #0x04
	CALL __Get1ByteRamToLArg
	CALL __SRUInt2Ram
	MOV A, _main_data@0
	CMPRS A, _IRdata
	B0BTS1	134.2
	JMP	L35
	BTS1 _sysFlag.4
	JMP L36
	INCMS _btn_value
	NOP
	MOV A, _btn_value
	SUB A, #0x04
	B0BTS1	134.2
	JMP	L39
	MOV A, #0x01
	MOV _btn_value, A
L39:
	MOV A, _btn_value
	MOV _rdelay_acton_fun_arg@0, A
	CALL _rdelay_acton_fun
	JMP L36
L35:
	MOV A, _main_data@0
	SUB A, _IRdata
	b0bts0	134.2
	JMP	L41
	BTS1 _sysFlag.4
	JMP L43
	BCLR _sysFlag.4
	CLR _btn_value
	JMP L44
L43:
	BSET _sysFlag.4
	MOV A, #0x01
	MOV _btn_value, A
L44:
L41:
L36:
L33:
	CALL _touch_check
	CALL _touch_deal
L31:
	JMP L30
L29:
_main_end:
CALLTREE _main invoke _Sys_Init,__Get1ByteRamToLArg,__SRUInt2Ram,_rdelay_acton_fun,_touch_check,_touch_deal
_interrupt@_ISR_isr SEGMENT CODE AT 0x8 INBANK
_vector_for_ISR_isr:
	JMP _ISR_isr
_Function_ISR_isr_code SEGMENT CODE INBANK USING _Function_ISR_isr_data
_ISR_isr:
	PUSH
		B0MOV A, 132
		B0MOV _bufY, A
		B0MOV A, 131
		B0MOV _bufZ, A
		B0MOV A, 130
		B0MOV _bufR, A
	B0MOV A, T
	B0MOV _bufT, A
	B0MOV A, I
	B0MOV _bufI, A
	B0BTS1 0xC8.0
	JMP L47
	BTS1 _sysFlag1.0
	JMP L49
	MOV A, #0x08
	B0MOV 0xBF, A
	BCLR _sysFlag1.0
	MOV A, _IR_time
	CMPRS A, #0x3c
	B0BTS1	134.2
	JMP	L51
	CLR _IR_data
	MOV A, #0x01
	MOV _IR_bit, A
	BSET _sysFlag.5
L51:
	CLR _IR_time
	JMP L50
L49:
	MOV A, #0x10
	B0MOV 0xBF, A
	BSET _sysFlag1.0
	BTS1 _sysFlag.5
	JMP L53
	MOV A, _IR_time
	CMPRS A, #0x05
	B0BTS1	134.2
	JMP	L55
	MOV A, #0x80
	OR _IR_data, A
L55:
	CLR _IR_time
	INCMS _IR_bit
	NOP
	MOV A, _IR_bit
	CMPRS A, #0x09
	JMP L57
	BSET _sysFlag.0
	CLR _IR_bit
	BCLR _sysFlag.5
	MOV A, _IR_data
	CMPRS A, #0xbb
	JMP L59
	INCMS _IRdata
	NOP
	JMP L58
L59:
	MOV A, _IR_data
	CMPRS A, #0x1b
	JMP L58
	MOV A, #0x10
	ADD _IRdata, A
	JMP L58
L57:
	B0BCLR 134.2
	RRCM _IR_data
L58:
L53:
L50:
	CLR _IR_count
	B0BCLR 0xC8.0
	B0BSET 0xC9.0
	JMP L48
L47:
	B0BTS1 0xC8.4
	JMP L63
	MOV A, _IR_time
	SUB A, #0xf0
	b0bts0	134.2
	JMP	L65
	INCMS _IR_time
	NOP
L65:
	INCMS _Touch_time
	NOP
	BTS1 _sysFlag.0
	JMP L67
	INCMS _IR_count
	NOP
L67:
	MOV A, #0x70
	B0MOV 0xD8, A
	MOV A, #0xba
	B0MOV 0xD9, A
	B0BCLR 0xC8.4
	B0BSET 0xC9.4
	B0BSET 0xD8.7
	JMP L64
L63:
	B0BTS1 0xC8.5
	JMP L69
	B0BCLR 0xC8.5
	BTS0 _sysFlag.7
	JMP L71
	B0BSET 0xD5.4
	JMP L45
L71:
	MOV A, _sdata46
	MOV __SrcLArg0_isr, A
	ADD A, #0x01
	MOV _sdata46, A
	CLR WH
	B0MOV A, WH
	MOV __SrcLArg1_isr, A
	MOV A, #0xb8
	MOV __SrcRArg0_isr, A
	MOV A, #0x0b
	MOV __SrcRArg1_isr, A
	CALL __CmpLong_isr
	B0BTS0	134.0
	JMP	L73
	B0BTS1	134.2
	JMP	L73
	BCLR _sysFlag.7
	CLR _sdata46
	B0BSET 0xD5.4
	JMP L74
L73:
	BTS1 _sysFlag.6
	JMP L75
	BCLR _sysFlag.6
	B0BSET 0xD5.4
	JMP L76
L75:
	BSET _sysFlag.6
	B0BCLR 0xD5.4
L76:
L74:
L69:
L64:
L48:
L45:
	B0MOV A, _bufT
	B0MOV T, A
	B0MOV A, _bufI
	B0MOV I, A
	B0MOV A, _bufY
	B0MOV 132, A
	B0MOV A, _bufZ
	B0MOV 131, A
	B0MOV A, _bufR
	B0MOV 130, A
	POP
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
