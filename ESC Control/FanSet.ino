//READ ME!!!!!!!
// the weird timed high low fan write lines are necisary to initialize the ESC
//This code may only work on th RC Eflight Fucted fan ESC's

#include <Servo.h>
Servo ESC;
int fan;

void setup() {
  Serial.begin(9600);
  fan=0;
  ESC.attach(13,1000,2000);

  while(millis()<3000){
    fan = 255;
    ESC.write(fan);
  }
  while (millis()<6000 && millis()>3000){
    fan = 0;
    ESC.write(fan);
  }
}

void loop() {
  fanSet(fan);
}

void fanSet(int fan){
ESC.write(fan);
}
