#define BLYNK_PRINT Serial        // 將 Blynk 的輸出訊息導向序列埠監控
#define BLYNK_TEMPLATE_ID "TMPL6a5aCTY4h"  // Blynk 應用程式模板 ID (範例為快速入門模板)
#define BLYNK_TEMPLATE_NAME "Quickstart Template"  // Blynk 應用程式模板名稱
#define BLYNK_AUTH_TOKEN "KOZ0vVcmLTIWwJe_GGglcabiZyD0Msxw"  // Blynk 授權碼 (請從 Blynk 雲端取得)

#include <WiFi.h>                  // Wi-Fi 函式庫
#include <WiFiClient.h>            // Wi-Fi 客戶端函式庫
#include <BlynkSimpleEsp32.h>       // Blynk SimpleEsp32 函式庫

// Wi-Fi 網路名稱和密碼 (請填寫您的資訊)
char ssid[] = "";
char pass[] = "";

void setup() {
  Serial.begin(115200);        // 初始化序列埠監控 (波特率 115200 bps)
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // 初始化 Blynk 連線 (授權碼、SSID、密碼)

  // 設定腳位模式
  pinMode(4, OUTPUT);         // 設定第 4 號數位腳位為輸出模式 (控制 LED)
  pinMode(17, INPUT_PULLUP);  // 設定第 17 號數位腳位為輸入模式，並啟用上拉電阻 (偵測按鈕)
}

bool flag = 0;  // 初始化布林變數，用於防呆

void loop() {
  Blynk.run();  // 執行 Blynk 後台處理 (維持連線及監控虛擬埠)

  // 讀取按鈕狀態 (按下為 LOW, 放開為 HIGH)
  bool button_value = digitalRead(17);

  // 偵測按鈕按下 (避免連續送出訊息)
  if (!button_value && !flag) {
    Blynk.virtualWrite(V3, "Button Down");  // 透過 V3 虛擬埠發送 "Button Down" 訊息到 Blynk 應用程式
    Serial.println("down");                // 在序列埠監控輸出 "down"
    flag = 1;                               // 更新旗標，避免連續送出訊息
  }

  // 偵測按鈕放開 (避免連續送出訊息)
  else if (button_value && flag) {
    Blynk.virtualWrite(V3, "Button Up");    // 透過 V3 虛擬埠發送 "Button Up" 訊息到 Blynk 應用程式
    Serial.println("up");                  // 在序列埠監控輸出 "up"
    flag = 0;                               // 更新旗標，準備偵測下一次按下
  }
}

BLYNK_WRITE(V0) {
  int value = param.asInt(); // 取得從 Blynk 應用程式發送的整數值
  digitalWrite(4, value);   // 控制第 4 號數位腳位的電位 (控制 LED 亮灭)
  Serial.print(23);          // 序列埠監控輸出數字 23 (可修改為有意義的訊息)
}
