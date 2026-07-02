# Smart Metereological Station with Arduino Uno
This project is about a metereological station developped in Arduino Uno that monitors the temperature and humidity
in real time using the DHT22 sensor and exhibits the data using an LCD 16x2 with the I2C protocol.

# Functionalities
* **Real Time Monotoring**: The temperature and humidity data is monitored in each 2 seconds.
* **Local Interface**: The data is exhibited in the LCD 16x2 using the protocol I2C.
* **IOT integration**: The data is send in a **JSON format** throw the UART port allowing the integration
  with Python scripts.
* **Timing of Code**: The use of millis() allows a better flow of the code and of the processor.

# Connections
The connection schematic is available inside of the folder.

# How to use
1. You can clone this repository or copy the code inside the sketch.ino.
2. You need to install the following libraries:
   * `DHT sensor library`(by Adafruit)
   * `Liquid Crystal I2C` (by Frank de Brabander)
3. Do the **Upload** of the code to the Arduino.
4. Open the **Serial Monitor** with the baud rate of 9600
5. Every 2 seconds the LCD will display the data and the serial monitor will display the data like a JSON format.
