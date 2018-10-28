#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define bitsp 115200
//9600 | 115200
String comdata="";
void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(bitsp);
  }

void loop(){
  while (Serial.available() > 0)  
    {
        comdata += char(Serial.read());
        delay(2);
    }
    
   if (comdata.length() > 0)
    {
       display_fun(comdata);
       Serial.println(comdata);
       comdata = "";
  }
}

void display_fun(String st){
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setTextSize(1);
   display.setCursor(0,0);
   display.println(st);
   display.display();
  }

//void function(int yanse){
//    for(int i=0;i<16;i++){
//        strip.setPixelColor(i,Wheel(yanse));//单次显示
//      }
//      strip.show();
//  }
//
//  uint32_t Wheel(byte WheelPos) {//中文直译轮子？传入数据代表一个颜色，也就是化繁为简为传入数字返回一个完整的RGB值
//  WheelPos = 255 - WheelPos;
//  if(WheelPos < 85) {
//    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  }
//  if(WheelPos < 170) {
//    WheelPos -= 85;
//    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//  WheelPos -= 170;
//  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//}
