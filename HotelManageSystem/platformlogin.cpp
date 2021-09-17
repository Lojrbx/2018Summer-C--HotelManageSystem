#include "platformlogin.h"
#include "ui_platformlogin.h"
#pragma execution_character_set("utf-8")
platformlogin::platformlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::platformlogin)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
}

platformlogin::~platformlogin()
{
    delete ui;
}

void platformlogin::on_loginBtn_clicked()
{
    QString name = "admin";
    QString password = "admin";
    if(ui->Username->text()==name&&ui->Password->text()==password)
    {
        this->close();
        plt_dlg->exec();
    }
    else
    {
        QMessageBox::warning(NULL,"错误","用户名或密码输入错误！",QMessageBox::Ok);
        ui->Username->clear();
        ui->Password->clear();
        ui->Username->setFocus();
    }
}
