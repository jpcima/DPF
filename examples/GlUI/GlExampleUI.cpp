/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2019 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "DistrhoUI.hpp"
#include "ImageWidgets.hpp"
#include "Window.hpp"
#include "Artwork.hpp"

START_NAMESPACE_DISTRHO

class CairoExampleUI : public UI
{
public:
    CairoExampleUI()
        : UI(200, 200)
    {
        Image *knobSkin = new Image(
            Artwork::knobData,
            Artwork::knobWidth, Artwork::knobHeight);
        fKnobSkin = knobSkin;

        ImageKnob* knob = new ImageKnob(this, *knobSkin);
        fKnob = knob;

        
        // knob->setSize(100, 60);
        // knob->setSize(70, 90);
        knob->setSize(64, 64);
        knob->setAbsolutePos(10, 100);
        // knob->setRotationAngle(270);
        

        Image *buttonOn = new Image(
            Artwork::buttonOnData,
            Artwork::buttonOnWidth, Artwork::buttonOnHeight);
        fButtonOn = buttonOn;
        Image *buttonOff = new Image(
            Artwork::buttonOffData,
            Artwork::buttonOffWidth, Artwork::buttonOffHeight);
        fButtonOff = buttonOff;

        ImageButton* button = new ImageButton(this, *buttonOff, *buttonOn);
        fButton = button;
        button->setSize(50, 30);
        button->setAbsolutePos(100, 160);
    }

    ~CairoExampleUI()
    {
    }

    void onDisplay()
    {
    }

    void parameterChanged(uint32_t index, float value)
    {
        // unused
        (void)index;
        (void)value;
    }

private:
    ScopedPointer<Image> fKnobSkin;
    ScopedPointer<ImageKnob> fKnob;
    ScopedPointer<ImageButton> fButton;
    ScopedPointer<Image> fButtonOn;
    ScopedPointer<Image> fButtonOff;
};

UI* createUI()
{
    return new CairoExampleUI;
}

END_NAMESPACE_DISTRHO
