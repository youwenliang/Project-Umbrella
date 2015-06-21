#include <Process.h>

void setup() {
// put your setup code here, to run once:
pinMode(13, OUTPUT);
pinMode(A0, INPUT);
Bridge.begin();
}

void loop() {
// put your main code here, to run repeatedly:
uploadData();
delay(10);
}

void uploadData(){
Process p;
int SensorValue = analogRead(A0);
p.runShellCommand("curl -k -X PATCH https://sizzling-fire-3461.firebaseio.com/Data.json -d '{ \"Data\" : "+ String(SensorValue) +"}'");
while(p.running());
}
