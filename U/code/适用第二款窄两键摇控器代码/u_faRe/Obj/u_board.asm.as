CHIP SN8P2501D
EXTERN DATA X
EXTERN DATA H
EXTERN DATA L
EXTERN DATA T
EXTERN DATA I
.CODE
.stabs "lcc4_compiled.",0x3C,0,0,0
.stabs "C:\Users\zyb\Desktop\delayTimer\U\code\u_faRe/",0x64,0,3,Ltext0
.stabs ".\Src\u_board.c",0x64,0,3,Ltext0
Ltext0:
.stabs "int:t1=r1;-128;127;",128,0,0,0
.stabs "char:t2=r2;-128;127;",128,0,0,0
.stabs "double:t3=r1;4;0;",128,0,0,0
.stabs "float:t4=r1;4;0;",128,0,0,0
.stabs "long double:t5=r1;4;0;",128,0,0,0
.stabs "long int:t6=r1;-32768;32767;",128,0,0,0
.stabs "long long int:t7=r1;-2147483648;2147483647;",128,0,0,0
.stabs "signed char:t8=r1;-128;127;",128,0,0,0
.stabs "unsigned char:t9=r1;0;255;",128,0,0,0
.stabs "unsigned long:t10=r1;0;65535;",128,0,0,0
.stabs "unsigned long long:t11=r1;0;4294967295;",128,0,0,0
.stabs "unsigned int:t12=r1;0;255;",128,0,0,0
.stabs "void:t13=13",128,0,0,0
.stabs "bit:t14",128,0,0,0
.stabs ":t300=L16:0",128,0,0,0
.stabs ":t301=L16:1",128,0,0,0
.stabs ":t302=L16:2",128,0,0,0
.stabs ":t303=L16:3",128,0,0,0
.stabs ":t304=L16:4",128,0,0,0
.stabs ":t305=L16:5",128,0,0,0
.stabs ":t306=L16:6",128,0,0,0
.stabs ":t307=L16:7",128,0,0,0
.stabs ":t308=ar1;0;9;1",128,0,0,0
PUBLIC _IR_Flag
PUBLIC _IR_time
PUBLIC _Touch_flag
PUBLIC _touch_preFlag
PUBLIC _edgeFlag
PUBLIC _IR_data_deal_flag
PUBLIC _secFlag
PUBLIC _IR_count
PUBLIC _IRdata_len
PUBLIC _isRec
PUBLIC _buzzerFlag
PUBLIC _buzzerEnableFlag
PUBLIC _Sys_Init
PUBLIC _rdelay_acton_fun_arg@0
PUBLIC _main
PUBLIC _ISR_isr
PUBLIC _IRdata
_IRdata@segment SEGMENT DATA INBANK
	_IRdata DS 10
_IR_bit@segment SEGMENT DATA INBANK
	_IR_bit DS 1
PUBLIC _sysFunFlag
PUBLIC _timeFunFlag
PUBLIC _Touch_time
_Touch_time@segment SEGMENT DATA INBANK
	_Touch_time DS 1
PUBLIC _IR_data
_IR_data@segment SEGMENT DATA INBANK
	_IR_data DS 9
PUBLIC _SDian_bz
_SDian_bz@segment BITSEGMENT DATA AT 46 INBANK
	_SDian_bz DSBIT 1
PUBLIC _SDian_Cnt
_SDian_Cnt@segment SEGMENT DATA AT 47 INBANK
	_SDian_Cnt DS 1
_u_board_c_GlobalBitDataPool0 BITSEGMENT DATA BANK 0 INBANK
	_IR_Flag DSBIT 1
	_Touch_flag DSBIT 1
	_touch_preFlag DSBIT 1
	_edgeFlag DSBIT 1
	_IR_data_deal_flag DSBIT 1
	_isRec DSBIT 1
	_buzzerFlag DSBIT 1
	_buzzerEnableFlag DSBIT 1
_u_board_c_GlobalBitDataPool1 BITSEGMENT DATA BANK 0 INBANK
	_sysFunFlag DSBIT 1
	_timeFunFlag DSBIT 1
_IR_time@segment SEGMENT DATA INBANK
	_IR_time DS 1
_btn_value@segment SEGMENT DATA INBANK
	_btn_value DS 1
_secFlag@segment SEGMENT DATA INBANK
	_secFlag DS 1
_IR_count@segment SEGMENT DATA INBANK
	_IR_count DS 1
_IRdata_len@segment SEGMENT DATA INBANK
	_IRdata_len DS 1
_Function_Sys_Init_data SEGMENT DATA INBANK
_Function_touch_check_data SEGMENT DATA INBANK
_Function_touch_deal_data SEGMENT DATA INBANK
_Function_IR_Data_deal_data SEGMENT DATA INBANK
	_IR_Data_deal_data@0	DS	1
	_IR_Data_deal_data@1	DS	1
	_IR_Data_deal_data@2	DS	1
	_IR_Data_deal_data@3	DS	1
_Function_IR_decode_data SEGMENT DATA INBANK
	_IR_decode_data@0	DS	1
	_IR_decode_data@1	DS	1
	_IR_decode_data@2	DS	1
_Function_rdelay_acton_fun_data SEGMENT DATA INBANK
	_rdelay_acton_fun_arg@0 DS 1
_Function_main_data SEGMENT DATA INBANK
	_main_data@0	DS	1
_sdata321@segment SEGMENT DATA INBANK
	_sdata321 DS 1
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
	W2 DS 1
	W3 DS 1
	W4 DS 1
	W5 DS 1
_VirtualRegIsr SEGMENT DATA BANK 0 INBANK COMMON
	WG DS 1
	WH DS 1
	WI DS 1
	WJ DS 1
