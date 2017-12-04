#include "IRremote.h"
#include <Servo.h>

  int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
 int sensorValue = 50;
 int Servo_Pin = 10;
 int ledPinRed = 7;
 int ledPinBlue = 8;
 int ledPinGreen = 9;
 int led[] = {7,8,9};
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
Servo myservo;


void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
pinMode(ledPinRed, OUTPUT);
pinMode(ledPinGreen, OUTPUT); 
pinMode(ledPinBlue, OUTPUT); 
//  
  for(int i=0; i< 3; i++){
  pinMode(led[i], OUTPUT);
  }
  irrecv.enableIRIn(); // Start the receiver
  myservo.attach(10);
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received
// describing Remote IR codes 

{
  Serial.println(results.value);
  switch(results.value)

  {

  case 0xFD8877: 
  Serial.println("UP");
  controlSpk("UP") ; 
  break;
  case 0xFD28D7: 
  Serial.println("LEFT"); 
  controlSpk("LEFT");
  break;
  case 0xFDA857: 
  Serial.println("OK");
  controlSpk("OK");
  break;
  case 0xFD6897: 
  Serial.println("RIGHT");
  controlSpk("RIGHT");
  break;
  case 0xFD9867:
  Serial.println("DOWN");
  controlSpk("DOWN");
  break;
  case 0xFD00FF: Serial.println(" 1");    break;
  case 0xFF9867: Serial.println(" 2");    break;
  case 0xFFB04F: Serial.println(" 3");    break;
  case 0xFF30CF: Serial.println(" 4");    break;
  case 0xFF18E7: Serial.println(" 5");    break;
  case 0xFF7A85: Serial.println(" 6");    break;
  case 0xFF10EF: Serial.println(" 7");    break;
  case 0xFF38C7: Serial.println(" 8");    break;
  case 0xFF5AA5: Serial.println(" 9");    break;
  case 0xFF42BD: Serial.println(" *");    break;
  case 0xFF4AB5: Serial.println(" 0");    break;
  case 0xFF52AD: Serial.println(" #");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case


  delay(1); // Do not get immediate repeat

}

  void controlSpk(String button){  

  if(button == "UP"){ 
  digitalWrite(ledPinRed, 10);         
      sensorValue =90;
  }
  if(button == "DOWN"){
      digitalWrite(ledPinGreen, 50);         
      sensorValue =0; 
  }
  if(button == "RIGHT"){
      digitalWrite(ledPinBlue, 50);         
      sensorValue =0;
  }
  if(button == "LEFT"){
      digitalWrite(ledPinRed, 10);         

      sensorValue =180; 
  }
  if(button == "OK"){
          digitalWrite(ledPinBlue, 50);         
      sensorValue =0; 
  }
  Serial.println(sensorValue);
  myservo.write(sensorValue); 
}
