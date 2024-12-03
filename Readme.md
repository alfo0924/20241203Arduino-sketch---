# 20241203 sketch_dec03a.ino

這段程式碼是用於控制 ESP32 開發板，並透過 Blynk 手機應用程式進行互動。

**程式碼包含以下部分：**

* **前置設定 (Preprocessing):**
    * `#define BLYNK_PRINT Serial`: 將 Blynk 的輸出訊息導向序列埠監控 (Serial monitor)。
    * `#define BLYNK_TEMPLATE_ID` 和 `#define BLYNK_TEMPLATE_NAME`: 定義 Blynk 應用程式的模板 ID 和名稱 (範例使用的是快速入門模板)。
    * `#define BLYNK_AUTH_TOKEN`: 定義 Blynk 應用程式的授權碼 (需從 Blynk 雲端取得，请注意出于安全考量，不要将您的授权码泄露给他人)。
    * 引用必要的函式庫:
        * `WiFi.h`: 用於連接 Wi-Fi 網路。
        * `WiFiClient.h`: 用於建立 Wi-Fi 客戶端連線。
        * `BlynkSimpleEsp32.h`: 用於 Blynk SimpleEsp32 函式庫。
* **Wi-Fi 憑證 (WiFi Credentials):**
    * `char ssid[] = "";`: 用於儲存 Wi-Fi 網路名稱 (SSID)。
    * `char pass[] = "";`: 用於儲存 Wi-Fi 網路密碼 (預設為空)。 **請記得在此處填寫您的 Wi-Fi 網路資訊。**

* **設定 (setup) 函式:**
    * `Serial.begin(115200);`: 初始化序列埠監控，設定傳輸速率為 115200 bps。
    * `Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);`: 初始化 Blynk 連線，提供授權碼、SSID 和密碼。

* **迴圈 (loop) 函式:**
    * `Blynk.run();`: 執行 Blynk 的後台處理，維持連線並監控虛擬埠 (virtual pin) 的變化。

* **BLYNK_WRITE(V0) 虛擬埠寫入事件:**
    * `int value = param.asInt();`: 取得從 Blynk 應用程式發送的整數值。
    * `digitalWrite(4, value);`: 將讀取到的整數值寫入 ESP32 的第 4 號數位腳位 (digital pin 4)，控制其高低電位 (HIGH/LOW)。

**簡單來說，這段程式碼的功能是：**

1. 連接 Wi-Fi 網路 (需填寫您的 Wi-Fi 資訊)。
2. 連接到 Blynk 雲端，使用您設定的授權碼。
3. 在 Blynk 應用程式中建立一個控制元件 (例如按鈕或開關)，連結到 V0 虛擬埠。
4. 當您操作 Blynk 應用程式的控制元件時，會觸發 Blynk.write 事件，將該值傳送給 ESP32。
5. ESP32 讀取該值，並控制第 4 號數位腳位的電位，例如控制 LED 的亮灭。

