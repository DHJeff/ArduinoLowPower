/*
  WiFiPower.ino
  
  Written by Jeff Wu (jeff@arduino.org)
  
  This example for the Arduino Primo board shows how to use
  low power library to manage WiFi power.
  The STM32 is able to turn the WiFi on or off directly, 
  Reducing the power consumption of Primo board.
  This example code is in the public domain.
  
*/

#include "ArduinoLowPower.h"

int reading; // the current reading from the input pin
int state = true; //variable for setting WiFi status
long last_time = 0; // the last time the output pin was toggled
long debounce = 200; // the debounce time, increase if the output flickers

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(USER2_BUTTON, INPUT);
}

void loop() {
  // read the state of the USER2 BUTTON value:
  reading = digitalRead(USER2_BUTTON);

  // if the input is LOW and we've Waiting long enough to ignore any noise 
  // on the circuit, toggle the output pin and remember the time
  if(reading == 0 && millis() - last_time > debounce ) {
    state = !state; // reverse state
    if(state == true) {
      LowPower.powerOnWifi(); //turn the WiFi on
      LowPower.enableWifi(); //enable WiFi
    }
    else {
      LowPower.powerOffWifi(); //turn the WiFi off
      LowPower.disableWifi(); //disable WiFi
    }
    last_time = millis();
  }
}