#include <Arduino.h>
#include <ESP8266WiFi.h>

class HtmlWrapper
{
  public:
    HtmlWrapper();
    ~HtmlWrapper();

    void DisplayWebPage(WiFiClient client, String state);
    String ActOnRequest(String header, int outputPin);
};