.stabs "R:G12",32,0,0,0x82
.stabs "Z:G12",32,0,0,0x83
.stabs "Y:G12",32,0,0,0x84
.stabs "PFLAG:G12",32,0,0,0x86
.stabs "FZ:G300",32,0,0,0x86
.stabs "FDC:G301",32,0,0,0x86
.stabs "FC:G302",32,0,0,0x86
.stabs "FLVD24:G304",32,0,0,0x86
.stabs "FLVD36:G305",32,0,0,0x86
.stabs "FNPD:G306",32,0,0,0x86
.stabs "FNT0:G307",32,0,0,0x86
.stabs "P0M:G12",32,0,0,0xB8
.stabs "FP00M:G300",32,0,0,0xB8
.stabs "PEDGE:G12",32,0,0,0xBF
.stabs "FP00G1:G304",32,0,0,0xBF
.stabs "FP00G0:G303",32,0,0,0xBF
.stabs "P1W:G12",32,0,0,0xC0
.stabs "P1M:G12",32,0,0,0xC1
.stabs "FP10M:G300",32,0,0,0xC1
.stabs "FP12M:G302",32,0,0,0xC1
.stabs "FP13M:G303",32,0,0,0xC1
.stabs "P2M:G12",32,0,0,0xC2
.stabs "FP20M:G300",32,0,0,0xC2
.stabs "FP21M:G301",32,0,0,0xC2
.stabs "FP22M:G302",32,0,0,0xC2
.stabs "FP23M:G303",32,0,0,0xC2
.stabs "FP24M:G304",32,0,0,0xC2
.stabs "FP25M:G305",32,0,0,0xC2
.stabs "P5M:G12",32,0,0,0xC5
.stabs "FP54M:G304",32,0,0,0xC5
.stabs "INTRQ:G12",32,0,0,0xC8
.stabs "FP00IRQ:G300",32,0,0,0xC8
.stabs "FT0IRQ:G304",32,0,0,0xC8
.stabs "FTC0IRQ:G305",32,0,0,0xC8
.stabs "INTEN:G12",32,0,0,0xC9
.stabs "FP00IEN:G300",32,0,0,0xC9
.stabs "FT0IEN:G304",32,0,0,0xC9
.stabs "FTC0IEN:G305",32,0,0,0xC9
.stabs "OSCM:G12",32,0,0,0xCA
.stabs "FCPUM1:G304",32,0,0,0xCA
.stabs "FCPUM0:G303",32,0,0,0xCA
.stabs "FCLKMD:G302",32,0,0,0xCA
.stabs "FSTPHX:G301",32,0,0,0xCA
.stabs "WDTR:G12",32,0,0,0xCC
.stabs "TC0R:G12",32,0,0,0xCD
.stabs "PCL:G12",32,0,0,0xCE
.stabs "PCH:G12",32,0,0,0xCF
.stabs "P0:G12",32,0,0,0xD0
.stabs "FP00:G300",32,0,0,0xD0
.stabs "P1:G12",32,0,0,0xD1
.stabs "FP10:G300",32,0,0,0xD1
.stabs "FP11:G301",32,0,0,0xD1
.stabs "FP12:G302",32,0,0,0xD1
.stabs "FP13:G303",32,0,0,0xD1
.stabs "P2:G12",32,0,0,0xD2
.stabs "FP20:G300",32,0,0,0xD2
.stabs "FP21:G301",32,0,0,0xD2
.stabs "FP22:G302",32,0,0,0xD2
.stabs "FP23:G303",32,0,0,0xD2
.stabs "FP24:G304",32,0,0,0xD2
.stabs "FP25:G305",32,0,0,0xD2
.stabs "P5:G12",32,0,0,0xD5
.stabs "FP54:G304",32,0,0,0xD5
.stabs "T0M:G12",32,0,0,0xD8
.stabs "FT0TB:G300",32,0,0,0xD8
.stabs "FT0RATE0:G304",32,0,0,0xD8
.stabs "FT0RATE1:G305",32,0,0,0xD8
.stabs "FT0RATE2:G306",32,0,0,0xD8
.stabs "FT0ENB:G307",32,0,0,0xD8
.stabs "T0C:G12",32,0,0,0xD9
.stabs "TC0M:G12",32,0,0,0xDA
.stabs "FTC0ENB:G307",32,0,0,0xDA
.stabs "FTC0RATE2:G306",32,0,0,0xDA
.stabs "FTC0RATE1:G305",32,0,0,0xDA
.stabs "FTC0RATE0:G304",32,0,0,0xDA
.stabs "FTC0CKS:G303",32,0,0,0xDA
.stabs "FALOAD0:G302",32,0,0,0xDA
.stabs "FTC0OUT:G301",32,0,0,0xDA
.stabs "FPWM0OUT:G300",32,0,0,0xDA
.stabs "TC0C:G12",32,0,0,0xDB
.stabs "STKP:G12",32,0,0,0xDF
.stabs "FGIE:G307",32,0,0,0xDF
.stabs "FSTKPB1:G301",32,0,0,0xDF
.stabs "FSTKPB0:G300",32,0,0,0xDF
.stabs "P0UR:G12",32,0,0,0xE0
.stabs "FP00R:G300",32,0,0,0xE0
.stabs "P1UR:G12",32,0,0,0xE1
.stabs "FP10R:G300",32,0,0,0xE1
.stabs "FP12R:G302",32,0,0,0xE1
.stabs "FP13R:G303",32,0,0,0xE1
.stabs "P2UR:G12",32,0,0,0xE2
.stabs "FP20R:G300",32,0,0,0xE2
.stabs "FP21R:G301",32,0,0,0xE2
.stabs "FP22R:G302",32,0,0,0xE2
.stabs "FP23R:G303",32,0,0,0xE2
.stabs "FP24R:G304",32,0,0,0xE2
.stabs "FP25R:G305",32,0,0,0xE2
.stabs "P5UR:G12",32,0,0,0xE5
.stabs "FP54R:G304",32,0,0,0xE5
.stabs "_YZ:G12",32,0,0,0xE7
.stabs "P1OC:G12",32,0,0,0xE9
.stabs "STK3L:G12",32,0,0,0xF8
.stabs "STK3H:G12",32,0,0,0xF9
.stabs "STK2L:G12",32,0,0,0xFA
.stabs "STK2H:G12",32,0,0,0xFB
.stabs "STK1L:G12",32,0,0,0xFC
.stabs "STK1H:G12",32,0,0,0xFD
.stabs "STK0L:G12",32,0,0,0xFE
.stabs "STK0H:G12",32,0,0,0xFF
.stabs "IR_Flag:G300",32,0,0,_IR_Flag
.stabs "IR_time:G9",32,0,0,_IR_time
.stabs "Touch_flag:G301",32,0,0,_Touch_flag
.stabs "touch_preFlag:G302",32,0,0,_touch_preFlag
.stabs "edgeFlag:G303",32,0,0,_edgeFlag
.stabs "IR_data_deal_flag:G304",32,0,0,_IR_data_deal_flag
.stabs "btn_value:S9",38,0,0,_btn_value
.stabs "secFlag:G9",32,0,0,_secFlag
.stabs "IR_count:G9",32,0,0,_IR_count
.stabs "IRdata_len:G9",32,0,0,_IRdata_len
.stabs "isRec:G305",32,0,0,_isRec
.stabs "buzzerFlag:G306",32,0,0,_buzzerFlag
.stabs "buzzerEnableFlag:G307",32,0,0,_buzzerEnableFlag
.stabs "Sys_Init:F13",36,0,0,_Sys_Init
_Function_Sys_Init_code SEGMENT CODE INBANK USING _Function_Sys_Init_data
_Sys_Init:
.stabn 0xC0,0,0,L2-_Sys_Init
L2:
.stabn 0x44,0,92,L3-_Sys_Init
L3:
 .stabn 0x44,0,93,L4-_Sys_Init
