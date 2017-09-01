// https://learn.adafruit.com/easy-alexa-or-echo-control-of-your-esp8266-huzzah/software-setup
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#include <wifisetup.h>


#define SERIAL_BAUDRATE 9600

fauxmoESP fauxmo;
WifiSetup wifiSetup;

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
    wifiSetup.setup();

    Serial.println("FauxMo demo sketch");
    Serial.println("After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'");

    // Wifi
    wifiSetup.setup();

    // Fauxmo
    fauxmo.addDevice("relay");
    fauxmo.addDevice("pixels");
    fauxmo.onMessage(callback);
}

void loop() {
  fauxmo.handle();
}
