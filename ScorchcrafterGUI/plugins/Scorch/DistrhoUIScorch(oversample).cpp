/*
 * DISTRHO 3BandEQ Plugin, based on 3BandEQ by Michael Gruhn
 * Copyright (C) 2012-2015 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * For a full copy of the license see the LICENSE file.
 */

#include "DistrhoUIScorch.hpp"

START_NAMESPACE_DISTRHO

#define paramSampon 0

#define paramNoise 13

#define paramBass 7

#define paramMid 8

#define paramTreble 9

#define paramPresence 10

#define paramContour 11

#define paramMaster 2

#define paramGain 4

#define paramBright 5

#define paramChannel 6

#define paramBoost 3

#define paramNoiseSw 12

namespace Art = DistrhoArtworkScorch;

// -----------------------------------------------------------------------

ScorchUI::ScorchUI()
    : UI(Art::backgroundWidth, Art::backgroundHeight),
      fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight)
{

int idx;

    // knobs
    Image knobImage(Art::knobData, Art::knobWidth, Art::knobHeight);

    fKnobNoise = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobNoise->setId(paramNoise);
    fKnobNoise->setAbsolutePos(19, 136);
    fKnobNoise->setRange(0.0f, 1.0f);
    fKnobNoise->setDefault(0.5f);
    fKnobNoise->setRotationAngle(270);
    fKnobNoise->setCallback(this);

    fKnobBass = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobBass->setId(paramBass);
    fKnobBass->setAbsolutePos(115, 136);
    fKnobBass->setRange(0.0f, 1.0f);
    fKnobBass->setDefault(0.5f);
    fKnobBass->setRotationAngle(270);
    fKnobBass->setCallback(this);

    fKnobMid = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobMid->setId(paramMid);
    fKnobMid->setAbsolutePos(195, 136);
    fKnobMid->setRange(0.0f, 1.0f);
    fKnobMid->setDefault(0.5f);
    fKnobMid->setRotationAngle(270);
    fKnobMid->setCallback(this);

    fKnobTreble = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobTreble->setId(paramTreble);
    fKnobTreble->setAbsolutePos(275, 136);
    fKnobTreble->setRange(0.0f, 1.0f);
    fKnobTreble->setDefault(0.5f);
    fKnobTreble->setRotationAngle(270);
    fKnobTreble->setCallback(this);

    fKnobPresence = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobPresence->setId(paramPresence);
    fKnobPresence->setAbsolutePos(355, 136);
    fKnobPresence->setRange(0.0f, 1.0f);
    fKnobPresence->setDefault(0.5f);
    fKnobPresence->setRotationAngle(270);
    fKnobPresence->setCallback(this);

    fKnobContour = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobContour->setId(paramContour);
    fKnobContour->setAbsolutePos(435, 136);
    fKnobContour->setRange(0.0f, 1.0f);
    fKnobContour->setDefault(0.5f);
    fKnobContour->setRotationAngle(270);
    fKnobContour->setCallback(this);

    fKnobMaster = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobMaster->setId(paramMaster);
    fKnobMaster->setAbsolutePos(19, 248);
    fKnobMaster->setRange(0.0f, 1.0f);
    fKnobMaster->setDefault(0.5f);
    fKnobMaster->setRotationAngle(270);
    fKnobMaster->setCallback(this);

    fKnobGain = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobGain->setId(paramGain);
    fKnobGain->setAbsolutePos(99, 248);
    fKnobGain->setRange(0.0f, 1.0f);
    fKnobGain->setDefault(0.5f);
    fKnobGain->setRotationAngle(270);
    fKnobGain->setCallback(this);

    Image switchImageNormal(Art::switchData, Art::switchWidth, Art::switchHeight/2);

    Image switchImageDown(Art::switchData+(Art::switchWidth*Art::switchHeight/2*4), Art::switchWidth, Art::switchHeight/2);

    fSwitchBright = new ImageSwitch(this, switchImageNormal, switchImageDown);

    fSwitchBright->setAbsolutePos(213, 243);

    fSwitchBright->setId(paramBright);
    fSwitchBright->setCallback(this);

    fSwitchNoise = new ImageSwitch(this, switchImageNormal, switchImageDown);

    fSwitchNoise->setAbsolutePos(16, 128);

    fSwitchNoise->setId(paramNoiseSw);
    fSwitchNoise->setCallback(this);

    fSwitchBoost = new ImageSwitch(this, switchImageNormal, switchImageDown);

    fSwitchBoost->setAbsolutePos(213, 259);

    fSwitchBoost->setId(paramBoost);
    fSwitchBoost->setCallback(this);

    for(idx=0;idx<9;idx++)
    {
    fSwitchChannel[idx] = new ImageSwitch(this, switchImageNormal, switchImageDown);

    if(idx <= 2)
    fSwitchChannel[idx]->setAbsolutePos(213, 287 + (idx * 16));
    else if (idx >= 3 && idx <= 5)
    fSwitchChannel[idx]->setAbsolutePos(261, 287 + ((idx - 3) * 16));
    else if(idx >=6 && idx < 9)
    fSwitchChannel[idx]->setAbsolutePos(309, 287 + ((idx - 6) * 16));

    fSwitchChannel[idx]->setId(paramChannel);
    fSwitchChannel[idx]->setCallback(this);
    }

    for(idx=0;idx<6;idx++)
    {
    fSwitchSampon[idx] = new ImageSwitch(this, switchImageNormal, switchImageDown);
    if(idx <= 2)
    fSwitchSampon[idx]->setAbsolutePos(412, 287 + (idx * 16));
    else if (idx >= 3 && idx <= 5)
    fSwitchSampon[idx]->setAbsolutePos(478, 287 + ((idx - 3) * 16));

    fSwitchSampon[idx]->setId(paramSampon);
    fSwitchSampon[idx]->setCallback(this);
    }

    // set default values
   // programLoaded(0);
}

