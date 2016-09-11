/***************************************************
  This is based on an example for the Adafruit VS1053 Codec Breakout
 ****************************************************/
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// These are the pins used for the music maker shield. Pasted straight from bundled sample code. 
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
#define CARDCS 4             // Card chip select pin
#define DREQ 3               // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup() {

  // speaker volume
  int volume = 10;

  //Serial.begin(9600);

  // make our random more random
  randomSeed(analogRead(0));

  // initialise the music player
  if (! musicPlayer.begin()) { // initialise the music player
    //Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }

  if (!SD.begin(CARDCS)) {
    //Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(volume, volume);

  // Set all the pins we are going to use to output.
  for (int thisPin = 22; thisPin <= 55; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }

  // From sample code. 
  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
    Serial.println(F("DREQ pin is not an interrupt pin"));
}

void loop() {

  // Pin mapping:
  //
  // 22      = Vocodor
  // 24      = Eye
  // 26      = Holo
  // 28      = Blue logic
  // 30      = White steady logic
  // 32 - 40 = White random logic

  // 26 Holo may be off or on each loop. 

  int holoOn = random(0,100);

  if (holoOn % 2) 
  { 
    digitalWrite(26, HIGH);    
  }
  else
  {
    digitalWrite(26, LOW);
  }

  // 24 Eye always on

  digitalWrite(24, HIGH);

  // 28 Blue logic, always on

  digitalWrite(28, HIGH);

  //30 upper white logic, always on

  digitalWrite(30, HIGH);

  // This is a super dirty way to get a shuffled playlist.
  // The files are all named nnn.mp3. We just pick a random number
  // between 1 and 27 and play that file.
  //
  // The conversion between strings and chars was based on googling
  // and may not actually be good.

  int trackList = random(1, 27);

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

    // Pin 22 is the vocoder. Ultimately this should pulse
    // to the souns, but one step at a time. For now flickering is OK.

    digitalWrite(22, HIGH);
    delay(random(1, 4));
    digitalWrite(22, LOW);

    // 32 - 40, random white logic. 

    int thisPin = random(32, 41);
    int thisDelay = random(1, 8);

    digitalWrite(thisPin, HIGH);
    delay(thisDelay);
    digitalWrite(thisPin, LOW);

  }

  // at the end of the track, turn off mouth and holo. turn lower logic on solid.

  digitalWrite(22, LOW);
  digitalWrite(26, LOW);

  for (int thisPin = 32; thisPin <= 41; thisPin++) {
    digitalWrite(thisPin, HIGH);
  }

  // pause a bit, then do it again!

  delay(random(1000, 3000));

}
