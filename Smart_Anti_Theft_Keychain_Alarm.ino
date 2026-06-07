#define BLYNK_TEMPLATE_ID "TMPL35gYg7Ir9"
#define BLYNK_TEMPLATE_NAME "smrat keychain"
#define BLYNK_AUTH_TOKEN "0lpPFgT_YYJ-aa7xwEwN7p9ptFf5RUMq"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Wifi's name";
char pass[] = "Wifi's Password";

#define SENSOR_PIN D5
#define BUZZER_PIN D6
#define LED_PIN D7

int lastState = 0;

void setup() {
  Serial.begin(115200);

  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.println("System Started");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int vibration = digitalRead(SENSOR_PIN);

  Serial.println(vibration);

  // Trigger only once when vibration starts
  if (vibration == HIGH && lastState == 0) {
    Serial.println("Theft Alert!");

    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);

    Blynk.virtualWrite(V0, 1);

    // 🔔 SEND NOTIFICATION
    Blynk.logEvent("theft_alert", "🚨 Keychain moved!");

    lastState = 1;
  }

  // Reset when no vibration
  if (vibration == LOW && lastState == 1) {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);

    Blynk.virtualWrite(V0, 0);

    lastState = 0;
  }

  delay(100);
}