L4:
	CLR (0xCA &  0xFF)
.stabn 0x44,0,94,L5-_Sys_Init
L5:
	CLR (0xC9 &  0xFF)
.stabn 0x44,0,95,L6-_Sys_Init
L6:
	CLR (0xC8 &  0xFF)
.stabn 0x44,0,98,L7-_Sys_Init
L7:
	MOV A, #0xfe
	B0MOV 0xB8, A
.stabn 0x44,0,99,L8-_Sys_Init
L8:
	MOV A, #0xef
	B0MOV 0xC2, A
.stabn 0x44,0,101,L9-_Sys_Init
L9:
	MOV A, #0xfb
	B0MOV 0xC1, A
.stabn 0x44,0,102,L10-_Sys_Init
L10:
	MOV A, #0xff
	B0MOV 0xC5, A
.stabn 0x44,0,104,L11-_Sys_Init
L11:
	MOV A, #0x01
	B0MOV 0xE0, A
.stabn 0x44,0,105,L12-_Sys_Init
L12:
	CLR (0xE2 &  0xFF)
.stabn 0x44,0,106,L13-_Sys_Init
L13:
	CLR (0xE1 &  0xFF)
.stabn 0x44,0,107,L14-_Sys_Init
L14:
	CLR (0xE5 &  0xFF)
.stabn 0x44,0,109,L15-_Sys_Init
L15:
	B0BCLR 0xD1.3
.stabn 0x44,0,110,L16-_Sys_Init
L16:
	B0BCLR 0xD1.2
.stabn 0x44,0,111,L17-_Sys_Init
L17:
	B0BCLR 0xD2.4
.stabn 0x44,0,112,L18-_Sys_Init
L18:
	B0BSET 0xD1.0
.stabn 0x44,0,113,L19-_Sys_Init
L19:
	B0BSET 0xD5.4
.stabn 0x44,0,116,L20-_Sys_Init
L20:
	MOV A, #0x10
	B0MOV 0xBF, A
.stabn 0x44,0,118,L21-_Sys_Init
L21:
	B0BCLR 0xC8.0
.stabn 0x44,0,119,L22-_Sys_Init
L22:
	B0BSET 0xC9.0
.stabn 0x44,0,120,L23-_Sys_Init
L23:
	BSET _edgeFlag
.stabn 0x44,0,123,L24-_Sys_Init
L24:
	MOV A, #0x70
	B0MOV 0xD8, A
.stabn 0x44,0,125,L25-_Sys_Init
L25:
	MOV A, #0xba
	B0MOV 0xD9, A
.stabn 0x44,0,126,L26-_Sys_Init
L26:
	B0BCLR 0xC8.4
.stabn 0x44,0,127,L27-_Sys_Init
L27:
	B0BSET 0xC9.4
.stabn 0x44,0,128,L28-_Sys_Init
L28:
	B0BSET 0xD8.7
.stabn 0x44,0,130,L29-_Sys_Init
L29:
	MOV A, #0x70
	B0MOV 0xDA, A
.stabn 0x44,0,131,L30-_Sys_Init
L30:
	MOV A, #0x83
	B0MOV 0xCD, A
.stabn 0x44,0,132,L31-_Sys_Init
L31:
	B0MOV 0xDB, A
.stabn 0x44,0,133,L32-_Sys_Init
L32:
	B0BSET 0xDA.2
.stabn 0x44,0,134,L33-_Sys_Init
L33:
	B0BCLR 0xDA.1
.stabn 0x44,0,135,L34-_Sys_Init
L34:
	B0BCLR 0xDA.0
.stabn 0x44,0,136,L35-_Sys_Init
L35:
	B0BSET 0xC9.5
.stabn 0x44,0,137,L36-_Sys_Init
L36:
	B0BSET 0xDA.7
.stabn 0x44,0,139,L37-_Sys_Init
L37:
	B0BSET 0xDF.7
.stabn 0xE0,0,0,L38-_Sys_Init
L38:
.stabn 0x44,0,140,L39-_Sys_Init
L39:
L1:
	RET
.stabs "touch_check:f9",36,0,0,_touch_check
_Function_touch_check_code SEGMENT CODE INBANK USING _Function_touch_check_data
_touch_check:
.stabn 0xC0,0,0,L51-_touch_check
L51:
.stabn 0x44,0,144,L52-_touch_check
L52:
 .stabn 0x44,0,145,L53-_touch_check
L53:
	B0BTS0 0xD2.3
	JMP L41
.stabn 0xC0,0,1,L54-_touch_check
L54:
.stabn 0x44,0,146,L55-_touch_check
L55:
 .stabn 0x44,0,147,L56-_touch_check
L56:
	BTS1 _Touch_flag
	JMP L43
.stabn 0x44,0,148,L57-_touch_check
L57:
	CLR _Touch_time
	JMP L42
L43:
.stabn 0x44,0,149,L58-_touch_check
L58:
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
	JMP	L42
	B0BTS1	134.2
	JMP	L42
.stabn 0xC0,0,2,L59-_touch_check
L59:
.stabn 0x44,0,150,L60-_touch_check
L60:
 .stabn 0x44,0,151,L61-_touch_check
L61:
	CLR _Touch_time
.stabn 0x44,0,152,L62-_touch_check
L62:
	BSET _Touch_flag
.stabn 0x44,0,154,L63-_touch_check
L63:
	MOV A, #0x01
	JMP L40
.stabn 0xE0,0,2,L64-_touch_check
L64:
.stabn 0x44,0,155,L65-_touch_check
L65:
 .stabn 0xE0,0,1,L66-_touch_check
L66:
.stabn 0x44,0,156,L67-_touch_check
L67:
L41:
.stabn 0xC0,0,1,L68-_touch_check
L68:
.stabn 0x44,0,158,L69-_touch_check
L69:
 .stabn 0x44,0,159,L70-_touch_check
L70:
	BTS1 _Touch_flag
	JMP L47
.stabn 0xC0,0,2,L71-_touch_check
L71:
.stabn 0x44,0,160,L72-_touch_check
L72:
 .stabn 0x44,0,161,L73-_touch_check
L73:
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
	JMP	L48
	B0BTS1	134.2
	JMP	L48
.stabn 0xC0,0,3,L74-_touch_check
L74:
.stabn 0x44,0,162,L75-_touch_check
L75:
 .stabn 0x44,0,163,L76-_touch_check
