/*
  ==============================================================================

	CustomLookAndFeel.cpp
	Created: 29 Aug 2024 12:18:27pm
	Author:  jesus.torres01

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//==============================================================================
CustomLookAndFeel::CustomLookAndFeel() {
    juce::LookAndFeel_V4::setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::black);
    juce::LookAndFeel_V4::setColour(juce::Slider::thumbColourId, juce::Colours::white);
    juce::LookAndFeel_V4::setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::yellow);
    juce::LookAndFeel_V4::setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    juce::LookAndFeel_V4::setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    juce::LookAndFeel_V4::setColour(juce::TextButton::textColourOffId, juce::Colours::yellow);
    juce::LookAndFeel_V4::setColour(juce::TextButton::buttonOnColourId, juce::Colours::red);
}
