/*
  ==============================================================================

    WaveformDisplay.h
    Created: 1 Aug 2022 12:33:56pm
    Author:  bvans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component
{
public:
    WaveformDisplay();
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
