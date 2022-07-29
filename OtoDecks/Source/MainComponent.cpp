#include "MainComponent.h"
#include <JuceHeader.h>

//==============================================================================
MainComponent::MainComponent() // four classes: component, audio source, button listener, slider listener
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(2, 2);
    }

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);

    playButton.addListener(this); // register with button to receive click events; 'this' is pointer to itself; inherited from button listener
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this); // thing that wants to receive the events needs to tell the GUI object that is wants to register for events
    volSlider.setRange(0.0, 1.0);

    speedSlider.addListener(this); // thing that wants to receive the events needs to tell the GUI object that is wants to register for events
    speedSlider.setRange(0.0, 2.0);

    //keyPressed.addListener(this);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate) // called first, and once only
{
    // This function will be called when the audio device is started, or when its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need, but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

    phase = 0.0;
    dphase = 0.0001;

    formatManager.registerBasicFormats(); // register audio formats to read files

    //juce::URL audioURL{ "file:///C:\\Users\\bvans\\Desktop\\Technology\\University-of-London\\Level5\\Session3\\OOP\\Week14\\tracks\\electro_smash.mp3" };

    //auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false)); // unpack audio URL and converted to input stream, and creates a reader
    //if (reader != nullptr) // file is accessible
    //{
    //    std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource (reader, true)); // create audio format reader source, when file is read
    //    transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate); // control playback of audio
    //    readerSource.reset(newSource.release()); // transfer ownership to class variable
    //    transportSource.start();
    //}

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate); // now need to get it to the audio system

    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate); // now need to get it to the audio system
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) // call after prepareToPlay, and called repeatedly (like 'draw')
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer (to prevent the output of random noise)
    
    // bufferToFill.clearActiveBufferRegion();

    //auto* leftChannel = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    //auto* rightChannel = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);

    //for (auto i = 0; i < bufferToFill.numSamples; ++i) // increments and assigns; while i++ copies, increements copy and then assigns
    //{
    //    // double sample = rand.nextDouble() * 0.5;
    //    double sample = fmod(phase, 0.3);

    //    leftChannel[i] = sample;
    //    rightChannel[i] = sample;

    //    phase += dphase;
    //}

    // transportSource.getNextAudioBlock(bufferToFill);
    resampleSource.getNextAudioBlock(bufferToFill);
    // DBG("getNextAudioBlock!");
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()

    transportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colour{ 62, 95, 138 } );

    // You can add your drawing code here!
    g.setColour(juce::Colours::navajowhite);
    g.setFont(30.0f);
    g.drawText("Hello from Canada!", getLocalBounds(),
    juce::Justification::centred, true);
    DBG("Paint!");
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    DBG("MainComponent::resized");

    double rowHeight = getHeight() / 10;
    double width = getWidth() - 20;

    playButton.setBounds(10, 10, width, rowHeight);
    stopButton.setBounds(10, 20 + (rowHeight), width, rowHeight);

    volSlider.setBounds(10, 30 + (rowHeight * 2), width, rowHeight);
    speedSlider.setBounds(10, 30 + (rowHeight * 3), width, rowHeight);

    loadButton.setBounds(10, getHeight() - 80, width, rowHeight);
}

void MainComponent::buttonClicked(juce::Button* button) // pointer to button; memory address
{
    if (button == &playButton)
    {
        // std::cout << "Play button has been clicked!" << std::endl;
        DBG("Play button has been clicked!");
        juce::Logger::outputDebugString("Play button!");
        transportSource.start();

    }
    else if (button == &stopButton)
    {
        // std::cout << "Stop button has been clicked!" << std::endl;
        DBG("Stop button has been clicked!");
        juce::Logger::outputDebugString("Stop button!");
        transportSource.stop();

    }
    else if (button == &loadButton)
    {
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
                juce::File chosenFile = chooser.getResult();
                loadURL(juce::URL{ chosenFile });
            });
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        DBG("Volume slider moved: " << slider->getValue());
        transportSource.setGain(slider->getValue());
        // dphase = volSlider.getValue() * 0.001;
        // juce::Logger::outputDebugString(slider->getValue());
    }
    else if (slider == &speedSlider)
    {
        DBG("Speed slider moved: " << slider->getValue());
        resampleSource.setResamplingRatio(slider->getValue());
    }
}

void MainComponent::loadURL(juce::URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false)); // unpack audio URL and converted to input stream, and creates a reader
    if (reader != nullptr) // file is accessible
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true)); // create audio format reader source, when file is read
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate); // control playback of audio
        readerSource.reset(newSource.release()); // transfer ownership to class variable

    }
}