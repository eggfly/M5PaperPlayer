#include <Arduino.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorMOD.h"
#include "AudioOutputI2S.h"

// enigma.mod sample from the mod archive: https://modarchive.org/index.php?request=view_by_moduleid&query=42146
#include "enigma.h"
#include "super_mario_mod.h"

AudioGeneratorMOD *mod;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;


//#define I2S_BCK_PIN 27
//#define I2S_LRCK_PIN 26
//#define I2S_DATA_PIN 25

#define I2S_BCK_PIN  19
#define I2S_LRCK_PIN 32
#define I2S_DATA_PIN 18


void setup()
{
  // WiFi.mode(WIFI_OFF); //WiFi.forceSleepBegin();
  Serial.begin(115200);
  delay(500);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  audioLogger = &Serial;
  // super_mario_bros or enigma_mod
  // file = new AudioFileSourcePROGMEM(nighthawk___super_mario_bros, sizeof(nighthawk___super_mario_bros));
  // file = new AudioFileSourcePROGMEM(enigma_mod, sizeof(enigma_mod));
  file = new AudioFileSourcePROGMEM(super_mario_bros, sizeof(super_mario_bros));
  // out = new AudioOutputI2S(0, 1); // Uncomment this line, comment the next one to use the internal DAC channel 1 (pin25) on ESP32
  out = new AudioOutputI2S();
  out->SetPinout(I2S_BCK_PIN, I2S_LRCK_PIN, I2S_DATA_PIN);
  out->SetGain(0.15);

  mod = new AudioGeneratorMOD();
  mod->SetBufferSize(3 * 1024);
  mod->SetSampleRate(44100);
  mod->SetStereoSeparation(32);
  mod->begin(file, out);
}

void loop()
{
  if (mod->isRunning()) {
    if (!mod->loop()) mod->stop();
  } else {
    Serial.printf("MOD done\n");
    delay(1000);
  }
}
