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
#define lazorPin 3
#define buzzerPin 4

#define ledCount 3 //Number of LEDs used to represent active programs
const byte ledPins [ledCount] = {5,6,7}; //Pin numbers in array for said LEDs

  //Pins for servos
#define horizPin 9
#define vertPin 10

#define potPin A0 //Potentiometer Pin

int potVal = 0; //
int previousLoop = 0;

  //var for virtual joystick
int ypos=0;
int xpos=0;

void setup() {
    //attach servos
  srvHoriz.attach(horizPin);
  srvVert.attach(vertPin);
    //attach everything else
  pinMode(lazorPin, OUTPUT); 
  pinMode(buzzerPin, OUTPUT);
    //attach LEDs
  for(int i=0; i<ledCount; i++){
    pinMode(ledPins[i], OUTPUT);
  }
  
  Serial.begin(19200); //listen for "Processing 3" port 19200
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
  int vertStart = random(10,150);
  int vertEnd = random(10,150);
    //Fire commands.
  int timeBetweenBursts = random(150,1000);
  int timeBetweenShots = random(20,100);
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
  digitalWrite(lazorPin, LOW);
  tone(buzzerPin, 500);
  delay(30);
  digitalWrite(lazorPin, HIGH);
  noTone(buzzerPin);
}

void virtualJoystick(){
  /* Using a local computer via processing to control the turret
   * with a mouse acting as a virtual joystick.
   * Processing sends variable int "xpos" which holds a degree point
   * with either "x" or "y" at the end to signify which axis is controlled. */
  digitalWrite(lazorPin, HIGH);
  static int degs = 0; //degrees calc var //d'ya like degs?
  while(Serial.available() > 0){
    char input = Serial.read();
    switch(input){
      case '0'...'9':
        degs=degs*10+input-'0'; //Degs? 
        break;
      case 'x':
        srvHoriz.write(degs); //Yeah, Degs. //Oh. Dogs..?
        degs=0;
        break;
      case 'y':
        srvVert.write(degs); //yeah... I like DOGS.
        degs=0;
        break;
      case 'a':
        hitMeWithThoseLaserBeams();
        delay(50);
        degs=0;
        break;
    }
  }
}

void displayLED(){ 
    /*LEDs used to highlight current mode.
    * When new mode is selected, clear LED from last mode
    * and activate LED relevant to new mode */
    digitalWrite(ledPins[previousLoop],LOW);
    digitalWrite(ledPins[potVal],HIGH);
    previousLoop = potVal;
}

void loop(){
  potVal = analogRead(potPin);
  potVal /= (int) 255.75;
  
  switch (potVal){
    case 0:
      displayLED();
      break;
    case 1:
      displayLED();
      lazorStrobe();
      break;
    case 2:
    case 3:
      displayLED();
      virtualJoystick();
      break;
    default:
      for(int i=0; i<ledCount; i++){
        digitalWrite(ledPins[i],HIGH);
      }
      delay(500);
      for(int i=0; i<ledCount; i++){
        digitalWrite(ledPins[i],LOW);
      }
      delay(500);
      break;
  }
}









