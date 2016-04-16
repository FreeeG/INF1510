 #define rfReceivePin A0  //RF Receiver pin = Analog pin 0
 #define ledPin 13        //Onboard LED = digital pin 13

unsigned int data = 0;   // variable used to store received data
const unsigned int upperThreshold = 600;  //upper threshold value
const unsigned int lowerThreshold = 200;  //lower threshold value
int tell = 0;
long prevMillis = 0;
int rod = 2;
int gronn = 6;
 
 void setup(){
   pinMode(ledPin, OUTPUT);
   pinMode(rod, OUTPUT);
   pinMode(gronn, OUTPUT);
   digitalWrite(gronn, LOW);
   digitalWrite(rod, LOW);
   Serial.begin(9600);
 }

 void loop(){
   data=analogRead(rfReceivePin);    //listen for data on Analog pin 0
   
    if(data>upperThreshold){
     digitalWrite(ledPin, LOW);   //If a LOW signal is received, turn LED OFF
     Serial.println(data);
    
   }
   
   if(data<lowerThreshold){       
     digitalWrite(ledPin, HIGH);   //If a HIGH signal is received, turn LED ON
     Serial.println(data);
     if(tell==0 && millis()-prevMillis > 3000){
      digitalWrite(rod, HIGH);
      ok();
     }
     if(tell == 1 && millis()-prevMillis > 3000){ //Add more ifs for more buttons or lights
      digitalWrite(gronn, HIGH);
      ok();
     }
   }
 }
void ok(){
    prevMillis = millis();
    tell++;
}
 
