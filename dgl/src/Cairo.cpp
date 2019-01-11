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

#include "../Geometry.hpp"
#include "../Cairo.hpp"

START_NAMESPACE_DGL

static const double m_2PI = 6.28318530717958647693;

// -----------------------------------------------------------------------
// Line

template<typename T>
void Line<T>::draw(const GraphicsContext* context)
{
    DISTRHO_SAFE_ASSERT_RETURN(fPosStart != fPosEnd,);

    cairo_t* cr = context->cairo;

    cairo_new_path(cr);
    cairo_move_to(cr, fPosStart.fX, fPosStart.fY);
    cairo_line_to(cr, fPosEnd.fX, fPosEnd.fY);

    cairo_stroke(cr);
}

// -----------------------------------------------------------------------
// Circle

template<typename T>
void Circle<T>::_draw(const GraphicsContext* context, const bool outline)
{
    cairo_t* cr = context->cairo;

    cairo_save(cr);
    cairo_translate(cr, fPos.fX, fPos.fY);
    cairo_scale(cr, fSize, fSize);
    cairo_arc(cr, 0.0, 0.0, 1.0, 0.0, m_2PI);
    cairo_restore(cr);

    (outline ? cairo_stroke : cairo_fill)(cr);
}

// -----------------------------------------------------------------------
// Triangle

template<typename T>
void Triangle<T>::_draw(const GraphicsContext* context, const bool outline)
{
    DISTRHO_SAFE_ASSERT_RETURN(fPos1 != fPos2 && fPos1 != fPos3,);

    cairo_t* cr = context->cairo;

    cairo_new_path(cr);
    cairo_move_to(cr, fPos1.fX, fPos1.fY);
    cairo_line_to(cr, fPos2.fX, fPos2.fY);
    cairo_line_to(cr, fPos3.fX, fPos3.fY);
    cairo_close_path(cr);

    (outline ? cairo_stroke : cairo_fill)(cr);
}

// -----------------------------------------------------------------------
// Rectangle

template<typename T>
void Rectangle<T>::_draw(const GraphicsContext* context, const bool outline)
{
    DISTRHO_SAFE_ASSERT_RETURN(fSize.isValid(),);

    cairo_t* cr = context->cairo;

    cairo_new_path(cr);
    cairo_rectangle(cr, fPos.fX, fPos.fY, fSize.fWidth, fSize.fHeight);

    (outline ? cairo_stroke : cairo_fill)(cr);
}

// -----------------------------------------------------------------------
// Possible template data types

template class Point<double>;
template class Point<float>;
template class Point<int>;
template class Point<uint>;
template class Point<short>;
template class Point<ushort>;

template class Size<double>;
template class Size<float>;
template class Size<int>;
template class Size<uint>;
template class Size<short>;
template class Size<ushort>;

template class Line<double>;
template class Line<float>;
template class Line<int>;
template class Line<uint>;
template class Line<short>;
template class Line<ushort>;

template class Circle<double>;
template class Circle<float>;
template class Circle<int>;
template class Circle<uint>;
template class Circle<short>;
template class Circle<ushort>;

template class Triangle<double>;
template class Triangle<float>;
template class Triangle<int>;
template class Triangle<uint>;
template class Triangle<short>;
template class Triangle<ushort>;

template class Rectangle<double>;
template class Rectangle<float>;
template class Rectangle<int>;
template class Rectangle<uint>;
template class Rectangle<short>;
template class Rectangle<ushort>;

// -----------------------------------------------------------------------

END_NAMESPACE_DGL
