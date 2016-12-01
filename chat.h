#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QString>

class Chat : public QWidget
{
    Q_OBJECT
public:
    explicit Chat(QWidget *parent = 0);

    void setHTML(const QString &_html);

    QWebEnginePage * page();

signals:

public slots:

private:
    QWebEngineView * chatW;
    QString html;
};

#endif // CHAT_H
