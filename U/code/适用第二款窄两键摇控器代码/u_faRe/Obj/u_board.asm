
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

;---------------Begin emit user code-----------------

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
_DEFINE_ISRBACKUP_DATA 2
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
;Line#92 {               

 .stabn 0x44,0,93,L4-_Sys_Init
L4:
;Line#93         OSCM = 0x00;                // 普通模式(双时钟)         

 	;MOVU1 0xCA ,#0
	__SelectBANKCNST 0
	CLR (0xCA & 0xFF)
.stabn 0x44,0,94,L5-_Sys_Init
L5:
;Line#94         INTEN= 0x00;                //

 	;MOVU1 0xC9 ,#0
	__SelectBANKCNST 0
	CLR (0xC9 & 0xFF)
.stabn 0x44,0,95,L6-_Sys_Init
L6:
;Line#95         INTRQ= 0x00;                //

 	;MOVU1 0xC8 ,#0
	__SelectBANKCNST 0
	CLR (0xC8 & 0xFF)
.stabn 0x44,0,98,L7-_Sys_Init
L7:
;Line#98         P0M  = 0xFE;                // P00输入  0=输入   1=输出

 	;MOVU1 0xB8 ,#254
	MOV A, #0xfe
	B0MOV 0xB8, A
.stabn 0x44,0,99,L8-_Sys_Init
L8:
;Line#99         P2M  = 0xEF;                // P2.3输入 P2.4输出驱动LED红色电源指示灯 P2.1输出驱动8个LED灯 高电平有效

 	;MOVU1 0xC2 ,#239
	MOV A, #0xef
	B0MOV 0xC2, A
.stabn 0x44,0,101,L9-_Sys_Init
L9:
;Line#101         P1M  = 0xFB;                // P1.0输出驱动LED 蓝色触摸灯    P1.3P1.2输出驱动两组继电器

 	;MOVU1 0xC1 ,#251
	MOV A, #0xfb
	B0MOV 0xC1, A
.stabn 0x44,0,102,L10-_Sys_Init
L10:
;Line#102         P5M  = 0xFF;                // P5.4输出 蜂鸣器输出保持高电平

 	;MOVU1 0xC5 ,#255
	MOV A, #0xff
	B0MOV 0xC5, A
.stabn 0x44,0,104,L11-_Sys_Init
L11:
;Line#104         P0UR = 0x01;                // 0=不上拉 1=上拉 P0.0拉

 	;MOVU1 0xE0 ,#1
	MOV A, #0x01
	B0MOV 0xE0, A
.stabn 0x44,0,105,L12-_Sys_Init
L12:
;Line#105         P2UR = 0x00;                //

 	;MOVU1 0xE2 ,#0
	__SelectBANKCNST 0
	CLR (0xE2 & 0xFF)
.stabn 0x44,0,106,L13-_Sys_Init
L13:
;Line#106         P1UR = 0x00;                // 0x0C

 	;MOVU1 0xE1 ,#0
	__SelectBANKCNST 0
	CLR (0xE1 & 0xFF)
.stabn 0x44,0,107,L14-_Sys_Init
L14:
;Line#107         P5UR = 0x00;                //

 	;MOVU1 0xE5 ,#0
	__SelectBANKCNST 0
	CLR (0xE5 & 0xFF)
.stabn 0x44,0,109,L15-_Sys_Init
L15:
;Line#109         DELAY1_OFF;   

 	;MOVX1 0xD1.3 ,#0
	B0BCLR 0xD1.3
.stabn 0x44,0,110,L16-_Sys_Init
L16:
;Line#110         DELAY2_OFF; 

 	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
.stabn 0x44,0,111,L17-_Sys_Init
L17:
;Line#111 	    R_POWER_LED_ON;

 	;MOVX1 0xD2.4 ,#0
	B0BCLR 0xD2.4
.stabn 0x44,0,112,L18-_Sys_Init
L18:
;Line#112         B_BTOUCH_LED_OFF;

 	;MOVX1 0xD1.0 ,#1
	B0BSET 0xD1.0
.stabn 0x44,0,113,L19-_Sys_Init
L19:
;Line#113         BUZZER_OFF;

 	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
.stabn 0x44,0,116,L20-_Sys_Init
L20:
;Line#116         PEDGE = 0x10;               //下降沿触发中断

 	;MOVU1 0xBF ,#16
	MOV A, #0x10
	B0MOV 0xBF, A
.stabn 0x44,0,118,L21-_Sys_Init
L21:
;Line#118 		FP00IRQ  = 0;               //清除中断标志

 	;MOVX1 0xC8.0 ,#0
	B0BCLR 0xC8.0
.stabn 0x44,0,119,L22-_Sys_Init
L22:
;Line#119         FP00IEN  = 1;               //P0.0 外部中断(INT0)使能

 	;MOVX1 0xC9.0 ,#1
	B0BSET 0xC9.0
.stabn 0x44,0,120,L23-_Sys_Init
L23:
;Line#120         edgeFlag = 1;

 	;MOVX1 _edgeFlag ,#1
	__SelectBANK _edgeFlag
	BSET _edgeFlag
.stabn 0x44,0,123,L24-_Sys_Init
L24:
;Line#123         T0M=0x70;                   // 16M/16/2= 2uS   Fcpu的2分频 

 	;MOVU1 0xD8 ,#112
	MOV A, #0x70
	B0MOV 0xD8, A
.stabn 0x44,0,125,L25-_Sys_Init
L25:
;Line#125         T0C=186;                    //256-139/2 = 256- 69.5 = 186.5 每139us中断一次      

 	;MOVU1 0xD9 ,#186
	MOV A, #0xba
	B0MOV 0xD9, A
.stabn 0x44,0,126,L26-_Sys_Init
L26:
;Line#126 		FT0IRQ=0;                   // T0 中断请求标志清零。

 	;MOVX1 0xC8.4 ,#0
	B0BCLR 0xC8.4
.stabn 0x44,0,127,L27-_Sys_Init
L27:
;Line#127 		FT0IEN=1;                   //允许响应 T0 中断。

 	;MOVX1 0xC9.4 ,#1
	B0BSET 0xC9.4
.stabn 0x44,0,128,L28-_Sys_Init
L28:
;Line#128         FT0ENB=1;                   //启动定时器T0运行 

 	;MOVX1 0xD8.7 ,#1
	B0BSET 0xD8.7
.stabn 0x44,0,130,L29-_Sys_Init
L29:
;Line#130         TC0M=0x70;                  // 16MHz/16=  Fcpu/2   2us  256-250/2=

 	;MOVU1 0xDA ,#112
	MOV A, #0x70
	B0MOV 0xDA, A
.stabn 0x44,0,131,L30-_Sys_Init
L30:
;Line#131         TC0R=131;                   //每隔125*2 =250us中断一次

 	;MOVU1 0xCD ,#131
	MOV A, #0x83
	B0MOV 0xCD, A
.stabn 0x44,0,132,L31-_Sys_Init
L31:
;Line#132         TC0C=131;                   //  

 	;MOVU1 0xDB ,#131
	B0MOV 0xDB, A
.stabn 0x44,0,133,L32-_Sys_Init
L32:
;Line#133         FALOAD0=1;                  //使能 TC0 自动装载

 	;MOVX1 0xDA.2 ,#1
	B0BSET 0xDA.2
.stabn 0x44,0,134,L33-_Sys_Init
L33:
;Line#134 		FTC0OUT=0;                  //允许P5.4口作PWM输出

 	;MOVX1 0xDA.1 ,#0
	B0BCLR 0xDA.1
.stabn 0x44,0,135,L34-_Sys_Init
L34:
;Line#135 		FPWM0OUT = 0;               //允许PWM/BUZZER功能  

 	;MOVX1 0xDA.0 ,#0
	B0BCLR 0xDA.0
