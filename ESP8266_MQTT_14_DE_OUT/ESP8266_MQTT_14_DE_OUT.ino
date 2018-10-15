#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "GVT-4141";
const char* password =  "1532000662";
const char* mqttServer = "m15.cloudmqtt.com";
const int mqttPort = 11727;
const char* mqttUser = "sttavgpn";
const char* mqttPassword = "tJ6Ni1VSRamY";
unsigned int lastCall = 0;
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()){
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )){
      Serial.println("connected");
    }
    else{
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  client.subscribe("Linha_303");
  client.publish("teste", "Im Ready");
}
 
void callback(char* topic, byte* payload, unsigned int length){
  String mensagem = "";
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
    mensagem += (char)payload[i];
  }
  Serial.println();
  Serial.print("O endereço da parada onde a pessoa deseja embarcar é: ");Serial.println(mensagem);
  Serial.println("-----------------------");
}
 
void loop(){
  client.loop();
  if(millis() - lastCall > 10000){
    Serial.println("Looping");
    lastCall = millis();
  }
}
