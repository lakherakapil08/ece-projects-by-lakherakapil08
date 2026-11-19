
#include <DHT.h>

// DHT22 Configuration
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// LED GPIO Pins
#define GREEN_LED 18
#define YELLOW_LED 19
#define RED_LED 21
#define BLUE_LED 22

// WiFi configuration (Wokwi)
#include <WiFi.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

void setup() {
  Serial.begin(115200);

  // Initialize LEDs
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Initialize DHT22
  dht.begin();

  Serial.println("ESP32 Temperature Monitoring System");

  // Connect to Wokwi WiFi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BLUE_LED, !digitalRead(BLUE_LED));
    Serial.print(".");
    delay(500);
  }

  digitalWrite(BLUE_LED, HIGH);

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT22 reading failed!");
    delay(2000);
    return;
  }

  // Turn off temperature LEDs
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.println("-----------------------");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Temperature classification
  if (temperature < 25) {

    digitalWrite(GREEN_LED, HIGH);
    Serial.println("Status: MINIMUM");

  }
  else if (temperature <= 35) {

    digitalWrite(YELLOW_LED, HIGH);
    Serial.println("Status: MODERATE");

  }
  else {

    digitalWrite(RED_LED, HIGH);
    Serial.println("Status: EXTREME");

  }

  // WiFi indicator
  digitalWrite(BLUE_LED,
    WiFi.status() == WL_CONNECTED ? HIGH : LOW);

  delay(200);
}
