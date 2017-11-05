/*******************************************************************************
 * Copyright (c) 2012 Jørgen Lind
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*******************************************************************************/

#ifndef BLOCK_H
#define BLOCK_H

#include <QtCore/QObject>

#include "text_style.h"

class Text;
class Screen;

class Block
{
public:
    Block(Screen *screen);
    virtual ~Block();

    Q_INVOKABLE Screen *screen() const;

    void clear();
    void clearToEnd(int from);
    void clearCharacters(int from, int to);
    void deleteCharacters(int from, int to);
    void deleteToEnd(int from);
    void deleteLines(int from);

    void replaceAtPos(int i, const QString &text, const TextStyle &style, bool only_latin = true);
    void insertAtPos(int i, const QString &text, const TextStyle &style, bool only_latin = true);

    void setScreenIndex(int index) { m_screen_index = index; }
    int screenIndex() const { return m_screen_index; }
    size_t line() { return m_new_line; }
    void setLine(size_t line) {
        if (line != m_new_line) {
            m_changed = true;
            m_new_line = line;
        }
    }

    const QString &textLine() const;
    int textSize() { return m_text_line.size(); }

    int width() const { return m_width; }
    void setWidth(int width);
    int lineCount() const { return m_height ? m_height : (std::max((m_text_line.size() - 1),0) / m_width) + 1; }
    int lineCountAfterModified(int from_char, int text_size, bool replace) {
        int new_size = replace ? std::max(from_char + text_size, m_text_line.size())
            : std::max(from_char, m_text_line.size()) + text_size;
        return ((new_size - 1) / m_width) + 1;
    }
    void setLineCount(int8_t v);

    void setVisible(bool visible);
    bool visible() const;

    Block *split(int line);
    Block *takeLine(int line);
    void removeLine(int line);

    void moveLinesFromBlock(Block *block, int start_line, int count);

    virtual void dispatchEvents();
    void releaseTextObjects();

    QVector<TextStyleSpan> styleSpans() { return m_style_spans; }
    void printStyleSpans() const;
    void printStyleSpans(QDebug &debug) const;
    void printStyleSpansWidthText() const;

protected:
    void mergeCompatibleStyles();
    void ensureStyleAlignWithLines(int i);
    Screen *m_screen;
    QString m_text_line; // just the text of this line; or for an image, the ID
    QVector<TextStyleSpan> m_style_spans; // styled character ranges
    size_t m_line;
    size_t m_new_line;
    int m_screen_index;

    int16_t m_width;
    int8_t m_height = 0; // 0 means we're storing wrappable text; another value means this is a rectangular block

    bool m_visible : 1;
    bool m_changed : 1;
    bool m_only_latin : 1;
};

#endif // BLOCK_H
