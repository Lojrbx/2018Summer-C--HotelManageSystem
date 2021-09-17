#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include<QString>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    QSqlDatabase dbconnect();
    int checkdata(QSqlDatabase db);
    void insertdata(QSqlDatabase db);
    ~Register();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
