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
PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2, DJAudio* _playerForParsingMetaData) : deckGUI1(_deckGUI1), deckGUI2(_deckGUI2), playerForParsingMetaData(_playerForParsingMetaData)

{
    // In your constructor, you should add any child components, and initialise any special settings that your component needs.

    //trackTitles.push_back("Black Dog");
    //trackTitles.push_back("Lemon Song");
    //trackTitles.push_back("Dazed and Confused");
    //trackTitles.push_back("Out on the Tiles");
    //trackTitles.push_back("Wearing and Tearing");
    //trackTitles.push_back("Boogie with Stu");

    //tableComponent.getHeader().addColumn("Title", 1, 180);
    //tableComponent.getHeader().addColumn("Artist", 2, 140);
    //tableComponent.getHeader().addColumn("", 3, 80);
    //tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);

    addAndMakeVisible(importButton);
    addAndMakeVisible(searchField);
    addAndMakeVisible(library);
    addAndMakeVisible(addToPlayer1Button);
    addAndMakeVisible(addToPlayer2Button);

    importButton.addListener(this);
    searchField.addListener(this);
    addToPlayer1Button.addListener(this);
    addToPlayer2Button.addListener(this);

    searchField.setTextToShowWhenEmpty("Search Library (enter to submit)", juce::Colours::orangered);
    searchField.onReturnKey = [this] { searchLibrary(searchField.getText()); };

    // setup table and load library from file
    library.getHeader().addColumn("Tracks", 1, 1);
    library.getHeader().addColumn("Length", 2, 1);
    library.getHeader().addColumn("Artist", 3, 1);
    library.getHeader().addColumn("Album", 4, 1);
    library.getHeader().addColumn("delete", 5, 1);
    library.setModel(this);
    loadLibrary();
}

PlaylistComponent::~PlaylistComponent()
{
    // tableComponent.setModel(nullptr);
    saveLibrary();
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour{ 30, 144, 255 });

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::orangered);
    g.setFont (30.0f);
    // g.drawText ("PlaylistComponent", getLocalBounds(),
                //juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child components that your component contains..

    // tableComponent.setBounds(5, 5, getWidth() - 5, getHeight());
    importButton.setBounds(0.3 * getWidth(), 5, 0.4 * getWidth(), getHeight() / 10);
    library.setBounds(20, 4 * getHeight() / 30, getWidth() - 40, 20 * getHeight() / 30);
    searchField.setBounds(0, 16 * getHeight() / 20, getWidth(), getHeight() / 12);
    addToPlayer1Button.setBounds(0, 18 * getHeight() / 20, getWidth() / 2, getHeight() / 10);
    addToPlayer2Button.setBounds(getWidth() / 2, 18 * getHeight() / 20, getWidth() / 2, getHeight() / 10);

    //set columns
    library.getHeader().setColumnWidth(1, 4 * getWidth() / 20);
    library.getHeader().setColumnWidth(2, 4 * getWidth() / 20);
    library.getHeader().setColumnWidth(3, 4 * getWidth() / 20);
    library.getHeader().setColumnWidth(4, 4 * getWidth() / 20);
    library.getHeader().setColumnWidth(5, 2 * getWidth() / 20);
}

int PlaylistComponent::getNumRows()
{
    return tracks.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::yellow);
    }
    else
    {
        g.fillAll(juce::Colours::darkslateblue);
    }
}

void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (rowNumber < getNumRows())
        if (columnId == 1)
        {
            g.drawText(tracks[rowNumber].title, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
        }
        if (columnId == 2)
        {
            g.drawText(tracks[rowNumber].length, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
        }
}

PlaylistComponent::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, PlaylistComponent::Component *existingComponentToUpdate)
{
    if (columnId == 5)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{ "Delete Track" };

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
    //int id = std::stoi(button->getComponentID().toStdString());

    //DBG("Button clicked!" << button->getComponentID());
    //DBG(trackTitles[id]);

    if (button == &importButton)
    {
        DBG("Load button clicked");
        importToLibrary();
        library.updateContent();
    }
    else if (button == &addToPlayer1Button)
    {
        DBG("Add to Player 1 clicked");
        loadInPlayer(deckGUI1);
    }
    else if (button == &addToPlayer2Button)
    {
        DBG("Add to Player 2 clicked");
        loadInPlayer(deckGUI2);
    }
    else
    {
        int id = std::stoi(button->getComponentID().toStdString());
        DBG(tracks[id].title + " removed from Library");
        deleteFromTracks(id);
        library.updateContent();
    }
}

