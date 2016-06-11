//Bibiliotek
  #include <stdio.h> //Blaatann
  #include <stdlib.h> //Blaatann
  #include <Servo.h> //Servo
  #include <SoftwareSerial.h> //RX, TX
//Bibiliotek

//Rotary encoder
 const int rotA = 3;  //Pin A til ground(C)
 const int rotB = 4;  //Pin B til ground(C)
 int enc = 0; //lagrer vridningsverdien
 int rotLast; //Hvilken amp har pinA fra rot encoder i det vi starter sketchen
 int aVal; //PinA´s naavaerende possisjon
 boolean retning;  //Hvilken retning går encoderen? 
//Rotary encoder

//Servo-motor
  Servo kompass;
  #define STOP 71.999
  #define VENSTRE 56
  #define HOYRE 84
//Servo-motor

//Vibrasjons-motor
  const int vibrator = 2;
  boolean vibrere = false;
  unsigned long vibrMillis;
  int vibrTid = 0;
  int vibrTeller = 0;
  boolean vibBoolean = false;
//Vibrasjons-motor

//Blaatann
  char incomingByte;
  const char venstre = 2;
  const char hoyre = 9;
  const char x = 'f';
  const char o = 'v';
  const char naer = 'n';
  const char lengre = 'l';
  SoftwareSerial mySerial(0, 1); // RX, TX
//Blaatann


//RGB-LED
  const int rgbR = 11;
  const int rgbG = 9; 
  const int rgbB = 10;
//RGB-LED

//Variabler for avstand
  int avstand;
  unsigned long fargeMillis = millis(); //egen millis for blinke delay
  int blinkDelay = 0; //variabel som blir styrt i metode senere, settes til default 0
  boolean fargeSjekk = false; //boolean som sjekker om lysene er paa eller av. Brukes til aa styre blinking
  String avstandsModus;
//Variabler for avstand

//variabler for rutervalg:
  boolean kjoer = false;
//variabler for rutervalg:

//Ymis Instr.
  boolean trykket = false;
  unsigned long prevMillis; //Millis paa lys
  int i = 1; // teller
  int knapp = 13; //Aksepterknapp
//Ymis Instr.



void setup() {
  pinMode (rotA,INPUT); // Rotary encoder
  pinMode (rotB,INPUT); // Rotary encoder
  rotLast = digitalRead(rotA); // Sett encoderens start possisjon

  pinMode(rgbR, OUTPUT); //RGB-LED
  pinMode(rgbG, OUTPUT); //RGB-LED
  pinMode(rgbB, OUTPUT); //RGB-LED

  pinMode(vibrator,OUTPUT); // VibrasjonsMottor
  
  pinMode(knapp, INPUT); //Akseptanseknapp
  
  kompass.attach(8); // Designer port for modServo
  kompass.write(STOP); //Initialliser uten momentum
  
  //Blaatann snakker med TX/RX og trenger derfor ikke initialiseres eller deklareres
  Serial.begin(9600); //Seriel port read på 9600
  //regnbue();
}

void loop() {
  
  if( Serial.available() > 0 ){ // if data is available to read
    incomingByte = Serial.read();
    Serial.print(incomingByte);
    if(incomingByte=='q' || 'r' || 'x'){ //Maa velge vansklighetsgrad forst.
       
      vanskelighet(incomingByte);
      
      if(incomingByte=='s'){ //Start testrute
        startRute(); // start testrute med testparameter: int avstand
      }
    } 
  }
}

void vanskelighet(char x){
  if(x =='q'){  //rod
    farge(255,0,0);
  }
  else if(x =='r'){ //gul
    farge(248,255,0);
  }
  else if(x =='x'){ //gronn
    farge(0,255,0);
  }
  for(int i1 = 0; i1<3; i1++){
    digitalWrite(vibrator, HIGH);
    delay(500);
    digitalWrite(vibrator, LOW);
    delay(500);
  }

  while(!trykket){
    incomingByte = Serial.read();
    if(incomingByte=='s'){
      trykket = true;
      for(int i1 = 0; i1<3; i1++){
        farge(0,0,255);
        delay(250);
        analogOff();
        delay(250);
      }
      avstand = 2000; // Testtur med en gitt avstand paa 1500 meter 
      startRute(); //Starter testrute
    }
  }
}
void startRute () {
  kjoer = true;
  while (kjoer) {
    receiveSignal();
    avstandsFeedback (avstand); //bestemmer hvilket lys som skal blinke og hvor fort det skal blinke basert paa avstand
    ventLys();
    ventKompass();
 }
}

