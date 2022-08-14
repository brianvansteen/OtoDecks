/*
  ==============================================================================

    Track.cpp
    Created: 14 Aug 2022 10:25:08am
    Author:  bvans

  ==============================================================================
*/

#include "Track.h"
#include <filesystem>

Track::Track(juce::File _file) : file(_file),
title(_file.getFileNameWithoutExtension()),
URL(juce::URL{ _file })
{
    DBG("Created new track with title: " << title);
}

bool Track::operator==(const juce::String& other) const
{
    return title == other;
}