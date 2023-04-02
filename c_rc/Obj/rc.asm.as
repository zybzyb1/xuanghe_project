CHIP SN8P2501B
EXTERN DATA X
EXTERN DATA H
EXTERN DATA L
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
_InterruptBackupData SEGMENT DATA BANK 0 INBANK COMMON
	_bufT ds 1
	_bufI ds 1
	_bufY ds 1
	_bufZ ds 1
	_bufR ds 1
_Function_ISR_isr_data SEGMENT DATA INBANK
_VirtualReg SEGMENT DATA BANK 0 INBANK COMMON
	W0 DS 1
_Function_Sys_Init_code SEGMENT CODE INBANK USING _Function_Sys_Init_data
_Sys_Init:
	CLR (0xCA &  0xFF)
	CLR (0xC9 &  0xFF)
	CLR (0xC8 &  0xFF)
	MOV A, #0xff
	B0MOV 0xB8, A
	B0MOV 0xC2, A
	MOV A, #0xf1
	B0MOV 0xC1, A
	MOV A, #0xff
	B0MOV 0xC5, A
	CLR (0xE0 &  0xFF)
	CLR (0xE2 &  0xFF)
	MOV A, #0x0c
	B0MOV 0xE1, A
	CLR (0xE5 &  0xFF)
	B0BSET 0xD1.2
	B0BSET 0xD1.3
	B0BSET 0xD5.4
	MOV A, #0x10
	B0MOV 0xD8, A
	CLR (0xD9 &  0xFF)
	B0BSET 0xC9.4
	MOV A, #0x40
	B0MOV 0xDA, A
	MOV A, #0x06
	B0MOV 0xCD, A
	B0MOV 0xDB, A
	B0BSET 0xDA.2
	B0BSET 0xC9.5
	B0BSET 0xDA.7
	B0BSET 0xDF.7
	CALL _ZhiJDeal
	MOV A, #0x64
	MOV _Worktime, A
	CLR _WorkBuff
	MOV A, _SDian_Cnt
	CMPRS A, #0x02
	JMP L2
	BTS1 _SDian_bz
	JMP L4
	MOV A, #0x02
	MOV _SDian_Cnt, A
	JMP L3
L4:
	MOV A, #0x01
	MOV _SDian_Cnt, A
	JMP L3
L2:
	MOV A, _SDian_Cnt
	CMPRS A, #0x03
	JMP L6
	BTS1 _SDian_bz
	JMP L8
	MOV A, #0x03
	MOV _SDian_Cnt, A
	JMP L7
L8:
	MOV A, #0x01
	MOV _SDian_Cnt, A
	JMP L7
L6:
	MOV A, _SDian_Cnt
	CMPRS A, #0x04
	JMP L10
	BTS1 _SDian_bz
	JMP L12
	MOV A, #0x04
	MOV _SDian_Cnt, A
	JMP L11
L12:
	MOV A, #0x01
	MOV _SDian_Cnt, A
	JMP L11
L10:
	MOV A, #0x01
	MOV _SDian_Cnt, A
	BSET _SDian_bz
L11:
L7:
L3:
L1:
	RET
CALLTREE _Sys_Init invoke _ZhiJDeal
_Function_Delayms_code SEGMENT CODE INBANK USING _Function_Delayms_data
_Delayms:
	CLR _Delayms_data@0
	JMP L18
L15:
	MOV A, #0x64
	MOV _Delayms_data@1, A
	JMP L22
L19:
L20:
	DECMS _Delayms_data@1
	NOP
L22:
	MOV A, _Delayms_data@1
	CMPRS A, #0x00
	JMP L19
L16:
	INCMS _Delayms_data@0
	NOP
L18:
	MOV A, _Delayms_data@0
	SUB A, _Delayms_arg@0
	B0BTS1	134.2
	JMP	L15
L14:
	RET
_Function_TimeDeal_code SEGMENT CODE INBANK USING _Function_TimeDeal_data
_TimeDeal:
	MOV A, _WorkBuff
	SUB A, #0x28
	B0BTS1	134.2
	JMP	L24
	BTS1 _Funflag1.1
	JMP L26
	BSET _Funflag1.2
L26:
L24:
	MOV A, _WorkBuff
	SUB A, _Worktime
	B0BTS1	134.2
	JMP	L28
	INCMS _SDian_Cnt
	NOP
	MOV A, _SDian_Cnt
	SUB A, #0x04
	B0BTS1	134.2
	JMP	L30
	MOV A, #0x04
	MOV _SDian_Cnt, A
L30:
	BSET _Funflag1.2
L28:
L23:
	RET
