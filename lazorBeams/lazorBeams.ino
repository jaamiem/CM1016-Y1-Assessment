/* Arduino Based Laser Turret
 * Sem-1-Y1 nov-2016
 * Team 14: George, Jamie, Jozi, Liam, Mathew, Teodor.
 * 
 * Purpose: Turret has 3 different modes of controlling the turret; Strobe, VirtualJoystick, and Potentiometer 
 *        Strobe - Fires Laser at random axis for random amount of shots
 *        VJS - Control Servos via Processing 3. Laser Functionality to be added.
 *        Potentiometer - control the servos with two potentiometers attached to the breadboard. Laser is perma-ON.
 *        
 *        modes are cycled via a button triggering interrupts.
 */

#include <Servo.h>
  //Import and define Servo library
Servo srvHoriz;
Servo srvVert;

  //Define Constants for pin numbers
#define buttonPin 2
#define lazorPin 3
#define buzzerPin 4

#define ledCount 4 //Number of LEDs used to represent active programs
const byte ledPins [ledCount] = {5,6,7,8}; //Pin numbers in array for said LEDs

  //Pins for servos
#define horizPin 9
#define vertPin 10

  //pins for Potentiometres
#define potHorizPin 11
#define potVertPin 12

  //variables for later use
int buttonLoop = 0;
byte previousLoop = 0;
byte currProgram = 0;

int buttonState = 0;

int potHorizRead = 0;
int potVertRead = 0;

int potHoriz = 0;
int potVert = 0;

  //var for virtual joystick
int ypos=0;
int xpos=0;

void setup() {
    //attach servos
  srvHoriz.attach(horizPin);
  srvVert.attach(vertPin);
    //attach everything else
  pinMode(buttonPin, INPUT);
  pinMode(lazorPin, OUTPUT); 
  pinMode(buzzerPin, OUTPUT);
    //attach LEDs
  for(int i=0; i<ledCount; i++){
    pinMode(ledPins[i], OUTPUT);
  }
    //Prime Interrupt // assign to button pin // call pinISR() // MODE = CHANGE ** Activate when Pin CHANGEs value
  attachInterrupt(digitalPinToInterrupt(buttonPin),pinISR,CHANGE);
    
  Serial.begin(19200); //listen for "Processing 3" port 19200
  Serial.println("Booting...");//debug test
}

void pin_ISR(){
  reset();
}

void reset(){
  digitalWrite(lazorPin,LOW);
  srvHoriz.write(90);
  delay(500);
  srvVert.write(90);
  delay(500);
  hitMeWithThoseLaserBeams();
  previousLoop = buttonLoop;
  if(buttonLoop >= 3){
    buttonLoop = 0;
  }
  else {
    buttonLoop++;
  }
  displayLED();
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPins[buttonLoop], HIGH);
    delay(1000);
    digitalWrite(ledPins[buttonLoop], LOW);
    delay(500);
  }
}

void lazorStrobe(){
  /* Select rand start/end point on both axis.
   * select rand amount of shots to fire,& length to wait between shots/bursts
   * Calc degree change on axis by (END-START)/SHOTS
   * Loop through, write axis change to servo, fire lazor */
   
    //Assign random ints to variables at the start of each loop.
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

    //Begin shooting.
  for(int shot=0; shot<numShots; shot++){
    srvHoriz.write(horizStart); //Write to start pos.
    srvVert.write(vertStart);
    
    horizStart += horizDiv; //Modify start pos for next call.
    vertStart += vertDiv;
    
    hitMeWithThoseLaserBeams(); //call laser fire func.

    delay(timeBetweenShots); //wait on random.
  }
  delay(timeBetweenBursts); //wait on random.
}

void hitMeWithThoseLaserBeams(){
    /* Set Buzzer and Laser to HIGH[ON]
     * Wait for 0.02 seconds
     * set to LOW[OFF] */
  digitalWrite(lazorPin, HIGH);
  analogWrite(buzzerPin, 10);
  delay(20);
  digitalWrite(lazorPin, LOW);
  analogWrite(buzzerPin, 0);
}

void virtualJoystick(){
  /* Using a local computer via processing to control the turret
   * with a mouse acting as a virtual joystick.
   * Processing sends variable int "xpos" which holds a degree point
   * with either "x" or "y" at the end to signify which axis is controlled. */
  static int degs = 0; //degrees calc var //d'ya like degs?
  if(Serial.available()){
    char ch = Serial.read();
    switch(ch){
      case '0'...'9':
        degs=degs*10+ch-'0'; //Degs? 
        break;
      case 'x':
        srvHoriz.write(degs); //Yeah, Degs. //Oh. Dogs..?
        degs=0;
        break;
      case 'y':
        srvVert.write(degs); //yeah... I like DOGS.
        degs=0;
        break;
    }
  }
}

void potentioControl(){
  digitalWrite(lazorPin, HIGH);
  
  potHorizRead = analogRead(potHorizPin);
  potVertRead = analogRead(potVertPin);

  potHoriz = round(potHorizRead/6);
  potVert = round(potVertRead/6);
  
  srvHoriz.write(potHorizRead);
  srvVert.write(potVertRead);
}

void displayLED(){ 
    /*LEDs used to highlight current mode.
    * When new mode is selected, clear LED from last mode
    * and activate LED relevant to new mode */
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
      lazorStrobe();
      break;
    case 2:
      displayLED();
      virtualJoystick();
      break;
    case 3:
      displayLED();
      potentioControl();
      break;
    default:
      for(int i=0; i<ledCount; i++){
        digitalWrite(ledPins[i],LOW);
      }
  }
}


























