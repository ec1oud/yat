/*******************************************************************************
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

#include "graphical_block.h"

#include "text.h"
#include "screen.h"

#include <QtCore/QDebug>
#include <QtCore/QtMath>

#include <algorithm>

GraphicalBlock::GraphicalBlock(Screen *screen)
    : Block(screen)
{
}

GraphicalBlock::~GraphicalBlock()
{
}

void GraphicalBlock::setImage(QImage i)
{
    m_image = i;
    m_width = qCeil(qreal(m_image.width()) / m_screen->monoFontWidth());
    //    m_height = qCeil(qreal(m_image.height()) / m_screen->lineHeight());
}

void GraphicalBlock::dispatchEvents()
{
    if (!m_changed)
        return;
    // TODO what now?  This isn't a QObject.  Should it be?
    // Then all the QML Image elements would bind to a source property here.
    // But that's overhead.  Why aren't we just populating the scene graph directly?
}
