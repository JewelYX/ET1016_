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
const long interval = 2500;
unsigned long previousMillisLDR = 0;
const long intervalLDR = 1000;
int beep = 0;
int LDR = 0;
int BLUE = 0;
int ELDER_BLUE = 0;
// LDR function
int ldr_value;
int time_record = 0;
int sum = 0;
int startTime = 0;
// Check which button is pressed.Decides how much time to cross.
int button_input;

int ldr_values[5];  // To store 5 LDR values
int ldr_index = 0;

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
  if (currentMillis - previousMillis >= interval) {
    if (beep) {
      previousMillis = currentMillis;
      buzz.playTone(1000, 100);
    }
  }

  // LDR checking for nearby cars
  if (currentMillis - previousMillisLDR >= intervalLDR) {
    if (LDR) {
      previousMillisLDR = currentMillis;

      if (ldr_index < 5) {
        ldr_value = analogRead(LDR_PIN);
        ldr_values[ldr_index] = ldr_value;
        ldr_index++;
      } else {
        sum += ldr_value;
        time_record++;

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
        LDR = 0;
        Car_trafficlight();
      }
    }
  }

  // Reading button inputs
  if (digitalRead(BUTTONK1) == 0) {
    if (BLUE == 0) {
      beep = 0;
      LDR = 1;
      button_input = 0;
      BLUE = 1;
    }
  } else if (digitalRead(BUTTONK2) == 0) {
    if (ELDER_BLUE == 0) {
      beep = 0;
      LDR = 1;
      button_input = 15;
      ELDER_BLUE = 1;
    }
  } else {
    digitalWrite(BLUE_LED, LOW);
    beep = 1;
  }

  if (BLUE || ELDER_BLUE) {
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
  BLUE = 0;
  ELDER_BLUE = 0;
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
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
