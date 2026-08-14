#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_PROJECT_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";
#define DHTPIN 4
#define DHTTYPE DHT11
#define SOIL_PIN 34
#define WATER_PIN 35
#define RELAY 23
LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
int pumpStatus = 0;
bool manualPump = false;
// Replace CITY_NAME and API_KEY
String weatherURL =
"http://api.openweathermap.org/data/2.5/weather?q=CITY_NAME&appid=YOUR_WEATHER_API_KEY&units=
metric";
float outsideTemp = 0;
float outsideHum = 0;
String conditionTxt = "";
void getWeather() {
 if (WiFi.status() == WL_CONNECTED) {
 HTTPClient http;
 http.begin(weatherURL);
 int httpCode = http.GET();
 if (httpCode == 200) {
 String payload = http.getString();
 DynamicJsonDocument doc(2048);
 deserializeJson(doc, payload);
 outsideTemp = doc["main"]["temp"];
 outsideHum = doc["main"]["humidity"];
 conditionTxt = String(doc["weather"][0]["main"].as<const char*>());
 Blynk.virtualWrite(V6, outsideTemp);
 Blynk.virtualWrite(V7, outsideHum);
 Blynk.virtualWrite(V8, conditionTxt);
 Serial.println("Weather Updated");
 }
 http.end();
 }
}
BLYNK_WRITE(V5)
{
 int val = param.asInt();
 if(val == 1){
 manualPump = true;
 digitalWrite(RELAY, LOW);
 pumpStatus = 1;
 }
 else{
 manualPump = false;
 }
 Blynk.virtualWrite(V4, pumpStatus);
}
void sendData()
{
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 int soil = analogRead(SOIL_PIN);
 soil = map(soil, 4095, 0, 0, 100);
 int water = analogRead(WATER_PIN);
 water = map(water, 0, 4095, 0, 100);
 if(!manualPump)
 {
 if(soil < 40 && water > 20){
 digitalWrite(RELAY, LOW);
 pumpStatus = 1;
 }
 else{
 digitalWrite(RELAY, HIGH);
 pumpStatus = 0;
 }
 }
 Blynk.virtualWrite(V0, t);
 Blynk.virtualWrite(V1, h);
 Blynk.virtualWrite(V2, soil);
 Blynk.virtualWrite(V3, water);
 Blynk.virtualWrite(V4, pumpStatus);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("T:");
 lcd.print(t);
 lcd.print("C H:");
 lcd.print(h);
 lcd.setCursor(0,1);
 lcd.print("Soil:");
 lcd.print(soil);
 lcd.print("% W:");
 lcd.print(water);
 display.clearDisplay();
 display.setTextSize(1);
 display.setCursor(0,0);
 display.print("Soil: ");
 display.print(soil);
 display.println("%");
 display.print("Water: ");
 display.print(water);
 display.println("%");
 display.print("Pump: ");
 display.println(pumpStatus ? "ON" : "OFF");
 display.print("Out:");
 display.print(outsideTemp);
 display.println("C");
 display.print("Hum:");
 display.print(outsideHum);
 display.println("%");
 display.display();
}
void setup()
{
 Serial.begin(115200);
 pinMode(RELAY, OUTPUT);
 digitalWrite(RELAY, HIGH);
 dht.begin();
 lcd.init();
 lcd.backlight();
 lcd.setCursor(0,0);
 lcd.print("Smart Irrigation");
 lcd.setCursor(0,1);
 lcd.print("Initializing...");
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
 while(1);
 }
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(0,10);
 display.println("Smart Irrigation");
 display.display();
 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 timer.setInterval(1500L, sendData);
 timer.setInterval(60000L, getWeather);
}
void loop()
{
 Blynk.run();
 timer.run();
}