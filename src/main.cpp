/**

                                            ▒▒██░░                                              ██████████
                                      ██▒▒        ▒▒██                                    ░░  ██░░░░░░░░░░██
                                    ██                    ░░                                ██░░░░░░░░░░░░░░██
                                    ██                    ░░                                ██░░░░░░░░████░░██████████
                                  ▒▒                  ██      ░░██              ██          ██░░░░░░░░████░░██▒▒▒▒▒▒██
                          ▒▒    ██        ██                                  ██░░██        ██░░░░░░░░░░░░░░██▒▒▒▒▒▒██
                                  ██        ██                    ░░          ██░░░░██      ██░░░░░░░░░░░░░░████████
                      ░░▓▓▒▒      ▒▒    ██                                  ██░░░░░░░░██      ██░░░░░░░░░░░░██
                                    ▒▒                                      ██░░░░░░░░████████████░░░░░░░░██
                    ██        ▒▒██░░░░██    ██              ▓▓░░      ░░▒▒  ██░░░░░░░░██░░░░░░░░░░░░░░░░░░░░██
                    ▒▒  ████      ▒▒    ████                              ▒▒██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██
                      ██                ██                                ████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██
                                        ░░                                  ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██
                    ██      ▒▒    ▒▒  ██                                    ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██
      ▒▒          ▒▒      ░░██████  ░░██                                  ████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██
  ░░░░░░░░  ░░      ▒▒░░░░▒▒          ██                                ░░  ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██
  ░░░░░░              ░░░░▒▒          ▒▒                              ▒▒      ██░░░░░░░░░░░░░░░░░░░░░░░░░░██
              ░░    ░░    ░░░░          ░░                              ▒▒      ██████░░░░░░░░░░░░░░░░████
    ░░        ░░    ▒▒          ██▒▒    ██                                            ████████████████

  Turbo duck.

*/







































#include <Arduino.h>
#include <XT_DAC_Audio.h>
#include <Adafruit_NeoPixel.h>
#include "config/pins.h"
#include "assets/default_sound.h"

Adafruit_NeoPixel eyes(2, PIN_EYES, NEO_GRB + NEO_KHZ800);
XT_Wav_Class Sound(default_sound);
XT_DAC_Audio_Class DacAudio(PIN_SPEAKER, 0);
bool musicPlayed = false;

void setup()
{
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  eyes.begin();
  eyes.setBrightness(100);
}

void loop()
{
  if (!musicPlayed)
  {
    DacAudio.FillBuffer();

    if (Sound.Playing)
    {
      eyes.rainbow((millis() / 6 % 1280) * 256);
    }
    else
    {
      musicPlayed = true;
      eyes.clear();
    }

    eyes.show();
  }
  else
  {
    delay(100);
  }

  if (digitalRead(PIN_BUTTON) == LOW)
  {
    musicPlayed = false;
    DacAudio.Play(&Sound);
  }
}
