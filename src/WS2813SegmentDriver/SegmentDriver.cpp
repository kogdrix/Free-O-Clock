#include "SegmentDriver.h"
#include <FastLED.h>
SegmentDriver::SegmentDriver()
{
}

CRGB leds[NUM_LEDS];
bool led_state[NUM_LEDS] = {false};
int16_t gHue = 0;
int8_t prevHour = -1;
int8_t prevMin = -1;
void SegmentDriver::setTime(int8_t hour, int8_t minute, int8_t second)
{
  if (prevHour != hour)
  {
    prevHour = hour;

    for (int16_t z = 0; z < 42; z++)
    {
      leds[z] = CRGB::Black;
    }
  }

  if (prevMin != minute)
  {

    prevMin = minute;
    for (int16_t z = 41; z < NUM_LEDS; z++)
    {
      leds[z] = CRGB::Black;
    }
  }
  setDelimeterState(second % 2 == 0);
  if (!(hour < 10))
  {
    setDigitValue(hour % 10, 1);
    setDigitValue(hour / 10, 0);
  }
  else
  {
    setDigitValue(0, 0);
    setDigitValue(hour, 1);
  }
  if (!(minute < 10))
  {
    setDigitValue(minute % 10, 3);
    setDigitValue(minute / 10, 2);
  }
  else
  {
    setDigitValue(0, 2);
    setDigitValue(minute, 3);
  }
}

void SegmentDriver::loop()
{
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  

  EVERY_N_MILLISECONDS(250) { gHue++; } 
}

void SegmentDriver::setDelimeterState(bool state)
{
  if (state)
  {
    leds[84] = CHSV(gHue, 255, 255);
    leds[85] = CHSV(gHue, 255, 255);
  }
  else
  {
    leds[84] = CRGB::Black;
    leds[85] = CRGB::Black;
  }
}

void SegmentDriver::setup()
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  setSegmentDefinitions();
  setDigitDefinitions();
}

void SegmentDriver::setDigitValue(int8_t value, int8_t digitPosition)
{
  int8_t baseMultiplier = digitPosition;
  for (int16_t i = 0; i < 7; i++)
  {
    if (digitDefinitions[value][i].leds[0] != -1)
    {
      for (int16_t y = 0; y < 3; y++)
      {
        leds[digitDefinitions[value][i].leds[y] + (baseMultiplier * 21)] = CHSV(gHue, 255, 255);
      }
      
    }
  }
}

