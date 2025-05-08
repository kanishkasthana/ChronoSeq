//Author Kanishk Asthana kasthana@ucsd.edu
//Wiring: Connect +5V DC from an external adapter/power supply to JD-VCC for a 8 channel relay. Connect ground to ground of external power supply. Also connect VCC to arduino 5V. 
//Do not connect Arduino GND to relay GND.  
//Defining relay variables according to the pins they are connected to

const int Relay1 = 13;
const int Relay2 = 12; 
const int Relay3 = 11;
const int Relay4 = 10; 
const int Relay5 = 9;  
const int Relay6 = 8; 
const int Relay7 = 7;  
const int Relay8 = 6;
//Relay vector will store current state of the relays
bool relayStateVector[8]={false,false,false,false,false,false,false,false};
String commandString;
void setup()
{
    Serial.begin(9600);
    pinMode(Relay1, OUTPUT);
    pinMode(Relay2, OUTPUT); 
    pinMode(Relay3, OUTPUT); 
    pinMode(Relay4, OUTPUT); 
    pinMode(Relay5, OUTPUT); 
    pinMode(Relay6, OUTPUT); 
    pinMode(Relay7, OUTPUT); 
    pinMode(Relay8, OUTPUT); 
    
    //Turn all Relays Off as soon as you power up
    
    digitalWrite(Relay1,HIGH);
    digitalWrite(Relay2,HIGH);
    digitalWrite(Relay3,HIGH);
    digitalWrite(Relay4,HIGH);
    digitalWrite(Relay5,HIGH);
    digitalWrite(Relay6,HIGH);
    digitalWrite(Relay7,HIGH);
    digitalWrite(Relay8,HIGH);
}

void updateRelayState(bool stateVector[8]){
  //Inversing order of stateVector to match Hardware Layout
  //Taking the inverse of the stateVector because a low signal turns the relay on
    digitalWrite(Relay1,!stateVector[7]);
    digitalWrite(Relay2,!stateVector[6]);
    digitalWrite(Relay3,!stateVector[5]);
    digitalWrite(Relay4,!stateVector[4]);
    digitalWrite(Relay5,!stateVector[3]);
    digitalWrite(Relay6,!stateVector[2]);
    digitalWrite(Relay7,!stateVector[1]);
    digitalWrite(Relay8,!stateVector[0]);
}

void loop()
{
  if(Serial.available()>8){
    commandString=Serial.readStringUntil('\n');
    if(commandString.length()==8){
      for(int i=0;i<8;i++){
        if(commandString[i]=='0')
          relayStateVector[i]=false;
        else if(commandString[i]=='1')
          relayStateVector[i]=true;
      }
      updateRelayState(relayStateVector);
    }
  }
}
 