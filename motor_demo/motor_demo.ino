//2016/3/10 : adding switching to motor constrol 

int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT); //motor control output 
  pinMode(4, INPUT); //switch input => off
  pinMode(5, INPUT); //switch input => half light , else => full light
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(4)){
    Serial.println("dark");
    analogWrite(3, 0 );
  }else if(digitalRead(5)){
    analogWrite(3, 50 );
    Serial.println("light");

  }else{
    analogWrite(3, 255 );
    Serial.println("more light");
  }

}

//10 : not moving
//20~90 : moving slow, no automatic start 
//90~ 255: moving fast, automatic start 

//problem review: 
//need real 12 V input for motor driver
//need to have common gnd between arduino and motor driver 


