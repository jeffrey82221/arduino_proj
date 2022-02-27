#include <Timer.h>

Timer tcb;
unsigned long count = 10;
void writeToSerial(){
   Serial.println(count);
   count--; 
}

void setup(){
 Serial.begin(115200);
 tcb.every(1000,writeToSerial);
}

void loop(){
 if(count>=0){
   tcb.update(); 
 }
}
