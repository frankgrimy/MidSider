//#include "PluginProcessor.h"
//#include "PluginEditor.h"

#include "MidSider/PluginProcessor.h"
#include "MidSider/PluginEditor.h"

//==============================================================================
MidSiderAudioProcessor::MidSiderAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                       apvts(*this, nullptr, "Parameters", createParameterLayout())
#endif
{
    apvts.addParameterListener("bypass", this);
    apvts.addParameterListener("stereoMidSide", this);
}

// Parameter Layout

juce::AudioProcessorValueTreeState::ParameterLayout MidSiderAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Stereo, Mid, Side, Left to Mono, Right to Mono
    
    //params.reserve(2);

    auto pStereoMidSide = std::make_unique<juce::AudioParameterChoice>("stereoMidSide", "Listening mode", juce::StringArray("Stereo", "Mid", "Side", "Left to Mono", "Right to Mono"), 0);
    auto pBypass = std::make_unique<juce::AudioParameterBool>("bypass", "Bypass", false);

    params.push_back(std::move(pStereoMidSide));
    params.push_back(std::move(pBypass));

    return { params.begin(), params.end() };

}

void MidSiderAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "stereoMidSide")
    {
        stereoMidSideIndex = newValue;
    }
    else if (parameterID == "bypass")
    {
        bypassPlugin = newValue;
    }
}

MidSiderAudioProcessor::~MidSiderAudioProcessor()
{
    apvts.removeParameterListener("bypass", this);
    apvts.removeParameterListener("stereoMidSide", this);
}

//==============================================================================

//==============================================================================
const juce::String MidSiderAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidSiderAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidSiderAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidSiderAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidSiderAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidSiderAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidSiderAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidSiderAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MidSiderAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidSiderAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MidSiderAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    stereoMidSideIndex = *apvts.getRawParameterValue("stereoMidSide");
    bypassPlugin = *apvts.getRawParameterValue("bypass");
}

void MidSiderAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidSiderAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MidSiderAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    /* for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
    } */

    auto* leftChannel = buffer.getWritePointer(0);
    auto* rightChannel = buffer.getWritePointer(1);
    
    if (!bypassPlugin) {
        for (int sample = 0; sample < buffer.getNumSamples(); ++ sample)
        {
            if (stereoMidSideIndex == 0) // Stereo
            {
                // Do nothing
            }
            else if (stereoMidSideIndex == 1) // Mid
            {
                float midChannel = (leftChannel[sample] + rightChannel[sample]) / 2;
                leftChannel[sample] = midChannel;
                rightChannel[sample] = midChannel;
            }
            else if (stereoMidSideIndex == 2) // Side
            {
                float sideChannel = (leftChannel[sample] - rightChannel[sample]) / 2;
                leftChannel[sample] = sideChannel;
                rightChannel[sample] = -sideChannel;
            }
            else if (stereoMidSideIndex == 3) // Left to Mono
            {
                float monoChannel = (leftChannel[sample] + rightChannel[sample]) / 2;
                leftChannel[sample] = monoChannel;
                rightChannel[sample] = monoChannel;
            }
            else if (stereoMidSideIndex == 4) // Right to Mono
            {
                float monoChannel = (leftChannel[sample] + rightChannel[sample]) / 2;
                leftChannel[sample] = monoChannel;
                rightChannel[sample] = monoChannel;
            }
        }
    }
    else {
        // Do nothing
    }
}

//==============================================================================
bool MidSiderAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MidSiderAudioProcessor::createEditor()
{
    return new MidSiderAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void MidSiderAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::MemoryOutputStream stream(destData, false);
    apvts.state.writeToStream(stream);
}

void MidSiderAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        apvts.state = tree;
        stereoMidSideIndex = *apvts.getRawParameterValue("stereoMidSide");
        bypassPlugin = *apvts.getRawParameterValue("bypass");
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidSiderAudioProcessor();
}