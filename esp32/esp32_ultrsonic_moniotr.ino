#include <WiFi.h>
#include <HTTPClient.h>

// ======================
// WiFi Credentials
// ======================

const char* ssid = "wifi-ssid";
const char* password = "wifi-password";

// ======================
// Backend Server URL
// ======================

const char* serverName =
"http://<backend-server-ip>:3000/distance";

// ======================
// HC-SR04 Pinshttps://192.168.1.7/
// ======================

const int trigPin = 5;
const int echoPin = 18;

// ======================
// Sound Speed
// ======================

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

// ======================
// Setup
// ======================

void setup() {

  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Connect WiFi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("ESP32 IP Address: ");

  Serial.println(WiFi.localIP());
}

// ======================
// Main Loop
// ======================

void loop() {

  // Clear trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10us pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  distanceCm = duration * SOUND_SPEED / 2;

  // Convert to inch
  distanceInch =
    distanceCm * CM_TO_INCH;

  // Print Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);

  // ======================
  // Send Data to Backend
  // ======================

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(serverName);

    http.addHeader(
      "Content-Type",
      "application/json"
    );

    // JSON Data
    String jsonData =
      "{\"distance_cm\":"
      + String(distanceCm)
      + ",\"distance_inch\":"
      + String(distanceInch)
      + "}";

    // Send POST Request
    int httpResponseCode =
      http.POST(jsonData);

    Serial.print("HTTP Response: ");

    Serial.println(httpResponseCode);

    http.end();
  }

  else {

    Serial.println(
      "WiFi Disconnected"
    );
  }

  delay(2000);
}