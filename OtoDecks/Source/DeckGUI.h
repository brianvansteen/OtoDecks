/*
  ==============================================================================

    DeckGUI.h
    Created: 31 Jul 2022 1:02:42pm
    Author:  bvans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component
{
public:
    DeckGUI();
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
