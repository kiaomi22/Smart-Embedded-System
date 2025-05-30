#include <Servo.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 5
const int pinServo = 3;
const int pinSoil = A0;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define buzzerPin 4

void setup() {
  lcd.backlight();
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  myservo.attach(pinServo);
  myservo.write(0);
}

void loop() {
  float pembacaan = analogRead(pinSoil);
  float kelembapanTanah = (100 - ((pembacaan/1023.00)*100));
  float kelembapanUdara = dht.readHumidity();
  Serial.print("Kelembapan tanah: ");
  Serial.println(kelembapanTanah);
  Serial.print("Kelembapan udara: ");
  Serial.println(kelembapanUdara);

  if (kelembapanTanah < 10){
    myservo.write(90);
    Serial.println("Kran terbuka");
  } else {
    myservo.write(0);
    Serial.println("Kran tertutup");
  }

  delay(2000);
  lcd.setCursor(0,0);

  if (kelembapanUdara > 70){
    lcd.print("Kel. Udara:");
    lcd.print(kelembapanUdara);
    lcd.print((char)223);
    lcd.setCursor(0, 1);
    lcd.print("Bukalah Jendela!");
    tone(buzzerPin, 800);
  } else {
    lcd.print("Kel. Udara:");
    lcd.print(kelembapanUdara);
    lcd.print((char)223);
    lcd.setCursor(0, 1);
    lcd.print("Tutuplah Jendela!");
    noTone(buzzerPin);
  }
}