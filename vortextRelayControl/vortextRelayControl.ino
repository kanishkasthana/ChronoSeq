//Defining relay variables according to the pins they are connected to

int relay=7;
int relay2=5;
bool relay1State=false;
bool relay2State=false;
String commandString="";
String stateString="";
 
void setup()
{
    Serial.begin(9600);
    pinMode(relay, OUTPUT);
    pinMode(relay2,OUTPUT);
    //Turn all Relay Off as soon as you power up
    digitalWrite(relay,LOW);
    digitalWrite(relay2,LOW);
}

void updateRelay1(bool powerState){
  if(powerState)
    digitalWrite(relay,HIGH);
  else
    digitalWrite(relay,LOW);
}

void updateRelay2(bool powerState){
  if(powerState)
    digitalWrite(relay2,HIGH);
  else
    digitalWrite(relay2,LOW);
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
          stateString=inputString.substring(1);
          if(stateString=="0"){
            relay1State=false;
            updateRelay1(relay1State);
          }
          else if(stateString=="1")
          {
            relay1State=true;
            updateRelay1(relay1State);
          }
          break;
        case 'B':
          stateString=inputString.substring(1);
          if(stateString=="0"){
            relay2State=false;
            updateRelay2(relay2State);
          }
          else if(stateString=="1")
          {
            relay2State=true;
            updateRelay2(relay2State);
          }
          break;

        case 'W':
          delay(inputString.substring(1).toInt());
          break;
      }
    }while(index!=-1);
  }
  updateRelay1(relay1State);
  updateRelay2(relay2State);
} 
