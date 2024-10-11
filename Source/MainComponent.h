/*
  ==============================================================================

	MainComponent.h
	Created: 5 Aug 2024 8:17:45pm
	Author:  jesus.torres01

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"


//==============================================================================
/*
	This component lives inside our window, and this is where you should put all
	your controls and content.
*/
class MainComponent : public AudioAppComponent
{
public:
	//==============================================================================
	MainComponent();
	~MainComponent();

	//==============================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	//==============================================================================
	void paint(Graphics& g) override;
	void resized() override;

private:
	//==============================================================================
	AudioFormatManager formatManager;
	AudioThumbnailCache thumbCache{ 100 };

	DJAudioPlayer player1{ formatManager };
	DeckGUI deckGUI1{ &player1, formatManager, thumbCache };

	DJAudioPlayer player2{ formatManager };
	DeckGUI deckGUI2{ &player2, formatManager, thumbCache };

	juce::MixerAudioSource mixerSource;

	PlaylistComponent playlistComponent{ formatManager, deckGUI1 , deckGUI2 };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