.stabn 0x44,0,136,L35-_Sys_Init
L35:
;Line#136         FTC0IEN=1;                  //允许中断Enable TC0 Interrput

 	;MOVX1 0xC9.5 ,#1
	B0BSET 0xC9.5
.stabn 0x44,0,137,L36-_Sys_Init
L36:
;Line#137         FTC0ENB=1;                  // 定时器开启

 	;MOVX1 0xDA.7 ,#1
	B0BSET 0xDA.7
.stabn 0x44,0,139,L37-_Sys_Init
L37:
;Line#139         FGIE = 1;                   // Enable all Interrput

 	;MOVX1 0xDF.7 ,#1
	B0BSET 0xDF.7
.stabn 0xE0,0,0,L38-_Sys_Init
L38:
.stabn 0x44,0,140,L39-_Sys_Init
L39:
;Line#140 }

L1:
	RET
.stabs "touch_check:f9",36,0,0,_touch_check
_Function_touch_check_code SEGMENT CODE INBANK USING _Function_touch_check_data
_touch_check:
.stabn 0xC0,0,0,L51-_touch_check
L51:
.stabn 0x44,0,144,L52-_touch_check
L52:
;Line#144 {   //触摸输出检测   无触摸时高电平，有触摸时低电平时长大于300ms

 .stabn 0x44,0,145,L53-_touch_check
L53:
;Line#145     if(TOUCH_PIN == 0)

 	;NEX1 L41 ,0xD2.3 ,#0
	B0BTS0 0xD2.3
	JMP L41
.stabn 0xC0,0,1,L54-_touch_check
L54:
.stabn 0x44,0,146,L55-_touch_check
L55:
;Line#146     {

 .stabn 0x44,0,147,L56-_touch_check
L56:
;Line#147 			   if(Touch_flag) 

 	;EQ L43 ,_Touch_flag ,#0
	__SelectBANK _Touch_flag
	BTS1 _Touch_flag
	JMP L43
.stabn 0x44,0,148,L57-_touch_check
L57:
;Line#148 					 Touch_time = 0;

 	;MOVU1 _Touch_time ,#0
	__SelectBANK _Touch_time
	CLR _Touch_time
	JMP L42
L43:
.stabn 0x44,0,149,L58-_touch_check
L58:
;Line#149          else if(Touch_time > 500)  //139微秒 *500 = 69.5ms

 	;CVUI2 W0:W1 ,_Touch_time
	__SelectBANK _Touch_time
	MOV A, _Touch_time
	__SelectBANKCNST 0
	CLR W1
	;LE L42 ,W0:W1 ,#500
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
	JLE L42
.stabn 0xC0,0,2,L59-_touch_check
L59:
.stabn 0x44,0,150,L60-_touch_check
L60:
;Line#150 				 {

 .stabn 0x44,0,151,L61-_touch_check
L61:
;Line#151 					    Touch_time = 0;

 	;MOVU1 _Touch_time ,#0
	__SelectBANK _Touch_time
	CLR _Touch_time
.stabn 0x44,0,152,L62-_touch_check
L62:
;Line#152 				      Touch_flag = 1; 

 	;MOVX1 _Touch_flag ,#1
	__SelectBANK _Touch_flag
	BSET _Touch_flag
.stabn 0x44,0,154,L63-_touch_check
L63:
;Line#154 					    return 1;

 	;RETU1 #1
	MOV A, #0x01
	JMP L40
.stabn 0xE0,0,2,L64-_touch_check
L64:
.stabn 0x44,0,155,L65-_touch_check
L65:
;Line#155 				 } 

 .stabn 0xE0,0,1,L66-_touch_check
L66:
.stabn 0x44,0,156,L67-_touch_check
L67:
;Line#156     }

L41:
.stabn 0xC0,0,1,L68-_touch_check
L68:
.stabn 0x44,0,158,L69-_touch_check
L69:
;Line#158 		{

 .stabn 0x44,0,159,L70-_touch_check
L70:
;Line#159 				if(Touch_flag)

 	;EQ L47 ,_Touch_flag ,#0
	__SelectBANK _Touch_flag
	BTS1 _Touch_flag
	JMP L47
.stabn 0xC0,0,2,L71-_touch_check
L71:
.stabn 0x44,0,160,L72-_touch_check
L72:
;Line#160 				{

 .stabn 0x44,0,161,L73-_touch_check
L73:
;Line#161 						if(Touch_time > 2000)  //139微秒 *2000 = 279.5ms

 	;CVUI2 W0:W1 ,_Touch_time
	__SelectBANK _Touch_time
	MOV A, _Touch_time
	__SelectBANKCNST 0
	CLR W1
	;LE L48 ,W0:W1 ,#2000
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
	JLE L48
.stabn 0xC0,0,3,L74-_touch_check
L74:
.stabn 0x44,0,162,L75-_touch_check
L75:
;Line#162 						{

 .stabn 0x44,0,163,L76-_touch_check
L76:
;Line#163 							 Touch_time=0;

 	;MOVU1 _Touch_time ,#0
	__SelectBANK _Touch_time
	CLR _Touch_time
.stabn 0x44,0,164,L77-_touch_check
L77:
;Line#164 							 Touch_flag = 0;

 	;MOVX1 _Touch_flag ,#0
	__SelectBANK _Touch_flag
	BCLR _Touch_flag
.stabn 0xE0,0,3,L78-_touch_check
L78:
.stabn 0x44,0,166,L79-_touch_check
L79:
;Line#166 						}

 .stabn 0xE0,0,2,L80-_touch_check
L80:
.stabn 0x44,0,167,L81-_touch_check
L81:
;Line#167 				}

	JMP L48
L47:
.stabn 0x44,0,168,L82-_touch_check
L82:
;Line#168 				else Touch_time=0;

 	;MOVU1 _Touch_time ,#0
	__SelectBANK _Touch_time
	CLR _Touch_time
L48:
.stabn 0xE0,0,1,L83-_touch_check
L83:
.stabn 0x44,0,170,L84-_touch_check
L84:
;Line#170 		}

L42:
.stabn 0x44,0,171,L85-_touch_check
L85:
;Line#171 		return 0;

 	;RETU1 #0
	MOV A, #0x00
.stabn 0xE0,0,0,L86-_touch_check
L86:
.stabn 0x44,0,172,L87-_touch_check
L87:
;Line#172 }

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
;Line#175 {

 .stabn 0x44,0,176,L97-_touch_deal
L97:
;Line#176 	 if(Touch_flag)

 	;EQ L89 ,_Touch_flag ,#0
	__SelectBANK _Touch_flag
	BTS1 _Touch_flag
	JMP L89
.stabn 0xC0,0,1,L98-_touch_deal
L98:
.stabn 0x44,0,177,L99-_touch_deal
L99:
;Line#177 	 {

 .stabn 0x44,0,178,L100-_touch_deal
L100:
;Line#178 			if(!touch_preFlag)

 	;NEX1 L90 ,_touch_preFlag ,#0
	__SelectBANK _touch_preFlag
	BTS0 _touch_preFlag
	JMP L90
.stabn 0xC0,0,2,L101-_touch_deal
L101:
.stabn 0x44,0,179,L102-_touch_deal
L102:
;Line#179 			{

 .stabn 0x44,0,180,L103-_touch_deal
L103:
;Line#180 					touch_preFlag = 1;

 	;MOVX1 _touch_preFlag ,#1
	BSET _touch_preFlag
.stabn 0x44,0,181,L104-_touch_deal
L104:
;Line#181 				  btn_value++;

 	;ADDU1 _btn_value ,_btn_value ,#1
	__SelectBANK _btn_value
	INCMS _btn_value
	NOP
.stabn 0x44,0,183,L105-_touch_deal
L105:
;Line#183 					if(btn_value >= BUTTON_VALUE_MAX)

 	;LT L93 ,_btn_value ,#4
	MOV A, _btn_value
	SUB A, #0x04
	JLT L93
