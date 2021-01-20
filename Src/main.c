#include "main.h"
#include <xc.h>
#include <stdbool.h>

void init(void);

void main(void) {
    uint8_t com_flg = 0;
    bool b1_flag = false;
    bool b2_flag = false;
    bool b3_flag = false;
    bool b4_flag = false;

    init();

    while(true){

        if(I2C_ReceiveCheck()){
            if (com_flg == 0) com_flg = 1;
            CLRWDT();
        }
        else if (com_flg == 0){
            CLRWDT();
        }

        if(B1_S_1 == 0 && !b1_flag){
            B1_LED = 1;
            B1_OUT = 1;
            b1_flag = true;
        }else if(B1_S_2 == 1 && b1_flag){
            B1_LED = 0;
            B1_OUT = 0;
            B1_LED = 0;
            B1_OUT = 0;
            b1_flag = false;
        }
        if(B2_S_1 == 0 && !b2_flag){
            B2_LED = 1;
            B2_OUT = 1;
            b2_flag = true;
        }else if(B2_S_2 == 1 && b2_flag){
            B2_LED = 0;
            B2_OUT = 0;
            B2_LED = 0;
            B2_OUT = 0;
            b2_flag = false;
        }
        if(B3_S_1 == 0 && !b3_flag){
            B3_LED = 1;
            B3_OUT = 1;
            b3_flag = true;
        }else if(B3_S_2 == 1 && b3_flag){
            B3_LED = 0;
            B3_OUT = 0;
            B3_LED = 0;
            B3_OUT = 0;
            b3_flag = false;
        }
        if(B4_S_1 == 0 && !b4_flag){
            B4_LED = 1;
            B4_OUT = 1;
            b4_flag = true;
        }else if(B4_S_2 == 1 && b4_flag){
            B4_LED = 0;
            B4_OUT = 0;
            B4_LED = 0;
            B4_OUT = 0;
            b4_flag = false;
        }
    }
}

void init(void){
    uint8_t addr = 0x10;

    // Set oscilation
    OSCCON = 0xF0; //PLL　Enable

    // Set pin mode
    ANSELA = 0x00;
    ANSELB = 0x00;
  
    TRISA = 0xFF;
    TRISB = 0x00;
    WPUB = 0x00;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;

    B1_LED = 0;
    B1_OUT = 0;
    B2_LED = 0;
    B2_OUT = 0;
    B3_LED = 0;
    B3_OUT = 0;
    B4_LED = 0;
    B4_OUT = 0;

    // Set watch dog
    WDTCON = 0x13;

    I2C_init(addr);//アドレス
}

void interrupt  HAND(void){
    Slave_Interrupt();
}
