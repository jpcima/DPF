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

#include "DemoWidgetBanner.hpp"

#include "Cairo.hpp"
#include "Window.hpp"

static const char* banner =
"                                                                        "
"  *     *               *                                 *     *       "
"  **   **               *                           *     *     *       "
"  * * * *               *                                 *     *       "
"  *  *  *   ****    *** *   ****         *     *   **    ****   * ***   "
"  *     *       *  *   **  *    *        *     *    *     *     **   *  "
"  *     *   *****  *    *  ******        *  *  *    *     *     *    *  "
"  *     *  *    *  *    *  *             *  *  *    *     *     *    *  "
"  *     *  *   **  *   **  *    *        *  *  *    *     *  *  *    *  "
"  *     *   *** *   *** *   ****          ** **   *****    **   *    *  "
"                                                                        "
"                                                                        "
"                                                                        "
"                          *****   ****   *****                          "
"                           *   *  *   *  *                              "
"                           *   *  *   *  *                              "
"                           *   *  *   *  *                              "
"                           *   *  ****   ****                           "
"                           *   *  *      *                              "
"                           *   *  *      *                              "
"                           *   *  *      *                              "
"                          *****   *      *                              "
"                                                                        ";

enum
{
    rows = 23,
    columns = 72,
};

DemoWidgetBanner::DemoWidgetBanner(Widget* group)
    : Widget(group)
{
}

void DemoWidgetBanner::onDisplay()
{
    const GraphicsContext& gc = getParentWindow().getGraphicsContext();
    cairo_t* cr = gc.cairo;

    Point<int> pt = getAbsolutePos();
    Size<uint> sz = getSize();

    int x = pt.getX();
    int y = pt.getY();
    int w = sz.getWidth();
    int h = sz.getHeight();

    double diameter = (double)w / columns;
    double radius = 0.5 * diameter;
    double xoff = 0;
    double yoff = 0.5 * (h - rows * diameter);
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < columns; ++c)
        {
            Circle<float> dot(x + xoff + c * diameter,
                              y + yoff + r * diameter,
                              radius);

            char ch = banner[c + r * columns];
            if (ch != ' ')
                cairo_set_source_rgb(cr, 0.5, 0.9, 0.2);
            else
                cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);

            dot.draw(&gc);
        }
    }
}
