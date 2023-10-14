
#define DEBUG
#ifdef DEBUG
#define M_PRINTF(f_, ...) {Serial.printf((f_), ##__VA_ARGS__);}
#define M_PRINTLN(f_) {Serial.println((f_));}
#else
#define M_PRINTF(f_, ...) (0);
#define M_PRINTLN(f_) (0);
#endif

#include <Arduino.h>

#include "src/ESPConnect/ESPConnect.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "OneButton.h"
#include <Wire.h>
#include <DS3231.h>
#include "src/WS2813SegmentDriver/SegmentDriver.h"

#include <ESPmDNS.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include<SPIMemory.h>
#include "SPIFFS.h"
#include "src/cfgHandler/cfgHandler.h"

AsyncWebServer server(80);

#define DEBUG

OneButton button(34, true);
RTClib myRTC;
SegmentDriver segmentDisplay;

void setup()
{  
    Serial.begin(115200);
    ESPConnect.autoConnect("Free-O-Clock","1234567890");

   if(ESPConnect.begin(&server))
    {
        Serial.println("Connected to WiFi");
        Serial.println("IPAddress: "+WiFi.localIP().toString());
    }
    else
    {
        Serial.println("Failed to connect to WiFi");
    }

    segmentDisplay.setup(); 
    setDiscovery();
    Wire.begin();
    readFile(SPIFFS, "config.json"); 
    server.begin();
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


void setDiscovery()
{
  if (!MDNS.begin("fr33oclock"))
  {
    Serial.println("Error setting up MDNS responder!");       
  }
  else
  {    
    Serial.println("mDNS responder started");    
    // Add service to MDNS-SD
    MDNS.addService("http", "tcp", 80);
  }
}