.stabn 0x44,0,184,L106-_touch_deal
L106:
;Line#184 							btn_value = 1;				

 	;MOVU1 _btn_value ,#1
	MOV A, #0x01
	MOV _btn_value, A
L93:
.stabn 0x44,0,185,L107-_touch_deal
L107:
;Line#185 				  rdelay_acton_fun(btn_value);	

 	;PUSH _rdelay_acton_fun_arg@0 ,_btn_value
	__SelectBANK _btn_value
	MOV A, _btn_value
	__SelectBANK _rdelay_acton_fun_arg@0
	MOV _rdelay_acton_fun_arg@0, A
	;CALLV _rdelay_acton_fun
	CALL _rdelay_acton_fun
.stabn 0xE0,0,2,L108-_touch_deal
L108:
.stabn 0x44,0,186,L109-_touch_deal
L109:
;Line#186 			}

 .stabn 0xE0,0,1,L110-_touch_deal
L110:
.stabn 0x44,0,187,L111-_touch_deal
L111:
;Line#187 	 }

	JMP L90
L89:
.stabn 0xC0,0,1,L112-_touch_deal
L112:
.stabn 0x44,0,189,L113-_touch_deal
L113:
;Line#189 	 {

 .stabn 0x44,0,190,L114-_touch_deal
L114:
;Line#190 			touch_preFlag = 0;	

 	;MOVX1 _touch_preFlag ,#0
	__SelectBANK _touch_preFlag
	BCLR _touch_preFlag
.stabn 0xE0,0,1,L115-_touch_deal
L115:
.stabn 0x44,0,191,L116-_touch_deal
L116:
;Line#191 	 }

L90:
.stabn 0xE0,0,0,L117-_touch_deal
L117:
.stabn 0x44,0,192,L118-_touch_deal
L118:
;Line#192 }

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
;Line#197 {

 .stabn 0x44,0,198,L149-_IR_Data_deal
L149:
;Line#198 	u8 dat,i,light=0,onoff=0;

 	;MOVU1 _IR_Data_deal_data@2 ,#0
	__SelectBANK _IR_Data_deal_data@2
	CLR _IR_Data_deal_data@2
.stabn 0x44,0,198,L150-_IR_Data_deal
L150:
;Line#198 	u8 dat,i,light=0,onoff=0;

 	;MOVU1 _IR_Data_deal_data@3 ,#0
	__SelectBANK _IR_Data_deal_data@3
	CLR _IR_Data_deal_data@3
.stabn 0xC0,0,1,L151-_IR_Data_deal
L151:
.stabn 0x44,0,200,L152-_IR_Data_deal
L152:
;Line#200 	for(i=0;i<IRdata_len;i++) 

 	;MOVU1 _IR_Data_deal_data@1 ,#0
	__SelectBANK _IR_Data_deal_data@1
	CLR _IR_Data_deal_data@1
	JMP L123
L120:
.stabn 0xC0,0,2,L153-_IR_Data_deal
L153:
.stabn 0x44,0,201,L154-_IR_Data_deal
L154:
;Line#201 	{

 .stabn 0x44,0,202,L155-_IR_Data_deal
L155:
	__SelectBANK _IR_Data_deal_data@1
	MOV A, _IR_Data_deal_data@1
	B0MOV Y, #(_IRdata)$M
	B0MOV Z, #(_IRdata)$L
	B0ADD Z, A
	B0MOV A, @YZ
;Line#202 			if(IRdata[i]==IR_LIGHT_BUTTON)

 	;NEI1 L124 ,W0 ,#187
	CMPRS A, #0xbb
	JMP L124
.stabn 0x44,0,203,L156-_IR_Data_deal
L156:
;Line#203 				 light++;

 	;ADDU1 _IR_Data_deal_data@2 ,_IR_Data_deal_data@2 ,#1
	__SelectBANK _IR_Data_deal_data@2
	INCMS _IR_Data_deal_data@2
	NOP
	JMP L125
L124:
.stabn 0x44,0,204,L157-_IR_Data_deal
L157:
	__SelectBANK _IR_Data_deal_data@1
	MOV A, _IR_Data_deal_data@1
	B0MOV Y, #(_IRdata)$M
	B0MOV Z, #(_IRdata)$L
	B0ADD Z, A
	B0MOV A, @YZ
;Line#204 			else  if(IRdata[i]==IR_ONOFF_BUTTON)

 	;NEI1 L126 ,W0 ,#27
	CMPRS A, #0x1b
	JMP L126
.stabn 0x44,0,205,L158-_IR_Data_deal
L158:
;Line#205 				 onoff++;

 	;ADDU1 _IR_Data_deal_data@3 ,_IR_Data_deal_data@3 ,#1
	__SelectBANK _IR_Data_deal_data@3
	INCMS _IR_Data_deal_data@3
	NOP
L126:
L125:
.stabn 0xE0,0,2,L159-_IR_Data_deal
L159:
.stabn 0x44,0,206,L160-_IR_Data_deal
L160:
;Line#206 	}

L121:
.stabn 0x44,0,200,L161-_IR_Data_deal
L161:
;Line#200 	for(i=0;i<IRdata_len;i++) 

 	;ADDU1 _IR_Data_deal_data@1 ,_IR_Data_deal_data@1 ,#1
	__SelectBANK _IR_Data_deal_data@1
	INCMS _IR_Data_deal_data@1
	NOP
L123:
.stabn 0x44,0,200,L162-_IR_Data_deal
L162:
;Line#200 	for(i=0;i<IRdata_len;i++) 

 	;LT L120 ,_IR_Data_deal_data@1 ,_IRdata_len
	__SelectBANK _IR_Data_deal_data@1
	MOV A, _IR_Data_deal_data@1
	__SelectBANK _IRdata_len
	SUB A, _IRdata_len
	JLT L120
.stabn 0xE0,0,1,L163-_IR_Data_deal
L163:
.stabn 0x44,0,207,L164-_IR_Data_deal
L164:
;Line#207 	if(light > IRdata_len/2)

 .stabn 0x44,0,207,L165-_IR_Data_deal
L165:
;Line#207 	if(light > IRdata_len/2)

 	;RSH W0 ,_IRdata_len ,#1
	B0BCLR FC
	RRC _IRdata_len
	B0MOV W0, A
	;LE L128 ,_IR_Data_deal_data@2 ,W0
	__SelectBANK _IR_Data_deal_data@2
	MOV A, _IR_Data_deal_data@2
	__SelectBANKCNST 0
	CMPRS A, W0
	JLT L128
.stabn 0x44,0,208,L166-_IR_Data_deal
L166:
;Line#208 		 dat = IR_LIGHT_BUTTON;

 	;MOVU1 _IR_Data_deal_data@0 ,#187
	MOV A, #0xbb
	__SelectBANK _IR_Data_deal_data@0
	MOV _IR_Data_deal_data@0, A
	JMP L129
L128:
.stabn 0x44,0,209,L167-_IR_Data_deal
L167:
;Line#209 	else if(onoff > IRdata_len/2)

 	;RSH W0 ,_IRdata_len ,#1
	B0BCLR FC
	__SelectBANK _IRdata_len
	RRC _IRdata_len
	B0MOV W0, A
	;LE L130 ,_IR_Data_deal_data@3 ,W0
	__SelectBANK _IR_Data_deal_data@3
	MOV A, _IR_Data_deal_data@3
	__SelectBANKCNST 0
	CMPRS A, W0
	JLT L130
.stabn 0x44,0,210,L168-_IR_Data_deal
L168:
;Line#210 		 dat = IR_ONOFF_BUTTON;

 	;MOVU1 _IR_Data_deal_data@0 ,#27
	MOV A, #0x1b
	__SelectBANK _IR_Data_deal_data@0
	MOV _IR_Data_deal_data@0, A
