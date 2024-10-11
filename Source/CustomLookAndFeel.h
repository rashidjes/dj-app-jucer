/*
  ==============================================================================

	CustomLookAndFeel.h
	Created: 29 Aug 2024 12:18:27pm
	Author:  jesus.torres01

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
	CustomLookAndFeel();

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};
