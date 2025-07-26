#include <Wire.h>

#include "RichShieldTM1637.h"

#define CLK 10//CLK of the TM1637 IC connect to D10 of OPEN-SMART UNO R3
#define DIO 11//DIO of the TM1637 IC connect to D11 of OPEN-SMART UNO R3
#define GREEN_LED 5
#define BUTTON 8
#define RED_LED 4
TM1637 disp(CLK,DIO);

void MAN+(void);


void setup()
{
pinMode(GREEN_LED,OUTPUT);
pinMode(BUTTON,INPUT_PULLUP);
pinMode(RED_LED,OUTPUT);
  disp.init();//The initialization of the display
}

void loop()
{
  int time_limit;
  if(digitalRead(BUTTON) == 0)
  {
  delay(10000);
  digitalWrite(RED_LED,LOW);
  for(time_limit = 25; time_limit > 0; time_limit-=1)
  {
    digitalWrite(GREEN_LED,HIGH);
    disp.display(time_limit);
    delay(700);
    if(time_limit <=5)
    {
    digitalWrite(GREEN_LED,LOW);
    disp.clearDisplay();
    delay(400);
    }
  }
  }
  else
  {
    digitalWrite(RED_LED,HIGH);
  }  
  
}
