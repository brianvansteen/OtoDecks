#pragma once

#include <JuceHeader.h>
#include "DJaudio.h"
#include "DeckGUI.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

// main component inherits from audioAppComponent; built-on component, inherits from component class (GUI) and audio class

class MainComponent : public juce::AudioAppComponent,
                        public juce::Button::Listener,
                        public juce::Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //============================================================================== from audio source class

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override; // pure virtual function
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override; // pure virtual function

    //============================================================================== from component class

    void paint(juce::Graphics& g) override; // not pure virtual function; do not need to provide implementation
    void resized() override; // not pure virtual function; do not need to provide implementation

    void buttonClicked(juce::Button*) override; // function to implement Button::Listener; called when button clicked

    void sliderValueChanged(juce::Slider* slider) override; // function to implement Slider::Listener

private:
    //==============================================================================
    // Your private member variables go here...

    //juce::TextButton playButton{ "Play Now!" };
    //juce::TextButton stopButton{ "**** STOP ****" };
    //juce::TextButton loadButton{"LOAD AUDIO" };

    //juce::Slider volSlider;
    //juce::Label volLabel;
    //juce::Slider speedSlider;
    //juce::Label speedLabel;
    //juce::Slider positionSlider;
    //juce::Label positionLabel;

    // juce::Random rand;

    //double phase;
    //double dphase;

    // AudioFormatManager: responsible for knowing about different audio formats (i.e. decompression, channels), and how to play the file, sends to AudioFormatReader interface
    //juce::AudioFormatManager formatManager; // first layer of onion to work with different audio file formats

    //// AudioFormatReader object, base-level file reader; generic reader
    //
    //std::unique_ptr<juce::AudioFormatReaderSource> readerSource; // to create on the fly, to read a file once the file is identified; need a 'smart pointer'
    //
    //juce::AudioTransportSource transportSource; // to control playback of audio, adjust the volume; NOT speed
    //
    //juce::ResamplingAudioSource resampleSource{&transportSource, false, 2 }; // wrapper to transport source to control the speed

    // void loadURL(juce::URL audioURL);
    juce::FileChooser fChooser{ "Select a file..." };

    DJAudio player1; // set player1 object of DJAudio class
    DeckGUI deckGUI1;
    DeckGUI deckGUI2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
