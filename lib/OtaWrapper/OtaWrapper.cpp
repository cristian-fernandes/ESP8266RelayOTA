#include <SPI.h>
#include <FS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "OtaWrapper.h"

OtaWrapper::OtaWrapper()
{
    ArduinoOTA.onStart([]()
    {  
        String type;

        ArduinoOTA.getCommand() == U_FLASH ?  type = "sketch" : type = "filesystem";       

        Serial.println("OTA Start updating " + type);
    });

    ArduinoOTA.onEnd([]() 
    {      
        Serial.println("\nEnd");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
        Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) 
    {
        Serial.printf("OTA Error[%u]: ", error);

        switch(error) 
        {
            case OTA_AUTH_ERROR:
                Serial.println("Auth Failed");
            break;
            case OTA_BEGIN_ERROR:
                Serial.println("Begin Failed");
            break; 
                case OTA_CONNECT_ERROR:
                Serial.println("Connect Failed");
            break;
            case OTA_RECEIVE_ERROR:
                    Serial.println("Receive Failed");
            break; 
                case OTA_END_ERROR:
                    Serial.println("End Failed");
            break; 

        }
    });

    ArduinoOTA.begin();  
}

void OtaWrapper::handleOta()
{
    ArduinoOTA.handle();
}