L130:
L129:
.stabn 0xC0,0,1,L169-_IR_Data_deal
L169:
.stabn 0x44,0,212,L170-_IR_Data_deal
L170:
;Line#212     for(i=0;i<IR_DATA_BUFFER_SIZE;i++)

 	;MOVU1 _IR_Data_deal_data@1 ,#0
	__SelectBANK _IR_Data_deal_data@1
	CLR _IR_Data_deal_data@1
	JMP L135
L132:
.stabn 0x44,0,213,L171-_IR_Data_deal
L171:
	__SelectBANK _IR_Data_deal_data@1
	MOV A, _IR_Data_deal_data@1
	B0MOV Y, #(_IRdata)$M
	B0MOV Z, #(_IRdata)$L
	B0ADD Z, A
	MOV A, #0x00
	B0MOV @YZ, A
;Line#213 	   IRdata[i] = 0;

L133:
.stabn 0x44,0,212,L172-_IR_Data_deal
L172:
;Line#212     for(i=0;i<IR_DATA_BUFFER_SIZE;i++)

 	;ADDU1 _IR_Data_deal_data@1 ,_IR_Data_deal_data@1 ,#1
	__SelectBANK _IR_Data_deal_data@1
	INCMS _IR_Data_deal_data@1
	NOP
L135:
.stabn 0x44,0,212,L173-_IR_Data_deal
L173:
;Line#212     for(i=0;i<IR_DATA_BUFFER_SIZE;i++)

 	;LT L132 ,_IR_Data_deal_data@1 ,#10
	__SelectBANK _IR_Data_deal_data@1
	MOV A, _IR_Data_deal_data@1
	SUB A, #0x0a
	JLT L132
.stabn 0xE0,0,1,L174-_IR_Data_deal
L174:
.stabn 0x44,0,214,L175-_IR_Data_deal
L175:
;Line#214 	IRdata_len = 0;

 .stabn 0x44,0,214,L176-_IR_Data_deal
L176:
;Line#214 	IRdata_len = 0;

 	;MOVU1 _IRdata_len ,#0
	__SelectBANK _IRdata_len
	CLR _IRdata_len
.stabn 0x44,0,216,L177-_IR_Data_deal
L177:
;Line#216 	switch(dat)//红外接收正确

 	;EQ L138 ,_IR_Data_deal_data@0 ,#-69
	__SelectBANK _IR_Data_deal_data@0
	MOV A, _IR_Data_deal_data@0
	SUB A, #0xbb
	JEQ L138
	;LTI1 L119 ,_IR_Data_deal_data@0 ,#-69
	MOV A, _IR_Data_deal_data@0
	XOR A, #0x80
	SUB A, #0x3B
	JLT L119
L146:
	;EQ L143 ,_IR_Data_deal_data@0 ,#27
	__SelectBANK _IR_Data_deal_data@0
	MOV A, _IR_Data_deal_data@0
	SUB A, #0x1b
	JEQ L143
	JMP L119
.stabn 0xC0,0,1,L178-_IR_Data_deal
L178:
.stabn 0x44,0,217,L179-_IR_Data_deal
L179:
;Line#217 	{

L138:
.stabn 0x44,0,219,L180-_IR_Data_deal
L180:
;Line#219 				if(sysFunFlag==1)

 	;NEX1 L137 ,_sysFunFlag ,#1
	__SelectBANK _sysFunFlag
	BTS1 _sysFunFlag
	JMP L137
.stabn 0xC0,0,2,L181-_IR_Data_deal
L181:
.stabn 0x44,0,220,L182-_IR_Data_deal
L182:
;Line#220 				{

 .stabn 0x44,0,221,L183-_IR_Data_deal
L183:
;Line#221 					 btn_value++;

 	;ADDU1 _btn_value ,_btn_value ,#1
	__SelectBANK _btn_value
	INCMS _btn_value
	NOP
.stabn 0x44,0,222,L184-_IR_Data_deal
L184:
;Line#222 					 if(btn_value >= BUTTON_VALUE_MAX)

 	;LT L137 ,_btn_value ,#4
	MOV A, _btn_value
	SUB A, #0x04
	JLT L137
.stabn 0x44,0,223,L185-_IR_Data_deal
L185:
;Line#223 						 btn_value = 1;

 	;MOVU1 _btn_value ,#1
	MOV A, #0x01
	MOV _btn_value, A
.stabn 0xE0,0,2,L186-_IR_Data_deal
L186:
.stabn 0x44,0,224,L187-_IR_Data_deal
L187:
;Line#224 				}

 .stabn 0x44,0,225,L188-_IR_Data_deal
L188:
;Line#225 		break;

	JMP L137
L143:
.stabn 0x44,0,227,L189-_IR_Data_deal
L189:
;Line#227          if(sysFunFlag==1)

 	;NEX1 L144 ,_sysFunFlag ,#1
	__SelectBANK _sysFunFlag
	BTS1 _sysFunFlag
	JMP L144
.stabn 0xC0,0,2,L190-_IR_Data_deal
L190:
.stabn 0x44,0,228,L191-_IR_Data_deal
L191:
;Line#228 				 {

 .stabn 0x44,0,229,L192-_IR_Data_deal
L192:
;Line#229 				     sysFunFlag = 0;

 	;MOVX1 _sysFunFlag ,#0
	BCLR _sysFunFlag
.stabn 0x44,0,230,L193-_IR_Data_deal
L193:
;Line#230 					   btn_value = 0;

 	;MOVU1 _btn_value ,#0
	__SelectBANK _btn_value
	CLR _btn_value
.stabn 0xE0,0,2,L194-_IR_Data_deal
L194:
.stabn 0x44,0,231,L195-_IR_Data_deal
L195:
;Line#231 				 }

	JMP L137
L144:
.stabn 0xC0,0,2,L196-_IR_Data_deal
L196:
.stabn 0x44,0,233,L197-_IR_Data_deal
L197:
;Line#233 				 {

 .stabn 0x44,0,234,L198-_IR_Data_deal
L198:
;Line#234 						 sysFunFlag = 1;

 	;MOVX1 _sysFunFlag ,#1
	__SelectBANK _sysFunFlag
	BSET _sysFunFlag
.stabn 0x44,0,235,L199-_IR_Data_deal
L199:
;Line#235 					   btn_value = 1;

 	;MOVU1 _btn_value ,#1
	MOV A, #0x01
	__SelectBANK _btn_value
	MOV _btn_value, A
.stabn 0xE0,0,2,L200-_IR_Data_deal
L200:
.stabn 0x44,0,236,L201-_IR_Data_deal
L201:
;Line#236 				 }

 .stabn 0x44,0,238,L202-_IR_Data_deal
L202:
;Line#238     break;	

 .stabn 0x44,0,240,L203-_IR_Data_deal
L203:
;Line#240           return;			

 .stabn 0xE0,0,1,L204-_IR_Data_deal
L204:
.stabn 0x44,0,241,L205-_IR_Data_deal
L205:
;Line#241 	}

L137:
.stabn 0x44,0,243,L206-_IR_Data_deal
L206:
;Line#243   rdelay_acton_fun(btn_value);

 	;PUSH _rdelay_acton_fun_arg@0 ,_btn_value
	__SelectBANK _btn_value
	MOV A, _btn_value
	__SelectBANK _rdelay_acton_fun_arg@0
	MOV _rdelay_acton_fun_arg@0, A
	;CALLV _rdelay_acton_fun
	CALL _rdelay_acton_fun
.stabn 0xE0,0,0,L207-_IR_Data_deal
L207:
.stabn 0x44,0,245,L208-_IR_Data_deal
L208:
;Line#245 }

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
;Line#248 {

 .stabn 0x44,0,250,L220-_IR_decode
L220:
;Line#250 	u8 IR_Value = 0; 

 	;MOVU1 _IR_decode_data@2 ,#0
	__SelectBANK _IR_decode_data@2
	CLR _IR_decode_data@2
