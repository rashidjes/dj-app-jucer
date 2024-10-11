/*
  ==============================================================================

	DeckGUI.h
	Created: 7 Aug 2024 11:15:26am
	Author:  jesus.torres01

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomLookAndFeel.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI : public juce::Component,
	public juce::Button::Listener,
	public juce::Slider::Listener,
	public juce::FileDragAndDropTarget,
	public juce::Timer
{
public:
	DeckGUI(DJAudioPlayer* player,
		AudioFormatManager& formatManagerToUse,
		AudioThumbnailCache& cacheToUse);
	~DeckGUI() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	/** implement Button::Listener */
	void buttonClicked(Button* button) override;

	/** implement Slider::Listener */
	void sliderValueChanged(Slider* slider) override;

	bool isInterestedInFileDrag(const StringArray& files) override;
	void filesDropped(const StringArray& files, int x, int y) override;

	void timerCallback() override;

	DJAudioPlayer* getPlayer();

	WaveformDisplay& getWaveformDisplay();

private:
	ImageButton loadButton;
	ImageButton playButton;
	ImageButton stopButton;

	Slider volSlider;
	Slider speedSlider;
	Slider posSlider;

	juce::FileChooser fChooser{ "Select a file..." };

	DJAudioPlayer* player;

	WaveformDisplay waveformDisplay;

	/** MY CODE: Define a method to create full-functional buttons from images */
	void initImageButton(juce::ImageButton& button, const juce::String& imagePath);

	/** MY CODE: Define a method to create full-functional knobs that can be used like sliders */
	void initControlKnob(juce::Slider& slider,
		const double minRange,
		const double maxRange,
		const double DefaultLevel);

	CustomLookAndFeel customLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
