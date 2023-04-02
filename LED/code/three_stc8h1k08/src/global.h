#ifndef      _GLOBAL_H
#define      _GLOBAL_H

#define   UART_DISABLE //ENABLE  //      //串口能使

#define   SI_ON()   P17 = 1   //开启可控硅
#define   SI_OFF()  P17 = 0   //关断可控硅

#define   DIG1_OFF     P54=0    
#define   DIG2_OFF     P10=0 
#define   DIG1_ON      P54=1
#define   DIG2_ON      P10=1 

#define   A_OOUT(var)   P35=var
#define   B_OOUT(var)   P16=var
#define   C_OOUT(var)   P14=var
#define   D_OOUT(var)   P12=var
#define   E_OOUT(var)   P13=var
#define   F_OOUT(var)   P37=var
#define   G_OOUT(var)   P34=var
#endif

