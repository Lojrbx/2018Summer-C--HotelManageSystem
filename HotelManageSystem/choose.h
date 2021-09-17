#ifndef CHOOSE_H
#define CHOOSE_H

#include <QDialog>
#include"logindialog.h"
#include"platformlogin.h"
#include"hotellogin.h"
namespace Ui {
class Choose;
}

class Choose : public QDialog
{
    Q_OBJECT

public:
    explicit Choose(QWidget *parent = 0);
    ~Choose();
    Ui::Choose *ui;
    LoginDialog *lg_dlg = new LoginDialog;
    platformlogin *plt_dlg = new platformlogin;
    hotellogin *htl_dlg = new hotellogin;
private slots:

    void on_htlbtn_clicked();

    void on_pltfmbtn_clicked();

    void on_userbtn_clicked();

    void on_pushButton_clicked();

private:

};

#endif // CHOOSE_H
