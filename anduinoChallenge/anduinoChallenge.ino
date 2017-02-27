// Libraries
#include <WiFi101.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// WiFi parameters
#define WLAN_SSID       "AndiumNetwork"
#define WLAN_PASS       "co2nodes"

// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "samir5421"
#define AIO_KEY         "6ac6657ff6ea4c8a89334e3cc8c652fb"

// pin numbers
const int buttonPin = 1;     // the number of the pushbutton pin
const int ledPin =  LED_BUILTIN;      // the number of the LED pin

int buttonState = 0;         // variable for reading the pushbutton status

// Functions
void connect();

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

Adafruit_MQTT_Publish message = Adafruit_MQTT_Publish(&mqtt,  AIO_USERNAME "/feeds/Andium");

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);
  Serial.println(F("Pub/Sub for Adafruit.IO"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());

  // connect to adafruit io
  connect();

}

void loop() 
{

  buttonState = digitalRead(buttonPin);

  if(! mqtt.ping(3)) {
   // reconnect to adafruit io
   if(! mqtt.connected()) {
     connect();
   }
  }

  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("sending msg");
    message.publish("This msg is sent to adafruit.io");
    delay(3000); // wait 3 seconds
  } else {
    digitalWrite(ledPin, LOW);
  }
 

}


// connect to adafruit io via MQTT
void connect() {

  Serial.print(F("Connecting to Adafruit IO... "));

  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(5000);

  }

  Serial.println(F("Adafruit IO Connected!"));

}

