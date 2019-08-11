#include <SPI.h>
#include <FS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

class OtaWrapper
{
  public:
    OtaWrapper();
    ~OtaWrapper();

    //Handle OTA
    void handleOta();
};