// https://learn.adafruit.com/easy-alexa-or-echo-control-of-your-esp8266-huzzah/software-setup
#include <Arduino.h>
#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "fauxmoESP.h"

#define SERIAL_BAUDRATE 9600

fauxmoESP fauxmo;

void callback(uint8_t device_id, const char * device_name, bool state) {
  Serial.print("Device "); Serial.print(device_name);
  Serial.print(" state: ");
  if (state) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
}

void setup() {
    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);

    WiFiManager wifiManager;
    //reset saved settings
    // wifiManager.resetSettings();

    wifiManager.autoConnect();

    Serial.println("FauxMo demo sketch");
    Serial.println("After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'");

    // Fauxmo
    fauxmo.addDevice("relay");
    fauxmo.addDevice("pixels");
    fauxmo.onMessage(callback);
}

void loop() {
  fauxmo.handle();
}
