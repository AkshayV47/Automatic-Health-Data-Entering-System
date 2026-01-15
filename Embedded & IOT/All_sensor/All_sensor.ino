#define BLYNK_TEMPLATE_ID "***********"
#define BLYNK_TEMPLATE_NAME "IoT Enabled Patient Health Status System"
#define BLYNK_AUTH_TOKEN "Zn6HbKM5yE1jV9gySmtBwAB"

#define DT_PIN D2
#define SCK_PIN D1
#define TRIG_PIN D8
#define ECHO_PIN D7
#define MAX_SENSOR_DISTANCE_CM 400 // Max sensor range in cm (≈13 feet)
#define BLYNK_PRINT Serial

#include <HX711.h>
#include <NewPing.h>
#include <ESP8266TimerInterrupt.h>
#include <PulseSensorPlayground.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 
#include <SoftwareSerial.h>

const char* ssid ="***********";
const char* password ="*******";

const int PulseWire = A0;  
int Threshold = 550;

const float SENSOR_HEIGHT_FT = 8.0; // Height of sensor above ground in feet (adjust as needed)
const float CM_TO_FEET = 0.0328084; // 1 cm = 0.0328084 feet

PulseSensorPlayground pulseSensor;
BlynkTimer timer;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_SENSOR_DISTANCE_CM);
HX711 scale;

void sendSensorData() {
  // int myBPM = pulseSensor.getBeatsPerMinute();
  // if (pulseSensor.sawStartOfBeat()) {
  //   Serial.print("BPM: ");
  //   Serial.println(myBPM);
  //   Blynk.virtualWrite(V0, myBPM);
  // }
  float weight = scale.get_units(10); // Average of 2 readings
  Serial.print("Weight: ");
  float val = map(weight, 0, 645975, 0, 5000);
  float cal = val / 1000;
  Serial.println(cal, 2); // 2 decimal places
  Blynk.virtualWrite(V2, cal);
  // float distanceCm = sonar.ping_cm();
  // float distanceFt = distanceCm * CM_TO_FEET;
  // float personHeightFt = SENSOR_HEIGHT_FT - distanceFt;
  // if (personHeightFt < 0) personHeightFt = 0;
  // Serial.print("Person's height: ");
  // Serial.println(personHeightFt);
  // Blynk.virtualWrite(V1, personHeightFt);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  Serial.println("HX711 Weight Scale");
  scale.begin(DT_PIN, SCK_PIN);
  scale.set_scale();
  scale.tare(); // Zero the scale (remove any offset)
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("successfully!");
  }
  timer.setInterval(1000L, sendSensorData);  // Schedule sensor data send every 1000 ms (1 sec)
}

void loop() {
  Blynk.run();
  timer.run();  // Run BlynkTimer events
}

