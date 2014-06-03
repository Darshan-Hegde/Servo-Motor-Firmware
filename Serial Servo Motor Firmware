#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

int dont=1,yes=0,inc=0;
char readf[16]={0};
int dummy=0,dumv=0;
int angle=0;
int angcon=0;
int servno=0;

void setup()
{
  Serial.begin(9600);
  servo1.attach(8);
  servo2.attach(7);
  servo3.attach(6);
  servo4.attach(5);
  servo5.attach(4);
  servo6.attach(3);
  servo7.attach(2);
  servo8.attach(17);
}

void loop()
{
  if(Serial.available()>0)
  {
    readf[inc]=Serial.read();
    
    if(readf[0]=='$')
    dont=0;
  
    if(readf[inc]=='/')
    {
      dummy=inc;
    }
    
    dumv=inc-dummy;
    
    if(dumv==1)
    {
      if(readf[inc]=='n')
      {
        gopera();
        dont=1;
        for(inc=0;inc<16;inc++)
        readf[inc]='0';
        inc=0;
        dumv=0;
        dummy=0;
      }
    }
    
    if(dont==0)
    inc++;
  }
}

void gopera(void)
{
  for(inc=0;inc<16;inc++)
  Serial.print(readf[inc]); 
  Serial.println(" ");
  servno=readf[8]-48;
  Serial.print("the servo is");
  Serial.println(servno);
 
  angcon=readf[10]-48;
  angle=angcon*100;
  
  angcon=readf[11]-48;
  angle=angle+(angcon*10);
  
  angcon=readf[12]-48;
  angle=angle+angcon;
  
  if(angle>180)
  angle=0;
  
  Serial.print("the angle is");
  Serial.println(angle);
  gotval(servno,angle);
}

void gotval(int servno,int angle)
{
  Serial.println(servno);
  Serial.println(angle);
  if(servno==1)
  servo1.write(angle);
  if(servno==2)
  servo2.write(angle);
  if(servno==3)
  servo3.write(angle);
  if(servno==4)
  servo4.write(angle);
  if(servno==5)
  servo5.write(angle);
  if(servno==6)
  servo6.write(angle);
  if(servno==7)
  servo7.write(angle);
  if(servno==8)
  servo8.write(angle);
  delay(15);
}
