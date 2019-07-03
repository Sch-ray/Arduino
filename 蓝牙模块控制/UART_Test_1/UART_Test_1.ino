
void setup(){
  byte i=0;
  long data=0x1234,cmd=0,j=0;
  pinMode(0,INPUT);
  pinMode(1,OUTPUT);
  digitalWrite(1,0);
}
void loop(){
  if(!digitalRead(0)){//空闲高电平,开始传输数据拉低
    delayMicroseconds(145);//跳过起始位
    for(i=0;i<32;i++){
      digitalWrite(1,1);//测试用
      if(digitalRead(0) == 1)
      j=0x80000000;
      else
      j=0;
      cmd=cmd>>1;
      test|=j;
      digitalWrite(1,0);//测试用
      delayMicroseconds(90);
    }
  }
  if(data == cmd){
     digitalWrite(1,1);
     delay(300);
     digitalWrite(1,0);
     delay(300);
     digitalWrite(1,1);
     delay(300);
     digitalWrite(1,0);
     delay(300);
     digitalWrite(1,1);
     delay(300);
     digitalWrite(1,0);
     delay(300);
     cmd=0;
  }
}
