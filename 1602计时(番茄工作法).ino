/*
LiquidCrystal()　　　　 //构造函数
begin()　               //指定显示屏尺寸
clear()　　             //清屏并将光标置于左上角
home()　                //将光标置于左上角（不清屏）
setCursor()　　         //将光标置于指定位置
write()　　             //（在光标处）显示一个字符
print()　             　//显示字符串
cursor()　            　//显示光标（就是一个下划线）
noCursor()　　          //不显示光标
blink()　             　//光标闪烁（和8,9一起使用时不保证效果）
noBlink()　　           //光标不闪烁
noDisplay()　　         //关闭显示，但不会丢失内容（谁把灯关了？）
display()　　           //（使用noDisplay()后）恢复显示 
scrollDisplayLeft()　   //将显示的内容向左滚动一格
scrollDisplayRight() 　 //将显示的内容向右滚动一格
autoscroll()　　        //打开自动滚动（具体解释往下拉）
noAutoscroll()　       //关闭自动滚动
leftToRight()　　      //从左向右显示内容（默认）
rightToLeft()　　      //从右向左显示内容
createChar()　　       //大奥义·字符创造之术（往下拉）
5 byte smiley[8] = {    //1表示亮，0表示不亮，此例显示一个笑脸
 6     B00000,
 7     B10001,
 8     B00000,
 9     B00000,
10     B10001,
11     B01110,
12     B00000,
13 };
16     int x=1;    //x可以为0~7的任何数字
17     lcd.createChar(x , smiley);    //将x号字符设置为smiley数组表示的样子
18     lcd.begin(16, 2);  
19     lcd.write（x）;
*/
//#include <SPI.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int loag;
void setup(){
//  Serial.begin(9600);
  pinMode(8,OUTPUT);
  lcd.begin(16,2);
  lcd.print(" Tomato-Working ");
  loag=0;
  jishu("Work",1500);
  loag++;
  jishu("Rest",300);
  jishu("Work",1500);
  loag++;
  jishu("Rest",300);
  jishu("Work",1500);
  loag++;
  jishu("Rest",300);
  jishu("Work",1500);
  }
void loop(){
    lcd.setCursor(0,1);
    lcd.print("Congratulations!");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("     Effort     ");
    delay(1000);
  }

void jishu(char dis[4],int tim){//一次倒计时
  int loagz=5;
//  Serial.println(dis);
//  Serial.println(loagz);
  for(;tim>=0;tim--){
    digitalWrite(8,(loagz%2 == 0)?LOW:HIGH);
    if(loagz > 0)
      loagz--;
    lcd.setCursor(0,1);
    lcd.print(dis);
    lcd.print(":");
    
    if((tim/60) >= 10)
      lcd.print(tim/60);
      else{
        lcd.print("0");
        lcd.print(tim/60);
        }
        
    lcd.print(":");
    
    if((tim%60) >= 10)
      lcd.print(tim%60);
      else{
        lcd.print("0");
        lcd.print(tim%60);
        }
        
    lcd.setCursor(15-loag,1);
    lcd.print("####");
    delay(1000);
    }
  }
