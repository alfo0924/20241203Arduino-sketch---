
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6a5aCTY4h"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "KOZ0vVcmLTIWwJe_GGglcabiZyD0Msxw"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

#define DHTPIN 16
#define DHTTYPE DHT11
#define BUTTON_PIN 17
#define LED_PIN 4

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
char ssid[] = "alfredojayjaylin";
char pass[] = "9987321wificode";

// 按鈕防彈跳變數
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState = HIGH;
bool flag = false;

void setup() {
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(DHTPIN, OUTPUT);

    Serial.println("DHT11 test!");
    dht.begin();
}

void loop() {
    Blynk.run();
    
    // 按鈕防彈跳處理
    int reading = digitalRead(BUTTON_PIN);
    
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            
            if (buttonState == LOW && !flag) {
                Blynk.virtualWrite(V3, "Button Down");
                flag = true;
                Serial.println("down");
            } else if (buttonState == HIGH && flag) {
                Blynk.virtualWrite(V3, "Button Up");
                Serial.println("up");
                flag = false;
            }
        }
    }
    
    lastButtonState = reading;

    // DHT11 感測器讀取
    static unsigned long lastDHTReadTime = 0;
    if (millis() - lastDHTReadTime > 2000) {
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        
        if (!isnan(h) && !isnan(t)) {
            Serial.print("濕度: ");
            Serial.print(h);
            Serial.print("% 溫度: ");
            Serial.print(t);
            Serial.println("°C");

            String humidity_str = String(h, 2);
            String temperature_str = String(t, 2);
            Blynk.virtualWrite(V16, "濕度" + humidity_str + " 溫度" + temperature_str);
        } else {
            Serial.println("無法從DHT感測器讀取數據！");
        }
        
        lastDHTReadTime = millis();
    }
}

BLYNK_WRITE(V0) {
    int value = param.asInt();
    digitalWrite(LED_PIN, value);
    Serial.println(value);
}
