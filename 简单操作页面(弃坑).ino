/**
 *                             _ooOoo_
 *                            o8888888o
 *                            88" . "88
 *                            (| -_- |)
 *                            O\  =  /O
 *                         ____/`---'\____
 *                       .'  \\|     |//  `.
 *                      /  \\|||  :  |||//  \
 *                     /  _||||| -:- |||||-  \
 *                     |   | \\\  -  /// |   |
 *                     | \_|  ''\---/''  |   |
 *                     \  .-\__  `-`  ___/-. /
 *                   ___`. .'  /--.--\  `. . __
 *                ."" '<  `.___\_<|>_/___.'  >'"".
 *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *               \  \ `-.   \_ __\ /__ _/   .-` /  /
 *          ======`-.____`-.___\_____/___.-`____.-'======
 *                             `=---='
 *          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *                     佛祖保佑        永无BUG
 *            佛曰:
 *                   写字楼里写字间，写字间里程序员；
 *                   程序人员写程序，又拿程序换酒钱。
 *                   酒醒只在网上坐，酒醉还来网下眠；
 *                   酒醉酒醒日复日，网上网下年复年。
 *                   但愿老死电脑间，不愿鞠躬老板前；
 *                   奔驰宝马贵者趣，公交自行程序员。
 *                   别人笑我忒疯癫，我笑自己命太贱；
 *                   不见满街漂亮妹，哪个归得程序员？
*/
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
#define ytime 50
/*------------主菜单列表,0数组存储当前所选-------------------*/
char main_menu[6][6]={"GAME","GAME","MUSIC","BOOK","PHONE","TEST"};

void setup(){
  Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
Wire.begin();
pinMode(2,INPUT);//左
pinMode(3,INPUT);//上
pinMode(4,INPUT);//右
pinMode(5,INPUT);//下
pinMode(6,INPUT);//主页
pinMode(7,INPUT);//菜单
pinMode(8,INPUT);//返回
pinMode(9,INPUT);//确定
/*-----模拟一个载入页面，等程序完善的时候这个时间的间隔用来加载数据-----*/
 display.clearDisplay();
 display.setTextColor(WHITE);
 display.setTextSize(2);
 display.setCursor(20,10);
 display.println("Welcome!");
 display.setTextSize(1);
 display.setCursor(50,35);
 display.println("By:Sch_ray");
 display.drawRect(14,54,100,7,WHITE);
 display.display();
 start_page(5);
 delay(500);
 start_page(20);
 delay(500);
 start_page(50);
 delay(500);
 start_page(90);
 delay(200);
 start_page(100);
choice_page(main_menu);//显示菜单
}


/*------------------------------主循环----------------------------*/
/*-------------------------------桌面----------------------------*/
void loop(){
  int key=keyscan();
  if((key == 3) || (key == 5)){
    Serial.println("执行函数");
    rotate(key,main_menu);
    choice_page(main_menu);
  }
 }

/*------------------------------进度条---------------------------*/
void start_page(uint8_t percent){
  for (int i = 0; i < percent; i++)
    display.fillCircle(i+14,57,4,WHITE);//画圆，圆心坐标，半径
  display.display();
}

