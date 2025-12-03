# Centax IoT module

[![License](https://img.shields.io/badge/license-BSD-blue.svg)](https://raw.githubusercontent.com/manti-by/Apollo/master/LICENSE)

## About

ESP01-S based tem and humidity monitoring app, a satellite for [ODIN server](https://github.com/manti-by/odin/)

Author: Alexander Chaika <manti.by@gmail.com>

Source link: https://github.com/manti-by/centax/

Requirements:

- ESP01-S module
- DHT11 sensor [module](https://github.com/IOT-MCU/ESP-01S-DHT11-v1.0)

## Setup Centax application

1. Install [arduino-cli](https://docs.arduino.cc/arduino-cli/installation/) and [make](https://www.gnu.org/software/make/) tools.

2. Clone sources

    ```shell
    mkdir /home/manti/app/
    git clone https://github.com/manti-by/centax/ app/
    ```

3. Setup Arduino ESP8266/ESP01 support

    ```shell
    cd /home/manti/app/centax/
    make setup
    ```

4. Connect ESP01-S to a Programmer/Flasher, compile and upload a binary

    ```shell
    make compile
    make upload
    ```

NOTE: Check [Makefile](Makefile) for more details about commands