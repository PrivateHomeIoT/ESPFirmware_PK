#include "handleMQTT.h"
#include "handleWifi.h"

char* mqtt_server = (char*) "192.168.178.136";
int mqtt_port = 1500;
char* msg;
PubSubClient client(espClient);

void connectMQTT() {
  // Loop until we're reconnected
  if(connected){
    while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(myHostname)) {
      Serial.println("connected");
      // Once connected, publish an announcement
      client.publish((char*)((String)myHostname + "/status").c_str(), "online");
      client.subscribe((char*)myHostname);

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if (topic == (char*)((String)myHostname + "/").c_str()){
      if (msg == "1") digitalWrite(D2, HIGH);
      else if (msg == "0") digitalWrite(D2, HIGH);
      }
}

void loopMQTT() {
  if (!client.connected()) connectMQTT();
  client.loop();
}

void setupMQTT(){
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    connectMQTT();
    client.publish((char*)((String)myHostname + "/config").c_str(), myHostname);
}