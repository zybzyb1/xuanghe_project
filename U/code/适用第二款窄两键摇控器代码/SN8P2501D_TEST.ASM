
;********************************************************
;晶振  RC: 内部16MHz          当前版本: V0
;目标 MCU: SN8P2501BP,SOP14   
;开发作者:zyb                 烧录校验:  
;开始日期: 2022.9.26          完成日期: 2022.9.X
;本源码适用于发热管加热电路控制板，硬件部分由两路继电器控制
;输入控制由摇控器与触摸开关两路分别进行控制两路加热
;********************************************************
;               _____________  ____________
;              |             \/            |
;             -|P2.2                   P2.3|-TOUCH_PIN触摸输入脚
;        LIGHT-|P2.1                   P2.4|-B_TOUCH_LED_PIN蓝色触摸指示灯
;             -|P2.0                   P2.5|-
;          +5V-|VDD                     VSS|-GND
;       RELAY1-|P1.3/XIN          INT0/P0.0|-IR_PIN红外输入脚
;       RELAY2-|1.2/XOUT               P1.0|-R_POWER_LED红色电源指示灯
;             -|P1.1/RET/VPP   PWM/BZ0/P5.4|-pwm/buzzer
;              |___________________________|
;                   SN8P2511P,DIP8
;********************************************************
;#include <SN8P2501D.h>          // 头文件
;#include "global.h"             //

;#define   IR_ONOFF_BUTTON     0x1B    //红外摇控板开关键值
;#define   IR_LIGHT_BUTTON     0xBB    //红外摇控板加热丝档位调整键值

;#define   DELAY1_OFF     FP13=0    
;#define   DELAY2_OFF     FP12=0 
;#define   DELAY1_ON      FP13=1
;#define   DELAY2_ON      FP12=1 
;#define   TOUCH_PIN      FP23
;#define   BUZZER_OFF     FP54=1
;#define   BUZZER_ON      FP54=0

;#define   BUTTON_VALUE_MAX   4    //最大档位, 其实只有3档
;#define   IR_DATA_BUFFER_SIZE  5

;#define  R_POWER_LED_ON      FP24=0
;#define  B_BTOUCH_LED_ON     FP10=0
;#define  B_BTOUCH_LED_OFF    FP10=1
;********************************************************


CHIP	SN8P2501D					; Select the CHIP
//{{SONIX_CODE_OPTION
	.Code_Option	LVD		LVD_L		; 2.0V Reset
	.Code_Option	Reset_Pin	P11
	.Code_Option	Watch_Dog	Disable		; Disable Watchdog
	.Code_Option	High_Clk	IHRC_16M	; Internal 16M RC Oscillator
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
	ORG    00H
       ;宏定义
       IR_ONOFF_BUTTON   equ  1; 0x1B    ;红外摇控板开关键值
       IR_LIGHT_BUTTON   equ  9; 0xBB    ;红外摇控板加热丝档位调整键值
       
       DELAY1_PIN    equ   P1.3    
       DELAY2_PIN    equ   P1.2 
       TOUCH_PIN     equ   P2.3
       BUZZER_PIN    equ   P5.4
       LIGHT_PIN     equ   P2.1
       R_POWER_LED_PIN     equ   P2.4 
       B_BTOUCH_LED_PIN    equ   P1.0
      

       BUTTON_VALUE_MAX    equ   7    //最大档位, 其实只有6档
       IR_DATA_BUFFER_SIZE equ   5

      
      

       ;数据定义
       sysFlag          ds   1 
       sysFlag1         ds   1
       IR_time          ds   1		;下降沿之间的时间计数值
       IR_data          ds   1		;引导码+8个位数据各自占用的时间
       Touch_timeL      ds   1          ;触摸计时器L
       Touch_timeH      ds   1          ;触摸计时器H
       IR_bit           ds   1		;变量IR_bit用于指示红外数据的位数
       btn_value        ds   1          ;红外按键键值寄存器

       IR_count         ds   1          ;红外管接收到数据后延时计数器--250ms
       IRdata           ds   1
       buzzerCntL       ds   1          ;蜂鸣器计数器低字节
       buzzerCntH       ds   1          ;蜂鸣器计数器高字节
       pulseCount       ds   1          ;脉冲计数 ---计数前17个脉冲
       
       tempVal          ds   1          ;临时变量
 
       IR_Flag          equ  sysFlag.0 	;红外数据接收完成标志位
       Touch_flag       equ  sysFlag.1  ;触摸IC输出标志
       touch_preFlag    equ  sysFlag.2  ;上次触摸IC输出标志
       timeFunFlag      equ  sysFlag.3;       ;定时功能标志
       sysFunFlag       equ  sysFlag.4;       ;系统功能标志
       isRec            equ  sysFlag.5;
       buzzerFlag       equ  sysFlag.6;
       buzzerEnableFlag equ  sysFlag.7;

       edgeFlag         equ  sysFlag1.0     ;红外管接收脚边沿标识
       light_flag       equ  sysFlag1.1     ;照明LED灯状态指示灯
       isStartFlag      equ  sysFlag1.2     ;启动接收标志
       workFlag         equ  sysFlag1.3     ;正试计数脉冲
       int0_flag        equ  sysFlag1.4     ;int0中断标志
	   
