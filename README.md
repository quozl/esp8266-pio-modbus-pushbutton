# Modbus TCP pushbutton test for an ESP-01 module

A prototype for integrating an ESP-01 into an industrial Modbus TCP network.

## Hardware

* an ESP-01 module,
* a pushbutton,

## Firmware

* associates with first available known Wi-Fi network, indicating connection status using the blue LED on the ESP-01 module,
* presents an mDNS host and service,
* responds to Modbus TCP queries by reading the GPIO0 pushbutton,
* depends on a [Modbus Library for Arduino](https://github.com/emelianov/modbus-esp8266),
* built with [PlatformIO](https://platformio.org),

## Software

* a test script for probing the device,
* written in Python,
* displays query and response,
* returns pushbutton status as exit status.

----
