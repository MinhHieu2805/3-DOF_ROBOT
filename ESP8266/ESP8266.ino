#include <Wire.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

byte* data;
unsigned long b_time;
//const char* ssid = "72K1" ;
//const char* password =  "28051999" ;
//const char* mqttServer = "192.168.1.4";
const char* ssid = "C303" ;
const char* password =  "drcLab2020" ;
const char* mqttServer = "192.168.0.107";
String clientId = "ClientESP8266";
String sdata;
const char* px_topic = "px";
const char* py_topic = "py";
const char* pz_topic = "pz";
const char* t1_topic = "theta1";
const char* t2_topic = "theta2";
const char* t3_topic = "theta3";
const char* t_topic = "settime";
const char* FK_topic = "FK";
const char* IK_topic = "IK";
const char* run_topic = "run";
const char* d_theta1_topic = "d_theta1";
const char* d_theta2_topic = "d_theta2";
const char* d_theta3_topic = "d_theta3";
const char* flag1_topic = "flag1";
const char* flag2_topic = "flag2";
const char* flag3_topic = "flag3";
const char* d_px_topic ="d_px";
const char* d_py_topic ="d_py";
const char* d_pz_topic ="d_pz";
const char* m_topic = "72K1";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int j=0;

String px1,py1,pz1,t1,t2,t3,st,fw,iv,runn;
char flag;
char px2[10] = "6.00";
char py2[10] = "9.34";
char pz2[10] = "20.00";
char the1[10] = "0.00";
char the2[10] = "0.00";
char the3[10] = "0.00";
char px_d[10]= "13.5";
char py_d[10]= "9.5";
char pz_d[10]= "13.00";
char the1_d[10] = "0.00";
char the2_d[10] = "0.00";
char the3_d[10] = "0.00";
char flag_t1d[10] = "0.00";
char flag_t2d[10] = "0.00";
char flag_t3d[10] = "0.00";
char t[4] = "5.0";
char x[2] = "0";
char k_var[2] = "0";
char run_var[2] = "0";
String mang,p_x,p_y,p_z,the_1,the_2,the_3,flag_t1,flag_t2,flag_t3;

void setup()
{
  Serial.begin(115200);
  Wire.begin(D1, D2);
  setup_wifi();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
  pinMode(D7,OUTPUT);
}


void setup_wifi()
{
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}
void callback(char* topic, byte* payload, unsigned int length)
{
  if (strcmp(topic, px_topic) == 0)
  {
    px1 = "";
    for (int i = 0; i < length; i++)
    {
      px1 += (char)payload[i];
    }
    px1.toCharArray(px2, 10);
  }
    if (strcmp(topic, py_topic) == 0)
  {
    py1 = "";
    for (int i = 0; i < length; i++)
    {
      py1 += (char)payload[i];
    }
    py1.toCharArray(py2, 10);
  }
    if (strcmp(topic, pz_topic) == 0)
  {
    pz1 = "";
    for (int i = 0; i < length; i++)
    {
      pz1 += (char)payload[i];
    }
    pz1.toCharArray(pz2, 10);
  }
  if (strcmp(topic, t1_topic) == 0)
  {
    t1 = "";
    for (int i = 0; i < length; i++)
    {
      t1 += (char)payload[i];
    }
    t1.toCharArray(the1, 10);
  }
    if (strcmp(topic, t2_topic) == 0)
  {
    t2 = "";
    for (int i = 0; i < length; i++)
    {
      t2 += (char)payload[i];
    }
    t2.toCharArray(the2, 10);
  }
    if (strcmp(topic, t3_topic) == 0)
  {
    t3 = "";
    for (int i = 0; i < length; i++)
    {
      t3 += (char)payload[i];
    }
    t3.toCharArray(the3, 10);
  }
    if (strcmp(topic, t_topic) == 0)
  {
    st = "";
    for (int i = 0; i < 3; i++)
    {
      st += (char)payload[i];
    }
    if(length==2)
    {
      st[2]='.';
    }
     if(length==1)
    {
      st[1]='.'; st[2]='0';
    }
    st.toCharArray(t, 4);
  }
  if (strcmp(topic, FK_topic) == 0)
  {
    fw = "";
    for (int i = 0; i < length; i++)
    {
      fw = (char)payload[i];
    }
    fw.toCharArray(k_var,2);
  }
  if (strcmp(topic, IK_topic) == 0)
  {
    iv = "";
    for (int i = 0; i < length; i++)
    {
      iv = (char)payload[i];
    }
    iv.toCharArray(k_var,2);
  }
  if (strcmp(topic, run_topic) == 0)
  {
    runn = "";
    for (int i = 0; i < length; i++)
    {
      runn = (char)payload[i];
    }
    runn.toCharArray(run_var,2);
  }
}




