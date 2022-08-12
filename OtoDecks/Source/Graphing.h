/*
  ==============================================================================

    Graphing.h
    Created: 12 Aug 2022 11:33:18am
    Author:  bvans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Graphing  : public juce::Component
{
public:
    Graphing();
    ~Graphing() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Graphing)
};
