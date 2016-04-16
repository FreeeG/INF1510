//15.april
//uDimbar lysrekke med 6 leds 3 gronne 2 gule 1 rod.

const int rod = 11;  
const int gul2 = 10;
const int gul1 = 9;
const int gronn3 = 6;
const int gronn2 = 5;
const int gronn1 = 3;


void setup() {
  // put your setup code here, to run once:
  pinMode(rod, OUTPUT);
  pinMode(gul2, OUTPUT);
  pinMode(gul1, OUTPUT);
  pinMode(gronn3, OUTPUT);
  pinMode(gronn2, OUTPUT);
  pinMode(gronn1, OUTPUT);
}

void trigger(int a) { //Skrur av eller paa en port avhengig av current state
  if(digitalRead(a)==HIGH){
    digitalWrite(a, LOW);
  }else{
    digitalWrite(a, HIGH);
  }
}

void on(int a) { //Skru paa en port
  digitalWrite(a, HIGH);
}
  
void off(int a) { // Skru av en port
  digitalWrite(a, LOW);  
}
int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  
 delay(300);
 i=i+100;
 delay(300);

  if(i>200){
    on(gronn1);
    if(i>400){
      on(gronn2);
      if(i>600){
        on(gronn3);
        if(i>700){
          on(gul1);
          if(i>800){
            on(gul2);
            if(i>900){
              on(rod);
            }
          }
        }
      }
    }
  }
}
