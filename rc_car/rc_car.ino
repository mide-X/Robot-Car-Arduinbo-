/*Code to control a collision avoiding robot car.
The COMPONENTS used include an Ultrasonic Sensor 
for measuring distance, an IR receiver for decoding remote signals
for controlling the robot car movement.
And two Motors connected to the tyres for movement*/

//Declaring Pins for 2 Motors (H-Bridge)
const int ENAPin = 5; //H-bridge enable pin for motor A
const int ENBPin = 10;//H-bridge enable pin for motor B
const int in1Pin = 9; // H-Bridge input pins
const int in2Pin = 8;
const int in3Pin = 7; // H-Bridge input pins for second motor
const int in4Pin = 6;

//Declaring Pins for Infrared Receiver
#include <IRremote.h>

int RECV_PIN = 13;


IRrecv irrecv(RECV_PIN);

decode_results results;

//Declaring Pins for Ultrasonic Sensor
const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 3; // Echo Pin of Ultrasonic Sensor

//motor control functions i.e. forward, backward, left, right
void left(){
digitalWrite(ENAPin, HIGH);  
digitalWrite(ENBPin, HIGH);
digitalWrite(in1Pin,LOW);
digitalWrite(in2Pin,LOW);
//second motor
digitalWrite(in3Pin,HIGH);
digitalWrite(in4Pin,LOW);
//delay(500);
//return;
}

void right(){
digitalWrite(ENAPin, HIGH);  
digitalWrite(ENBPin, HIGH);
digitalWrite(in1Pin,HIGH);
digitalWrite(in2Pin,LOW);
//second motor
digitalWrite(in3Pin,LOW);
digitalWrite(in4Pin,LOW);
//delay(500);
//return;
}

void backward(){
digitalWrite(ENAPin, HIGH);  
digitalWrite(ENBPin, HIGH);
digitalWrite(in1Pin,LOW);
digitalWrite(in2Pin,HIGH);
//second motor
digitalWrite(in3Pin,LOW);
digitalWrite(in4Pin,HIGH);
//delay(1000);
//return;
}

void forward(){
digitalWrite(ENAPin, HIGH);  
digitalWrite(ENBPin, HIGH);
digitalWrite(in1Pin,HIGH);
digitalWrite(in2Pin,LOW);
//second motor
digitalWrite(in3Pin,HIGH);
digitalWrite(in4Pin,LOW);
delay(100);
//return;
}

void halt(){
digitalWrite(ENAPin, HIGH);  
digitalWrite(ENBPin, HIGH);
digitalWrite(in1Pin,LOW);
digitalWrite(in2Pin,LOW);
digitalWrite(in3Pin,LOW);
digitalWrite(in4Pin,LOW);
}

long microsecondsToInches(long microseconds)
{
return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds)
{
return microseconds / 29 / 2;}

long pinger(){
long duration, inches, cm;
pinMode(pingPin, OUTPUT);
digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);
Serial.print(inches);
Serial.print("in, ");
Serial.print(cm);
Serial.print("cm");
Serial.println();
delay(100);

return cm;
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // Starting Serial Terminal
 Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  // put your main code here, to run repeatedly:


if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
  int Distance= pinger();
switch(results.value){
  case 0x6621:{
  //move forward
 //  for(int i=0; i<10; i++){
   while(pinger() >= 10){
   //if (Distance >= 10){
    forward();
    delay(100);}
    break;
  }
  //else halt();
 // break;}
  //break;}
  
  case 0x2621:{
  //move backward
  backward();
  delay(1000);
  break;}
  
  case 0x1621:{

     while(pinger() >= 7){

  //move RIGHT
   right(); 
   delay(500);
   break;}
   break;}
   
   case 0x5621: {
  //move LEFT
while(pinger() <= 7){

  //move RIGHT
   left(); 
   delay(100);
   break;}}
   
  default:{
  halt();
  Serial.println("Stopped");
  break;}
}
}
