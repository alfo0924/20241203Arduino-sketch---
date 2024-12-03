#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6a5aCTY4h"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "KOZ0vVcmLTIWwJe_GGglcabiZyD0Msxw"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials
char ssid[] = "";
char pass[] = "";

void setup()
{
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    pinMode(4, OUTPUT);
}

void loop()
{
    Blynk.run();

}

BLYNK_WRITE(V0){
  int value = param.asInt(); //Get value as integer
  digitalWrite(4, value);
  Serial.print(23);
}
