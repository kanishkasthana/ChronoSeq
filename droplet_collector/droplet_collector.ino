#include <Servo.h>

const int servoPin2=9;
const int servoPin=11;
int defaultAngle=0;
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
  servo1.write(ang);
  angle=ang;
}
void setAngle2(int ang){
  servo2.write(ang);
  angle2=ang;
}

int getMicrosecondsFromAngle(int ang){
  return map(ang,0,180,544,2400);
}
void setAngleSlowly(int ang){
  int currentPosition=getMicrosecondsFromAngle(angle);
  int finalPosition=getMicrosecondsFromAngle(ang);
  int midPosition=(finalPosition+currentPosition)/2;
  int quarterPosition=(midPosition+currentPosition)/2;
  int threeQuartersPosition=(finalPosition+midPosition)/2;

  if(finalPosition<=currentPosition){
    for(int i=currentPosition;i>=finalPosition;i--){
        servo1.writeMicroseconds(i);
        if(i<=currentPosition && i>quarterPosition)
          delayMicroseconds(2000);
        else if(i<=quarterPosition && i>midPosition)
          delayMicroseconds(750);
        else if(i<=midPosition && i>threeQuartersPosition)
          delayMicroseconds(750);
        else if(i<=threeQuartersPosition && i>=finalPosition)
          delayMicroseconds(2000);
       }
    }
  else{
    for(int i=currentPosition;i<=finalPosition;i++){
        servo1.writeMicroseconds(i);
        if(i>=currentPosition && i<quarterPosition)
          delayMicroseconds(2000);
        else if(i>=quarterPosition && i<midPosition)
          delayMicroseconds(750);
        else if(i>=midPosition && i<threeQuartersPosition)
          delayMicroseconds(750);
        else if(i>=threeQuartersPosition && i<=finalPosition)
          delayMicroseconds(2000);
       }    
    }
  setAngle(ang);
}

void setAngleSlowly2(int ang){
  int currentPosition=getMicrosecondsFromAngle(angle2);
  int finalPosition=getMicrosecondsFromAngle(ang);
  int midPosition=(finalPosition+currentPosition)/2;
  int quarterPosition=(midPosition+currentPosition)/2;
  int threeQuartersPosition=(finalPosition+midPosition)/2;

  if(finalPosition<=currentPosition){
    for(int i=currentPosition;i>=finalPosition;i--){
        servo2.writeMicroseconds(i);
        if(i<=currentPosition && i>quarterPosition)
          delayMicroseconds(2000);
        else if(i<=quarterPosition && i>midPosition)
          delayMicroseconds(750);
        else if(i<=midPosition && i>threeQuartersPosition)
          delayMicroseconds(750);
        else if(i<=threeQuartersPosition && i>=finalPosition)
          delayMicroseconds(2000);
       }
    }
  else{
    for(int i=currentPosition;i<=finalPosition;i++){
        servo2.writeMicroseconds(i);
        if(i>=currentPosition && i<quarterPosition)
          delayMicroseconds(2000);
        else if(i>=quarterPosition && i<midPosition)
          delayMicroseconds(750);
        else if(i>=midPosition && i<threeQuartersPosition)
          delayMicroseconds(750);
        else if(i>=threeQuartersPosition && i<=finalPosition)
          delayMicroseconds(2000);
       }    
    }
  setAngle2(ang);
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
        case 'H':
          setAngle(0);
          setAngle2(0);
        case 'W':
          delay(inputString.substring(1).toInt());
          break;
        case 'X':
          setAngleSlowly(inputString.substring(1).toInt());
          break;
        case 'Y':
         setAngleSlowly2(inputString.substring(1).toInt());
         break;
      }
    }while(index!=-1);
  }
  setAngle(angle);
  setAngle2(angle2);
}
