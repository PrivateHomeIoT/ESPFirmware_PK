#include "handleMQTT.h"
#include "handleWifi.h"
#include "Arduino.h"

char mqtt_server[17]= "192.168.178.136";
int mqtt_port = 1500;
PubSubClient client(espClient);

void connectMQTT() {
  // Loop until we're reconnected
  if(connected){
    while (!client.connected()) {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqtt_server);
    // Attempt to connect
    if (client.connect(myHostname)) {
      Serial.println("connected");
      // Once connected, publish an announcement
      client.publish((char*)((String)myHostname + "/status").c_str(), "online");
      client.publish((char*)((String)myHostname + "/command").c_str(), "on");
      client.publish((char*)((String)myHostname + "/command").c_str(), "off");
      client.subscribe(((char*)((String)myHostname + "/").c_str()));
      client.subscribe(((char*)((String)myHostname + "/config").c_str()));
      client.subscribe(((char*)((String)myHostname + "/command").c_str()));
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
  char msg[100];
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg[i]=(char)payload[i];
  }
  Serial.println("  " + (String)myHostname + "/command");
  if (strcmp(topic, (char*)("Home/switch/cmnd/" + (String)myHostname).c_str()) == 0){
      Serial.println(msg);
      if (strcmp(msg, (char*)"1.0") == 0) digitalWrite(LED_BUILTIN, HIGH);
      else if (strcmp(msg, (char*)"0.0") == 0) digitalWrite(LED_BUILTIN, LOW);
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