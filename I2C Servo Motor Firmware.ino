


#include <Wire.h>

#include <Servo.h>

Servo myservo[8];

int inc=0;
char readf[26]={0};
volatile int yesdo=0;

int angle=0;
int angcon=0;
int servno=0;

int gangle=0;//group angle
int gs=0;//group starting address
int ge=0;//group ending address
int gpwm=0;//groups pwm

//int iangle[8]={0};//individual simultaneous
//int iservo[8]={0};
//int assoc=0;
//int ianga=0;


void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  myservo[0].attach(8);
  myservo[1].attach(7);
  myservo[2].attach(6);
  myservo[3].attach(5);
  myservo[4].attach(4);
  myservo[5].attach(3);
  myservo[6].attach(2);
  myservo[7].attach(17);
}

void loop()
{
  if(yesdo==1)
  {
    gopera();
    for(inc=0;inc<26;inc++)
    readf[inc]='0';
    inc=0;
    yesdo=0;
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    readf[inc] = Wire.read(); // receive byte as a character
    Serial.print(readf[inc]);
    inc++;    
    
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println();         // print the integer
  yesdo=1; 
}

void gopera(void)
{
  for(inc=0;inc<20;inc++)
  Serial.print(readf[inc]); 
  Serial.println(" ");
  
  if(readf[8]=='g')
  {
    callgroup(); 
  }
  else
  {
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
}

void gotval(int servno,int angle)
{
  Serial.println(servno);
  Serial.println(angle);
  myservo[servno-1].write(angle);
  delay(15);
}

//void callind(void)
//{
//  Serial.println("user called for ind");
//  if(readf[10]=='g')
//  callgoind();
//  else
//  {
//    assoc=readf[10]-48;
//    iservo[assoc-1]=1;
//    
//    angcon=readf[12]-48;
//    ianga=angcon*100;
//    
//    angcon=readf[13]-48;
//    ianga=ianga+(angcon*10);
//    
//    angcon=readf[14]-48;
//    ianga=ianga+angcon;
//    
//    iangle[assoc-1]=ianga;
//    
//    Serial.print(assoc);
//    Serial.print(assoc-1);
//    Serial.println(ianga);
//  }
//}
//
void callgroup(void)
{
  Serial.println("user called for group");
  if(readf[10]=='g')
  callgogroup();
  else
  {
   gs=readf[10]-48;
   Serial.print("group starting address");
   Serial.println(gs);
   ge=readf[12]-48;
   Serial.println(ge);
   
    angcon=readf[14]-48;
    gangle=angcon*100;
    
    angcon=readf[15]-48;
    gangle=gangle+(angcon*10);
    
    angcon=readf[16]-48;
    gangle=gangle+angcon;
    
    Serial.print("group angle");
    Serial.println(gangle);
  }
}
//
//void callgoind(void)
//{
//  int k=0;
//  Serial.println("user want ind to go");
//  for(k=0;k<8;k++)
//  {
//    Serial.println(iservo[k]);
//    if(iservo[k]==1)
//    myservo[k].write(iangle[k]);
//    Serial.println(iangle[k]);
//  }
//  
//  
//}

void callgogroup(void)
{
  Serial.println("user wants group to go");
  for(gs;gs<=ge;gs++)
  {
   myservo[gs-1].write(gangle);
   Serial.print(gs);
  }
  Serial.println(gangle);
}