void PlaylistComponent::loadInPlayer(DeckGUI* deckGUI)
{
    int selectedRow{ library.getSelectedRow() };
    if (selectedRow != -1)
    {
        DBG("Adding: " << tracks[selectedRow].title << " to Player");
        deckGUI->loadFile(tracks[selectedRow].URL);
    }
    else
    {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon,
            "Add to Deck Information:",
            "Please select a track to add to deck",
            "OK",
            nullptr
        );
    }
}

void PlaylistComponent::importToLibrary()
{
    DBG("PlaylistComponent::importToLibrary called");

    //initialize file chooser
    juce::FileChooser chooser{ "Select files" };
    if (chooser.browseForMultipleFilesToOpen())
    {
        for (const juce::File& file : chooser.getResults())
        {
            juce::String fileNameWithoutExtension{ file.getFileNameWithoutExtension() };
            if (!isInTracks(fileNameWithoutExtension)) // if not already loaded
            {
                Track newTrack{ file };
                juce::URL audioURL{ file };
                newTrack.length = getLength(audioURL);
                tracks.push_back(newTrack);
                DBG("loaded file: " << newTrack.title);
            }
            else // display info message
            {
                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon,
                    "Load information:",
                    fileNameWithoutExtension + " already loaded",
                    "OK",
                    nullptr
                );
            }
        }
    }
}

bool PlaylistComponent::isInTracks(juce::String fileNameWithoutExtension)
{
    return (std::find(tracks.begin(), tracks.end(), fileNameWithoutExtension) != tracks.end());
}

void PlaylistComponent::deleteFromTracks(int id)
{
    tracks.erase(tracks.begin() + id);
}

juce::String PlaylistComponent::getLength(juce::URL audioURL)
{
    playerForParsingMetaData->loadURL(audioURL);
    double seconds{ playerForParsingMetaData->getLengthInSeconds() };
    juce::String minutes{ secondsToMinutes(seconds) };
    return minutes;
}

juce::String PlaylistComponent::secondsToMinutes(double seconds)
{
    //find seconds and minutes and make into string
    int secondsRounded{ int(std::round(seconds)) };
    juce::String min{ std::to_string(secondsRounded / 60) };
    juce::String sec{ std::to_string(secondsRounded % 60) };

    if (sec.length() < 2) // if seconds is 1 digit or less
    {
        //add '0' to seconds until seconds is length 2
        sec = sec.paddedLeft('0', 2);
    }
    return juce::String{ min + ":" + sec };
}

void PlaylistComponent::searchLibrary(juce::String searchText)
{
    DBG("Searching library for: " << searchText);
    if (searchText != "")
    {
        int rowNumber = whereInTracks(searchText);
        library.selectRow(rowNumber);
    }
    else
    {
        library.deselectAllRows();
    }
}

int PlaylistComponent::whereInTracks(juce::String searchText)
{
    // finds index where track title contains searchText
    auto it = find_if(tracks.begin(), tracks.end(),
        [&searchText](const Track& obj) {return obj.title.contains(searchText); });
    int i = -1;

    if (it != tracks.end())
    {
        i = std::distance(tracks.begin(), it);
    }

    return i;
}

void PlaylistComponent::saveLibrary()
{
    // create .csv to save library
    std::ofstream myLibrary("my-library.csv");

    // save library to file
    for (Track& t : tracks)
    {
        myLibrary << t.file.getFullPathName() << "," << t.length << "\n";
    }
}

void PlaylistComponent::loadLibrary()
{
    // create input stream from saved library
    std::ifstream myLibrary("my-library.csv");
    std::string filePath;
    std::string length;

    // Read data, line by line
    if (myLibrary.is_open())
    {
        while (getline(myLibrary, filePath, ',')) {
            juce::File file{ filePath };
            Track newTrack{ file };

            getline(myLibrary, length);
            newTrack.length = length;
            tracks.push_back(newTrack);
        }
    }
    myLibrary.close();
}