#include <FreqCounter.h>

void setup() {
  Serial.begin(57600);
  pinMode( 6, OUTPUT);
  pinMode( 7, OUTPUT);
  pinMode( 8, OUTPUT);
  pinMode( 9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}
long int frq;
bool led = false;

void loop() {
  if(Serial.available() > 0)
  {
    String cmd = Serial.readStringUntil(';');

    // Read frequency @pin5
    if(cmd.startsWith("F"))
    {
      FreqCounter::f_comp = 8;            // Set compensation to 12
      FreqCounter::start(100);            // Start counting with gatetime of 100ms
      while (FreqCounter::f_ready == 0);  // wait until counter ready
      frq = FreqCounter::f_freq;          // read result
      Serial.print("F ");                // print header & split
      Serial.print(frq);                 // print result
      Serial.print(";");
    }

    // Output @pin6-10
    if(cmd.startsWith("O "))
    {
      if(cmd.length() >= 7)
      {
        digitalWrite( 6, (cmd.charAt(2) == '1')? HIGH : LOW);
        digitalWrite( 7, (cmd.charAt(3) == '1')? HIGH : LOW);
        digitalWrite( 8, (cmd.charAt(4) == '1')? HIGH : LOW);
        digitalWrite( 9, (cmd.charAt(5) == '1')? HIGH : LOW);
        digitalWrite(10, (cmd.charAt(6) == '1')? HIGH : LOW);
      } 

      Serial.print(cmd + ";");
    }

    // visualize for dispatching
    if(led)
    {
      led = false;
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      led = true;
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}
