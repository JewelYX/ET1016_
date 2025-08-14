// Name: Ooi Yee Yang, Nicholas Yoong
// Admission No: OYY 2506032 NY 2516138
// Class: DCEP/1A/04

#include <Wire.h>
#include "RichShieldPassiveBuzzer.h"
#include "RichShieldTM1637.h"

#define BUTTONK1 8
#define BUTTONK2 9
#define GREEN_LED 5
#define RED_LED 4
#define BLUE_LED 6
#define YELLOW_LED 7
#define CLK 10
#define DIO 11
#define LDR_PIN A2
#define PassiveBuzzerPin 3

TM1637 disp(CLK, DIO);
PassiveBuzzer buzz(PassiveBuzzerPin);

// Function Prototypes
void pedestrian_light(void);
void buzz_tone(void);
void constant_buzz(int msdelay);
void Car_trafficlight(void);
void BLUE_LIGHT(int button_input);

// Variable Declarations
// buzzer time limit
int time_limit; 
int initial_buzzer;
int buzz_time;
// replace blocking code with millis
unsigned long previousMillis = 0;
unsigned long previousMillisLDR = 0;
//Turning on each feature of the traffic light
int beep = 0;
int LDR = 0;
int BLUE = 0;
int GetLDR = 0;
// LDR function
int ldr_value;
double time_record = 0.0;
int sum = 0;
int ldr_values[5];  // To store 5 LDR values
int ldr_index = 0;
// Check which button is pressed.Decides how much time to cross.
int button_input;


void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BUTTONK1, INPUT_PULLUP);
  pinMode(BUTTONK2, INPUT_PULLUP);
  pinMode(LDR_PIN, INPUT_PULLUP);

  disp.init();
  Serial.begin(9600);

  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();

  // Constant beeping every 2.5 seconds
  if (currentMillis - previousMillis >= 2500) {
    if (beep) {
      previousMillis = currentMillis;
      buzz.playTone(1000, 100);
    }
  }

  // LDR checking for nearby cars WHILE still beeping every 2.5 seconds
  if (currentMillis - previousMillisLDR >= 1000) {
    if (LDR) {
      previousMillisLDR = currentMillis;
      if (GetLDR) {
        ldr_value = analogRead(LDR_PIN);
        ldr_values[ldr_index] = ldr_value;
        sum+= ldr_value;
        time_record++;
        ldr_index++;
        if (ldr_index >= 5) {
          GetLDR = 0;
        }
      } else {
          Serial.println("Stored LDR values:");
          for (int i = 0; i < 5; i++) {
            Serial.println(ldr_values[i]);
          }

        double average = sum / time_record;
        Serial.print("Average LDR value: ");
        Serial.println(average);

        if (average < 1000) {
          constant_buzz(15000);
        } else {
          constant_buzz(5000);
        }

        ldr_index = 0;
        time_record = 0;
        sum = 0;
        LDR = 0;
        beep = 0;
        Car_trafficlight();
      }
    }
  }

  // Reading button inputs
  if (digitalRead(BUTTONK1) == 0 || digitalRead(BUTTONK2) == 0) {
    beep = 1;
    if (digitalRead(BUTTONK1) == 0) {
        button_input = 0;
  } else if (digitalRead(BUTTONK2) == 0) {
      button_input = 15;
  } else {
    digitalWrite(BLUE_LED, LOW);
    beep = 1;
    BLUE = 0;
  }
  LDR = 1;
  GetLDR = 1;
} else {
  beep = 1;
}
if (BLUE == 1) {
  BLUE_LIGHT(button_input);
 }
}
// ------------------------------------------------------------------------------------------------
// User-defined functions by Yee Yang
void constant_buzz(int delayms) {
  for (int i = delayms / 2500; i > 0; i--) {
    buzz.playTone(1000, 100);
    delay(2500);
  }
  BLUE = 1;
}

void BLUE_LIGHT(int button_input) {
  for (initial_buzzer = 5000; initial_buzzer > 0; initial_buzzer -= 500) {
    digitalWrite(BLUE_LED, HIGH);
    buzz.playTone(1500, 10);
    delay(150);
  }

  delay(500);

  for (time_limit = 25 + button_input; time_limit > 0; time_limit--) {
    disp.display(time_limit);
    buzz_tone();
    delay(900);

    if (time_limit <= 5) {
      disp.clearDisplay();
      digitalWrite(BLUE_LED, LOW);
      delay(200);
      digitalWrite(BLUE_LED, HIGH);
    }
  }

  digitalWrite(BLUE_LED, LOW);
  delay(1500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  BLUE = 0;
  beep = 1;
}


// ------------------------------------------------------------------------------------------------
// User-defined functions by Nicholas
void Car_trafficlight(void) {
  int ledPins[] = {GREEN_LED, YELLOW_LED, RED_LED};

  for (int i = 0; i < 2;) {
    digitalWrite(ledPins[i], LOW);
    i += 1;
    digitalWrite(ledPins[i], HIGH);
    delay(3000);
  }
// digitalWrite(BLUE_LED,HIGH);
}

void buzz_tone() {
  for (buzz_time = 1000; buzz_time > 0; buzz_time -= 250) {
    buzz.playTone(1000, 25);
    delay(75);
  }
}
