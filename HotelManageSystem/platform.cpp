#include "platform.h"
#include "ui_platform.h"

platform::platform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::platform)
{
    ui->setupUi(this);
}

platform::~platform()
{
    delete ui;
}