.CODE
	ORG	0				;Code section start
	jmp		Reset				;Reset vector
							;Address 4 to 7 are reserved
	ORG	8
        JMP     IntService

        ORG     10H	
Reset:
        CLR    OSCM         ;// 普通模式(双时钟)         
        CLR    INTEN        ;                
        CLR    INTRQ        ;               
      
        //--- I0 Config --------------------------------------
        MOV  A, #0FEH
        B0MOV P0M,  A;                // P00输入  0=输入   1=输出
        MOV  A, #0F7H
        B0MOV P2M,  A;                // P2.3输入 P2.4输出驱动LED红色电源指示灯 P2.1输出驱动8个LED灯 高电平有效

        MOV  A, #0ffH
        B0MOV P1M,  A;                // P1.0输出驱动LED 蓝色触摸灯    P1.3P1.2输出驱动两组继电器
        MOV  A, #0ffH
        B0MOV P5M,  A;                // P5.4输出 蜂鸣器输出保持高电平
        
        MOV   A, 0x01;
        B0MOV P0UR, A;                // 0=不上拉 1=上拉 P0.0拉
        MOV   A, 0x00
        B0MOV P2UR, A;                //
        B0MOV P1UR, A;                // 
        B0MOV P5UR, A;                //

        B0BCLR DELAY1_PIN;         
        B0BCLR DELAY2_PIN; 
	B0BCLR R_POWER_LED_PIN;
        B0BSET B_BTOUCH_LED_PIN;
        B0BCLR BUZZER_PIN;
   
        CLR    sysFlag
        CLR    sysFlag1
        CLR    btn_value
        CLR    IR_data
        CLR    IR_time
        CLR    IR_bit
        CLR    IRdata
        CLR    IR_count
        CLR    buzzerCntL
        CLR    buzzerCntH
        CLR    Touch_timeL
        CLR    Touch_timeH
        CLR    pulseCount
        
        B0BCLR   sysFunFlag   ;上电置0
        B0BCLR   light_flag
        B0BSET     buzzerEnableFlag;蜂鸣器响 

        //--- P00 Config-------------------------------------
        MOV   A, #10H
        B0MOV PEDGE,  A;               //下降沿触发中断
        ;PEDGE = 0x08;               //上升沿触发中断
        B0BCLR	FP00IRQ;               //清除中断标志
        B0BSET   FP00IEN;               //P0.0 外部中断(INT0)使能
        B0BSET   edgeFlag;

        //--- T0  Config--定时器T0配置------------------------------------
		//FT0TB = 0;                  //禁止 RTC
        MOV  A,  #70H
        B0MOV T0M, A;                   // 16M/16/2= 2uS   Fcpu的2分频 
        //T0M=0x10;                   // 1M/16/128=500uS   Fcpu的128分频
        MOV  A,  #0baH   ;
        B0MOV T0C,   A ;                    //256-139/2 = 256- 69.5 = 186.5 每139us中断一次 实际上是150us     
	B0BCLR	FT0IRQ ;                   // T0 中断请求标志清零。
	B0BSET 	FT0IEN ;                   //允许响应 T0 中断。
        B0BSET   FT0ENB;                   //启动定时器T0运行 

        //--- TC0 PWM Config  蜂鸣器驱动 2K频率-高电平和低电平的时间宽度都为 250μs--------------------------------------
        MOV  A, #70H
        B0MOV TC0M, A;                  // 16MHz/16=  Fcpu/2   2us  256-250/2=
        MOV  A, #155
        B0MOV  TC0R, A;                   //每隔125*2 =250us中断一次
        B0MOV  TC0C, A;                   //  
        B0BSET  FALOAD0;                  //使能 TC0 自动装载
        B0BCLR	FTC0OUT;                  //允许P5.4口作PWM输出
	B0BCLR	FPWM0OUT;                //允许PWM/BUZZER功能  
        B0BSET   FTC0IEN;                  //允许中断Enable TC0 Interrput
        B0BSET   FTC0ENB;                  // 定时器开启
        //----Start Run---------------------------------------
        B0BSET   FGIE;                    // Enable all Interrput
 
        

