#define BLYNK_TEMPLATE_ID "TMPL3X7o-fqIf"
#define BLYNK_TEMPLATE_NAME "IoT Enabled Patient Health Status System"
#define BLYNK_AUTH_TOKEN "Zn6HbKM5yE1jV9gySmtBwABWVJToYvwH"

#include <PulseSensorPlayground.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const char* ssid ="OPPOReno8T5G";
const char* password ="OPPO8T5G";

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
