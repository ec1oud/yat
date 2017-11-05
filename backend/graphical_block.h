/******************************************************************************
 * Copyright (c) 2017 Shawn Rutledge
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
******************************************************************************/

#ifndef GRAPHICAL_BLOCK_H
#define GRAPHICAL_BLOCK_H

#include <QtCore/QObject>
#include <QtGui/QImage>
#include "block.h"

class Text;
class Screen;

class GraphicalBlock : public Block
{
public:
    GraphicalBlock(Screen *screen);
    ~GraphicalBlock();

    void setImage(QImage i);
    const QImage *image() { return &m_image; }

    QString id() { return m_text_line; }
    void setIdNumeric(int id) { m_text_line = QString::number(id); }

    void dispatchEvents() override;

private:
    QImage m_image;
};

#endif // GRAPHICAL_BLOCK_H
