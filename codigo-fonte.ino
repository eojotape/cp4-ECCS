#include "Arduino.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include <DHT.h>

char ssid[] = ""; // Replace with your Wi-Fi SSID
char pass[] = ""; // Replace with your Wi-Fi password
char serverAddress[] = "https://api.tago.io/data"; // TagoIO API endpoint
char contentHeader[] = "application/json"; // Content type for HTTP request
char tokenHeader[] = "74123ea9-6948-4f20-840d-5c54aab14355"; // Your TagoIO token
HTTPClient client; // Initialize an instance of the HTTP client

const int LDR_PIN = A0;
const int GREEN_LED_PIN = 2;
const int YELLOW_LED_PIN = 3;
const int RED_LED_PIN = 4;
const int BUZZER_PIN = 8;
const int ALERT_THRESHOLD = 200; //isso é quanto o sensor capta de luminosidade

unsigned long previousTime = 0;
int buzzerState = LOW;

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

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
  Serial.print("Luminosidade: "); //report no monitor serial
  Serial.println(lightValue);

  if (lightValue >= 350  ) { //969 é o equivalente a máxima luminosidade no tinkercad, na vida real varia e precisamos ajustar o valor conforme necessário. A leitura deve ser feita pelo 
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
  
  }
  else if (lightValue > ALERT_THRESHOLD) { //alert_threshold indica o valor do intervalo de luminosidade, nesse caso se for > que 50, a luz amarela se acende
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    
  } 
  else { 
    digitalWrite(GREEN_LED_PIN, LOW); //se qualquer coisa fora das condições acima ocorrer, o verde se acende, ou seja, o verde só acende se o valor ideal de luminosidade estiver definido.
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    delay(3000);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(3000);
    digitalWrite(BUZZER_PIN, LOW);
  }
  
  delay(100); //quanto tempo entre cada leitura do monitor serial em ms
}
