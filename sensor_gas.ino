/*
  Blynk example for MQ-135 air quality sensor
  You should get Auth Token in the Blynk App.
  You need to write the right wifiCredentials.
*/

#define BLYNK_TEMPLATE_ID "TMPL6vS9Qc0M1"
#define BLYNK_TEMPLATE_NAME "UDARA"
#define BLYNK_AUTH_TOKEN "3GDwv9Sf23Oy-o-YVADmQYmrB538JbLc"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int airQualityPin = A0; // Pin analog untuk sensor MQ-135
int buzzer_pin = 2; // Pin untuk buzzer
int led_pin = 5;    // Pin untuk LED

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "3GDwv9Sf23Oy-o-YVADmQYmrB538JbLc";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Lab Robotika"; //nama hotspot yang digunakan
char pass[] = "lab_robotika"; //password hotspot yang digunakan

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(airQualityPin, INPUT);   // Set pin sensor kualitas udara sebagai input
  pinMode(buzzer_pin, OUTPUT);     // Set buzzer pin as output
  pinMode(led_pin, OUTPUT);        // Set LED pin as output

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, sendSensor); // Kirim data setiap detik
}

void loop()
{
  Blynk.run();
  timer.run();
}

void sendSensor() {
    int airQualityValue = analogRead(airQualityPin);  // Membaca nilai dari sensor kualitas udara MQ-135
    
    // Cetak nilai kualitas udara ke Serial Monitor
    Serial.print("Air Quality Value: ");
    Serial.println(airQualityValue);
    
    // Kirim data kualitas udara ke Blynk
    Blynk.virtualWrite(V14, airQualityValue);  // Kirim nilai kualitas udara ke virtual pin V14 di Blynk
    
    // Tetapkan ambang batas untuk kualitas udara buruk
    int airQualityThreshold = 300; // Contoh ambang batas kualitas udara (bisa disesuaikan)

    // Periksa apakah nilai kualitas udara melebihi ambang batas
    if (airQualityValue > airQualityThreshold) {
        digitalWrite(buzzer_pin, HIGH); // Nyalakan buzzer
        digitalWrite(led_pin, HIGH);    // Nyalakan LED
        Blynk.logEvent("notif_sensor"); // Kirim notifikasi Blynk
    } else {
        digitalWrite(buzzer_pin, LOW);  // Matikan buzzer
        digitalWrite(led_pin, LOW);     // Matikan LED
    }
}
