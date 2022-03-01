// C++ code
//
#include <Arduino.h>
int sensorState = 0;
int sensorPin = 14;
int ledPin = 4;

void setup()
{
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);

}

void loop()
{
  // read the state of the sensor/digital input
  sensorState = digitalRead(sensorPin);
  // check if sensor pin is HIGH. if it is, set the
  // LED on.
  // Serial.println(sensorState);
  if (sensorState == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
    // Serial.println("Sensor activated!");
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(ledPin, LOW);
  }
  delay(1000); // Delay a little bit to improve simulation performance
}