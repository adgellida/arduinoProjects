/*
	bionicFinger
	Author: Antonio David Gellida Lavara - @adgellida
*/

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <SoftReset.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchStartPin = 6;
const int switchPushPin = 7;
const int ledPin = 13;

int switchStartState = 0;
int switchStartStateOld = 0;

int switchPushState = 0;
int switchPushStateOld = 0;

int menuVar = 1;
int i = 0;
int gamingTime = 10000;

//EEPROM

int adress = 0;
byte highScore;

//Functions Declarations

void ShowMaxScore();
void PlayMode();
void GamePulsationScreenCreation();
void WarmUpScreen();

//Setup

void setup() {

  lcd.begin(16, 2);
  pinMode(switchStartPin, INPUT);
  pinMode(switchPushPin, INPUT);
  pinMode(ledPin, OUTPUT);

}

//Program

void loop() {

  //Read the buttons state

  switchStartState = digitalRead(switchStartPin);
  switchPushState = digitalRead(switchPushPin);

  //Menu selection

  if ((switchStartState == HIGH) && (!switchStartStateOld)) {

    menuVar++;
    if (menuVar > 2) menuVar = 1;

  }

  switch (menuVar) {

    case 1:

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Play");
      lcd.setCursor(0, 1);
      delay(50);

      if ((switchPushState == HIGH) && (!switchPushStateOld)) {

        WarmUpScreen();
        GamePulsationScreenCreation();
        PlayMode();

      }

      break;

    case 2:

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Show Max. Score");
      lcd.setCursor(0, 1);
      delay(50);

      if ((switchPushState == HIGH) && (!switchPushStateOld)) {

        ShowMaxScore();

      }

      break;

    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }

  switchPushStateOld = switchPushState;
  switchStartStateOld = switchStartState;

}

//Functions Implementations

void ShowMaxScore() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Max. Score:");
  lcd.setCursor(0, 1);
  highScore = EEPROM.read(adress);
  lcd.print(highScore);
  delay(1000);

}

void WarmUpScreen() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("New Game");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Countdown:");
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("YA!");
  delay(500);

}

void GamePulsationScreenCreation() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pulsations:");
  lcd.setCursor(0, 1);
  lcd.print(i);

}

void PlayMode() {

  while (millis() < gamingTime) {

    switchPushState = digitalRead(switchPushPin);

    if ((switchPushState == HIGH) && (!switchPushStateOld)) {

      i++;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pulsations:");
      lcd.setCursor(0, 1);
      lcd.print(i);

    }

    switchPushStateOld = switchPushState;

  }

  //Shows the score

  if (millis() >= gamingTime) {

    digitalWrite(ledPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SCORE:");
    lcd.setCursor(0, 1);
    lcd.print(i);
    delay(3000);

  }

  //...and if the score is higher...

  if (i > highScore) {

    highScore = i;
    EEPROM.write(adress, highScore);

  }

  digitalWrite(ledPin, LOW);
  //i = 0;

  //...Returning to menu

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Returning to menu");
  delay(3000);

  soft_restart();

}