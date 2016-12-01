#include "chat.h"

Chat::Chat(QWidget *parent) : QWidget(parent)
{
    chatW = new QWebEngineView(this);
}

void Chat::setHTML(const QString &_html)
{
    html = _html;
    chatW->setHtml(html);
}

QWebEnginePage *Chat::page()
{
    return chatW->page();
}
