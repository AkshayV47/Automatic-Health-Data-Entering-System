#define BLYNK_TEMPLATE_ID "TMPL3X7o-fqIf"
#define BLYNK_TEMPLATE_NAME "IoT Enabled Patient Health Status System"
#define BLYNK_AUTH_TOKEN "Zn6HbKM5yE1jV9gySmtBwABWVJToYvwH"

#include <NewPing.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>   
#include <SoftwareSerial.h>
// Pin definitions for HC-SR04
#define TRIG_PIN D8  // Trigger pin
#define ECHO_PIN D7  // Echo pin
#define MAX_SENSOR_DISTANCE_CM 400 // Max sensor range in cm (≈13 feet)
#define BLYNK_PRINT Serial
// Initialize NewPing object
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_SENSOR_DISTANCE_CM);
const char* ssid ="OPPOReno8T5G";
const char* password ="OPPO8T5G";
// Constants
const float SENSOR_HEIGHT_FT = 8.0; // Height of sensor above ground in feet (adjust as needed)
const float CM_TO_FEET = 0.0328084; // 1 cm = 0.0328084 feet

void setup() {
  // Start Serial Monitor
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  // Measure distance in cm and convert to feet
  float distanceCm = sonar.ping_cm();
  float distanceFt = distanceCm * CM_TO_FEET;

  // Handle invalid readings (0 means out of range or error)
  if (distanceCm == 0) {
    Serial.println("No valid measurement (out of range or error)");
  } else {
    // Calculate person's height
    float personHeightFt = SENSOR_HEIGHT_FT - distanceFt;

    // Ensure height is non-negative
    if (personHeightFt < 0) personHeightFt = 0;

    // Output to Serial Monitor
    Serial.print("Distance to head: ");
    Serial.print(distanceFt);
    Serial.print(" ft, Person's height: ");
    Serial.print(personHeightFt);
    Blynk.virtualWrite(V1,personHeightFt);
    Serial.println(" ft");
  }
  Blynk.run();
  // Delay before next reading
  delay(1000);
}