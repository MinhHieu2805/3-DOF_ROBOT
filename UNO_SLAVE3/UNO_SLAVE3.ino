#include <Wire.h>
#include <AccelStepper.h>
AccelStepper stepper(1,8,4);
int ENA = 2 ;

char a0,b0,c0,d0,e0,f0,j0,k0;
String a;
float the3,sub,the3_r;
float flag=0;
const float pi=3.14159265359;
int xung,xung1,xung2;
int t;
int state=0;
float accel,vmax;
unsigned long time1,time2,sub_time;

void control()
{
  Serial.println("Ham control duoc goi");
  state = 1;
}

void setup() {
 Wire.begin(14);                
 Wire.onReceive(receiveEvent); 
 Wire.onRequest(requestEvent);
 Serial.begin(115200);   
 pinMode (ENA, OUTPUT);
 digitalWrite (ENA,LOW);        
 attachInterrupt(1, control, RISING);
}

void loop() {
if(state==1)
{
   if(the3!=flag)
   {
    sub= the3-flag;
    xung= sub*6400/360;
    xung1= abs(xung);
    xung2= the3*6400/360;
    if(t>=5)
    {
      vmax=xung1/(t+2-2*(sqrt(0.4*t)));
      accel=vmax/(0.2*t);
    }
    if(t==4)
    {
      vmax=xung1/(t+2-2*(sqrt(1/(0.1*t))));
      accel=vmax*0.2*t;
    }
    if(t==3)
    {
      vmax=xung1/(t+2-2*(sqrt(1/(0.12*t))));
      accel=vmax*0.24*t;
    }
    if(t==2)
    {
      vmax=xung1/(t+2-2*(sqrt(1/(0.21*t))));
      accel=vmax*0.43*t; //cong thuc 0.43->0.42
    }
    if(t==1)
    {
      vmax=10000;
      accel=3.8*xung1;  //cong thuc accel=4*xung
    }
  if (stepper.distanceToGo() == 0) 
  {
  delay(1000);
  time1 = millis();
  stepper.setMaxSpeed(vmax);
  stepper.setAcceleration(accel);
  stepper.moveTo(xung2);
  stepper.runToPosition();
  time2 = millis();
  sub_time = time2-time1;
  Serial.print("Thoi gian thuc te: ");
  Serial.println(sub_time);
  Serial.print("gia toc: ");
  Serial.println(accel);
  Serial.print("Van toc: ");
  Serial.println(vmax);
  Serial.print("Xung: ");
  Serial.println(xung1);
  Serial.println(xung2);
  Serial.print("Thoi gian dat: ");
  Serial.println(t);
  flag=the3;
  delay(1000);
  state=0;
 }
 }
 else state=0;
}
 the3 = the3_r*180/pi;
 Serial.println(the3);
 Serial.println(flag);
 delay(500);
}

void requestEvent()
{
 static char theta3[9];
 static char theta33[9];
 dtostrf(the3_r,6,4,theta3);
 dtostrf(flag,6,2,theta33);
 char var = 'a';
 char var1 = 'b';
 Wire.write(theta3);
 Wire.write(var);
 Wire.write(theta33);
 Wire.write(var1);
}
void receiveEvent() 
{
 int i=0;
  while (0 < Wire.available()) 
  {
    char x = Wire.read();  
    i+=1;
    if(i==1) a0=x;   
    if(i==2) b0=x;       
    if(i==3) c0=x;    
    if(i==4) d0=x;    
    if(i==5) e0=x;     
    if(i==6) f0=x;
    if(i==7) j0=x;
    if(i==8) k0=x;
  }
  if(a0=='0')
  {
  a=""; 
  a= String(a+b0+c0+d0+e0+f0+j0);
  t = a.toFloat();
  }     
  if(a0=='1')
  {
    a="";
    if(i==2)
    a= String(a+b0);
    if(i==3)
    a= String(a+b0+c0);
    if(i==4)
    a= String(a+b0+c0+d0);
    if(i==5)
    a= String(a+b0+c0+d0+e0);
    if(i==6)
    a= String(a+b0+c0+d0+e0+f0);
    if(i==7)
    a= String(a+b0+c0+d0+e0+f0+j0);
    if(i==8)
    a= String(a+b0+c0+d0+e0+f0+j0+k0);
    the3_r = a.toFloat();
  }    
}