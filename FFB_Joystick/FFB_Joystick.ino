#include "Joystick.h"

int pitchState = LOW;
int rollState = LOW;

unsigned long pitchPrevious = 0;
unsigned long rollPrevious = 0;

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
  pinMode(A2,INPUT);
  
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
  mygains[0].totalGain = 100;
  mygains[0].springGain = 100;
  //y
  mygains[1].totalGain = 100;
  mygains[1].springGain = 100;

  Joystick.setGains(mygains);
  Joystick.begin();
}

void loop() {
  //steps if needed
  //xAxisStepper.runSpeed();
  //yAxisStepper.runSpeed();
  
  //pitch
  int yAxis = map(analogRead(A1),740,377,1023,0);
  //roll 
  int xAxis = map(analogRead(A2),315,683 ,1023,0);

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
  //sets expected intervals to desired force
  int pitchInterval = map(abs(pitchforce),0,255,500,0);
  int rollInterval = map(abs(rollforce),0,255,500,0);
 
  //updates stored runtime
  unsigned long pitchMillis = millis();
  unsigned long rollMillis = millis();
  
  //roll
  if(rollforce > 0){
    digitalWrite(9,LOW);
    digitalWrite(7,HIGH);
    if (rollMillis - rollPrevious >= rollInterval) {
      rollPrevious = rollMillis;
      if (rollState == LOW){
        rollState = HIGH;
      } else {
        rollState = LOW;
      }
    }
    digitalWrite(8,rollState);

  }
  else if(rollforce < 0){
    digitalWrite(9,LOW);
    
    digitalWrite(7,LOW);
    if (rollMillis - rollPrevious >= rollInterval) {
      rollPrevious = rollMillis;
      if (rollState == LOW){
        rollState = HIGH;
      } else {
        rollState = LOW;
      }
    }
    digitalWrite(8,rollState);
    
  }
  //if(rollforce = 0){
    //digitalWrite(9,HIGH);
  //}
  
  //pitch
  if(pitchforce < 0){
  
    digitalWrite(6,LOW);
    digitalWrite(4,LOW);
    if (pitchMillis - pitchPrevious >= pitchInterval) {
      pitchPrevious = pitchMillis;
      if (pitchState == LOW){
        pitchState = HIGH;
      } else {
        pitchState = LOW;
      }
    }
    digitalWrite(5,pitchState);

  }
  else if(pitchforce > 0){
    digitalWrite(6,LOW);
    
    digitalWrite(4,HIGH);
    if ((pitchMillis - pitchPrevious) >= pitchInterval) {
      pitchPrevious = pitchMillis;
      if (pitchState == LOW){
        pitchState = HIGH;
      } else {  
        pitchState = LOW;
      }
    }
    digitalWrite(5,pitchState);

  }
  //if(pitchforce = 0){
    //digitalWrite(6,HIGH);
  //}
}
