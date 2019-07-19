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

#include "DistrhoPluginInfo.h"

#include "DistrhoUI.hpp"

#include "Image.hpp"
#include "Window.hpp"
#include "extra/String.hpp"

#include "Artwork.hpp"

#ifdef DISTRHO_OS_WINDOWS
#include <windows.h>
#endif

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

class FileDialogExampleUI : public UI
{
public:
    FileDialogExampleUI()
        : UI(128, 128),
          fImageNonSelected(Artwork::FileChoiceData, Artwork::FileChoiceWidth, Artwork::FileChoiceHeight, GL_BGR),
          fImageSelected(Artwork::FileSuccessData, Artwork::FileSuccessWidth, Artwork::FileSuccessHeight, GL_BGR)
    {
    }

protected:
   /* --------------------------------------------------------------------------------------------------------
    * DSP/Plugin Callbacks */

   /**
      A parameter has changed on the plugin side.
      This is called by the host to inform the UI about parameter changes.
    */
    void parameterChanged(uint32_t index, float value) override
    {
    }

   /* --------------------------------------------------------------------------------------------------------
    * Widget Callbacks */

   /**
      The drawing function.
    */
    void onDisplay() override
    {
        if (fSelectedFile.length() == 0)
            fImageNonSelected.drawAt(0, 0);
        else
            fImageSelected.drawAt(0, 0);
    }

   /**
      A function called when a mouse button is pressed or released.
    */
    bool onMouse(const MouseEvent& ev) override
    {
        // Test for left-clicked + pressed first.
        if (ev.button != 1 || ! ev.press)
            return false;

        Window::FileBrowserOptions options;
        getParentWindow().openFileBrowser(options);

        return true;
    }

   /**
      The file selection callback.
    */
    void uiFileBrowserSelected(const char* filename) override
    {
        d_stdout("File was selected: %s", filename);

#ifdef DISTRHO_OS_WINDOWS
        OutputDebugStringA(("File was selected: " + String(filename)).buffer());
#endif

        fSelectedFile = filename;
        repaint();
    }

    // -------------------------------------------------------------------------------------------------------

private:
    Image fImageNonSelected;
    Image fImageSelected;
    String fSelectedFile;

   /**
      Set our UI class as non-copyable and add a leak detector just in case.
    */
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileDialogExampleUI)
};

/* ------------------------------------------------------------------------------------------------------------
 * UI entry point, called by DPF to create a new UI instance. */

UI* createUI()
{
    return new FileDialogExampleUI();
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
