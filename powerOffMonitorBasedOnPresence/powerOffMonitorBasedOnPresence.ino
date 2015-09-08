/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 12;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(13, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:

  if (buttonState == 1) {
    Serial.println(buttonState);
    delay(1);        // delay in between reads for stability
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1);
  }

  if (buttonState == 0) {
    Serial.println(buttonState);
    delay(1);        // delay in between reads for stability
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(1);
  }

}



