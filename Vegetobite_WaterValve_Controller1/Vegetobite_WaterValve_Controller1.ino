#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6-fvE8_dg"
#define BLYNK_TEMPLATE_NAME "Vegetobite Water Valve Controller"
#define BLYNK_AUTH_TOKEN "qtfarBngOlwzwm8AVLdhyRf1kPYkdubo"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vegetobite2";
char pass[] = "wargaFAMA17304";

//char ssid[] = "bahani-2.4Ghz@unifi";
//char pass[] = "burungbiru";

// Solenoid valve pins
const int valve1Pin = 32; // Valve 1 - Tank 1
const int valve2Pin = 33; // Valve 2 - Tank 2
const int valve3Pin = 25; // Valve 3 - Tank 3
const int valve4Pin = 26; // Valve 4 - Tank 4

// --- BLYNK HANDLERS ---

// Valve 1 (GPIO 32) - V0 control, V1 status
BLYNK_WRITE(V0) {
  bool state = param.asInt();
  digitalWrite(valve1Pin, state ? LOW : HIGH);
  Serial.print("Valve 1 (Tank 1): ");
  Serial.println(state ? "ON" : "OFF");
  Blynk.virtualWrite(V1, state ? 255 : 0);
}

// Valve 2 (GPIO 33) - V2 control, V3 status
BLYNK_WRITE(V2) {
  bool state = param.asInt();
  digitalWrite(valve2Pin, state ? LOW : HIGH);
  Serial.print("Valve 2 (Tank 2): ");
  Serial.println(state ? "ON" : "OFF");
  Blynk.virtualWrite(V3, state ? 255 : 0);
}

// Valve 3 (GPIO 25) - V4 control, V5 status
BLYNK_WRITE(V4) {
  bool state = param.asInt();
  digitalWrite(valve3Pin, state ? LOW : HIGH);
  Serial.print("Valve 3 (Tank 3): ");
  Serial.println(state ? "ON" : "OFF");
  Blynk.virtualWrite(V5, state ? 255 : 0);
}

// Valve 4 (GPIO 26) - V6 control, V7 status
BLYNK_WRITE(V6) {
  bool state = param.asInt();
  digitalWrite(valve4Pin, state ? LOW : HIGH);
  Serial.print("Valve 4 (Tank 4): ");
  Serial.println(state ? "ON" : "OFF");
  Blynk.virtualWrite(V7, state ? 255 : 0);
}

void setup() {
  Serial.begin(115200);

  // Set pin modes
  pinMode(valve1Pin, OUTPUT);
  pinMode(valve2Pin, OUTPUT);
  pinMode(valve3Pin, OUTPUT);
  pinMode(valve4Pin, OUTPUT);

  // Set all relays OFF initially (HIGH for active LOW relay modules)
  digitalWrite(valve1Pin, HIGH);
  digitalWrite(valve2Pin, HIGH);
  digitalWrite(valve3Pin, HIGH);
  digitalWrite(valve4Pin, HIGH);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}