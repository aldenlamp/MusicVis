//
// Created by alden lamp on 11/17/20.
//

#ifndef FINAL_PROJECT_MUSICVIS_CONTROLLER_H
#define FINAL_PROJECT_MUSICVIS_CONTROLLER_H

#include "cinder/app/App.h"
#include "cinder/app/RendererGL.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/audio/audio.h"


namespace visualizer { 

using ci::audio::VoiceRef;
using ci::audio::SourceFileRef;

class MusicVisController : public ::ci::app::App{

public:
  void setup() override;

  void draw() override;

  void mouseDown(ci::app::MouseEvent event) override;

  ci::audio::VoiceRef ref;

};

}


#endif //FINAL_PROJECT_MUSICVIS_CONTROLLER_H
