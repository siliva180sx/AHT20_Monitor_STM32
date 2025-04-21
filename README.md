# 🌡️ AHT20 溫濕度監控系統（STM32 + WinForms 上位機 + OLED）

本專案整合STM32韌體、OLED顯示與C#上位機，透過I2C從AHT20感測器讀取溫濕度資料，並使用UART傳送至 PC 端顯示，同時SPI傳送數據至OLED顯示即時資訊，構成一套完整的即時監控系統。


## 🔗 子專案連結

- 🔌 [👉 韌體原始碼 - STM32 專案](https://github.com/siliva180sx/AHT20_Monitor_STM32/tree/main/STM32_AHT20_GitHub)
- 🖥️ [👉 上位機原始碼 - WinForms GUI](https://github.com/siliva180sx/AHT20_Monitor_STM32/tree/main/AHT20_Monitor_GitHub)

---

## 🖼️ 上位機 GUI 預覽圖

![GUI預覽畫面]([https://github.com/siliva180sx/AHT20_Monitor_STM32/raw/main/AHT20_Monitor_GitHub/img/screenshot.png](https://github.com/siliva180sx/AHT20_Monitor_STM32/tree/main/img))

---

## 🔧 功能說明

### ✅ 韌體功能（STM32）
- 使用STM32F103ZET6的MCU（標準庫）
- I2C通訊讀取AHT20溫濕度感測器資料
- 資料以 UART 傳送至電腦（預設 115200 baud）
- SPI顯示功能：使用SH1106的OLED模組，透過SPI顯示目前溫度與濕度資料
- 顯示格式：可切換 °C / °F 顯示單位，搭配外部按鍵中斷實現單位切換
- 顯示內容：溫度、濕度、單位標示，未來可擴充顯示時間、警報等資訊
- 使用模組化方式撰寫：`bsp_usart`, `bsp_i2c`, `bsp_aht20`, `bsp_spi_oled`, `bsp_exti`


### ✅ 上位機功能（WinForm）
- 使用C#開發WinForm介面
- 串口參數可設定（COM 埠、數據位、停止位）
- 即時顯示溫度/濕度數據（Chart圖表同步顯示）
- Start/Stop資料流控制

---

## 🧰 開發工具與環境

| 項目 | 工具 |
|------|------|
| MCU 開發 | Keil uVision 5 |
| 上位機 | Visual Studio 2019 / 2022 |
| 通訊協定 | SPI（顯示器）、I2C（感測器）、UART（電腦） |
| 其他 | SunnyUI 套件|

---

## 📫 聯絡方式

黃文廷  
📧 kenken0981002806@gmail.com

