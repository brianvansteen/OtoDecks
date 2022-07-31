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
    formatManager.registerBasicFormats(); // ensures audio system knows about the basic audio formats
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) // pure virtual function
{
    //transportSource.getNextAudioBlock(bufferToFill);
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudio::releaseResources() // pure virtual function
{
    // transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudio::loadURL(juce::URL audioURL) // select audio file to play
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

void DJAudio::setPositionRelative(double pos) // between 0 and 1; i.e. 0 - 100% of any length audio file
{
    if (pos < 0 || pos > 1.0)
    {

    }
    else
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos; // pos of 0 - 1 applied to length of audio file in seconds
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