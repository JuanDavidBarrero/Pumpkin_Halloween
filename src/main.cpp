#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#define PIN 12

#define NUMPIXELS 3

const int motionSensor = 27;

bool state = false;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void ColorPumpking(int, int, int, int);

void IRAM_ATTR detectsMovement()
{
  state = true;
}

void setup()
{
  Serial.begin(115200);
  pixels.begin();
  pixels.setBrightness(20);
  ColorPumpking(50, 0, 0, 0);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
}

void loop()
{
  if (state)
  {
    Serial.println("Movimiento detectado");
    ColorPumpking(5, 255, 50, 0);
    delay(300);
    ColorPumpking(5, 200, 0, 0);
    delay(300);
    ColorPumpking(5, 0, 215, 0);
    delay(300);
    state = false;
  }
  ColorPumpking(50, 0, 0, 0);
}

void ColorPumpking(int times, int red, int green, int blue)
{
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));

    pixels.show();

    delay(times);
  }
}
