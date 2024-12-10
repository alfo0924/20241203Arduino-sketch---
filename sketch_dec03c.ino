#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6a5aCTY4h"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "KOZ0vVcmLTIWwJe_GGglcabiZyD0Msxw"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

// WiFi設定
char ssid[] = "alfredojayjaylin";
char pass[] = "9987321wificode";

// 宣告硬體計時器指標
hw_timer_t * timer = NULL;

// 宣告計數器變數
int counter = 0;

// 定義DHT11感測器
#define DHTPIN 16     // DHT11連接到腳位16
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

// 定義中斷服務程序
void ARDUINO_ISR_ATTR interrupt_func() {
    digitalWrite(4, !digitalRead(4));
}

// 定義傳送感測器數據到Blynk的函數
void sendSensor() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();  // 讀取溫度
    
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    
    // 將濕度和溫度數據傳送到Blynk的虛擬腳位
    Blynk.virtualWrite(V16, h);  // 濕度傳送到V16
    Blynk.virtualWrite(V17, t);  // 溫度傳送到V17
}

void setup() {
    Serial.begin(115200);
    pinMode(4, OUTPUT);
    
    // 初始化DHT11感測器
    dht.begin();
    
    // 連接到Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    
    // 初始化計時器
    timer = timerBegin(100000);
    timerAttachInterrupt(timer, &interrupt_func);
    timerAlarm(timer, 100000, true, 0);

    if(timer == NULL) {
        Serial.println("Error occur in setting timer");
    }
}

void loop() {
    Blynk.run();
    
    // 讀取溫濕度數值
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();  // 讀取溫度
    
    // 檢查讀取是否成功並輸出
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
    } else {
        // 輸出濕度數值
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println("%");
        
        // 輸出溫度數值
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println("°C");
        
        // 將溫濕度數據傳送到Blynk
        Blynk.virtualWrite(V16, humidity);  // 濕度傳送到V16
        Blynk.virtualWrite(V17, temperature);  // 溫度傳送到V17
    }
    
    // 計數器相關操作
    Serial.print("Counter: ");
    Serial.println(counter);
    counter++;
    
    delay(1000);
}
