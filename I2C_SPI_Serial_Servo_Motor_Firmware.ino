#include <Servo.h>
#include <Wire.h>
#include <SPI.h>
Servo myservo[8];

int dont=1,yes=0,inc=0;
char readf[16]={0};
int dummy=0,dumv=0;
int angle=0;
int angcon=0;
int servno=0;
volatile int yesdo=0;

char buf [26];
volatile byte pos;
volatile boolean process_it;

int gangle=0;//group angle
int gs=0;//group starting address
int ge=0;//group ending address
int gpwm=0;//groups pwm
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
  
  
  pinMode(MISO, OUTPUT);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPI.attachInterrupt();
}


ISR (SPI_STC_vect)
{
byte c = SPDR;  // grab byte from SPI Data Register
  
  // add to buffer if room
  if (pos < sizeof buf)
    {
    buf [pos++] = c;
    
    // example: newline means time to process buffer
    if (c == '\n')
      process_it = true;
      
    }  // end of room available
}  // end of interrupt routine SPI_STC_vect


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
  
   if (process_it)
    {
    for(inc=0;inc<26;inc++)
    readf[inc]=buf[inc];
    buf [pos] = 0;  
    Serial.println (buf);
    pos = 0;
    process_it = false;
    gopera();
    }  // end of flag set
    
  
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
  myservo[servno-1].write(angle);
  delay(15);
}
