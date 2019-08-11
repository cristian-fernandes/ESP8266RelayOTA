#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "OtaWrapper.h"
#include "HtmlWrapper.h"

// Setting the Wi-Fi credentials
const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const long timeoutTime = 2000;
const int output = 0;


// Setting the fixed IP properties (To have a fixed address and also for OTA)
IPAddress ip(192, 168, 0, 50);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0, 1);

// Instantiating a Web Server in PORT 80
WiFiServer server(80);

//Object encapsulating OTA Commands
OtaWrapper *otaWrapper;

// Object encapsulating HTML Stuff
HtmlWrapper *htmlWrapper;

String header;
String outputState = "Desligada";

unsigned long currentTime = millis();
unsigned long previousTime = 0; 

void PoolWifi();
void DisplayWebPage(WiFiClient client, String state);
String ActOnRequest(String header);

void setup() 
{
  Serial.begin(115200);
  pinMode(output, OUTPUT);

  // Setting output to LOW, for starters
  digitalWrite(output, LOW);

  // Connect to Wi-Fi network with the credentials provided earlier
  WiFi.config(ip, dns, gateway, subnet); 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  otaWrapper = new OtaWrapper();

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  // Handle OTA Upload if necessary
  otaWrapper->handleOta();

  // Pools ESP8266 Port looking for Clients
  PoolWifi();
}

void PoolWifi()
{
  // Listening for incoming clients
  WiFiClient client = server.available();   

  // We got a client :)
  if (client) 
  {
    Serial.println("New Client.");

    //String to hold incoming data from the client
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;

    // Loop while the client is with an open connection
    while (client.connected() && currentTime - previousTime <= timeoutTime) 
    { 
      currentTime = millis();        

      if (client.available()) 
      {        
        // Read client's request byte by byte
        char c = client.read();
        Serial.write(c);
        header += c;

        // If the byte is return
        if (c == '\n') 
        {
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            //Act accordingly to the request
            outputState = htmlWrapper->ActOnRequest(header, output);
            
            // Display the HTML web page to the client
            htmlWrapper->DisplayWebPage(client, outputState);

            // Break out of the while loop
            break;

          } 
          else 
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } 
        else if (c != '\r') 
        {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }

    // Clear the header variable
    header = "";

    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");  
  }
}
