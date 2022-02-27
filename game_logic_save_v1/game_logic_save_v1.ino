
#include <LiquidCrystal.h>
#include <Timer.h> //download and install Timer.h package! 
#include <TimerOne.h>


/*************************************************
 * Definition and function for Beeping !!!!
 *************************************************/
 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
//#define melodyPin A2

//decaration of Pin
const int optic = A1;
const int melodyPin = A2;
const int buttom = A3;
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//inistialize global const
const int start_second = 10; //the starting count down second of the game (should be set to 15*60 second by rule)

//initialize global parameter and classes
Timer tcb;
volatile bool buttom_value = false; 
int count = 0;
int count_down_second = start_second; //set the count down second parameter to the initial state 
bool state = false; // state of the wheel optic sensor FSM 
bool timer_counting = false;
bool buzz_stopped_phase = false;

//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
 
void sing(int s) {
  // iterate over the notes of the melody:
  int song = s;
  if (song == 2) {
    //Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      noInterrupts();
      if(buttom_value==true) break;
      interrupts();
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];
 
      buzz(melodyPin, underworld_melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
 
    }
 
  } else {
 
    //Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      noInterrupts();
      if(buttom_value==true) break;
      interrupts();
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];
 
      buzz(melodyPin, melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
 
    }
  }
}
 
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
 
}
///////////////////beeping//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////  

void lcd_display(int count_down_second){
  //this function convert the value in second to the time display formate of time with minus and second
  lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
  int m = count_down_second/60;
  int s = count_down_second%60;
  //Serial.print(count_down_second);
  lcd.print(m/10);
  lcd.print(m%10);
  lcd.print(':');
  lcd.print(s/10);
  lcd.print(s%10);  
}
void timer_do(){
   lcd_display(count_down_second);//the count down display operation are executed with interupt with an timer 
   if(timer_counting) count_down_second--;//the count down should only be in exercise phase.
}

void blinking_detecting_thread(void){
   // as we set blinking in an inturpt timmer function, we can view it as an new thread parallel to the main loop
   static bool light = true;
   static int cnt = 0;
   static const int duration = 1000; // duration of blinking interval 
   cnt++;
   //FSM of blinking : goes from on <--> off with cnt as duration
   if(light&cnt>duration){
      lcd.noDisplay();
      light=false;
      cnt=0;

   }else if(!light&cnt>duration){
      lcd.display();    
      light=true;
      cnt=0;
   }
   //detecting also occure here! 
  buzz_stop_detection();//detection of exercise end phrase -> buzz silence phase. 
  //in the parallel thread of main loop, we also do the detection of buttom with the blinking interupt function 
}
void restart_detection(void){
  //FSM of buttom pressing detection
  static bool st = false; 
  if(digitalRead(buttom)==LOW&st==false){
      st = false;
       buttom_value = false;
   }else if(digitalRead(buttom)==HIGH&st==false){
      st = true;
      buttom_value = false;
   }else if(digitalRead(buttom)==LOW&st==true){ 
      st = false;
      buttom_value = true;
   }else if(digitalRead(buttom)==HIGH&st==true){
      st = true;
      buttom_value = false;
   }
}
void buzz_stop_detection(void){
   
   if(digitalRead(buttom)==HIGH){
     while(digitalRead(buttom)==HIGH){

     }//detection of HIGH to LOW
     buttom_value = true; //controlling the on/off of buzzing sound
   }
}
void setup()
{
 pinMode(optic,INPUT);
 pinMode(melodyPin, OUTPUT);//buzzer
 pinMode(buttom,INPUT);//buttom

 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Rounds:"); // print a simple message
 lcd.setCursor(0,1);
 lcd.print("Time:");
 tcb.every(1000,timer_do); //the timer implemented by interupt (in another thread!) 
 //blinking_timmer.every(1000,blinking);

}
void loop()
{
 //Control of Display 
 if(buzz_stopped_phase==false){
  
   lcd.setCursor(9,0);
   lcd.print(count);
   
   //Sensing the wheel and count (optic detection)
   //FSM for constrolling the count
    if(digitalRead(optic)==LOW&state==false){
      state = false;
        
    }else if(digitalRead(optic)==HIGH&state==false){
      state = true;
    }else if(digitalRead(optic)==LOW&state==true){ //do the counting
      state = false;
      count++;
    }else if(digitalRead(optic)==HIGH&state==true){
      state = true;
    }
  
   if(count_down_second>=0&&count>0){
     //while the wheel sensor detected, we enter the timer_counting phase 
     //after the count_down_second count to 0, enter the exercise end phase
     timer_counting = true;
     //every loop, the timmer should be executed
     tcb.update();
   }else{
     if(count==0){//begining of the game : starting phase
       //In the beginning, we are in starting phase, and we are trying to detect the wheel starting here
       //the optic detectiong are still running in the same loop
     }else{ //times up : entering exercise end phase
       timer_counting = false; //timer_counting set to zero, so the timmer will stop counting!
       //do the blinking very 1000 ms with interupt timmer
       // as we set blinking in an inturpt timmer function, we can view it as an new thread parallel to the main loop
       // we need an new thread because the main loop are paused to execute the singing function which are coded with serial sense!
       Timer1.initialize(1000); 
       Timer1.attachInterrupt(blinking_detecting_thread); // blinkLED to run every 0.15 seconds
       
       while(!buttom_value){       
         // the main loop paused here to execute singing! 
         // once the buttom pressing are detected in the blinking-detection thread, the while loop break ! 
         sing(1);//beeping here! 
       }
       delay(10000);
       // here we set the buttom value to LOW again to prepare for the next round. 
       noInterrupts();
       buttom_value = false;
       interrupts();
       Timer1.stop();
       Timer1.detachInterrupt();

       //once the while loop break, it means that the buzzer are silence, as well as the "blinking-detection" thread is stopped.
       //the main loop entered the buzz stopped phase, which are coded in the next "else" scope!
       buzz_stopped_phase = true;
       lcd.display();    //lcd should not be dark while the blinking phase are pass
     }
   }
 }else{ //buzz_stopped_phase = true
   //Serial.print('enter buzz_stopped_phase');
   //in this phase , we are waiting the stop buttom to be pressed. and the game can restart!
   Timer1.initialize(1000);
   Timer1.attachInterrupt(restart_detection); 
   Timer1.restart();

   if(buttom_value){
     buzz_stopped_phase = false;
     Timer1.stop();
     Timer1.detachInterrupt();
     //TODO:re-initialize the motor controll associate parameter, lcd-display, count down second here
     count = 0;

     //count down restart 
     count_down_second = start_second;
     //lcd restart
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Rounds:"); // print a simple message
     lcd.setCursor(0,1);
     lcd.print("Time:");
     timer_counting = true;
     noInterrupts();
     buttom_value = false;
     interrupts();
   }
 }
   
 
 //analogWrite(2, count*10 );

 //lcd_key = read_LCD_buttons();  // read the buttons
 //lcd.print(); 
}


