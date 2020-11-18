//
// Created by alden lamp on 11/17/20.
//

#include <controller/musicvis_controller.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGL.h"
#include "cinder/gl/gl.h"

#include "cinder/audio/Voice.h"
#include "cinder/audio/Source.h"

#include "Resources.h"

namespace visualizer {

void MusicVisController::setup() {
  ref = ci::audio::Voice::create(ci::audio::load(ci::app::loadResource(FLUME_AMBER)));
//  ci::audio::VoiceRef ref = ci::audio::Voice::create(ci::audio::load(ci::app::loadResource(FLUME_AMBER)));
//  ref->start();
//  ref->setVolume(1);
  ref->start();

}

void MusicVisController::draw() {

}

void MusicVisController::mouseDown(ci::app::MouseEvent event) {

//  ref->setVolume(1);
//  ref->start();
}

}