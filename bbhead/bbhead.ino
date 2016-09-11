
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

void setup() {

  // set a bunch of digital pins to output and turn them on.

  int red = 10;
  int blue = 11;
  int amber = 12;

  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(amber, OUTPUT);

  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);
  digitalWrite(amber, HIGH);

  // make the randomness more random
  randomSeed(analogRead(0));

  // Connect to the servo and center it. 
  bbheadRotation.attach(8); 
  bbheadRotation.write(90);

  // Pause for a couple of beats to let the servo reach the desired position.
  delay(15);
  
}

void loop() {

  // look left

  bbheadRotation.write(35);
  delay(1000);

  // look right

  bbheadRotation.write(145);
  delay(1000);

  // return to center

  bbheadRotation.write(90);
  delay(5000);
  
}
