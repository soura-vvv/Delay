/*
  ==============================================================================

    LongDelay.cpp
    Created: 19 Apr 2023 10:35:05pm
    Author:  soura

  ==============================================================================
*/

#include "LongDelay.h"



FXRackLongDelay::FXRackLongDelay()
{
    readIndex = 0;
    writeIndex = 0;
    delaySize = 0;
    buffSize = 0;
    numInputChannels = 0;
}

FXRackLongDelay::~FXRackLongDelay()
{

}

void FXRackLongDelay::prepareToPlay(float sampleRate,int samplesPrerBlock,int numInputChannels)
{
    
   buffSize = sampleRate * 2 * numInputChannels;//2 sec max delay
   this->numInputChannels = numInputChannels;
   delayBuffer.resize(buffSize, 0.0f); 
}

void FXRackLongDelay::processBlock(juce::AudioBuffer<float>& buffer,int delayLength,float wetness,float feedback)
{
    
    readIndex = writeIndex - delayLength*numInputChannels;
    if (readIndex < 0)
        readIndex = buffSize + readIndex;

    for (int n = 0; n < buffer.getNumSamples(); n++)
    {
        
        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
        {
            auto wetSample = delayBuffer[readIndex];
            buffer.getWritePointer(channel)[n] = buffer.getReadPointer(channel)[n] + wetness * wetSample;
            delayBuffer[writeIndex] = buffer.getReadPointer(channel)[n] + feedback * wetSample;


            readIndex=(readIndex+1)%buffSize;
            writeIndex=(writeIndex+1)%buffSize;

        }


    }


}