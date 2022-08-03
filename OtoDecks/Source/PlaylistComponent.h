/*
  ==============================================================================

    PlaylistComponent.h
    Created: 3 Aug 2022 12:10:21pm
    Author:  bvans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <string>
#include <vector>

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component, public juce::TableListBoxModel
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;

    void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

private:
    
    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitles;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
