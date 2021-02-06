/*
 * ตัวอย่างการใช้ BLYNK APP ควบคุมการปิดเปิดหลอดไฟ
 */
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "xxxxxxxxxx";
char ssid[] = "xxxxxxxxxx";
char pass[] = "xxxxxxxxxx";
void setup() {
  Serial.begin(115200);
  //เริ่มการเชื่อมต่อ Blynk Server
  Blynk.begin(auth, ssid, pass);
}
void loop() {
  Blynk.run();
}
