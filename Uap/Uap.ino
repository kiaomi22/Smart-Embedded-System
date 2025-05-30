#include <DHT.h>
#include <Servo.h>

// Pin Definitions
#define DHTPIN 2
#define DHTTYPE DHT22
#define SOIL_PIN A0
#define RAIN_PIN A1
#define FLAME_PIN 3
#define LDR_PIN A2
#define RELAY_PIN 4
#define TRIG_PIN 2
#define ECHO_PIN 6
#define SERVO_PIN 9
#define MQ2_PIN A3  // analog pin A3
#define BUZZER 7
#define IR_SENSOR_PIN 5

// Inisialisasi Objek
DHT dht(DHTPIN, DHTTYPE);
Servo servo;

void setup() {
  Serial.begin(9600);
  dht.begin();
  servo.attach(SERVO_PIN);
  
  pinMode(FLAME_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
}

void loop() {

  // Ultrasonic (Deteksi kehadiran)
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 15) {
    servo.write(45); // buka pintu
  } else {
    servo.write(0); // tutup pintu
  }
  delay(2000); // jeda baca sensor
}

// // === Servo Door Access (Smart Home) ===
//   if (digitalRead(RFID_PIN) == LOW && !doorOpen) {
//     Serial.println("Akses diterima, membuka pintu...");
//     servo.write(90); // buka pintu
//     doorOpen = true;
//     delay(3000); // tunggu 3 detik
//     servo.write(0); // tutup kembali
//     doorOpen = false;
//   }

  //  int ir = digitalRead(IR_SENSOR_PIN);
  // if (ir == LOW) {
  //   Serial.println("Objek terdeteksi oleh sensor IR");
 
  // } else if(ir == HIGH){
  //   Serial.println("Objek Tidak terdeteksi");
  // }
     

  //Gas MQ
  // int gasValue = analogRead(MQ2_PIN);
  // Serial.print("Nilai Gas MQ-2: ");
  // Serial.println(gasValue);

  // if (gasValue > 400) { // ambang batas bisa disesuaikan
  //   Serial.println("🚨 Gas Terdeteksi! Aktifkan alarm!");
  //   tone(BUZZER, 1000);
  //   delay(50);
  //   noTone(BUZZER);
  //   delay(50);
  // }
// }

//   // DHT Sensor
//   float temp = dht.readTemperature();
//   float hum = dht.readHumidity();
//   Serial.print("Suhu: ");
//   Serial.print(temp);
//   Serial.print(" °C, Kelembaban: ");
//   Serial.print(hum);
//   Serial.println(" %");

//   // Soil Moisture
//   int soilValue = analogRead(SOIL_PIN);
//   Serial.print("Soil Moisture: ");
//   Serial.println(soilValue);

//   // Rain Drop
//   int rainValue = analogRead(RAIN_PIN);
//   Serial.print("Rain Value: ");
//   Serial.println(rainValue);

//   // Flame Sensor
//   bool flameDetected = digitalRead(FLAME_PIN) == LOW;
//   Serial.print("Api Terdeteksi: ");
//   Serial.println(flameDetected ? "YA" : "TIDAK");
// bool fireDetected = digitalRead(FLAMEPIN) == LOW;
// if (fireDetected || temp > 50.0) {
//   digitalWrite(BUZZERPIN, HIGH);        // Aktifkan buzzer alarm
//   digitalWrite(RELAYPIN, HIGH);         // Aktifkan pompa air untuk pemadaman
// } else {
//   digitalWrite(BUZZERPIN, LOW);
// }

//   // LDR (Smart Light)
//   int ldrValue = analogRead(LDR_PIN);
//   Serial.print("Cahaya: ");
//   Serial.println(ldrValue);
//   if (ldrValue < 500) {
//     digitalWrite(RELAY_PIN, HIGH);  // Nyalakan lampu
//   } else {
//     digitalWrite(RELAY_PIN, LOW);   // Matikan lampu
//   }

//   // Ultrasonic (Deteksi kehadiran)
//   long duration, distance;
//   digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
//   digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);
//   duration = pulseIn(ECHO_PIN, HIGH);
//   distance = duration * 0.034 / 2;
//   Serial.print("Jarak: ");
//   Serial.print(distance);
//   Serial.println(" cm");
//   if (distance < 15) {
//     servo.write(90); // buka pintu
//   } else {
//     servo.write(0); // tutup pintu
//   }

//   // Pengairan Otomatis
//   if (soilValue > 600 && rainValue < 500) {
//     digitalWrite(RELAY_PIN, HIGH); // aktifkan pompa
//     Serial.println("Pompa ON (Tanah Kering dan Tidak Hujan)");
//   } else {
//     digitalWrite(RELAY_PIN, LOW);
//     Serial.println("Pompa OFF");
//   }

//   delay(2000); // jeda baca sensor
// }