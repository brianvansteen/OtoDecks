/*
  ==============================================================================

    DJaudio.h definition file
    Created: 30 Jul 2022 9:26:41am
    Author:  bvans

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DJAudio : public juce::AudioSource // DJAudio is inheriting from AudioSource
{
public:

    DJAudio(juce::AudioFormatManager& _formatManager);
    ~DJAudio();
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override; // pure virtual function
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override; // pure virtual function
    void releaseResources() override; // pure virtual function 

    void loadURL(juce::URL audioURL); // load audio file
    void setGain(double gain); // set playback volume
    void setSpeed(double ratio); // set playback speed
    void setPosition(double posInSecs); // set playback position of the audio file
    void setPositionRelative(double pos); // set playback relative position of the audio file; i.e. 0 - 100% of any length audio file

    void start(); // start playback
    void stop(); // stop playback

    double getPositionRelative(); // get the relative position of the playhead; between 0 and 1

private:

    // AudioFormatManager: responsible for knowing about different audio formats (i.e. decompression, channels), and how to play the file, sends to AudioFormatReader interface
    juce::AudioFormatManager& formatManager; // first layer of onion to work with different audio file formats

    std::unique_ptr<juce::AudioFormatReaderSource> readerSource; // to create on the fly, to read a file once the file is identified; need a 'smart pointer'

    juce::AudioTransportSource transportSource; // to control playback of audio, adjust the volume; NOT speed

    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 }; // wrapper to transport source to control the speed
};