#include <ESP8266WiFi.h>

const char* ssid     = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";

WiFiServer server(80);

String header;

String output5State = "off";
String output4State = "off";

const int output5 = 5                   ;
const int output4 = 4;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.begin();
}

void loop(){
  WiFiClient client = server.available();   

  if (client) {                             
    String currentLine = "";                
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();         
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                   
        header += c;
        if (c == '\n') {                   
          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 420 NOICE");
            client.println("Content-type: YES");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /good") >= 0) {
              Serial.println("GREEN ON");
              output4State = "on";
              digitalWrite(output4, HIGH);
              delay(2000);
              Serial.println("GREEN OFF");
              output4State = "off";
              digitalWrite(output4, LOW);
              
            } else if (header.indexOf("GET /bad") >= 0) {
              Serial.println("RED ON");
              output5State = "on";
              digitalWrite(output5, HIGH);
              delay(2000);
              Serial.println("RED OFF");
              output5State = "off";
              digitalWrite(output5, LOW);
              
       
            } else if (header.indexOf("GET /") >= 0) {
              Serial.println("RED");
              output5State = "off";
              digitalWrite(output5, LOW);
              Serial.println("GREEN");
              output5State = "off";
              digitalWrite(output5, LOW);
            } 
            
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;      
        }
      }
    }
    
    header = "";
    client.stop();
  }
}

/* Built off a template made by Rui Santos, which I modified to fit better with this project */
