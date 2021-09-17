#include "choose.h"
#include "ui_choose.h"
#pragma execution_character_set("utf-8")
Choose::Choose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choose)
{
    ui->setupUi(this);
    QPixmap *pixmap = new QPixmap(".\\img\\blue.png");
    pixmap->scaled(ui->label->size(), Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);
}

Choose::~Choose()
{
    delete ui;
}



void Choose::on_htlbtn_clicked()
{
    htl_dlg->exec();

}

void Choose::on_pltfmbtn_clicked()
{
    plt_dlg->exec();
}

void Choose::on_userbtn_clicked()
{
    lg_dlg->exec();
}

void Choose::on_pushButton_clicked()
{
    accept();
}
