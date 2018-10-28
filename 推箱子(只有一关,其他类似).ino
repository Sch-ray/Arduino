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
#define ytime 10
uint8_t Wall[]={0xFF,0x00,0xDD,0x00,0x77,0x00,0xDD,0x00};//墙的图案
uint8_t Box[]={0x7E,0xC3,0xFF,0x99,0x81,0x81,0x81,0xFF};//箱子的图案
uint8_t Man[]={0x7E,0xFF,0x81,0x22,0x08,0x18,0x40,0x3C};//角色的图案
uint8_t Sign[]={0x3C,0x42,0xA5,0x91,0x89,0xA5,0x42,0x3C};//标记点的图案
uint8_t Box_after[]={0x3C,0x5A,0x81,0xFF,0x81,0x81,0x81,0xFF};//箱子推上去的图案
uint8_t Walls[29][2]={
48,0,56,0,64,0,72,0,
48,8,72,8,80,8,88,8,
32,16,40,16,48,16,88,16,
32,24,72,24,88,24,
32,32,88,32,
32,40,40,40,48,40,72,40,80,40,88,40,
48,48,72,48,
48,56,56,56,64,56,72,56};
uint8_t Signs[3][2]={56,24,64,24,56,32};
uint8_t Boxs[3][2]={56,24,56,32,64,32};
uint8_t Man_x=64,Man_y=40;

void dis(){
    display.clearDisplay();
    for(uint8_t i=0;i<29;i++){//绘制墙
      display.drawBitmap(Walls[i][0],Walls[i][1],Wall,8,8,1);
    }
    for(uint8_t i=0;i<3;i++){//重叠就绘制箱子打开的图案，不重叠就绘制标记
        if((Boxs[i][0] == Signs[i][0]) && (Boxs[i][1] == Signs[i][1])){
            display.drawBitmap(Boxs[i][0],Boxs[i][1],Box_after,8,8,1);
            Serial.print("绘制一次箱子打开:");
            Serial.println(Boxs[i][0],Boxs[i][1]);
          }
          else{
              display.drawBitmap(Signs[i][0],Signs[i][1],Sign,8,8,1);
            Serial.print("绘制一次标记点:");
            Serial.println(Signs[i][0],Signs[i][1]);
            }
      }
    for(uint8_t i=0;i<3;i++){//不重叠就绘制箱子
        if((Boxs[i][0] != Signs[i][0]) && (Boxs[i][1] != Signs[i][1])){
            display.drawBitmap(Boxs[i][0],Boxs[i][1],Box,8,8,1);
            Serial.print("绘制一次正常箱子:");
            Serial.println(Boxs[i][0],Boxs[i][1]);
          }
      }
    display.drawBitmap(Man_x,Man_y,Man,8,8,1);
    display.display();
  }
int moved(int8_t x,int8_t y){
  if(Contrast(Boxs,3,Man_x+x,Man_y+y)){
      if((Contrast(Walls,29,Man_x+x+x,Man_y+y+y)) || (Contrast(Boxs,3,Man_x+x+x,Man_y+y+y))){
          return 1;
        }
      for(uint8_t i=0;i<3;i++){
          if((Man_x+x == Boxs[i][0]) && (Man_y+y == Boxs[i][1])){
              Boxs[i][0]+=x;
              Boxs[i][1]+=y;
              break;
            }
        }
      Man_x+=x;
      Man_y+=y;
      dis();
      return 0;
    }
    else if(Contrast(Walls,29,Man_x+x,Man_y+y)){
        return 1;
      }
      else{
          Man_x+=x;
          Man_y+=y;
          dis();
          return 0;
        }
  return 1;
}

int Contrast(uint8_t ary[][2],uint8_t n,uint8_t x,uint8_t y){
    for(uint8_t i=0;i<n;i++){
        if((ary[i][0] == x)&&(ary[i][1] == y)){
            return 1;
          }
      }
    return 0;
  }
void setup(){
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(2,INPUT);//INPUT_PULLUP
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  dis();
}
void loop() {
  if(digitalRead(2)){
    delay(ytime);
    if(digitalRead(2)){
      while(digitalRead(2)){
      }
      moved(-8,0);
  }
}
  if(digitalRead(3)){
    delay(ytime);
    if(digitalRead(3)){
      while(digitalRead(3)){
      }
      moved(0,-8);
  }
}
  if(digitalRead(4)){
    delay(ytime);
    if(digitalRead(4)){
      while(digitalRead(4)){
      }
      moved(8,0);
    }
  }
  if(digitalRead(5)){
    delay(ytime);
    if(digitalRead(5)){
      while(digitalRead(5)){
      }
      moved(0,8);
    }
  }
}
