#include <Wire.h>
#include <string.h>
char a0,b0,c0,d0,e0,f0,j0,q0,m0,r0,re_var;
char x[1] = "0";
char t_slave[6]; 
char t1_slave[9]; 
char t2_slave[9]; 
char t3_slave[9]; 
char re[2] = "0";
String a;
float the1,the2,the3,t;
//float the1, the2, the3;
float s3, t31, t32, t1, t2, t3, k1, k2, k, anp1, cosanp1, cosanp1_2, sinanp1, t11, t12, flag;
float c_3,n1, n2, n, anp2, cosanp2, cosanp2_2, sinanp2, t21, t22, t23, t24;
float test_11,test_12,test_13,test_14,test_21,test_22,test_23,test_24;
float test_31,test_32,test_33,test_34,test_41,test_42,test_43,test_44;
float test_51,test_52,test_53,test_54;
const float pi=3.14159265359;
float px, px1;
float py, py1;
float pz, pz1;
const float d=9.5; const float d4=13; const float d5=13.5;
int state;
int count = 0;
int var=0;

void setup() {
 Wire.begin(8);               
 Wire.onReceive(receiveEvent);
 Wire.onRequest(requestEvent);
 Serial.begin(115200);
 attachInterrupt(1,change,RISING);
}
void change()
{
  flagt2=t2;
}

void loop()
{
  dtostrf(t,6,4,t_slave);
  if(state==0)
  {
    FK();
    the1 = px;
    the2 = py;
    the3 = pz;
    dtostrf(the1,6,4,t1_slave);
    dtostrf(the2,6,4,t2_slave);
    dtostrf(the3,6,4,t3_slave);
  }
    if(state==1)
  {
    px1=px;
    py1=py;
    pz1=pz;
    IK();
    the1 = t1;
    the2 = t2;
    the3 = t3;
    dtostrf(the1,6,4,t1_slave);
    dtostrf(the2,6,4,t2_slave);
    dtostrf(the3,6,4,t3_slave);
  }
    Serial.println(t1,4);
    Serial.println(t2,4);
    Serial.println(t3,4);
  if(count==0)
  {
  for(int j=0;j<2;j++)
    {
      String y;
      y = String(j);
      y.toCharArray(x,2);
      if(x[0]=='0')
      {
        Wire.beginTransmission(10); 
        Wire.write(x); 
        Wire.write(t_slave);
        Wire.endTransmission(); 
        delay(100);
      }
      if(x[0]=='1')
      {
        Wire.beginTransmission(10); 
        Wire.write(x);
        Wire.write(t1_slave);
        Wire.endTransmission();  
        delay(100);
      }
    }
  }
    if(count==1)
  {
  for(int j=0;j<2;j++)
    {
      String y;
      y = String(j);
      y.toCharArray(x,2);
      if(x[0]=='0')
      {
        Wire.beginTransmission(12); 
        Wire.write(x); 
        Wire.write(t_slave);
        Wire.endTransmission(); 
        delay(100);
      }
      if(x[0]=='1')
      {
        Wire.beginTransmission(12); 
        Wire.write(x);
        Wire.write(t2_slave);
        Wire.endTransmission();  
        delay(100);
      }
    }
  }
      if(count==2)
  {
  for(int j=0;j<2;j++)
    {
      String y;
      y = String(j);
      y.toCharArray(x,2);
      if(x[0]=='0')
      {
        Wire.beginTransmission(14); 
        Wire.write(x); 
        Wire.write(t_slave);
        Wire.endTransmission(); 
        delay(100);
      }
      if(x[0]=='1')
      {
        Wire.beginTransmission(14); 
        Wire.write(x);
        Wire.write(t3_slave);
        Wire.endTransmission();  
        delay(100);
      }
    }
  }
    delay(100);
    count++;
    if(count==3)   count=0;
}
// function that executes whenever data is received from master
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
    if(i==8) q0=x;
    if(i==9) m0=x;
    if(i==10)r0=x;
  }
   if(a0=='0')
  {
  a=""; 
  a= String(a+b0+c0+d0);
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
    a= String(a+b0+c0+d0+e0+f0+j0+q0);
    if(i==9)
    a= String(a+b0+c0+d0+e0+f0+j0+q0+m0);
    if(i==10)
    a= String(a+b0+c0+d0+e0+f0+j0+q0+m0+r0);
    px = a.toFloat();
  }
    if(a0=='2')
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
    a= String(a+b0+c0+d0+e0+f0+j0+q0);
    if(i==9)
    a= String(a+b0+c0+d0+e0+f0+j0+q0+m0);
    if(i==10)
    a= String(a+b0+c0+d0+e0+f0+j0+q0+m0+r0);
    py = a.toFloat();
  }
    if(a0=='3')
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
    a= String(a+b0+c0+d0+e0+f0+j0+q0);
    if(i==9)
    a= String(a+b0+c0+d0+e0+f0+j0+q0+m0);
    if(i==10)
    a= String(a+b0+c0+d0+e0+f0+j0+q0+m0+r0);
    pz = a.toFloat();
  }
    if(a0=='4')
    {
      a="";
      a= String(a+b0);
      state= a.toInt();
    }
}

