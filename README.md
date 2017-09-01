# ESP8266 demo of WifiManager and FauxMoESP

I was very excited when I found the following two libraries:

* https://github.com/tzapu/WiFiManager - allows your ESP8266 device to prompt you for the local Wifi SSID/password, and then stores it, just like fancy retail devices
* https://bitbucket.org/xoseperez/fauxmoesp.git - turns your ESP8266 device into faux Belkin Wemo device(s) which can be turned on/off via Amazon Alexa or Google Home (I tested the former).

But sadly when I tried to combine them into one project (this project) they clashed during compilation.

I've forked two libraries - `fauxmoesp` and its dependency [`ESPAsyncWebServer`](https://github.com/me-no-dev/ESPAsyncWebServer) - so that they do not redeclare various `HTTP_*` enum values from `ESP8266WiFi.h` in https://github.com/esp8266/Arduino.git. These are referenced in `platformio.ini`.

The `platformio.ini` here is preconfigured for the Adafruit Huzzah breakout board, but you can modify it for whichever ESP8266 board you are working with.

It is important to keep the `lib_deps` section which references my git branches that work nicely together (at the time of writing):

```
lib_deps =
  WifiManager
  https://github.com/drnic/ESPAsyncWebServer#ESP8266WebServerOK
  https://bitbucket.org/drnic/fauxmoesp.git#ESP8266WebServerOK
```

To compile/upload/monitor output:

```
pio run --target upload --target monitor
```

This will automatically download the dependency libraries before compilation.

On the initial deployment, when the ESP8266 device does not have your local Wifi configuration (or if you uncomment `wifiManager.resetSettings();` line), the output will look similar to:

```
*WM: AP IP address:
*WM: 192.168.4.1
*WM: HTTP server started
```

With your phone or laptop, look for a wifi access point called `ESP1716003` or similar and connect to it. Your phone will popup the WifiManager web page and allow you to configure your ESP8266 device for your local Wifi access point.

Then the serial output will eventually look like:

```
*WM: Sent wifi save page
*WM: Connecting to new AP
*WM: Connecting as wifi client...
*WM: Connection result:
*WM: 3
FauxMo demo sketch
After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'
```

On subsequent restarts of the ESP8266 device the output will look similar to:

```
*WM: Connection result:
*WM: 3
*WM: IP Address:
*WM: 192.168.86.130
FauxMo demo sketch
After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'
```

You can now ask Alexa to discover devices and then you will have two new devices: `pixels` and `relay`. Then say "Alexa, turn on pixels" and you will eventually see a serial message.
