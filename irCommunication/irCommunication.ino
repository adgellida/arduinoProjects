/*
	irCommunication

	Author: Antonio David Gellida Lavara - @adgellida
*/

#include <DigitalToggle.h>
#include <NECIRrcv.h>
#define IRPIN 4    // pin that IR detector is connected to

NECIRrcv ir(IRPIN) ;
int ledPin2 = 2; int ledPin3 = 3;

void setup()
{
  //Serial.begin(9600) ;
  //Serial.println("NEC IR code reception") ;
  ir.begin() ;
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop()
{
  unsigned long ircode ;

  while (ir.available()) {

    ircode = ir.read() ;

    //Serial.println(ircode,HEX) ;
    if (ircode == 0xF20DFD02) digitalToggleFast(ledPin2);
    if (ircode == 0xF10EFD02) digitalToggleFast(ledPin3);
    //if (ircode == 0xA15EFF00) digitalToggleFast(ledPin3);
    //if (ircode == 0xB847FF00) digitalWrite(9, HIGH);
  }
}