_Function_ZhiJDeal_code SEGMENT CODE INBANK USING _Function_ZhiJDeal_data
_ZhiJDeal:
	MOV A, #0x01
	MOV _Delayms_arg@0, A
	CALL _Delayms
L33:
	B0BTS1 0xD1.2
	JMP L36
L36:
	B0BTS1 0xD1.3
	JMP L38
L38:
	MOV A, #0x01
	MOV _Delayms_arg@0, A
	CALL _Delayms
	B0BTS1 0xD1.2
	JMP L40
	JMP L35
L40:
	B0BTS1 0xD1.3
	JMP L42
	JMP L35
L42:
	BSET _Funflag0.7
	B0BSET 0xC1.2
	B0BSET 0xC1.3
	JMP L35
L34:
	JMP L33
L35:
L32:
	RET
CALLTREE _ZhiJDeal invoke _Delayms
_Function_KeyeDeal_code SEGMENT CODE INBANK USING _Function_KeyeDeal_data
_KeyeDeal:
	BTS0 _Funflag0.5
	JMP L129
	BTS0 _Funflag1.0
	JMP L129
	BCLR X.7
	JMP L130
L129:
	BSET X.7
L130:
	BTS1 X.7
	JMP L45
L45:
L46:
L44:
	RET
_Function_AdccDeal_code SEGMENT CODE INBANK USING _Function_AdccDeal_data
_AdccDeal:
	BTS1 _Funflag1.1
	JMP L48
	JMP L47
L48:
	BTS0 _Funflag0.1
	JMP L50
	BSET _Funflag0.1
	B0BCLR 0xB8.0
	B0BSET 0xC1.0
	B0BCLR 0xD1.0
	MOV A, #0x02
	MOV _Delayms_arg@0, A
	CALL _Delayms
	JMP L51
L50:
	BTS0 _Funflag0.2
	JMP L52
	CLR (0xD9 &  0xFF)
	B0BCLR 0xC1.0
	B0BSET 0xB8.0
	B0BSET 0xD0.0
	B0BSET 0xD8.7
	NOP
	NOP
L54:
	MOV A, #0x5a
	B0MOV 0xCC, A
	MOV A, _JS1
	CMPRS A, #0x14
	B0BTS1	134.2
	JMP	L57
	JMP L56
L57:
	B0BTS1 0xD1.0
	JMP L59
	JMP L56
L59:
L55:
	JMP L54
L56:
	B0BCLR 0xD8.7
	B0MOV A, 0xD9
	ADD _RS_Cnt, A
	CLR (0xD9 &  0xFF)
	CLR _JS1
	B0BCLR 0xB8.0
	B0BSET 0xC1.0
	B0BCLR 0xD1.0
	BSET _Funflag0.2
	JMP L53
L52:
	BTS0 _Funflag0.3
	JMP L61
	BSET _Funflag0.3
	B0BCLR 0xB8.0
	B0BSET 0xC1.0
	B0BCLR 0xD1.0
	MOV A, #0x02
	MOV _Delayms_arg@0, A
	CALL _Delayms
	JMP L62
L61:
	BTS0 _Funflag0.4
	JMP L63
	CLR (0xD9 &  0xFF)
	B0BCLR 0xC1.0
	B0BCLR 0xB8.0
	B0BSET 0xD8.7
	NOP
	NOP
L65:
	MOV A, #0x5a
	B0MOV 0xCC, A
	MOV A, _JS1
	CMPRS A, #0x14
	B0BTS1	134.2
	JMP	L68
	JMP L67
L68:
	B0BTS1 0xD1.0
	JMP L70
	JMP L67
L70:
L66:
	JMP L65
L67:
	B0BCLR 0xD8.7
	B0MOV A, 0xD9
	ADD _RT_Cnt, A
	CLR _JS1
	CLR (0xD9 &  0xFF)
	B0BCLR 0xB8.0
	B0BSET 0xC1.0
	B0BCLR 0xD1.0
	BSET _Funflag0.4
	JMP L64
L63:
	INCMS _AD_Cnt
	NOP
	MOV A, _AD_Cnt
	CMPRS A, #0x08
	JMP L72
	CLR _AD_Cnt
	RRCM _RT_Cnt
	RRCM _RT_Cnt
	RRCM _RT_Cnt
	MOV A, #0x1F
	AND _RT_Cnt, A
	RRCM _RS_Cnt
	RRCM _RS_Cnt
	RRCM _RS_Cnt
	AND _RS_Cnt, A
	MOV A, #0xe6
	B0MOV L, A
	MOV A, _RS_Cnt
	CALL __MulInt2Reg
	MOV __SrcLArg0, A
	MOV A, _RT_Cnt
	MOV __SrcRArg0, A
	MOV A, #(_AD_value)$M
	B0MOV H, A
	MOV A, #(_AD_value)$L
	B0MOV L, A
	CALL __DivUInt2Ram
	MOV A, _AD_value
	SUB A, #0xe3
	B0BTS1	134.2
	JMP	L74
	MOV A, #0x01
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L75
	B0BSET 0xD1.3
	B0BSET 0xD1.2
	JMP L75
