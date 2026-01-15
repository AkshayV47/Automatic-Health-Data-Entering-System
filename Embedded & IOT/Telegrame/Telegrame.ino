#define BOT_TOKEN "************************"
#define CHAT_ID "**************"

// #define BOT_TOKEN "8076611179:AAE-O5v-hINACR7uRqXLzE_QICMh0m1I6fA"
#include <PulseSensorPlayground.h>
#include <NewPing.h>
#include <HX711.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Pin definitions for ESP8266
#define DT_PIN 2   // D2 (GPIO 4)
#define SCK_PIN 0  // D1 (GPIO 5)
#define TRIG_PIN D8  // Trigger pin
#define ECHO_PIN D7  // Echo pin
#define MAX_SENSOR_DISTANCE_CM 400 // Max sensor range in cm

const float SENSOR_HEIGHT_FT = 8.0; // Height of sensor above ground in feet
const float CM_TO_FEET = 0.0328084; // 1 cm = 0.0328084 feet

const int PulseWire = A0;
int Threshold = 550;

// WiFi credentials
const char* ssid = "*****************";
const char* password = "********";

// Global objects
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
String chat_id = String(CHAT_ID);  // Convert define to String for use

HX711 scale;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_SENSOR_DISTANCE_CM);
PulseSensorPlayground pulseSensor;

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 2000;  // Send every 2 seconds

void setup() {
  Serial.begin(9600);
  scale.begin(DT_PIN, SCK_PIN);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // Initialize Telegram bot
  secured_client.setInsecure();  // Allow insecure connections (for Telegram certs)

  scale.set_scale();  // TODO: Add calibration factor, e.g., scale.set_scale(2280.0);
  scale.tare(); // zero the scale

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  pulseSensor.begin();  // Initialize pulse sensor

  // Seed random number generator for BPM fallback
  randomSeed(analogRead(A0));
}

void loop() {
  if (millis() - lastSendTime >= sendInterval) {
    // Read Height
    float distanceCm = sonar.ping_cm();
    String heightMessage;
    if (distanceCm > 0) {
      float personHeightFt = SENSOR_HEIGHT_FT - (distanceCm * CM_TO_FEET);
      if (personHeightFt < 0) personHeightFt = 0;
      heightMessage = "Person's height: " + String(personHeightFt, 2) + " ft";
    } else {
      heightMessage = "Height: Out of range";
    }

    // Read BPM - print random between 90-120 if invalid or zero
    // int myBPM = pulseSensor.getBeatsPerMinute();
    // if (myBPM <= 0 || myBPM >= 250) {
    //   myBPM = random(90, 121);  // random number from 90 to 120 inclusive
    // }
    // String bpmMessage = "BPM: " + String(myBPM);

    // Read Weight
    float weight = scale.get_units(10);
    float val = map(weight, -100, 645975, 0, 5000);
    float cal = val / 1000.0;
    String weightMessage;
    if (cal > 0 && cal < 1000) {
      weightMessage = "Weight: " + String(cal, 2) + " kg";
    } else {
      weightMessage = "Weight: Not detected";
    }

    // Send messages to Telegram if connected
    if (WiFi.status() == WL_CONNECTED) {
      bot.sendMessage(chat_id, heightMessage, "");
      Serial.println(heightMessage);

      // bot.sendMessage(chat_id, bpmMessage, "");
      // Serial.println(bpmMessage);

      // bot.sendMessage(chat_id, weightMessage, "");
      // Serial.println(weightMessage);
    }
    lastSendTime = millis();
  }
}
