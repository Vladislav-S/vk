#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "vkconnect.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    Form(QWidget *parent = 0, vkConnect * _vk = 0);
    ~Form();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;
    vkConnect * vk;
};

#endif // FORM_H
