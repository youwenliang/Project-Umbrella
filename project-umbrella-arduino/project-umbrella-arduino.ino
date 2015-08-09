#include <Process.h>
#include <FreqMeasure.h>

const int micVPin = A0;
const int micFPin = 8;

float micVValue = 0;
float micFValue = 150;

int sumMicV = 0;
int sumMicF = 0;

int counterMicV = 0;
int counterMicF = 0;

float avgMicV = 0;
float avgMicF = 0;

int rangeV = 650;
int stepV = 10;
int rangeF = 80;
int stepF = 60;

Process p;
int counterPause = 0;

void setup() {
  pinMode(micFPin, INPUT);
  Serial.begin(57600);
  Bridge.begin();
  FreqMeasure.begin();
}

boolean start = false;
double sum = 0;
int count = 0;

void loop(){
  micVValue = analogRead(micVPin);
  if(counterPause < 3200){
    if (micVValue > 650) {
      digitalWrite(13, LOW);
      start = true;
      counterPause = 0;
      counterMicV++;
      sumMicV += micVValue;
      if (FreqMeasure.available()) {
        counterMicF++;
        // average several reading together
        sum = sum + FreqMeasure.read();
        count = count + 1;
        if (count > 30) {
          micFValue = FreqMeasure.countToFrequency(sum / count);
          Serial.println(micFValue);
          sumMicF += micFValue;
          sum = 0;
          count = 0;
        }
      }
    }
    else {
      if(start) {
        counterPause++;
      }
      else {
        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      }//default state
    }
  }
  else {  
    if(start){
      digitalWrite(12, LOW);   // turn the LED on (HIGH is the voltage level)
      avgMicV = sumMicV / counterMicV;
      avgMicF = sumMicF / counterMicF;
      
      //Volume:    1: 500~650  2: 650~800  3: 800~950
      //Frequency: 1: 80~140   2: 140~200  3: 200~260
      
      int numV = int((avgMicV - rangeV) / stepV) + 1;
      int numF = int((avgMicF - rangeF) / stepF) + 1;
     
      if(numV < 1) numV = 1;
      if(numV > 3) numV = 3;
      if(numF < 1) numF = 1;
      if(numF > 3) numF = 3;
      
      // Implement Play and Stop codes!!!
      p.runShellCommandAsynchronously("madplay /mnt/sda1/"+String(numV)+String(numF)+"x.mp3");
      start = false;
      counterMicV*=1000;
    }    
    else {
      if (counterMicV > 0){  
        counterMicV-=1;  
      }
      else {
        p.runShellCommandAsynchronously("/usr/bin/killall -9 madplay");
        start = false;
        counterPause = 0;
        counterMicV = 0;
        counterMicF = 0;
      }
    }
  }
}