// -----------------------------------------------------------------------
// DSP Callbacks

void ScorchUI::parameterChanged(uint32_t index, float value)
{
int idx;

    switch (index)
    {
    case paramNoise:
        fKnobNoise->setValue(value);
        break;
    case paramBass:
        fKnobBass->setValue(value);
        break;
    case paramMid:
        fKnobMid->setValue(value);
        break;
    case paramTreble:
        fKnobTreble->setValue(value);
        break;
    case paramPresence:
        fKnobPresence->setValue(value);
        break;
    case paramContour:
        fKnobContour->setValue(value);
        break;
    case paramMaster:
        fKnobMaster->setValue(value);
        break;
    case paramGain:
        fKnobGain->setValue(value);
        break;
    case paramBright:
        fSwitchBright->setDown(value > 0.5f);
        break;
    case paramNoiseSw:
        fSwitchNoise->setDown(value > 0.5f);
        break;
    case paramBoost:
        fSwitchBoost->setDown(value > 0.5f);
        break;
    case paramChannel:

for(idx=0;idx<9;idx++)
{
fSwitchChannel[idx]->setDown(0.0f);
}

if(value < 0.05f)
fSwitchChannel[0]->setDown(1.0f);
else if ((value >= 0.05f) && (value < 0.15f))
fSwitchChannel[1]->setDown(1.0f);
else if ((value >= 0.15f) && (value < 0.25f))
fSwitchChannel[2]->setDown(1.0f);
else if ((value >= 0.25f) && (value < 0.35f))
fSwitchChannel[3]->setDown(1.0f);
else if ((value >= 0.35f) && (value < 0.45f))
fSwitchChannel[4]->setDown(1.0f);
else if ((value >= 0.45f) && (value < 0.55f))
fSwitchChannel[5]->setDown(1.0f);
else if ((value >= 0.55f) && (value < 0.65f))
fSwitchChannel[6]->setDown(1.0f);
else if ((value >= 0.65f) && (value < 0.75f))
fSwitchChannel[7]->setDown(1.0f);
else if ((value >= 0.75f) && (value < 0.85f))
fSwitchChannel[8]->setDown(1.0f);

        break;

    case paramSampon:

for(idx=0;idx<6;idx++)
{
fSwitchSampon[idx]->setDown(0.0f);
}

if(value == 0.01f)
fSwitchSampon[0]->setDown(1.0f);
else if(value == 0.02f)
fSwitchSampon[1]->setDown(1.0f);
else if(value == 0.03f)
fSwitchSampon[2]->setDown(1.0f);
else if(value == 0.04f)
fSwitchSampon[3]->setDown(1.0f);
else if(value == 0.05f)
fSwitchSampon[4]->setDown(1.0f);
else if(value == 0.06f)
fSwitchSampon[5]->setDown(1.0f);

        break;

    }
}

