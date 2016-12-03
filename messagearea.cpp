#include "messagearea.h" // потерялся файл?
#include "ui_messagearea.h"

MessageArea::MessageArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageArea)
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    this->resize(500, 900);
    QPushButton * but1 = new QPushButton("Button", this);
    but1->resize(400, 800);
    //ui->setupUi(this);
}

MessageArea::~MessageArea()
{
    delete ui;
}
