/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SDA_PIN 2
#define SCL_PIN 13
#define TILT_SENSOR_PIN 14

bool screenOn = true; // para controlar si la pantalla está encendida o apagada

// Pin del sensor KY-039
const int pulsePin = 12;
const int tempPin = 15;
int pulseValue;
int tempValue;

float R1 = 10000; // value of R1 on board
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; 


// Variables para cálculo de frecuencia cardíaca
unsigned long previousMillis = 0; 
const long interval = 1000; // Intervalo de 1 segundo
int beatCount = 0; 
int heartRate = 0;
int lastPulseValue = 0;
bool beatDetected = false;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  pinMode(TILT_SENSOR_PIN, INPUT_PULLUP);
  Wire.begin(SDA_PIN, SCL_PIN);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
}

void loop() {

  bool tiltState = digitalRead(TILT_SENSOR_PIN);
  if (tiltState && !screenOn) {
    display.ssd1306_command(SSD1306_DISPLAYON); // Encender pantalla
    screenOn = true;
  } else if (!tiltState && screenOn) {
    display.ssd1306_command(SSD1306_DISPLAYOFF); // Apagar pantalla
    screenOn = false;
  }

  // Leer el valor del sensor
  pulseValue = analogRead(pulsePin);
  tempValue = analogRead(tempPin);
  Serial.println(tempValue);

  // Convertir lectura de temperatura a grados Celsius
  R2 = R1 * (1023.0 / (float)tempValue - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
  T = T - 273.15;
  
  // Detectar latido
  if (pulseValue > 100 && lastPulseValue <= 100 && !beatDetected) {
    beatDetected = true;
    beatCount++;  // Incrementar el conteo de latidos cuando se detecta uno
  } 
  else if (pulseValue <= 100 && beatDetected) {
    beatDetected = false;  // Resetear el detector de latidos cuando el valor caiga por debajo del umbral
  }
  
  if(beatDetected) {
    beatCount++;
  }

  // Cálculo de frecuencia cardíaca cada segundo
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    heartRate = beatCount * 60; // Convertir a latidos por minuto
    beatCount = 0;  // Reiniciar el conteo de latidos
  }

  lastPulseValue = pulseValue;

  // Mostrar frecuencia cardíaca
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  if(heartRate > 0) {
    display.println("Frecuencia Cardiaca: " + String(heartRate) + " BPM"); 
    display.println("Temp.: " + String(T) + "C");
  } else {
    display.println("Pulso: No detectado");
    display.println("Temp.: " + String(T) + "C");
  }

  display.display();
  delay(500); // Delay para refrescar la información cada medio segundo
}

float convertToCelsius(int analogValue) {
  float referenceValue = 480;  // Valor promedio aproximado a 16°C
  float referenceTemperature = 16.0; // 16°C
  float conversionFactor = 0.1;  // Este factor es una suposición, y tendrás que ajustarlo según tus necesidades

  return referenceTemperature + (analogValue - referenceValue) * conversionFactor;
}