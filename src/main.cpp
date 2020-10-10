#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#define PIN 12

#define NUMPIXELS 15

const int motionSensor = 27;

bool state = false;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void ColorPumpking(int);

void IRAM_ATTR detectsMovement()
{
  state = true;
}

void setup()
{
  Serial.begin(115200);
  pixels.begin();
  pixels.setBrightness(20);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
}

void loop()
{

  if (state)
  {
    ColorPumpking(1);
    state = false;
  }
  pixels.clear();
}

void ColorPumpking(int times)
{
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(random(0, 255), random(0, 25), random(0, 10)));

    delay(times);
  }
  pixels.show();
}

