/*
  ==============================================================================

	MainComponent.cpp
	Created: 5 Aug 2024 8:17:45pm
	Author:  jesus.torres01

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() {
	setSize(800, 600);

	if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
		&& !RuntimePermissions::isGranted(RuntimePermissions::recordAudio)) {
		RuntimePermissions::request(RuntimePermissions::recordAudio,
			[&](bool granted) { if (granted)  setAudioChannels(2, 2); });
	}
	else {
		setAudioChannels(0, 2);
	}

	addAndMakeVisible(deckGUI1);
	addAndMakeVisible(deckGUI2);

	addAndMakeVisible(playlistComponent);

	formatManager.registerBasicFormats();
}

MainComponent::~MainComponent() {
	shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
	player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
	player2.prepareToPlay(samplesPerBlockExpected, sampleRate);

	mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	mixerSource.addInputSource(&player1, false);
	mixerSource.addInputSource(&player2, false);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
	mixerSource.getNextAudioBlock(bufferToFill);
}
void MainComponent::releaseResources() {
	player1.releaseResources();
	player2.releaseResources();
	mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint(Graphics& g) {
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
	deckGUI1.setBounds(0, 0, getWidth() / 2, getHeight() / 1.4); ///////// MY CODE: Make the deck bigger to organise its elements better /////////
	deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 1.4); ///////// MY CODE: Make the deck bigger to organise its elements better /////////
	playlistComponent.setBounds(0, getHeight() / 1.6, getWidth(), getHeight() / 1.6); ///////// MY CODE: Make the play list smaller to organise the deck's elements better /////////
}
