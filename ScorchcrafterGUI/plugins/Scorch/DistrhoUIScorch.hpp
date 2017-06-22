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

#ifndef DISTRHO_UI_3BANDEQ_HPP_INCLUDED
#define DISTRHO_UI_3BANDEQ_HPP_INCLUDED

#include "DistrhoUI.hpp"
#include "ImageWidgets.hpp"

#include "DistrhoArtworkScorch.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class ScorchUI : public UI,
                         public ImageKnob::Callback, public ImageSwitch::Callback
{
public:
    ScorchUI();

protected:
    // -------------------------------------------------------------------
    // DSP Callbacks

    void parameterChanged(uint32_t index, float value) override;
    void programLoaded(uint32_t index) override;

    // -------------------------------------------------------------------
    // Widget Callbacks

    void imageKnobDragStarted(ImageKnob* knob) override;
    void imageKnobDragFinished(ImageKnob* knob) override;
    void imageKnobValueChanged(ImageKnob* knob, float value) override;

    void imageSwitchClicked(ImageSwitch* imageSwitch, bool down) override;


    void onDisplay() override;

private:
    Image fImgBackground;

     ScopedPointer<ImageKnob>   fKnobNoise, fKnobBass, fKnobMid, fKnobTreble, fKnobPresence, fKnobContour, fKnobMaster, fKnobGain;

    ScopedPointer<ImageSwitch> fSwitchBright, fSwitchNoise, fSwitchBoost, fSwitchChannel[9];

 
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScorchUI)
};


// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_3BANDEQ_HPP_INCLUDED