.stabn 0x44,0,251,L221-_IR_decode
L221:
;Line#251 	k=1;							//先让变量k等于1，因为k为0时取出的将会是“引导码的时间间隔”

 	;MOVU1 _IR_decode_data@1 ,#1
	MOV A, #0x01
	__SelectBANK _IR_decode_data@1
	MOV _IR_decode_data@1, A
.stabn 0xC0,0,1,L222-_IR_decode
L222:
.stabn 0x44,0,253,L223-_IR_decode
L223:
;Line#253 	for(j=0;j<=7;j++)				//内层循环8次为了拼合8个数据位为1个字节

 	;MOVU1 _IR_decode_data@0 ,#0
	__SelectBANK _IR_decode_data@0
	CLR _IR_decode_data@0
	JMP L213
L210:
.stabn 0xC0,0,2,L224-_IR_decode
L224:
.stabn 0x44,0,254,L225-_IR_decode
L225:
;Line#254 	{

 .stabn 0x44,0,255,L226-_IR_decode
L226:
	__SelectBANK _IR_decode_data@1
	MOV A, _IR_decode_data@1
	B0MOV Y, #(_IR_data)$M
	B0MOV Z, #(_IR_data)$L
	B0ADD Z, A
	B0MOV A, @YZ
;Line#255 		if(IR_data[k]>5)			//若“时间间隔”比5大那肯定是“1码”反之为“0码”

 	;LE L214 ,W0 ,#5
	CMPRS A, #0x05
	JLT L214
.stabn 0x44,0,256,L227-_IR_decode
L227:
;Line#256 			IR_Value|=0x80;			//通过按位或运算高位填1

 	;ORU1 _IR_decode_data@2 ,_IR_decode_data@2 ,#128
	MOV A, #0x80
	__SelectBANK _IR_decode_data@2
	OR _IR_decode_data@2, A
L214:
.stabn 0x44,0,257,L228-_IR_decode
L228:
;Line#257 		if(j<7)						    //若数据没有拼合完8次

 	;GE L216 ,_IR_decode_data@0 ,#7
	__SelectBANK _IR_decode_data@0
	MOV A, _IR_decode_data@0
	SUB A, #0x07
	JGE L216
.stabn 0x44,0,258,L229-_IR_decode
L229:
;Line#258 			IR_Value>>=1;			  //通过右移运算“腾出”位置准备下一位判定

 	;RSH _IR_decode_data@2 ,_IR_decode_data@2 ,#1
	B0BCLR FC
	__SelectBANK _IR_decode_data@2
	RRCM _IR_decode_data@2
L216:
.stabn 0x44,0,259,L230-_IR_decode
L230:
;Line#259 		k++;						      //下标变量自增

 	;ADDU1 _IR_decode_data@1 ,_IR_decode_data@1 ,#1
	__SelectBANK _IR_decode_data@1
	INCMS _IR_decode_data@1
	NOP
.stabn 0xE0,0,2,L231-_IR_decode
L231:
.stabn 0x44,0,260,L232-_IR_decode
L232:
;Line#260 	}

L211:
.stabn 0x44,0,253,L233-_IR_decode
L233:
;Line#253 	for(j=0;j<=7;j++)				//内层循环8次为了拼合8个数据位为1个字节

 	;ADDU1 _IR_decode_data@0 ,_IR_decode_data@0 ,#1
	__SelectBANK _IR_decode_data@0
	INCMS _IR_decode_data@0
	NOP
L213:
.stabn 0x44,0,253,L234-_IR_decode
L234:
;Line#253 	for(j=0;j<=7;j++)				//内层循环8次为了拼合8个数据位为1个字节

 	;LE L210 ,_IR_decode_data@0 ,#7
	__SelectBANK _IR_decode_data@0
	MOV A, _IR_decode_data@0
	CMPRS A, #0x07
	JLT L210
.stabn 0xE0,0,1,L235-_IR_decode
L235:
.stabn 0x44,0,262,L236-_IR_decode
L236:
;Line#262 	return IR_Value;				//返回红外接收的数据

 .stabn 0x44,0,262,L237-_IR_decode
L237:
;Line#262 	return IR_Value;				//返回红外接收的数据

 	;RETU1 _IR_decode_data@2
	__SelectBANK _IR_decode_data@2
	MOV A, _IR_decode_data@2
.stabn 0xE0,0,0,L238-_IR_decode
L238:
.stabn 0x44,0,263,L239-_IR_decode
L239:
;Line#263 }

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
;Line#265 {

 .stabn 0x44,0,269,L249-_rdelay_acton_fun
L249:
	__SelectBANK _rdelay_acton_fun_arg@0
	MOV A, _rdelay_acton_fun_arg@0
	ADD A, #0x80
	CMPRS A, #0x84
	B0BTS0 FC
	JMP L446
	SUB A, #0x80
	B0BTS1 FC
	JMP L446
	B0ADD PCL, A
	JMP L243
	JMP L244
	JMP L245
	JMP L246
L446:
;Line#269     switch(action_value)

	JMP L242
.stabn 0xC0,0,1,L250-_rdelay_acton_fun
L250:
.stabn 0x44,0,270,L251-_rdelay_acton_fun
L251:
;Line#270 		{

L243:
.stabn 0x44,0,272,L252-_rdelay_acton_fun
L252:
;Line#272             DELAY1_OFF; 

 	;MOVX1 0xD1.3 ,#0
	B0BCLR 0xD1.3
.stabn 0x44,0,273,L253-_rdelay_acton_fun
L253:
;Line#273 			DELAY2_OFF;  

 	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
.stabn 0x44,0,274,L254-_rdelay_acton_fun
L254:
;Line#274         break;

	JMP L242
L244:
.stabn 0x44,0,276,L255-_rdelay_acton_fun
L255:
;Line#276             DELAY1_ON; 

 	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
.stabn 0x44,0,277,L256-_rdelay_acton_fun
L256:
;Line#277 			DELAY2_OFF;  

 	;MOVX1 0xD1.2 ,#0
	B0BCLR 0xD1.2
.stabn 0x44,0,278,L257-_rdelay_acton_fun
L257:
;Line#278         break;

	JMP L242
L245:
.stabn 0x44,0,280,L258-_rdelay_acton_fun
L258:
;Line#280             DELAY1_OFF; 

 	;MOVX1 0xD1.3 ,#0
	B0BCLR 0xD1.3
.stabn 0x44,0,281,L259-_rdelay_acton_fun
L259:
;Line#281 			DELAY2_ON;  

 	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
.stabn 0x44,0,282,L260-_rdelay_acton_fun
L260:
;Line#282         break;

	JMP L242
L246:
.stabn 0x44,0,284,L261-_rdelay_acton_fun
L261:
;Line#284             DELAY1_ON; 

 	;MOVX1 0xD1.3 ,#1
	B0BSET 0xD1.3
.stabn 0x44,0,285,L262-_rdelay_acton_fun
L262:
;Line#285 			DELAY2_ON;  

 	;MOVX1 0xD1.2 ,#1
	B0BSET 0xD1.2
.stabn 0x44,0,286,L263-_rdelay_acton_fun
L263:
;Line#286         break;

 .stabn 0x44,0,289,L264-_rdelay_acton_fun
L264:
;Line#289 				break;

 .stabn 0xE0,0,1,L265-_rdelay_acton_fun
L265:
.stabn 0x44,0,290,L266-_rdelay_acton_fun
L266:
;Line#290 		}

L242:
.stabn 0xE0,0,0,L267-_rdelay_acton_fun
L267:
.stabn 0x44,0,291,L268-_rdelay_acton_fun
L268:
;Line#291 }

L240:
	RET
