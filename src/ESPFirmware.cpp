#include "handleWifi.h"
#include "handleHttp.h"
#include "handleJSON.h"
#include "handleMQTT.h"

void setup(){
    delay(1000);
    pinMode(D2, OUTPUT);
    Serial.begin(115200);
    Serial.println();
    loadData();
    wifiSetup();
    httpSetup();
}

void loop(){
    delay(100);
    wifiLoop();
    loopMQTT();
}