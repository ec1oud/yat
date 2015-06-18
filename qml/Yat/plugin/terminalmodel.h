#ifndef TERMINALMODEL_H
#define TERMINALMODEL_H

#include <QJSValue>
#include <QObject>
#include <QTimer>

class YatPty;

class TerminalModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJSValue rows READ rows NOTIFY rowsChanged) // array of row objects
public:
    explicit TerminalModel(QObject *parent = 0);

    QJSValue rows() { return m_rows; }

signals:
    void rowsChanged();
    void quiescent();

public slots:
    void exec(const QString &cmd);

protected slots:
    void read(const QByteArray &data);

protected:
//    void update();
    void appendTextRow(QString text);

protected:
    QJSValue m_rows;
    YatPty *m_pty;
    QJSValue m_inputFieldModel;
    QTimer m_quiescentTimer;
};

#endif // TERMINALMODEL_H
