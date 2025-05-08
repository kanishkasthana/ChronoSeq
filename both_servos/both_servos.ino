#include <Servo.h>

const int servoPin2=9;
const int servoPin=11;
int defaultAngle=180;
int angle=defaultAngle;
int angle2=defaultAngle;

Servo servo1;
Servo servo2;
void setup() {
  Serial.begin(9600);
  servo1.attach(servoPin);
  servo1.write(defaultAngle);
  servo2.attach(servoPin2);
  servo2.write(defaultAngle);
}

void setAngle(int ang){
  servo1.write(180-ang);
  angle=ang;
}
void setAngle2(int ang){
  servo2.write(180-ang);
  angle2=ang;
}

void loop() {
  String commandString=Serial.readStringUntil('\n');
  if(commandString.length()>0){
    int index=0;
    String inputString="";
    do{
      index=commandString.indexOf('|');
      if(index==-1){
        inputString=commandString;
        Serial.println("No remaining commands with the following input:");
        Serial.println(inputString);
      }
      else{
        inputString=commandString.substring(0,index);
        commandString=commandString.substring(index+1);
        Serial.println("Input:");
        Serial.println(inputString);
        Serial.println("Remaining Command:");
        Serial.println(commandString);
      }
      char command=inputString.charAt(0);
      switch(command){
        case 'A':
          setAngle(inputString.substring(1).toInt());
          break;
        case 'B':
          setAngle2(inputString.substring(1).toInt());
          break;
        case 'W':
          delay(inputString.substring(1).toInt());
          break;
      }
    }while(index!=-1);
  }

  setAngle(angle);
  setAngle2(angle2);
}
