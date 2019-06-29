#include<Servo.h>
 
Servo servo;
 
 
//left motor
int L1=2;
int L2=3;
int enL= 5;
 
//right motor
int R1=4;
int R2=7;
int enR=6;
 
//front_sonar
#define trigPinF A0
#define echoPinF A1
//left_sonar
#define trigPinL A2
#define echoPinL A3
//right_sonar
#define trigPinR A4
#define echoPinR A5
 
long cmF;
long cmL;
long cmR;
 
long duration;
const int max=60;
 
 
int mod(int v);  //Modulus function
int set_motors(int a,int b);
 
 
void setup(){
  pinMode(L1,OUTPUT);  //Left motor
  pinMode(L2,OUTPUT);
 
  pinMode(R1,OUTPUT);  //Right motor
  pinMode(R2,OUTPUT);
 
  pinMode(enL,OUTPUT);  //Enable pins of L and R motors
  pinMode(enR,OUTPUT);
 
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
 
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
 
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  Serial.begin(9600);
}
 
 
void loop() {
  sonar();
 
//  if(cmF<=20){
//    set_motors(0,0);
//  }
  if(cmL<=20 && cmR<=20 && cmF>20){
    set_motors(max,max);
    delay(1000);
    //Front
  }
  else if(cmL<=20 && cmF<=20 && cmR>20){
    set_motors(max,-max);
    delay(1000);
    //Right
  }
  else if(cmL>=20 && cmR<=20 && cmF<=20){
    set_motors(-max,max);
    delay(1000);
    //Left
  }else if(cmF<=20 && cmL<=20 && cmF<=20){
    set_motors(0,0);
    delay(2000);
    //Back
    set_motors(-max,-max);
    delay(1000);
  }
  else if(cmF<=20 && cmR>=20 &&cmL>=20){
    set_motors(0,0);
    delay(500);
    set_motors(max,-max);
    delay(1000);
    //Right left clear -> move Right
  }
  else if(cmL<=20 && cmF>=20 && cmR>=20){
    set_motors(0,0);
    delay(500);
    set_motors(max,max);
    delay(1000);
    //Front Right clear ->front
  }
  else if(cmR<=20 &&cmF>=20 && cmL>=20){
    set_motors(0,0);
    delay(500);
    set_motors(max,max);
    delay(1000);
    //Front left clear ->front
  }
  else{
    set_motors(max,max);
    //Front left Right clear ->front
  }
}
 
 
long TimetoDistance(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return (microseconds * 0.03448) / 2;
}
 
  void sonar(){
    //Sonar Front
    digitalWrite(trigPinF, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinF, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinF, LOW);
 
    duration = pulseIn(echoPinF, HIGH);
    cmF = TimetoDistance(duration);
    Serial.print("cmF : ");
    Serial.println(cmF);
 
   //Sonar Left
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);
 
    duration = pulseIn(echoPinL, HIGH);
    cmL = TimetoDistance(duration);
    Serial.print("cmL : ");
    Serial.println(cmL);
   
    //sonar Right
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinR, LOW);
 
    duration = pulseIn(echoPinR, HIGH);
    cmR = TimetoDistance(duration);
    Serial.print("cmR : ");
    Serial.println(cmR);
    Serial.print(" ");
    delay(10);
  }
 
  int set_motors(int l,int r){   //motor setup
 
  Serial.println(l);
  Serial.println(r);
  if(l==0 && r== 0){
    analogWrite(enL,0);
    analogWrite(enR,0);
    Serial.println("Stop.");
   
    digitalWrite(L1,HIGH);
    digitalWrite(L2,HIGH);
   
    digitalWrite(R1,HIGH);
    digitalWrite(R2,HIGH);
  }
  else if(l>=0 && r>=0){
    //max,max
    analogWrite(enL,l);
    analogWrite(enR,r);
    Serial.println("Stright.");
   
    digitalWrite(L1,HIGH);
    digitalWrite(L2,LOW);
   
    digitalWrite(R1,HIGH);
    digitalWrite(R2,LOW);
  }
  else if(l<=0 && r>=0){
    //-max,max
    analogWrite(enL,mod(l));
    analogWrite(enR,mod(r));
    Serial.println("Left.");
   
    digitalWrite(L1,LOW);
    digitalWrite(L2,HIGH);
   
    digitalWrite(R1,HIGH);
    digitalWrite(R2,LOW);
  }
  else if(l>=0 && r<=0){
    //max,-max
    analogWrite(enL,mod(l));
    analogWrite(enR,mod(r));
    Serial.println("Right.");
   
    digitalWrite(L1,HIGH);
    digitalWrite(L2,LOW);
   
    digitalWrite(R1,LOW);
    digitalWrite(R2,HIGH);
  }
  else if(l<=0 && r<=0){
    //-max,-max
    analogWrite(enL,mod(l));
    analogWrite(enR,mod(r));
    Serial.println("Back.");
   
    digitalWrite(L1,LOW);
    digitalWrite(L2,HIGH);
   
    digitalWrite(R1,LOW);
    digitalWrite(R2,HIGH);
  }
 
}
 
int mod(int v){
  //always return positive
  if(v<0){
    return -1*v;
  }
  else if(v>0){
    return v;
  }
  return v;
}
