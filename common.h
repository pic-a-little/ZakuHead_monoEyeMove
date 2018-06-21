#ifndef XC_HEADER_USER_COMMON_H
#define	XC_HEADER_USER_COMMON_H

/* 
 * Author: 　Bonokaba
 * Comments: Exceed model ZAKU HEAD　モノアイ動作・点灯用コード
 * Revision history: v1.0.0
 */

#include <xc.h> // include processor files - each processor file is guarded.  

#define eepAddrRandSeed             (0)
unsigned char randSeed;//sland用(メインで回してmodeSet()で設定)

/*
 * 覚書
 * 
 * 機動戦士ガンダム　EXCEED MODEL ZAKU HEAD の
 * モノアイを光らせ，サーボで動かすためのコード
 *
 * 電源ON後および指定時間（15分）おきに規定回数モノアイを動作する。
 * 
 * モノアイの動作は モノアイ光る＞サーボ稼働＞モノアイ消灯　で１セット
 * サーボ稼働回数，稼働速度，稼働間隔はrand利用である程度ランダムに変化。
 * 
 * また，リードスイッチに磁石を近づけた時にも1回モノアイ動作する。
 *  
 * PIN配置は下記だったんじゃないかと
 *   RA1 = LED    RA1 - LED - 560ohm? - GND
 *   RA2 = サーボ信号線   RA2 - Servo(Yellow)
 *   RA4 = リードスイッチ VCC -  RA4 - SW - 10Kohm - GND だったはず。
 * 
 * 内部動作概略
 * 
 * 全体的に割り込みで動作する
 * 割り込み概略
 *  TMR0_ISRが1msごとに発生。　＞　LEDをDutyにしたがって点滅
 *  TMR1 と ECCPでサーボを制御。 (TMR1_ISRが20msごとに制御パルスを立ち上げ，ECCPの割り込みで制御パルスを下げる)
 *  TMR2_CallBackで15分おきに残動作回数moveCountをUp
 *  RA4割り込み発生（IOCAF4_ISR）でも残動作回数moveCountをUp
 * 
 * その他のコード
 *  moveCountが１以上ならmain()の中のfor泣きでモノアイ稼働を実施
 * 
 * LED点灯制御とサーボ挙動制御のコードはそれぞれmonoEyeLED.cとservoControl.cに記載。
 * 
 * srandは起動ごとになんとなく変更してEEPROMに保存
 * 
 */



#endif	/* XC_HEADER_USER_COMMON_H */

