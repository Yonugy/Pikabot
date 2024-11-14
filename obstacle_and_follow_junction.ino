#include "CytronMotorDriver.h"
CytronMD MotorLeft(PWM_PWM, 11,10);
CytronMD MotorRight(PWM_PWM,9,3);

#define IrLeft A0
#define IrRight A1
#define trig 5
#define echo 4

long duration;
long distance;

void motorMove(int left, int right){
  MotorLeft.setSpeed(left);
  MotorRight.setSpeed(right);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(IrLeft, INPUT);
  pinMode(IrRight, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  distance=20;
  while (distance>15){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    duration=pulseIn(echo, HIGH);
    distance=0.017*duration;
    motorMove(100,100);    
  }
  motorMove(150,-150);
  delay(1500);
  while (digitalRead(IrLeft)==LOW && digitalRead(IrRight)==LOW){
    motorMove(150,150);
  }
  delay(1000);
  while (digitalRead(IrLeft)==LOW || digitalRead(IrRight)==LOW){
    if (digitalRead(IrLeft)==LOW && digitalRead(IrRight)==LOW){
      motorMove(150,150);
    }else if (digitalRead(IrLeft)==HIGH){
      motorMove(0,150);
    }else if (digitalRead(IrLeft)==HIGH){
      motorMove(150,0);
    }
  }
  
}
