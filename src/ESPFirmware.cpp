#include "handleWifi.h"
#include "handleHttp.h"
#include "handleJSON.h"

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
    wifiLoop();
}