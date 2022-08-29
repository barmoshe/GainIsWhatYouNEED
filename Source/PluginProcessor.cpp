/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainIsWhatYouNEEDAudioProcessor::GainIsWhatYouNEEDAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

GainIsWhatYouNEEDAudioProcessor::~GainIsWhatYouNEEDAudioProcessor()
{
}

//==============================================================================
const juce::String GainIsWhatYouNEEDAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainIsWhatYouNEEDAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainIsWhatYouNEEDAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainIsWhatYouNEEDAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainIsWhatYouNEEDAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainIsWhatYouNEEDAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainIsWhatYouNEEDAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainIsWhatYouNEEDAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GainIsWhatYouNEEDAudioProcessor::getProgramName (int index)
{
    return {};
}

void GainIsWhatYouNEEDAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GainIsWhatYouNEEDAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    rawVolume=0.015;

    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GainIsWhatYouNEEDAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainIsWhatYouNEEDAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void GainIsWhatYouNEEDAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample=0; sample<buffer.getNumSamples(); sample++) {
            channelData[sample]=buffer.getSample(channel, sample)*rawVolume;
        }    }
}

//==============================================================================
bool GainIsWhatYouNEEDAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GainIsWhatYouNEEDAudioProcessor::createEditor()
{
    return new GainIsWhatYouNEEDAudioProcessorEditor (*this);
}

//==============================================================================
void GainIsWhatYouNEEDAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainIsWhatYouNEEDAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainIsWhatYouNEEDAudioProcessor();
}
