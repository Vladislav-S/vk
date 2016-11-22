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

    int getW();
    int getH();
public slots:
    void ready();
private slots:

private:
    Ui::Form *ui;
    vkConnect * vk;
    int w;
    int h;
    QJsonObject friends;

};

#endif // FORM_H
