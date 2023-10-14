#include "OneButton.h"
#include <Wire.h>
#include <DS3231.h>
#include "src/WS2013SegmentDriver/SegmentDriver.h"

OneButton button(34, true);
RTClib myRTC;
SegmentDriver segmentDisplay;

void setup()
{
    segmentDisplay.setup();

    Serial.begin(115200);
    Wire.begin();
    button.attachClick(doubleClick);
}

void loop()
{
    segmentDisplay.loop();

    button.tick();

    EVERY_N_MILLISECONDS(200)
    {
        DateTime now = myRTC.now();
        segmentDisplay.setTime(now.hour(), now.minute(), now.second());
    }
}