L76:
	CLR _Touch_time
.stabn 0x44,0,164,L77-_touch_check
L77:
	BCLR _Touch_flag
.stabn 0xE0,0,3,L78-_touch_check
L78:
.stabn 0x44,0,166,L79-_touch_check
L79:
 .stabn 0xE0,0,2,L80-_touch_check
L80:
.stabn 0x44,0,167,L81-_touch_check
L81:
	JMP L48
L47:
.stabn 0x44,0,168,L82-_touch_check
L82:
	CLR _Touch_time
L48:
.stabn 0xE0,0,1,L83-_touch_check
L83:
.stabn 0x44,0,170,L84-_touch_check
L84:
L42:
.stabn 0x44,0,171,L85-_touch_check
L85:
	MOV A, #0x00
.stabn 0xE0,0,0,L86-_touch_check
L86:
.stabn 0x44,0,172,L87-_touch_check
L87:
L40:
	RET
CALLTREE _touch_check invoke __CmpLong
.stabs "touch_deal:f13",36,0,0,_touch_deal
_Function_touch_deal_code SEGMENT CODE INBANK USING _Function_touch_deal_data
_touch_deal:
.stabn 0xC0,0,0,L95-_touch_deal
L95:
.stabn 0x44,0,175,L96-_touch_deal
L96:
 .stabn 0x44,0,176,L97-_touch_deal
L97:
	BTS1 _Touch_flag
	JMP L89
.stabn 0xC0,0,1,L98-_touch_deal
L98:
.stabn 0x44,0,177,L99-_touch_deal
L99:
 .stabn 0x44,0,178,L100-_touch_deal
L100:
	BTS0 _touch_preFlag
	JMP L90
.stabn 0xC0,0,2,L101-_touch_deal
L101:
.stabn 0x44,0,179,L102-_touch_deal
L102:
 .stabn 0x44,0,180,L103-_touch_deal
L103:
	BSET _touch_preFlag
.stabn 0x44,0,181,L104-_touch_deal
L104:
	INCMS _btn_value
	NOP
.stabn 0x44,0,183,L105-_touch_deal
L105:
	MOV A, _btn_value
	SUB A, #0x04
	B0BTS1	134.2
	JMP	L93
.stabn 0x44,0,184,L106-_touch_deal
L106:
	MOV A, #0x01
	MOV _btn_value, A
L93:
.stabn 0x44,0,185,L107-_touch_deal
L107:
	MOV A, _btn_value
	MOV _rdelay_acton_fun_arg@0, A
	CALL _rdelay_acton_fun
.stabn 0xE0,0,2,L108-_touch_deal
L108:
.stabn 0x44,0,186,L109-_touch_deal
L109:
 .stabn 0xE0,0,1,L110-_touch_deal
L110:
.stabn 0x44,0,187,L111-_touch_deal
L111:
	JMP L90
L89:
.stabn 0xC0,0,1,L112-_touch_deal
L112:
.stabn 0x44,0,189,L113-_touch_deal
L113:
 .stabn 0x44,0,190,L114-_touch_deal
L114:
	BCLR _touch_preFlag
.stabn 0xE0,0,1,L115-_touch_deal
L115:
.stabn 0x44,0,191,L116-_touch_deal
L116:
L90:
.stabn 0xE0,0,0,L117-_touch_deal
L117:
.stabn 0x44,0,192,L118-_touch_deal
L118:
L88:
	RET
CALLTREE _touch_deal invoke _rdelay_acton_fun
.stabs "IR_Data_deal:f13",36,0,0,_IR_Data_deal
_Function_IR_Data_deal_code SEGMENT CODE INBANK USING _Function_IR_Data_deal_data
_IR_Data_deal:
.stabs "dat:9",128,0,0,_IR_Data_deal_data@0
.stabs "i:9",128,0,0,_IR_Data_deal_data@1
.stabs "light:9",128,0,0,_IR_Data_deal_data@2
.stabs "onoff:9",128,0,0,_IR_Data_deal_data@3
.stabn 0xC0,0,0,L147-_IR_Data_deal
L147:
.stabn 0x44,0,197,L148-_IR_Data_deal
L148:
 .stabn 0x44,0,198,L149-_IR_Data_deal
L149:
	CLR _IR_Data_deal_data@2
.stabn 0x44,0,198,L150-_IR_Data_deal
L150:
	CLR _IR_Data_deal_data@3
.stabn 0xC0,0,1,L151-_IR_Data_deal
L151:
.stabn 0x44,0,200,L152-_IR_Data_deal
L152:
	CLR _IR_Data_deal_data@1
	JMP L123
L120:
.stabn 0xC0,0,2,L153-_IR_Data_deal
L153:
.stabn 0x44,0,201,L154-_IR_Data_deal
L154:
 .stabn 0x44,0,202,L155-_IR_Data_deal
L155:
	MOV A, _IR_Data_deal_data@1
	B0MOV 132, #(_IRdata)$M
	B0MOV 131, #(_IRdata)$L
	B0ADD 131, A
	B0MOV A, 231
	CMPRS A, #0xbb
	JMP L124
.stabn 0x44,0,203,L156-_IR_Data_deal
L156:
	INCMS _IR_Data_deal_data@2
	NOP
	JMP L125
L124:
.stabn 0x44,0,204,L157-_IR_Data_deal
L157:
	MOV A, _IR_Data_deal_data@1
	B0MOV 132, #(_IRdata)$M
	B0MOV 131, #(_IRdata)$L
	B0ADD 131, A
	B0MOV A, 231
	CMPRS A, #0x1b
	JMP L126
.stabn 0x44,0,205,L158-_IR_Data_deal
L158:
	INCMS _IR_Data_deal_data@3
	NOP
L126:
L125:
.stabn 0xE0,0,2,L159-_IR_Data_deal
L159:
.stabn 0x44,0,206,L160-_IR_Data_deal
L160:
L121:
.stabn 0x44,0,200,L161-_IR_Data_deal
L161:
	INCMS _IR_Data_deal_data@1
	NOP
L123:
.stabn 0x44,0,200,L162-_IR_Data_deal
L162:
	MOV A, _IR_Data_deal_data@1
	SUB A, _IRdata_len
	B0BTS1	134.2
	JMP	L120
.stabn 0xE0,0,1,L163-_IR_Data_deal
L163:
.stabn 0x44,0,207,L164-_IR_Data_deal
L164:
 .stabn 0x44,0,207,L165-_IR_Data_deal
L165:
	B0BCLR 134.2
	RRC _IRdata_len
	B0MOV W0, A
	MOV A, _IR_Data_deal_data@2
	CMPRS A, W0
	B0BTS1	134.2
	JMP	L128
