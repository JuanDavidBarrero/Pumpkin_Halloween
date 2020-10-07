#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#define PIN 12

#define NUMPIXELS 3

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void ColorPumpking(int, int, int, int);

void setup()
{
  pixels.begin();
  pixels.setBrightness(20);
}

void loop()
{
  ColorPumpking(5, 255, 50, 0);
}
void ColorPumpking(int times, int red, int green, int blue)
{
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));

    pixels.show();

    delay(5);
  }
}
