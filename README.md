# Smart-Irrigation-System-IOT

# 🌱 Smart Irrigation System using ESP32 & Blynk IoT

A Smart Irrigation System built using **ESP32** and **Blynk IoT** that monitors soil moisture and environmental conditions to automate irrigation. The system helps conserve water by automatically controlling the water pump while allowing real-time monitoring and manual control through the Blynk mobile app.

---

## ✨ Features

- 🌱 Automatic irrigation based on soil moisture
- 📱 Remote monitoring with Blynk IoT
- 💧 Automatic & manual pump control
- 🌡️ Temperature and humidity monitoring
- 🌧️ Rain detection
- 💦 Water level monitoring
- ☀️ Light intensity monitoring
- 📊 Real-time sensor data dashboard

---

## 🛠️ Hardware Used

- ESP32 DevKit V1
- Soil Moisture Sensor
- DHT11 Sensor
- Rain Sensor
- Water Level Sensor
- LDR Sensor
- Relay Module
- DC Water Pump

---

## 💻 Software & Libraries

**Software**
- Arduino IDE
- Blynk IoT

**Libraries**
- WiFi.h
- BlynkSimpleEsp32.h
- DHT.h

---

## 🔌 Pin Configuration

| Component | GPIO |
|-----------|------|
| DHT11 | 4 |
| Soil Moisture | 34 |
| Water Level | 33 |
| Rain Sensor | 32 |
| LDR | 35 |
| Relay | 23 |

---

## ⚙️ Working

1. ESP32 reads sensor values.
2. Data is sent to the Blynk dashboard.
3. If soil moisture is below the threshold, the pump turns **ON**.
4. When sufficient moisture or rain is detected, the pump turns **OFF**.
5. Users can also control the pump manually from the Blynk app.

---


## 🚀 Future Scope

- Weather API integration
- Firebase/Cloud storage
- AI-based irrigation prediction
- Solar-powered system
- Multi-farm monitoring

---

## 👨‍💻 Made By : 

**Prince Patel**

**Yash Suba**  
**Aastha Thakkar**  
**Palak Patel**  


⭐ If you found this project useful, consider giving it a **Star** on GitHub!
