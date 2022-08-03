/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 3 Aug 2022 12:10:21pm
    Author:  bvans

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and initialise any special settings that your component needs.

    trackTitles.push_back("Black Dog");
    trackTitles.push_back("Lemon Song");

    tableComponent.getHeader().addColumn("Title", 1, 200);
    tableComponent.getHeader().addColumn("Artist", 2, 200);
    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and draws some placeholder text to get you started.

       You should replace everything in this method with your own drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child components that your component contains..

    tableComponent.setBounds(5, 5, getWidth() - 5, getHeight());
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected)
{

}

void PlaylistComponent::paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{

}
