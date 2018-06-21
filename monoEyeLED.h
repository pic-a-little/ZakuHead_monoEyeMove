#ifndef XC_HEADER_MONOEYELED_H
#define	XC_HEADER_MONOEYELED_H

/*
 * File:   monoEyeLED.h
 * Author: bonokaba
 * Comments: Exceed model ZAKU HEAD　モノアイ動作・点灯用コード
 * Revision history: v1.0.0
 */

#include <xc.h> // include processor files - each processor file is guarded.  

#define monoEyeLED RA1
#define monoEyeON (1)
#define monoEyeOFF (0)

//動作中のモード
#define ledModeUp       (0)
#define ledModeHoldON   (1)
#define ledModeDown     (2)
#define ledModeHoldOFF  (3)


#define OUTPUT_CONDITION_DUTY_MAX (15)
#define DUTY_RAND_BASE 0x3fff;

struct ledOutputCondition{
    unsigned short int       dutyBit;    //0b00001111形式でDutyをセット
    unsigned char   dutyStatus; //0~15 duty変化中は0~14で，基本増加
    unsigned char   currentMode; // 0=ledModeUP, 1=ledModeHoldON, 2=ledModeDown, 3=ledModeHoldOFF
};

struct ledOutputCondition monoEye1;





/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/
void initLED(struct ledOutputCondition *outConditionS);//初期化用。

void setLEDCurrentMode(struct ledOutputCondition *outConditionS, unsigned char nextMode, short int msDulation); //指定されたモードに切り替える
void changeLEDCurrentMode(struct ledOutputCondition *outConditionS, short int msDulation);  //呼ばれるたびに 点灯＞点灯中＞消灯＞消灯中＞点灯の順でモードを切り替える


//↓内部関数
void ledStateTransition(struct ledOutputCondition *outConditionS, short int msDulation);    // msDulationの間隔を開けて，setLEDDutyを実行し，光り方を徐々に変える
void setLEDDuty(struct ledOutputCondition *outConditionS);  //現在のモードにしたがってDuty比を１つ増減させる


#endif	/* XC_HEADER_MONOEYELED_H */

