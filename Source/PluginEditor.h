/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomSlider.h"

//==============================================================================
/**
*/
class FXRackAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FXRackAudioProcessorEditor (FXRackAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~FXRackAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FXRackAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Label feedbackLabel;
    juce::Slider feedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;


    juce::Label wetnessLabel;
    juce::Slider wetnessSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetnessAttachment;

    juce::Label delayTimeLabel;
    juce::Slider delayTimeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayTimeAttachment;

    //UI

    juce::Image backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::BackGrounds_jpg, BinaryData::BackGrounds_jpgSize);
    juce::Image woodenFrame = juce::ImageFileFormat::loadFrom(BinaryData::frame_png, BinaryData::frame_pngSize);
    juce::Rectangle<float> frameArea = juce::Rectangle<float>(-20, -80, 640, 460);

    CustomSlider customSlider;
    juce::Rectangle<int> areaToPlayWith;
    juce::Rectangle<int> currentArea;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FXRackAudioProcessorEditor)
};


