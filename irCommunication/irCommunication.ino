#include <DigitalToggle.h>
#include <NECIRrcv.h>
#define IRPIN 4    // pin that IR detector is connected to

NECIRrcv ir(IRPIN) ;
int ledPin1 = 1; int ledPin2 = 2; int ledPin3 = 3;

void setup()
{
 //Serial.begin(9600) ;
 //Serial.println("NEC IR code reception") ;
 ir.begin() ;
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 pinMode(ledPin3, OUTPUT);
 }

void loop()
{
 unsigned long ircode ;
  
 while (ir.available()){
 
   ircode = ir.read() ;
 
   //Serial.println(ircode,HEX) ;
   if (ircode == 0xF30CFF00) digitalToggleFast(ledPin1);
   if (ircode == 0xE718FF00) digitalToggleFast(ledPin2);
   if (ircode == 0xA15EFF00) digitalToggleFast(ledPin3);
   //if (ircode == 0xB847FF00) digitalWrite(9, HIGH);
   }
}
