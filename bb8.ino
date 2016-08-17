/*
 Based on:
 http://www.arduino.cc/en/Tutorial/ForLoop

 This lights up BB-8's head. Pins 9 - 13 are used for the blinking logics on 
 the lower row of lights. Pin 8 is for the 'always on' lights. 
 */

void setup() {
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 7; thisPin <= 13; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}

void loop() {

  // Turn pin 8 on and leave it. 

  digitalWrite(8, HIGH);

  // Randomize the pattern on pins 9 - 13

  int thisPin = random(9,14);
  int thisDelay = random(100, 200);
  
  digitalWrite(thisPin, HIGH);
  delay(thisDelay);
  digitalWrite(thisPin, LOW);

  // Pulse pin 7

  digitalWrite(7, HIGH);
  delay(random(5,20));
  digitalWrite(7, LOW);
  

}
