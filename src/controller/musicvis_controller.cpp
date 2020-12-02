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

  auto ctx = ci::audio::Context::master();

  // create a SourceFile and set its output samplerate to match the Context.
  ci::audio::SourceFileRef sourceFile = ci::audio::load(loadResource(FLUME_AMBER), ctx->getSampleRate());

  // load the entire sound file into a BufferRef, and construct a BufferPlayerNode with this.

  ci::audio::BufferRef buffer = sourceFile->loadBuffer();

  auto node = ci::audio::BufferPlayerNode(buffer);
  mBufferPlayerNode = ctx->makeNode(node);

  std::cout << "Frames per Block: " << mBufferPlayerNode->getFramesPerBlock() << std::endl;
  std::cout << "Num Frames: " << mBufferPlayerNode->getNumFrames() << std::endl;
  std::cout << "Sample Rate: " << mBufferPlayerNode->getSampleRate() << std::endl;
  std::cout << "Num Channels: " << mBufferPlayerNode->getNumChannels() << std::endl;
  std::cout << "Buffer Size: " << mBufferPlayerNode->getBuffer()->getSize() << std::endl;
//  auto channel = mBufferPlayerNode->getBuffer()->getChannel(0);
//  std::cout << channel.size() << std::endl;


  // connect and enable the Context
  mBufferPlayerNode >> ctx->getOutput();
  ctx->enable();

  mBufferPlayerNode->start();


//  ref = ci::audio::Voice::create(ci::audio::load(ci::app::loadResource(FLUME_AMBER)));
//  ci::audio::VoiceRef ref = ci::audio::Voice::create(ci::audio::load(ci::app::loadResource(FLUME_AMBER)));
//  ref->start();
//  ref->setVolume(1);
//  ref->start();

}

void MusicVisController::draw() {
  auto channel = mBufferPlayerNode->getBuffer()->getChannel(1);
  std::cout << "Pos: " << mBufferPlayerNode->getReadPosition();
  std::cout << "\tBufferVal: " << mBufferPlayerNode->getBuffer()->getData()[mBufferPlayerNode->getReadPosition()];
  std::cout << "\tChannelVal: " << channel[mBufferPlayerNode->getReadPosition()] << std::endl;

}

void MusicVisController::mouseDown(ci::app::MouseEvent event) {

//  ref->setVolume(1);
//  ref->start();
}

}