# Box-Sizing-Tool

## Goal
To develop an Arduino based “box-sizing-tool”, that allows packages to be placed on a surface and reads back their weight, width, length and height.

## How to use it and makes changes
If you want to just use the tool, connect it to power and make sure the scale is connected, otherwise it won't initialize. Don't place anything on the scale, or it will be tared wrong. Then wait for the logos to show, and place a package on the loading surface. The live values will be shown on the onboard screen.
If you want to make changes, download the entire repository and install all the Arduino libraries listed below. Open the folder as a PlatformIO Project.
Just run and change the `main.cpp` file like a normal Arduino file and flash it to the board as usual.

## Components
1x Metal frame
1x Loading surface
1x Micro USB cable
3x US sensors
4x 50 kg load cells
4x 4-wire du Pont cables 
3x US sensor casing

## Method
An ultrasonic sensor is used to measure the distance to the package. That distance is subtracted from the distance of the sensor to the central axis, returning the size of the corresponding side of the package. This is done three times in sequence, once for every side, resulting in all the package’s sides being measured. 
Four 50 kg load cells, placed beneath the loading surface and in direct contact with it, measure the weight of the package. All the size and weight measurements are then displayed on the Arduino’s onboard screen. This sequence is repeated continuously and indefinitely. 


### Detail

#### Ultrasonic sensor
Emits an ultrasonic wave and measures the time it takes to reflect back. That time is then converted to distance in the code [(learn more)](https://www.keyence.com/ss/products/sensor/sensorbasics/ultrasonic/info/).

#### 50 kg load cells
The spring loaded cell bends under load. A strain gauge perceives the this and returns a value for it. This value is converted into usable units using a factor. In the code, the outputted value is also adjusted through multiplication, to correct a measurement issue [(learn more)](https://circuitjournal.com/50kg-load-cells-with-HX711).

#### Arduino Board
The project is based on the Heltec WiFi Kit 8. It is based on the ESP8266 microcontroller and uses up to 6V input. It has an onboard screen and WiFi a antenna [(learn more)](https://heltec.org/project/wifi-kit-32/).

#### Wiring
A diagram for the wiring is available [here](images/Box Sizing Tool Diagram.jpg).


## Code
The code sequence is written in C++, but based on Arduino. It therefore uses Arduino libraries and needs an Arduino IDE installation. This version is written on VSCode and uses PlatformIO to manage it.

### Dependencies
Libraries: HX711, SPI, Wire, Adafruit_GFX, Adafruit_SSD1306 and AdafruitBusIO.

### Code sequence
- Multiple #define are used to define logo layouts, pin layouts for the US sensors, the load cell (scale) pins and screen address.
- The US sensor functions are also defined. These follow this sequence: turn off (to start from 0), turn on for 10 milliseconds, turn off, read duration, convert to distance, calculate package size, return size.
- The print and display function gets defined. It takes all the read values and prints them to the serial connection and onboard display respectively.
- setup(): runs at the start after the arduino turns on. It only runs once. In this case the pins are defined, so the board knows what comes from where. Serial.begin(115200) starts the connection. Then the scale is initialized, and a connection is established (Note that the setup will fail if the scale isn’t connected). After that comes the display connection. If successful, it gets cleared, and then displays both logos one after the other. 
- loop(): this is where the main program runs. This function runs continuously. It reads the values from the US sensors and scale, then displays the box. It then waits (delay(100)) 0.1 seconds and runs again.


## Current status
The project hasn’t been finished due to a few problems that occur during operation:
- The program/board/display stops working after restarting a few times. Has to be connected to a PC and flashed again. 
- Not all US sensors return a value. Sensor Z (length) normally does, and sensor Y only works when it’s touched (ground connection was checked). Sensor X doesn’t return a value or it’s not being displayed for some reason. 
- Sometimes the scale doesn’t calibrate right, and it shows a wrong value, or fluctuates randomly.


### Next steps
Some work has to be done:
- Check if the setup() and sequence of the code is causing the display to crash or clog after a restart.
- Check if the loop() sequence has a bottleneck and slows/interrupts the sensor’s function.

## More info
Check out the wiring diagram and board pinout under 
