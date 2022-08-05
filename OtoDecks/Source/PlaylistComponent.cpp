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
    trackTitles.push_back("Dazed and Confused");
    trackTitles.push_back("Out on the Tiles");
    trackTitles.push_back("Wearing and Tearing");
    trackTitles.push_back("Boogie with Stu");

    tableComponent.getHeader().addColumn("Title", 1, 180);
    tableComponent.getHeader().addColumn("Artist", 2, 140);
    tableComponent.getHeader().addColumn("", 3, 80);
    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent()
{
    tableComponent.setModel(nullptr);
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

void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::orange);
    }
    else
    {
        g.fillAll(juce::Colours::darkolivegreen);
    }
}

void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (rowNumber < getNumRows())
    {
        g.drawText(trackTitles[rowNumber], 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
}

PlaylistComponent::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, PlaylistComponent::Component *existingComponentToUpdate)
{
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{ "*** Play ***" };

            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);

            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());

    DBG("Button clicked!" << button->getComponentID());
    DBG(trackTitles[id]);
}
