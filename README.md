# Simple-Arduino-ESP8266-Webhook
Arduino ESP8266 project.


This is supposed to be used with the Arduinio ESP8266 Wifi board to:
1. Connect to your wifi network.
2. Create a local IP address.
3. Activate a red or green LED when the ip address is entered in the address bar followed by `/good` (for green) or `/bad` (for red).

**How the circuit is intended to look:**


![circuit](https://user-images.githubusercontent.com/48888771/133632875-ac814622-df34-4beb-b090-c3be799613d5.png)


# How to use this:
1. Copy the code to your Arduino IDE.
2. Edit the config part with your wifi SSID and Password:
```cpp
const char* ssid     = "WIFI_NAME";
const char* password = "WIFI_PASSWORD"; 
```
3. Build a circuit that look more or less as the one in the picture above.
4. Compile, and run the code on your Arduino.
5. Connect to the IP address and type in `/good` or `/bad` as the path.
6. If all goes as plan, your components should go on!


Have Fun!
