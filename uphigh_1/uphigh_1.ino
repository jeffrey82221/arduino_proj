//In this motor control code : 
//there are 2 way(mode) to relate the motor speed and the wheel speed
//the wheel speed is measure by the optical sensor that are able to cature the wheel rotation every time the occlusion happens
//In the first mode : the motor speed are associate with the rotate count of the wheel in a "Linear Increasing Exponential Decreasing" Way
//In the second mode : the motor speed are proportion to the wheel rotation speed. the speed are smoothed in order to get better result.
// the speed are caculate in every wheel rotation oclussion, however, if the occulsion happend to late, the caculate speed automatically decrease! 

//In functionality of each const parameter are explained namely alighted with the code
// we can try to alter them in order to get more pleasing visual effect to user by experiment.


//decaration of Pin 
const int optic = A3;
const int motorPin = 3;
const int switchoffPin = 4;
const int switchPin = 5;

//initialize global parameter
float count = 0; //count of the wheel rotation
int timmer = 0; //the timer count to measure the stopping time of the wheel
int loop_count = 0; // the loop count to measure the time period
float time_period = 0; //the time period to caculate the speed of the wheel 
bool state = false; //the state of the optic sensor FSM 

//inistialize global const
const float decrease_rate = 2; //the decrease rate of the motor after stopping 
const float count_upper_limit = 100; // the upper limit of the motor speed 
const float stopping_time = 100; //the time that start to decrease the motor speed
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(optic,INPUT);
  //pinMode(8,OUTPUT);//IN4
  //pinMode(7,OUTPUT);//IN3
  pinMode(motorPin,OUTPUT);
  pinMode(switchoffPin, INPUT); //switch input => off
  pinMode(switchPin, INPUT); //switch input => mode 1 (motor change by count) , else => mode 2 (motor change by speed)
 
}

float motor_function_1(float count){
  static const float ratio = 10;
  return count*ratio;
}
float motor_function_2(float speed_){
  static const float ratio = 10;
  return speed_*ratio;
}
float speed_convert(float time_period){
  static const float circum = 100; 
  return circum/(time_period+1);
}
float temperal_speed_smoothing(float speed_){
  static const int window = 5;
  static float speed_que[window];
  float sum = 0;
  //shifting the que
  for(int i=0;i<window-1;i++){
    speed_que[i] = speed_que[i+1];
  }
  speed_que[window-1]=speed_;
  //caculated the smoothed average 
  for(int i=0;i<window;i++){
    sum += speed_que[i];
  }
  return sum/(float) window;
  //return speed_;
}
void loop() {
  
  timmer++;
  loop_count++;

  // the finite state machine the detect the negative triggering/////////////////////////
  if(digitalRead(optic)==LOW&state==false){
    state = false;
      
  }else if(digitalRead(optic)==HIGH&state==false){
    state = true;
  }else if(digitalRead(optic)==LOW&state==true){ //do the counting
    state = false;
    if(count<count_upper_limit){
      count++;
      time_period = loop_count;
      loop_count=0;
    }
    timmer==0;
  }else if(digitalRead(optic)==HIGH&state==true){
    state = true;
  }
  ////////////////////////////////////////////////////////////////////////////////////////
  //decreasing the motor speed if stopping too long
  if(timmer>stopping_time){
    timmer = 0;
    if(count>0) count/=decrease_rate;
  }
  ///////////////////////////////////////////////////////////////////////////////////////
  //Serial.print(temperal_speed);
  //switching control and output value processing
  if(digitalRead(switchoffPin)){
    //mode 0 : off
    Serial.print("I am off!");
  }else if(digitalRead(switchPin)){
    //mode 1 : linear increasing exponential decreasing 
    Serial.print("mode 1:");
    Serial.print(motor_function_1(count));
    analogWrite(motorPin, motor_function_1(count)); // the speed of motor should be a custom function of "count"
  }else{
    //mode 2 : proportional to speed 
    Serial.print("mode 2:");
    float instant_speed = speed_convert(loop_count);
    float temperal_speed = temperal_speed_smoothing(speed_convert(time_period));
    if(instant_speed<temperal_speed){
      //decreasing the speed 
      Serial.print(count==0?0:motor_function_2(instant_speed));
      analogWrite(motorPin, count==0?0:motor_function_2(instant_speed)); // the speed of motor should be a custom function of "count"
      //NOTE: in the beginning, to prevent outputting large speed, we use count == 0 as a reference. 
      // if count = 0 , there should not be any speed. However, since loop_count is very small, the division will be very large, giving large speed,
      // and it is not reasonable to speed motor up in the first place while no any wheel rotation. 
    }else{
      //smoothed speed     
      Serial.print(motor_function_2(temperal_speed));
      analogWrite(motorPin, motor_function_2(temperal_speed)); // the speed of motor should be a custom function of "count"
    }
  }
  
  Serial.println();
 
}
