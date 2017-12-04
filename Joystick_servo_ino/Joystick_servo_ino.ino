// Arduino 07 -  Servo, Serial Monitor, and Joystick
//
//This program controls a servo motor continuously 
//according to the input provided from a joystick
//and shows joystick input and output to servo on the screen 
//of an attached computer, via the Arduino Serial Monitor.
// ---------------------------------------------------------------------------

#include <Servo.h>
#define SERVO_PIN 9
#define GROUND_JOY_PIN A3            //joystick ground pin will connect to Arduino analog pin A3
#define VOUT_JOY_PIN A2              //joystick +5 V pin will connect to Arduino analog pin A2
//#define XJOY_PIN A1  
//#define XJOY_PIN A0//X axis reading from joystick will go into analog pin A1
Servo myservo ;
int x = A1;
int y = A0;
void setup() 
{
  Serial.begin(9600);
  pinMode(VOUT_JOY_PIN, OUTPUT) ;    //pin A3 shall be used as output
  pinMode(GROUND_JOY_PIN, OUTPUT) ;  //pin A2 shall be used as output
  digitalWrite(VOUT_JOY_PIN, HIGH) ; //set pin A3 to high (+5V)
  digitalWrite(GROUND_JOY_PIN,LOW) ; //set pin A3 to low (ground)
  myservo.attach(9); 
}

void loop() 
{
  delay(1);                    
  int joystickXVal = analogRead(x) ;  //read joystick input on pin A1
   joystickXVal = analogRead(y) ;  //read joystick input on pin A1

  Serial.print(joystickXVal);                //print the value from A1
  Serial.println(" = input from joystick");  //print "=input from joystick" next to the value
  joystickXVal = map(joystickXVal, 0, 1023, 0, 179);
  Serial.print(joystickXVal);  //print a from A1 calculated, scaled value
  Serial.println(" = output to servo");      //print "=output to servo" next to the value
  Serial.println() ;
  myservo.write(joystickXVal);      //write the calculated value to the servo  
}

