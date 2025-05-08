#include <Servo.h>

#define yAxisLimitPin A0
#define xAxisLimitPin A1
const int servoPin=11;
const int tubeDownAngle=0;
const int tubeUpAngle=180;
const int dirPin2=6;
const int stepPin1=3;
const int stepPin2=2;
const int dirPin1=5;
const int enablePin=8;
int xpos=0;
int ypos=0;
int microDelay=50;
int smoothMotionMicroDelay=100;
int xcount=0;
int ycount=0;
Servo servo1;

void setup() {
  pinMode(yAxisLimitPin,INPUT);
  pinMode(xAxisLimitPin,INPUT);
  pinMode(stepPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  pinMode(enablePin,OUTPUT);
  Serial.begin(9600);
  servo1.attach(servoPin);
  servo1.write(tubeDownAngle);
  digitalWrite(enablePin,HIGH);//Disable Motor on Startup
}

void enableMotors(){
  digitalWrite(enablePin,LOW);
}

void disableMotors(){
  digitalWrite(enablePin,HIGH);
}

void moveX(int steps){
  if(xpos+steps>=-12000 && xpos+steps<=0){
    xpos=xpos+steps;
    if(steps>0){
      digitalWrite(dirPin1,HIGH);
      digitalWrite(dirPin2,HIGH);
    }
    else{
      digitalWrite(dirPin1,LOW);
      digitalWrite(dirPin2,LOW);
    }
    
    for(int i=0;i<abs(steps);i++){
      digitalWrite(stepPin1,HIGH);
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(microDelay);
      digitalWrite(stepPin1,LOW);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(microDelay);
    }
  }
  else{
     Serial.println("Error!That position is out of bounds! I Cannot move there.");
    }
}

void moveY(int steps){
  if(ypos+steps>=-20000 && ypos+steps<=0){
    ypos=ypos+steps;
    if(steps>0){
      digitalWrite(dirPin1,HIGH);
      digitalWrite(dirPin2,LOW);
    }
    else{
      digitalWrite(dirPin1,LOW);
      digitalWrite(dirPin2,HIGH);
    }
    
    for(int i=0;i<abs(steps);i++){
      digitalWrite(stepPin1,HIGH);
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(microDelay);
      digitalWrite(stepPin1,LOW);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(microDelay);
    }
  }
  else{
    Serial.println("Error!That position is out of bounds! I Cannot move there.");
  }
}

void moveYSmoothly(int steps){
  if(ypos+steps>=-20000 && ypos+steps<=0){
    ypos=ypos+steps;
    if(steps>0){
      digitalWrite(dirPin1,HIGH);
      digitalWrite(dirPin2,LOW);
    }
    else{
      digitalWrite(dirPin1,LOW);
      digitalWrite(dirPin2,HIGH);
    }
    int startDelay=500+smoothMotionMicroDelay,stopDelay=smoothMotionMicroDelay;
    for(int i=0;i<abs(steps);i++){
      if(i<500){
        digitalWrite(stepPin1,HIGH);
        digitalWrite(stepPin2,HIGH);
        delayMicroseconds(startDelay);
        digitalWrite(stepPin1,LOW);
        digitalWrite(stepPin2,LOW);
        delayMicroseconds(startDelay);
        startDelay--;
      }
      else if(i>=500 && i<(abs(steps)-500)){
        digitalWrite(stepPin1,HIGH);
        digitalWrite(stepPin2,HIGH);
        delayMicroseconds(smoothMotionMicroDelay);
        digitalWrite(stepPin1,LOW);
        digitalWrite(stepPin2,LOW);
        delayMicroseconds(smoothMotionMicroDelay);
      }
      else if(i>=(abs(steps)-500)){
        digitalWrite(stepPin1,HIGH);
        digitalWrite(stepPin2,HIGH);
        delayMicroseconds(stopDelay);
        digitalWrite(stepPin1,LOW);
        digitalWrite(stepPin2,LOW);
        delayMicroseconds(stopDelay);
        stopDelay++;
      }
      
    }
  }
  else{
    Serial.println("Error!That position is out of bounds! I Cannot move there.");
  }
}

void tubeControl(int command){
  if(command==1){
    servo1.write(tubeUpAngle);
  }
  else{
    servo1.write(tubeDownAngle);
  }
  delay(500);
}

void tubeControlFast(int command){
  if(command==1){
    servo1.write(tubeUpAngle);
  }
  else{
    servo1.write(tubeDownAngle);
  }
  delay(200);
}

void tubeDownSmoothly(){
  int initialPosition=2400;//Always call this function with the previous position having tube up. Otherwise it defeats the purpose of smooth motion.
  int finalPosition=544;
  for(int i=initialPosition;i>=finalPosition;i--){
    servo1.writeMicroseconds(i);
    if(i>=2200 && i<=2400)
      delayMicroseconds(2000);
    else if(i>=2000 && i<2200)
      delayMicroseconds(1000);
    else if(i>=944 && i<2000)
      delayMicroseconds(500);
    else if(i>=744 && i<944)
      delayMicroseconds(1000);
    else if(i>=544 && i<744)
      delayMicroseconds(2000);
  }
}

//Help recalibrate the robot to keep precision
void goHome(){
 enableMotors();
 tubeControl(1); //Tube Up
 //Moving in Positive Y direction back to Home
 digitalWrite(dirPin1,HIGH);
 digitalWrite(dirPin2,LOW);
 //Keep moving towards the origin till you hit the Y limit switch
 while(digitalRead(yAxisLimitPin)==HIGH){
      digitalWrite(stepPin1,HIGH);
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(microDelay);
      digitalWrite(stepPin1,LOW);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(microDelay);
 }
 ypos=0;//Recalibrate
 Serial.println("Y axis recalibrated! We are now at Y=0.");
 
 //Moving in Positive X direction back to Home
 digitalWrite(dirPin1,HIGH);
 digitalWrite(dirPin2,HIGH);
 //Keep moving towards the origin till you hit the X limit switch
 while(digitalRead(xAxisLimitPin)==HIGH){
      digitalWrite(stepPin1,HIGH);
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(microDelay);
      digitalWrite(stepPin1,LOW);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(microDelay);
 }
 xpos=0; //Recalibrate
 Serial.println("X axis recalibrated! We are now at X=0.");
 tubeControl(0);//Tube Down
}

void getCoordinatesFromPosition(){
 xcount=0;
 ycount=0;
 enableMotors();
 tubeControl(1); //Tube Up
 //Moving in Positive Y direction back to Home
 digitalWrite(dirPin1,HIGH);
 digitalWrite(dirPin2,LOW);
 //Keep moving towards the origin till you hit the Y limit switch
 while(digitalRead(yAxisLimitPin)==HIGH){
      digitalWrite(stepPin1,HIGH);
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(microDelay);
      digitalWrite(stepPin1,LOW);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(microDelay);
      ycount--;
 }
 ypos=0;//Recalibrate
 //Serial.println("Y axis recalibrated! We are now at Y=0.");
 
 //Moving in Positive X direction back to Home
 digitalWrite(dirPin1,HIGH);
 digitalWrite(dirPin2,HIGH);
 //Keep moving towards the origin till you hit the X limit switch
 while(digitalRead(xAxisLimitPin)==HIGH){
      digitalWrite(stepPin1,HIGH);
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(microDelay);
      digitalWrite(stepPin1,LOW);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(microDelay);
      xcount--;
 }
 xpos=0; //Recalibrate
 Serial.println("X coordinates are: "+String(xcount)+" . Y coordinates are: "+String(ycount));
 tubeControl(0);//Tube Down
}



void goToCoordinates(int x,int y){
  enableMotors();
  tubeControl(1);
  moveY(y-ypos);
  moveX(x-xpos);
  tubeControl(0);
}

void goToCoordinatesKeepTubeUp(int x,int y){
  enableMotors();
  tubeControl(1);
  moveY(y-ypos);
  moveX(x-xpos);
}

void goToCoordinatesSmoothly(int x,int y){
  enableMotors();
  moveYSmoothly(y-ypos);
  tubeDownSmoothly();
}

void goToCoordinatesFast(int x,int y){
  enableMotors();
  tubeControlFast(1);
  moveY(y-ypos);
  moveX(x-xpos);
  tubeControlFast(0);
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
        case 'W':
          delay(inputString.substring(1).toInt());
          break;
        case 'T':
          tubeControl(inputString.substring(1).toInt());
          break;
        case 'V':
          tubeDownSmoothly();
          break;
        case 'X':
          moveX(inputString.substring(1).toInt());
          break;
        case 'Y':
          moveY(inputString.substring(1).toInt());
          break;
        case 'E':
          enableMotors();
          break;
        case 'D':
          disableMotors();
          break;
        case 'H':
          goHome();
          break;
        case 'C':
          getCoordinatesFromPosition();
          break;
        case 'G':
          {
            String coordinates=inputString.substring(1);
            int commaIndex=coordinates.indexOf(',');
            if(commaIndex!=-1){
              int x=coordinates.substring(0,commaIndex).toInt();
              int y=coordinates.substring(commaIndex+1).toInt();
              goToCoordinates(x,y);
            }
          }
          break;
        case 'U':
          {
            String coordinates=inputString.substring(1);
            int commaIndex=coordinates.indexOf(',');
            if(commaIndex!=-1){
              int x=coordinates.substring(0,commaIndex).toInt();
              int y=coordinates.substring(commaIndex+1).toInt();
              goToCoordinatesKeepTubeUp(x,y);
            }
          }
          break;
        case 'M':{
          String microseconds=inputString.substring(1);
          servo1.writeMicroseconds(microseconds.toInt());
        }
          break;
        case 'S':
          {
            String coordinates=inputString.substring(1);
            int commaIndex=coordinates.indexOf(',');
            if(commaIndex!=-1){
              int x=coordinates.substring(0,commaIndex).toInt();
              int y=coordinates.substring(commaIndex+1).toInt();
              goToCoordinatesSmoothly(x,y);
            }
          }
          break;          
        case 'F':
          {
            String coordinates=inputString.substring(1);
            int commaIndex=coordinates.indexOf(',');
            if(commaIndex!=-1){
              int x=coordinates.substring(0,commaIndex).toInt();
              int y=coordinates.substring(commaIndex+1).toInt();
              goToCoordinatesFast(x,y);
            }
          }
          break;
          
      }
    }while(index!=-1);
  }
}
