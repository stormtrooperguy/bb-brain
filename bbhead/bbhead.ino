
/* Simple code for an animatronic BB-8 display. This will move the head to various positions to 
 * make him appear 'alive'. The random positions and intervals are to try to break it up so that
 * people around him for a while won't see a repeated pattern. 
 * 
 * This code also lights up some LEDs on the body. 
 * 
 */

// Include the servo library and create a head

#include <Servo.h>

Servo bbheadRotation; // Rotation of the head

//Servo bbheadTilt; // Angle of the head

// We don't really want the head moving by 1 degree with a 0.453 second delay, so 
// set some defined intervals and positions to use. 

int headPos[] = { 0, 45, 90, 135, 180 };
int headIntervals[] = { 1000, 5000, 10000, 15000, 20000, 25000, 30000 };

void setup() {

  // make the randomness more random
  randomSeed(analogRead(0));

  // serial communication to help see what's happening
  Serial.begin(9600);    

  // set a bunch of digital pins to output and turn them on.

  // Connect to the servo and center it. 
  bbhead.attach(9); 
  bbhead.write(90);

  // Pause for a couple of beats to let the servo reach the desired position.
  delay(15);
  
}

void loop() {

  // For this loop, select a head stop and delay. 
  int headStop = random(0,4);
  int headDelay = random(0, 6);

  // print these to the serial monitor. I'll take this out when I'm satisfied.
  Serial.println(headStop);
  Serial.println(headDelay);
  Serial.println();

  // move to the selected position and wait. 
  bbhead.write(headPos[headStop]);
  delay(headIntervals[headDelay]);

  // I want some led activity in the body, not just on. 
  // implement some function to decide if the LEDs should flicker 
  // somewhere. Code TBD.
  
}
