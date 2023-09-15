#include <ESP8266WiFi.h>
#include <WebSocketsClient.h> 

WebSocketsClient webSocket;

// const char* ssid = "cortesía Soto Ledezma";
// const char* password = "9q6qT9CdU4";

const char* ssid = "NANO";
const char* password = "queso123";

const int clkPin = D1;      // Conecta al pin CLK del rotary encoder
const int dtPin = D2;       // Conecta al pin DT del rotary encoder
const int buttonPin = D3;   // Conecta al pin SW del rotary encoder

// Pin del LED (PWM)
const int ledPin = D5;      // Asume que se usa el pin D5 (PWM) para el LED

// Pines para los LEDs controlados por el sensor KY-027
const int LED1_PIN = D6;
const int LED2_PIN = D7;

#define KY032_SENSOR_PIN D4 // Puedes cambiar el pin según tu conexión


// Para el sensor KY-027
#define SENSOR_PIN D8

// Para determinar la dirección del giro del encoder
int lastStateCLK;
int currentStateCLK;

// Valor de intensidad del LED (0 apagado, 1023 máximo en ESP8266)
int ledValue = 0; 

bool ledOn = true;   // Asumimos que el LED comienza encendido

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(clkPin, INPUT_PULLUP);
  pinMode(dtPin, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);

  lastStateCLK = digitalRead(clkPin); 
  analogWrite(ledPin, ledValue);

  pinMode(KY032_SENSOR_PIN, INPUT);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");

    webSocket.begin("3.16.200.225", 3000);  // Reemplaza 'tu_servidor_websocket' con la dirección IP o el nombre de dominio y el puerto del servidor
  webSocket.onEvent(webSocketEvent); 

}

void loop() {
  webSocket.loop();
  currentStateCLK = digitalRead(clkPin);
  if (currentStateCLK != lastStateCLK) {     
    if (digitalRead(dtPin) != currentStateCLK) {
      ledValue += 10; 
      if (ledValue > 1023) ledValue = 1023;
    } else {
      ledValue -= 10;  
      if (ledValue < 0) ledValue = 0;
    } 
    if (ledOn) {
      analogWrite(ledPin, ledValue);
    }
  } 
  lastStateCLK = currentStateCLK;

  if (digitalRead(buttonPin) == LOW) {
    if (ledOn) {
      analogWrite(ledPin, 0);
    } else {
      analogWrite(ledPin, 200); 
    }
    ledOn = !ledOn;
    delay(200);
  }

  // Código para el sensor KY-027
  int sensorValue = digitalRead(SENSOR_PIN);
  
  if(sensorValue == LOW) {
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
  } else {
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
  }

  int ky032Value = digitalRead(KY032_SENSOR_PIN);

  if(ky032Value != HIGH) {  // Asume que HIGH significa objeto detectado
    Serial.println("Objeto");
    String message = "{\"tipo\":\"Infrarojo\", \"valor\":1 , \"ID\":\"XAC1976\"}";
    webSocket.sendTXT(message);
    Serial.println("Mensaje websocket enviado");
    delay(200);
  }
  

}


void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Desconectado!\n");
            break;
        case WStype_CONNECTED:
            Serial.printf("[WSc] Conectado a la URL: %s\n", payload);
            break;
        // case WStype_TEXT:
        //     Serial.printf("[WSc] Mensaje recibido: %s\n", payload);
        //     break;
        // case WStype_BIN:
        //     Serial.printf("[WSc] Datos binarios recibidos: %u bytes\n", length);
        //     break;
    }
}