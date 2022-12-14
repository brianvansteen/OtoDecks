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
DeckGUI::DeckGUI(DJAudio* _player, juce::AudioFormatManager& formatManagerToUse, juce::AudioThumbnailCache& cacheToUse) : player(_player), waveFormDisplay(formatManagerToUse, cacheToUse)
// pass _player variable into player object; so DeckGUI has access to player
// different way to using the initialization list; instead of ONLY passing an instance of the same type of object and storing it (player), passing the constructor arguments to waveForm through the constructor initialization
// passing the two arguements when instantiating waveFormDisplay object

{
    // In your constructor, you should add any child components, and initialise any special settings that your component needs.

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    otherLookAndFeel1.setColour(juce::Slider::thumbColourId, juce::Colours::orangered);
    otherLookAndFeel2.setColour(juce::Slider::thumbColourId, juce::Colours::forestgreen);
    otherLookAndFeel3.setColour(juce::Slider::thumbColourId, juce::Colours::cornflowerblue);
    // getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::orangered);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);

    addAndMakeVisible(waveFormDisplay);

    playButton.addListener(this); // register with button to receive click events; 'this' is pointer to itself; inherited from button listener
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.setLookAndFeel(&otherLookAndFeel1);
    volSlider.setSliderStyle(juce::Slider::Rotary);
    volSlider.addListener(this); // thing that wants to receive the events needs to tell the GUI object that is wants to register for events
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setNumDecimalPlacesToDisplay(2);
    volSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 60, volSlider.getTextBoxHeight());
    addAndMakeVisible(volLabel);
    volLabel.setText("Volume", juce::dontSendNotification);
    volLabel.attachToComponent(&volSlider, true);

    speedSlider.setLookAndFeel(&otherLookAndFeel2);
    speedSlider.setSliderStyle(juce::Slider::Rotary);
    speedSlider.addListener(this); // thing that wants to receive the events needs to tell the GUI object that is wants to register for events
    speedSlider.setRange(0.1, 2.0);
    speedSlider.setValue(1.0);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 60, speedSlider.getTextBoxHeight());
    addAndMakeVisible(speedLabel);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, true);

    addAndMakeVisible(dampingSlider);
    dampingSlider.setRange(1, 1000.0);
    dampingSlider.setTextValueSuffix(" factor");
    dampingSlider.setValue(10.0);
    dampingSlider.addListener(this);
    dampingSlider.setSkewFactorFromMidPoint(500);
    dampingSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 120, dampingSlider.getTextBoxHeight());
    addAndMakeVisible(dampingLabel);
    dampingLabel.setText("Damping", juce::dontSendNotification);
    dampingLabel.attachToComponent(&dampingSlider, true);

    positionSlider.setLookAndFeel(&otherLookAndFeel3);
    // positionSlider.setSliderStyle(juce::Slider::Rotary);
    positionSlider.addListener(this); // thing that wants to receive the events needs to tell the GUI object that is wants to register for events
    positionSlider.setRange(0.0, 1.0);
    positionSlider.setTextValueSuffix(" % of track");
    positionSlider.setNumDecimalPlacesToDisplay(2);
    positionSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 120, positionSlider.getTextBoxHeight());
    addAndMakeVisible(positionLabel);
    positionLabel.setText("Position", juce::dontSendNotification);
    positionLabel.attachToComponent(&positionSlider, true);

    startTimer(500);

}

DeckGUI::~DeckGUI()
{
    stopTimer();
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
    // g.drawText ("DJ Audio", getLocalBounds(),juce::Justification::centred, true);   // draw some placeholder text
    g.drawText("DJ Audio", 10, 10, getWidth(), 10, juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child components that your component contains..

    double rowHeight = getHeight() / 12;
    double width = (getWidth() - 20);
    auto sliderLeft = 60;

    auto border = 4;

    auto area = getLocalBounds();

    auto dialArea = area.removeFromTop(area.getHeight() * 2);

    playButton.setBounds(15, 40, (width / 3) - 10, rowHeight);
    stopButton.setBounds((width / 3) + 15, 40, (width / 3) - 10, rowHeight);
    loadButton.setBounds(2 * (width / 3) + 15, 40, (width / 3) - 10, rowHeight);

    //setColour(juce::Slider::thumbColourId, juce::Colours::red);
    volSlider.setBounds(sliderLeft, 10 + (rowHeight * 2), width / 2 - sliderLeft, rowHeight * 4);
    speedSlider.setBounds(sliderLeft + width / 2, 10 + (rowHeight * 2), width / 2 - sliderLeft, rowHeight * 4);
    positionSlider.setBounds(sliderLeft, 10 + (rowHeight * 5), width - sliderLeft, rowHeight * 2);
    dampingSlider.setBounds(sliderLeft, 10 + (rowHeight * 7), width - sliderLeft, rowHeight * 2);

    waveFormDisplay.setBounds(5, 8 * (getHeight() / 10), width + 10, rowHeight * 2.2);

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
        player->setPosition(0); // player calls setPosition(0) function from DJaudio to start playing from the beginning
        player->start(); // player calls start function from DJaudio

    }
    else if (button == &stopButton) // button to stop audio file play
    {
        // std::cout << "Stop button has been clicked!" << std::endl;
        DBG("Stop button has been clicked!");
        juce::Logger::outputDebugString("Stop button!");
        // transportSource.stop();
        player->stop(); // player calls stop function from DJaudio

    }
    //else if (button == &loadButton) // button to load new audio file
    //{
    //    auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;
    //    fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
    //        {
    //            juce::File chosenFile = chooser.getResult();
    //            player->loadURL(juce::URL{ chosenFile }); // player calls loadURL function from DJaudio
    //            waveFormDisplay.loadURL(juce::URL{ chosenFile }); // waveFormDisplay from private initialization list of DeckGUI.h (WaveformDisplay waveFormDisplay;)
    //        });
    //}
    else if (button == &loadButton) // button to load new audio file
    {
        DBG("Load button was clicked ");
        juce::FileChooser chooser{ "Select a file" };
        if (chooser.browseForFileToOpen())
        {
            loadFile(juce::URL{ chooser.getResult() });
        }
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
        player->setGain(slider->getValue()); // player calls setGain function from DJaudio
    }
    else if (slider == &speedSlider)
    {
        DBG("Speed slider moved: " << slider->getValue());
        // resampleSource.setResamplingRatio(slider->getValue());
        player->setSpeed(slider->getValue()); // player calls setSpeed function from DJaudio
    }
    else if (slider == &positionSlider)
    {
        DBG("Position slider: " << slider->getValue());
        player->setPositionRelative(slider->getValue()); // player calls setPositionRelative function from DJaudio
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
    DBG("dragging......");
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int, int y)
{
    DBG("dropping!!");
    if (files.size() == 1)
    {
        player->loadURL(juce::URL{ juce::File{files[0]} }); // player calls loadURL function from DJaudio
        waveFormDisplay.loadURL(juce::URL{ fChooser.getResult() });
    }
}

void DeckGUI::loadFile(juce::URL audioURL)
{
    DBG("DeckGUI::loadFile called");
    player->loadURL(audioURL);
    waveFormDisplay.loadURL(audioURL);
}

void DeckGUI::timerCallback()
{
    // DBG("timer call back!");
    waveFormDisplay.setPositionRelative(player->getPositionRelative());
}