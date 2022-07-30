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

private:

    // AudioFormatManager: responsible for knowing about different audio formats (i.e. decompression, channels), and how to play the file, sends to AudioFormatReader interface
    juce::AudioFormatManager formatManager; // first layer of onion to work with different audio file formats

    std::unique_ptr<juce::AudioFormatReaderSource> readerSource; // to create on the fly, to read a file once the file is identified; need a 'smart pointer'

    juce::AudioTransportSource transportSource; // to control playback of audio, adjust the volume; NOT speed
};