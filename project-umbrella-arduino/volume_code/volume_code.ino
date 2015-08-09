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
int counter = 0;
int x = 1;
int y = 1;

void loop(){
  //micValue = analogRead(micPin);
  //Serial.println(micValue);
  //if(micValue < 600){
    if(!start) {
      digitalWrite(ledPin, HIGH);
      p.runShellCommandAsynchronously("madplay /mnt/sda1/"+String(x)+""+String(y)+"x.mp3");
    }
    else {
      p.runShellCommandAsynchronously("/usr/bin/killall -9 madplay");
      if(x < 3) x++;
      else y++;
      if(y>3) y = 3;
    }
    counter++;
    if(counter > 100) {
      start = !start;
      counter = 0;
    }

    //while(p.running());
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

