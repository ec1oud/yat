#ifndef TERMINALMODEL_H
#define TERMINALMODEL_H

#include <QJSValue>
#include <QObject>

class TerminalModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJSValue rows READ rows NOTIFY rowsChanged) // array of row objects
public:
    explicit TerminalModel(QObject *parent = 0);

    QJSValue rows() { update(); return m_rows; }

signals:
    void rowsChanged();

public slots:

protected:
    void update();
    void appendTextRow(QString text);

protected:
    QJSValue m_rows;
};

#endif // TERMINALMODEL_H
