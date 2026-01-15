#define BLYNK_TEMPLATE_ID "**********************"
#define BLYNK_TEMPLATE_NAME "IoT Enabled Patient Health Status System"
#define BLYNK_AUTH_TOKEN "********************"
#include <PulseSensorPlayground.h>
#include <NewPing.h>
#include <HX711.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>   
#include <SoftwareSerial.h>

// Pin definitions for ESP8266
#define DT_PIN 4   // D2 (GPIO 4)
#define SCK_PIN 5  // D1 (GPIO 5)
#define TRIG_PIN D8  // Trigger pin
#define ECHO_PIN D7  // Echo pin
#define MAX_SENSOR_DISTANCE_CM 400 // Max sensor range in cm (≈13 feet)
#define BLYNK_PRINT Serial
const float SENSOR_HEIGHT_FT = 8.0; // Height of sensor above ground in feet (adjust as needed)
const float CM_TO_FEET = 0.0328084; // 1 cm = 0.0328084 feet
const int PulseWire = A0;  
int Threshold = 550;

const char* ssid ="***********";
const char* password ="*******";
// Constants
HX711 scale; // Create HX711 object without parameters
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_SENSOR_DISTANCE_CM);
PulseSensorPlayground pulseSensor;
void setup() {
  Serial.begin(9600); // Start serial communication
  Serial.println("HX711 Weight Scale");

  // Initialize HX711 with DT and SCK pins
  scale.begin(DT_PIN, SCK_PIN);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  // Optional: Reset scale to zero
  scale.set_scale();
  scale.tare(); // Zero the scale (remove any offset)
  Serial.println("Setup complete. Place a weight to read...");
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("PulseSensor initialized successfully!");
  } else {
    Serial.println("PulseSensor failed to initialize.");
  }
}

void loop() {
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
  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    Serial.println("♥ A HeartBeat Happened!");
    Serial.print("BPM: ");
    Blynk.virtualWrite(V0,myBPM);
    Serial.println(myBPM);
  }
  Blynk.run();
  // Read raw data from HX711
  long reading = scale.read();
  Serial.print("Raw reading: ");
  Serial.println(reading);

  // Optional: Convert to weight (requires calibration)
  float weight = scale.get_units(10); // Average of 2 readings
  Serial.print("Weight: ");
  float val = map(weight, -100, 645975, 0, 5000);
  float cal = val / 1000;
  Serial.println(cal, 2); // 2 decimal places
  Blynk.virtualWrite(V2, cal);

  delay(1000); // Delay for readable output
}
