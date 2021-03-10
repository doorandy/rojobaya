#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>


const char* ssid = "IZZI-73B1";
const char* password = "chocolatin19";


int izq = 5;
int der = 4;
int d = 0;
int i = 0;
int estado = 0;

String server = "http://192.168.0.3:8000/guardarData";

void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  pinMode(der, INPUT);
  pinMode(izq, INPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("WiFi contectado");
}

void loop() {
  d = digitalRead(der);
  i = digitalRead(izq);
  if(d == 1 && i == 1 && estado != 1)
  {
    post("Apagado");
    Serial.println("Apagado");
    estado = 1;
  }
  else
  {
    if (d==1 && i==0 && estado != 2)
    {
      post("Derecha");
      Serial.println("Derecha");
      estado = 2;
    }
    else
    {
      if (i==1 && d==0 && estado != 3)
      {
        post("Izquierda");
        Serial.println("Izquierda");
        estado = 3;
      }
    }
  }
  // put your main code here, to run repeatedly:
}
void post(String estado) {
  HTTPClient http;
  String json;
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["estado"] = estado;
  root.printTo(json);
  http.begin(server); //URL del microservicio
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  Serial.println(json);
  http.end();
}