Loop:
       
        CALL IR_deal     ;红外处理
        CALL touch_check ;触摸检测
        CALL touch_deal  ;触摸处理
     
        JMP Loop;


;**************** 红外处理************************
IR_deal: 
        B0BTS1     IR_Flag
        JMP        IR_deal_end
        MOV        A,#230
        CMPRS      A,IR_count
        JMP        IR_noden      ;IR_count != 230 还存在 IR_count > 230的情况
IR_den:
        B0BCLR     IR_Flag       ;IR_count = 230 //红外数据接收完成后 230*139 = 31970us处理数据
        CLR        IR_count
        
        ;B0BTS0     sysFunFlag ;红外按键是在系统功能未开启的情况下才能使用，如果sysFunFlag=1则系统功能己开启
        ;JMP        IR_deal_end

        B0MOV      A, IRdata
	AND        A, #0FH
	B0MOV      tempVal,A  ;低四位代表IR_LIGHT_BUTTON关键值 
        
        B0BCLR     FC          ;高四位代表IR_ONOFF_BUTTON开键值
        RRCM       IRdata
        B0BCLR     FC 
        RRCM       IRdata
        B0BCLR     FC 
        RRCM       IRdata
        B0BCLR     FC 
        RRCM       IRdata 
        B0MOV      A, IRdata
        CMPRS      A, tempVal
	JMP        value_noDen    ;如果两键值不相等则继续判断
        CLR        IRdata
        JMP        IR_deal_end ;如果两键值相等则退出
value_noDen:      ;如果两键值不相等则继续判断
        CLR        IRdata
        B0BTS0    FC
        JMP        onoffDeal ;没借位，说明IR_ONOFF_BUTTON开键值 > IR_LIGHT_BUTTON关键值 
                             ;借位，说明IR_ONOFF_BUTTON开键值 < IR_LIGHT_BUTTON关键值
        ;灯键处理 
        B0BSET     buzzerEnableFlag;蜂鸣器响
	B0BSET     sysFunFlag
	B0BCLR     B_BTOUCH_LED_PIN;
        B0BSET     R_POWER_LED_PIN;
        CALL       btn_inc_fun     ;调用键值加1处理函数
        JMP        IR_deal_end ; 
 
onoffDeal:   ;电源开关键开处理
        B0BSET     buzzerEnableFlag;蜂鸣器响 
        B0BTS0     sysFunFlag ;红外按键是在系统功能未开启的情况下才能使用，如果sysFunFlag=1则系统功能己开启
        JMP        IR_deal_end ;

        B0BTS0     light_flag
        JMP        light_off_d ;关处理
        B0BSET     LIGHT_PIN   ;开灯处理灯亮
        B0BSET     light_flag
       	B0BSET     R_POWER_LED_PIN;
        B0BCLR     B_BTOUCH_LED_PIN;
        JMP        IR_deal_end ;
light_off_d:
        B0BCLR     LIGHT_PIN   ;关灯处理
        B0BCLR     light_flag
	B0BCLR     R_POWER_LED_PIN;
        B0BSET     B_BTOUCH_LED_PIN;
        JMP        IR_deal_end ;
	
IR_noden:
      B0BTS1      FC
      JMP         IR_den ;发生了借位说明IR_count > 230https://www.msn.cn/zh-cn/feed
      ;JMP         IR_deal_end            
IR_deal_end:
      B0BTS1   int0_flag
      RET
      MOV      A, #0F0H
      CMPRS    A,IR_time 
      RET
	  JMP      IR_BUDEN0