void ScorchUI::programLoaded2(uint32_t index, float value)
{
int idx;

    switch (index)
    {
    case paramNoise:
        fKnobNoise->setValue(value);
        break;
    case paramBass:
        fKnobBass->setValue(value);
        break;
    case paramMid:
        fKnobMid->setValue(value);
        break;
    case paramTreble:
        fKnobTreble->setValue(value);
        break;
    case paramPresence:
        fKnobPresence->setValue(value);
        break;
    case paramContour:
        fKnobContour->setValue(value);
        break;
    case paramMaster:
        fKnobMaster->setValue(value);
        break;
    case paramGain:
        fKnobGain->setValue(value);
        break;
    case paramBright:
        fSwitchBright->setDown(value > 0.5f);
        break;
    case paramNoiseSw:
        fSwitchNoise->setDown(value > 0.5f);
        break;
    case paramBoost:
        fSwitchBoost->setDown(value > 0.5f);
        break;
    case paramChannel:

for(idx=0;idx<9;idx++)
{
fSwitchChannel[idx]->setDown(0.0f);
}

if(value < 0.05f)
fSwitchChannel[0]->setDown(1.0f);
else if ((value >= 0.05f) && (value < 0.15f))
fSwitchChannel[1]->setDown(1.0f);
else if ((value >= 0.15f) && (value < 0.25f))
fSwitchChannel[2]->setDown(1.0f);
else if ((value >= 0.25f) && (value < 0.35f))
fSwitchChannel[3]->setDown(1.0f);
else if ((value >= 0.35f) && (value < 0.45f))
fSwitchChannel[4]->setDown(1.0f);
else if ((value >= 0.45f) && (value < 0.55f))
fSwitchChannel[5]->setDown(1.0f);
else if ((value >= 0.55f) && (value < 0.65f))
fSwitchChannel[6]->setDown(1.0f);
else if ((value >= 0.65f) && (value < 0.75f))
fSwitchChannel[7]->setDown(1.0f);
else if ((value >= 0.75f) && (value < 0.85f))
fSwitchChannel[8]->setDown(1.0f);

        break;

    case paramSampon:

for(idx=0;idx<6;idx++)
{
fSwitchSampon[idx]->setDown(0.0f);
}

if(value == 0.01f)
fSwitchSampon[0]->setDown(1.0f);
else if(value == 0.02f)
fSwitchSampon[1]->setDown(1.0f);
else if(value == 0.03f)
fSwitchSampon[2]->setDown(1.0f);
else if(value == 0.04f)
fSwitchSampon[3]->setDown(1.0f);
else if(value == 0.05f)
fSwitchSampon[4]->setDown(1.0f);
else if(value == 0.06f)
fSwitchSampon[5]->setDown(1.0f);

        break;

    }
}


void ScorchUI::programLoaded(uint32_t index)
{

}

// -----------------------------------------------------------------------
// Widget Callbacks


void ScorchUI::imageKnobDragStarted(ImageKnob* knob)
{
    editParameter(knob->getId(), true);
}

void ScorchUI::imageKnobDragFinished(ImageKnob* knob)
{
    editParameter(knob->getId(), false);
}

void ScorchUI::imageKnobValueChanged(ImageKnob* knob, float value)
{
    setParameterValue(knob->getId(), value);
}

