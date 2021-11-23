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
using namespace juce;
class KnobLookAndFeel : public LookAndFeel_V4
{
public:
    Image myStrip;
    int width;
    KnobLookAndFeel()
    {
        setColour(Slider::thumbColourId, Colours::red);
        myStrip = ImageCache::getFromMemory(BinaryData::KNOBS_png, BinaryData::KNOBS_pngSize);

        float ratio = 1;
        auto w = ratio * myStrip.getWidth();
        auto h = ratio * myStrip.getHeight();
    
        myStrip = myStrip.rescaled(w, h, juce::Graphics::ResamplingQuality::highResamplingQuality);
        width = w;

    }
    
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {


        const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
        const int nFrames = myStrip.getHeight() / myStrip.getWidth(); // number of frames for vertical film strip
        const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0)); // current index from 0 --> nFrames-1

        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius - 1.0f;
        const float ry = centreY - radius /* - 1.0f*/;

        g.drawImage(myStrip, // image
            (int)rx, (int)ry, myStrip.getWidth(), myStrip.getWidth(),   // dest
            0, frameIdx * myStrip.getWidth(), myStrip.getWidth(), myStrip.getWidth()); // source



    }
  
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool, bool isButtonDown) override
    {
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;
      
        buttonArea.removeFromLeft(edge);
        buttonArea.removeFromTop(edge);

        // shadow
        g.setColour(Colours::darkgrey.withAlpha(0.5f));
        g.fillRect(buttonArea);

        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate(offset, offset);

        g.setColour(backgroundColour);
        g.fillRect(buttonArea);
    }
 
    

};


class KnobLookAndFeelBig : public LookAndFeel_V4
{
public:
    Image myStrip;
    int width;
    KnobLookAndFeelBig()
    {
        setColour(Slider::thumbColourId, Colours::red);
        myStrip = ImageCache::getFromMemory(BinaryData::KNOBS_png, BinaryData::KNOBS_pngSize);

        float ratio = 1.25f;
        auto w = ratio * myStrip.getWidth();
        auto h = ratio * myStrip.getHeight();

        myStrip = myStrip.rescaled(w, h, juce::Graphics::ResamplingQuality::highResamplingQuality);
        width = w;

    }

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {


        const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
        const int nFrames = myStrip.getHeight() / myStrip.getWidth(); // number of frames for vertical film strip
        const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0)); // current index from 0 --> nFrames-1

        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius - 1.0f;
        const float ry = centreY - radius /* - 1.0f*/;

        g.drawImage(myStrip, // image
            (int)rx, (int)ry, myStrip.getWidth(), myStrip.getWidth(),   // dest
            0, frameIdx * myStrip.getWidth(), myStrip.getWidth(), myStrip.getWidth()); // source



    }

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool, bool isButtonDown) override
    {
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;

        buttonArea.removeFromLeft(edge);
        buttonArea.removeFromTop(edge);

        // shadow
        g.setColour(Colours::darkgrey.withAlpha(0.5f));
        g.fillRect(buttonArea);

        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate(offset, offset);

        g.setColour(backgroundColour);
        g.fillRect(buttonArea);
    }



};


class KnobLookAndFeelVerical : public LookAndFeel_V4
{
public:
    Image myStrip;
    int i_width;
    KnobLookAndFeelVerical()
    {
        setColour(Slider::thumbColourId, Colours::red);
        myStrip = ImageCache::getFromMemory(BinaryData::SLIDER_FIXX_png, BinaryData::SLIDER_FIXX_pngSize);

        float ratio = 0.5;
        auto w = ratio * myStrip.getWidth();
        auto h = ratio * myStrip.getHeight();

        myStrip = myStrip.rescaled(w, h, juce::Graphics::ResamplingQuality::highResamplingQuality);
        i_width = w;

    }
   
    void drawLinearSlider(Graphics& g, int x, int y, int width,
        int height, float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override
        
    {
       // g.drawImage(myStrip, // image
        //    (int)sliderPos + x, (int)y, myStrip.getWidth(), myStrip.getWidth(),   // dest
        //    0, myStrip.getWidth(), myStrip.getWidth(), myStrip.getWidth()); // source
        int tmp = sliderPos - i_width / 2;
        if (tmp < 0) tmp = 0;

        if (sliderPos +  i_width/2 > width +2*x) tmp = width + 2 * x - i_width;
        g.drawImageAt(myStrip, tmp, 0);
        //LookAndFeel_V4::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
   
    void drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override
    {
        float kx, ky;

        if (style == Slider::LinearVertical)
        {
            kx = (float)x + (float)width * 0.5f;
            ky = sliderPos;
        }
        else
        {
            kx = sliderPos;
            ky = (float)y + (float)height * 0.5f;
        }


        g.drawImage(myStrip, // image
            (int)x, (int)y, myStrip.getWidth(), myStrip.getWidth(),   // dest
            0,  myStrip.getWidth(), myStrip.getWidth(), myStrip.getWidth()); // source
    }


    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {





    }

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool, bool isButtonDown) override
    {
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;

        buttonArea.removeFromLeft(edge);
        buttonArea.removeFromTop(edge);

        // shadow
        g.setColour(Colours::darkgrey.withAlpha(0.5f));
        g.fillRect(buttonArea);

        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate(offset, offset);

        g.setColour(backgroundColour);
        g.fillRect(buttonArea);
    }



};



class DistZenethAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DistZenethAudioProcessorEditor (DistZenethAudioProcessor&);
    ~DistZenethAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistZenethAudioProcessor& audioProcessor;
    juce::Image  backgroundImage;
    Slider res, cut, dist, emp;
    KnobLookAndFeel otherLookAndFeel;
    KnobLookAndFeelBig otherLookAndFeelbig;
    KnobLookAndFeelVerical otherLookAndFeelvertical;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistZenethAudioProcessorEditor)
};
