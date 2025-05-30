#define BLYNK_TEMPLATE_ID "TMPLxxxxxxx"
#define BLYNK_TEMPLATE_NAME "YourTemplateName"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxx"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char ssid[] = "Nuju Coffee Kedaton";
char pass[] = "zozogakmahallagi";

// ===== KONFIGURASI PIN =====
#define DHTPIN D2                        // D4 = GPIO2, D2 = GPIO4 (sesuaikan dgn board kamu)
#define DHTTYPE DHT22
const int pirPin = D1;                  // sesuaikan dengan wiring di ESP8266 kamu
const int ledGerak = D5;
const int ledSuhuTinggi = D6;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

void kirimDataKeBlynk() {
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();
  int motion = digitalRead(pirPin);

  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembapan);
  Blynk.virtualWrite(V2, motion == HIGH ? "Terdeteksi" : "Tidak");

  digitalWrite(ledGerak, motion == HIGH ? HIGH : LOW);
  digitalWrite(ledSuhuTinggi, suhu > 35 ? HIGH : LOW);

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(suhu);
  lcd.print((char)223);
  lcd.print("C H:");
  lcd.print(kelembapan);
  lcd.print("% ");

  lcd.setCursor(0, 1);
  lcd.print("Gerak: ");
  lcd.print(motion == HIGH ? "TERDETEKSI " : "TIDAK     ");

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" C, Kelembapan: ");
  Serial.print(kelembapan);
  Serial.print(" %, Gerakan: ");
  Serial.print(motion == HIGH ? "Terdeteksi" : "Tidak");
  Serial.print(", Suhu Tinggi: ");
  Serial.println(suhu > 35 ? "YA" : "TIDAK");
}

void setup() {
  Serial.begin(115200);

  pinMode(pirPin, INPUT);
  pinMode(ledGerak, OUTPUT);
  pinMode(ledSuhuTinggi, OUTPUT);

  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  WiFi.begin(ssid, pass);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, kirimDataKeBlynk);
}

void loop() {
  Blynk.run();
  timer.run();
}
