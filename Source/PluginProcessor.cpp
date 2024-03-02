/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
FXRackAudioProcessor::FXRackAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
     ), parameters(*this, nullptr, juce::Identifier("FXRack"), {
         std::make_unique<juce::AudioParameterFloat>("feedback","Feedback",0.0f,1.0f,0.05f),
         std::make_unique<juce::AudioParameterFloat>("wetness", "Wetness", 0.0f, 1.0f, 0.75f),
         std::make_unique<juce::AudioParameterFloat>("delayTime", "DelayTime", 0.0f, 2.0f, 0.5f)
         })
#endif
{
    feedback = parameters.getRawParameterValue("feedback");
    wetness = parameters.getRawParameterValue("wetness");
    delayTime = parameters.getRawParameterValue("delayTime");
}

FXRackAudioProcessor::~FXRackAudioProcessor()
{
}

//==============================================================================
const juce::String FXRackAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FXRackAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FXRackAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FXRackAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FXRackAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FXRackAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FXRackAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FXRackAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FXRackAudioProcessor::getProgramName (int index)
{
    return {};
}

void FXRackAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FXRackAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    //parametricEQ.prepareToPlay(sampleRate, samplesPerBlock,getNumInputChannels());
    longDelay.prepareToPlay(sampleRate, samplesPerBlock, getNumInputChannels());
}

void FXRackAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FXRackAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FXRackAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    longDelay.processBlock(buffer,*delayTime*getSampleRate(), *wetness, *feedback);
    //0.68 Critically Stable
    
}

//==============================================================================
bool FXRackAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FXRackAudioProcessor::createEditor()
{
    return new FXRackAudioProcessorEditor (*this,parameters);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void FXRackAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FXRackAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FXRackAudioProcessor();
}