IR_DEN0:
      CLR        IR_time
      CLR        pulseCount
      B0BSET     edgeFlag          ;红外管接收脚边沿标识
      B0BCLR     isRec             ;照明LED灯状态指示灯
      B0BCLR     isStartFlag       ;启动接收标志
      B0BCLR     workFlag
	  B0BCLR     int0_flag
 //--- P00 Config-------------------------------------
      MOV   A, #10H
      B0MOV PEDGE,  A;               //下降沿触发中断
      ;PEDGE = 0x08;               //上升沿触发中断
      B0BCLR	FP00IRQ;               //清除中断标志
      B0BSET   FP00IEN;               //P0.0 外部中断(INT0)使能
      B0BSET   edgeFlag;
      RET
IR_BUDEN0:
      B0BTS1   FC
      JMP      IR_DEN0
      RET
;******************end***********************************
;/*************触摸功能*********************/

;-------------触摸输出检测-------------------
;无触摸时高电平，有触摸时低电平时长大于300ms
touch_check:
    B0BTS0   TOUCH_PIN 
    JMP      touch_Hight        ;当引脚高电平   
    B0BTS0   Touch_flag       ;当引脚为低电平执行
    JMP      touch_L;当Touch_flag=0时执行
                    ;当Touch_flag=1时执行 //139微秒 *500 = 69.5ms
    MOV      A,#1 ; 500 =1F4H    
    CMPRS    A,Touch_timeH
    JMP      Hsubnden
    MOV      A,#0f4H  ;Touch_timeH =1 处理 比较低字节 
    CMPRS    A,Touch_timeL
    JMP      Lsubnden    ;跳至低字节不相等，高字节相等，处理
    JMP      daden500;低字节相等，高字节相等，处理
    
Lsubnden:
     B0BTS1   FC 
     JMP      daden500;c=0发生借位，Touch_timeL>#F4H且 高字节相等，
     JMP      touch_check_end ;c=0未发生借位，

Hsubnden:   ;Touch_timeH !=1 处理 
    B0BTS1   FC
    JMP      daden500   ;进位标志置 0 借位发生，表明Touch_timeH > 1 即大于500
    JMP      touch_check_end ;Touch_timeH < 1

daden500:    ; Touch_timeH  Touch_timeL >=500 执行   
    CLR       Touch_timeL
    CLR       Touch_timeH
    B0BSET   Touch_flag
    B0BSET   sysFunFlag
    JMP      touch_check_end 
touch_L:
    CLR      Touch_timeL
    CLR      Touch_timeH
    JMP      touch_check_end


touch_Hight:    ;当引脚为高电平执行  
    B0BTS1   Touch_flag        ;当引脚为低电平执行
    JMP      touch_flag_L;当Touch_flag=0时执行
    ;处理if(Touch_time > 2000) 
    ;2000 hex 7D0
    MOV      A,   #7   ; 先判断高位 Touch_timeH=7   
    CMPRS    A,   Touch_timeH
    JMP      Hnoden 
Hden:;高字节相等继续判断低字节
    MOV      A,   #0d0H 
    CMPRS    A,   Touch_timeL
    JMP      Lnoden
Lden:;高低字节都相等  说明计数等于2000 处理等于大于2000
    CLR      Touch_timeL    
    CLR      Touch_timeH
    B0BCLR   Touch_flag
    JMP      touch_check_end

Hnoden:;高字节不相等
    B0BTS0   FC    
    JMP      touch_check_end ;没发生借位
    JMP      Lden ; Touch_timeH>7 说明计数大于2000 处理大于2000
Lnoden:    ;处理高字节等于7低字节不等于D0H
    B0BTS0   FC    
    JMP      touch_check_end ;没发生借位，说明Touch_timeL<7DH
    JMP      Lden ;发生借位 Touch_timeH=7,Touch_timeL>7DH 说明计数大于2000 处理大于2000
touch_flag_L:
    CLR       Touch_timeL
    CLR       Touch_timeH
   ; JMP       touch_check_end
touch_check_end:
    RET
;-------------------------------------------------------------
;-----------------触摸处理------------------------------------
touch_deal:
    B0BTS0     Touch_flag   ; 判断触摸标志==1
    JMP        deal_den1    ;Touch_flag==1处理
    B0BCLR     touch_preFlag ;Touch_flag==0处理
    JMP        touch_deal_end