.stabn 0x44,0,208,L166-_IR_Data_deal
L166:
	MOV A, #0xbb
	MOV _IR_Data_deal_data@0, A
	JMP L129
L128:
.stabn 0x44,0,209,L167-_IR_Data_deal
L167:
	B0BCLR 134.2
	RRC _IRdata_len
	B0MOV W0, A
	MOV A, _IR_Data_deal_data@3
	CMPRS A, W0
	B0BTS1	134.2
	JMP	L130
.stabn 0x44,0,210,L168-_IR_Data_deal
L168:
	MOV A, #0x1b
	MOV _IR_Data_deal_data@0, A
L130:
L129:
.stabn 0xC0,0,1,L169-_IR_Data_deal
L169:
.stabn 0x44,0,212,L170-_IR_Data_deal
L170:
	CLR _IR_Data_deal_data@1
	JMP L135
L132:
.stabn 0x44,0,213,L171-_IR_Data_deal
L171:
	MOV A, _IR_Data_deal_data@1
	B0MOV 132, #(_IRdata)$M
	B0MOV 131, #(_IRdata)$L
	B0ADD 131, A
	MOV A, #0x00
	B0MOV 231, A
L133:
.stabn 0x44,0,212,L172-_IR_Data_deal
L172:
	INCMS _IR_Data_deal_data@1
	NOP
L135:
.stabn 0x44,0,212,L173-_IR_Data_deal
L173:
	MOV A, _IR_Data_deal_data@1
	SUB A, #0x0a
	B0BTS1	134.2
	JMP	L132
.stabn 0xE0,0,1,L174-_IR_Data_deal
L174:
.stabn 0x44,0,214,L175-_IR_Data_deal
L175:
 .stabn 0x44,0,214,L176-_IR_Data_deal
L176:
	CLR _IRdata_len
.stabn 0x44,0,216,L177-_IR_Data_deal
L177:
	MOV A, _IR_Data_deal_data@0
	SUB A, #0xbb
	B0BTS0	134.0
	JMP	L138
	MOV A, _IR_Data_deal_data@0
	XOR A, #0x80
	SUB A, #0x3B
	B0BTS1	134.2
	JMP	L119
L146:
	MOV A, _IR_Data_deal_data@0
	SUB A, #0x1b
	B0BTS0	134.0
	JMP	L143
	JMP L119
.stabn 0xC0,0,1,L178-_IR_Data_deal
L178:
.stabn 0x44,0,217,L179-_IR_Data_deal
L179:
L138:
.stabn 0x44,0,219,L180-_IR_Data_deal
L180:
	BTS1 _sysFunFlag
	JMP L137
.stabn 0xC0,0,2,L181-_IR_Data_deal
L181:
.stabn 0x44,0,220,L182-_IR_Data_deal
L182:
 .stabn 0x44,0,221,L183-_IR_Data_deal
L183:
	INCMS _btn_value
	NOP
.stabn 0x44,0,222,L184-_IR_Data_deal
L184:
	MOV A, _btn_value
	SUB A, #0x04
	B0BTS1	134.2
	JMP	L137
.stabn 0x44,0,223,L185-_IR_Data_deal
L185:
	MOV A, #0x01
	MOV _btn_value, A
.stabn 0xE0,0,2,L186-_IR_Data_deal
L186:
.stabn 0x44,0,224,L187-_IR_Data_deal
L187:
 .stabn 0x44,0,225,L188-_IR_Data_deal
L188:
	JMP L137
L143:
.stabn 0x44,0,227,L189-_IR_Data_deal
L189:
	BTS1 _sysFunFlag
	JMP L144
.stabn 0xC0,0,2,L190-_IR_Data_deal
L190:
.stabn 0x44,0,228,L191-_IR_Data_deal
L191:
 .stabn 0x44,0,229,L192-_IR_Data_deal
L192:
	BCLR _sysFunFlag
.stabn 0x44,0,230,L193-_IR_Data_deal
L193:
	CLR _btn_value
.stabn 0xE0,0,2,L194-_IR_Data_deal
L194:
.stabn 0x44,0,231,L195-_IR_Data_deal
L195:
	JMP L137
L144:
.stabn 0xC0,0,2,L196-_IR_Data_deal
L196:
.stabn 0x44,0,233,L197-_IR_Data_deal
L197:
 .stabn 0x44,0,234,L198-_IR_Data_deal
L198:
	BSET _sysFunFlag
.stabn 0x44,0,235,L199-_IR_Data_deal
L199:
	MOV A, #0x01
	MOV _btn_value, A
.stabn 0xE0,0,2,L200-_IR_Data_deal
L200:
.stabn 0x44,0,236,L201-_IR_Data_deal
L201:
 .stabn 0x44,0,238,L202-_IR_Data_deal
L202:
 .stabn 0x44,0,240,L203-_IR_Data_deal
L203:
 .stabn 0xE0,0,1,L204-_IR_Data_deal
L204:
.stabn 0x44,0,241,L205-_IR_Data_deal
L205:
L137:
.stabn 0x44,0,243,L206-_IR_Data_deal
L206:
	MOV A, _btn_value
	MOV _rdelay_acton_fun_arg@0, A
	CALL _rdelay_acton_fun
.stabn 0xE0,0,0,L207-_IR_Data_deal
L207:
.stabn 0x44,0,245,L208-_IR_Data_deal
L208:
L119:
	RET
CALLTREE _IR_Data_deal invoke _rdelay_acton_fun
.stabs "IR_decode:f9",36,0,0,_IR_decode
_Function_IR_decode_code SEGMENT CODE INBANK USING _Function_IR_decode_data
_IR_decode:
.stabs "j:9",128,0,0,_IR_decode_data@0
.stabs "k:9",128,0,0,_IR_decode_data@1
.stabs "IR_Value:9",128,0,0,_IR_decode_data@2
.stabn 0xC0,0,0,L218-_IR_decode
L218:
.stabn 0x44,0,248,L219-_IR_decode
L219:
 .stabn 0x44,0,250,L220-_IR_decode
L220:
	CLR _IR_decode_data@2
.stabn 0x44,0,251,L221-_IR_decode
L221:
	MOV A, #0x01
	MOV _IR_decode_data@1, A
.stabn 0xC0,0,1,L222-_IR_decode
L222:
.stabn 0x44,0,253,L223-_IR_decode
L223:
	CLR _IR_decode_data@0
	JMP L213
L210:
.stabn 0xC0,0,2,L224-_IR_decode
L224:
.stabn 0x44,0,254,L225-_IR_decode
L225:
 .stabn 0x44,0,255,L226-_IR_decode
