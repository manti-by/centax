setup:
	usermod -a -G dialout root
	arduino-cli config set board_manager.additional_urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
	arduino-cli core update-index
	arduino-cli core install esp8266:esp8266
	arduino-cli lib install 'Adafruit Unified Sensor' 'DHT sensor library'

compile:
	arduino-cli compile --fqbn esp8266:esp8266:generic --build-property "build.extra_flags=-DWIFI_PASSWORD=\"${WIFI_PASSWORD}\"" centax.ino

upload:
	arduino-cli upload -b esp8266:esp8266:generic -p /dev/ttyUSB0

monitor:
	arduino-cli monitor -p /dev/ttyUSB0 -b esp8266:esp8266:generic -c baudrate=115200

check:
	arduino-lint
