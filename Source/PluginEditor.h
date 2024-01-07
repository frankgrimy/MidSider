#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MidSiderAudioProcessorEditor  : public juce::AudioProcessorEditor/* ,
                                      private juce::Timer */
{
public:
    MidSiderAudioProcessorEditor (MidSiderAudioProcessor&);
    ~MidSiderAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void stereoPaint(){
        stereo.setToggleState(true, juce::dontSendNotification);
        mid.setToggleState(false, juce::dontSendNotification);
        side.setToggleState(false, juce::dontSendNotification);
        left2Mono.setToggleState(false, juce::dontSendNotification);
        right2Mono.setToggleState(false, juce::dontSendNotification);
    }

    void midPaint(){
        stereo.setToggleState(false, juce::dontSendNotification);
        mid.setToggleState(true, juce::dontSendNotification);
        side.setToggleState(false, juce::dontSendNotification);
        left2Mono.setToggleState(false, juce::dontSendNotification);
        right2Mono.setToggleState(false, juce::dontSendNotification);
    }

    void sidePaint(){
        stereo.setToggleState(false, juce::dontSendNotification);
        mid.setToggleState(false, juce::dontSendNotification);
        side.setToggleState(true, juce::dontSendNotification);
        left2Mono.setToggleState(false, juce::dontSendNotification);
        right2Mono.setToggleState(false, juce::dontSendNotification);
    }

    void left2MonoPaint(){
        stereo.setToggleState(false, juce::dontSendNotification);
        mid.setToggleState(false, juce::dontSendNotification);
        side.setToggleState(false, juce::dontSendNotification);
        left2Mono.setToggleState(true, juce::dontSendNotification);
        right2Mono.setToggleState(false, juce::dontSendNotification);
    }

    void right2MonoPaint(){
        stereo.setToggleState(false, juce::dontSendNotification);
        mid.setToggleState(false, juce::dontSendNotification);
        side.setToggleState(false, juce::dontSendNotification);
        left2Mono.setToggleState(false, juce::dontSendNotification);
        right2Mono.setToggleState(true, juce::dontSendNotification);
    }

    /* void timerCallback() final {
        DBG(audioProcessor.apvts.getParameter("stereoMidSide")->getValue());
    } */


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidSiderAudioProcessor& audioProcessor;

    juce::TextButton stereo, mid, side, left2Mono, right2Mono;

    juce::ToggleButton bypassToggle;
    juce::Label bypassLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassToggleAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidSiderAudioProcessorEditor)
};
