//Bibiliotek
  #include <stdio.h> //Blaatann
  #include <stdlib.h> //Blaatann
  #include <Servo.h> //Servo
  #include <SoftwareSerial.h> //RX, TX
//Bibiliotek

//Rotary encoder
 const int rotA = 3;  //Pin A til ground(C)
 const int rotB = 4;  //Pin B til ground(C)
 int encoderPosCount = 46; //lagrer vridningsverdien
 int rotALast; //Hvilken amp har pinA fra rot encoder i det vi starter sketchen
 int aVal; //PinA´s naavaerende possisjon
 boolean bCW;  //Hvilken retning går encoderen?
//Rotary encoder

//Servo-motor
  Servo kompass;
//Servo-motor

//Vibrasjons-motor
  const int vibrator = 2;
//Vibrasjons-motor

//Blaatann
  char incomingByte;
  const char venstre = 2;
  const char hoyre = 9;
  const char x = 'f';
  const char o = 'v';
  SoftwareSerial mySerial(0, 1); // RX, TX
//Blaatann


//RGB-LED
  const int rgbR = 11;
  const int rgbG = 9; 
  const int rgbB = 10;
//RGB-LED

//Ymis Instr.
  unsigned long prevMillis;
  int i = 1; // teller
  //Aksepter/Intterface knapp.
//Ymis Instr.

void setup() {
  pinMode (rotA,INPUT); // Rotary encoder
  pinMode (rotB,INPUT); // Rotary encoder

  pinMode(rgbR, OUTPUT); //RGB-LED
  pinMode(rgbG, OUTPUT); //RGB-LED
  pinMode(rgbB, OUTPUT); //RGB-LED

  pinMode (vibrator,OUTPUT); // VibrasjonsMottor

  //Blaatann snakker med TX/RX og trenger derfor ikke initialiseres eller deklareres

  kompass.attach(8); // Designer port for modServo
  kompass.write(46); //Initialliser uten momentum

  rotALast = digitalRead(rotA); // Sett encoderens start possisjon
  Serial.begin(9600); //Seriel port read på 9600
}

void farge(int rod, int gronn, int blaa){
   #ifdef COMMON_ANODE
    rod = 255 - rod;
    gronn = 255 - gronn;
    blaa = 255 - blaa;
  #endif
  analogWrite(rgbR, rod);
  analogWrite(rgbG, gronn);
  analogWrite(rgbB, blaa);
}

void gul(){ //Deffinerer fargen gul
  fargeBlink(180, 255, 0);
}

void gronn(){ //Deffinerer fargen gronn
  fargeBlink(0,255,0);
}

void rod(){ //Deffinerer fargen rod
  fargeBlink(255,0,0);
}

void analogOff(){ //AnalogWriter med null som parrametere for aa skru av fargen som evt er paa
  farge(0,0,0);
}


void fargeBlink(int rod, int gronn, int blaa){
  if(analogRead(rgbR) || analogRead(rgbG) || analogRead(rgbB) >= 0){
    analogOff();
  }else{
    farge(rod,gronn,blaa);
  }
}

void vibrer(){ //telefon ring
  digitalWrite(vibrator, HIGH);
  delay(500);
  digitalWrite(vibrator, LOW);
  delay(500);
  digitalWrite(vibrator, HIGH);
  delay(500);
  digitalWrite(vibrator, LOW);
  delay(500);
  digitalWrite(vibrator, HIGH);
  delay(500);
  digitalWrite(vibrator, LOW);
  delay(500);
  digitalWrite(vibrator, HIGH);
  delay(500);
  digitalWrite(vibrator, LOW);
  delay(500);
}



void vib(int c){
  while(i<=3){
    
    if(i>=3){
      //c= c*1.5;
    }
    
    digitalWrite(vibrator, HIGH);
    delay(c/8);
    digitalWrite(vibrator, LOW);
    delay(c);
    i++;
  }
}

void vib1(int c){
  while(i<=4){
    
    if(i>=3){
      //c= c*1.5;
    }
    
    digitalWrite(vibrator, HIGH);
    delay(c/8);
    digitalWrite(vibrator, LOW);
    delay(c*1.5);
    i++;
  }
}


void vib2(int c){
  while(i<=4){
    
    if(i==3){
      c= c*4;
    }else if(i==4){
      
    }
    
    digitalWrite(vibrator, HIGH);
    delay(c/8);
    digitalWrite(vibrator, LOW);
    delay(c*1.5);
    i++;
  }
}

String a = "hehe";

void loop() {

 vib2(400);


 
 if( Serial.available() > 0 ){ // if data is available to read
   incomingByte = Serial.read();
   Serial.print(incomingByte);
   if(incomingByte=='2'){ //Venstre
     kompass.write(30);
   } else if(incomingByte== '9'){ //Hoyre
     kompass.write(60);
   }else if(incomingByte== 'f'){ //Start
     digitalWrite(vibrator, HIGH);
     kompass.write(46);
   }else if(incomingByte== 'v'){ //Maal
     digitalWrite(vibrator, LOW);
     kompass.write(46);
   }
 }
 if(millis()-prevMillis > 70) {
   kompass.write(46);
   prevMillis = millis();
  }
}
