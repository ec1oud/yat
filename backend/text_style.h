#ifndef TEXT_STYLE_H
#define TEXT_STYLE_H

#include <QtGui/QColor>

#include "color_palette.h"

class Screen;

class TextStyle
{
public:
    enum Style {
        Normal            = 0x0000,
        Italic            = 0x0001,
        Bold              = 0x0002,
        Underlined        = 0x0004,
        Blinking          = 0x0008,
        FastBlinking      = 0x0010,
        Gothic            = 0x0020,
        DoubleUnderlined  = 0x0040,
        Framed            = 0x0080,
        Overlined         = 0x0100,
        Encircled         = 0x0200,
        Inverse           = 0x0400
    };
    Q_DECLARE_FLAGS(Styles, Style)

    TextStyle();

    Styles style;
    QRgb foreground;
    QRgb background;

    bool isCompatible(const TextStyle &other) const;
};

class Text;
class TextStyleSpan : public TextStyle {
public:
    TextStyleSpan(const TextStyle &style, int start_index, int end_index)
        : TextStyle(style)
        , start_index(start_index)
        , end_index(end_index)
        , style_dirty(true)
        , index_dirty(true)
        , text_dirty(true)
    {
    }

    TextStyleSpan()
        : start_index(0)
        , end_index(0)
        , style_dirty(false)
        , index_dirty(false)
        , text_dirty(false)
    {
    }

    void releaseTextSegment(Screen *screen);

    Text *text_segment = nullptr;
    int16_t start_index;
    int16_t end_index;
    bool style_dirty : 1;
    bool index_dirty : 1;
    bool text_dirty : 1;

    void setStyle(const TextStyle &style) {
        foreground = style.foreground;
        background = style.background;
        this->style = style.style;
    }
};

QDebug operator<<(QDebug debug, TextStyleSpan line);
QDebug operator<<(QDebug debug, TextStyle::Styles styles);

#endif // TEXT_STYLE_H
