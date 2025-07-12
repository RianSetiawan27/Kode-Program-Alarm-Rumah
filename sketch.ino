#define BLYNK_TEMPLATE_ID "TMPL6qcn1_Lsy"
#define BLYNK_TEMPLATE_NAME "Alarm Rumah"
#define BLYNK_AUTH_TOKEN "Crp9fZ3NQO5BypA_26l66auCUYaNnVEo"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define PIR_PIN 13        // pin sensor PIR
#define BUZZER_PIN 12     // pin buzzer aktif
#define LED_PIN 14        // pin LED merah

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Sistem Alarm Siap. Tunggu gerakan...");
}

// Fungsi sirene: frekuensi naik-turun seperti suara ambulans
void siren(int duration_ms) {
  unsigned long start = millis();
  while (millis() - start < duration_ms) {
    for (int freq = 1000; freq <= 1500; freq += 10) {
      tone(BUZZER_PIN, freq);
      delay(5);
    }
    for (int freq = 1500; freq >= 1000; freq -= 10) {
      tone(BUZZER_PIN, freq);
      delay(5);
    }
  }
  noTone(BUZZER_PIN);
}

void loop() {
  Blynk.run();

  int motion = digitalRead(PIR_PIN);
  if (motion == HIGH) {
    Serial.println("Gerakan Terdeteksi!");
    Blynk.virtualWrite(V0, "GERAKAN TERDETEK");
    Blynk.logEvent("motion_detected", "Gerakan terdeteksi di rumah!");

    digitalWrite(LED_PIN, HIGH); // LED merah menyala
    siren(5000);                 // mainkan sirene
    digitalWrite(LED_PIN, LOW);  // LED mati kembali

    Blynk.virtualWrite(V0, "TIDAK ADA GERAK");
  }
}
