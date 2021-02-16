#include "handlePorts.h"
#include "handleWifi.h"
#include "handleJSON.h"

char* handlePort (char* msg, char* topic){
    if (topic == (char*)((String)myHostname + "/").c_str()){
        if (msg == "1") digitalWrite(D2, HIGH);
        else if (msg == "0") digitalWrite(D2, HIGH);
    }
    return msg;
}