//red go to 5V
//yellow go to gnd
//orange go to input
#include <Servo.h>

Servo servo1; 


void setup() {
  servo1.attach(A0); //analog pin 0
  //servo1.setMaximumPulse(2000);
  //servo1.setMinimumPulse(700);
  Serial.begin(19200);
  Serial.println("Ready");

}

void loop() {  
  servo1.write(0);
  delay(1000);
  servo1.write(90);
  delay(1000);
  servo1.write(180);
  delay(1000);
} 


