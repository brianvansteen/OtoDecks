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
    formatManager.registerBasicFormats();
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}

void DJAudio::releaseResources() // pure virtual function
{
    transportSource.releaseResources();
}

void DJAudio::loadURL(juce::URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false)); // unpack audio URL and converted to input stream, and creates a reader
    if (reader != nullptr) // file is accessible
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true)); // create audio format reader source, when file is read
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate); // control playback of audio
        readerSource.reset(newSource.release()); // transfer ownership to class variable

    }
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
    transportSource.start();
}

void DJAudio::stop()
{
    transportSource.stop();
}