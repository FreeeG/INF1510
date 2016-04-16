const int rgbR = 11;
const int rgbG = 9; 
const int rgbB = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(rgbR, OUTPUT);
  pinMode(rgbG, OUTPUT);
  pinMode(rgbB, OUTPUT);
}

int valueFade = 0;
int fadeValue = 255 ;
  
void loop() {
  setColor(0,0,255);
  delay(1000);
  decreaseBlue(255,20);
  increaseRed(0,20);
}


void decreaseBlue(int fadeValue, int vent){
  while ( fadeValue > 0 ) {   
    fadeValue -= 1;
    setColor(0,0,fadeValue);
    delay(vent);
  }  
}

void increaseRed(int fadeValue, int vent){
   while (fadeValue < 255) {
    fadeValue += 1;
    setColor(fadeValue,0,0);
    delay(30);
  } 
  
}

void setColor(int red, int green, int blue){
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(rgbR, red);
  analogWrite(rgbG, green);
  analogWrite(rgbB, blue);  
}
