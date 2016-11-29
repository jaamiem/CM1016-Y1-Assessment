#include <Servo.h>
Servo yservo; Servo xservo;
int ypos=0;
int xpos=0;

void setup(){
  xservo.attach(12);
  yservo.attach(13);

  Serial.begin(19200);
  Serial.println("Rolling");

}

void loop() {
  static int v = 0;
  if(Serial.available()){
    char ch = Serial.read();
    switch(ch){
      case '0'...'9':
      v=v*10+ch-'0';
      break;
      case 'x':
      xservo.write(v);
      v=0;
      break;
      case 'y';
      yservo.write(v);
      v=0;
      break;
    }
  }

}
