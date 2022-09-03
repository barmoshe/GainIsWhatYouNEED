/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
 */
class GainIsWhatYouNEEDAudioProcessorEditor  : public juce::AudioProcessorEditor,
public juce::Slider::Listener
{
public:
    GainIsWhatYouNEEDAudioProcessorEditor (GainIsWhatYouNEEDAudioProcessor&);
    ~GainIsWhatYouNEEDAudioProcessorEditor() override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainIsWhatYouNEEDAudioProcessor& audioProcessor;
    juce::Slider gainSlider;
    public  :
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainIsWhatYouNEEDAudioProcessorEditor)
};
