# 🌡️ SHT20 溫濕度監控系統（STM32 + WinForm + OLED）

本專案整合STM32韌體、OLED顯示與C#監控介面，透過I2C從SHT20感測器讀取溫濕度資料，並使用UART傳送至 PC 端顯示，同時使用SPI傳送數據至OLED顯示即時資訊，構成一套完整的即時監控系統。


## 🔗 子專案連結

- 🔌 [👉 韌體原始碼 - STM32 專案](https://github.com/siliva180sx/SHT20_Monitor_STM32/tree/main/STM32_SHT20_Sensor)
- 🖥️ [👉 監控介面原始碼 - WinForms GUI](https://github.com/siliva180sx/SHT20_Monitor_STM32/tree/main/SHT20_Monitor)

---

## 🖼️ 監控介面 GUI 預覽圖

![GUI預覽畫面](https://github.com/siliva180sx/SHT20_Monitor_STM32/blob/main/%E7%9B%A3%E6%8E%A7%E4%BB%8B%E9%9D%A2.PNG)

---

## 🔧 功能說明

### ✅ 韌體功能（STM32）
- 使用STM32F103ZET6的MCU（標準庫）
- I2C通訊讀取SHT20溫濕度感測器資料
- 資料以 UART 傳送至電腦（預設 115200 baud）
- SPI顯示功能：使用SH1106的OLED模組，透過SPI顯示目前溫度與濕度資料
- 顯示格式：可切換 °C / °F 顯示單位，搭配外部按鍵中斷實現單位切換
- 顯示內容：溫度、濕度
- 使用模組化方式撰寫：`bsp_usart`, `bsp_i2c`, `bsp_aht20`, `bsp_spi_oled`, `bsp_exti`


### ✅ 監控介面功能（WinForm）
- 使用C#開發WinForm介面
- 串口參數可設定（COM 埠、數據位、停止位）
- 即時顯示溫度/濕度數據（Chart圖表同步顯示）

---

## 🧰 開發工具與環境

| 項目       | 工具                  |
|------------|---------------------- |
| MCU 開發   | Keil uVision 5        |
| 監控介面     | Visual Studio 2019    |
| 通訊協定   | SPI、I2C、UART        |
| 其他       | SunnyUI 套件(WinForm) |


---

## 📫 聯絡方式
- 姓名：黃文廷
- 電子郵件：kenken0981002806@gmail.com

