#include <Kelvin2RGB.h>
#include <TimeLib.h>
#include <Time.h>
#include <Dusk2Dawn.h>
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3

#define BRIGHTNESSPOT A0

int rise,set = 0;

void setup() {
  Serial.begin(9600);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  setTime(23,45,00,12,11,2019); 
}
void loop() {
  time_t t = now();
  if (hour() == 0 || rise == 0 || set == 0){
    Dusk2Dawn brno(49.19522,16.60796,+1);
    rise = brno.sunrise(year(),month(),day(),false);
    set = brno.sunset(year(),month(),day(),false);
  }
  int a = hour()*60 + minute();
  int dex;
  if (a >= rise && a <= set){
    dex = map(a,rise,set,5000,1000);
  }
  else{
    dex = 800;
  }
  int i = map(analogRead(BRIGHTNESSPOT),0,1023,0,100);
  Kelvin2RGB kelvin(dex, i);
  letitshine(kelvin.Red,kelvin.Green,kelvin.Blue);
}
void letitshine(int r, int g, int b) {
  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  analogWrite(BLUEPIN, b);
}



