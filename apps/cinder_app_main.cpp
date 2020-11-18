//
// Created by alden lamp on 11/17/20.
//

//#include "cinder_app_main.h"
#include <controller/musicvis_controller.h>

using visualizer::MusicVisController;

void prepareSettings(MusicVisController::Settings *settings){
  settings->setResizable(false);
}

CINDER_APP(MusicVisController, ci::app::RendererGl, prepareSettings);