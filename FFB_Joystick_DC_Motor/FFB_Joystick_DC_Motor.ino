#include "Joystick.h"

int pitchState = LOW;
int rollState = LOW;


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 0 , 0,
  true, true,//x, y
  false, //z
  false, false, false,//rx, ry, rz
  false,false,false,false,false);

Gains mygains[2];
 EffectParams myeffectparams[2];
 int32_t forces[2] = {0};
  
void setup() {
  //make it work with some accuracy
  analogReference(5); 
  
  //pitch
  pinMode(A1,INPUT);
  //roll
  pinMode(A3,INPUT);
  
  //pitch driver control
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  //roll driver control
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);

  //init axes
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(1023,0);
  //x
  mygains[0].totalGain = 200;
  mygains[0].springGain = 100;
  //y
  mygains[1].totalGain = 200;
  mygains[1].springGain = 100;

  Joystick.setGains(mygains);
  Joystick.begin();
}

void loop() {
  //pitch
  int yAxis = map(analogRead(A1),740,377,1023,0);
  //roll 
  int xAxis = map(analogRead(A3),315,683 ,1023,0);

  //inits roll effects
  myeffectparams[0].springMaxPosition = 1023;
  myeffectparams[0].springPosition = xAxis;//0-1023
  //inits pitch effects
  myeffectparams[1].springMaxPosition = 1023;
  myeffectparams[1].springPosition = yAxis;//0-1023
  
  
  //sends stick position
  Joystick.setYAxis(yAxis);
  Joystick.setXAxis(xAxis);
  
  //fetches stick effects
  Joystick.setEffectParams(myeffectparams);
  Joystick.getForce(forces);


  int rollforce = forces[0]*-1;
  int pitchforce = forces[1]*-1;

  //roll
  if(rollforce > 0){
    digitalWrite(8,LOW);
    digitalWrite(7,HIGH);
    analogWrite(9,abs(forces[0]));

  }
  else if(rollforce < 0){
    digitalWrite(8,LOW); 
    digitalWrite(7,LOW);
    analogWrite(9,abs(forces[0]));
    
  }
  if(rollforce = 0){
    analogWrite(9,0);
  }
  
  //pitch
  if(pitchforce < 0){
    digitalWrite(6,LOW);
    digitalWrite(4,HIGH);
    analogWrite(5,abs(forces[1]));

  }
  else if(pitchforce > 0){
    digitalWrite(6,LOW);   
    digitalWrite(4,LOW);
    analogWrite(5,abs(forces[1]));

  }
  if(pitchforce = 0){
    analogWrite(5,0);
  }
}
