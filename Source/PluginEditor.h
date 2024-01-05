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
class MidSiderAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MidSiderAudioProcessorEditor (MidSiderAudioProcessor&);
    ~MidSiderAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonPaint(){
    if (audioProcessor.getStereoMidSideIndex() == 0)
    {
      stereo.setToggleState(true, juce::dontSendNotification);
      mid.setToggleState(false, juce::dontSendNotification);
      side.setToggleState(false, juce::dontSendNotification);
      left2Mono.setToggleState(false, juce::dontSendNotification);
      right2Mono.setToggleState(false, juce::dontSendNotification);
    }
    else if (audioProcessor.getStereoMidSideIndex() == 1)
    {
      stereo.setToggleState(false, juce::dontSendNotification);
      mid.setToggleState(true, juce::dontSendNotification);
      side.setToggleState(false, juce::dontSendNotification);
      left2Mono.setToggleState(false, juce::dontSendNotification);
      right2Mono.setToggleState(false, juce::dontSendNotification);
    }
    else if (audioProcessor.getStereoMidSideIndex() == 2)
    {
      stereo.setToggleState(false, juce::dontSendNotification);
      mid.setToggleState(false, juce::dontSendNotification);
      side.setToggleState(true, juce::dontSendNotification);
      left2Mono.setToggleState(false, juce::dontSendNotification);
      right2Mono.setToggleState(false, juce::dontSendNotification);
    }
    else if (audioProcessor.getStereoMidSideIndex() == 3)
    {
      stereo.setToggleState(false, juce::dontSendNotification);
      mid.setToggleState(false, juce::dontSendNotification);
      side.setToggleState(false, juce::dontSendNotification);
      left2Mono.setToggleState(true, juce::dontSendNotification);
      right2Mono.setToggleState(false, juce::dontSendNotification);
    }
    else if (audioProcessor.getStereoMidSideIndex() == 4)
    {
      stereo.setToggleState(false, juce::dontSendNotification);
      mid.setToggleState(false, juce::dontSendNotification);
      side.setToggleState(false, juce::dontSendNotification);
      left2Mono.setToggleState(false, juce::dontSendNotification);
      right2Mono.setToggleState(true, juce::dontSendNotification);
    };
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidSiderAudioProcessor& audioProcessor;

    juce::TextButton stereo, mid, side, left2Mono, right2Mono;
    //juce::Label stereoLabel, midLabel, sideLabel, left2MonoLabel, right2MonoLabel;

    juce::ToggleButton bypassToggle;
    juce::Label bypassLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidSiderAudioProcessorEditor)
};
