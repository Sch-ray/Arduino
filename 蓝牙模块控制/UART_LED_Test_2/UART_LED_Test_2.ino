byte i=0,j=0,x=0,data[4]={0x12,0x34,0x56,0x78},cmd[4]={0},tim=0;
/*
PB0作为TX通信,支持9600波特率
PB1作为WS2812操作口,目前功能为测试保留
PB2其实只需要一个光立方上面的芯片就可以实现一个I/0控制8个
PB3
PB4
PB5为复位键,因为还需要USB下载,所以需要保留bootload,因此留空
*/
void setup(){
  pinMode(0,INPUT);
  pinMode(1,OUTPUT);
  digitalWrite(1,0);
}

void loop(){
//////////////////////
/////数据捕捉部分//////
/////////////////////
  if(!digitalRead(0)){//数据捕捉部分
    
    delayMicroseconds(145);//跳过起始位
    for(i=0;i<8;i++){
      digitalWrite(1,1);//测试用
      if(digitalRead(0) == 1)
      j=0x80;
      else
      j=0;
      cmd[0]>>=1;
      cmd[0]|=j;
      digitalWrite(1,0);//测试用
      delayMicroseconds(90);
    }
    for(x=1;x<4;x++){//捕捉三次即可,第一次的起始位不太好计算
      tim=0;
      while(digitalRead(0)){//最后一次延时跳到了停止位,等待下降沿
        if(++tim == 100)//如果数据传输完毕,即不再拉低,会一直执行并自加
          break;//超过时间,结束本次while
         }
      if(tim == 100)
        break;
          
      delayMicroseconds(145);//跳过起始位
      for(i=0;i<8;i++){
        digitalWrite(1,1);//测试用
        if(digitalRead(0) == 1)
        j=0x80;
        else
        j=0;
        cmd[x]>>=1;
        cmd[x]|=j;
        digitalWrite(1,0);//测试用
        delayMicroseconds(90);
      }
    }
  }

//////////////////////
/////数据判断部分//////
/////////////////////
switch(cmd[0]){//第一层判断指令,第二层判断操作对象,第三层和第四层判断数据(两个字节),假设是时间以分钟计时可以达45天之久
  case 0x1:
  case 0x2:
  case 0x3:
  }
}
