# 💧 AQUASENSE — Industrial Water Leakage Detection System

An ESP32-based IoT water leakage detection system that monitors **3 analog sensor zones** and **4 pipeline leak points**, displays real-time status on an OLED screen, and triggers a **buzzer + red LED alarm** on detection.

Built and simulated entirely in [Wokwi](https://wokwi.com).

🔗 **Live Simulation:** [https://wokwi.com/projects/479522170151266305](https://wokwi.com/projects/479522170151266305)

---

## ✨ Features

- 🌊 Monitors **3 analog zones** (flow/pressure sensors via ADC)
- 🚰 Detects leakage at **4 pipeline points** (Main + 3 Branches) via pushbuttons
- 📟 Real-time status on a **128×64 SSD1306 OLED** (I2C)
- 🔔 **Audible + visual alarm** — buzzer (2 kHz) + red LED on leak
- 🟢 Green LED indicates system normal
- 🖥️ Serial monitor logging every 500 ms
- ⚙️ Adjustable leak threshold (`threshold = 2000` on 12-bit ADC)

---

## 🧰 Hardware / Components

|        Component       | Wokwi Part  | ESP32 Pin |   Function     |
|------------------------|-------------|-----------|----------------|
| Analog Sensor — Zone 1 | `pot1`      | GPIO 34   | ADC input      |
| Analog Sensor — Zone 2 | `pot2`      | GPIO 33   | ADC input      |
| Analog Sensor — Zone 3 | `pot3`      | GPIO 32   | ADC input      |
| Main Pipe Leak Button  | `btn1`      | GPIO 14   | `INPUT_PULLUP` |
| Branch 1 Leak Button   | `btn2`      | GPIO 16   | `INPUT_PULLUP` |
| Branch 2 Leak Button   | `btn4`      | GPIO 17   | `INPUT_PULLUP` |
| Branch 3 Leak Button   | `btn3`      | GPIO 13   | `INPUT_PULLUP` |
| Buzzer                 | `bz1`       | GPIO 25   | Alarm tone     |
| Red LED (alarm)        | `led1`(`r1`)| GPIO 26   | Leak indicator |
| Green LED (normal)     | `led2`(`r3`)| GPIO 27   | NormalIndicator|
| OLED SDA               | `oled1`     | GPIO 21   | I2C data       |
| OLED SCL               | `oled1`     | GPIO 22   | I2C clock      |
| OLED Address           | ----------- | `0x3C`    | SSD1306        |
|------------------------|-------------|-----------|----------------|
---

## ⚡ How It Works

1. **Analog sensing** — three potentiometers simulate water-flow/pressure sensors. Each reading is compared to `threshold` (2000). Above it → leak in that zone.
2. **Pipeline monitoring** — four pushbuttons simulate leak points on the main pipe and three branches. A pressed button (`LOW`) = leak.
3. **Logic** — if **any** of the 7 inputs reports a leak, `leakageDetected` becomes `true`.
4. **Response** —
   - **Leak:** 🔴 Red LED ON, 🟢 Green LED OFF, 🔔 buzzer @ 2000 Hz
   - **Normal:** 🟢 Green LED ON, 🔴 Red LED OFF, buzzer silent
5. **Display** — OLED shows `AQUASENSE INDUSTRIAL`, overall status, and per-zone / per-branch status (`LEAK` / `OK`).
6. **Logging** — all values are printed to Serial @ 115200 baud.

---

## 📚 Libraries

Adafruit GFX Library
Adafruit SSD1306

Also requires the built-in **Wire** library (bundled with Arduino).

Install via Arduino IDE → *Sketch → Include Library → Manage Libraries*.

---

## 🚀 Getting Started

### Option A — Simulate on Wokwi (no hardware)
1. Open (https://wokwi.com/projects/479522170151266305)
2. Click ▶️ **Play**
3. Turn the potentiometers above ~2000 or press any button → alarm triggers

### Option B — Run on real hardware
1. Wire the ESP32 as per the pin table above
2. Open `aquasense.ino` in Arduino IDE
3. Install the two Adafruit libraries
4. Select **ESP32 Dev Module** → Upload



## 🔮 Future Improvements

- 📶 Publish sensor data to MQTT / Blynk / ThingSpeak (ESP32 Wi-Fi)
- 📱 Push notifications via Telegram or Blynk app
- 🗄️ Log leak events to SD card or cloud database
- 🎚️ Make threshold configurable via OLED menu
- 🔋 Add deep-sleep mode for battery operation
- 🧠 Add leak-location classification using pressure-drop patterns

---

## 👤 Author

**Your Name**
- LinkedIn: https://www.linkedin.com/in/ameer-hamza-442093318?utm_source=share_via&utm_content=profile&utm_medium=member_android
- GitHub: https://github.com/ameerhamza43

---

## 📄 License

MIT License — free to use, modify, and share.
