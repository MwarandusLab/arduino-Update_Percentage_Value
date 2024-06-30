#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Inventor";
const char* password = "30010231";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

}

void loop() {
  // Call the functions for each fan
  sendDataToServerFan1();
  delay(2000);
  
  sendDataToServerFan2();
  delay(2000);
  
  // Add more calls for other fans as needed
}

void sendDataToServer(const char* fanName, const char* percentage) {
  HTTPClient http;

  // Your server URL
  String serverUrl = "https://beemultiscent.com/iot/diffuser";

  // Create JSON object
  DynamicJsonDocument jsonDoc(200);
  jsonDoc["percentage"] = percentage;
  jsonDoc["fan_name"] = fanName;

  // Serialize JSON to string
  String dataToSend;
  serializeJson(jsonDoc, dataToSend);

  // Print the complete URL with data for debugging
  Serial.print("Sending data to server: ");
  Serial.println(dataToSend);

  // Make POST request
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(dataToSend);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void sendDataToServerFan1() {
  sendDataToServer("fan_1", "10.5");
}

void sendDataToServerFan2() {
  sendDataToServer("fan_2", "20.5");
}

// Define functions for other fans similarly
