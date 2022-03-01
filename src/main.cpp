#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
//#include "LittleFS.h"
//#include <ESP8266FtpServer.h> 

#define RED 15
#define GREEN 12
#define BLUE 13 
#define LDR A0 //foto resistor
#define BTN 4 //default high level

//const char *ssid = "Link";
//const char *pass = "gptsamara63";
const char *ssid = "MyESP";
const char *psk = "12345678";
IPAddress local_ip(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);
ESP8266WebServer HTTP(80);
//FtpServer ftpSrv;
bool handleFileRead(String path);
String getContentType(String filename);
//Сейчас 25*С...26*С влажность 50% давление 757 мм. рт. ст. 
const char* const str[] PROGMEM = {"Сейчас ", "*C", "...", " влажность ", "%", " давление "," мм. рт. ст."};


String utf8rus(String source) // Перекодировка для поддержки русского языка в скетче
{
  int i, k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;
  while (i < k) {
    n = source[i]; i++;
    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
            n = source[i]; i++;
            if (n == 0x81) {
              n = 0xA8;
              break;
            }
            if (n >= 0x90 && n <= 0xBF) n = n + 0x2F;
            break;
          }
        case 0xD1: {
            n = source[i]; i++;
            if (n == 0x91) {
              n = 0xB7;
              break;
            }
            if (n >= 0x80 && n <= 0x8F) n = n + 0x6F;
            break;
          }
      }
    }
    m[0] = n; target = target + String(m);
  }
  return target;
}



void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(A0, INPUT); 
  pinMode(BTN, INPUT);
  Serial.begin(115200);
  /*WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  delay(100);
  WiFi.softAP(ssid, psk);
  //WiFi.softAPConfig (local_ip, gateway, subnet);
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  delay(500);
  Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum());*/
  int t1 = 25;
  int t2 = 26;
  int h = 50;
  int p = 757;
  char strBuf[90];
  char num[3];
  strcpy_P(strBuf,  (char*)pgm_read_dword(&(str[0])));
  itoa(t1, num, 10);
  strcat(strBuf,  num);
  strcat_P(strBuf,  (char*)pgm_read_dword(&(str[1]))); 
  strcat_P(strBuf,  (char*)pgm_read_dword(&(str[2])));
  itoa(t2, num, 10);
  strcat(strBuf,  num);
  strcat_P(strBuf,  (char*)pgm_read_dword(&(str[1])));
  strcat_P(strBuf,  (char*)pgm_read_dword(&(str[3])));
  itoa(h, num, 10);
  strcat(strBuf,  num);
  strcat_P(strBuf,  (char*)pgm_read_dword(&(str[4])));
  strcat_P(strBuf,  (char*)pgm_read_dword(&(str[5])));
  itoa(p, num, 10);
  strcat(strBuf,  num);
  strcat_P(strBuf,  (char*)pgm_read_dword(&(str[6])));
  Serial.println(strBuf);
  Serial.println(F("Привет end!"));
}

void loop() {
  //HTTP.handleClient();
/*
  int ldr = analogRead(LDR);
  bool btn = digitalRead(BTN);
  //Serial.println(btn);
  int lvl = map(ldr, 60, 900, 0, 255);
  digitalWrite(RED, !btn);
  delay(1000);
  //analogWrite(RED, 255);
  //delay(1000);
  //digitalWrite(GREEN, HIGH);
  analogWrite(GREEN, lvl);
  delay(1000);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  //delay(1000);
  for (int i = 0; i < 255; i++){
    analogWrite(BLUE, i);
    delay(10);
  }
  
  //delay(1000);
  digitalWrite(BLUE, LOW);
  //delay(1000);*/
}
