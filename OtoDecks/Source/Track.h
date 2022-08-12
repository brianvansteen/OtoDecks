/*
  ==============================================================================

    Track.h
    Created: 9 Aug 2022 12:17:36pm
    Author:  bvans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Track  : public juce::Component
{
public:
    Track();
    ~Track() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Track)
};
