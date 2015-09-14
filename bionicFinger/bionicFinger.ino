#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchStartPin = 6;
const int switchPushPin = 7;
const int ledPin = 8;

int gameScreen = 0;
int warmUpScreen = 0;

int switchStartState = 0;

int switchPushState = 0;
int switchPushStateOld = 0;

int i = 0;
int time = 0;
int warmUpTime = 3000;
int last = 0;

//EEPROM
int adress = 0;
byte highScore;

void setup() {
  lcd.begin(16, 2);
  pinMode(switchStartPin, INPUT);
  pinMode(switchPushPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  switchStartState = digitalRead(switchStartPin);
  switchPushState = digitalRead(switchPushPin);
  time = millis();

  if (switchStartState == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Max. Sco:");
    lcd.setCursor(0, 1);
    highScore = EEPROM.read(adress);
    lcd.print(highScore);
    delay(1000);
  }

  if (warmUpScreen == 0) {
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
    warmUpScreen = 1;
  }

  if (gameScreen == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pulsations:");
    lcd.setCursor(0, 1);
    lcd.print(i);
    time = millis();
    gameScreen = 1;
  }

  if ((switchPushState == HIGH) && (!switchPushStateOld)) {
    i++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pulsations:");
    lcd.setCursor(0, 1);
    lcd.print(i);
  }

  if (time > warmUpTime + last + 5000) {
    digitalWrite(ledPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SCORE:");
    lcd.setCursor(0, 1);
    lcd.print(i);
    delay(3000);

    if (i > highScore) {
      highScore = i;
      EEPROM.write(adress, highScore);
    }

    digitalWrite(ledPin, LOW);
    last = time;
    i = 0;
    warmUpScreen = 0;
    gameScreen = 0;
  }

  switchPushStateOld = switchPushState;

}
