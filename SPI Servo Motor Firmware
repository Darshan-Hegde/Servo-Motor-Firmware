


#include <SPI.h>
#include <Servo.h>

Servo myservo[8];

char buf [26];
volatile byte pos;
volatile boolean process_it;

int inc=0;
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

void setup (void)
{
  Serial.begin (9600);   // debugging

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPI.attachInterrupt();
  
  myservo[0].attach(8);
  myservo[1].attach(7);
  myservo[2].attach(6);
  myservo[3].attach(5);
  myservo[4].attach(4);
  myservo[5].attach(3);
  myservo[6].attach(2);
  myservo[7].attach(17);

}  // end of setup


// SPI interrupt routine
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

// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (process_it)
    {
    buf [pos] = 0;  
    Serial.println (buf);
    pos = 0;
    process_it = false;
    gopera();
    }  // end of flag set
    
    
}  // end of loop

void gopera(void)
{
  for(inc=0;inc<20;inc++)
  Serial.print(buf[inc]);
  Serial.println(" ");
  
  if(buf[8]=='g')
  {
    callgroup(); 
  }
  else
  {
    servno=buf[8]-48;
    Serial.print("the servo is");
    Serial.println(servno);
   
    angcon=buf[10]-48;
    angle=angcon*100;
    
    angcon=buf[11]-48;
    angle=angle+(angcon*10);
    
    angcon=buf[12]-48;
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
//  if(buf[10]=='g')
//  callgoind();
//  else
//  {
//    assoc=buf[10]-48;
//    iservo[assoc-1]=1;
//    
//    angcon=buf[12]-48;
//    ianga=angcon*100;
//    
//    angcon=buf[13]-48;
//    ianga=ianga+(angcon*10);
//    
//    angcon=buf[14]-48;
//    ianga=ianga+angcon;
//    
//    iangle[assoc-1]=ianga;
//    
//    Serial.print(assoc);
//    Serial.print(assoc-1);
//    Serial.println(ianga);
//  }
//}

void callgroup(void)
{
  Serial.println("user called for group");
  if(buf[10]=='g')
  callgogroup();
  else
  {
   gs=buf[10]-48;
   Serial.print("group starting address");
   Serial.println(gs);
   ge=buf[12]-48;
   Serial.println(ge);
   
    angcon=buf[14]-48;
    gangle=angcon*100;
    
    angcon=buf[15]-48;
    gangle=gangle+(angcon*10);
    
    angcon=buf[16]-48;
    gangle=gangle+angcon;
    
    Serial.print("group angle");
    Serial.println(gangle);
  }
}

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