deal_den1:
    B0BTS0     touch_preFlag   ; 判断上次触摸标志touch_preFlag==0？
    JMP        touch_deal_end  ; touch_preFlag=1 处理
    B0BSET     touch_preFlag   ;touch_preFlag=0 处理 
    B0BSET     buzzerEnableFlag;蜂鸣器响
    B0BCLR     B_BTOUCH_LED_PIN;
    B0BSET     R_POWER_LED_PIN;
    CALL       btn_inc_fun     ;调用键值加1处理函数
touch_deal_end:
   
    RET 

btn_inc_fun:   ;键值加1处理函数 判断键值是否超过最大值BUTTON_VALUE_MAX
    INCMS      btn_value
    NOP
    MOV        A, #BUTTON_VALUE_MAX
    CMPRS      A, btn_value
    JMP        deal_noden2   ;btn_value不等BUTTON_VALUE_MAX
deal_den2:                   ;btn_value相等BUTTON_VALUE_MAX
    MOV        A,  #1  
    B0MOV      btn_value,A
    CALL       delay_action_fun
    JMP        btn_end
deal_noden2:    ;btn_value不等BUTTON_VALUE_MAX            
    B0BTS1     FC
    JMP        deal_den2 ;发生借位说明btn_value>BUTTON_VALUE_MAX
    CALL       delay_action_fun
    ;JMP        btn_end     
btn_end:
 
    RET 	
;-------------------------------------------------------------
;***************************END********************************

;8888888888*继电器动作函数*8888888888888888888
delay_action_fun: 
    MOV      A,#0
    CMPRS    A, btn_value
    JMP      cmpare1
    B0BCLR   DELAY1_PIN  ;btn_value=0 处理
    B0BCLR   DELAY2_PIN  ; 断开所有继电器
    JMP      delay_fun_end
cmpare1:
    MOV      A, #1
    CMPRS    A, btn_value 
    JMP      cmpare2
    B0BSET   DELAY1_PIN;btn_value=1 处理
    B0BCLR   DELAY2_PIN  ;继电器2断开继电器1吸合
    JMP      delay_fun_end
cmpare2:
    MOV      A, #2
    CMPRS    A, btn_value 
    JMP      cmpare3
    B0BCLR   DELAY1_PIN ;btn_value=2 处理
    B0BSET   DELAY2_PIN ;继电器1断开继电器2吸合
    JMP      delay_fun_end
cmpare3:
    MOV      A, #3
    CMPRS    A, btn_value 
    JMP      cmpare4
    B0BSET   DELAY1_PIN ;btn_value=3 处理
    B0BSET   DELAY2_PIN ;吸合所有继电器
    JMP      delay_fun_end
cmpare4:
    MOV      A, #4
    CMPRS    A, btn_value 
    JMP      cmpare5
    B0BSET   LIGHT_PIN;btn_value=4 处理 灯点亮           
    JMP      delay_fun_end
cmpare5:
    MOV      A, #5
    CMPRS    A, btn_value 
    JMP      cmpare6
    B0BSET   LIGHT_PIN ;btn_value=5 处理灯亮
    B0BCLR   DELAY1_PIN ;
    B0BCLR   DELAY2_PIN; 断开所有继电器
    JMP      delay_fun_end
cmpare6:
    MOV      A, #6
    CMPRS    A, btn_value 
    JMP      delay_fun_end
    B0BCLR   LIGHT_PIN ;btn_value=6 处理 处理灯灭
    B0BCLR   sysFunFlag  
    B0BCLR   light_flag    
    B0BCLR   R_POWER_LED_PIN;
    B0BSET   B_BTOUCH_LED_PIN;
    ;DELAY1_PIN = DELAY_OFF ;
    ;DELAY2_PIN = DELAY_OFF ; 断开所有继电器
   ; JMP      delay_fun_end
 
delay_fun_end:
     RET
;8888888888888888*end*888888888888888888888
;
;脉冲宽度说明：高电平时宽1.75ms低电平时宽0.56ms为0 ，高电平时宽0.56ms低电平时宽0.56ms为1
;              前面17个脉冲8个+9个0，不计入内
IntService:
      PUSH