L226:
	MOV A, _IR_decode_data@1
	B0MOV 132, #(_IR_data)$M
	B0MOV 131, #(_IR_data)$L
	B0ADD 131, A
	B0MOV A, 231
	CMPRS A, #0x05
	B0BTS1	134.2
	JMP	L214
.stabn 0x44,0,256,L227-_IR_decode
L227:
	MOV A, #0x80
	OR _IR_decode_data@2, A
L214:
.stabn 0x44,0,257,L228-_IR_decode
L228:
	MOV A, _IR_decode_data@0
	SUB A, #0x07
	b0bts0	134.2
	JMP	L216
.stabn 0x44,0,258,L229-_IR_decode
L229:
	B0BCLR 134.2
	RRCM _IR_decode_data@2
L216:
.stabn 0x44,0,259,L230-_IR_decode
L230:
	INCMS _IR_decode_data@1
	NOP
.stabn 0xE0,0,2,L231-_IR_decode
L231:
.stabn 0x44,0,260,L232-_IR_decode
L232:
L211:
.stabn 0x44,0,253,L233-_IR_decode
L233:
	INCMS _IR_decode_data@0
	NOP
L213:
.stabn 0x44,0,253,L234-_IR_decode
L234:
	MOV A, _IR_decode_data@0
	CMPRS A, #0x07
	B0BTS1	134.2
	JMP	L210
.stabn 0xE0,0,1,L235-_IR_decode
L235:
.stabn 0x44,0,262,L236-_IR_decode
L236:
 .stabn 0x44,0,262,L237-_IR_decode
L237:
	MOV A, _IR_decode_data@2
.stabn 0xE0,0,0,L238-_IR_decode
L238:
.stabn 0x44,0,263,L239-_IR_decode
L239:
L209:
	RET
.stabs "rdelay_acton_fun:f13",36,0,0,_rdelay_acton_fun
_Function_rdelay_acton_fun_code SEGMENT CODE INBANK USING _Function_rdelay_acton_fun_data
_rdelay_acton_fun:
.stabs "action_value:p9",160,0,0,_rdelay_acton_fun_arg@0
.stabn 0xC0,0,0,L247-_rdelay_acton_fun
L247:
.stabn 0x44,0,265,L248-_rdelay_acton_fun
L248:
 .stabn 0x44,0,269,L249-_rdelay_acton_fun
L249:
	MOV A, _rdelay_acton_fun_arg@0
	ADD A, #0x80
	CMPRS A, #0x84
	B0BTS0 134.2
	JMP L446
	SUB A, #0x80
	B0BTS1 134.2
	JMP L446
	B0ADD 206, A
	JMP L243
	JMP L244
	JMP L245
	JMP L246
L446:
	JMP L242
.stabn 0xC0,0,1,L250-_rdelay_acton_fun
L250:
.stabn 0x44,0,270,L251-_rdelay_acton_fun
L251:
L243:
.stabn 0x44,0,272,L252-_rdelay_acton_fun
L252:
	B0BCLR 0xD1.3
.stabn 0x44,0,273,L253-_rdelay_acton_fun
L253:
	B0BCLR 0xD1.2
.stabn 0x44,0,274,L254-_rdelay_acton_fun
L254:
	JMP L242
L244:
.stabn 0x44,0,276,L255-_rdelay_acton_fun
L255:
	B0BSET 0xD1.3
.stabn 0x44,0,277,L256-_rdelay_acton_fun
L256:
	B0BCLR 0xD1.2
.stabn 0x44,0,278,L257-_rdelay_acton_fun
L257:
	JMP L242
L245:
.stabn 0x44,0,280,L258-_rdelay_acton_fun
L258:
	B0BCLR 0xD1.3
.stabn 0x44,0,281,L259-_rdelay_acton_fun
L259:
	B0BSET 0xD1.2
.stabn 0x44,0,282,L260-_rdelay_acton_fun
L260:
	JMP L242
L246:
.stabn 0x44,0,284,L261-_rdelay_acton_fun
L261:
	B0BSET 0xD1.3
.stabn 0x44,0,285,L262-_rdelay_acton_fun
L262:
	B0BSET 0xD1.2
.stabn 0x44,0,286,L263-_rdelay_acton_fun
L263:
 .stabn 0x44,0,289,L264-_rdelay_acton_fun
L264:
 .stabn 0xE0,0,1,L265-_rdelay_acton_fun
L265:
.stabn 0x44,0,290,L266-_rdelay_acton_fun
L266:
L242:
.stabn 0xE0,0,0,L267-_rdelay_acton_fun
L267:
.stabn 0x44,0,291,L268-_rdelay_acton_fun
L268:
L240:
	RET
.stabs "main:F13",36,0,0,_main
_Function_main_code SEGMENT CODE INBANK USING _Function_main_data
_main:
.stabn 0xC0,0,0,L281-_main
L281:
.stabn 0x44,0,296,L282-_main
L282:
 .stabn 0x44,0,298,L283-_main
L283:
	CALL _Sys_Init
L270:
.stabn 0xC0,0,1,L284-_main
L284:
.stabn 0x44,0,301,L285-_main
L285:
 .stabn 0x44,0,303,L286-_main
L286:
	BTS1 _IR_Flag
	JMP L273
.stabn 0xC0,0,2,L287-_main
L287:
.stabn 0x44,0,304,L288-_main
L288:
 .stabn 0x44,0,305,L289-_main
L289:
	BCLR _IR_Flag
.stabn 0x44,0,306,L290-_main
L290:
	CLR _IR_count
.stabn 0x44,0,307,L291-_main
L291:
	BSET _IR_data_deal_flag
.stabn 0x44,0,308,L292-_main
L292:
	MOV A, _IRdata_len
	MOV _main_data@0, A
	INCMS _IRdata_len
	NOP
	CALL _IR_decode
	B0MOV W0, A
	MOV A, _main_data@0
	CLR W3
	ADD A, #(_IRdata)$L
	B0MOV 131, A
	MOV A, #(_IRdata)$M
	ADC A, W3
	B0MOV 132, A
	B0MOV A, W0
	B0MOV 231, A
.stabn 0x44,0,309,L293-_main
L293:
	MOV A, _IRdata_len
	SUB A, #0x0a
	B0BTS1	134.2
	JMP	L274
.stabn 0x44,0,310,L294-_main
L294:
	CLR _IRdata_len
.stabn 0xE0,0,2,L295-_main
L295:
.stabn 0x44,0,311,L296-_main
L296:
	JMP L274
L273:
.stabn 0xC0,0,2,L297-_main
L297:
.stabn 0x44,0,313,L298-_main
L298:
 .stabn 0x44,0,315,L299-_main
