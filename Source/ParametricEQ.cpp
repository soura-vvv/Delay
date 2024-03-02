/*
  ==============================================================================

    ParametricEQ.cpp
    Created: 19 Apr 2023 4:28:53pm
    Author:  soura

  ==============================================================================
*/

#include "ParametricEQ.h"



FXRackParametricEQ::FXRackParametricEQ()
{
    a0 = 0.f;
    a1 = 0.f;
    a2 = 0.f;
    b1 = 0.f;
    b2 = 0.f;
    c0 = 0.f;
    d0 = 1.0f;

    xnm1[0] = 0.0f,xnm1[1]=0.0f;
    xnm2[0] = 0.0f, xnm2[1] = 0.0f;
    ynm1[0] = 0.0f, ynm1[1] = 0.0f;
    ynm2[0] = 0.0f, ynm2[1] = 0.0f;



   /* a0 = 0.0332;
    a2 = -0.0332;
    b1 = -1.9318;
    b2 = 0.9336;
    c0 = 2.9811;*/

}

FXRackParametricEQ::~FXRackParametricEQ()
{

}

void FXRackParametricEQ::prepareToPlay(double sampleRate,int samplesPerBlock,int numInputChannels)
{
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;
    //this->buff=

}

void FXRackParametricEQ::processBlock(juce::AudioBuffer<float>& buffer)
{
    //float* channelData = nullptr;
    //auto* channelData[2] = {};
    //auto channelData=std::array<float*, 2>{buffer.getReadPointer(0), buffer.getReadPointer(1)};

    for (int n = 0; n < buffer.getNumSamples(); n++)
    {
        updateCoefficients();
        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
        {
            auto sample = buffer.getReadPointer(channel)[n];
            

            float wetSample = a0 * sample + a1 * xnm1[channel] + a2 * xnm2[channel] - b1 * ynm1[channel] - b2 * ynm2[channel];

            buffer.getWritePointer(channel)[n] = d0 * sample + c0 * wetSample;


            xnm2[channel] = xnm1[channel];
            ynm2[channel] = ynm1[channel];
            xnm1[channel] = sample;
            ynm1[channel] = wetSample;

        }

        
    }
}

void FXRackParametricEQ::updateCoefficients()
{
    
}
