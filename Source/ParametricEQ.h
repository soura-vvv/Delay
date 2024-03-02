/*
  ==============================================================================

    ParametricEQ.h
    Created: 19 Apr 2023 4:28:53pm
    Author:  soura

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class FXRackParametricEQ
{
public:
    FXRackParametricEQ();
    ~FXRackParametricEQ();

    void prepareToPlay(double sampleRate,int samplesPerBlock,int numInputChannels);
    void processBlock(juce::AudioBuffer<float>& buffer);
    void updateCoefficients();
private:

    float sampleRate;
    int samplesPerBlock;
    float a0, a1, a2, b1, b2, c0, d0;   //Filter Coefficients
    float xnm1[2], xnm2[2], ynm1[2], ynm2[2];
    std::vector<std::vector<float>> buff;
};