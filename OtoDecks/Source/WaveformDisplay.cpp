/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 1 Aug 2022 12:33:56pm
    Author:  bvans

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse, juce::AudioThumbnailCache& cacheToUse) : audioThumb(1000, formatManagerToUse, cacheToUse), fileLoaded(false), position(10)

{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::orangered);
    if (fileLoaded)
    {
        audioThumb.drawChannel(g, getLocalBounds(), 0, audioThumb.getTotalLength(), 0, 1.5f); // g from paint function to draw on canvas within bounds of waveform compononent (from DeckGUI::resized function)
        // from 0 to end of audio file
        g.setColour(juce::Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    {
        // g.setFont (30.0f);
        g.setFont(juce::Font(20.0f, juce::Font::italic));
        g.drawText("file is loading....", getLocalBounds(), juce::Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(juce::URL audioURL) // DeckGUI needs to tell WaveformDisplay when file is ready, from loadButton
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL)); // getting URL; unpack URL, turn into new input source calling URLInputSource, then setSource onto audioThumb
    // AudioThumbnail::setSource is a boolean; specifies the file or stream that contains the audio file; returns True is valid audio source
    if (fileLoaded)
    {
        DBG("Waveform loaded!");
    }
    else
    {
        DBG("WFD: not loaded....");
    }
}