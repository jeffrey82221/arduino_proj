#include <dht.h>
#define dht_dpin A0

// sensor variable
dht DHT;
int motionPin = A1;

// outputs
int redPin = 11;
int greenPin = 9;
int bluePin = 10;
int motorPin = 4;

// led brightness
int redVal;
int greenVal;
int blueVal;

// angry last
int angryLa;

void setup() {
  // monitor setup
  Serial.begin(9600);
  Serial.println("Meatball's favorite plant :)\n");

  // led reset to all off
  redVal = 255;
  greenVal = 255;
  blueVal = 255;
  update();
}

// update function for led output
void update(){
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
}

// color change function
void color_change(int R_how, int G_how, int B_how, int time_length){
  for (int i=0; i<255; i++){
      if (i<R_how)  redVal--;
      if (i<G_how)  greenVal--;
      if (i<B_how)  blueVal--;      
    update(); 
    delay(time_length);  
  }
    for (int j=0; j<255; j++){    
      if (j<R_how)  redVal++;
      if (j<G_how)  greenVal++;
      if (j<B_how)  blueVal++;       
    update(); 
    delay(time_length);
  }
}

// emotion condition
//  boolean imJoy = (20.00<DHT.temperature && DHT.temperature<30.00);
//  boolean imHappy = (digitalRead(motionPin) == HIGH);
  
// expressions
void joy(){
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C Status: Joy");
  color_change(2,247,141,10);
}

void angry(){
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C Status: Angry");
  color_change(189,63,0,10);
}

void happy(){
  Serial.println("Status: Happy");
  color_change(255,97,176,10);
}

void sad(){
  Serial.println("Status: Sad");
  redVal = 255;
  greenVal = 255;
  blueVal = 255;
  update();
  }
void loop() {
// read data from sensor
  DHT.read11(dht_dpin);
  
// reaction of the led
  if (digitalRead(motionPin) == HIGH){
    angryLa = 0;
    digitalWrite(motorPin,HIGH);
    for (int t=0;t<3;t++){happy();}
  }
  else{
    digitalWrite(motorPin,LOW);
    if (23.00<DHT.temperature && DHT.temperature<30.00){
      angryLa = 0;
      joy();
    }
    else{
      if (angryLa>=10)
        sad();
      else{
        angry();
        angryLa += 1;
      }
    }
  }
}  