.stabs "main:F13",36,0,0,_main
_Function_main_code SEGMENT CODE INBANK USING _Function_main_data
_main:
.stabn 0xC0,0,0,L281-_main
L281:
.stabn 0x44,0,296,L282-_main
L282:
;Line#296 {                                            

 .stabn 0x44,0,298,L283-_main
L283:
;Line#298 	Sys_Init();                   // 系统初始化

 	;CALLV _Sys_Init
	CALL _Sys_Init
L270:
.stabn 0xC0,0,1,L284-_main
L284:
.stabn 0x44,0,301,L285-_main
L285:
;Line#301 	{	

 .stabn 0x44,0,303,L286-_main
L286:
;Line#303 		if(IR_Flag)				//红外数据接收完成

 	;EQ L273 ,_IR_Flag ,#0
	__SelectBANK _IR_Flag
	BTS1 _IR_Flag
	JMP L273
.stabn 0xC0,0,2,L287-_main
L287:
.stabn 0x44,0,304,L288-_main
L288:
;Line#304 		{

 .stabn 0x44,0,305,L289-_main
L289:
;Line#305 			IR_Flag=0; 

 	;MOVX1 _IR_Flag ,#0
	BCLR _IR_Flag
.stabn 0x44,0,306,L290-_main
L290:
;Line#306 			IR_count =0;

 	;MOVU1 _IR_count ,#0
	__SelectBANK _IR_count
	CLR _IR_count
.stabn 0x44,0,307,L291-_main
L291:
;Line#307 			IR_data_deal_flag=1;

 	;MOVX1 _IR_data_deal_flag ,#1
	__SelectBANK _IR_data_deal_flag
	BSET _IR_data_deal_flag
.stabn 0x44,0,308,L292-_main
L292:
;Line#308 		    IRdata[IRdata_len++] = IR_decode();

 	;MOVU1 _main_data@0 ,_IRdata_len
	__SelectBANK _IRdata_len
	MOV A, _IRdata_len
	__SelectBANK _main_data@0
	MOV _main_data@0, A
	;ADDU1 _IRdata_len ,_IRdata_len ,#1
	__SelectBANK _IRdata_len
	INCMS _IRdata_len
	NOP
	;CALLU1 W0 ,_IR_decode
	CALL _IR_decode
	B0MOV W0, A
	;CVUU2 W2:W3 ,_main_data@0
	__SelectBANK _main_data@0
	MOV A, _main_data@0
	__SelectBANKCNST 0
	CLR W3
	;LEA W4:W5 ,_IRdata
	;ADDP2 W2:W3 ,W4:W5 ,W2:W3
	ADD A, #(_IRdata)$L
	B0MOV Z, A
	MOV A, #(_IRdata)$M
	ADC A, W3
	;MOVU1 *W2:W3 ,W0
	B0MOV Y, A
	B0MOV A, W0
	B0MOV @YZ, A
.stabn 0x44,0,309,L293-_main
L293:
;Line#309 		    if(IRdata_len >= IR_DATA_BUFFER_SIZE)	

 	;LT L274 ,_IRdata_len ,#10
	__SelectBANK _IRdata_len
	MOV A, _IRdata_len
	SUB A, #0x0a
	JLT L274
.stabn 0x44,0,310,L294-_main
L294:
;Line#310           		IRdata_len=0;				

 	;MOVU1 _IRdata_len ,#0
	CLR _IRdata_len
.stabn 0xE0,0,2,L295-_main
L295:
.stabn 0x44,0,311,L296-_main
L296:
;Line#311 		}

	JMP L274
L273:
.stabn 0xC0,0,2,L297-_main
L297:
.stabn 0x44,0,313,L298-_main
L298:
;Line#313 		{

 .stabn 0x44,0,315,L299-_main
L299:
;Line#315 			if(IR_count > 1 && IR_data_deal_flag)	//250ms 

 	;LE L277 ,_IR_count ,#1
	__SelectBANK _IR_count
	MOV A, _IR_count
	CMPRS A, #0x01
	JLT L277
	;EQ L277 ,_IR_data_deal_flag ,#0
	__SelectBANK _IR_data_deal_flag
	BTS1 _IR_data_deal_flag
	JMP L277
.stabn 0xC0,0,3,L300-_main
L300:
.stabn 0x44,0,316,L301-_main
L301:
;Line#316 			{		

 .stabn 0x44,0,317,L302-_main
L302:
;Line#317         		IR_data_deal_flag=0;

 	;MOVX1 _IR_data_deal_flag ,#0
	BCLR _IR_data_deal_flag
.stabn 0x44,0,324,L303-_main
L303:
;Line#324 				IR_Data_deal();

 	;CALLV _IR_Data_deal
	CALL _IR_Data_deal
.stabn 0xE0,0,3,L304-_main
L304:
.stabn 0x44,0,325,L305-_main
L305:
;Line#325 			}

L277:
.stabn 0xE0,0,2,L306-_main
L306:
.stabn 0x44,0,326,L307-_main
L307:
;Line#326 		}

L274:
.stabn 0x44,0,327,L308-_main
L308:
;Line#327 		if(touch_check())  //触摸检测

 	;CALLU1 W0 ,_touch_check
	CALL _touch_check
	;EQ L279 ,W0 ,#0
	AND A, #0xFF
	JEQ L279
.stabn 0xC0,0,2,L309-_main
L309:
.stabn 0x44,0,328,L310-_main
L310:
;Line#328 		{

 .stabn 0x44,0,329,L311-_main
L311:
;Line#329 			 sysFunFlag = 1;

 	;MOVX1 _sysFunFlag ,#1
	__SelectBANK _sysFunFlag
	BSET _sysFunFlag
.stabn 0xE0,0,2,L312-_main
L312:
.stabn 0x44,0,330,L313-_main
L313:
;Line#330 		}

L279:
.stabn 0x44,0,331,L314-_main
L314:
;Line#331 		touch_deal();

 	;CALLV _touch_deal
	CALL _touch_deal
.stabn 0xE0,0,1,L315-_main
L315:
.stabn 0x44,0,333,L316-_main
L316:
;Line#333 	}

L271:
.stabn 0x44,0,300,L317-_main
L317:
;Line#300 	while(1)

	JMP L270
.stabn 0xE0,0,0,L318-_main
L318:
.stabn 0x44,0,335,L319-_main
L319:
;Line#335 }                  

L269:
_main_end:

CALLTREE _main invoke _Sys_Init,_IR_decode,_IR_Data_deal,_touch_check,_touch_deal

.stabs "ISR:F13",36,0,0,_ISR_isr

_interrupt@_ISR_isr SEGMENT CODE AT 0x8 INBANK
_vector_for_ISR_isr:
	JMP _ISR_isr

_Function_ISR_isr_code SEGMENT CODE INBANK USING _Function_ISR_isr_data
_ISR_isr:
	__PUSH_REG 2
.stabn 0xC0,0,0,L345-_ISR_isr
L345:
.stabn 0x44,0,342,L346-_ISR_isr
L346:
;Line#342 {   

 .stabn 0x44,0,346,L347-_ISR_isr
L347:
;Line#346 	if(FP00IRQ)

 	;EQ L322 ,0xC8.0 ,#0
	B0BTS1 0xC8.0
	JMP L322
.stabn 0xC0,0,1,L348-_ISR_isr
L348:
.stabn 0x44,0,347,L349-_ISR_isr
L349:
;Line#347 	{             //P00 interrput//P0.0 外部中断(INT0)

 .stabn 0x44,0,349,L350-_ISR_isr
L350:
;Line#349 			if(edgeFlag) //下沿中断

 	;EQ L324 ,_edgeFlag ,#0
	__SelectBANK _edgeFlag
	BTS1 _edgeFlag
	JMP L324
.stabn 0xC0,0,2,L351-_ISR_isr
L351:
.stabn 0x44,0,350,L352-_ISR_isr
L352:
;Line#350 			{     //高电平达到9ms为开始 位

 .stabn 0x44,0,351,L353-_ISR_isr
