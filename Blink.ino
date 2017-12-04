
int ledPins[] = {2,3,4,5,6,7,8,9};


void setup()
{
  for(int i = 0; i < 8; i++){
      pinMode(ledPins[i],OUTPUT);
  }
}

void loop()
{
  oneAfterAnotherNoLoop();
  //oneAfterAnotherLoop();
  //oneOnAtATime();
  //inAndOut();
}


void oneAfterAnotherNoLoop(){
  int delayTime = 100;
  digitalWrite(ledPins[0], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[1], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[2], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[3], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[4], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[5], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[6], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[7], HIGH);
  delay(delayTime);

//Turns Each LED Off
  digitalWrite(ledPins[7], LOW);
  delay(delayTime);
  digitalWrite(ledPins[6], LOW);
  delay(delayTime);
  digitalWrite(ledPins[5], LOW);
  delay(delayTime);
  digitalWrite(ledPins[4], LOW);
  delay(delayTime);
  digitalWrite(ledPins[3], LOW);
  delay(delayTime);
  digitalWrite(ledPins[2], LOW);
  delay(delayTime);
  digitalWrite(ledPins[1], LOW);
  delay(delayTime);
  digitalWrite(ledPins[0], LOW);
  delay(delayTime);
}


void oneAfterAnotherLoop(){
  int delayTime = 100;
  for(int i = 0; i <= 7; i++){
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
  }

  for(int i = 7; i >= 0; i--){
    digitalWrite(ledPins[i], LOW);
    delay(delayTime);
  }
}

void oneOnAtATime(){
  int delayTime = 100;

  for(int i = 0; i <= 7; i++){
    int offLED = i - 1;
    if(i == 0) {
      offLED = 7;
    }
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[offLED], LOW);
    delay(delayTime);
  }
}

void inAndOut(){
  int delayTime = 100;
  for(int i = 0; i <= 3; i++){
    int offLED = i - 1;
    if(i == 0) {
      offLED = 3;
    }
    int onLED1 = 3 - i;
    int onLED2 = 4 + i;
    int offLED1 = 3 - offLED;
    int offLED2 = 4 + offLED;

    digitalWrite(ledPins[onLED1], HIGH);
    digitalWrite(ledPins[onLED2], HIGH);
    digitalWrite(ledPins[offLED1], LOW);
    digitalWrite(ledPins[offLED2], LOW);
    delay(delayTime);
  }

  //runs the LEDs into the middle
  for(int i = 3; i >= 0; i--){
    int offLED = i + 1;
    if(i == 3) {
      offLED = 0;
    }

    int onLED1 = 3 - i;
    int onLED2 = 4 + i;
    int offLED1 = 3 - offLED;
    int offLED2 = 4 + offLED;

    digitalWrite(ledPins[onLED1], HIGH);
    digitalWrite(ledPins[onLED2], HIGH);
    digitalWrite(ledPins[offLED1], LOW);
    digitalWrite(ledPins[offLED2], LOW);
    delay(delayTime);
  }
}
