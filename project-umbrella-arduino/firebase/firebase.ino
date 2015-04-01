#include <Process.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
  Bridge.begin();
  Console.begin();
}

boolean flag = true;

void loop() {
  // put your main code here, to run repeatedly:
  uploadData();
  //delay(10);
}

void uploadData(){
  Process p;
  String colorValue = setLedColorHSV(int(map(analogRead(A0), 0, 1000, 0, 360)),1,1);
  Console.println("curl -k -X PATCH https://sizzling-fire-3461.firebaseio.com/Data.json -d '{\"background-color\" : \""+colorValue+"\"}'");
  p.runShellCommand("curl -k -X PATCH https://sizzling-fire-3461.firebaseio.com/Data.json -d '{\"background-color\" : \""+colorValue+"\"}'");
  while(p.running());

  if(flag) {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    flag = false;
  }
  else {
    digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
    flag = true;
  }
}

String setLedColorHSV(int h, double s, double v) {
  //this is the algorithm to convert from RGB to HSV
  double r=0; 
  double g=0; 
  double b=0;

  double hf=h/60.0;

  int i=(int)floor(h/60.0);
  double f = h/60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s*f);
  double tv = v * (1 - s * (1 - f));

  switch (i)
  {
  case 0: //rojo dominante
    r = v;
    g = tv;
    b = pv;
    break;
  case 1: //verde
    r = qv;
    g = v;
    b = pv;
    break;
  case 2: 
    r = pv;
    g = v;
    b = tv;
    break;
  case 3: //azul
    r = pv;
    g = qv;
    b = v;
    break;
  case 4:
    r = tv;
    g = pv;
    b = v;
    break;
  case 5: //rojo
    r = v;
    g = pv;
    b = qv;
    break;
  }

  //set each component to a integer value between 0 and 255
  int red=constrain((int)255*r,0,255);
  int green=constrain((int)255*g,0,255);
  int blue=constrain((int)255*b,0,255);

  return "rgb("+String(red)+","+String(green)+","+String(blue)+")";
}