L353:
;Line#351 				  PEDGE = 0x08;               //触发方式为上沿触发

 	;MOVU1 0xBF ,#8
	MOV A, #0x08
	B0MOV 0xBF, A
.stabn 0x44,0,352,L354-_ISR_isr
L354:
;Line#352 				  edgeFlag = 0; 

 	;MOVX1 _edgeFlag ,#0
	BCLR _edgeFlag
.stabn 0x44,0,353,L355-_ISR_isr
L355:
;Line#353 				  if(IR_time>60)	//判断引导码(9ms+1.12ms)（0.56ms+1.12ms）

 	;LE L326 ,_IR_time ,#60
	__SelectBANK _IR_time
	MOV A, _IR_time
	CMPRS A, #0x3c
	JLT L326
.stabn 0xC0,0,3,L356-_ISR_isr
L356:
.stabn 0x44,0,354,L357-_ISR_isr
L357:
;Line#354 				  {

 .stabn 0x44,0,355,L358-_ISR_isr
L358:
;Line#355 						IR_data[0]=IR_time;		//存储相应位时间宽度 

 	;MOVU1 _IR_data+0 ,_IR_time
	__SelectBANK _IR_data
	MOV _IR_data+0, A
.stabn 0x44,0,356,L359-_ISR_isr
L359:
;Line#356 					    IR_bit=1;						  //位数变量自增

 	;MOVU1 _IR_bit ,#1
	MOV A, #0x01
	__SelectBANK _IR_bit
	MOV _IR_bit, A
.stabn 0x44,0,357,L360-_ISR_isr
L360:
;Line#357 						isRec = 1;

 	;MOVX1 _isRec ,#1
	__SelectBANK _isRec
	BSET _isRec
.stabn 0xE0,0,3,L361-_ISR_isr
L361:
.stabn 0x44,0,358,L362-_ISR_isr
L362:
;Line#358 				   }

L326:
.stabn 0x44,0,359,L363-_ISR_isr
L363:
;Line#359 				   IR_time =0;  //清零时间宽度计数值

 	;MOVU1 _IR_time ,#0
	__SelectBANK _IR_time
	CLR _IR_time
.stabn 0xE0,0,2,L364-_ISR_isr
L364:
.stabn 0x44,0,360,L365-_ISR_isr
L365:
;Line#360 			}

	JMP L325
L324:
.stabn 0xC0,0,2,L366-_ISR_isr
L366:
.stabn 0x44,0,362,L367-_ISR_isr
L367:
;Line#362 			{   //上沿中断

 .stabn 0x44,0,363,L368-_ISR_isr
L368:
;Line#363 				PEDGE = 0x10;  //触发方式为下降沿触发

 	;MOVU1 0xBF ,#16
	MOV A, #0x10
	B0MOV 0xBF, A
.stabn 0x44,0,364,L369-_ISR_isr
L369:
;Line#364 				edgeFlag = 1;

 	;MOVX1 _edgeFlag ,#1
	__SelectBANK _edgeFlag
	BSET _edgeFlag
.stabn 0x44,0,366,L370-_ISR_isr
L370:
;Line#366 				if(isRec)

 	;EQ L329 ,_isRec ,#0
	__SelectBANK _isRec
	BTS1 _isRec
	JMP L329
.stabn 0xC0,0,3,L371-_ISR_isr
L371:
.stabn 0x44,0,367,L372-_ISR_isr
L372:
;Line#367 				{

 .stabn 0x44,0,368,L373-_ISR_isr
L373:
;Line#368 					IR_data[IR_bit]=IR_time;		//存储相应位时间宽度

 	;CVUU2 WG:WH ,_IR_bit
	__SelectBANK _IR_bit
	MOV A, _IR_bit
	__SelectBANKCNST 0
	CLR WH
	;LEA WI:WJ ,_IR_data
	;ADDP2 WG:WH ,WI:WJ ,WG:WH
	ADD A, #(_IR_data)$L
	B0MOV Z, A
	MOV A, #(_IR_data)$M
	ADC A, WH
	;MOVU1 *WG:WH ,_IR_time
	B0MOV Y, A
	__SelectBANK _IR_time
	MOV A, _IR_time
	B0MOV @YZ, A
.stabn 0x44,0,369,L374-_ISR_isr
L374:
;Line#369 					IR_time=0;						//清零时间宽度计数值

 	;MOVU1 _IR_time ,#0
	CLR _IR_time
.stabn 0x44,0,370,L375-_ISR_isr
L375:
;Line#370 					IR_bit++;						  //位数变量自增

 	;ADDU1 _IR_bit ,_IR_bit ,#1
	__SelectBANK _IR_bit
	INCMS _IR_bit
	NOP
.stabn 0x44,0,371,L376-_ISR_isr
L376:
;Line#371 					if(IR_bit==9)				  //如果达到了9位（引导码+8个数据位）

 	;NEI1 L331 ,_IR_bit ,#9
	MOV A, _IR_bit
	CMPRS A, #0x09
	JMP L331
.stabn 0xC0,0,4,L377-_ISR_isr
L377:
.stabn 0x44,0,372,L378-_ISR_isr
L378:
;Line#372 					{

 .stabn 0x44,0,373,L379-_ISR_isr
L379:
;Line#373 						IR_Flag=1;				  //红外数据接收完成标志位置1

 	;MOVX1 _IR_Flag ,#1
	__SelectBANK _IR_Flag
	BSET _IR_Flag
.stabn 0x44,0,374,L380-_ISR_isr
L380:
;Line#374 						IR_bit=0;					  //位数变量清零

 	;MOVU1 _IR_bit ,#0
	__SelectBANK _IR_bit
	CLR _IR_bit
.stabn 0x44,0,375,L381-_ISR_isr
L381:
;Line#375 						isRec =0;

 	;MOVX1 _isRec ,#0
	__SelectBANK _isRec
	BCLR _isRec
.stabn 0xE0,0,4,L382-_ISR_isr
L382:
.stabn 0x44,0,376,L383-_ISR_isr
L383:
;Line#376 					}

L331:
.stabn 0xE0,0,3,L384-_ISR_isr
L384:
.stabn 0x44,0,377,L385-_ISR_isr
L385:
;Line#377 				}

L329:
.stabn 0xE0,0,2,L386-_ISR_isr
L386:
.stabn 0x44,0,378,L387-_ISR_isr
L387:
;Line#378 			}   

L325:
.stabn 0x44,0,379,L388-_ISR_isr
L388:
;Line#379 	        FP00IRQ  = 0;               //清除中断标志

 	;MOVX1 0xC8.0 ,#0
	B0BCLR 0xC8.0
.stabn 0x44,0,380,L389-_ISR_isr
L389:
;Line#380 	        FP00IEN  = 1;               //P0.0 外部中断(INT0)使能

 	;MOVX1 0xC9.0 ,#1
	B0BSET 0xC9.0
.stabn 0xE0,0,1,L390-_ISR_isr
L390:
.stabn 0x44,0,381,L391-_ISR_isr
L391:
;Line#381 	}

	JMP L323
L322:
.stabn 0x44,0,382,L392-_ISR_isr
L392:
;Line#382 	else if(FT0IRQ)   //定时器T0中断 139us中断一次

 	;EQ L333 ,0xC8.4 ,#0
	B0BTS1 0xC8.4
	JMP L333
.stabn 0xC0,0,1,L393-_ISR_isr
L393:
.stabn 0x44,0,383,L394-_ISR_isr
L394:
;Line#383 	{

 .stabn 0x44,0,384,L395-_ISR_isr
L395:
;Line#384 		if(IR_time < 0xf0)IR_time++;

 	;GE L335 ,_IR_time ,#240
	__SelectBANK _IR_time
	MOV A, _IR_time
	SUB A, #0xf0
	JGE L335
