#include "text_style.h"

#include "screen.h"
#include "text.h"

#include <QtCore/QDebug>

TextStyle::TextStyle()
    : style(Normal)
    , foreground(0)
    , background(0)
{
}

bool TextStyle::isCompatible(const TextStyle &other) const
{
    return foreground == other.foreground
            && background == other.background
            && style == other.style;
}

QDebug operator<<(QDebug debug, TextStyleSpan line)
{
    const QDebugStateSaver saver(debug);
    debug.nospace();
    debug << '[' << line.start_index << ' ' << line.style << ":" << hex <<
             (line.foreground & 0xFFFFFF) << ":" << (line.background & 0xFFFFFF) << ' ' << line.end_index << ']';
    return debug;
}

void TextStyleSpan::releaseTextSegment(Screen *screen)
{
    if (text_segment) {
        text_segment->setVisible(false);
        screen->releaseTextSegment(text_segment);
        text_segment = 0;
    }
}

QDebug operator<<(QDebug debug, TextStyle::Styles styles)
{
    if (styles == TextStyle::Normal)
        debug << "nrm";
    if (styles & TextStyle::Italic)
        debug << "ita";
    if (styles & TextStyle::Bold)
        debug << "bld";
    if (styles & TextStyle::Underlined)
        debug << "uld";
    if (styles & TextStyle::Blinking)
        debug << "bln";
    if (styles & TextStyle::FastBlinking)
        debug << "fbl";
    if (styles & TextStyle::Gothic)
        debug << "gth";
    if (styles & TextStyle::DoubleUnderlined)
        debug << "dul";
    if (styles & TextStyle::Framed)
        debug << "frm";
    if (styles & TextStyle::Overlined)
        debug << "ovl";
    if (styles & TextStyle::Encircled)
        debug << "enc";
    if (styles & TextStyle::Inverse)
        debug << "inv";
    return debug;
}
