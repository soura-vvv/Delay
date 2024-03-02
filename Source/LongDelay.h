/*
  ==============================================================================

    LongDelay.h
    Created: 19 Apr 2023 10:35:05pm
    Author:  soura

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class FXRackLongDelay
{
public:
    FXRackLongDelay();
    ~FXRackLongDelay();
    void prepareToPlay(float sampleRate,int samplesPerBlock,int numInputChannels);
    void processBlock(juce::AudioBuffer<float>& buffer,int delayLength,float wetness,float feedback);

private:
    std::vector<float> delayBuffer;
    int readIndex;
    int writeIndex;
    int delaySize;
    int buffSize;
    int numInputChannels;
};