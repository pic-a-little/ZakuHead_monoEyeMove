/*
 * File:   servoControl.c
 * Author: bonokaba
 * Comments: Exceed model ZAKU HEAD　モノアイ動作・点灯用コード
 * Revision history: v1.0.0
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "servoControl.h"

void initServo(struct servoCondition *initServo){
    initServo->currentPotion = servoCenter;
    initServo->targetPotion = servoCenter;
    servoPower = servoOFF;
}

void moveServo(unsigned short int target, short int usDulation){
    TMR1_StartTimer();__delay_ms(80);
    short int i;
    __nop();
    if(target < servoLeftMax){ target = servoLeftMax;}
    else if(target > servoRightMax){ target = servoRightMax;}
    servo1.targetPotion = target;
    
    servoPower = servoON;
  //  __delay_ms(1000);
    while (servo1.currentPotion != servo1.targetPotion){
        if(servo1.currentPotion < servo1.targetPotion){
            servo1.currentPotion++;
        }else{
            servo1.currentPotion--;
        }
        for(i=0;i<usDulation;i++){
            __delay_us(1);
        }
    }
    TMR1_StopTimer();
    servoPower = servoOFF;
    
}
