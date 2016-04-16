//16.April
//Vibrator pulsering
//Dimbar lysrekke med 6 leds 3 gronne 2 gule 1 rod.

const int rod = 11;  
const int gul2 = 10;
const int gul1 = 9;
const int gronn3 = 6;
const int gronn2 = 5;
const int gronn1 = 3;
const int vibrator = A0;

void setup() {
  pulse(vibrator, 3); //kort pulse av vibratoren
  pulse(vibrator, 3);
  pulse(vibrator, 3);
  delay(5000); //vent 5 sekunder
  increase(gronn1,80);
  increase(gronn2,25);
  increase(gronn3,27);
  increase(gul1,30);
  increase(gul2,40);
  increase(rod,45);
}

void pulse(int a, int b){ // dim opp og ned a=hva b = delay
  increase(a,b);
  delay(30);
  decrease(a,b);
}

void increase(int a, int b){ //oek a(hva) delay paa B
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    analogWrite(a, fadeValue);
    delay(b);
  } 
}

void decrease(int a, int b){ //senk a(hva) delay paa B
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    analogWrite(a, fadeValue);
    delay(b);
  }
}

void on(int a) { // Skru paa A
  digitalWrite(a, HIGH);
}

void loop() {

}
