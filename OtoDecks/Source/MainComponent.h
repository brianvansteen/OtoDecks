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

class MainComponent : public juce::AudioAppComponent
                        //public juce::Button::Listener,
                        //public juce::Slider::Listener
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

    //void buttonClicked(juce::Button*) override; // function to implement Button::Listener; called when button clicked

    //void sliderValueChanged(juce::Slider* slider) override; // function to implement Slider::Listener

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
    DJAudio player2; // set player2 object of DJAudio class
    DeckGUI deckGUI1{&player1, formatManager, thumbCache}; // DeckGUI with pointer to DJAudio player1, as well as AudioFormatManager and AudioThumbnailCache from below
    DeckGUI deckGUI2{&player2, formatManager, thumbCache}; // DeckGUI with pointer to DJAudio player2, as well as AudioFormatManager and AudioThumbnailCache from below

    // got first layer, got the data in main component, DeckGUI ready to receive the data, and made the connection between the two

    juce::MixerAudioSource mixerSource;

    // setting up these in main component, since it can see, access and pass data to both decks; deckGUIs cannot see each other
    // get data from main component and pass through each layer, until it lands on audio thumbnail
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{100}; // cache 100 files

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