;********************** INT0 中断服务程序************************** 
       //P00 interrput//P0.0 外部中断(INT0)
      B0BTS1   FP00IRQ ; 检测 P00IRQ。 ; INT0 中断服务程序
      JMP      T0_int ; P00IRQ = 0。
      B0BCLR   FP00IRQ ; P00IRQ 清零。
      B0BSET   int0_flag
   
      B0BTS1   edgeFlag  ;
      JMP      Rising_edge;跳至上升沿中断处理 
   
  ;Falling edge    //下降沿中断  
      MOV      A, #8   ; //触发方式设为上沿触发
      B0MOV    PEDGE,A
      B0BCLR   edgeFlag  

      B0BTS0   workFlag
      JMP      work_pluse ;开始记录时间长 1-0码 

      B0BTS1   isRec     
      JMP      first_int  ;0：第一次下沿中断

      B0BTS0   isStartFlag ;启动标志0 判断4.5ms高电平脉宽
      JMP      first_int   ;为1,退出
      MOV      A, #25     ;//判断引导码4.5ms, 25*139us=3.475ms
      CMPRS    A,IR_time
      JMP      timeBuDen  ;跳至IR_time!=25处理
falling_result:             ; IR_time=25处理
      CLR      IR_data
      B0BSET   isStartFlag
      MOV      A,#0
      B0MOV    IR_bit,A  ; //位数变量自增
      CLR      IR_time   ; //清零时间宽度计数值
      JMP      Exit_int0      
timeBuDen:  
      B0BTS1   FC
      JMP      falling_result
      CLR      IR_time   ;//清零时间宽度计数值
      JMP      Exit_int0  ;没借位说明IR_time<25 

first_int:
      CLR      IR_time
      JMP      Exit_int0

work_pluse:    ;开始记录时间长 1-0码 
      MOV      A, #5
      CMPRS    A, IR_time
      JMP      noDen5
timeDen5:                ;IR_time>=5,若“时间间隔”比5大那肯定是“1码”反之为“0码”
      MOV      A, #80H  
      OR       IR_data, A ;//通过按位或运算高位填1    		
      JMP      dataOK
noDen5:
      B0BTS1   FC			    		
      JMP      timeDen5  ;产生借位说明IR_time>5			                   
dataOK:	 
      CLR      IR_time	 ;清零时间宽度计数值        //若数据没有拼合完8次
      INCMS    IR_bit 	 ;位数变量自增	
      MOV      A, #8	 ;如果达到了6位（8个数据位）
      CMPRS    A, IR_bit
      JMP      bitBuden9
                         ;IR_bit达到了8位（8个数据位）处理
      B0BSET   IR_Flag   ;红外数据接收完成标志位置1
      CLR      IR_bit    ;位数变量清零
      CLR      pulseCount
      B0BCLR   isRec
      B0BCLR   isStartFlag
      B0BCLR   workFlag
    
      MOV      A, #IR_LIGHT_BUTTON      
      CMPRS    A, IR_data     
      JMP      IRd_buDenLight
      INCMS    IRdata
      JMP      Exit_int0
IRd_buDenLight:
      MOV      A, #IR_ONOFF_BUTTON
      CMPRS    A, IR_data 
      JMP      Exit_int0
      MOV      A, #0x10
      ADD      IRdata,A
      JMP      Exit_int0
bitBuden9:			 
       B0BCLR  FC    ;通过右移运算“腾出”位置准备下一位判定
       RRCM    IR_data 
       JMP      Exit_int0 	
     
  
Rising_edge:;上升沿中断
      MOV      A,   #010H
      B0MOV    PEDGE,A
      B0BSET   edgeFlag	 ;配置触发方式为下降沿触发;
      		         	

      B0BTS0   workFlag
      JMP      pulseBuden

      B0BTS1   isRec     
      JMP      first_edge_int  ;0：第一次上沿中断
     
      B0BTS1   isStartFlag ;启动标志
      JMP      pulseBuden
      INCMS    pulseCount
      MOV      A,#17
      CMPRS    A, pulseCount
      JMP      pulseBuden
      CLR      pulseCount
      B0BSET   workFlag
pulseBuden:
      CLR      IR_time
      JMP      Exit_int0

first_edge_int:
       ;第一次上沿中断,开始处理9ms判断
      MOV      A, #55     ;//判断引导码(9ms+1.12ms)（0.56ms+1.12ms） 55*139us=7.645ms
      CMPRS    A,IR_time
      JMP      timeBuDen1  ;跳至IR_time!=55处理
