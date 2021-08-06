 
// ---------------------------------- IMPORTS

#include <Arduino.h>
#include <HX711.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// ---------------------------------- neomesh +  CLAC LOGO

const uint8_t neomeshLogo [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00,
0xF3, 0xF0, 0x0F, 0xE0, 0x1F, 0xC0, 0x79, 0xF8, 0xF8, 0x03, 0xF0, 0x0F, 0xE1, 0xFB, 0xF0, 0x00,
0xFF, 0xF8, 0x1F, 0xF0, 0x3F, 0xF0, 0x7F, 0xFD, 0xFC, 0x0F, 0xFC, 0x1F, 0xF9, 0xFF, 0xF8, 0x00,
0xFF, 0xF8, 0x3F, 0xF8, 0x7F, 0xF8, 0x7F, 0xFF, 0xFE, 0x1F, 0xFC, 0x3F, 0xF9, 0xFF, 0xF8, 0x00,
0xFF, 0xF8, 0x7F, 0xF8, 0xFF, 0xF8, 0x7F, 0xFF, 0xFE, 0x1F, 0xFE, 0x3F, 0xF1, 0xFF, 0xFC, 0x00,
0xFC, 0xF8, 0xFC, 0x78, 0xFC, 0xFC, 0x7E, 0x7F, 0x3E, 0x3F, 0x1E, 0x3E, 0x21, 0xFC, 0xFC, 0x00,
0xF8, 0xFC, 0xF8, 0x7C, 0xF8, 0x7C, 0x7C, 0x7E, 0x3F, 0x3E, 0x1F, 0x3F, 0x01, 0xF8, 0xFC, 0x00,
0xF8, 0xFC, 0xFF, 0xFD, 0xF8, 0x7C, 0x7C, 0x7E, 0x3F, 0x3F, 0xFF, 0x3F, 0xE1, 0xF8, 0x7C, 0x00,
0xF8, 0xFC, 0xFF, 0xFD, 0xF8, 0x7C, 0x7C, 0x7E, 0x3F, 0x3F, 0xFF, 0x1F, 0xF1, 0xF8, 0x7C, 0x00,
0xF8, 0xFC, 0xFF, 0xFD, 0xF8, 0x7C, 0x7C, 0x7E, 0x3F, 0x3F, 0xFF, 0x0F, 0xF9, 0xF8, 0xFC, 0x00,
0xF8, 0xFC, 0xF8, 0x00, 0xF8, 0x7C, 0x7C, 0x7E, 0x3F, 0x3E, 0x00, 0x03, 0xF9, 0xF8, 0xFC, 0x18,
0xF8, 0xFC, 0xFC, 0x00, 0xFC, 0xFC, 0x7C, 0x7E, 0x3F, 0x3F, 0x00, 0x10, 0xF9, 0xF8, 0xFC, 0x7E,
0xF8, 0xFC, 0x7F, 0xF0, 0xFF, 0xFC, 0x7C, 0x7E, 0x3F, 0x1F, 0xFC, 0x3C, 0xF9, 0xF8, 0xFC, 0x7E,
0xF8, 0xFC, 0x7F, 0xF8, 0x7F, 0xF8, 0x7C, 0x7E, 0x3F, 0x1F, 0xFE, 0x7F, 0xF9, 0xF8, 0xFC, 0x7E,
0xF8, 0xFC, 0x3F, 0xF8, 0x3F, 0xF0, 0x7C, 0x7E, 0x3F, 0x0F, 0xFE, 0x7F, 0xF1, 0xF8, 0xFC, 0x7E,
0xF8, 0xFC, 0x0F, 0xF0, 0x1F, 0xE0, 0x7C, 0x7E, 0x3F, 0x03, 0xFC, 0x1F, 0xE1, 0xF8, 0x7C, 0x3C,
0x00, 0x00, 0x03, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x00, 0x18,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t clacLogo [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x67, 0x8E, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x27, 0x04, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF1, 0x06, 0x20, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x86, 0x71, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x86, 0x71, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x06, 0x00, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x20, 0x72, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// ---------------------------------- SCREEN CONNECTION PINS

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

#define OLED_RESET     16 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------------------------- US CONNECTION PINS
// Explanation: typeOfPin = PortPin(GPIO), PIN pinName (#esp8266 pin number) on Heltec Board -- CABLE COLOR

const int trigPinX = 14; //PIN SDA (#06) on Heltec Board -- RED
const int echoPinX = 2; //PIN SCL (#14 ) on Heltec Board -- BROWN

const int trigPinY = 0; //PIN D3 (#15) on Heltec Board -- GREEN
const int echoPinY = 15; //PIN D8 (#13) on Heltec Board -- YELLOW

const int trigPinZ = 13; //PIN D7 (#12) on Heltec Board -- WHITE
const int echoPinZ = 12; //PIN D6 (#10) on Heltec Board -- GREY

// ---------------------------------- SCALE CONNECTION PINS

HX711 scale;

uint8_t dataPin = 1; //PIN TX (#26) on Heltec Board  1 -- GREY
uint8_t clockPin = 3; //PIN RX (#25) on Heltec Board  3 -- WHITE

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

const float distToAxisX = 39;
const float distToAxisY = 36;
const float distToAxisZ = 56;

volatile float weight;
int x, y, z;

// ---------------------------------- CUSTOM FUNCS

int readX(float dist)
{
  delay(150);
  digitalWrite(trigPinX, LOW); //clears the trigPin
  delayMicroseconds(2);

  digitalWrite(trigPinX, HIGH); //activates the US for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPinX, LOW);

  durationX = pulseIn(echoPinX, HIGH); //reads echo, return travel time in microseconds
  distanceX = durationX * 0.034 / 2; //convert time to distance
  sizeX = dist - distanceX; //convert travelled distance to package size
  if (sizeX < -5) { //return 0 when sensor is empty
    return 0;
  }
  return sizeX;
}

int readY(float dist)
{
  delay(150);
  digitalWrite(trigPinY, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinY, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinY, LOW);

  durationY = pulseIn(echoPinY, HIGH);
  distanceY = durationY * 0.034 / 2;
  sizeY = dist - distanceY;
  if (sizeY < -5) {
    return 0;
  }
  return sizeY;
}

int readZ(float dist)
{
  delay(150);
  digitalWrite(trigPinZ, LOW);
  delayMicroseconds(2);
 
  digitalWrite(trigPinZ, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinZ, LOW);

  durationZ = pulseIn(echoPinZ, HIGH);
  distanceZ = durationZ * 0.034 / 2;
  sizeZ = dist - distanceZ;
  if (sizeZ < -5) {
    return 0;
  }
  return sizeZ;
}

void printBox(int x = 0, int y = 0, int z = 0, float weight = 0)
{
  Serial.print("HÖHE: ");
  Serial.println(y);
  Serial.print("LÄNGE: ");
  Serial.println(z);
  Serial.print("BREITE: ");
  Serial.println(x);
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
  display.printf("L: %d ", z);
  display.println("cm");
  display.printf("B: %d ", x);
  display.println("cm");
  display.print("Gewicht: ");
  if (weight < 0.0) {
    weight = 0.0;
  }
  display.print(weight, 2);
  display.print("kg");

  display.display();
}

// ---------------------------------- SETUP

void setup()
{
  // ---------------------------------- PIN SETUP

  pinMode(1, FUNCTION_3);
  pinMode(3, FUNCTION_3);
  pinMode(trigPinX, OUTPUT); 
  pinMode(trigPinY, OUTPUT); 
  pinMode(trigPinZ, OUTPUT); 
  pinMode(echoPinX, INPUT);
  pinMode(echoPinY, INPUT);
  pinMode(echoPinZ, INPUT);

  Serial.begin(115200);

  // ---------------------------------- SCALE SETUP
  
  scale.begin(dataPin, clockPin);
  scale.set_scale(19150); // loadcell factor 200kg = 19150
  scale.tare(); // reset the scale to zero


  // ---------------------------------- DISPLAY SETUP
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // SSD1306_SWITCHCAPVCC = generate display voltage from 5V internally
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay(); // Clear the buffer

  // Show the display buffer on the screen. You MUST call display() after
  //  drawing commands to make them visible on screen!

  // ---------------------------------- Display Logos
  display.drawBitmap(0, 0, neomeshLogo, 128, 32, 1);
  display.display();
  delay(1500);
  display.clearDisplay();
  display.drawBitmap(0, 0, clacLogo, 128, 32, 1);
  display.display();
  delay(1500);

  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display().
} 

// ---------------------------------- LOOP
void loop()
{
  // read box size
  x = readX(distToAxisX);
  y = readY(distToAxisY);
  z = readZ(distToAxisZ);
  weight = (scale.get_units(5)) * 0.756; //offset the weigh error of +24.4%
  // printBox(x, y, z, weight);
  displayBox(x, y, z, weight);
  delay(100); //delay 0.1s, for good measure ;)
}