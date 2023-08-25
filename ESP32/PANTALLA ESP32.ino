#include <TFT_eSPI.h>
#include <WiFi.h>           // Para conectar el ESP32 a una red WiFi
#include <WebSocketsClient.h> // Para usar el cliente WebSocket
#include <ArduinoJson.h>

TFT_eSPI tft = TFT_eSPI();
WebSocketsClient webSocket;

const char* ssid = "NANO";
const char* password = "queso123";
const char* serverIP = "3.134.204.135"; // Cambia esto a la IP del servidor WS
const uint16_t serverPort = 3000; // Cambia esto al puerto donde esté ejecutándose el servidor WebSocket

// Variables para los datos de temperatura y humedad
// int temp = 25;
// int humidity = 50;

float temp = 25.0;
float humidity = 50.0;

// Índice para la posición x en el gráfico
int xIndex = 0;

// Variables para almacenar el punto anterior
int prevTempY = 0;
int prevHumidityY = 0;

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  
  // Dibujar ejes para temperatura
  drawAxes(5, "Temp", 15, 35);
  
  // Dibujar ejes para humedad
  drawAxes(165, "Hum", 30, 100);

    // Conectamos a WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado!");

  // Configuramos el cliente WebSocket
  webSocket.begin(serverIP, serverPort);
  webSocket.onEvent(webSocketEvent);
}

void drawAxes(int xStart, const char* title, int minValue, int maxValue) {
  // Dibuja los ejes
  tft.drawLine(xStart, 10, xStart, 210, TFT_WHITE);    // Eje Y
  tft.drawLine(xStart, 210, xStart + 150, 210, TFT_WHITE); // Eje X
  
  // Etiquetas para el eje Y
  tft.drawString(String(minValue), xStart - 20, 200, 2);
  tft.drawString(String((maxValue + minValue) / 2), xStart - 30, 105, 2);
  tft.drawString(String(maxValue), xStart - 20, 10, 2);
  
  // Etiquetas para el eje X (asumiendo que se trate del tiempo, en segundos)
  tft.drawString("0s", xStart, 215, 2);
  tft.drawString("T", xStart + 140, 215, 2);
}

void loop() {

  webSocket.loop();
  //delay(500); // Demora para visualización
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
if (type == WStype_TEXT) {
    String json = String((char *)payload);

    // Crear un objeto JsonDocument. Debes ajustar la capacidad según tu necesidad.
    StaticJsonDocument<200> doc;

    // Analizar el mensaje JSON
    DeserializationError error = deserializeJson(doc, json);
    if (error) {
      Serial.print("deserializeJson() falló: ");
      Serial.println(error.f_str());
      return;
    }

    // Verificar el tipo de mensaje
    const char* tipo = doc["tipo"];
    if (!tipo || strcmp(tipo, "sensorDHT11") != 0) {
      // No es el tipo de mensaje que esperamos, así que lo ignoramos
      return;
    }

    Serial.println("Mensaje recibido: " + json);

    // Obtener los datos del JSON
    // temp = doc["temp"];
    // humidity = doc["hum"];

    temp = doc["temp"].as<float>();
    humidity = doc["hum"].as<float>();

    // Dibujar datos
    plotData();
    
    // Actualizar valor actual de temperatura y humedad junto a sus títulos
    tft.fillRect(5 + 40, 5, 40, 10, TFT_BLACK);
    tft.drawString("Temp " + String(temp) + "°C", 5 + 40, 5, 2);

    tft.fillRect(165 + 30, 5, 50, 10, TFT_BLACK);
    tft.drawString("Hum " + String(humidity) + "%", 165 + 30, 5, 2);
    
    // Incrementar índice x
    xIndex += 2;
    
    if (xIndex >= 140) {
      xIndex = 0;
      prevTempY = 0;
      prevHumidityY = 0;
      tft.fillRect(6, 11, 149, 199, TFT_BLACK);     // Limpiar área del gráfico de temperatura
      tft.fillRect(166, 11, 149, 199, TFT_BLACK);   // Limpiar área del gráfico de humedad

      // Dibujar ejes para temperatura
      drawAxes(5, "Temp", 15, 35);
      
      // Dibujar ejes para humedad
      drawAxes(165, "Hum", 30, 100);

    }
  }
}

void plotData() {

  // Verificar y ajustar los valores si están fuera de rango
  temp = constrain(temp, 15.0, 35.0);
  humidity = constrain(humidity, 30.0, 100.0);

  int yTemp = map(temp, 15, 35, 200, 110);
  int yHumidity = map(humidity, 30, 100, 200, 10);

  // Dibujar las líneas de temperatura
  if (prevTempY != 0) {
    tft.drawLine(5 + xIndex - 2, prevTempY, 5 + xIndex, yTemp, TFT_RED);
  }

  // Dibujar las líneas de humedad
  if (prevHumidityY != 0) {
    tft.drawLine(165 + xIndex - 2, prevHumidityY, 165 + xIndex, yHumidity, TFT_BLUE);
  }

  // Actualizar los valores anteriores
  prevTempY = yTemp;
  prevHumidityY = yHumidity;
}