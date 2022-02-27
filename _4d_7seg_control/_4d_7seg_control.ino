void set7Seg(int number, int pos);

const int pinState[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
};
int count = 0;
void setup() {
    for(int i = 3; i < 14; i++) {
       pinMode(i, OUTPUT);
    } 
   
}


void loop() {

    numberto4seg(count++);
    if(count > 9999){
      count = 0;
    }
    //set7Seg(8,1);
    //set7Seg(9,2);
    //set7Seg(8,3);
    //set7Seg(8,4);
  
}

void numberto4seg(int number){
    int a1 = number/1000;
    int a2 = (number/100)%10;
    int a3 = (number/10)%10;
    int a4 = (number/1)%10;
    set7Seg(a1, 4); 
    set7Seg(a2, 3); 
    set7Seg(a3, 2);
    set7Seg(a4, 1);
}

void set7Seg(int number, int pos) {
    for(int i = 10; i < 14; i++) {
        digitalWrite(i, 1);
    }

    for(int i = 0;i < 7;i++) {
        digitalWrite(i + 3, pinState[number][i]);
    }

    digitalWrite(pos + 9, 0);
    delay(5);
}
