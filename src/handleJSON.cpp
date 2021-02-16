#include <Arduino.h>
#include <Arduino_Json.h>
#include <LittleFS.h>
#include <EEPROM.h>
#include "handleJSON.h"
#include "handlePorts.h"
#include "handleHttp.h"
#include "handleWifi.h"
#include "handleEncryption.h"
#include "handleMQTT.h"

void loadData(){
    EEPROM.begin(512);
    EEPROM.get(0, ssid);
    EEPROM.get(0 + sizeof(ssid), password);
    char ok[2 + 1];
    EEPROM.get(0 + sizeof(ssid) + sizeof(password), aes_key);
    EEPROM.get(0 + sizeof(ssid) + sizeof(password) + sizeof(aes_key), aes_iv);
    EEPROM.get(0 + sizeof(ssid) + sizeof(password) + sizeof(aes_key) + sizeof(aes_iv), ok);
    EEPROM.end();
    if (String(ok) != String("OK"))
    {
        ssid[0] = 0;
        password[0] = 0;
        firstBoot = true;
    }
    Serial.println("Recovered credentials:");
    Serial.println(ssid);
    Serial.println(strlen(password) > 0 ? "********" : "<no password>");
    Serial.println("Finished loading data");
}

void saveData(){
    EEPROM.begin(512);
    EEPROM.put(0, ssid);
    EEPROM.put(0 + sizeof(ssid), password);
    char ok[2 + 1] = "OK";
    EEPROM.put(0 + sizeof(ssid) + sizeof(password), aes_key);
    EEPROM.put(0 + sizeof(ssid) + sizeof(password) + sizeof(aes_key), aes_iv);
    EEPROM.put(0 + sizeof(ssid) + sizeof(password) + sizeof(aes_key) + sizeof(aes_iv), ok);
    EEPROM.commit();
    EEPROM.end();
    Serial.println("Saved wifi credentials");
}