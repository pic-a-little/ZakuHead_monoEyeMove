/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC12F1840
        Driver Version    :  2.00
*/

/* 
 * Author: 　Bonokaba
 * Comments: Exceed model ZAKU HEAD　モノアイ動作・点灯用コード
 * Revision history: v1.0.0
 */

#include "mcc_generated_files/mcc.h"
#include "servoControl.h"
#include "monoEyeLED.h"
#include <stdlib.h>        /* For rand() function*/
#include "common.h"

#define _ (1)

/*
                         Main application
 */


void main(void)
{
    short int i;
    unsigned short tmp;
    unsigned short smvTimes,j;
    unsigned short rndServoUS;

    // initialize the device
    SYSTEM_Initialize();

    randSeed = eeprom_read(eepAddrRandSeed)+2;
    srand((unsigned int)randSeed);
    eeprom_write(eepAddrRandSeed, randSeed);    
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

     // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();    
    
    //初期位置移動
    initLED(&monoEye1);
    initServo(&servo1);
    __delay_ms(5000);
    

    for (;_;) {
        if (moveCount > 0) {
            moveCount--;
            
            setLEDCurrentMode(&monoEye1, ledModeUp, 20);
            setLEDCurrentMode(&monoEye1, ledModeHoldON, 0);

            smvTimes = rand() % 3 + 1; // サーボの動作回数を決定する
            rndServoUS = 100 + rand() % 400; //サーボの動作スピードを決定する
            for (j = 0; j < smvTimes; j++) {
                tmp = (servoRightMax - (unsigned short) (rand() / 29)); //RAND_MAX＝2767なので　RightMax-LeftMaxに収めるために29で徐算。
                moveServo(tmp, rndServoUS);
                                tmp = rand() % 10;
                for (i = 0; i < tmp; i++) {
                    __delay_ms(300);
                }
            }

            setLEDCurrentMode(&monoEye1, ledModeDown, 10);
            
            setLEDCurrentMode(&monoEye1, ledModeHoldOFF, 0);
            __delay_ms(900);
            tmp = rand() % 8;
            for (i = 0; i < tmp; i++) {
                __delay_ms(300);
            }
            
        }
    }
}
/**
 End of File
*/