void SegmentDriver::setDigitDefinitions()
{
  // 0
  digitDefinitions[0][0] = digitAbsoluteLedPositions[0];
  digitDefinitions[0][1] = digitAbsoluteLedPositions[1];
  digitDefinitions[0][2] = digitAbsoluteLedPositions[2];
  digitDefinitions[0][3] = digitAbsoluteLedPositions[3];
  digitDefinitions[0][4] = digitAbsoluteLedPositions[4];
  digitDefinitions[0][5] = digitAbsoluteLedPositions[5];
  // 1
  digitDefinitions[1][0] = digitAbsoluteLedPositions[1];
  digitDefinitions[1][1] = digitAbsoluteLedPositions[2];
  // 2
  digitDefinitions[2][0] = digitAbsoluteLedPositions[0];
  digitDefinitions[2][1] = digitAbsoluteLedPositions[1];
  digitDefinitions[2][2] = digitAbsoluteLedPositions[6];
  digitDefinitions[2][3] = digitAbsoluteLedPositions[4];
  digitDefinitions[2][4] = digitAbsoluteLedPositions[3];

  // 3
  digitDefinitions[3][0] = digitAbsoluteLedPositions[0];
  digitDefinitions[3][1] = digitAbsoluteLedPositions[1];
  digitDefinitions[3][2] = digitAbsoluteLedPositions[6];
  digitDefinitions[3][3] = digitAbsoluteLedPositions[2];
  digitDefinitions[3][4] = digitAbsoluteLedPositions[3];

  // 4
  digitDefinitions[4][0] = digitAbsoluteLedPositions[1];
  digitDefinitions[4][1] = digitAbsoluteLedPositions[2];
  digitDefinitions[4][2] = digitAbsoluteLedPositions[6];
  digitDefinitions[4][3] = digitAbsoluteLedPositions[5];

  // 5
  digitDefinitions[5][0] = digitAbsoluteLedPositions[0];
  digitDefinitions[5][1] = digitAbsoluteLedPositions[5];
  digitDefinitions[5][2] = digitAbsoluteLedPositions[6];
  digitDefinitions[5][3] = digitAbsoluteLedPositions[2];
  digitDefinitions[5][4] = digitAbsoluteLedPositions[3];

  // 6
  digitDefinitions[6][0] = digitAbsoluteLedPositions[0];
  digitDefinitions[6][1] = digitAbsoluteLedPositions[5];
  digitDefinitions[6][2] = digitAbsoluteLedPositions[6];
  digitDefinitions[6][3] = digitAbsoluteLedPositions[2];
  digitDefinitions[6][4] = digitAbsoluteLedPositions[3];
  digitDefinitions[6][5] = digitAbsoluteLedPositions[4];

  // 7
  digitDefinitions[7][0] = digitAbsoluteLedPositions[0];
  digitDefinitions[7][1] = digitAbsoluteLedPositions[1];
  digitDefinitions[7][2] = digitAbsoluteLedPositions[2];

  // 8
  digitDefinitions[8][0] = digitAbsoluteLedPositions[0];
  digitDefinitions[8][1] = digitAbsoluteLedPositions[1];
  digitDefinitions[8][2] = digitAbsoluteLedPositions[2];
  digitDefinitions[8][3] = digitAbsoluteLedPositions[3];
  digitDefinitions[8][4] = digitAbsoluteLedPositions[4];
  digitDefinitions[8][5] = digitAbsoluteLedPositions[5];
  digitDefinitions[8][6] = digitAbsoluteLedPositions[6];

  // 9
  digitDefinitions[9][0] = digitAbsoluteLedPositions[0];
  digitDefinitions[9][1] = digitAbsoluteLedPositions[1];
  digitDefinitions[9][2] = digitAbsoluteLedPositions[2];
  digitDefinitions[9][3] = digitAbsoluteLedPositions[3];
  digitDefinitions[9][4] = digitAbsoluteLedPositions[5];
  digitDefinitions[9][5] = digitAbsoluteLedPositions[6];
}

void SegmentDriver::setSegmentDefinitions()
{
  digitAbsoluteLedPositions[0].leds[0] = 0; // A 0
  digitAbsoluteLedPositions[0].leds[1] = 1; // A 0
  digitAbsoluteLedPositions[0].leds[2] = 2; // A 0

  digitAbsoluteLedPositions[1].leds[0] = 3; // B 1
  digitAbsoluteLedPositions[1].leds[1] = 4; // B 1
  digitAbsoluteLedPositions[1].leds[2] = 5; // B 1

  digitAbsoluteLedPositions[2].leds[0] = 6; // C 2
  digitAbsoluteLedPositions[2].leds[1] = 7; // C 2
  digitAbsoluteLedPositions[2].leds[2] = 8; // C 2

  digitAbsoluteLedPositions[3].leds[0] = 9;  // D 3
  digitAbsoluteLedPositions[3].leds[1] = 10; // D 3
  digitAbsoluteLedPositions[3].leds[2] = 11; // D 3

  digitAbsoluteLedPositions[4].leds[0] = 12; // E 4
  digitAbsoluteLedPositions[4].leds[1] = 13; // E 4
  digitAbsoluteLedPositions[4].leds[2] = 14; // E 4

  digitAbsoluteLedPositions[5].leds[0] = 15; // F 5
  digitAbsoluteLedPositions[5].leds[1] = 16; // F 5
  digitAbsoluteLedPositions[5].leds[2] = 17; // F 5

  digitAbsoluteLedPositions[6].leds[0] = 18; // G 6
  digitAbsoluteLedPositions[6].leds[1] = 19; // G 6
  digitAbsoluteLedPositions[6].leds[2] = 20; // G 6
}