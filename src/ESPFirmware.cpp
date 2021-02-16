#include "handleWifi.h"
#include "handleHttp.h"

void setup(){
    delay(1000);
    pinMode(D2, OUTPUT);
    Serial.begin(115200);
    Serial.println();
    wifiSetup();
    httpSetup();
}

void loop(){
    wifiLoop();
}