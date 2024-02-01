// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>
// TaskHandle_t task1;

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Hoai Nam";
const char* password = "123456789";
const int serverPort = 8888;

WiFiServer server(serverPort);

const int endStop[] = {22,32,33};

#include <Servo.h>
static const int servoPin = 2;
Servo servo1;

const float pi = 3.141592653;    // PI


void setup() {
  motoroff();

  Serial.begin(115200);

  for (int i = 0; i < 3; i++) {
    pinMode(endStop[i],INPUT_PULLUP);
  }

  servo1.attach(servoPin);
  // BTS_ON();
  TCP_ON();

}

bool BTS=false;
bool TCP=false;

void loop() {
  if (BTS==true){
    if (SerialBT.available()) {
      String received = SerialBT.readStringUntil('\n');
      Serial.println(received);
      command(received);
    }
  }

  if (TCP==true){
    WiFiClient client = server.available();
    if (client) {
//  client.print("Hello from ESP32!");
      if (client.available()) {
        String received = client.readStringUntil('\n');
        Serial.println(received);
        command(received);

      }
  }
  }
  if (Serial.available()) {
    String received = Serial.readStringUntil('\n');
    Serial.println(received);
    command(received);
  }
  
  
}

void BTS_ON(){
  SerialBT.begin("RobotDelta");
  BTS=true;
}
void BTS_OFF(){
  BTS=false;
  SerialBT.end();
}

void TCP_ON(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started");
  TCP=true;
}

void TCP_OFF(){
  WiFi.disconnect();
  TCP=false;
}
