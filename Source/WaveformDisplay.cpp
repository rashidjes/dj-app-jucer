/*
  ==============================================================================

	WaveformDisplay.cpp
	Created: 10 Aug 2024 9:19:23am
	Author:  jesus.torres01

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
	AudioThumbnailCache& cacheToUse)
	: audioThumb(1000, formatManagerToUse, cacheToUse), fileLoaded(false), position(0) {
	audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay() {}

void WaveformDisplay::paint(juce::Graphics& g) {
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(juce::Colours::orange);

	if (fileLoaded) {
		audioThumb.drawChannel(g,
			getLocalBounds(),
			0,
			audioThumb.getTotalLength(),
			0,
			1.0f);
		g.setColour(Colours::lightgreen);
		g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
	}
	else {
		g.setFont(juce::FontOptions(20.0f));
		g.drawText("File not loaded...", getLocalBounds(),
			juce::Justification::centred, true);   // draw some placeholder text
	}
}

void WaveformDisplay::resized() {}

void WaveformDisplay::loadURL(URL audioURL) {
	//DBG("WaveformDisplay::loadURL");
	audioThumb.clear();
	fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));

	if (fileLoaded) {
		DBG("Loaded!");
		repaint();
	}
	else {
		DBG("Not loaded!");
	}
}

void WaveformDisplay::setPositionRelative(double pos) {
	if (pos != position) {
		position = pos;
		repaint();
	}
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source) {
	//DBG("WaveformDisplay::changeListenerCallback");
	repaint();
}
