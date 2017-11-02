#include <string.h>
#include <stdbool.h>
#include "regis.h"
#include <time.h>
#include <ctype.h>

#include <QtCore/QDebug>
#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(lcRegis, "yat.regis")

void ReGISImage::init(int width, int height) {
    m_image = QImage(width, height, QImage::Format_ARGB32);
    if (m_painter) {
        delete m_painter;
        m_painter = nullptr;
    }
    erase();
}

void ReGISImage::resize(int width, int height) {
    // TODO copy existing image data?
    init(width, height);
}

void ReGISImage::ensurePainter() {
    if (!m_painter) {
        m_painter = new QPainter(&m_image);
        m_painter->setPen(Qt::white);
        m_painter->setBrush(Qt::white);
        m_painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        QFont mono(QLatin1String("monospace"));
        mono.setPixelSize(14);
        m_painter->setFont(mono);
    }
}

void ReGISImage::erase() {
    m_image.fill(Qt::transparent);
}

void ReGISImage::processScreenCommand() {
    if (m_paramStr == "E")
        erase();
    else if (m_paramStr == "C0")
        m_cursor = false;
    else if (m_paramStr == "C1")
        m_cursor = true;
    else
        qCWarning(lcRegis) << "unhandled command: S" << m_paramStr << "from" << m_commandStr;
}

void ReGISImage::processWriteControlCommand() {
    qCWarning(lcRegis) << "unhandled command: W" << m_paramStr << "from" << m_commandStr;
}

void ReGISImage::processCommand(char endsWith) {
    switch (m_command) {
    case 'v':
    case 'V':
        ensurePainter();
        if (m_numericParameters.length() > 1) {
            QPoint p = numericAsPoint();
            m_painter->drawLine(m_pen, p);
            m_pen = p;
        } else {
            m_painter->drawPoint(m_pen);
        }
        break;
    case 'P':
        m_pen = numericAsPoint();
        break;
    case 'T':
        if (endsWith == '\'') {
            ensurePainter();
            if (!m_paramStr.isEmpty())
                m_painter->drawText(m_pen + QPoint(0, m_painter->fontMetrics().ascent()), QLatin1String(m_paramStr));
        } else if (endsWith == ')') {
            qCDebug(lcRegis) << "handling text modal command" << m_paramStr << "from" << m_commandStr;
            // TODO
        }
        break;
    case 'S':
        processScreenCommand();
        break;
    case 'W':
        processWriteControlCommand();
        break;
    default:
        qCWarning(lcRegis) << "unhandled command:" << m_command << "from" << m_commandStr;
    }
    m_state = StateInitial; // assume if we finished one, will start over, but nesting will be a problem
}

QPoint ReGISImage::numericAsPoint() {
    if (m_numericParameters.length() == 2)
        return QPoint(m_numericParameters[0], m_numericParameters[1]);
    qCWarning(lcRegis) << "unexpected number of point coordinates:" << m_numericParameters.length() << "from" << m_commandStr;
    return QPoint();
}

void ReGISImage::appendNumericParameter() {
    if (m_paramStr.isEmpty())
        return;
    bool ok = false;
    int val = m_paramStr.toInt(&ok);
    if (ok)
        m_numericParameters.append(val);
    else
        qCWarning(lcRegis) << "can't parse as a number:" << m_paramStr << "from" << m_commandStr;
    m_paramStr.clear();
}

void ReGISImage::processChar(char ch)
{
    if (ch == '\r' || ch == '\n') {
        if (m_state != StateCommand && m_state != StateInitial)
            qCWarning(lcRegis) << "unfinished command" << m_commandStr;
        m_state = StateInitial;
        m_commandStr.clear();
        return;
    }

    m_commandStr.append(ch);

    switch (m_state) {
    case StateInitial:
        if (isalpha(ch)) {
            m_command = ch;
            m_state = StateCommand;
        }
        break;
    case StateCommand:
        switch (ch) {
        case '(':
        case '[':
        case '\'':
            m_paramStr.clear();
            m_numericParameters.clear();
            m_openPunct = ch;
            m_state = StateOpeningPunct;
            break;
        default:
            qCWarning(lcRegis) << "unexpected" << ch << "within command" << m_commandStr;
            break;
        }
        break;
    case StateOpeningPunct:
        switch (ch) {
        case ')':
            if (m_openPunct != '(')
                qCWarning(lcRegis) << "unmatched" << ch << "after" << m_openPunct << "from" << m_commandStr;
            else
                processCommand(ch);
            break;
        case ']':
            if (m_openPunct != '[')
                qCWarning(lcRegis) << "unmatched" << ch << "after" << m_openPunct << "from" << m_commandStr;
            else {
                appendNumericParameter();
                processCommand(ch);
            }
            break;
        case '\'':
            if (m_openPunct != '\'')
                qCWarning(lcRegis) << "unmatched" << ch << "after" << m_openPunct << "from" << m_commandStr;
            else
                processCommand(ch);
            break;
        case ',':
            if (m_openPunct == '[')
                appendNumericParameter();
            else if (m_openPunct == '(') {
                m_parameters.append(m_paramStr);
                m_paramStr.clear();
            }
            break;
        default:
            m_paramStr.append(ch);
            break;
        }
    }
}
