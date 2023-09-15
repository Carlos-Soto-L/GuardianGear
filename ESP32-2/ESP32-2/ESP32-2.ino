#include <Wire.h>
#include <VL53L0X.h>
#include <Adafruit_NeoPixel.h>
#include <WebSocketsClient.h> 
#include <WiFi.h>

#define LDR_PIN 33
#define RGB_LED_R_PIN 26
#define RGB_LED_G_PIN 27
#define RGB_LED_B_PIN 25

#define LED_PIN     23
#define LED_COUNT   64 // 8x8
#define TOUCH_PIN   32
#define XSHUT_PIN   13

#define SENSOR_KY031_PIN 19

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
VL53L0X sensor;

WebSocketsClient webSocket;

// const char* ssid = "cortesía Soto Ledezma";
// const char* password = "9q6qT9CdU4";

const char* ssid = "NANO";
const char* password = "queso123";

bool sensorActive = true;
bool lastTouchState = false;
bool lastState = LOW;
bool currentState = LOW;
int contador = 1;

void setup() {
  Serial.begin(115200);

  Serial.println("Conectando a la red WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Conectando...");
  }

Serial.println("Conectado a la red WiFi!");

  // Setup del VL53L0X y NeoPixel
  pinMode(TOUCH_PIN, INPUT);
  pinMode(XSHUT_PIN, OUTPUT);
  pinMode(SENSOR_KY031_PIN, INPUT);
  digitalWrite(XSHUT_PIN, HIGH);
  delay(10);
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
  strip.begin();
  strip.show();

  // Setup del LDR y LED RGB
  pinMode(LDR_PIN, INPUT);
  pinMode(RGB_LED_R_PIN, OUTPUT);
  pinMode(RGB_LED_G_PIN, OUTPUT);
  pinMode(RGB_LED_B_PIN, OUTPUT);
  
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  
  ledcAttachPin(RGB_LED_R_PIN, 0);
  ledcAttachPin(RGB_LED_G_PIN, 1);
  ledcAttachPin(RGB_LED_B_PIN, 2);

  webSocket.begin("3.16.200.225", 3000);  // Reemplaza 'tu_servidor_websocket' con la dirección IP o el nombre de dominio y el puerto del servidor
  webSocket.onEvent(webSocketEvent); 

}

void setColor(int r, int g, int b) {
  ledcWrite(0, r);
  ledcWrite(1, g);
  ledcWrite(2, b);
}

void loop() {
  webSocket.loop();
  bool touchState = digitalRead(TOUCH_PIN);
  int ldrState = digitalRead(LDR_PIN);

  // Control del VL53L0X y NeoPixel
  if (touchState && !lastTouchState) {
    sensorActive = !sensorActive;

    if (sensorActive) {
      if (contador == 1) {
        digitalWrite(XSHUT_PIN, HIGH);
        delay(10);
        sensor.init();
        sensor.startContinuous();
        contador = 2;
      } else {
        digitalWrite(XSHUT_PIN, LOW);
        clearStrip();
        contador = 1;
      }
    }
  }
  lastTouchState = touchState;

  if (sensorActive) {
    int distance = sensor.readRangeContinuousMillimeters();
    Serial.print("Distancia: ");
    Serial.print(distance);
    if (sensor.timeoutOccurred()) {
      Serial.print(" TIMEOUT");
    }
    Serial.println(" mm");

    if (distance < 200) {
      drawCircle(strip.Color(255, 0, 0));
    } else if (distance >= 200 && distance <= 400) {
      drawCircle(strip.Color(255, 165, 0));
    } else if (distance != 65535) {
      drawCircle(strip.Color(0, 255, 0));
    }
    delay(1000);
  }

  // Control del LDR y LED RGB
  if(ldrState == LOW) {
    setColor(0, 0, 0);
  } else {
    setColor(255, 0, 0);
    delay(500);
    setColor(0, 255, 0);
    delay(500);
    setColor(0, 0, 255);
    delay(500);
  }

    // Lectura del sensor KY-031
  currentState = digitalRead(SENSOR_KY031_PIN);
  Serial.println(currentState);
  if (lastState == LOW && currentState == HIGH) {
      // Aquí tu código para manejar el golpe
      String message = "{\"tipo\":\"sensorGolpe\", \"valor\":1 , \"ID\":\"XAC1976\"}";
      webSocket.sendTXT(message);
      Serial.println("Mensaje websocket enviado");
  }
  lastState = currentState;
}

void drawCircle(uint32_t color) {
  clearStrip(); // Limpia la matriz primero

  // Definimos los LEDs que forman un círculo y su interior en la matriz 8x8
  int circleLEDs[] = {
    2, 3, 4, 5,
    9, 10, 11, 12, 13, 14,
    17, 18, 19, 20, 21, 22,
    25, 26, 27, 28, 29, 30,
    33, 34, 35, 36, 37, 38,
    41, 42, 43, 44, 45, 46,
    49, 50, 51, 52, 53, 54,
    58, 59, 60, 61
  };

  // Encender los LEDs definidos con el color especificado
  for (int i = 0; i < sizeof(circleLEDs) / sizeof(circleLEDs[0]); i++) {
    strip.setPixelColor(circleLEDs[i], color);
  }

  strip.show();
}

void clearStrip() {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
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