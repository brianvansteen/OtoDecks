/*
  ==============================================================================

    DeckGUI.cpp
    Created: 31 Jul 2022 1:02:42pm
    Author:  bvans

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudio* _player) : player(_player) // pass _player variable into player object; so DeckGUI has access to player
{
    // In your constructor, you should add any child components, and initialise any special settings that your component needs.

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);

    playButton.addListener(this); // register with button to receive click events; 'this' is pointer to itself; inherited from button listener
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this); // thing that wants to receive the events needs to tell the GUI object that is wants to register for events
    volSlider.setRange(0.0, 1.0);
    addAndMakeVisible(volLabel);
    volLabel.setText("Volume", juce::dontSendNotification);
    volLabel.attachToComponent(&volSlider, true);

    speedSlider.addListener(this); // thing that wants to receive the events needs to tell the GUI object that is wants to register for events
    speedSlider.setRange(0.0, 2.0);
    addAndMakeVisible(speedLabel);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, true);

    positionSlider.addListener(this); // thing that wants to receive the events needs to tell the GUI object that is wants to register for events
    positionSlider.setRange(0.0, 1.0);
    addAndMakeVisible(positionLabel);
    positionLabel.setText("Position", juce::dontSendNotification);
    positionLabel.attachToComponent(&positionSlider, true);
}

DeckGUI::~DeckGUI()
{
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(juce::Colour{ 62, 95, 138 });

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::navajowhite);
    g.setFont (30.0f);
    g.drawText ("DJ Audio", getLocalBounds(),juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child components that your component contains..

    double rowHeight = getHeight() / 10;
    double width = (getWidth() - 20) / 2;
    auto sliderLeft = 80;

    playButton.setBounds(10, 10, width, rowHeight);
    stopButton.setBounds(10, 20 + (rowHeight), width, rowHeight);

    volSlider.setBounds(sliderLeft, 30 + (rowHeight * 2), width - sliderLeft - 10, rowHeight);
    speedSlider.setBounds(sliderLeft, 30 + (rowHeight * 3), width - sliderLeft - 10, rowHeight);
    positionSlider.setBounds(sliderLeft, 30 + (rowHeight * 4), width - sliderLeft - 10, rowHeight);

    loadButton.setBounds(10, getHeight() - 80, width, rowHeight);

}

void DeckGUI::buttonClicked(juce::Button* button) // pointer to button; memory address
{
    if (button == &playButton) // button to start audio file play
    {
        // std::cout << "Play button has been clicked!" << std::endl;
        DBG("Play button has been clicked!");
        juce::Logger::outputDebugString("Play button!");
        // transportSource.setPosition(0);
        // transportSource.start();
        player->setPosition(0);
        player->start();

    }
    else if (button == &stopButton) // button to stop audio file play
    {
        // std::cout << "Stop button has been clicked!" << std::endl;
        DBG("Stop button has been clicked!");
        juce::Logger::outputDebugString("Stop button!");
        // transportSource.stop();
        player->stop();

    }
    else if (button == &loadButton) // button to load new audio file
    {
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
                juce::File chosenFile = chooser.getResult();
                player->loadURL(juce::URL{ chosenFile });
            });
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        DBG("Volume slider moved: " << slider->getValue());
        // transportSource.setGain(slider->getValue());
        // dphase = volSlider.getValue() * 0.001;
        // juce::Logger::outputDebugString(slider->getValue());
        player->setGain(slider->getValue());
    }
    else if (slider == &speedSlider)
    {
        DBG("Speed slider moved: " << slider->getValue());
        // resampleSource.setResamplingRatio(slider->getValue());
        player->setSpeed(slider->getValue());
    }
    else if (slider == &positionSlider)
    {
        DBG("Position slider: " << slider->getValue());
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int, int y)
{
    if (files.size() == 1)
    {
        player->loadURL(juce::URL{ juce::File{files[0]} });
    }
}