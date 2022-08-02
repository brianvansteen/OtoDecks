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
class WaveformDisplay  : public juce::Component, public juce::ChangeListener // add ChangeBroadcaster listener to inheritance
{
public:
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse, juce::AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void loadURL(juce::URL audioURL);

private:

    juce::AudioThumbnail audioThumb; // AudioThumbnail constructor (to draw waveform share of audio) has three arguments, but do not have access to incoming data coming into my constructor (WaveformDisplay
    // so need to add it to initialization list in the constructor file >> audioThumb(1000, formatManagerToUse, cacheToUse)
    // only want 1 instance of AudioFormatManager and AudioThumbnailCache since the cache is shared between any audio thumbnails; both will be part of Main Component where data is stored

    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
