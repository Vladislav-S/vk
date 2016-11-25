#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QDesktopServices>
#include <QString>
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


    void on_lineEdit_textChanged(const QString &arg1);

private:

    bool isCorrectLogin(const QString &str);

    Ui::loginDialog *ui;
    QUrlQuery urlq;
    QString urlStr;
    QUrl url;

};

#endif // LOGINDIALOG_H
