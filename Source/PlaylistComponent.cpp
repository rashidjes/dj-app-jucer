/*
  ==============================================================================

	PlaylistComponent.cpp
	Created: 14 Aug 2024 6:47:48pm
	Author:  jesus.torres01

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(AudioFormatManager& formatManager, DeckGUI& deckGUI1, DeckGUI& deckGUI2)
	: formatManager(formatManager), deckGUI1(deckGUI1), deckGUI2(deckGUI2) {
	setLookAndFeel(&customLookAndFeel);

	/** MY CODE: Get the list of songs and their duration from a particular directory */
	juce::File currentFile(__FILE__);
	juce::File directory = currentFile.getSiblingFile("../assets/tracks/");
	getTrackTitles(directory);
	//DBG("trackTitles.size()=>" << trackTitles.size());

	/** MY CODE: Set up the new table header */
	tableComponent.getHeader().setColour(TableHeaderComponent::backgroundColourId, Colours::palegoldenrod);
	tableComponent.getHeader().addColumn("Track tile", 1, 300);
	tableComponent.getHeader().addColumn("Duration", 2, 100);
	tableComponent.getHeader().addColumn("Left deck", 3, 200);
	tableComponent.getHeader().addColumn("Right deck", 4, 200);
	tableComponent.setModel(this);

	addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent() {}

void PlaylistComponent::paint(juce::Graphics& g) {
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(juce::Colours::white);
	g.setFont(juce::FontOptions(14.0f));
	g.drawText("PlaylistComponent", getLocalBounds(),
		juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized() {
	tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows() {
	return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(Graphics& g,
	int rowNumber,
	int width,
	int height,
	bool rowIsSelected) {
	if (rowIsSelected) {
		g.fillAll(Colours::orange);
	}
	else {
		g.fillAll(juce::Colours::black);
	}
}

void PlaylistComponent::paintCell(Graphics& g,
	int rowNumber,
	int columnId,
	int width,
	int height,
	bool rowIsSelected) {
	/** MY CODE: Add first two columns song name and duration */
	g.setColour(juce::Colours::white);
	if (columnId == 1) { // Song name column
		g.drawText(trackTitles[rowNumber], 2, 0, width - 4, height, Justification::centredLeft, true);
	}
	else if (columnId == 2) { // Duration column
		g.drawText(formatDuration(durations[rowNumber]), 2, 0, width - 4, height, juce::Justification::centredLeft);
	}
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
	int columnId,
	bool isRowSelected,
	Component* existingComponentToUpdate) {
	/** MY CODE: Add buttons to play songs on left and right decks */
	if (columnId == 3 || columnId == 4) {
		auto* btn = new juce::TextButton(columnId == 3 ? "Play on Left deck" : "Play on Right deck");
		btn->onClick = [this, rowNumber, columnId] { playButtonClicked(rowNumber, columnId == 3 ? 0 : 1); };
		existingComponentToUpdate = btn;
	}

	return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button) {}

/** MY CODE: Implement a method to format seconds as minutes:seconds */
juce::String PlaylistComponent::formatDuration(double seconds) {
	int minutes = static_cast<int>(seconds) / 60;
	int secs = static_cast<int>(seconds) % 60;
	return juce::String(minutes) + ":" + juce::String(secs).paddedLeft('0', 2);
}

/** MY CODE: Implement a method to get the list of songs within a particular directory */
void PlaylistComponent::getTrackTitles(const juce::File& directory) {
	formatManager.registerBasicFormats();

	if (directory.isDirectory()) {
		auto files = directory.findChildFiles(juce::File::findFiles, false, "*.mp3;*.wav;*.flac");
		for (auto& file : files) {
			trackTitles.add(file.getFileName());

			if (auto* reader = formatManager.createReaderFor(file)) {
				durations.add(reader->lengthInSamples / reader->sampleRate);
			}
		}
	}
}

/** MY CODE: Implement a method to play the songs on the decks based on the column index */
void PlaylistComponent::playButtonClicked(int rowNumber, int playerIndex) {
	juce::File currentFile(__FILE__);
	auto fileName = trackTitles[rowNumber];
	juce::File chosenFile = currentFile.getSiblingFile("../assets/tracks/" + fileName);

	if (playerIndex == 0) {
		deckGUI1.getPlayer()->loadURL(URL{ chosenFile });
		deckGUI1.getPlayer()->start();
		deckGUI1.getWaveformDisplay().loadURL(URL{ chosenFile });
	}
	else {
		deckGUI2.getPlayer()->loadURL(URL{ chosenFile });
		deckGUI2.getPlayer()->start();
		deckGUI2.getWaveformDisplay().loadURL(URL{ chosenFile });
	}
}
