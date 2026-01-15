#define BLYNK_TEMPLATE_ID "***************"
#define BLYNK_TEMPLATE_NAME "IoT Enabled Patient Health Status System"
#define BLYNK_AUTH_TOKEN "**************"

#include <PulseSensorPlayground.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char* ssid ="************";
const char* password ="******";

const int PulseWire = A0;  
int Threshold = 550;

PulseSensorPlayground pulseSensor;

void setup() {
  Serial.begin(9600);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  if (pulseSensor.begin()) {
    Serial.println("PulseSensor initialized successfully!");
  } else {
    Serial.println("PulseSensor failed to initialize.");
  }
}

void loop() {

  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    Serial.println("♥ A HeartBeat Happened!");
    Serial.print("BPM: ");
    Blynk.virtualWrite(V0,myBPM);
    Serial.println(myBPM);
  }
  Blynk.run();
  delay(20);
}