/*------------------------------菜单显示----------------------------*/
void choice_page(char list[][6]){
  uint8_t now=1;//默认选中第一个
  for(int i=1;i<=sizeof(list/6);i++){//循环一维
    if((list[0][0] == list[i][i*6]) && (list[0][1] == list[i][i*6+1]) && (list[0][2] == list[i][i*6+2]) && (list[0][3] == list[i][i*6+3])){
      now=i;
      break;
    }
  }
    Serial.print("菜单显示时所选是:");
    Serial.println(now);
  if(now <= 5){//如果一个页面就可以显示
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    for(int i=1; i<6; i++){//12345
        if(now == i){
          display.setCursor(0,i*10-10);//如果是当前所选就顶行显示
          display.print(list[i]);
        }
        else{
          display.setCursor(10,i*10-10);//否则缩进显示
          display.print(list[i]);
        }
    }
    display.setCursor(0,53);//显示下面的固定菜单选项
    display.println("BACK------------ENTEN");
    display.display();
  }
  else{//如果一个页面难以显示新加载一个页面，目前只能做到这样，如果需要滑动显示需要稍微复杂一点，还需要判断特意申请一个显示数组
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    for(int i=6; i<11; i++){//678910
        if(now == i){
          display.setCursor(0,i*10-10);//如果是当前所选就顶行显示
          display.println(list[i]);
        }
        else{
          display.setCursor(10,i*10-10);//否则缩进显示
          display.println(list[i]);
        }
    }
    display.setCursor(0,53);//显示下面的固定菜单选项
    display.println("BACK------------ENTEN");
    display.display();
  }
}
/*------------------------------菜单所选元素调整---------------------------*/
int rotate(uint8_t key,char list[][6]){
  uint8_t now=1;//这个变量是指当前菜单里所选的元素是第几个
  for(int i=1;i<=sizeof(list/6);i++){//循环一维
    if((list[0][0] == list[i][i*6]) && (list[0][1] == list[i][i*6+1]) && (list[0][2] == list[i][i*6+2]) && (list[0][3] == list[i][i*6+3])){
      now=i;
      break;
    }
  }
    Serial.print("调整之前菜单所选是:");
    Serial.println(now);
  if(key == 3){//按了上
    if(now == 1)
      return 1;
    for(int i=0;i<6;i++){//完整复制
        list[0][i]=list[now-1][i];
      }
      Serial.println("向上");
  }
  if(key == 5){//按了下
    if(now == (sizeof(list))/6-1)//如果到顶了就直接返回
      return 1;
    for(int i=0;i<6;i++){
        list[0][i]=list[now+1][i];
      }
      Serial.println("向下");
  }
  for(int i=1;i<=sizeof(list);i++){
    if(list[0] == list[i]){
      now=i;
      break;
    }
  }
    Serial.print("调整之后菜单所选是:");
    Serial.println(now);
}
/*------------------------------按键检测----------------------------*/
int keyscan(){
  if(digitalRead(2)){
    delay(ytime);
    if(digitalRead(2)){
      while(digitalRead(2)){
      }
      return 2;
  }
}
  if(digitalRead(3)){
    delay(ytime);
    if(digitalRead(3)){
      while(digitalRead(3)){
      }
      return 3;
  }
}
  if(digitalRead(4)){
    delay(ytime);
    if(digitalRead(4)){
      while(digitalRead(4)){
      }
      return 4;
    }
  }
  if(digitalRead(5)){
    delay(ytime);
    if(digitalRead(5)){
      while(digitalRead(5)){
      }
      return 5;
    }
  }
  if(digitalRead(6)){
    delay(ytime);
    if(digitalRead(6)){
      while(digitalRead(6)){
      }
      return 6;
  }
}
  if(digitalRead(7)){
    delay(ytime);
    if(digitalRead(7)){
      while(digitalRead(7)){
      }
      return 7;
  }
}
  if(digitalRead(8)){
    delay(ytime);
    if(digitalRead(8)){
      while(digitalRead(8)){
      }
      return 8;
    }
  }
  if(digitalRead(9)){
    delay(ytime);
    if(digitalRead(9)){
      while(digitalRead(9)){
      }
      return 9;
    }
  }
  return 0;
 }
// display.drawPixel(10, 10, WHITE);点
// display.drawLine(起点X, 起点Y, 终点X, 终点Y, WHITE);线条
// display.drawRect(x, y, 长度, 高度, WHITE);矩形
// display.drawCircle(X,Y，半径, WHITE);圆形
// display.fillCircle(x, y, 10, WHITE);实心圆
// display.drawRoundRect(x, y, x, y, 圆角的长度, WHITE);圆角矩形
// display.drawTriangle(三个点的坐标)三角形
// display.drawBitmap(坐标，坐标, 数组, 数组宽, 数组高, BLACK);
// 文字：
// display.setTextSize(1);大小
// display.setTextColor(WHITE);颜色
// display.setCursor(0,0);光标，这个光标可以自动检测到字体大小
// display.println("Hello, world!");

// display.display()
// display.clearDisplay()

//void eeprom_write(byte i2cadd,byte eepaddh,byte eepaddl,char* data){
//  Wire.beginTransmission(i2cadd);
//  Wire.write(eepaddh);
//  Wire.write(eepaddl);
//  for(int a=0;a<32;a++){
//     Wire.write(data[a]);
//  }
//  Wire.endTransmission();
//}
//
//void eeprom_read(byte i2cadd,byte eepaddh,byte eepaddl,char* data){
//  Wire.beginTransmission(i2cadd);
//  Wire.write(eepaddh);
//  Wire.write(eepaddl);
//  Wire.endTransmission();
//  Wire.requestFrom(i2cadd,32);//告知要取数据
//  for(int a=0;a<32;a++){
//    if (Wire.available()) data[a] = Wire.read();
//  }
//  }
