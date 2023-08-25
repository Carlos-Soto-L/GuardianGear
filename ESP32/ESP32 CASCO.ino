#include <WiFi.h>
#include <WebSocketsClient.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include "DHT.h"
#include <ArduinoJson.h>
// MATRIZ
#include <Adafruit_NeoPixel.h>
#define LED_PIN 13

#define RXD2 16 // Pin D16 en la ESP32
#define TXD2 4  // Pin D4 en la ESP32

// SENSOR DHT11
#define DHTPIN 2     // Pin al que está conectado el DHT11
#define DHTTYPE DHT11   // DHT 11

// Definición para el sensor KY-010
#define SENSOR_KY010_PIN 19
bool lastState = LOW;
bool currentState = LOW;


#define SENSOR_KY003_PIN 15  // Pin para el sensor KY-003
bool lastStateKY003 = LOW;

DHT dht(DHTPIN, DHTTYPE);


// Cambia estos valores por los de tu red WiFi
// const char* ssid = "cortesía Soto Ledezma";
// const char* password = "9q6qT9CdU4";

const char* ssid = "NANO";
const char* password = "queso123";

TinyGPS gps;
SoftwareSerial gps_com(RXD2, TXD2); // RX, TX
WebSocketsClient webSocket;

// Definiciones para NeoPixel y sensor de luz.
#define PIN 14
#define NUMPIXELS 64
#define LIGHT_SENSOR_PIN 34
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define BUZZER_KY006_PIN 17 


void setup() {
  Serial.begin(9600);
  gps_com.begin(9600);
  // SENSOR DHT11
  dht.begin();

  // Configuración para el sensor KY-010
  pinMode(SENSOR_KY010_PIN, INPUT);


  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  webSocket.begin("3.134.204.135", 3000);
  webSocket.onEvent(webSocketEvent);
  Serial.println("Conectado a WiFi!");

  // Inicializaciones para NeoPixel y sensor de luz.
  strip.begin();
  strip.show();
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  pinMode(SENSOR_KY003_PIN, INPUT);

  pinMode(BUZZER_KY006_PIN, OUTPUT);
  digitalWrite(BUZZER_KY006_PIN, LOW); // Asegurarse de que el buzzer esté apagado al inicio

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

}

void loop() {
  webSocket.loop();
  bool newData = false;

  for (unsigned long start = millis(); millis() - start < 100;) {
    while (gps_com.available()) {
      char c = gps_com.read();
      if (gps.encode(c))
        newData = true;
    }


  }

  // Leer humedad y temperatura
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Comprobar si alguna lectura falló y salir temprano (para intentar de nuevo)
  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo en la lectura del sensor!");
    return;
  }else{
   String messageDHT11 = "{\"tipo\":\"sensorDHT11\",\"temp\":" + String(t) + ",\"hum\":" + String(h) + ", \"ID\":\"XAC1976\"}";
    webSocket.sendTXT(messageDHT11); // Enviar el mensaje JSON al WebSocket
  }

  // Lectura del sensor KY-010
  currentState = digitalRead(SENSOR_KY010_PIN);
  if (lastState == LOW && currentState == HIGH) {
          String message = "{\"tipo\":\"sensorGolpe\", \"valor\":1 , \"ID\":\"XAC1976\"}";
          webSocket.sendTXT(message);
  }
  lastState = currentState;


  if (newData) {
  float flat, flon;
  gps.f_get_position(&flat, &flon);

  flat = flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat;
  flon = flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon;

  String message = "{\"tipo\":\"sensorGPS\",\"lat\":" + String(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6) + ",\"lon\":" + String(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6) + ", \"ID\":\"XAC1976\"}";
  webSocket.sendTXT(message); // Enviar el mensaje JSON al WebSocket
  }

    // Código para NeoPixel y sensor de luz.
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  if (lightValue > 512) {
    drawTriangle();
    strip.show();
    delay(100);
  } else {
    clearDisplay();
    strip.show();
  }


  bool currentStateKY003 = digitalRead(SENSOR_KY003_PIN);
  if (currentStateKY003 != lastStateKY003 && currentStateKY003 == HIGH) {
      String message = "{\"tipo\":\"sensorIman\", \"valor\":1, \"ID\":\"XAC1976\"}";
      webSocket.sendTXT(message);
  }
  lastStateKY003 = currentStateKY003;
  

}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
    {
      Serial.println("WebSocket desconectado");
      break;
    }
    case WStype_CONNECTED:
    {
      Serial.println("WebSocket conectado");
      String message = "{\"tipo\":\"inicio\", \"usuario\":\"Cascos 1\", \"ID\":\"XAC1976\"}";
      webSocket.sendTXT(message);
      break;
    }
    case WStype_TEXT:
    {
      Serial.printf("WebSocket message: %s\n", payload);

      // Convierte el payload a String y luego a JsonObject para fácil acceso
      String jsonString = String((char*)payload);
      DynamicJsonDocument doc(256);
      deserializeJson(doc, jsonString);
      const char* tipo = doc["tipo"];
      int valor = doc["valor"];

      if (String(tipo) == "buzzer" && valor == 1) {
        digitalWrite(BUZZER_KY006_PIN, HIGH);   // Enciende el buzzer
        delay(100);                             // Lo deja encendido por 100ms
        digitalWrite(BUZZER_KY006_PIN, LOW);    // Apaga el buzzer
      }
      break;
    }
    // Puedes manejar otros tipos de eventos aquí
  }
}


void drawTriangle() {
  // Color anaranjado
  uint32_t orange = strip.Color(255, 165, 0); 

  for (int row = 0; row < 8; row++) {
    int startCol = 3 - (row / 2);
    int endCol = 4 + (row / 2);

    for (int col = startCol; col <= endCol; col++) {
      setPixelColor(col, row, orange);
    }
  }
}

void clearDisplay() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, 0);
  }
}

void setPixelColor(int x, int y, uint32_t color) {
  int pixelNumber;

  if (y % 2 == 0) { // Si la fila es par
    pixelNumber = (y * 8) + x;
  } else { // Si la fila es impar
    pixelNumber = (y * 8) + (7 - x);
  }

  strip.setPixelColor(pixelNumber, color);
}