#ifndef ERROR_DIALOG_H
#define ERROR_DIALOG_H

#include <QDialog>

namespace Ui {
class error_dialog;
}

class error_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit error_dialog(QWidget *parent = 0);
    error_dialog(QWidget *parent = 0, const QString & error_msg = "");
    ~error_dialog();

signals:
    void on_ok();
private slots:
    void on_pushButton_clicked();

    void on_error_dialog_destroyed();

    void on_error_dialog_finished(int result);

private:
    Ui::error_dialog *ui;
};

#endif // ERROR_DIALOG_H
