
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

const char* ssid     = "Avdhoot"; // Your SSID (Name of your WiFi)
const char* password = "Avdhoot#1234"; //Your Wifi password


const char* host = "api.thingspeak.com";
String api_key = "UEOX0EAZIR30LH58"; // Your API Key provied by thingspeak

int Soil_Moisture_Sensor = 13;
int Soil_Moisture_Sensor_Value;
void setup ()
{
  pinMode(Soil_Moisture_Sensor,INPUT);
  Serial.begin(9600);
  Connect_to_Wifi();

}
void loop ()
{
Send_Data(getSensorData());

}

void Connect_to_Wifi()
{
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

float getSensorData(){

  Soil_Moisture_Sensor_Value = analogRead(Soil_Moisture_Sensor);   
  Serial.print("Soil_Moisture_Sensor_Value:");
  Serial.println(Soil_Moisture_Sensor_Value);

  return Soil_Moisture_Sensor_Value;   
}

void Send_Data(int Sensor_data){
  Serial.println("");
  Serial.println("Prepare to send data");

  WiFiClient client;
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else
  {
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(Sensor_data);
    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);
    delay(1000);
  }

  client.stop();
}
