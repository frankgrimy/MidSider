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
    startTimerHz(10);

    //midSideStereoButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "midSideStereo", stereo);
    addAndMakeVisible(&stereo);
    stereo.setButtonText("Stereo");
    stereo.onClick = [this]() {
      audioProcessor.apvts.getParameter("stereoMidSide")->setValueNotifyingHost(0.0);
      //stereoPaint();
      };

    addAndMakeVisible(&mid);
    mid.setButtonText("Mid");
    mid.onClick = [this]() {
      audioProcessor.apvts.getParameter("stereoMidSide")->setValueNotifyingHost(0.20);
      //midPaint();
      };

    addAndMakeVisible(&side);
    side.setButtonText("Side");
    side.onClick = [this]() {
      audioProcessor.apvts.getParameter("stereoMidSide")->setValueNotifyingHost(0.59);
      //sidePaint();
      };

    addAndMakeVisible(&left2Mono);
    left2Mono.setButtonText("L->Mono");
    left2Mono.onClick = [this]() {
      audioProcessor.apvts.getParameter("stereoMidSide")->setValueNotifyingHost(0.79);
      //left2MonoPaint();
      };

    addAndMakeVisible(&right2Mono);
    right2Mono.setButtonText("R->Mono");
    right2Mono.onClick = [this]() {
      audioProcessor.apvts.getParameter("stereoMidSide")->setValueNotifyingHost(1);
      //right2MonoPaint();
      };

    addAndMakeVisible(&bypassToggle);
    bypassToggleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "bypass", bypassToggle);
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
    //buttonPaint();

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

void MidSiderAudioProcessorEditor::timerCallback() {

  //DBG(audioProcessor.apvts.getParameter("stereoMidSide")->getValue());
  if (audioProcessor.getStereoMidSideIndex() == 0) {
      stereoPaint();
  }
  else if (audioProcessor.getStereoMidSideIndex() == 1) {
      midPaint();
  }
  else if (audioProcessor.getStereoMidSideIndex() == 2) {
      sidePaint();
  }
  else if (audioProcessor.getStereoMidSideIndex() == 3) {
      left2MonoPaint();
  }
  else if (audioProcessor.getStereoMidSideIndex() == 4) {
      right2MonoPaint();
  }
}