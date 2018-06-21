
#ifndef XC_HEADER_SERVO_H
#define	XC_HEADER_SERVO_H

/*
 * File:   servoControl.h
 * Author: bonokaba
 * Comments: Exceed model ZAKU HEAD　モノアイ動作・点灯用コード
 * Revision history: v1.0.0
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include "common.h"


#define servoON (1)
#define servoOFF (0)

#define MOVECOUNT (5) //連続動作回数の再設定値

#define TMR1_OFFSET (25536)       //制御パルスの最小時間

#define servoLeftMax (2420) + TMR1_OFFSET //サーボの左舷最大(モノアイカバーに当たらないギリギリ)
#define servoCenter  (3000) + TMR1_OFFSET //サーボのセンター
#define servoRightMax (3580) + TMR1_OFFSET    //サーボの右舷最大(モノアイカバーに当たらないギリギリ)

short int moveCount = MOVECOUNT;
unsigned short servoPotion = servoCenter; //servoPotion is set by Timer1 interruption as duty rate.
short int servoPower = 0;

struct servoCondition{
    unsigned short int       currentPotion;
    unsigned short int       targetPotion;
};

struct servoCondition servo1;

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

void initServo(struct servoCondition *initServo);//初期化用。

void moveServo(unsigned short int target, short int usDulation);    //現在位置からtarget位置まで，usDulationマイクロ秒おきに動作



#endif	/* XC_HEADER_SERVO_H */

