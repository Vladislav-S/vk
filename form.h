#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QKeyEvent>
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

    void on_l_contacts_itemActivated(QListWidgetItem *item);

    void on_b_sent_clicked();

private:
    Ui::Form *ui;
    vkConnect * vk;
    int w;
    int h;
    QJsonObject friends;
    QJsonObject lastMessages;
    QString currentDiaolg;

};

#endif // FORM_H