void ScorchUI::imageSwitchClicked(ImageSwitch* imageSwitch, bool down)
{

int channelhit; 
int samponhit;
int idx;

    if(imageSwitch == fSwitchBright)
    {
    editParameter(paramBright, true);
    setParameterValue(paramBright, down ? 1.0f : 0.0f);
    editParameter(paramBright, false);
    return;
    } 

    if(imageSwitch == fSwitchNoise)
    {
    editParameter(paramNoiseSw, true);
    setParameterValue(paramNoiseSw, down ? 1.0f : 0.0f);
    editParameter(paramNoiseSw, false);
    return;
    } 

    if(imageSwitch == fSwitchBoost)
    {
    editParameter(paramBoost, true);
    setParameterValue(paramBoost, down ? 1.0f : 0.0f);
    editParameter(paramBoost, false);
    return;
    } 

    channelhit = 0;

    for(idx=0;idx<9;idx++)
    {
    if(imageSwitch == fSwitchChannel[idx])
    channelhit = 1;
    }
  
    if(channelhit == 1)
    {
    for(idx=0;idx<9;idx++)
    {
    fSwitchChannel[idx]->setDown(0.0f);
    }

    if(imageSwitch == fSwitchChannel[0])
    {
    editParameter(paramChannel, true);
    setParameterValue(paramChannel, down ? 0.0f : 0.0f);
    editParameter(paramChannel, false);

    fSwitchChannel[0]->setDown(1.0f);
 
    }
    else if (imageSwitch == fSwitchChannel[1])
    {
    editParameter(paramChannel, true);
    setParameterValue(paramChannel, down ? 0.05f : 0.0f);
    editParameter(paramChannel, false);

    fSwitchChannel[1]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchChannel[2])
    {
    editParameter(paramChannel, true);
    setParameterValue(paramChannel, down ? 0.15f : 0.0f);
    editParameter(paramChannel, false);

    fSwitchChannel[2]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchChannel[3])
    {
    editParameter(paramChannel, true);
    setParameterValue(paramChannel, down ? 0.25f : 0.0f);
    editParameter(paramChannel, false);

    fSwitchChannel[3]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchChannel[4])
    {
    editParameter(paramChannel, true);
    setParameterValue(paramChannel, down ? 0.35f : 0.0f);
    editParameter(paramChannel, false);

    fSwitchChannel[4]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchChannel[5])
    {
    editParameter(paramChannel, true);
    setParameterValue(paramChannel, down ? 0.45f : 0.0f);
    editParameter(paramChannel, false);

    fSwitchChannel[5]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchChannel[6])
    {
    editParameter(paramChannel, true);
    setParameterValue(paramChannel, down ? 0.55f : 0.0f);
    editParameter(paramChannel, false);

    fSwitchChannel[6]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchChannel[7])
    {
    editParameter(paramChannel, true);
    setParameterValue(paramChannel, down ? 0.65f : 0.0f);
    editParameter(paramChannel, false);

    fSwitchChannel[7]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchChannel[8])
    {
    editParameter(paramChannel, true);
    setParameterValue(paramChannel, down ? 0.75f : 0.0f);
    editParameter(paramChannel, false);

    fSwitchChannel[8]->setDown(1.0f);

    }

   }

    samponhit = 0;

    for(idx=0;idx<6;idx++)
    {
    if(imageSwitch == fSwitchSampon[idx])
    samponhit = 1;
    }

    if(samponhit == 1)
    {
    for(idx=0;idx<6;idx++)
    {
    fSwitchSampon[idx]->setDown(0.0f);
    }

    if(imageSwitch == fSwitchSampon[0])
    {
    editParameter(paramSampon, true);
    setParameterValue(paramSampon, down ? 0.01f : 0.0f);
    editParameter(paramSampon, false);

    fSwitchSampon[0]->setDown(1.0f);
 
    }
    else if (imageSwitch == fSwitchSampon[1])
    {
    editParameter(paramSampon, true);
    setParameterValue(paramSampon, down ? 0.02f : 0.0f);
    editParameter(paramSampon, false);

    fSwitchSampon[1]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchSampon[2])
    {
    editParameter(paramSampon, true);
    setParameterValue(paramSampon, down ? 0.03f : 0.0f);
    editParameter(paramSampon, false);

    fSwitchSampon[2]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchSampon[3])
    {
    editParameter(paramSampon, true);
    setParameterValue(paramSampon, down ? 0.04f : 0.0f);
    editParameter(paramSampon, false);

    fSwitchSampon[3]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchSampon[4])
    {
    editParameter(paramSampon, true);
    setParameterValue(paramSampon, down ? 0.05f : 0.0f);
    editParameter(paramSampon, false);

    fSwitchSampon[4]->setDown(1.0f);

    }
    else if (imageSwitch == fSwitchSampon[5])
    {
    editParameter(paramSampon, true);
    setParameterValue(paramSampon, down ? 0.06f : 0.0f);
    editParameter(paramSampon, false);

    fSwitchSampon[5]->setDown(1.0f);

    }

   }


}


void ScorchUI::onDisplay()
{
    fImgBackground.draw();
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new ScorchUI();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
