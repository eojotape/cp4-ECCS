#include "Arduino.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include <DHT.h>

#define DHTPIN 13     // pino do sensor conectado
#define DHTTYPE DHT11   // modelo do sensor usado

DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "Pedro"; // Replace with your Wi-Fi SSID
char pass[] = "Pedro12345"; // Replace with your Wi-Fi password
char serverAddress[] = "https://api.tago.io/data"; // TagoIO API endpoint
char contentHeader[] = "application/json"; // Content type for HTTP request
char tokenHeader[] = "74123ea9-6948-4f20-840d-5c54aab14355"; // Your TagoIO token
HTTPClient client; // Initialize an instance of the HTTP client

const int LDR_PIN = 12;

unsigned long previousTime = 0;
int buzzerState = LOW;



void init_wifi() {
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int lightValue = analogRead(LDR_PIN);
    
     float tempC = dht.readTemperature(); // leitura da temperatura em Celsius
  float hum = dht.readHumidity(); // leitura da umidade relativa do ar
  Serial.print("Temperatura: ");
  Serial.print(tempC);
  Serial.print("°C, Umidade: ");
  Serial.print(hum);
  Serial.println("%");
  delay(2000);
    
  }

void setup() {
  Serial.begin(9600);
  dht.begin();

  
  delay(100); //quanto tempo entre cada leitura do monitor serial em ms
}

