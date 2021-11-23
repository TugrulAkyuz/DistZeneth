/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistZenethAudioProcessorEditor::DistZenethAudioProcessorEditor (DistZenethAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::BACKGROUND_png, BinaryData::BACKGROUND_pngSize);
    float ratio = 0.5;
    auto w = ratio*backgroundImage.getWidth();
    auto h = ratio*backgroundImage.getHeight();
   
    backgroundImage = backgroundImage.rescaled(w, h, juce::Graphics::ResamplingQuality::highResamplingQuality);

    res.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    res.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
  
    res.setLookAndFeel(&otherLookAndFeel);
    

    dist.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dist.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    dist.setLookAndFeel(&otherLookAndFeel);

    cut.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cut.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    cut.setLookAndFeel(&otherLookAndFeelbig);



    emp.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    emp.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    emp.setLookAndFeel(&otherLookAndFeelvertical);

    addAndMakeVisible(res);
    addAndMakeVisible(cut);
    addAndMakeVisible(dist);
    addAndMakeVisible(emp);
    setSize (w , h);
}

DistZenethAudioProcessorEditor::~DistZenethAudioProcessorEditor()
{
    res.setLookAndFeel(nullptr);
    dist.setLookAndFeel(nullptr);
    cut.setLookAndFeel(nullptr);
    emp.setLookAndFeel(nullptr);
   
}

//==============================================================================
void DistZenethAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    //auto Image background = ImageCache::getFromMemory(BinaryData::filename_ext, BinaryData::filename_extSize);
    
    g.drawImageAt(backgroundImage, 0, 0);
}

void DistZenethAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   
    res.setBounds(175, 265, 220, 220);
    dist.setBounds(175 + 330, 265, 220, 220);
    cut.setBounds(175 + 145, 250, 220, 220);
    emp.setBounds(getWidth()-165, getHeight() - 70, 110, 30);
}
