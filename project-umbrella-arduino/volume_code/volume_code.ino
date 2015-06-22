#include <Process.h>

const int micPin = A0;
const int ledPin =  13;

int micValue = 0;
Process p;

void setup() {
  Bridge.begin();
  pinMode(ledPin, OUTPUT);      
  pinMode(micPin, INPUT);     
  Serial.begin(57600);
  Serial.println("Begin");
}

boolean start = false;

void loop(){
  //micValue = analogRead(micPin);
  //Serial.println(micValue);
  //if(micValue < 600){
    digitalWrite(ledPin, HIGH);
    p.begin("madplay /mnt/sda1/water1.mp3");
    while(p.running());
  //}
//  while(p.running()){
//    micValue = analogRead(micPin);
//    Serial.println(micValue);
//    if(micValue > 600){
//      p.close();
//      digitalWrite(ledPin, LOW);
//    }
//  }
//    digitalWrite(ledPin, HIGH);  
//    p.runShellCommand("madplay /mnt/sda1/water1.mp3");
//    while(p.running());
//    Serial.println("it works!");
//  } 
}

