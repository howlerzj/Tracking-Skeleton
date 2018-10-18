/*
Created by James Sherry 2018-10-09
Halloween project. Skeleton who has a moving jaw and
will lock onto the closest person and follow them
with his head until someone closer comes.
Also a bird fried who will move his head from side
to side and eyes will light up randomly.


// green tap servo is jaw
*/
#include <Servo.h>

Servo jawServo; // creating jaw servo object
Servo headServo;  // creating servo for spining head
Servo birdServo;  // creating servo for bird head.

int jawpos = 0; // range is 0-70 for jaw
int headpos = 0; // this will follow but range is 0-180
int birdpos = 0; // this tilts from 0 - 70
int birdLed = 13;  // Bird Leds at pin 13


/***** Located the first target info *****/
const int TrigPinLocate = 2;  // trigger of locating first contact
const int EchoPinLocate = 3;  // Echo for locating first contact
float cmLocate ; 

/***** Lock on to first target info *****/
const int TrigPinTargetL = 4;  // trigger of aquired target 
const int EchoPinTargetL = 5;  // Echo for aquired targe
float cmTargetR;
const int TrigPinTargetR = 6;  // trigger of aquired target 
const int EchoPinTargetR = 7;  // Echo for aquired targe
float cmTargetL;
float inchesLocate; // convert to inches
float inchesTargetR; // convert to inches
float inchesTargetL; // convert to inches




void setup() {
  // put your setup code here, to run once:
  
 /* *****setting up birds eyes******/
pinMode(birdLed, OUTPUT);  // Bird Leds as output

 /* *****setting up servos for movement******/
jawServo.attach(10);  //Jaw attached at pin 12
headServo.attach(8);  //Jaw attached at pin 9
birdServo.attach(9);  //Jaw attached at pin 9


 /* *****setting up ultrasonic sensors******/
Serial.begin (9600);
// locate sensor
pinMode(TrigPinLocate, OUTPUT);
pinMode(EchoPinLocate, INPUT);

// two target sensors
pinMode(TrigPinTargetR, OUTPUT);
pinMode(EchoPinTargetR, INPUT);
pinMode(TrigPinTargetL, OUTPUT);
pinMode(EchoPinTargetL, INPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:




// First find the closet person when approaching the house

 /****** Scaning for a victom ******/
 
digitalWrite(TrigPinLocate, LOW);
delayMicroseconds(2);
digitalWrite(TrigPinLocate, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPinLocate, LOW);
cmLocate = pulseIn(EchoPinLocate, HIGH) / 58.0; // the echo time is converted to cm
cmLocate = (int(cmLocate * 100.0)) / 100.0;  // Keep two decimal points
inchesLocate = cmLocate/2.5;   // convert to inches

 /****** Scaning and locking on to target right sensor******/
digitalWrite(TrigPinTargetR, LOW);
delayMicroseconds(2);
digitalWrite(TrigPinTargetR, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPinTargetR, LOW);
cmTargetR = pulseIn(EchoPinTargetR, HIGH) / 58.0;  // target echo time is converted to cm
cmTargetR = (int(cmTargetR * 100.0)) / 100.00;  // keep two decimals
inchesTargetR = cmTargetR/2.5;   // convert to inches

 /****** Scaning and locking on to target left sensor******/
digitalWrite(TrigPinTargetL, LOW);
delayMicroseconds(2);
digitalWrite(TrigPinTargetL, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPinTargetL, LOW);
cmTargetL = pulseIn(EchoPinTargetL, HIGH) / 58.0;  // target echo time is converted to cm
cmTargetL = (int(cmTargetL * 100.0)) / 100.00;  // keep two decimals
inchesTargetL = cmTargetL/2.5;   // convert to inches 

// Serial.print(cmLocate);
  if (cmLocate < 150){
    movingBird();
    Serial.println(cmLocate);
  }

/*  
// Decide if the cmLocate is closer the cmTarget
if (cmLocate < cmTargetR || cmLocate < cmTargetL){
  headServo.write(0);// move Servo to the right to lock on
}
else {
trackTarget();
}
*/
trackTarget();
// if cmLocate is closer lock on to this target


// if cmTarget is closer track with servoHead


// if head is pointing to door AND taget is at a certain distance to be determined move head of bird



}
void trackTarget(){
  
  movingJaw();

  if(inchesTargetL <= 96 || inchesTargetR <= 96) {  // seting limit to 96 inches
    
  
  if (inchesTargetL + 2 < inchesTargetR) {
    headpos = headpos -2;
  }
  if (inchesTargetR +2 < inchesTargetL) {
    headpos = headpos +2;
  }
  }
  if (headpos > 160){
    headpos = 160;
  }
  if (headpos < 0){
    headpos = 0;
  }
  Serial.println("Left distance");
  Serial.println (inchesTargetL);
  Serial.println("left cm");
  Serial.println (cmTargetL);
  Serial.println("Right distance");
  Serial.println (inchesTargetR);
    Serial.println("right cm");
  Serial.println (cmTargetR);
  Serial.println("headpos");
  Serial.print (headpos);
  headServo.write(headpos);
}
void movingJaw(){


  for (jawpos = 0; jawpos <= 70; jawpos += 1) { // goes from 0 degrees to 70 degrees no bigger 
    // in steps of 1 degree
    jawServo.write(jawpos);  // tell servo for mouth to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
for (jawpos = 70; jawpos >= 0; jawpos -= 1) { // goes from 70 degrees to 0 degrees
    jawServo.write(jawpos);  
    delay(15);                       // waits 15ms for the servo to reach the position
  
}
}
void movingBird(){
birdBlinking();
  for (birdpos = 0; birdpos <= 70; birdpos += 1) { // goes from 0 degrees to 70 degrees no bigger 
    // in steps of 1 degree
    birdServo.write(birdpos);  // tell servo for mouth to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
for (birdpos = 70; birdpos >= 0; birdpos -= 1) { // goes from 70 degrees to 0 degrees
    birdServo.write(birdpos);  
    delay(15);                       // waits 15ms for the servo to reach the position
  
}
}
  /****** birds eyes blinking eyes******/ 
  void birdBlinking(){
  digitalWrite (birdLed, HIGH);
  delay(1000);
  digitalWrite (birdLed, LOW);
  delay(1000);
  }

