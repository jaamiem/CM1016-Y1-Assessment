/*
 * Arduino Based Laser Turret
 * 
 * Team 14: Jamie, Liam, Teo, Mathew, George, Jozi
 * 
 * Current research: array assignments, interrupts.
 */

#include <Servo.h>
  //Import and define Servo library
Servo srvHoriz;
Servo srvVert;

  //Define Constants for pin numbers
#define buttonPin 2
#define lazorPin 3
#define buzzerPin 4

#define ledCount 4  //Number of LEDs used to represent programs
const byte ledPins [ledCount] = {5,6,7,8}; //Pin numbers in array for said LEDs

  //Pins for servos
#define horizPin 9
#define vertPin 10

  //variables for later use
int buttonLoop = 0;
int previousLoop;
int currProgram = 0;

void setup() {
    //attach servos
  srvHoriz.attach(horizPin);
  srvVert.attach(vertPin);
    //attach everything else
  pinMode(buttonPin, INPUT);
  pinMode(lazorPin, OUTPUT); 
  pinMode(buzzerPin, OUTPUT);

  for(byte i=0; i<ledCount; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  attachInterrupt(digitalPinToInterrupt(buttonPin),pinISR,CHANGE);
}

void pinISR(){
  digitalWrite(lazorPin,LOW);
  srvHoriz.write(90);
  delay(500);
  srvVert.write(90);
  delay(500);
  previousLoop = buttonLoop;
  buttonLoop = 0;
}

void LazorStrobe(){
    //Assign random variables at the start of each loop.
    //Servos.
  int horizStart = random(1,180); 
  int horizEnd = random(1,180);
  int vertStart = random(40,150);
  int vertEnd = random(40,150);
    //Fire commands.
  int timeBetweenBursts = random(200,2000);
  int timeBetweenShots = random(50,200);
  int numShots = random(2,20);

    //Calculate calculate degrees of movement between each shot.
  int horizDiv = (horizEnd - horizStart) / numShots;
  int vertDiv = (vertEnd - vertStart) / numShots;

  srvHoriz.write(horizStart); //Set Servos to start pos and wait.
  srvVert.write(vertStart);
  delay(100);

    //Begin shooting
  for(int shot=0; shot<numShots; shot++){
    srvHoriz.write(horizStart); //Write to start pos
    srvVert.write(vertStart);
    
    horizStart += horizDiv; //Modify start pos
    vertStart += vertDiv;
    
    hitMeWithThoseLaserBeams(); //call laser fire

    delay(timeBetweenShots); //wait on random
  }
  delay(timeBetweenBursts); //wait on random
}

void hitMeWithThoseLaserBeams(){
  digitalWrite(lazorPin, HIGH);
  analogWrite(buzzerPin, 10); //Buzzer and laser on
  delay(20);               //wait
  digitalWrite(lazorPin, LOW);//buzzer and laser off
  analogWrite(buzzerPin, 0);
}

void displayLED(){
  digitalWrite(ledPins[previousLoop],LOW);
  digitalWrite(ledPins[buttonLoop],HIGH);
}

void loop(){
  switch (buttonLoop){
    case 0:
      displayLED();
      break;
    case 1:
      displayLED();
      break;
    case 2:
      displayLED();
      break;
    case 3:
      displayLED();
      break;
    default:
      for(byte i=0; i<ledCount; i++){
        digitalWrite(ledPins[i],LOW);
      }
  }
}


























