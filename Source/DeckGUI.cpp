/*
  ==============================================================================

	DeckGUI.cpp
	Created: 7 Aug 2024 11:15:26am
	Author:  jesus.torres01

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
	AudioFormatManager& formatManagerToUse,
	AudioThumbnailCache& cacheToUse)
	: player(_player), waveformDisplay(formatManagerToUse, cacheToUse) {
	setLookAndFeel(&customLookAndFeel);

	///////// MY CODE: Initialise and configure the buttons /////////
	initImageButton(loadButton, "../assets/images/load.png");
	initImageButton(playButton, "../assets/images/play.png");
	initImageButton(stopButton, "../assets/images/pause.png");

	///////// MY CODE: Initialise and configure the control knobs /////////
	initControlKnob(volSlider, 0.0, 1.0, 0.5);
	initControlKnob(speedSlider, 0.0, 100.0, 0.0);

	///////// MY CODE: Initialise and configure the position control slider /////////
	addAndMakeVisible(posSlider);
	posSlider.addListener(this);
	posSlider.setRange(0.0, 1.0);

	addAndMakeVisible(waveformDisplay);

	startTimer(500);
}

DeckGUI::~DeckGUI() {
	stopTimer();
}

void DeckGUI::paint(juce::Graphics& g) {
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(juce::Colours::white);
	g.setFont(juce::FontOptions(14.0f));
	g.drawText("",
		getLocalBounds(),
		juce::Justification::centred,
		true);   // draw some placeholder text
}

void DeckGUI::resized() {
	int rowW = getWidth() / 3;
	int rowH = getHeight() / 9;

	loadButton.setBounds(0, rowH / 2, rowW, rowH * 1.25);
	playButton.setBounds(rowW, rowH / 2, rowW, rowH * 1.25);
	stopButton.setBounds(rowW * 2, rowH / 2, rowW, rowH * 1.25);

	volSlider.setBounds(getWidth() / 6, rowH * 2, rowW, rowH * 2.5);
	speedSlider.setBounds(getWidth() / 2, rowH * 2, rowW, rowH * 2.5);
	posSlider.setBounds(0, rowH * 5, getWidth(), rowH);

	waveformDisplay.setBounds(0, rowH * 6, getWidth(), rowH * 2);
}

void DeckGUI::buttonClicked(Button* button) {
	if (button == &loadButton) {
		//DBG("load button was clicked");
		auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
		fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser) {
			auto chosenFile = chooser.getResult();
			player->loadURL(URL{ chosenFile });
			waveformDisplay.loadURL(URL{ chosenFile });
			}
		);
	}

	if (button == &playButton) {
		//DBG("play button was clicked");
		player->start();
	}

	if (button == &stopButton) {
		//DBG("stop button was clicked");
		player->stop();

	}
}

void DeckGUI::sliderValueChanged(Slider* slider) {
	if (slider == &volSlider) {
		player->setGain(slider->getValue());
	}

	if (slider == &speedSlider) {
		player->setSpeed(slider->getValue());
	}

	if (slider == &posSlider) {
		player->setPositionRelative(slider->getValue());
	}
}

bool DeckGUI::isInterestedInFileDrag(const StringArray& files) {
	//DBG("DeckGUI::isInterestedInFileDrag");
	return true;
}

void DeckGUI::filesDropped(const StringArray& files, int x, int y) {
	//DBG("DeckGUI::filesDropped");
	if (files.size() == 1) {
		player->loadURL(URL{ File{files[0]} });
	}
}

void DeckGUI::timerCallback() {
	//DBG("DeckGUI::timerCallback");
	waveformDisplay.setPositionRelative(player->getPositionRelative());
}

DJAudioPlayer* DeckGUI::getPlayer() {
	return player;
}

WaveformDisplay& DeckGUI::getWaveformDisplay() {
	return waveformDisplay;
}

/** MY CODE: Implement a method to create full-functional buttons from images */
void DeckGUI::initImageButton(juce::ImageButton& button, const juce::String& imagePath) {
	// Load the image for the button
	juce::File currentFile(__FILE__); // Get the current file path
	juce::File loadFile = currentFile.getSiblingFile(imagePath);
	juce::Image loadImage = juce::ImageFileFormat::loadFrom(loadFile);

	// Create the button and set the image
	button.setImages(false, true, true,
		loadImage, 1.0f, juce::Colours::transparentBlack,
		loadImage, 1.0f, juce::Colours::transparentBlack,
		loadImage, 1.0f, juce::Colours::transparentBlack);

	// Set the button's hover cursor
	juce::MouseCursor hoverCursor(juce::MouseCursor::PointingHandCursor);
	button.setMouseCursor(hoverCursor);

	// additional config
	button.setClickingTogglesState(true);
	addAndMakeVisible(button);
	button.addListener(this);
}

/** MY CODE: Implement a method to create full-functional knobs that can be used like sliders */
void DeckGUI::initControlKnob(juce::Slider& slider,
	const double minRange,
	const double maxRange,
	const double DefaultLevel) {
	slider.setSliderStyle(juce::Slider::Rotary);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
	slider.setRange(minRange, maxRange);
	slider.setValue(DefaultLevel);
	addAndMakeVisible(slider);
	slider.addListener(this);
}
