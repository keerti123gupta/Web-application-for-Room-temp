#include<DHT.h>
#include<ESP8266WiFi.h>

#define DHTTYPE DHT11
#define DHTPIN D5

DHT dht(DHTPIN, DHTTYPE);

const char* wname = "Mercury X";
const char* password = "C100diya";
const char* host = "118.185.43.122";
String url = "http://118.185.43.122/0187cs161069/dht11/submit.php";

int wifi = D4;
int sync = D0;

void setup() {
  Serial.begin(9600);
  pinMode(wifi,OUTPUT);
  pinMode(sync,OUTPUT);
  WiFi.begin(wname, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(wifi, HIGH);
    delay(500);

    digitalWrite(wifi, LOW);
    delay(500);
  }
  digitalWrite(wifi, LOW);
  dht.begin();
  delay(2000);
}

void loop() {
  String temp = url;
  float t = dht.readTemperature();
  float t1 = dht.readTemperature(true);
  float h = dht.readHumidity();
  delay(1000);

    WiFiClient client;
    const int port = 80;
    if (!client.connect(host, port)) {
    Serial.println("Connection Failed");
    digitalWrite(sync, HIGH);
    return;
  }
  temp += "?Temp_C=";
  temp += (String)t;
  temp += "&Temp_F=";
  temp += (String)t1;
  temp += "&Humidity=";
  temp += (String)h;
  
  Serial.println(temp);
  client.print(String ("GET ") + temp + " HTTP/1.1\r\n" +  "Host: " + host + "\r\n" +  "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while( client.available() == 0 ){

      if (millis() - timeout > 5000){
          Serial.println("Connection Timeout");
          client.stop();
          return;
      }

      if (client.available()){

          String data = client.readStringUntil('\r');
          Serial.print(data);
          for(int i = 1 ; i<10 ; i++){
            digitalWrite(sync, LOW);
            delay(100);

            digitalWrite(sync, HIGH);
            delay(100);
          }  
      }

            digitalWrite(sync, LOW);
            delay(4000);
  }
}

