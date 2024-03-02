/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FXRackAudioProcessorEditor::FXRackAudioProcessorEditor (FXRackAudioProcessor& p,juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p),valueTreeState(vts)
{

    setLookAndFeel(&customSlider);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    wetnessLabel.setText("Dry/Wet", juce::dontSendNotification);
    addAndMakeVisible(wetnessLabel);
    
    wetnessSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(wetnessSlider);
    wetnessAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "wetness", wetnessSlider));
    wetnessSlider.setTextBoxStyle(juce::Slider::NoTextBox, true,50,50);
    //wetnessLabel.attachToComponent(&wetnessSlider,false);
    wetnessLabel.setFont(juce::Font::bold);
    //wetnessLabel.setS

    feedbackLabel.setText("FeedBack", juce::dontSendNotification);
    addAndMakeVisible(feedbackLabel);

    feedbackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(feedbackSlider);
    feedbackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "feedback", feedbackSlider));
    feedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 50);
    //feedbackLabel.attachToComponent(&feedbackSlider, false);



    delayTimeLabel.setText("                                Time", juce::dontSendNotification);
    addAndMakeVisible(delayTimeLabel);

    delayTimeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(delayTimeSlider);
    delayTimeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delayTime", delayTimeSlider));
    delayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 50);
    //delayTimeLabel.attachToComponent(&delayTimeSlider, false);

   
    setSize (600, 300);
    

}

FXRackAudioProcessorEditor::~FXRackAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void FXRackAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont(juce::Font::bold);
    g.setFont (25.0f);
    

    //juce::Image backgroundImage = juce::ImageFileFormat::loadFrom(juce::File("../BackGround.png"));
    //Background Colour
   
    g.drawImageAt(backgroundImage, 0, 0, false);
    
    //Wooden Frame
    
    g.drawImage(woodenFrame, frameArea, juce::RectanglePlacement::stretchToFit,false);
    //g.drawImageAt(woodenFrame, 0, 0, false);
    //g.drawImage()
    g.setOpacity(1.0f);
    g.drawFittedText("MIX", juce::Rectangle<int>(2 * getWidth() / 12 - 10, 1.75 * getHeight() / 6-100, 120, 150), juce::Justification::centred, 1, 1.0f);
    //g.drawRect(2 * getWidth() / 12 - 10, 1.75 * getHeight() / 6, 120, 120);
    g.drawFittedText("FEEDBACK", juce::Rectangle<int>(5 * getWidth() / 12 - 10, 1.75 * getHeight() / 6 - 100, 120, 150), juce::Justification::centred, 1, 1.0f);
    g.drawFittedText("TIME", juce::Rectangle<int>(8 * getWidth() / 12 - 10, 1.75 * getHeight() / 6 - 100, 120, 150), juce::Justification::centred, 1, 1.0f);

    g.setFont(30.0f);
    //g.drawRect(2* getWidth() / 12 - 10, 3.5 * getHeight() / 6, 8 * getWidth() / 12+15, 150);
    g.drawFittedText("DELAY", juce::Rectangle<int>(2 * getWidth() / 12 - 10, 3.5 * getHeight() / 6 , 8 * getWidth() / 12+15, 150), juce::Justification::centred, 1, 1.0f);

}

void FXRackAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    int knobSize = 120;
    
    //areaToPlayWith = getLocalBounds().removeFromLeft(100).removeFromTop(50);
    //currentArea= areaToPlayWith = area.removeFromLeft(100).removeFromTop(50);
    wetnessSlider.setBounds(2*getWidth()/12-10, 1.75*getHeight()/6, knobSize, knobSize);
    wetnessLabel.setBounds(500,200,400,400);
    feedbackSlider.setBounds(5 * getWidth() / 12-10, 1.75 * getHeight() / 6,knobSize,knobSize);
    delayTimeSlider.setBounds(8 * getWidth() / 12-10, 1.75 * getHeight() / 6,knobSize,knobSize);
    //wetnessLabel.setBounds(getLocalBounds().removeFromBottom(20));
}
