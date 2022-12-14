#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTTYPE DHT22
int DHTPin = D5; 
DHT dht(DHTPin, DHTTYPE);

const char* ssid = "Students";
const char* password = "alumnosITPA";
WiFiServer server(80);

void setup() 
{
  Serial.begin(9600);

  pinMode(DHTPin, INPUT);
  dht.begin(); 
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.print("IP: ");  
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() 
{
  WiFiClient client = server.available();
  if (!client) {
  return;
  }
  while(!client.available()){
  }

  
  int Temperature = dht.readTemperature(); 
  int Humidity = dht.readHumidity(); 
  
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("ESP8266 Server");
  client.println("<br><br>");
  client.println("Temperature: ");
  client.println(Temperature);
  client.println("C");
  client.println("<br>");
  client.println("Humidity: ");
  client.println(Humidity);
  client.println("%");
  client.println("</html>");

  delay(20000);
}