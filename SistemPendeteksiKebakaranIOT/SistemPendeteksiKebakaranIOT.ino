#define BLYNK_TEMPLATE_ID "TMPLxxxxxxx"
#define BLYNK_TEMPLATE_NAME "YourTemplateName"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxx"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define BLYNK_PRINT Serial

// === Konfigurasi Pin ===
#define DHTPIN D5
#define DHTTYPE DHT11
#define ledMerah D2
#define ledHijau D1
#define BuzzerPin D3
#define servoPin D4

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// === Objek dan Variabel ===
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
WidgetLCD lcd1(V2);

const float suhuAmbang = 40.0;
unsigned long lastUpdate = 0;
const unsigned long interval = 2000;

BLYNK_WRITE(V3) {
  int switchValue = param.asInt();
  if (switchValue == 1) {
    digitalWrite(ledMerah, HIGH);
    digitalWrite(ledHijau, LOW);
    tone(BuzzerPin, 250);
    myservo.write(180);
    lcd1.clear();
    lcd1.print(0, 0, "Ada Api Berbahaya!!");
    Blynk.logEvent("kebakaran", "Ada Api Berbahaya!!!");
  } else {
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, HIGH);
    noTone(BuzzerPin);
    myservo.write(0);
    lcd1.clear();
    lcd1.print(0, 0, "Aman Dari Api");
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Sensor DHT11");
  lcd.setCursor(0, 1);
  lcd.print("Membaca nilai...");

  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);

  dht.begin();
  myservo.attach(servoPin);
  myservo.write(0);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  Blynk.run();
  unsigned long now = millis();

  if (now - lastUpdate >= interval) {
    lastUpdate = now;
    bacaSensorDanTindak();
  }
}

void bacaSensorDanTindak() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Gagal membaca sensor DHT11");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Kelembaban: ");
  lcd.print(humidity);
  lcd.print(" %");

  if (temperature > suhuAmbang) {
    digitalWrite(ledMerah, HIGH);
    digitalWrite(ledHijau, LOW);
    tone(BuzzerPin, 250);
    myservo.write(180);
    lcd1.clear();
    lcd1.print(0, 0, "Ada Api Berbahaya!!");
    Blynk.logEvent("kebakaran", "Ada Api Berbahaya!!!");
  } else {
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, HIGH);
    noTone(BuzzerPin);
    myservo.write(0);
    lcd1.clear();
    lcd1.print(0, 0, "Aman Dari Api");
  }

  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V0, humidity);
}

