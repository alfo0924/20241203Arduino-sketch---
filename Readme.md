# sketch_dec03a.ino

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


#  sketch_dec03b.ino



這段程式碼利用 Blynk SimpleEsp32 函式庫，讓 ESP32 開發板與 Blynk 手機應用程式進行互動，並控制一個按鈕和 LED 燈。

* **前置設定 (Preprocessing):**
    * 定義 Blynk 相關設定 (與之前分析相似)。
    * 引用必要的函式庫:
        * `WiFi.h`: 用於連接 Wi-Fi 網路。
        * `WiFiClient.h`: 用於建立 Wi-Fi 客戶端連線。
        * `BlynkSimpleEsp32.h`: 用於 Blynk SimpleEsp32 函式庫。
* **Wi-Fi 憑證 (WiFi Credentials):**
    * 定義 Wi-Fi 網路名稱 (SSID) 和密碼 (請填寫您的 Wi-Fi 資訊)。

* **設定 (setup) 函式:**
    * 初始化序列埠監控和 Blynk 連線 (與之前分析相似)。
    * `pinMode(4, OUTPUT);`: 設定第 4 號數位腳位為輸出模式，用於控制 LED。
    * `pinMode(17, INPUT_PULLUP);`: 設定第 17 號數位腳位為輸入模式，並啟用內部上拉電阻，用於檢測按鈕狀態。
    * `bool flag = 0;`: 初始化一個布林變數 `flag` 用於防呆，避免按鈕按下時連續送出訊息。

* **迴圈 (loop) 函式:**
    * 執行 Blynk 後台處理。
    * `bool button_value = digitalRead(17);`: 讀取第 17 號數位腳位的電位值，代表按鈕的狀態 (按下為 LOW, 放開為 HIGH)。
    * 按鈕狀態改變且 `flag` 為 0 時 (表示按鈕剛按下):
        * `Blynk.virtualWrite(V3, "Button Down");`: 透過 V3 虛擬埠發送訊息 "Button Down" 到 Blynk 應用程式。
        * `Serial.println("down");`: 在序列埠監控輸出 "down"。
        * 將 `flag` 更新為 1，避免連續送出訊息。
    * 按鈕狀態改變且 `flag` 為 1 時 (表示按鈕剛放開):
        * `Blynk.virtualWrite(V3, "Button Up");`: 透過 V3 虛擬埠發送訊息 "Button Up" 到 Blynk 應用程式。
        * `Serial.println("up");`: 在序列埠監控輸出 "up"。
        * 將 `flag` 更新為 0，準備偵測下一次按下。

* **BLYNK_WRITE(V0) 虛擬埠寫入事件:** (與之前分析相似)
    * 讀取從 Blynk 應用程式發送的整數值。
    * 控制第 4 號數位腳位的電位，例如控制 LED 的亮灭 (需搭配 Blynk 應用程式設定 V0 虛擬埠的輸出功能)。
    * 在序列埠監控輸出數字 23 (意義不明確，可能為測試訊息)。

**Blynk 應用程式設定:**

* 需要在 Blynk 應用程式中建立以下元件:
    * 一個按鈕 (Button)，連結到 V3 虛擬埠，用於顯示按鈕的狀態。
    * (可选) 任何可以輸出數值的元件 (例如滑塊或數值輸入框)，連結到 V0 虛擬埠，用於控制 LED 燈。

**程式碼運作流程:**

1. 連接 Wi-Fi 網路和 Blynk 雲端。
2. 初始化 LED 和按鈕的腳位設定。
3. 監控按鈕狀態，並透過 Blynk 應用程式顯示按鈕的按下 (Down) 和放開 (Up)。
4. (可选) 接收 Blynk 應用程式發送的數值，控制 LED 燈的亮灭。

**额外的注意:**

* 序列埠監控輸出數字 23 的意義不明確，可以将其删除或修改为有意义的訊息。
* Blynk 應用程式的設定需要根据您的需求进行调整。


* 程式碼導入必要的 Blynk、WiFi 等函式庫。
* 定義 Wi-Fi 網路名稱、密碼和 Blynk 授權碼 (請填寫您的資訊)。
* `setup` 函式初始化序列埠監控、Blynk 連線，並設定 LED 和按鈕的腳位模式。
* `loop` 函式透過 Blynk 監控 V0 虛擬埠的數值變化，並控制 LED 的亮灭。
    * 同時監控按鈕的狀態，並透過 V3 虛擬埠發送按鈕的按下 (Down) 和放開 (Up) 訊息到 Blynk 應用程式。
    * `flag` 變數用於防呆，避免按鈕連續按下時重複送出訊息。
* `BLYNK_WRITE(V0)` 函式處理 Blynk 應用程式發送來的數值，
