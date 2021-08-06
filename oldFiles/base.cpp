
// ---------------------------------- IMPORTS
#include <Arduino.h>
#include <HX711.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PCF8574.h>

// ---------------------------------- SCREEN CONNECTION PINS

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

#define OLED_RESET     16 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// TO DO
// - Change pin numbers
// - add connection to IO Extender
// - 

// ---------------------------------- US CONNECTION PINS
const int trigPinX = P0; //PIN 0 on Extender
const int echoPinX = P1; //PIN 1 on Extender

const int trigPinY = P2; //PIN 2 on Extender
const int echoPinY = P3; //PIN 3 on Extender

const int trigPinZ = P4; //PIN 4 on Extender
const int echoPinZ = P5; //PIN 5 on Extender

// ---------------------------------- SCALE CONNECTION PINS
HX711 scale;

uint8_t dataPin = 23;
uint8_t clockPin = 24;

uint32_t start, stop;

// ---------------------------------- VARIABLES
long durationX;
long durationY;
long durationZ;

float distanceX;
float distanceY;
float distanceZ;

int sizeX;
int sizeY;
int sizeZ;

const float distToAxisX = 35;
const float distToAxisY = 35;
const float distToAxisZ = 35;

volatile float weight;
int x, y, z;

// ---------------------------------- CUSTOM FUNCS
void measure(uint8_t cnt)
{
  Serial.print("  RAW: ");
  Serial.println(scale.read());
  Serial.print("  AVG: ");
  Serial.println(scale.read_average(cnt));
  Serial.print("VALUE: ");
  Serial.println(scale.get_value(cnt));
  Serial.print("UNITS: ");
  Serial.println(scale.get_units(cnt), 1);
}

int readX(float dist)
{
  digitalWrite(trigPinX, LOW); //clears the trigPin
  delayMicroseconds(2);

  digitalWrite(trigPinX, HIGH); //activates the US for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPinX, LOW);

  durationX = pulseIn(echoPinX, HIGH); //reads echo, return travel time in microseconds
  distanceX = durationX * 0.034 / 2;
  sizeX = dist - distanceX;
  return sizeX;
}

int readY(float dist)
{
  digitalWrite(trigPinY, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinY, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinY, LOW);

  durationY = pulseIn(echoPinY, HIGH);
  distanceY = durationY * 0.034 / 2;
  sizeY = dist - distanceY;
  return sizeY;
}

int readZ(float dist)
{
  digitalWrite(trigPinZ, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinZ, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinZ, LOW);

  durationZ = pulseIn(echoPinZ, HIGH);
  distanceZ = durationZ * 0.034 / 2;
  sizeZ = dist - distanceZ;
  return sizeZ;
}

void printBox(int x, int y, int z, float weight)
{
  Serial.print("HÖHE: ");
  Serial.println(y);
  Serial.print("LÄNGE: ");
  Serial.println(x);
  Serial.print("BREITE: ");
  Serial.println(z);
  Serial.print("KG: ");
  Serial.println(weight);
}

void displayBox(int x = 0, int y = 0, int z = 0, float weight = 0) 
{
  display.clearDisplay();
  display.setTextSize(1.5); // Draw X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.printf("H: %d ", y);
  display.println("cm");
  display.printf("L: %d ", x);
  display.println("cm");
  display.printf("B: %d ", z);
  display.println("cm");
  display.printf("Gewicht: %g ", weight);
  display.print("kg");

  display.display();      // Show text
  delay(100);
}

// ---------------------------------- SETUP
void setup()
{
  // ---------------------------------- US PINS SETUP
  pinMode(trigPinX, OUTPUT); 
  pinMode(trigPinY, OUTPUT); 
  pinMode(trigPinZ, OUTPUT); 
  pinMode(echoPinX, INPUT);
  pinMode(echoPinY, INPUT);
  pinMode(echoPinZ, INPUT);

  Serial.begin(9600);

  // ---------------------------------- SCALE SETUP
  scale.begin(dataPin, clockPin);
  scale.set_scale(19150); // loadcell factor 50 KG = 19150
  scale.tare(); // reset the scale to zero
  measure(10);

  // ---------------------------------- DISPLAY SETUP
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!

  display.display();
  delay(1000);

  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display().
}

// ---------------------------------- LOOP
void loop()
{
  // read box size
  // x = readX(distToAxisX);
  // y = readY(distToAxisY);
  // z = readZ(distToAxisZ);
  // weight = scale.get_units(5);

  printBox(0, 0, 0, 0);
  displayBox(0, 0, 0, 0);
  delay(1500);
}

