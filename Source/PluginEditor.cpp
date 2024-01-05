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

    addAndMakeVisible(&stereo);
    //addAndMakeVisible(&stereoLabel);
    //stereoLabel.setText("Stereo", juce::dontSendNotification);
    //stereoLabel.setJustificationType(juce::Justification::centred);
    stereo.setButtonText("Stereo");
    stereo.onClick = [this] {
      audioProcessor.setStereoMidSideIndex(0);
      };

    addAndMakeVisible(&mid);
    //addAndMakeVisible(&midLabel);
    //midLabel.setText("Mid", juce::dontSendNotification);
    //midLabel.setJustificationType(juce::Justification::centred);
    mid.setButtonText("Mid");
    mid.onClick = [this] {
      audioProcessor.setStereoMidSideIndex(1);
      };

    addAndMakeVisible(&side);
    //addAndMakeVisible(&sideLabel);
    //sideLabel.setText("Side", juce::dontSendNotification);
    //sideLabel.setJustificationType(juce::Justification::centred);
    side.setButtonText("Side");
    side.onClick = [this] {
      audioProcessor.setStereoMidSideIndex(2);
      };

    addAndMakeVisible(&left2Mono);
    //addAndMakeVisible(&left2MonoLabel);
    //left2MonoLabel.setText("L->Mono", juce::dontSendNotification);
    //left2MonoLabel.setJustificationType(juce::Justification::centred);
    left2Mono.setButtonText("L->Mono");
    left2Mono.onClick = [this] {
      audioProcessor.setStereoMidSideIndex(3);
      };

    addAndMakeVisible(&right2Mono);
    //addAndMakeVisible(&right2MonoLabel);
    //right2MonoLabel.setJustificationType(juce::Justification::centred);
    //right2MonoLabel.setText("R->Mono", juce::dontSendNotification);
    right2Mono.setButtonText("R->Mono");
    right2Mono.onClick = [this] {
      audioProcessor.setStereoMidSideIndex(4);
      };

    addAndMakeVisible(&bypassToggle);
    bypassToggle.onClick = [this] {
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
    // stereoLabel.setSize(buttonSize, buttonSize);
    // stereoLabel.setFont(juce::Font("Calibri", windowX * 0.048f, juce::Font::plain));
    // stereoLabel.setTopLeftPosition(0, 0);
    
    mid.setSize(buttonSize, buttonSize);
    mid.setTopLeftPosition(stereo.getRight(), 0);
    // midLabel.setSize(buttonSize, buttonSize);
    // midLabel.setFont(juce::Font("Calibri", windowX * 0.048f, juce::Font::plain));
    // midLabel.setTopLeftPosition(stereo.getRight(), 0);

    side.setSize(buttonSize, buttonSize);
    side.setTopLeftPosition(mid.getRight(), 0);
    // sideLabel.setSize(buttonSize, buttonSize);
    // sideLabel.setFont(juce::Font("Calibri", windowX * 0.048f, juce::Font::plain));
    // sideLabel.setTopLeftPosition(mid.getRight(), 0);

    left2Mono.setSize(buttonSize, buttonSize);
    left2Mono.setTopLeftPosition(side.getRight(), 0);
    // left2MonoLabel.setSize(buttonSize, buttonSize);
    // left2MonoLabel.setFont(juce::Font("Calibri", windowX * 0.048f, juce::Font::plain));
    // left2MonoLabel.setTopLeftPosition(side.getRight(), 0);

    right2Mono.setSize(buttonSize, buttonSize);
    right2Mono.setTopLeftPosition(left2Mono.getRight(), 0);
    // right2MonoLabel.setSize(buttonSize, buttonSize);
    // right2MonoLabel.setFont(juce::Font("Calibri", windowX * 0.048f, juce::Font::plain));
    // right2MonoLabel.setTopLeftPosition(left2Mono.getRight(), 0);

    //bypassToggle.setBounds(windowX - buttonSize, windowY - buttonSize, buttonSize, buttonSize);
    bypassToggle.setSize(30, 30);
    bypassToggle.setTopLeftPosition(0, windowY - bypassToggle.getHeight());
    
    //bypassLabel.attachToComponent(&bypassToggle, true);
    bypassLabel.setFont(juce::Font("Calibri", getWidth() * 0.040f, juce::Font::plain));
    bypassLabel.setSize(windowX * 0.24, 30);
    bypassLabel.setTopLeftPosition(20, windowY - 30);

}