L299:
	MOV A, _IR_count
	CMPRS A, #0x01
	B0BTS1	134.2
	JMP	L277
	BTS1 _IR_data_deal_flag
	JMP L277
.stabn 0xC0,0,3,L300-_main
L300:
.stabn 0x44,0,316,L301-_main
L301:
 .stabn 0x44,0,317,L302-_main
L302:
	BCLR _IR_data_deal_flag
.stabn 0x44,0,324,L303-_main
L303:
	CALL _IR_Data_deal
.stabn 0xE0,0,3,L304-_main
L304:
.stabn 0x44,0,325,L305-_main
L305:
L277:
.stabn 0xE0,0,2,L306-_main
L306:
.stabn 0x44,0,326,L307-_main
L307:
L274:
.stabn 0x44,0,327,L308-_main
L308:
	CALL _touch_check
	AND A, #0xFF
	B0BTS0	134.0
	JMP	L279
.stabn 0xC0,0,2,L309-_main
L309:
.stabn 0x44,0,328,L310-_main
L310:
 .stabn 0x44,0,329,L311-_main
L311:
	BSET _sysFunFlag
.stabn 0xE0,0,2,L312-_main
L312:
.stabn 0x44,0,330,L313-_main
L313:
L279:
.stabn 0x44,0,331,L314-_main
L314:
	CALL _touch_deal
.stabn 0xE0,0,1,L315-_main
L315:
.stabn 0x44,0,333,L316-_main
L316:
L271:
.stabn 0x44,0,300,L317-_main
L317:
	JMP L270
.stabn 0xE0,0,0,L318-_main
L318:
.stabn 0x44,0,335,L319-_main
L319:
L269:
_main_end:
CALLTREE _main invoke _Sys_Init,_IR_decode,_IR_Data_deal,_touch_check,_touch_deal
.stabs "ISR:F13",36,0,0,_ISR_isr
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
.stabn 0xC0,0,0,L345-_ISR_isr
L345:
.stabn 0x44,0,342,L346-_ISR_isr
L346:
 .stabn 0x44,0,346,L347-_ISR_isr
L347:
	B0BTS1 0xC8.0
	JMP L322
.stabn 0xC0,0,1,L348-_ISR_isr
L348:
.stabn 0x44,0,347,L349-_ISR_isr
L349:
 .stabn 0x44,0,349,L350-_ISR_isr
L350:
	BTS1 _edgeFlag
	JMP L324
.stabn 0xC0,0,2,L351-_ISR_isr
L351:
.stabn 0x44,0,350,L352-_ISR_isr
L352:
 .stabn 0x44,0,351,L353-_ISR_isr
L353:
	MOV A, #0x08
	B0MOV 0xBF, A
.stabn 0x44,0,352,L354-_ISR_isr
L354:
	BCLR _edgeFlag
.stabn 0x44,0,353,L355-_ISR_isr
L355:
	MOV A, _IR_time
	CMPRS A, #0x3c
	B0BTS1	134.2
	JMP	L326
.stabn 0xC0,0,3,L356-_ISR_isr
L356:
.stabn 0x44,0,354,L357-_ISR_isr
L357:
 .stabn 0x44,0,355,L358-_ISR_isr
L358:
	MOV _IR_data+0, A
.stabn 0x44,0,356,L359-_ISR_isr
L359:
	MOV A, #0x01
	MOV _IR_bit, A
.stabn 0x44,0,357,L360-_ISR_isr
L360:
	BSET _isRec
.stabn 0xE0,0,3,L361-_ISR_isr
L361:
.stabn 0x44,0,358,L362-_ISR_isr
L362:
L326:
.stabn 0x44,0,359,L363-_ISR_isr
L363:
	CLR _IR_time
.stabn 0xE0,0,2,L364-_ISR_isr
L364:
.stabn 0x44,0,360,L365-_ISR_isr
L365:
	JMP L325
L324:
.stabn 0xC0,0,2,L366-_ISR_isr
L366:
.stabn 0x44,0,362,L367-_ISR_isr
L367:
 .stabn 0x44,0,363,L368-_ISR_isr
L368:
	MOV A, #0x10
	B0MOV 0xBF, A
.stabn 0x44,0,364,L369-_ISR_isr
L369:
	BSET _edgeFlag
.stabn 0x44,0,366,L370-_ISR_isr
L370:
	BTS1 _isRec
	JMP L329
.stabn 0xC0,0,3,L371-_ISR_isr
L371:
.stabn 0x44,0,367,L372-_ISR_isr
L372:
 .stabn 0x44,0,368,L373-_ISR_isr
L373:
	MOV A, _IR_bit
	CLR WH
	ADD A, #(_IR_data)$L
	B0MOV 131, A
	MOV A, #(_IR_data)$M
	ADC A, WH
	B0MOV 132, A
	MOV A, _IR_time
	B0MOV 231, A
.stabn 0x44,0,369,L374-_ISR_isr
L374:
	CLR _IR_time
.stabn 0x44,0,370,L375-_ISR_isr
L375:
	INCMS _IR_bit
	NOP
.stabn 0x44,0,371,L376-_ISR_isr
L376:
	MOV A, _IR_bit
	CMPRS A, #0x09
	JMP L331
.stabn 0xC0,0,4,L377-_ISR_isr
L377:
.stabn 0x44,0,372,L378-_ISR_isr
L378:
 .stabn 0x44,0,373,L379-_ISR_isr
L379:
	BSET _IR_Flag
.stabn 0x44,0,374,L380-_ISR_isr
L380:
	CLR _IR_bit
.stabn 0x44,0,375,L381-_ISR_isr
L381:
	BCLR _isRec
.stabn 0xE0,0,4,L382-_ISR_isr
L382:
.stabn 0x44,0,376,L383-_ISR_isr
L383:
L331:
.stabn 0xE0,0,3,L384-_ISR_isr
L384:
.stabn 0x44,0,377,L385-_ISR_isr
L385:
L329:
.stabn 0xE0,0,2,L386-_ISR_isr
L386:
.stabn 0x44,0,378,L387-_ISR_isr
L387:
L325:
.stabn 0x44,0,379,L388-_ISR_isr
L388:
	B0BCLR 0xC8.0
.stabn 0x44,0,380,L389-_ISR_isr
L389:
	B0BSET 0xC9.0
.stabn 0xE0,0,1,L390-_ISR_isr
L390:
.stabn 0x44,0,381,L391-_ISR_isr
L391:
	JMP L323
L322:
.stabn 0x44,0,382,L392-_ISR_isr
L392:
	B0BTS1 0xC8.4
	JMP L333
.stabn 0xC0,0,1,L393-_ISR_isr
L393:
.stabn 0x44,0,383,L394-_ISR_isr
L394:
 .stabn 0x44,0,384,L395-_ISR_isr
