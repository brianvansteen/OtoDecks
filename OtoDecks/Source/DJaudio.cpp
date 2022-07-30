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
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    //transportSource.getNextAudioBlock(bufferToFill);
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudio::releaseResources() // pure virtual function
{
    // transportSource.releaseResources();
    resampleSource.releaseResources();
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
    if (gain < 0 || gain > 1.0)
    {

    }
    else
    {
        transportSource.setGain(gain);
    }
}

void DJAudio::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 10.0)
    {

    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudio::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudio::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {

    }
    else
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudio::start()
{
    transportSource.start();
}

void DJAudio::stop()
{
    transportSource.stop();
}