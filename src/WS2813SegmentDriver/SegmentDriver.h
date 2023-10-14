#ifndef SEGMENTDRIVER_H
#define SEGMENTDRIVER_H
#include <FastLED.h>

#define DATA_PIN 23
#define LED_TYPE WS2813
#define COLOR_ORDER GRB
#define NUM_LEDS 86

#define BRIGHTNESS 24
#define FRAMES_PER_SECOND 120

struct ledSegments
{
  int16_t leds[3] = {-1};
};

class SegmentDriver
{
public:
  SegmentDriver();
  void setup();
  void loop();
  void setTime(int8_t hour, int8_t minute, int8_t second);

private:
  CRGB leds[NUM_LEDS];
  void setDigitDefinitions();
  void setSegmentDefinitions();
  void setDigitValue(int8_t value, int8_t digitPosition);
  void setDelimeterState(bool state);
  ledSegments digitAbsoluteLedPositions[7] = {};
  ledSegments digitDefinitions[10][7] = {};
};

#endif