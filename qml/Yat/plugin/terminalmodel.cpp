#include "terminalmodel.h"
#include "yat_pty.h"

#include <QQmlEngine>
#include <QJSValueIterator>
#include <qqml.h>
#include <QDebug>
#include <QRegularExpression>

static QLatin1String lengthPropName("length");

TerminalModel::TerminalModel(QObject *parent) :
    QObject(parent), m_pty(new YatPty(this))
{
    connect(m_pty, &YatPty::readyRead, this, &TerminalModel::read);
}

void TerminalModel::exec(const QString &cmd)
{
    m_pty->write(cmd.toLocal8Bit() + "\n");
}

void TerminalModel::read(const QByteArray &data)
{
    QString str = QString::fromLocal8Bit(data);
    foreach (const QString &line, str.split("\n"))
        appendTextRow(line);
    emit rowsChanged();
}

void TerminalModel::appendTextRow(QString text)
{
    static QRegularExpression termCodeRe("\\x1b\\[[0-9;]*m");
    static QRegularExpression termCodeRe2("\\x1b\\[[0-9;]*;");
    text.replace(termCodeRe, QString());
    text.replace(termCodeRe2, QString());
    QJSEngine *engine = qmlEngine(this);
    if (engine && m_rows.isUndefined()) {
        m_rows = engine->newArray();
        m_inputFieldModel = engine->newObject();
        m_inputFieldModel.setProperty("inputField", true);
        m_inputFieldModel.setProperty("text", QLatin1String("this is an input field, not plain text"));
    }
    QJSValue o = engine->newObject();
    o.setProperty("text", text);
    int length = m_rows.property(lengthPropName).toInt();
//qDebug() << text << "length was" << length;
    m_rows.setProperty(length - 1, o);
    m_rows.setProperty(length, m_inputFieldModel);
}
