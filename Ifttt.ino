#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTTYPE DHT22   
#define DHTpin 5
float T;

DHT dht(DHTpin, DHTTYPE); 

const char* ssid     = "Hinojosa";
const char* password = "*********";

const char* resource = "https://maker.ifttt.com/trigger/eventoRE/json/with/key/lCzCjQ1cf2zr1oc6C-NoLUyg8fVUnlO-U0oRRr07t_5";
const char* server = "maker.ifttt.com";

void setup() {
Serial.begin(9600);
dht.begin();
}

void loop() 
{
    T = dht.readTemperature(); 
    if (T>10)
    {
      WiFiClient client;

      client.print(String("GET ") + resource + 
                      " HTTP/1.1\r\n" +
                      "Host: " + server + "\r\n" + 
                      "Connection: close\r\n\r\n");
                  
      int timeout = 5 * 10; // 5 seconds             
      while(!!!client.available() && (timeout-- > 0))
      {
        delay(100);
      }
      while(client.available())
      {
        Serial.write(client.read());
      }
      client.stop();
    }
    else 
    {
      return;
    }
  }  
