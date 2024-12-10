// 定義Blynk相關設定
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6a5aCTY4h"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "KOZ0vVcmLTIWwJe_GGglcabiZyD0Msxw"

// 引入需要的函式庫
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

// WiFi連線設定
char ssid[] = "alfredojayjaylin";    // WiFi名稱
char pass[] = "9987321wificode";      // WiFi密碼

// 宣告硬體計時器指標，初始值為空
hw_timer_t * timer = NULL;

// 宣告計數器變數，用於追蹤執行次數
int counter = 0;

// 定義DHT11溫濕度感測器設定
#define DHTPIN 16     // DHT11連接到ESP32的腳位16
#define DHTTYPE DHT11 // 指定使用DHT11感測器型號
DHT dht(DHTPIN, DHTTYPE);

// 定義中斷服務程序（ISR）
// 當計時器觸發中斷時，此函數會被呼叫
// 功能：將腳位4的輸出狀態反轉（HIGH變LOW或LOW變HIGH）
void ARDUINO_ISR_ATTR interrupt_func() {
    digitalWrite(4, !digitalRead(4));
}

// 定義傳送感測器數據到Blynk的函數
void sendSensor() {
    // 讀取濕度值
    float h = dht.readHumidity();
    
    // 檢查讀取是否成功
    if (isnan(h)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    
    // 將濕度數據傳送到Blynk的虛擬腳位V16
    Blynk.virtualWrite(V16, h);
}

// 初始化設定
void setup() {
    // 設定序列埠通訊速率
    Serial.begin(115200);
    // 設定腳位4為輸出模式
    pinMode(4, OUTPUT);
    
    // 初始化DHT11感測器
    dht.begin();
    
    // 連接到Blynk雲端平台
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    
    // 初始化計時器
    // 設定clock頻率
    timer = timerBegin(100000);
    // 設定中斷函式
    timerAttachInterrupt(timer, &interrupt_func);
    // 設定進入中斷函式的頻率
    timerAlarm(timer, 100000, true, 0);

    // 檢查計時器是否成功初始化
    if(timer == NULL) {
        Serial.println("Error occur in setting timer");
    }
}

// 主程式迴圈
void loop() {
    // 運行Blynk程序
    Blynk.run();
    
    // 讀取濕度數值
    float humidity = dht.readHumidity();
    
    // 檢查讀取是否成功並輸出
    if (isnan(humidity)) {
        Serial.println("Failed to read humidity from DHT sensor!");
    } else {
        // 輸出濕度數值到序列埠
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println("%");
        // 將濕度數據傳送到Blynk的虛擬腳位V16
        Blynk.virtualWrite(V16, humidity);
    }
    
    // 計數器相關操作
    Serial.print("Counter: ");
    Serial.println(counter);
    counter++;
    
    // 延遲1秒
    delay(1000);
}
