#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QDesktopServices>
//#include "widget.h"

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

signals:
    void sentQUrl(QUrlQuery * qurlq);

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();


private:

    Ui::loginDialog *ui;
    QUrlQuery urlq;
    QString urlStr;
    QUrl url;

};

#endif // LOGINDIALOG_H
