#include "deltain.h"
#include "step.h"
// ?#include <Servo.h>


#define servoPin = 2;
// Se?rvo servo1;

#define pi = 3.141592653;    // PI

int main(){
motoroff();
  Serial.begin(115200);

  for (int i = 0; i < 3; i++) {
    pinMode(endStop[i],INPUT_PULLUP);
  }
}
void setup() {
  motoroff();
  Serial.begin(115200);

  for (int i = 0; i < 3; i++) {
    pinMode(endStop[i],INPUT_PULLUP);
  }

  // servo1.attach(servoPin);
  // BTS_ON();
  // TCP_ON();

}

void loop() {
  if (Serial.available()) {
    String received = Serial.readStringUntil('\n');
    Serial.println(received);
    command2(received);
  }  
}
