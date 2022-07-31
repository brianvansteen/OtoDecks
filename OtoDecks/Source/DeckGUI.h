/*
  ==============================================================================

    DeckGUI.h
    Created: 31 Jul 2022 1:02:42pm
    Author:  bvans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJaudio.h" // to know about this class

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component, public juce::Button::Listener, public juce::Slider::Listener

{
public:
    DeckGUI(DJAudio* player); // DeckGUI gets DJ audio player via the constructor, and use assignment list
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button*) override; // function to implement Button::Listener; called when button clicked

    void sliderValueChanged(juce::Slider* slider) override; // function to implement Slider::Listener

private:

    juce::TextButton playButton{ "Play Now!" };
    juce::TextButton stopButton{ "**** STOP ****" };
    juce::TextButton loadButton{ "LOAD AUDIO" };

    juce::Slider volSlider;
    juce::Label volLabel;
    juce::Slider speedSlider;
    juce::Label speedLabel;
    juce::Slider positionSlider;
    juce::Label positionLabel;

    juce::FileChooser fChooser{ "Select a file..." };

    DJAudio* player; // deck GUI is unaware of DJAudio player; when receive events from buttons, how to send events on to DJAudio player; so need reference with pointer

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
