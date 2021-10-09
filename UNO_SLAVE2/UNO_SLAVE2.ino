#include <Wire.h>
#include <AccelStepper.h>
AccelStepper stepper(1,8,4);
int ENA = 2 ;

char a0,b0,c0,d0,e0,f0,j0,k0;
String a;
float the2,sub,the2_r,sub_flag,sub_the;
float flag=0;
const float pi=3.14159265359;
int xung,xung1,xung2,xung_flag,xung_the,flag1,move_the;
int t,spec,t1,t2,tflag;
int state=0;
float accel,vmax,vmax_the,accel_the,vmax_flag,accel_flag;
unsigned long time1,time2,sub_time;

void control()
{
  Serial.println("Ham control duoc goi");
  state = 1;
}

void setup() {
 Wire.begin(12);                
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
   if(the2!=flag)
   {
    if((flag>60)||(the2>60))
    spec=1;
    else spec=0;
    Serial.println(spec);
    if(spec==1)
    { 
      move_the =-the2*33164/360;
      if(t>=5)
      {
//        tflag= the2-60;
//        if(tflag<30)
//        t1=t/5;
//        if(tflag>30)
        t1=t/2;
        t2=t-t1;
      }
      else
      {
        t1=1;
        t2=t-t1;
      }
      flag1 = 60;
      sub_flag =flag-flag1;
      xung_flag=sub_flag*33164/360;
      sub_the = the2-flag1;
      xung_the = sub_the*33164/360;
    if(t1>=5)
    {
      vmax_flag=xung_flag/(t1+2-2*(sqrt(0.4*t1)));
      accel_flag=vmax_flag/(0.2*t1);
    }
    if(t1==4)
    {
      vmax_flag=xung_flag/(t1+2-2*(sqrt(1/(0.1*t1))));
      accel_flag=vmax_flag*0.2*t1;
    }
    if(t1==3)
    {
      vmax_flag=xung_flag/(t1+2-2*(sqrt(1/(0.12*t1))));
      accel_flag=vmax_flag*0.24*t1;
    }
    if(t1==2)
    {
      vmax_flag=xung_flag/(t1+2-2*(sqrt(1/(0.21*t1))));
      accel_flag=vmax_flag*0.43*t1; //cong thuc 0.43->0.42
    }
    if(t1==1)
    {
      vmax_flag=10000;
      accel_flag=3.8*xung_flag;  //cong thuc accel=4*xung
    }
    ///////////////////////////////////////////////////
      if(t2>=5)
    {
      vmax_the=xung_the/(t2+2-2*(sqrt(0.4*t2)));
      accel_the=vmax_the/(0.2*t2);
    }
    if(t2==4)
    {
      vmax_the=xung_the/(t2+2-2*(sqrt(1/(0.1*t2))));
      accel_the=vmax_the*0.2*t2;
    }
    if(t2==3)
    {
      vmax_the=xung_the/(t2+2-2*(sqrt(1/(0.12*t2))));
      accel_the=vmax_the*0.24*t2;
    }
    if(t2==2)
    {
      vmax_the=xung_the/(t2+2-2*(sqrt(1/(0.21*t2))));
      accel_the=vmax_the*0.43*t2; //cong thuc 0.43->0.42
    }
    if(t2==1)
    {
      vmax_the=10000;
      accel_the=3.8*xung_the;  //cong thuc accel=4*xung
    }
    }
    if(spec==0)
    {
    sub=the2-flag;
    xung= sub*33164/360;
    xung1= abs(xung);
    xung2= -the2*33164/360;;
    
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
    }
  if (stepper.distanceToGo() == 0) 
  {
  if(spec==0)
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
  flag=the2;
  delay(1000);
  state=0;
  }
  if(spec==1)
  {
    delay(1000);
    time1 = millis();
    stepper.setMaxSpeed(vmax_flag);
    stepper.setAcceleration(accel_flag);
    stepper.moveTo(-5527);
    stepper.runToPosition();
    stepper.setMaxSpeed(vmax_the);
    stepper.setAcceleration(accel_the);
    stepper.moveTo(move_the);
    stepper.runToPosition();
    time2 = millis(); 
    sub_time = time2-time1;
    Serial.print("Thoi gian thuc te the: ");
    Serial.println(sub_time);
    Serial.print("Thoi gian dat t1: ");
    Serial.println(t1);
    Serial.print("Thoi gian dat t2: ");
    Serial.println(t2);
    flag=the2;
    delay(1000);
    state=0;
  }
 }
 }
 else state=0;
}
 the2 = the2_r*180/pi;
 Serial.println(the2);
 Serial.println(flag);
 delay(500);
}

void requestEvent()
{
 static char theta2[9];
 static char theta22[9];
 dtostrf(the2_r,6,4,theta2);
 dtostrf(flag,6,2,theta22);
 char var = 'a';
 char var1 = 'b';
 Wire.write(theta2);
 Wire.write(var);
 Wire.write(theta22);
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
    the2_r = a.toFloat();
    Serial.println("==========");
    Serial.println(i);
  }    
}