L395:
	MOV A, _IR_time
	SUB A, #0xf0
	b0bts0	134.2
	JMP	L335
.stabn 0x44,0,384,L396-_ISR_isr
L396:
	INCMS _IR_time
	NOP
L335:
.stabn 0x44,0,385,L397-_ISR_isr
L397:
	INCMS _Touch_time
	NOP
.stabn 0x44,0,387,L398-_ISR_isr
L398:
	MOV A, #0x70
	B0MOV 0xD8, A
.stabn 0x44,0,388,L399-_ISR_isr
L399:
	MOV A, #0xba
	B0MOV 0xD9, A
.stabn 0x44,0,389,L400-_ISR_isr
L400:
	B0BCLR 0xC8.4
.stabn 0x44,0,390,L401-_ISR_isr
L401:
	B0BSET 0xC9.4
.stabn 0x44,0,391,L402-_ISR_isr
L402:
	B0BSET 0xD8.7
.stabn 0xE0,0,1,L403-_ISR_isr
L403:
.stabn 0x44,0,393,L404-_ISR_isr
L404:
	JMP L334
L333:
.stabn 0x44,0,395,L405-_ISR_isr
L405:
	B0BTS1 0xC8.5
	JMP L337
.stabn 0xC0,0,1,L406-_ISR_isr
L406:
.stabn 0x44,0,396,L407-_ISR_isr
L407:
 .stabn 0x44,0,397,L408-_ISR_isr
L408:
	B0BCLR 0xC8.5
.stabn 0x44,0,398,L409-_ISR_isr
L409:
	BTS0 _buzzerEnableFlag
	JMP L339
.stabn 0xC0,0,2,L410-_ISR_isr
L410:
.stabn 0x44,0,399,L411-_ISR_isr
L411:
 .stabn 0x44,0,400,L412-_ISR_isr
L412:
	B0BSET 0xD5.4
.stabn 0x44,0,401,L413-_ISR_isr
L413:
	JMP L320
.stabn 0xE0,0,2,L414-_ISR_isr
L414:
.stabn 0x44,0,402,L415-_ISR_isr
L415:
L339:
.stabn 0x44,0,403,L416-_ISR_isr
L416:
	MOV A, _sdata321
	MOV __SrcLArg0_isr, A
	ADD A, #0x01
	MOV _sdata321, A
	CLR WH
	B0MOV A, WH
	MOV __SrcLArg1_isr, A
	MOV A, #0xb8
	MOV __SrcRArg0_isr, A
	MOV A, #0x0b
	MOV __SrcRArg1_isr, A
	CALL __CmpLong_isr
	B0BTS0	134.0
	JMP	L341
	B0BTS1	134.2
	JMP	L341
.stabn 0xC0,0,2,L417-_ISR_isr
L417:
.stabn 0x44,0,404,L418-_ISR_isr
L418:
 .stabn 0x44,0,405,L419-_ISR_isr
L419:
	BCLR _buzzerEnableFlag
.stabn 0x44,0,406,L420-_ISR_isr
L420:
	CLR _sdata321
.stabn 0x44,0,407,L421-_ISR_isr
L421:
	B0BSET 0xD5.4
.stabn 0xE0,0,2,L422-_ISR_isr
L422:
.stabn 0x44,0,408,L423-_ISR_isr
L423:
	JMP L342
L341:
.stabn 0xC0,0,2,L424-_ISR_isr
L424:
.stabn 0x44,0,410,L425-_ISR_isr
L425:
 .stabn 0x44,0,411,L426-_ISR_isr
L426:
	BTS1 _buzzerFlag
	JMP L343
.stabn 0xC0,0,3,L427-_ISR_isr
L427:
.stabn 0x44,0,412,L428-_ISR_isr
L428:
 .stabn 0x44,0,413,L429-_ISR_isr
L429:
	BCLR _buzzerFlag
.stabn 0x44,0,414,L430-_ISR_isr
L430:
	B0BSET 0xD5.4
.stabn 0xE0,0,3,L431-_ISR_isr
L431:
.stabn 0x44,0,415,L432-_ISR_isr
L432:
	JMP L344
L343:
.stabn 0xC0,0,3,L433-_ISR_isr
L433:
.stabn 0x44,0,417,L434-_ISR_isr
L434:
 .stabn 0x44,0,418,L435-_ISR_isr
L435:
	BSET _buzzerFlag
.stabn 0x44,0,419,L436-_ISR_isr
L436:
	B0BCLR 0xD5.4
.stabn 0xE0,0,3,L437-_ISR_isr
L437:
.stabn 0x44,0,420,L438-_ISR_isr
L438:
L344:
.stabn 0xE0,0,2,L439-_ISR_isr
L439:
.stabn 0x44,0,421,L440-_ISR_isr
L440:
L342:
.stabn 0xE0,0,1,L441-_ISR_isr
L441:
.stabn 0x44,0,423,L442-_ISR_isr
L442:
L337:
L334:
L323:
.stabs "buzzerCount:V12",38,0,0,_sdata321
.stabn 0xE0,0,0,L443-_ISR_isr
L443:
.stabn 0x44,0,424,L444-_ISR_isr
L444:
L320:
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
.stabs "_intrinsicbitfield:T15=s1bit0:12,0,1;bit1:12,1,1;bit2:12,2,1;\\",128,0,0,0
.stabs "bit3:12,3,1;bit4:12,4,1;bit5:12,5,1;bit6:12,6,1;bit7:12,7,1;;",128,0,0,0
.stabs "", 100, 0, 0,Letext
Letext:
.stabs ":t16=ar1;0;9;9",128,0,0,0
.stabs "IRdata:G16",32,0,0,_IRdata
.stabs "IR_bit:S9",40,0,0,_IR_bit
.stabs "sysFunFlag:G300",32,0,0,_sysFunFlag
.stabs "timeFunFlag:G301",32,0,0,_timeFunFlag
.stabs "Touch_time:G12",32,0,0,_Touch_time
.stabs ":t17=ar1;0;8;9",128,0,0,0
.stabs "IR_data:G17",32,0,0,_IR_data
.stabs "SDian_bz:G300",32,0,0,_SDian_bz
.stabs "SDian_Cnt:G9",32,0,0,_SDian_Cnt
extern data __SrcRArg1_isr
extern data __SrcRArg0_isr
extern data __SrcLArg1_isr
extern data __SrcLArg0_isr
extern data __SrcRArg1
extern data __SrcRArg0
extern data __SrcLArg1
extern data __SrcLArg0
EXTERN CODE __CmpLong_isr
EXTERN CODE __CmpLong
