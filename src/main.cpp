#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"
#include <Adafruit_NeoPixel.h>

HardwareSerial mySoftwareSerial(1);
DFRobotDFPlayerMini myDFPlayer;

#define PIN 4

#define NUMPIXELS 15

const int motionSensor = 15;
const int smokemachine = 0;

bool state = false;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void ColorPumpkin(int);

void IRAM_ATTR detectsMovement()
{
  state = true;
}

void setup()
{
  mySoftwareSerial.begin(9600, SERIAL_8N1, 16, 17); // speed, type, RX, TX
  Serial.begin(115200);

  pinMode(smokemachine, OUTPUT);
  digitalWrite(smokemachine, 0);

  pixels.begin();
  pixels.setBrightness(100);
  pixels.clear();
  pixels.show();
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial))
  { //Use softwareSerial to communicate with mp3.

    Serial.println(myDFPlayer.readType(), HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }

  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  //----Set volume----
  myDFPlayer.volume(10); //Set volume value (0~30).
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}

void loop()
{

  if (state)
  {
    Serial.println("Moviemitno detectado");
    myDFPlayer.volume(25);
    myDFPlayer.play(3);
    digitalWrite(smokemachine, 1);
    delay(500);
    digitalWrite(smokemachine, 0);
    ColorPumpkin(1);
    digitalWrite(smokemachine, 1);
    delay(500);
    digitalWrite(smokemachine, 0);
    state = false;
  }
  else
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      delay(5);
    }
    pixels.show();
    digitalWrite(smokemachine, 0);
  }
}

void ColorPumpkin(int times)
{
  pixels.clear();

  for (size_t j = 0; j < 25; j++)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(random(100, 255), random(0, 25), random(0, 10)));

      delay(times);
    }
    pixels.show();
    delay(500);
  }
}
