#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

const char* ssid     = "Mobile"; // Your SSID (Name of your WiFi)
const char* password = "123456789"; //Your Wifi password

const char* host = "api.thingspeak.com";
String api_key = "04NXTNQ2T7BYIDFD"; // Your API Key provied by thingspeak

int MQ_2 = 13;
int MQ_6 = 12;
int MQ_135 = 14;
int MQ_2_value;
int MQ_6_value;
int MQ_135_value;

void setup(){
  Serial.begin(9600); // Starts the serial communication
  pinMode(MQ_2,INPUT);
  pinMode(MQ_6,INPUT);
  pinMode(MQ_135,INPUT);
  Connect_to_Wifi();
}

void loop(){
  MQ_2_value = analogRead(MQ_2);
  MQ_6_value = analogRead(MQ_6);
  MQ_135_value = analogRead(MQ_135);
  Serial.print("MQ_2_value:");
  Serial.println(analogRead(MQ_2));
  // Serial.print("MQ_6_value:");
  // Serial.println(MQ_6_value);
  // Serial.print("MQ_135_value:");
  // Serial.println(MQ_135_value);

  delay(5000);
  Send_Data(MQ_2_value);
  delay(5000);
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


void Send_Data(int MQ_2){
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
    data_to_send += "&field4=";
    data_to_send += String(MQ_2);
    data_to_send += "\r\n\r\n";
    // data_to_send += "&field5=";
    // data_to_send += String(MQ_135);
    // data_to_send += "\r\n\r\n";    

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
