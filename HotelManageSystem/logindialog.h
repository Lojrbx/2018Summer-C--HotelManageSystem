#ifndef LOGINDIALOG_H_
#define LOGINDIALOG_H_

#include<QDialog>
#include"register.h"
#include"userdialog.h"
#include"list.h"
#include<string>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    QSqlDatabase connectdb();
    list * createlist(QSqlDatabase db);
    QString Username;
    bool check(list* List);
    ~LoginDialog();

private slots:

    void on_rgsBtn_clicked();

    void on_loginBtn_clicked();

private:
    Ui::LoginDialog *ui;
    Register *rgs_diag = new Register;
    UserDialog *usr_diag = new UserDialog;
signals:
    void sendData(QString);
};

#endif // LOGINDIALOG_H
