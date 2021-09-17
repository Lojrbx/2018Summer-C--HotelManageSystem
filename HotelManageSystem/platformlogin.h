#ifndef PLATFORMLOGIN_H
#define PLATFORMLOGIN_H

#include <QDialog>
#include"platformdialog.h"
#include<QMessageBox>
namespace Ui {
class platformlogin;
}

class platformlogin : public QDialog
{
    Q_OBJECT

public:
    explicit platformlogin(QWidget *parent = 0);
    ~platformlogin();

private slots:
    void on_loginBtn_clicked();

private:
    Ui::platformlogin *ui;
    platformdialog* plt_dlg = new platformdialog;
};

#endif // PLATFORMLOGIN_H
