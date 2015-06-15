#include "terminalmodel.h"

#include <QQmlEngine>
#include <QJSValueIterator>
#include <qqml.h>
#include <QDebug>

static QLatin1String lengthPropName("length");

TerminalModel::TerminalModel(QObject *parent) : QObject(parent)
{
}

void TerminalModel::update()
{
    QJSEngine *engine = qmlEngine(this);
qDebug() << engine << m_rows.isUndefined() << m_rows.isNull();
    if (engine && m_rows.isUndefined()) {
        m_rows = engine->newArray();
qDebug() << "appending rows";
        appendTextRow("row 1");
        appendTextRow("row 2");
        appendTextRow("row 3");
    }
//    emit rowsChanged();
}

void TerminalModel::appendTextRow(QString text)
{
    QJSEngine *engine = qmlEngine(this);
    QJSValue o = engine->newObject();
    o.setProperty("text", text);
    int length = m_rows.property(lengthPropName).toInt();
qDebug() << text << "length was" << length;
    m_rows.setProperty(length, o);
}