rising_result:             ; IR_time=60处理
      CLR      IR_data
      B0BSET   isRec
      MOV      A,#0
      B0MOV    IR_bit,A  ; //位数变量自增
      CLR      IR_time   ; //清零时间宽度计数值
      B0BCLR   isStartFlag;//清零启动标志
      JMP      Exit_int0      
timeBuDen1:  
      B0BTS1   FC
      JMP      rising_result
      CLR      IR_time   ;//清零时间宽度计数值
      JMP      Exit_int0  ;没借位说明IR_time<55  
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;     
						
Exit_int0:
       CLR       IR_count ;//有接收数据则清零延时计数器  
       B0BSET    FP00IEN  ;//P0.0 外部中断(INT0)使能
       JMP   Exit_int

;******************** T0 中断程序********************************
T0_int:  ; T0 中断程序。//定时器T0中断 139us中断一次
	B0BTS1   FT0IRQ    ; 检查是否有 T0 中断请求标志。
	JMP      TC0_int   ;
	B0BCLR   FT0IRQ    ;清 T0IRQ。 ;// T0 中断请求标志清零。
	MOV      A, #186   ;256-139/2 = 256- 69.5 = 186.5 每139us中断一次
	B0MOV    T0C, A

        MOV      A, #0F0H
        CMPRS    A,IR_time 

        INCMS    IR_time

        INCMS    Touch_timeL
        JMP      timeLno0
        INCMS    Touch_timeH  
timeLno0:      
        B0BTS0   IR_Flag        
        INCMS    IR_count   ;//接收到红外数据,计数器加1
        MOV      A, #70H
        B0MOV    T0M, A     ;16M/16/2= 2uS   Fcpu的2分频
    
        B0BSET   FT0IEN     ; //允许响应 T0 中断。
        B0BSET   FT0ENB     ; //启动定时器T0运行 
        JMP   Exit_int

;*************TC0中断子程序***********************************
TC0_int:  ; TC0 中断程序。 250uS
        B0BTS1 FTC0IRQ   ; 检查是否有 TC0 中断请求标志。 
	JMP EXIT_INT     ; TC0IRQ = 0，退出中断。
	B0BCLR FTC0IRQ   ; 清 TC0IRQ。
        MOV  A, #70H
        B0MOV TC0M, A;                  // 16MHz/16=  Fcpu/2   2us  256-250/2= 
        MOV  A, #155
        B0MOV  TC0R, A;                   //每隔125*2 =250us中断一次
        B0MOV  TC0C, A;                  
        B0BSET  FALOAD0;                  //使能 TC0 自动装载
        B0BCLR	FTC0OUT;                  //允许P5.4口作PWM输出
	B0BCLR	FPWM0OUT;                //允许PWM/BUZZER功能  
   
        B0BTS1    buzzerEnableFlag
        JMP       BUZZER_OFF_DEAL
            
        INCMS     buzzerCntL
        JMP       banDaYu3000
        INCMS     buzzerCntH
banDaYu3000:   ;1000 = 0x3E8
        MOV       A, #03H
        CMPRS     A, buzzerCntH
        JMP       BUZZER_BUDEN   ;跳转到buzzerCnt < 1000
        MOV       A, #0E8H       ;高字节相等再判断低字节
        CMPRS     A, buzzerCntL      
        JMP       BUZZER_BUDEN   ;高字节相等低字节不相等
        B0BCLR    buzzerEnableFlag
        CLR       buzzerCntL
        CLR       buzzerCntH
        B0BCLR    BUZZER_PIN
        JMP       TC0_int_end

BUZZER_BUDEN:
        B0BTS1    buzzerFlag
	JMP       buzzerIs0
        B0BCLR    buzzerFlag
        B0BCLR    BUZZER_PIN
        JMP       TC0_int_end
buzzerIs0:
        B0BSET    buzzerFlag
	B0BSET	  BUZZER_PIN     
        JMP       TC0_int_end

BUZZER_OFF_DEAL:
        B0BCLR    BUZZER_PIN
        JMP       TC0_int_end
TC0_int_end:
        B0BSET   FTC0IEN;                  ;//允许中断Enable TC0 Interrput
        B0BSET   FTC0ENB;                 ; // 定时器开启
        ;JMP   Exit_int	
Exit_int: ;退出中断

      POP
      RETI
      ENDP






				    

