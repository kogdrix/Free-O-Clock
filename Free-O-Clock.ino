


#include "OneButton.h"
#include <Wire.h>
#include <DS3231.h>
#include "src/WS2013SegmentDriver/SegmentDriver.h"



// FastLED




OneButton button(34, true);
RTClib myRTC;
SegmentDriver segmentDisplay;

void setup() {
   segmentDisplay.setup();
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(); 
  button.attachClick(doubleClick);
}

void loop() {
     segmentDisplay.loop();
  // put your main code here, to run repeatedly:
// ;
  button.tick();
  // insert a delay to keep the framerate modest
  

   EVERY_N_MILLISECONDS( 200 ) { 
    DateTime now = myRTC.now();
    segmentDisplay.setTime(now.hour(), now.minute(), now.second());
   } // slowly cycle the "base color" through the rainbow
  //fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void doubleClick()
{
  
  
} // doubleClick


  // 1
  // 2
  // 3
  // 4
  // 5
  // 6
  // 7
  // 8
  // 9
  //  üres  
  