void requestEvent() {
 static char theta1[9];
 dtostrf(px1,6,4,theta1);
 static char theta2[9];
 dtostrf(py1,6,4,theta2); 
 static char theta3[9];
 dtostrf(pz1,6,4,theta3);
 for(int j=0;j<3;j++)
    {
    String y;
    y = String(j);
    y.toCharArray(re,2);
    if(re[0]=='0')
      {
        re_var='a';
        Wire.write(theta1);
        Wire.write(re_var);
      }
     if(re[0]=='1')
      {
        re_var='b';
        Wire.write(theta2);
        Wire.write(re_var);
      }
     if(re[0]=='2')
      {
        re_var='c';
        Wire.write(theta3);
        Wire.write(re_var);
      }
    } 
}

void FK()
{
  // neu nhan ham FK thi cac du lieu px py pz se tuong ung t1 t2 t3
  px1= d4*cos(px)*sin(py)- sin(px)*d - d5*sin(px)*sin(pz) + d5*cos(px)*cos(py)*cos(pz);
  py1= d4*sin(px)*sin(py)+ cos(px)*d + d5*cos(px)*sin(pz) + d5*sin(px)*cos(py)*cos(pz);
  pz1= d4*cos(py) - d5*cos(pz)*sin(py);
}
void IK()
{
  for(int i=1;i>-2;i-=2)
  //theta3
  {
  s3 =(px*px+py*py+pz*pz-d4*d4-d5*d5-d*d)/(2*d5*d);
  t31=asin(s3);
  t32=pi-t31;
  // tính thêm cái gì đó
  if(abs(t31)<abs(t32)) t32=t31;
  if(abs(t32)<abs(t31)) t31=t32;
  //-----------------------------------
  if(i==1)  t3=t31;
  if(i==-1) t3=t32;
  //theta1
  k1=py;
  k2=-px;
  k=d+d5*s3;
  anp1 = atan2(k2/(sqrt(k1*k1+k2*k2)),k1/(sqrt(k1*k1+k2*k2)));
  cosanp1 = k/sqrt(k1*k1+k2*k2);
  cosanp1_2 = cosanp1*cosanp1;
  sinanp1 = sqrt(1-cosanp1_2);
  t11 = anp1 + atan2(sinanp1,cosanp1);
  t12 = anp1 + atan2(-sinanp1,cosanp1);
    for(int j=1;j>-2;j-=2)
    {
      //theta2
      c_3= j*sqrt(1-s3*s3);
      n1=d4;
      n2=-d5*c_3;
      n=pz;
      anp2 = atan2(n2/(sqrt(n1*n1+n2*n2)),n1/(sqrt(n1*n1+n2*n2)));
      cosanp2 = n/(sqrt(n1*n1+n2*n2));
      cosanp2_2= cosanp2*cosanp2;
      sinanp2 = sqrt(1-cosanp2_2);
      if(j==1)
      {
      t21 = anp2 + atan2(sinanp2,cosanp2);
      t22 = anp2 + atan2(-sinanp2,cosanp2);
      }
      if(j==-1)
      {
      t23 = anp2 + atan2(sinanp2,cosanp2);
      t24 = anp2 + atan2(-sinanp2,cosanp2);
      }
    }
    if((abs(t21)==abs(t23))&&(abs(t21)<0.0001))
    {
    t23=t22/2;
    t21=0;
    }
    if((abs(t21)==abs(t24))&&(abs(t21)<0.0001))
    {
    t24=t22/2;
    t21=0;
    }
    // tính thêm cái gì đó
    if(abs(t21)<abs(t22))
    t22=t21;
    if(abs(t21)>abs(t22))
    t21=t22;
    if(abs(t23)>abs(t24))
    t23=t24;
    if(abs(t24)>abs(t23))
    t24=t23;
    ////////////////////////////////////////
test_11= abs((-d*sin(t11)-d5*sin(t11)*sin(t3)+d5*cos(t11)*cos(t21)*cos(t3)+d4*cos(t11)*sin(t21))-px);
test_12= abs((-d*sin(t11)-d5*sin(t11)*sin(t3)+d5*cos(t11)*cos(t22)*cos(t3)+d4*cos(t11)*sin(t22))-px);
test_13= abs((-d*sin(t11)-d5*sin(t11)*sin(t3)+d5*cos(t11)*cos(t23)*cos(t3)+d4*cos(t11)*sin(t23))-px);
test_14= abs((-d*sin(t11)-d5*sin(t11)*sin(t3)+d5*cos(t11)*cos(t24)*cos(t3)+d4*cos(t11)*sin(t24))-px);
test_21= abs((-d*sin(t12)-d5*sin(t12)*sin(t3)+d5*cos(t12)*cos(t21)*cos(t3)+d4*cos(t12)*sin(t21))-px);
test_22= abs((-d*sin(t12)-d5*sin(t12)*sin(t3)+d5*cos(t12)*cos(t22)*cos(t3)+d4*cos(t12)*sin(t22))-px);
test_23= abs((-d*sin(t12)-d5*sin(t12)*sin(t3)+d5*cos(t12)*cos(t23)*cos(t3)+d4*cos(t12)*sin(t23))-px);
test_24= abs((-d*sin(t12)-d5*sin(t12)*sin(t3)+d5*cos(t12)*cos(t24)*cos(t3)+d4*cos(t12)*sin(t24))-px);
//-------------------------------------------------------------------------------------------
test_31= abs((d*cos(t11)+d5*cos(t11)*sin(t3)+d5*sin(t11)*cos(t21)*cos(t3)+d4*sin(t11)*sin(t21))-py);
test_32= abs((d*cos(t11)+d5*cos(t11)*sin(t3)+d5*sin(t11)*cos(t22)*cos(t3)+d4*sin(t11)*sin(t22))-py);
test_33= abs((d*cos(t11)+d5*cos(t11)*sin(t3)+d5*sin(t11)*cos(t23)*cos(t3)+d4*sin(t11)*sin(t23))-py);
test_34= abs((d*cos(t11)+d5*cos(t11)*sin(t3)+d5*sin(t11)*cos(t24)*cos(t3)+d4*sin(t11)*sin(t24))-py);
test_41= abs((d*cos(t12)+d5*cos(t12)*sin(t3)+d5*sin(t12)*cos(t21)*cos(t3)+d4*sin(t12)*sin(t21))-py);
test_42= abs((d*cos(t12)+d5*cos(t12)*sin(t3)+d5*sin(t12)*cos(t22)*cos(t3)+d4*sin(t12)*sin(t22))-py);
test_43= abs((d*cos(t12)+d5*cos(t12)*sin(t3)+d5*sin(t12)*cos(t23)*cos(t3)+d4*sin(t12)*sin(t23))-py);
test_44= abs((d*cos(t12)+d5*cos(t12)*sin(t3)+d5*sin(t12)*cos(t24)*cos(t3)+d4*sin(t12)*sin(t24))-py);
//-------------------------------------------------------------------------------------------
test_51= abs((d4*cos(t21)-d5*cos(t3)*sin(t21))-pz);
test_52= abs((d4*cos(t22)-d5*cos(t3)*sin(t22))-pz);
test_53= abs((d4*cos(t23)-d5*cos(t3)*sin(t23))-pz);
test_54= abs((d4*cos(t24)-d5*cos(t3)*sin(t24))-pz);
//--------------------------------------
if((test_11<0.1)&&(test_31<0.1)&&(test_51<0.1))
    {
    t1=t11;
    t2=t21;
    }
if((test_12<0.1)&&(test_32<0.1)&&(test_52<0.1))
    {
    t1=t11;
    t2=t22;
    }
if((test_13<0.1)&&(test_33<0.1)&&(test_53<0.1))
    {
    t1=t11;
    t2=t23;
    }
if((test_14<0.1)&&(test_34<0.1)&&(test_54<0.1))
    {
    t1=t11;
    t2=t24;
    }
if((test_21<0.1)&&(test_41<0.1)&&(test_51<0.1))
    {
    t1=t12;
    t2=t21;
    }
if((test_22<0.1)&&(test_42<0.1)&&(test_52<0.1))
    {
    t1=t12;
    t2=t22;
    }
if((test_23<0.1)&&(test_43<0.1)&&(test_53<0.1))
   {
    t1=t12;
    t2=t23;
    }
if((test_24<0.1)&&(test_44<0.1)&&(test_54<0.1))
    {
    t1=t12;
    t2=t24;
    }
  }
}