#include "CytronMotorDriver.h"
CytronMD motorLeft(PWM_PWM,11,10);
CytronMD motorRight(PWM_PWM, 9,3);
#define IRleft A0
#define IRright A1
#define button 2
#define trig 5
#define echo 4
long duration;
long distance;
int mode;

void motorMove(int left,int right){
  motorLeft.setSpeed(left);
  motorRight.setSpeed(right);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(IRleft, INPUT);
  pinMode(IRright, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(button)==LOW){
    mode=0;
    while (true){
      digitalWrite(trig,LOW);
      delayMicroseconds(2);
      digitalWrite(trig,HIGH);
      delayMicroseconds(10);
      digitalWrite(trig,LOW);
      duration=pulseIn(echo,HIGH);
      distance=duration*0.017;
      if (distance>15){
        if (digitalRead(IRleft)==LOW && digitalRead(IRright)==LOW){
          motorMove(100,100);
        }else if (digitalRead(IRleft)==HIGH){
          motorMove(-100,100);
        }else if (digitalRead(IRright)==HIGH){
          motorMove(100,-100);
        }
      }else{
        if (mode<2){
          motorMove(0,0);
          while (distance<15){
            tone(8, 523, 4);
            digitalWrite(trig,LOW);
            delayMicroseconds(2);
            digitalWrite(trig,HIGH);
            delayMicroseconds(10);
            digitalWrite(trig,LOW);
            duration=pulseIn(echo,HIGH);
            distance=duration*0.017;
          }
          noTone(8);
        }else{
          motorMove(0,0);
          break;
        }
        mode++;
      }
    }
  }

}
