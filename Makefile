setup:
	sudo usermod -a -G dialout root
	sudo arduino-cli config set board_manager.additional_urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
	sudo arduino-cli core update-index
	sudo arduino-cli core install esp8266:esp8266
	sudo arduino-cli lib install 'Adafruit Unified Sensor' 'DHT sensor library'

compile:
	sudo arduino-cli compile --fqbn esp8266:esp8266:generic centax.ino

upload:
	sudo arduino-cli upload -b esp8266:esp8266:generic -p /dev/ttyUSB0

monitor:
	sudo arduino-cli monitor -p /dev/ttyUSB0 -b esp8266:esp8266:generic -c baudrate=115200
