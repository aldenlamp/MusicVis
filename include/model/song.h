//
// Created by alden lamp on 11/17/20.
//

#ifndef FINAL_PROJECT_SONG_H
#define FINAL_PROJECT_SONG_H

#include "Resources.h"
#include "cinder/gl/gl.h"
#include "cinder/audio/audio.h"
#include "cinder/app/App.h"


namespace musicvis_model{

using ci::audio::BufferPlayerNodeRef;
using ci::audio::MonitorSpectralNodeRef;
using ci::audio::MonitorSpectralNode;
using ci::audio::SourceFileRef;
using ci::audio::BufferRef;
using std::vector;


enum song_names { Amber };

class Song{

public:
  Song(song_names name, size_t fft_size = 2048, size_t windowSize = 256);

  void Play();

  void Stop();

  const vector<float>& GetFFTResult();

private:
  BufferPlayerNodeRef player_node_;
  MonitorSpectralNodeRef monitor_node_;

};


}


#endif //FINAL_PROJECT_SONG_H
