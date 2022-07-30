/*
  ==============================================================================

    DJaudio.cpp
    Created: 30 Jul 2022 9:26:41am
    Author:  bvans

  ==============================================================================
*/

#include "DJaudio.h"



DJAudio::DJAudio()
{

}

DJAudio::~DJAudio()
{

}

void DJAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate) // pure virtual function
{

}

void DJAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{

}

void DJAudio::releaseResources() // pure virtual function
{

}

void DJAudio::loadURL(juce::URL audioURL)
{

}

void DJAudio::setGain(double gain)
{

}

void DJAudio::setSpeed(double ratio)
{

}

void DJAudio::setPosition(double posInSecs)
{

}

void DJAudio::start()
{

}

void DJAudio::stop()
{

}