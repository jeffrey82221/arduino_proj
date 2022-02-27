
#include <LiquidCrystal.h>
#include <Timer.h> //download and install Timer.h package! 
#include <TimerOne.h>

volatile bool buttom_value = false; 

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
 
#define melodyPin A2
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


Timer tcb;

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


// define some values used by the panel and buttons

const int optic = A1;
const int buttom = A3;
int count = 0;
const int start_second = 10;
int count_down_second = start_second;
bool state = false;
// read the buttons
void lcd_display(int count_down_second){
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
bool timer_counting = false;
void timer_do(){
   lcd_display(count_down_second);
   if(timer_counting) count_down_second--;
}

void blinking(void){
   static bool light = true;
   static int cnt = 0;
   static const int duration = 1000;
   cnt++;
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
  detection_1();
}
void detection(void){
  static bool st = false; 
  if(digitalRead(buttom)==LOW&st==false){
      st = false;
       buttom_value = false;
   }else if(digitalRead(buttom)==HIGH&st==false){
      st = true;
      buttom_value = false;
   }else if(digitalRead(buttom)==LOW&st==true){ //do the counting
      st = false;
      buttom_value = true;
   }else if(digitalRead(buttom)==HIGH&st==true){
      st = true;
      buttom_value = false;
   }
}
void detection_1(void){
   if(digitalRead(buttom)==HIGH){
     while(digitalRead(buttom)==HIGH){

     }//detection of HIGH to LOW
     buttom_value = true;
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
 tcb.every(1000,timer_do);
 //blinking_timmer.every(1000,blinking);

}
bool stop_state = false;
void loop()
{
 //Control of Display 
 if(stop_state==false){
   lcd.setCursor(9,0);
   lcd.print(count);
   
   //Sensing the wheel and count
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
     timer_counting = true;
     tcb.update();
   }else{
     if(count==0){//begining of the game 
       //do nothing
     }else{ //times up
       timer_counting = false;
       //count_down_second = start_second;
       Timer1.initialize(1000);
       Timer1.attachInterrupt(blinking); // blinkLED to run every 0.15 seconds

       while(!buttom_value){       
         sing(1);//beeping here! 
       }
       delay(1000);
       noInterrupts();
       buttom_value = false;
       interrupts();
       Timer1.stop();
       Timer1.detachInterrupt();
       stop_state = true;
       lcd.display();    

     }
   }
 }else{ //stop_state = true
   //Serial.print('enter stop state');
   Timer1.initialize(1000);
   Timer1.attachInterrupt(detection); 
   Timer1.restart();

   if(buttom_value){
     stop_state = false;
     count_down_second = start_second;
     Timer1.stop();
     Timer1.detachInterrupt();
     count = 0;
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


