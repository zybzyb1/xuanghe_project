#ifndef      _GLOBAL_H
#define      _GLOBAL_H



#define   UART_DISABLE //  ENABLE  //    //������ʹ

#define   ADC_DISABLE //ENABLE  //   ʹ��
 

#define   SI_ON()   P17 = 1   //�����ɿع�
#define   SI_OFF()  P17 = 0   //�ضϿɿع�

#define   DIG1_OFF     P15=0    
#define   DIG2_OFF     P16=0 
#define   DIG1_ON      P15=1
#define   DIG2_ON      P16=1 

#define   A_OOUT(var)   P34=var
#define   B_OOUT(var)   P35=var
#define   C_OOUT(var)   P37=var
#define   D_OOUT(var)   P10=var
#define   E_OOUT(var)   P12=var
#define   F_OOUT(var)   P13=var
#define   G_OOUT(var)   P14=var
#endif

