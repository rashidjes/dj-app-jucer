/*
  ==============================================================================

	PlaylistComponent.h
	Created: 14 Aug 2024 6:47:48pm
	Author:  jesus.torres01

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DeckGUI.h"
#include "CustomLookAndFeel.h"


//==============================================================================
/*
*/
class PlaylistComponent : public juce::Component,
	public juce::TableListBoxModel,
	public juce::Button::Listener
{
public:
	PlaylistComponent(AudioFormatManager& formatManager, DeckGUI& deckGUI1, DeckGUI& deckGUI2);
	~PlaylistComponent() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	int getNumRows() override;

	void paintRowBackground(Graphics&,
		int rowNumber,
		int width,
		int height,
		bool rowIsSelected) override;

	void paintCell(Graphics&,
		int rowNumber,
		int columnId,
		int width,
		int height,
		bool rowIsSelected) override;

	Component* refreshComponentForCell(int rowNumber,
		int columnId,
		bool isRowSelected,
		Component* existingComponentToUpdate) override;

	void buttonClicked(Button* button) override;

private:
	TableListBox tableComponent;
	juce::StringArray trackTitles;
	juce::Array<double> durations;
	AudioFormatManager& formatManager;
	DeckGUI& deckGUI1;
	DeckGUI& deckGUI2;

	juce::String formatDuration(double seconds);

	/** MY CODE: Define a method to get the list of songs within a particular directory */
	void getTrackTitles(const juce::File& directory);

	/** MY CODE: Define a method to play the songs on the decks based on the column index */
	void playButtonClicked(int rowNumber, int playerIndex);

	CustomLookAndFeel customLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