L74:
	MOV A, _AD_value
	SUB A, #0xce
	B0BTS1	134.2
	JMP	L78
	MOV A, #0x02
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L79
	B0BSET 0xD1.3
	B0BCLR 0xD1.2
	JMP L79
L78:
	MOV A, _AD_value
	SUB A, #0xad
	B0BTS1	134.2
	JMP	L82
	MOV A, #0x03
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L83
	B0BCLR 0xD1.3
	B0BCLR 0xD1.2
	JMP L83
L82:
	MOV A, _AD_value
	SUB A, #0x9b
	B0BTS1	134.2
	JMP	L86
	MOV A, #0x04
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L87
	B0BSET 0xD1.3
	B0BSET 0xD1.2
	JMP L87
L86:
	MOV A, _AD_value
	SUB A, #0x7d
	B0BTS1	134.2
	JMP	L90
	MOV A, #0x05
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L91
	B0BSET 0xD1.3
	B0BCLR 0xD1.2
	JMP L91
L90:
	MOV A, _AD_value
	SUB A, #0x67
	B0BTS1	134.2
	JMP	L94
	MOV A, #0x06
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L95
	B0BCLR 0xD1.3
	B0BCLR 0xD1.2
	JMP L95
L94:
	MOV A, _AD_value
	SUB A, #0x4b
	B0BTS1	134.2
	JMP	L98
	MOV A, #0x07
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L99
	B0BSET 0xD1.3
	B0BSET 0xD1.2
	JMP L99
L98:
	MOV A, _AD_value
	SUB A, #0x38
	B0BTS1	134.2
	JMP	L102
	MOV A, #0x08
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L103
	B0BSET 0xD1.3
	B0BCLR 0xD1.2
	JMP L103
L102:
	MOV A, _AD_value
	SUB A, #0x16
	B0BTS1	134.2
	JMP	L106
	MOV A, #0x09
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L107
	B0BCLR 0xD1.3
	B0BCLR 0xD1.2
	JMP L107
L106:
	MOV A, _AD_value
	SUB A, #0x05
	B0BTS1	134.2
	JMP	L110
	MOV A, #0x0a
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L111
	B0BSET 0xD1.3
	B0BSET 0xD1.2
	JMP L111
L110:
	MOV A, _AD_value
	SUB A, #0x05
	b0bts0	134.2
	JMP	L114
	MOV A, #0x0b
	MOV _WorkGear, A
	BTS1 _Funflag0.7
	JMP L116
	B0BSET 0xD1.3
	B0BCLR 0xD1.2
L116:
L114:
L111:
L107:
L103:
L99:
L95:
L91:
L87:
L83:
L79:
L75:
L72:
	BCLR _Funflag0.1
	BCLR _Funflag0.2
	BCLR _Funflag0.3
	BCLR _Funflag0.4
L64:
L62:
L53:
L51:
L47:
	RET
CALLTREE _AdccDeal invoke _Delayms,__MulInt2Reg,__DivUInt2Ram
_Function_main_code SEGMENT CODE INBANK USING _Function_main_data
_main:
	CALL _Sys_Init
L119:
	MOV A, #0x5a
	B0MOV 0xCC, A
	BTS1 _Funflag1.2
	JMP L122
	B0BCLR 0xD5.4
	B0BSET 0xD1.3
	B0BSET 0xD1.2
	JMP L123
L122:
	CALL _TimeDeal
	CALL _AdccDeal
	B0BSET 0xD5.4
L123:
L120:
	JMP L119
L118:
_main_end:
CALLTREE _main invoke _Sys_Init,_TimeDeal,_AdccDeal
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
	B0BTS1 0xC8.5
	JMP L125
	B0BCLR 0xC8.5
	INCMS _JS1
	NOP
	INCMS _TimerCnt
	NOP
	MOV A, _TimerCnt
	CMPRS A, #0xf9
	B0BTS1	134.2
	JMP	L127
	CLR _TimerCnt
	INCMS _WorkBuff
	NOP
L127:
L125:
L124:
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
extern data __SrcRArg0
extern data __SrcLArg0
EXTERN CODE __DivUInt2Ram
EXTERN CODE __MulInt2Reg
