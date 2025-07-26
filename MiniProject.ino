  #define BUTTONK1 8
#define GREEN_LED 5
#define RED_LED 4
#define BLUE_LED 6
#define YELLOW_LED 7
#include "RichShieldPassiveBuzzer.h"  
#include "RichShieldTM1637.h"
#define CLK 10
#define DIO 11
TM1637 disp(CLK,DIO);
#include <Wire.h>

//Prototypes
void pedestrian_light(void);
void setup()
{
pinMode(GREEN_LED,OUTPUT);
pinMode(BUTTONK1,INPUT_PULLUP);
pinMode(RED_LED,OUTPUT);
disp.init();//The initialization of the display
}

void loop()
{
pedestrian_light();
}

void pedestrian_light(void){

//variable declarations
  int time_limit;

//Initial light patterns
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(BLUE_LED,LOW);

  if(digitalRead(BUTTONK1) == 0)
  {
  delay(5000);
  for(time_limit = 25; time_limit > 0; time_limit-=1)
  {
    digitalWrite(BLUE_LED,HIGH);
    digitalWrite(YELLOW_LED,LOW);
    disp.display(time_limit);
    
    if(time_limit <=5)
    {
    digitalWrite(BLUE_LED,HIGH);
    disp.clearDisplay();
    delay(500);
    }
  }
  }
  else
  {
    digitalWrite(YELLOW_LED,HIGH);
  }  
  while (digitalRead(BUTTONK1) ==0);

}
