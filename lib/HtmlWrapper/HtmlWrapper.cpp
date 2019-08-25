#include <SPI.h>
#include <FS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "HtmlWrapper.h"

HtmlWrapper::HtmlWrapper()
{
}

void HtmlWrapper::DisplayWebPage(WiFiClient client, String state)
{
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");          
  
  // CSS to style the on/off buttons 
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #0000FF; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #77878A;}</style></head>");
  
  // Web Page Heading
  client.println("<body><h1>L&Acirc;MPADA DA GARAGEM</h1>");
  
  // Display current state, and ON/OFF buttons for GPIO
  client.println("<p>A l&acirc;mpada est&aacute;:  " + state + "</p>");
  
  // If the state is off, it displays the ON button       
  if (state == "Desligada") 
  {
    client.println("<p><a href=\"/on\"><button class=\"button\">LIGAR</button></a></p>");
  } 
  else 
  {
    client.println("<p><a href=\"/off\"><button class=\"button button2\">DESLIGAR</button></a></p>");
  } 
      
  client.println("</body></html>");
  
  // The HTTP response ends with another blank line
  client.println();
}

String HtmlWrapper::ActOnRequest(String header,  int outputPin)
{
  String outputState;

  if (header.indexOf("GET /on") >= 0)
  {
    Serial.println("GPIO 0 ON");
    outputState = "Ligada";
    digitalWrite(outputPin, HIGH);
  } 
  else if (header.indexOf("GET /off") >= 0) 
  {
    Serial.println("GPIO 0 OFF");
    outputState = "Desligada";
    digitalWrite(outputPin, LOW);
  }

  return outputState;
}
