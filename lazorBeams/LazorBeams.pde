//Processing code:
import processing.serial.*;       

int xpos=90; // set x servo's value to mid point (0-180);
int ypos=90; // and the same here
Serial port; // The serial port we will be using

void setup()
{
 
  size(360, 360);
  frameRate(100);
  println(Serial.list()); // List COM-ports
  //select second com-port from the list (COM3 for my device)
  // You will want to change the [1] to select the correct device
  // Remember the list starts at [0] for the first option.
  port = new Serial(this, Serial.list()[1], 19200);
}

void draw()
{
  fill(175);
  rect(0,0,360,360);
  fill(255,0,0); //rgb value so RED
  rect(180, 175, mouseX-180, 10); //xpos, ypos, width, height
  fill(0,255,0); // and GREEN
  rect(175, 180, 10, mouseY-180);
  int a = constrain(mouseY, 20, 340);
  int b = constrain(mouseX, 20, 320);
  int c = 0;
  if(mousePressed){
    c = 1;
  }
  update(a, b, c);
  ellipse(b,a,10,10);
  
}

void update(int x, int y, int z)
{
 
  //Calculate servo postion from mouseX
  xpos= x/2;
  ypos = y/2;

 
  //Output the servo position ( from 0 to 180)
  port.write((xpos-180)+"x");
  port.write((ypos-180)+"y");
  
  if( z == 1 ){
    port.write('a');
  }
}