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
#include <algorithm>
#include <fstream>
#include "DeckGUI.h"
#include "DJAudio.h"
#include "Track.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component, public juce::TableListBoxModel, public juce::Button::Listener, public juce::TextEditor::Listener // inherit TableListBoxModel, to allow PlayListComponent to behave like a table
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2, DJAudio* _playerForParsingMetaData);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;

    void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;

    void buttonClicked(juce::Button* button); // function to implement Button::Listener; called when button clicked

private:
    
    juce::TableListBox tableComponent;
    std::vector<Track> tracks;

    juce::TextButton importButton{ "IMPORT AUDIO LIBRARY" };
    juce::TextEditor searchField;
    juce::TableListBox library;
    juce::TextButton addToPlayer1Button{ "ADD TO LEFT DECK" };
    juce::TextButton addToPlayer2Button{ "ADD TO RIGHT DECK" };

    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    DJAudio* playerForParsingMetaData;

    juce::String getLength(juce::URL audioURL);
    juce::String secondsToMinutes(double seconds);

    void importToLibrary();
    void searchLibrary(juce::String searchText);
    void saveLibrary();
    void loadLibrary();
    void deleteFromTracks(int id);
    bool isInTracks(juce::String fileNameWithoutExtension);
    int whereInTracks(juce::String searchText);
    void loadInPlayer(DeckGUI* deckGUI);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
