#include <Process.h>
#include <FreqMeasure.h>

const int micVPin = 8;
const int micFPin = A0;

float micVValue = 0;
float micFValue = 0;

int sumMicV = 0;
int sumMicF = 0;

int counterMicV = 0;
int counterMicF = 0;

float avgMicV = 0;
float avgMicF = 0;

int rangeV = 500;
int stepV = 150;
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
  Serial.println(micVValue);
  
  if(counterPause > 100){
    avgMicV = sumMicV / counterMicV;
    avgMicF = sumMicF / counterMicF;
    
    //Volume:    1: 500~650  2: 650~800  3: 800~950
    //Frequency: 1: 80~140   2: 140~200  3: 200~260
    
    int numV = int((avgMicV - rangeV) / stepV) + 1;
    int numF = int((avgMicF - rangeF) / stepF) + 1;
    
    p.begin("madplay /mnt/sda1/"+String(numV)+String(numF)+"x.mp3");
    p.running();
    
    while(counterMicV > 0){  
      counterMicV--;  
    }
    //p.stop!;
    counterPause = 0;
  }
  else {
    if (micVValue > 500) {
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
      if(start) counterPause++;
      else ;//default state
    }
  }
}