.stabn 0x44,0,384,L396-_ISR_isr
L396:
;Line#384 		if(IR_time < 0xf0)IR_time++;

 	;ADDU1 _IR_time ,_IR_time ,#1
	INCMS _IR_time
	NOP
L335:
.stabn 0x44,0,385,L397-_ISR_isr
L397:
;Line#385 	        Touch_time++;

 	;ADDU1 _Touch_time ,_Touch_time ,#1
	__SelectBANK _Touch_time
	INCMS _Touch_time
	NOP
.stabn 0x44,0,387,L398-_ISR_isr
L398:
;Line#387 		T0M=0x70;                   // 16M/16/2= 2uS   Fcpu的2分频  

 	;MOVU1 0xD8 ,#112
	MOV A, #0x70
	B0MOV 0xD8, A
.stabn 0x44,0,388,L399-_ISR_isr
L399:
;Line#388         T0C=186;                    //256-139/2 = 256- 69.5 = 186.5 每139us中断一次      

 	;MOVU1 0xD9 ,#186
	MOV A, #0xba
	B0MOV 0xD9, A
.stabn 0x44,0,389,L400-_ISR_isr
L400:
;Line#389 		FT0IRQ=0;                   // T0 中断请求标志清零。

 	;MOVX1 0xC8.4 ,#0
	B0BCLR 0xC8.4
.stabn 0x44,0,390,L401-_ISR_isr
L401:
;Line#390 		FT0IEN=1;                   //允许响应 T0 中断。

 	;MOVX1 0xC9.4 ,#1
	B0BSET 0xC9.4
.stabn 0x44,0,391,L402-_ISR_isr
L402:
;Line#391         FT0ENB=1;                   //启动定时器T0运行 

 	;MOVX1 0xD8.7 ,#1
	B0BSET 0xD8.7
.stabn 0xE0,0,1,L403-_ISR_isr
L403:
.stabn 0x44,0,393,L404-_ISR_isr
L404:
;Line#393 	}

	JMP L334
L333:
.stabn 0x44,0,395,L405-_ISR_isr
L405:
;Line#395     else if(FTC0IRQ)                   // TC0 interrput

 	;EQ L337 ,0xC8.5 ,#0
	B0BTS1 0xC8.5
	JMP L337
.stabn 0xC0,0,1,L406-_ISR_isr
L406:
.stabn 0x44,0,396,L407-_ISR_isr
L407:
;Line#396     {        

 .stabn 0x44,0,397,L408-_ISR_isr
L408:
;Line#397 	      FTC0IRQ=0;                // Clr  flag

 	;MOVX1 0xC8.5 ,#0
	B0BCLR 0xC8.5
.stabn 0x44,0,398,L409-_ISR_isr
L409:
;Line#398           if(buzzerEnableFlag == 0)

 	;NEX1 L339 ,_buzzerEnableFlag ,#0
	__SelectBANK _buzzerEnableFlag
	BTS0 _buzzerEnableFlag
	JMP L339
.stabn 0xC0,0,2,L410-_ISR_isr
L410:
.stabn 0x44,0,399,L411-_ISR_isr
L411:
;Line#399 		  {

 .stabn 0x44,0,400,L412-_ISR_isr
L412:
;Line#400 		      BUZZER_OFF;

 	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
.stabn 0x44,0,401,L413-_ISR_isr
L413:
;Line#401               return;

	JMP L320
.stabn 0xE0,0,2,L414-_ISR_isr
L414:
.stabn 0x44,0,402,L415-_ISR_isr
L415:
;Line#402 		  }

L339:
.stabn 0x44,0,403,L416-_ISR_isr
L416:
;Line#403 		  if(buzzerCount++ > 3000)

 	;MOVI1 WG ,_sdata321
	__SelectBANK _sdata321
	MOV A, _sdata321
	__SelectBANK __SrcLArg0_isr
	MOV __SrcLArg0_isr, A
	;ADDU1 _sdata321 ,WG ,#1
	ADD A, #0x01
	__SelectBANK _sdata321
	MOV _sdata321, A
	;CVUI2 WG:WH ,WG
	__SelectBANKCNST 0
	CLR WH
	;LE L341 ,WG:WH ,#3000
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
	JLE L341
.stabn 0xC0,0,2,L417-_ISR_isr
L417:
.stabn 0x44,0,404,L418-_ISR_isr
L418:
;Line#404 		  {

 .stabn 0x44,0,405,L419-_ISR_isr
L419:
;Line#405 		      buzzerEnableFlag = 0;

 	;MOVX1 _buzzerEnableFlag ,#0
	__SelectBANK _buzzerEnableFlag
	BCLR _buzzerEnableFlag
.stabn 0x44,0,406,L420-_ISR_isr
L420:
;Line#406 		      buzzerCount = 0;

 	;MOVU1 _sdata321 ,#0
	__SelectBANK _sdata321
	CLR _sdata321
.stabn 0x44,0,407,L421-_ISR_isr
L421:
;Line#407 			  BUZZER_OFF;

 	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
.stabn 0xE0,0,2,L422-_ISR_isr
L422:
.stabn 0x44,0,408,L423-_ISR_isr
L423:
;Line#408 		  }

	JMP L342
L341:
.stabn 0xC0,0,2,L424-_ISR_isr
L424:
.stabn 0x44,0,410,L425-_ISR_isr
L425:
;Line#410 		  {

 .stabn 0x44,0,411,L426-_ISR_isr
L426:
;Line#411 		       if(buzzerFlag)

 	;EQ L343 ,_buzzerFlag ,#0
	__SelectBANK _buzzerFlag
	BTS1 _buzzerFlag
	JMP L343
.stabn 0xC0,0,3,L427-_ISR_isr
L427:
.stabn 0x44,0,412,L428-_ISR_isr
L428:
;Line#412 			   {

 .stabn 0x44,0,413,L429-_ISR_isr
L429:
;Line#413 			       buzzerFlag = 0;

 	;MOVX1 _buzzerFlag ,#0
	BCLR _buzzerFlag
.stabn 0x44,0,414,L430-_ISR_isr
L430:
;Line#414                    BUZZER_OFF;

 	;MOVX1 0xD5.4 ,#1
	B0BSET 0xD5.4
.stabn 0xE0,0,3,L431-_ISR_isr
L431:
.stabn 0x44,0,415,L432-_ISR_isr
L432:
;Line#415 			   }

	JMP L344
L343:
.stabn 0xC0,0,3,L433-_ISR_isr
L433:
.stabn 0x44,0,417,L434-_ISR_isr
L434:
;Line#417 				{

 .stabn 0x44,0,418,L435-_ISR_isr
L435:
;Line#418 			       buzzerFlag = 1;

 	;MOVX1 _buzzerFlag ,#1
	__SelectBANK _buzzerFlag
	BSET _buzzerFlag
.stabn 0x44,0,419,L436-_ISR_isr
L436:
;Line#419                    BUZZER_ON;

 	;MOVX1 0xD5.4 ,#0
	B0BCLR 0xD5.4
.stabn 0xE0,0,3,L437-_ISR_isr
L437:
.stabn 0x44,0,420,L438-_ISR_isr
L438:
;Line#420 			   }

L344:
.stabn 0xE0,0,2,L439-_ISR_isr
L439:
.stabn 0x44,0,421,L440-_ISR_isr
L440:
;Line#421 		  }

L342:
.stabn 0xE0,0,1,L441-_ISR_isr
L441:
.stabn 0x44,0,423,L442-_ISR_isr
L442:
;Line#423     }       

L337:
L334:
L323:
.stabs "buzzerCount:V12",38,0,0,_sdata321
.stabn 0xE0,0,0,L443-_ISR_isr
L443:
.stabn 0x44,0,424,L444-_ISR_isr
L444:
;Line#424 }                                 //

L320:
	__POP_REG 2
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
