/*
  ==============================================================================

	DJAudioPlayer.cpp
	Created: 5 Aug 2024 8:17:45pm
	Author:  jesus.torres01

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
	: formatManager(_formatManager) {}

DJAudioPlayer::~DJAudioPlayer() {}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
	resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() {
	transportSource.releaseResources();
	resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL) {
	auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
	if (reader != nullptr) { // good file!
		std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader,
			true));
		transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
		readerSource.reset(newSource.release());
	}

}

void DJAudioPlayer::setGain(double gain) {
	if (gain >= 0 && gain <= 1.0) { ///////// MY CODE: Change comparison approach /////////
		transportSource.setGain(gain);
	}
	else {
		DBG("Couldn't set gain");
	}
}

void DJAudioPlayer::setSpeed(double ratio) {
	if (ratio >= 0 && ratio <= 100) { ///////// MY CODE: Change comparison approach /////////
		resampleSource.setResamplingRatio(ratio);
	}
	else {
		DBG("Couldn't set speed");
	}
}

void DJAudioPlayer::setPosition(double posInSecs) {
	transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos) {
	if (pos >= 0 && pos <= 1.0) { ///////// MY CODE: Change comparison approach /////////
		double posInSecs = transportSource.getLengthInSeconds() * pos;
		setPosition(posInSecs);
	}
	else {
		DBG("Couldn't set position relative");
	}
}

void DJAudioPlayer::start() {
	transportSource.start();
}

void DJAudioPlayer::stop() {
	transportSource.stop();
}

double DJAudioPlayer::getPositionRelative() {
	return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
