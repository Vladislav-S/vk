#ifndef MYQTEXTEDIT_H
#define MYQTEXTEDIT_H

#include <QTextEdit>
#include <QDebug>
#include <QKeyEvent>
#include <QPushButton>

namespace Ui {
class myQTextEdit;
}

class myQTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit myQTextEdit(QWidget *parent = 0);
    void setPB(QPushButton * _pb);
    ~myQTextEdit();

private:
    Ui::myQTextEdit *ui;
    QPushButton * pb;

protected:
    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // MYQTEXTEDIT_H
