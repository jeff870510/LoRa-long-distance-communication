#include <SPI.h>
#include <RH_RF95.h>

int PIRSensor = 3;//設定紅外線感應針腳
int Button = 4;//設定緊急按鈕針腳
int homenode_num = 2;//設定住戶編號
int data_len;//設定資料長度
int activity;//紅外線感應器讀取到的數值
int emergency = 3;

RH_RF95 rf95;

void setup() {
  pinMode(PIRSensor,INPUT);//設定紅外線感應器腳位讀入模式
  pinMode(Button,INPUT);//設定緊急按鈕腳位讀入模式
  Serial.begin(9600);//設定初始鮑率
  Serial.println("LoRa Sender");//印出Lora Sender
  Serial.println(F("PIRSensor initial OK"));//確認紅外線感應器初始化設定成功
  if(!rf95.init())//初始化LoRa模組
    Serial.println("LoRa init failed");//若模組初始化失敗則報錯
  }

void loop() {
  if(digitalRead(Button) == LOW){
     String data = String(homenode_num)+" "+String(emergency);
     Serial.print("Sending message :");
     Serial.print(data);
     data_len = data.length()+1;
     char d[data_len];
     data.toCharArray(d, data_len); //String to char array
     Serial.println("Sending to rf95_server");
     rf95.send(d, sizeof(d));
     rf95.waitPacketSent();
     delay(100);
     rf95.send(d, sizeof(d));
     rf95.waitPacketSent();
     delay(100);
     rf95.send(d, sizeof(d));
     rf95.waitPacketSent();
     delay(100);
  }else {
     activity = digitalRead(PIRSensor);//讀取紅外線感應器數值
     Serial.print("Homenode_num:");
     Serial.println(homenode_num);
     Serial.print("Activity:");
     Serial.println(activity);
     String data = String(homenode_num)+" "+String(activity);
     Serial.print("Sending message :");
     Serial.print(data);
     data_len = data.length()+1;
     char d[data_len];
     data.toCharArray(d, data_len); //String to char array
     Serial.println("Sending to rf95_server");
     rf95.send(d, sizeof(d));
     rf95.waitPacketSent();
  }
  
  delay(5000);   // 每5秒鐘送一次資料
}
