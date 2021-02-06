#include <ESP32Servo.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
  char auth[] = "xxxxxxxxx";
  char ssid[] = "xxxxxxxxx";
  char pass[] = "xxxxxxxxx";
  Servo myservo;

void setup() {
  //Serial.begin(115200);
  //เริ่มการเชื่อมต่อ Blynk Server
  Blynk.begin(auth, ssid, pass);
  myservo.attach(13);
}
  BLYNK_WRITE(V3) {
  myservo.write(param.asInt());
}

void loop() {
  Blynk.run();
}
