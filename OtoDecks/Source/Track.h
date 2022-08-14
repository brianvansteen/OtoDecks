/*
  ==============================================================================

    Track.h
    Created: 14 Aug 2022 10:25:08am
    Author:  bvans

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Track
{
public:
    Track(juce::File _file);
    juce::File file;
    juce::URL URL;
    juce::String title;
    juce::String length;
    
    bool operator==(const juce::String& other) const; // files are compared by title
};