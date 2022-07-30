/*
  ==============================================================================

    DJaudio.h
    Created: 30 Jul 2022 9:26:41am
    Author:  bvans

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DJAudio : public juce::AudioSource
{
public:

    DJAudio();
    ~DJAudio();
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override; // pure virtual function
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override; // pure virtual function

    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);

    void start();
    void stop();
};