void reconnect()
{
  while (!client.connected())
  {
    if (client.connect(clientId.c_str()))
    {
      client.publish(m_topic, "Reconnect");               // Gửi dữ liệu
      client.subscribe(m_topic); 
      client.subscribe(px_topic);
      client.subscribe(py_topic);
      client.subscribe(pz_topic);
      client.subscribe(t1_topic);
      client.subscribe(t2_topic);
      client.subscribe(t3_topic);
      client.subscribe(t_topic);
      client.subscribe(FK_topic);
      client.subscribe(IK_topic);
      client.subscribe(run_topic);
    }
    else
    {
      delay(1000);
    }
  }
}
void loop()
{
  if(run_var[0]=='1')
  {
    Serial.println(run_var);
    digitalWrite(D7,HIGH);
    delay(500);
    digitalWrite(D7,LOW);
    run_var[0]='0';
  }
  if(k_var[0]=='0')
  {
    for(int j=0;j<5;j++)
    {
      String y;
      y = String(j);
      y.toCharArray(x,2);
      if(x[0]=='0')
      {
        Wire.beginTransmission(8);
        Wire.write(x);
        Wire.write(t);
        Wire.endTransmission();
      }
     if(x[0]=='1')
      {
      Wire.beginTransmission(8);
      Wire.write(x);
      Wire.write(the1);
      Wire.endTransmission();
      }
     if(x[0]=='2')
      {
      Wire.beginTransmission(8);
      Wire.write(x);
      Wire.write(the2);
      Wire.endTransmission();
      } 
     if(x[0]=='3')
      {
      Wire.beginTransmission(8);
      Wire.write(x);
      Wire.write(the3);
      Wire.endTransmission();
      }  
     if(x[0]=='4') 
      {
      Wire.beginTransmission(8);
      Wire.write(x);
      Wire.write(k_var);
      Wire.endTransmission();
      }
    }
  }
  if(k_var[0]=='1')
  {
  for(int j=0;j<5;j++)
    {
    String y;
    y = String(j);
    y.toCharArray(x,2);
    if(x[0]=='0')
      {
      Wire.beginTransmission(8);
      Wire.write(x);
      Wire.write(t);
      Wire.endTransmission();
      }
     if(x[0]=='1')
      {
      Wire.beginTransmission(8);
      Wire.write(x);
      Wire.write(px2);
      Wire.endTransmission();
      }
     if(x[0]=='2')
      {
      Wire.beginTransmission(8);
      Wire.write(x);
      Wire.write(py2);
      Wire.endTransmission();
      } 
     if(x[0]=='3')
      {
      Wire.beginTransmission(8);
      Wire.write(x);
      Wire.write(pz2);
      Wire.endTransmission();
      } 
    if(x[0]=='4') 
      {
      Wire.beginTransmission(8);
      Wire.write(x);
      Wire.write(k_var);
      Wire.endTransmission();
      }  
    }
  }
  
  Wire.requestFrom(8, 28);
  mang = "";
  while(Wire.available()){
  char c = Wire.read();
  mang += c;
  if(c=='a')
  {
   int var = mang.length();
   p_x= mang.substring(0,var-1);
   mang="";
  }
  if(c=='b')
  {
   int var = mang.length();
   p_y= mang.substring(0,var-1); 
   mang="";
  }
  if(c=='c')
  {
   int var = mang.length();
   p_z= mang.substring(0,var-1); 
   mang="";
  }
 }
  p_x.toCharArray(px_d,10); 
  p_y.toCharArray(py_d,10);
  p_z.toCharArray(pz_d,10);
  Serial.println();
  Serial.println(p_x);
  Serial.println(p_y);
  Serial.println(p_z);
  Serial.println("=============");
  Wire.requestFrom(10, 20);
  mang = "";
  while(Wire.available()){
  char c = Wire.read();
  mang += c; 
  if(c=='a')
  {
   int var = mang.length();
   the_1= mang.substring(0,var-1);
   mang="";
  }
  if(c=='b')
  {
   int var = mang.length();
   flag_t1= mang.substring(0,var-1); 
   mang="";
  }
  }
  the_1.toCharArray(the1_d,10);
  flag_t1.toCharArray(flag_t1d,10);
//  Serial.println(flagt1,4);
  Wire.requestFrom(12, 20);
  mang = "";
  while(Wire.available()){
  char c = Wire.read();
  mang += c; 
  if(c=='a')
  {
   int var = mang.length();
   the_2= mang.substring(0,var-1);
   mang="";
  }
  if(c=='b')
  {
   int var = mang.length();
   flag_t2= mang.substring(0,var-1); 
   mang="";
  }
  }
  the_2.toCharArray(the2_d,10);
  flag_t2.toCharArray(flag_t2d,10);

  Wire.requestFrom(14, 20);
  mang = "";
  while(Wire.available()){
  char c = Wire.read();
  mang += c; 
  if(c=='a')
  {
   int var = mang.length();
   the_3= mang.substring(0,var-1);
   mang="";
  }
  if(c=='b')
  {
   int var = mang.length();
   flag_t3= mang.substring(0,var-1); 
   mang="";
  }
  }
  the_3.toCharArray(the3_d,10);
  flag_t3.toCharArray(flag_t3d,10);
  
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  for(int i=0;i<9;i++)
  {
    if(i==0)
    client.publish(d_theta1_topic, the1_d);
    if(i==1)
    client.publish(d_theta2_topic, the2_d);
    if(i==2)
    client.publish(d_theta3_topic, the3_d);
    if(i==3)
    client.publish(d_px_topic, px_d);
    if(i==4)
    client.publish(d_py_topic, py_d);
    if(i==5)
    client.publish(d_pz_topic, pz_d);
    if(i==6)
    client.publish(flag1_topic, flag_t1d);
    if(i==7)
    client.publish(flag2_topic, flag_t2d);
    if(i==8)
    client.publish(flag3_topic, flag_t3d);
  }
  delay(500);
}
