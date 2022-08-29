/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainIsWhatYouNEEDAudioProcessorEditor::GainIsWhatYouNEEDAudioProcessorEditor (GainIsWhatYouNEEDAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (100, 200);
    //sliderAttach=new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, "gain", gainSlider);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    gainSlider.setRange(0.0, 1.0);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
}
void GainIsWhatYouNEEDAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    audioProcessor.rawVolume=gainSlider.getValue();
}
GainIsWhatYouNEEDAudioProcessorEditor::~GainIsWhatYouNEEDAudioProcessorEditor()
{
}

//==============================================================================
void GainIsWhatYouNEEDAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    gainSlider.setBounds(getLocalBounds());
}

void GainIsWhatYouNEEDAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


