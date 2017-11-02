#ifndef REGIS_H
#define REGIS_H

#include <QImage>
#include <QPainter>
#include <QPoint>
#include <QVarLengthArray>

class ReGISImage {
public:
    void init(int width,int height);
    void resize(int width,int height);
    void erase();
    void processChar(char ch);
    const QImage &image() const { return m_image; }

private:
    void appendNumericParameter();
    QPoint numericAsPoint();
    void ensurePainter();
    void processCommand(char endsWith);
    void processWriteControlCommand();
    void processScreenCommand();

    enum State {
        // What has already happened?
        StateInitial, // nothing
        StateCommand, // m_command is set now
        StateOpeningPunct,  // we've seen an opening parenthesis, bracket or quote
//        StateNestedOpeningPunct  // we've seen an opening parenthesis, bracket or quote inside another one
    };

    QPoint m_pen;
    QImage m_image = QImage(800, 480, QImage::Format_ARGB32);
    QPainter *m_painter = nullptr;
    bool m_cursor = false;
    State m_state = StateInitial;
    char m_command;
    char m_openPunct;
//    char m_nestedOpenPunct;
    QByteArray m_paramStr;
    QByteArray m_commandStr; // history from one newline to the next
    QVarLengthArray<int, 2> m_numericParameters;
    QVarLengthArray<QByteArray, 2> m_parameters;
};

#endif // REGIS_H
