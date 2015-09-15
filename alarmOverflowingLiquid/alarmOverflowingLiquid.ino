/*
	alarmOverflowingLiquid

	Author: Antonio David Gellida Lavara - @adgellida
*/

void setup() {
  
  pinMode(13, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  Serial.print("Water level Sensor Value:");
  Serial.println(analogRead(A0));
  delay(500);

  if (analogRead(A0)>500) digitalWrite(13, HIGH);
  if (analogRead(A0)<500) digitalWrite(13, LOW);

}
