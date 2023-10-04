#include "Arduino.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include <DHT.h>

#define DHTPIN 13     // pino do sensor conectado
#define DHTTYPE DHT11   // modelo do sensor usado

  DHT dht(DHTPIN, DHTTYPE);
  
  float tempC = 0; // leitura da temperatura em Celsius
  float hum = 0; // leitura da umidade relativa do ar


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

 tempC = dht.readTemperature(); // leitura da temperatura em Celsius
 hum = dht.readHumidity(); // leitura da umidade relativa do ar

  Serial.print("Temperatura: ");
  Serial.print(tempC);
  Serial.print("°C, Umidade: ");
  Serial.print(hum);
  Serial.println("%");
  Serial.print(lightValue);
  send_temperatura();
  send_humidade();
    delay(2000);
    
  }
 void send_temperatura() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;
  strcpy(postData, "{\n\t\"variable\": \"tempC\",\n\t\"value\": ");
  dtostrf(tempC, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);
  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}

void send_humidade() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;
  strcpy(postData, "{\n\t\"variable\": \"hum\",\n\t\"value\": ");
  dtostrf(hum, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"%\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
}
void setup() {
  Serial.begin(9600);
  dht.begin();
  init_wifi();
  
  delay(100); //quanto tempo entre cada leitura do monitor serial em ms
}