void receiveSignal(){
  if( Serial.available() > 0 ){ // if data is available to read
    incomingByte = Serial.read();
    Serial.print(incomingByte);
    if(incomingByte=='2'){ //Venstre
      kompass.write(VENSTRE);
    } else if(incomingByte== '9'){ //Hoyre
      kompass.write(HOYRE);
    } else if(incomingByte == 'n') { //Naermere med 25m
       avstand -= 25;
    } else if(incomingByte == 'l') { //Lenger unna med 25m
       avstand += 25;
    } else if(incomingByte== 'f'){ //Start
       digitalWrite(vibrator, HIGH);
       kompass.write(STOP);
    } else if(incomingByte== 'v'){ //Maal
       digitalWrite(vibrator, LOW);
       kompass.write(STOP);
    }
  }
}

void ventKompass(){ //"delay paa 70ms
  if(millis()-prevMillis > 70) {
    kompass.write(STOP);
    prevMillis = millis();
  } 
}

void ventLys(){
  if (vibrere == true) {
        if (millis()-vibrMillis < vibrTid) {
          vibratorMetode (true);
        } else {
          vibratorMetode (false);
        }
    }
}

//Feedback for avstander:
void avstandsFeedback (int avstand) {

//setter riktig fargemodus iforhold til avstand, og vibrerer dersom den har byttet fargemodus:
  if (avstand >= 1500) { //avstandsmodus rod
    if (!avstandsModus.equals("rod") && vibrere == false) {
      vibrMillis = millis();
      vibrTid = 50;
      vibrere = true;
    }
    avstandsModus = "rod";
  } else if (avstand < 1500 && avstand > 500) { //avstandsmodus gul
    if (!avstandsModus.equals("gul") && vibrere == false) {
      vibrMillis = millis();
      vibrTid = 50;
      vibrere = true;
    }
    avstandsModus = "gul";
  } else if (5 < avstand && avstand <= 500) { //avstandsmodus gronn
    if (!avstandsModus.equals("gronn") && vibrere == false) {
      vibrMillis = millis();
      vibrTid = 50;
      vibrere = true;
    }
    avstandsModus = "gronn";
  } else if (avstand < 5) {
    for(int i2 = 0; i2<4; i2++){
      kompass.write(VENSTRE);
      digitalWrite(vibrator, HIGH);
      delay(500);
      digitalWrite(vibrator, LOW);
      delay(500);
    }
    analogOff();
    kjoer = false;
    avstandsModus = "";
  }

  
  //Setter riktig blinking iforhold til avstand og fargemodus:
  if (avstandsModus.equals("rod")) {
    blinkDelay = avstand - 1500; //skal blinke fort dersom avstand er lav til neste modus
    
    if ((millis()-fargeMillis) > blinkDelay) {
      fargeMillis = millis();
      rod();
    }
    
  } else if (avstandsModus.equals("gul"))  {
    blinkDelay = avstand - 500; //skal blinke fort dersom avstand er lav til neste modus
    
    if ((millis()-fargeMillis) > blinkDelay) {
      fargeMillis = millis();
      Serial.println(avstand);
      gul();
    }
  } else if (avstandsModus.equals("gronn"))  {
    blinkDelay = avstand; //skal blinke fort dersom avstand er lav til neste modus
    
    if ((millis()-fargeMillis) > blinkDelay) {
      fargeMillis = millis();
      Serial.println(avstand);
      Serial.println(avstandsModus);
      gronn();
    }
  }
}

void regnbue(){
  while(true){
    unsigned int rgbColour[3];

    // Start off with red.
    rgbColour[0] = 255;
    rgbColour[1] = 0;
    rgbColour[2] = 0;  

  // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;
      
      farge(rgbColour[0], rgbColour[1], rgbColour[2]);
      delay(2);
    }
  }
  }
}


void farge(unsigned int rod, unsigned int gronn, unsigned int blaa){
   /*#ifdef COMMON_ANODE
    rod = 255 - rod;
    gronn = 255 - gronn;
    blaa = 255 - blaa;
  #endif*/
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
  if(fargeSjekk == true){
    analogOff();
    fargeSjekk = false;
  }else if (fargeSjekk == false){
    farge(rod,gronn,blaa);
    fargeSjekk = true;
  }
}

//metode for vibrator:
void vibratorMetode (boolean kjoer) {
  if (kjoer) {
    digitalWrite(vibrator, HIGH);
  } else {
    digitalWrite(vibrator, LOW);
    vibrere = false;
  }
}
