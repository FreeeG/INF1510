//16.April
const int rod = 11;  
const int gul2 = 10;
const int gul1 = 9;
const int gronn3 = 6;
const int gronn2 = 5;
const int gronn1 = 3;
const int vibrator = A0;


void setup() {
  pulse(vibrator, 3);
  pulse(vibrator, 3);
  pulse(vibrator, 3);
  delay(5000);
  increase(gronn1,80);
  increase(gronn2,25);
  increase(gronn3,27);
  increase(gul1,30);
  increase(gul2,40);
  increase(rod,45);
  // nothing happens in setup
}

void pulse(int a, int b){
  increase(a,b);
  decrease(a,b);
}

void increase(int a, int b){
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    analogWrite(a, fadeValue);
    delay(b);
  } 
}

void decrease(int a, int b){
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    analogWrite(a, fadeValue);
    delay(b);
  }
}

void on(int a) {
  digitalWrite(a, HIGH);
}

void loop() {
  // fade in from min to max in increments of 5 points:
  

  // fade out from max to min in increments of 5 points:

}
