#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define DHTTTHRESHOLD 11

#define SSID "Asgard"
#define SENSOR_ID "CENTAX-03"
#define SERVER_ADDRESS "http://192.168.1.100/api/v1/sensors/"

/***
  For working with a faster than ATmega328p 16 MHz chip, like an ESP8266,
  you need to increase the threshold for cycle counts.
  You can do this by passing a 3rd parameter for this threshold.
  11 - is good for the ESP8266 processor on ESP-01.
***/
DHT dht(DHTPIN, DHTTYPE, DHTTTHRESHOLD);


void setup() {
  Serial.begin(115200);

  Serial.print("[WIFI] Connecting to ");
  Serial.println(SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("[WIFI] Connected");

  Serial.print("[WIFI] IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("[DHT] Begin connection");
  dht.begin();
  Serial.println("[DHT] Connected");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temp) || isnan(humidity)) {
      Serial.println("[DHT] Failed to read the data");
    } else {
      WiFiClient client;
      HTTPClient http;

      Serial.println("[HTTP] Begin request");
      http.setReuse(true);
      http.begin(client, SERVER_ADDRESS);
      http.addHeader("Content-Type", "application/json");

      String payload = String("{\"sensor_id\":\"") + SENSOR_ID +
                       String("\",\"temp\":") + temp +
                       String(",\"humidity\":") + humidity + String("}");

      int httpCode = http.POST(payload);

      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          const String& payload = http.getString();
          Serial.println("[HTTP] Response:\n<<");
          Serial.println(payload);
          Serial.println(">>");
        } else {
          Serial.print("[HTTP] Error: ");
          Serial.println(httpCode);
        }
      }

      Serial.print("[HTTP] Response code: ");
      Serial.println(httpCode);

      Serial.print("[HTTP] Text: ");
      Serial.println(http.getString());

      Serial.println("[HTTP] End request");
      http.end();
    }

  } else {
    Serial.print(".");
  }

  delay(5 * 60 * 1000);
}
