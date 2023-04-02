
CHIP	SN8P2501D					; Select the CHIP
//{{SONIX_CODE_OPTION
	.Code_Option	LVD		LVD_L		; 2.0V Reset
	.Code_Option	Reset_Pin	P11
	.Code_Option	Watch_Dog	Disable		; Disable Watchdog
	.Code_Option	High_Clk	4M_X'tal	; Crystal/Resonator: 455Khz~8Mhz
	.Code_Option	Fcpu		#7     ; Fcpu = Fosc/16
	.Code_Option	Security	Enable
	.Code_Option	Noise_Filter	Enable
//}}SONIX_CODE_OPTION
.nolist							; do not list the macro file

	INCLUDESTD	MACRO1.H
	INCLUDESTD	MACRO2.H
	INCLUDESTD	MACRO3.H

.list
							; Enable the listing function
.DATA
	ORG    000H
        work0           ds      1
        SysFlag		ds	1
        countdelay	ds	1

       	AdcOverTime	equ	SysFlag.0
	Flag130ms	equ	SysFlag.1
	Flag10ms	equ	sysflag.2
	flag1s		equ	sysflag.3
.CODE
	ORG	0				;Code section start
	jmp		Reset				;Reset vector
							;Address 4 to 7 are reserved
	ORG	8	
Reset:
        CLR P0M ; 所有端口设为输入模式。
	CLR P1M
	CLR P5M
	MOV A, #0FFH ; 所有端口设为输出模式。
	B0MOV P2M, A
	B0MOV P1M, A
	B0MOV P5M, A
	;B0BCLR P1M.2 ; P1.2 设为输入模式。
	;B0BSET P1M.2 ; P1.2 设为输出模式。

        ;B0BSET P1.0 ; P1.0 置高。
	;B0BSET P1M.0 ; P1.0 设为输出模式。
        ;MOV A, #01H ; 开启 P1.0 的漏极开路功能。
	;B0MOV P1OC, A
Loop:
        MOV A, #0FFH ; 立即数 0FFH 写入所有输出口。
	B0MOV P2, A
	B0MOV P1, A
	B0MOV P5, A
        
        call    Delay50ms
        MOV A, #00H ; 立即数 0FFH 写入所有输出口。
	B0MOV P2, A
	B0MOV P1, A
	B0MOV P5, A
        call    Delay50ms
       ; CALL    INIT_IRQ

        JMP Loop;






INIT_IRQ:

;定时器T0初始化
	MOV	A,	#01100000b	;定时器模式Fcpu/4 16M/4/4=1M 1U计一次
	B0MOV	T0M,	A		;
	MOV	A,	#256-100	;计数寄存器赋初值(定时100U)
	MOV	T0C,	A		;
	
	B0BCLR	FT0IRQ			;清中断标志
	B0BSET	FT0IEN			;允许T0中断
	B0BSET	FT0ENB			;启动T0

;定时器TC0初始化
	MOV	A,#01110100B   ;自动装载
	B0MOV	TC0M,A
	MOV	A,#256-200     ; F = 16M /4 /2      --0.5US计数一次 
	B0MOV	TC0C,A
	B0MOV	TC0R,A	
  
	B0BCLR	FTC0IRQ		;清中断标志
	B0BSET	FTC0IEN		;允许TC0中断 
	B0BSET	FTC0ENB		;启动TC0 
   
	B0BSET	FGIE		;开总中断
	RET

MY_IRQ:
        PUSH
        DECMS	work0;;减1 Rwk00,为0就跳过下一行
        JMP     LED1
        MOV     A,#2
        MOV     work0,A
        MOV A,  #00H ; 立即数 00H 写入所有输出口。
	B0MOV P0, A
	B0MOV P1, A
	B0MOV P5, A
        JMP     IRQ_RET
LED1:  
        MOV A, #0FFH ; 立即数 0FFH 写入所有输出口。
	B0MOV P0, A
	B0MOV P1, A
	B0MOV P5, A
IRQ_RET:
        POP
        RETI


;------------------------------------------------------
;delay 52ms
;-=----------------------------------------------------
Delay50ms:
	mov		a,	#250
	mov		countdelay,	a
delay50ms1:
	dint				;delay 100ms
	bclr            Flag10ms	;
	eint				;
Delay50ms2:				;
;	b0bset		FWDRST		;Clear watchdog timer
;	bts1		Flag10ms	;
;	jmp             Delay50ms2
	decms		countdelay
	jmp		delay50ms1
Delay50msEnd:
	ret		


        ENDP

