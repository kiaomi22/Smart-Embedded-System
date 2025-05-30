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

#define DHTPIN 2
#define DHTTYPE DHT22

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const int ledMerah = 5;
const int ledHijau = 19;
const int servoPin = 18;
const int BuzzerPin = 4;

Servo myservo;       // Deklarasi objek servo
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD dan ukuran karakter
WidgetLCD lcd1(V2);  // Widget LCD Blynk

BLYNK_WRITE(V3) {  // Mendapatkan nilai dari button switch di Blynk
  int switchValue = param.asInt();
  if (switchValue == 1) {
    digitalWrite(ledMerah, HIGH);
    digitalWrite(ledHijau, LOW);
    tone(BuzzerPin, 250);
    myservo.write(180); 
    lcd1.clear();
    lcd1.print(0,0, "Ada Api Berbahaya!!");
    Blynk.logEvent("kebakaran","Ada Api Berbahaya!!!");
  } else {
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, HIGH);
    noTone(BuzzerPin);
    myservo.write(0); 
    lcd1.clear();
    lcd1.print(0,0, "Aman Dari Api");
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight(); // Inisialisasi LCD
  lcd.print("Sensor DHT22");
  lcd.setCursor(0, 1);
  lcd.print("Membaca nilai...");

  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);

  dht.begin(); // Inisialisasi sensor DHT22
  myservo.attach(servoPin); // Menghubungkan servo ke pin 18
  myservo.write(0); // Menggerakkan servo ke posisi awal

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  Blynk.run();
  float temperature = dht.readTemperature(); // Baca suhu dalam derajat Celsius
  float humidity = dht.readHumidity(); // Baca kelembaban dalam persen

  lcd.clear(); // Bersihkan tampilan LCD
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Kelembaban: ");
  lcd.print(humidity);
  lcd.print(" %");

  if (temperature > 40) {
    digitalWrite(ledMerah, HIGH);
    digitalWrite(ledHijau, LOW);
    tone(BuzzerPin, 250);
    myservo.write(180); 
    lcd1.clear();
    lcd1.print(0,0, "Ada Api Berbahaya!!");
    Blynk.logEvent("kebakaran","Ada Api Berbahaya!!!");
  } else {
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, HIGH);
    noTone(BuzzerPin);
    myservo.write(0); 
    lcd1.clear();
    lcd1.print(0,0, "Aman Dari Api");
  }

  Blynk.virtualWrite(V1, temperature); 
  Blynk.virtualWrite(V0, humidity);

  delay(2000);
}
