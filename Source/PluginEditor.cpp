/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidSiderAudioProcessorEditor::MidSiderAudioProcessorEditor (MidSiderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (250, 85);
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(2.941176470588235);
    setResizeLimits(250, 85, 750, 255);
    startTimerHz(5);

    addAndMakeVisible(&stereo);
    stereo.setButtonText("Stereo");
    stereo.onClick = [this]() {
      audioProcessor.setStereoMidSideIndex(0);
      };

    addAndMakeVisible(&mid);
    mid.setButtonText("Mid");
    mid.onClick = [this]() {
      audioProcessor.setStereoMidSideIndex(1);
      };

    addAndMakeVisible(&side);
    side.setButtonText("Side");
    side.onClick = [this]() {
      audioProcessor.setStereoMidSideIndex(2);
      };

    addAndMakeVisible(&left2Mono);
    left2Mono.setButtonText("L->Mono");
    left2Mono.onClick = [this]() {
      audioProcessor.setStereoMidSideIndex(3);
      };

    addAndMakeVisible(&right2Mono);
    right2Mono.setButtonText("R->Mono");
    right2Mono.onClick = [this]() {
      audioProcessor.setStereoMidSideIndex(4);
      };

    addAndMakeVisible(&bypassToggle);
    bypassToggle.onClick = [this]() {
      audioProcessor.setBypassPlugin(bypassToggle.getToggleState());
      };
    addAndMakeVisible(&bypassLabel);
    bypassLabel.setText("Bypass", juce::dontSendNotification);


}

MidSiderAudioProcessorEditor::~MidSiderAudioProcessorEditor()
{

}

//==============================================================================
void MidSiderAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    g.setFont(juce::Font("Calibri", getWidth() * 0.048f, juce::Font::bold));
    g.drawFittedText ("MidSider\nby Frank Grimy", getLocalBounds(), juce::Justification::centredBottom, 1);

    buttonPaint();

}

void MidSiderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    int windowX = getWidth();
    int windowY = getHeight();

    int buttonSize = windowX/5;

    stereo.setSize(buttonSize, buttonSize);
    stereo.setTopLeftPosition(0, 0);
    
    mid.setSize(buttonSize, buttonSize);
    mid.setTopLeftPosition(stereo.getRight(), 0);

    side.setSize(buttonSize, buttonSize);
    side.setTopLeftPosition(mid.getRight(), 0);

    left2Mono.setSize(buttonSize, buttonSize);
    left2Mono.setTopLeftPosition(side.getRight(), 0);

    right2Mono.setSize(buttonSize, buttonSize);
    right2Mono.setTopLeftPosition(left2Mono.getRight(), 0);

    bypassToggle.setSize(30, 30);
    bypassToggle.setTopLeftPosition(0, windowY - bypassToggle.getHeight());
    
    bypassLabel.setFont(juce::Font("Calibri", getWidth() * 0.040f, juce::Font::plain));
    bypassLabel.setSize(windowX * 0.24, 30);
    bypassLabel.setTopLeftPosition(20, windowY - 30);

}
