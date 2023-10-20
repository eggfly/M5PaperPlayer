
#include "Arduino.h"

#include "player.hpp"

singsang::CPlayer player;



void setup() {
  Serial.begin(115200);

  // audio.connecttoFS(SD, "20221125/Coldplay - Speed of Sound [n].flac");
  // audio.connecttoFS(SD, "super_mario.wav");
  // audio.connecttoFS(SD, "music/Vincent.wav");
  // audio.connecttoFS(SD, "super_mario.fake.mp3");
  player.begin();
  player.startNextSong();
}

void loop() {
  player.loop();
  if (Serial.available()) { // in serial monitor
    String r = Serial.readString();
    log_i("free heap=%i", ESP.getFreeHeap());
  }
}

// optional
void audio_info(const char *info) {
  Serial.print("info        ");
  Serial.println(info);
  if (strstr(info, "AAC HeaderFormat: RAW") != nullptr) {
    Serial.println("RAW AAC: startNextSong()");
    player.startNextSong();
  }
}

void audio_id3data(const char *info) { //id3 metadata
  Serial.print("id3data     "); Serial.println(info);
}
void audio_eof_mp3(const char *info) { //end of file
  Serial.print("eof_mp3     "); Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     "); Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle "); Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     "); Serial.println(info);
}
void audio_commercial(const char *info) { //duration in sec
  Serial.print("commercial  "); Serial.println(info);
}
void audio_icyurl(const char *info) { //homepage
  Serial.print("icyurl      "); Serial.println(info);
}
void audio_lasthost(const char *info) { //stream URL played
  Serial.print("lasthost    "); Serial.println(info);
}
