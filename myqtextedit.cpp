#include "myqtextedit.h"
#include "ui_myqtextedit.h"

myQTextEdit::myQTextEdit(QWidget *parent) :
    QTextEdit(parent),
    ui(new Ui::myQTextEdit)
{
}

void myQTextEdit::setPB(QPushButton *_pb)
{
    pb = _pb;
}

myQTextEdit::~myQTextEdit()
{ // ui утек
}

void myQTextEdit::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << event->key();
    switch (event->key()) {
        case Qt::Key_Return:
            //qDebug() << "entered";

        emit pb->clicked();
        setFocus(Qt::OtherFocusReason);
        default:
          QTextEdit::keyPressEvent(event);
      }
}
