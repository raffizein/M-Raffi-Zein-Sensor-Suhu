#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 32      
#define DHTTYPE DHT22 

const char* ssid = "Infinix Smart 4";      
const char* password = "12345567"; 
const char* serverUrl = "http://192.168.1.5:5000/data";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  dht.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    String jsonPayload = "{\"temperature\":" + String(temperature) + ", \"humidity\":" + String(humidity) + "}";
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  delay(60000);
}
