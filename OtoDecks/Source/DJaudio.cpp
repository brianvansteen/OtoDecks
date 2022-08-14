/*
  ==============================================================================

    DJaudio.cpp
    Created: 30 Jul 2022 9:26:41am
    Author:  bvans

  ==============================================================================
*/

#include "DJaudio.h"


DJAudio::DJAudio(juce::AudioFormatManager& _formatManager) : formatManager(_formatManager)
{
    reverbParameters.roomSize = 0.0f; // default setting for reverb; range of 0 - 1, where 1 is big
    reverbParameters.damping = 0.0f; // default setting for reverb; range of 0 - 1, where 1 is full damped
    reverbParameters.wetLevel = 0.0f; // default setting for reverb; range of 0 - 1
    reverbParameters.dryLevel = 1.0f; // default setting for reverb; range of 0 - 1
    reverbSource.setParameters(reverbParameters);
}

DJAudio::~DJAudio()
{

}

void DJAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate) // pure virtual function
{
    // registerBasicFormats now done in MainComponent.cpp
    // formatManager.registerBasicFormats(); // ensures audio system knows about the basic audio formats
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
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
    reverbSource.releaseResources();
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

void DJAudio::start()
{
    transportSource.start();
}

void DJAudio::stop()
{
    transportSource.stop();
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

double DJAudio::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

double DJAudio::getLengthInSeconds()
{
    return transportSource.getLengthInSeconds();
}

void DJAudio::setRoomSize(float size)
{
    DBG("setRoomSize called");
    if (size < 0 || size > 1.0)
    {
        DBG("DJAudioPlayer::setRoomSize size should be between 0 and 1.0");
    }
    else {
        reverbParameters.roomSize = size;
        reverbSource.setParameters(reverbParameters);
    }
}

void DJAudio::setDamping(float dampingAmt)
{
    DBG("setDamping called");
    if (dampingAmt < 0 || dampingAmt > 1.0)
    {
        DBG("DJAudioPlayer::setDamping amount should be between 0 and 1.0");
    }
    else {
        reverbParameters.damping = dampingAmt;
        reverbSource.setParameters(reverbParameters);
    }
}

void DJAudio::setWetLevel(float wetLevel)
{
    DBG("setWetLevel called");
    if (wetLevel < 0 || wetLevel > 1.0)
    {
        DBG("setWetLevel level should be between 0 and 1.0");
    }
    else {
        reverbParameters.wetLevel = wetLevel;
        reverbSource.setParameters(reverbParameters);
    }
}

void DJAudio::setDryLevel(float dryLevel)
{
    DBG("setDryLevel called");
    if (dryLevel < 0 || dryLevel > 1.0)
    {
        DBG("setDryLevel level should be between 0 and 1.0");
    }
    else {
        reverbParameters.dryLevel = dryLevel;
        reverbSource.setParameters(reverbParameters);
    }
}