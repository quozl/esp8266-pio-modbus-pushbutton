// Modbus TCP pushbutton test for an ESP-01 module

// Input: GPIO0, 3.3V logic level
// Output: WiFi, mDNS, Modbus TCP, discrete input register 100
// Output: blue LED on TX means connected to network

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ModbusIP_ESP8266.h>
#include <ESP8266mDNS.h>

ESP8266WiFiMulti wifiMulti;
ModbusIP mb;

void setup() {
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);

  WiFi.stopSmartConfig();
  WiFi.enableAP(false);

  wifiMulti.addAP("ESSID1", "PASSPHRASE1");
  wifiMulti.addAP("ESSID2", "PASSPHRASE2");

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }
  digitalWrite(1, LOW);

  mb.server();
  pinMode(0, INPUT);
  mb.addIsts(100);

  MDNS.begin("mpb");
  MDNS.addService("modbus", "tcp", 502);
}

void loop() {
  if (wifiMulti.run() != WL_CONNECTED) {
    digitalWrite(1, HIGH);
    delay(100);
    return;
  }
  digitalWrite(1, LOW);

  mb.task();
  mb.Ists(100, digitalRead(0));
  MDNS.update();
}
