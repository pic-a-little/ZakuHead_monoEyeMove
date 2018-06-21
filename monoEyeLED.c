/*
 * File:   monoEyeLED.c
 * Author: bonokaba
 * Comments: Exceed model ZAKU HEAD　モノアイ動作・点灯用コード
 * Revision history: v1.0.0
 */


#include <xc.h>
#include "monoEyeLED.h"
#include "mcc_generated_files/mcc.h"

void initLED(struct ledOutputCondition *outConditionS){
    outConditionS->dutyBit = 0x0000;
    outConditionS->dutyStatus = OUTPUT_CONDITION_DUTY_MAX;
//    outConditionS->dulation = 1;
//    outConditionS->currentPotion = 0;
    outConditionS->currentMode = ledModeHoldOFF;
}

void setLEDCurrentMode(struct ledOutputCondition *outConditionS, unsigned char nextMode, short int msDulation){
    nextMode = nextMode & 0x03; //バカ避け
    // 0=ledModeUP, 1=ledModeHoldON, 2=ledModeDown, 3=ledModeHoldOFF
    outConditionS->currentMode = nextMode;
    outConditionS->dutyStatus = 0;  //Dutyの設定をを初期化
    ledStateTransition(outConditionS,msDulation);
}

void changeLEDCurrentMode(struct ledOutputCondition *outConditionS, short int msDulation){
    outConditionS->currentMode++;
    outConditionS->currentMode = outConditionS->currentMode & 0x03; // 0=ledModeUP, 1=ledModeHoldON, 2=ledModeDown, 3=ledModeHoldOFF で回す
    outConditionS->dutyStatus = 0;  //Dutyの設定をを初期化
    ledStateTransition(outConditionS,msDulation);
}

void ledStateTransition(struct ledOutputCondition *outConditionS, short int msDulation){
    short int i;
    while(outConditionS->dutyStatus<OUTPUT_CONDITION_DUTY_MAX){
        for(i=0;i<msDulation;i++){
            __delay_ms(1);
        }
        setLEDDuty(outConditionS);// Dutyが最大になっていなければ，Duty比を変更する         
    }
 }

void setLEDDuty(struct ledOutputCondition *outConditionS){//現在のモードにしたがってDuty比を１つ増減させる
    switch(outConditionS->currentMode){
        case ledModeUp:
        {
            outConditionS->dutyBit = outConditionS->dutyBit << 1;
            if((outConditionS->dutyBit & 0xF000) != 0xF000){
                outConditionS->dutyBit++;   //dutyBitを1桁上げて末尾に1を入れる( Dutyが上がる))
                outConditionS->dutyBit = outConditionS->dutyBit << 1;
                outConditionS->dutyBit++;
                
            }else if((outConditionS->dutyBit) != 0xF000){
                outConditionS->dutyBit = outConditionS->dutyBit & (unsigned)0xfffe;
            }else{
                  outConditionS->dutyStatus = OUTPUT_CONDITION_DUTY_MAX;
                   __delay_ms(300);
            }
        }break;
        case ledModeHoldON:
        {
            outConditionS->dutyStatus++;
            outConditionS->dutyBit = (unsigned)0x1111;//出力下げて，ぼんやり点灯
        }break;
        case ledModeDown:
        {
            outConditionS->dutyStatus++;
            outConditionS->dutyBit = outConditionS->dutyBit << 1;
            outConditionS->dutyBit = outConditionS->dutyBit & (unsigned)0xfffe; //1bitずらし，末尾に0を追加して少しずつ暗くする
        }break;
        case ledModeHoldOFF:
        {
            outConditionS->dutyStatus++;
            outConditionS->dutyBit = 0x00;//OFFなら全消灯
        }break;
    }
}

