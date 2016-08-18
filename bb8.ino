/*************************************************** 
  This is based on an example for the Adafruit VS1053 Codec Breakout
 ****************************************************/

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
#define CARDCS 4     // Card chip select pin
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup() {
  
  // speaker volume
  int volume = 80;
  
  Serial.begin(9600);

  // make our random more random
  randomSeed(analogRead(0));
  
  // initialise the music player
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
 
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(volume,volume);

  // Set all of our musicPlayer GPIO pins to output.

  for (int thisPin = 1; thisPin <= 7; thisPin++) {
    musicPlayer.GPIO_pinMode(thisPin, OUTPUT);
  }

  /***** Two interrupt options! *******/ 
  // This option uses timer0, this means timer1 & t2 are not required
  // (so you can use 'em for Servos, etc) BUT millis() can lose time
  // since we're hitchhiking on top of the millis() tracker
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT);
  
  // This option uses a pin interrupt. No timers required! But DREQ
  // must be on an interrupt pin. For Uno/Duemilanove/Diecimilla
  // that's Digital #2 or #3
  // See http://arduino.cc/en/Reference/attachInterrupt for other pins
  // *** This method is preferred
  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
    Serial.println(F("DREQ pin is not an interrupt pin"));
}

void loop() {  

  // This is a super dirty way to get a shuffled playlist.
  // The files are all named nnn.mp3. We just pick a random number
  // between 1 and 138 and play that file.
  //
  // The conversion between strings and chars was based on googling
  // and may not actually be good. 

  int trackList = random(0,100);
  
  String fileExt = ".mp3";
  String curTrack = trackList + fileExt;

  // musicPlayer wanted track name as a char array, not a string. Again with the googles.

  int strLen = curTrack.length() + 1;
  char trackName[strLen];
  curTrack.toCharArray(trackName, strLen);

  // Start playing a file, then we can do stuff while waiting for it to finish

  if (! musicPlayer.startPlayingFile(trackName)) {
    Serial.println("Could not open file");
    while (1);
  }
  Serial.println(F("Started playing"));

  while (musicPlayer.playingMusic) {
    
    // pin 1 is always on. There will be a bunch of LEDs hooked up to
    // this one. 
    
    musicPlayer.GPIO_digitalWrite(1, HIGH);

    // Pin 2 is the vocoder. Ultimately this should pulse
    // to the music, but one step at a time. For now flickering is OK.
    
    musicPlayer.GPIO_digitalWrite(2,HIGH);
    delay(random(5,20));
    musicPlayer.GPIO_digitalWrite(2, LOW);

    // Last we want to blink a bunch of LEDs in random order at random
    // intervals
    
    int thisPin = random(3,7);
    int thisDelay = random(50, 100);

    musicPlayer.GPIO_digitalWrite(thisPin, HIGH);
    delay(thisDelay);
    musicPlayer.GPIO_digitalWrite(thisPin, LOW);

  }

}
