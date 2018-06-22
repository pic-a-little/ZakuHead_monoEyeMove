# ZAKU HEAD のモノアイを光らせ，サーボで動かすためのコード  
![ザクヘッド](https://github.com/pic-a-little/ZakuHead_monoEyeMove/blob/master/images/zakuHead.jpg "お写真")  [![作り方動画](https://img.youtube.com/vi/wLAY23P32GI/0.jpg)](https://www.youtube.com/watch?v=wLAY23P32GI)

工作の詳細は上記動画と下記のブログにてご参照ください。  
https://picalittle.blog.fc2.com/blog-entry-63.html  

EXCEED MODEL ZAKU HEAD にサーボとLEDを仕込んで，モノアイを動かします。  
PIC12F1840用です(コンフィグ変更でPIC12F1822でも可のハズ)  

## 利用方法

projectPackageディレクトリ内のzipファイルをMPLAB_Xに展開する
  
## 動作概要  
  
電源ON後および指定時間（15分）おきに規定回数モノアイを動作する。  
  
モノアイの動作は モノアイ光る＞サーボ稼働＞モノアイ消灯　で１セット  
サーボ稼働回数，稼働速度，稼働間隔はrand利用である程度ランダムに変化。  
  
また，リードスイッチに磁石を近づけた時にも1セットだけモノアイを動作する。  
   
## PIN配置  
下記だったんじゃないかと  
  RA1 = LED制御 :   RA1 - 470ohm? - LED  - GND  
  RA2 = サーボ制御 :   RA2 - Servo(Yellow)  
  RA4 = リードスイッチ入力 :   VCC -  SW - RA4 - 10K ohm - GND  

![回路図](https://github.com/pic-a-little/ZakuHead_monoEyeMove/blob/master/images/circuit.png "回路図")　 
 　
## 内部動作/コード概略  
  
全体的に割り込みで動作する作り  
### 割り込み概略  
 TMR0_ISRが1msごとに発生。　＞　LEDをDutyにしたがって点滅  
 TMR1 と ECCPでサーボを制御。 (TMR1_ISRが20msごとに制御パルスを立ち上げ，ECCPの割り込みで制御パルスを下げる)  
 TMR2_CallBackで15分おきに残動作回数moveCountをUp  
 RA4割り込み発生（IOCAF4_ISR）でも残動作回数moveCountをUp  
  
 moveCountが１以上ならmain()の中のfor泣きループでモノアイ稼働を実施  
  
### その他のコード  
LED点灯制御とサーボ挙動制御のコードはそれぞれmonoEyeLED.cとservoControl.cに記載  
srandは起動ごとになんとなく変更してEEPROMに保存  
