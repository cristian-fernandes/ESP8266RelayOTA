# ESP8266-01 Relay OTA

This sketch is a basic way to control a output pin through internet, it can be used in an infinity of things, my initial idea while creating this was to turn ON the lamp in my garage from the Wi-Fi connection, this way I can turn the lights on without entering the house.

This sketch needs basically:
  - ESP8266-01 (with NODEMCU firmware)
  - Something to be connected in the PIN 0 of the ESP8266-01 for the output of 3.3V.

# Features 

  - Webpage hosted in the ESP8266-01 where we can turn the pin on/off (webpage is currently in brazilian portuguese, sorry)
  - OTA: Over-the-air enabled: This way we can upgrade or modify our sketch without a serial connection, all the magic happens through WI-FI.
