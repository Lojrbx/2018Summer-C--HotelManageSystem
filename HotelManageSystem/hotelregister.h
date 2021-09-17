#ifndef HOTELREGISTER_H
#define HOTELREGISTER_H

#include <QDialog>
#include<QString>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
namespace Ui {
class hotelregister;
}

class hotelregister : public QDialog
{
    Q_OBJECT

public:
    explicit hotelregister(QWidget *parent = 0);
    ~hotelregister();
    QSqlDatabase dbconnect();
    int checkdata(QSqlDatabase db);
    void insertdata(QSqlDatabase db);
private slots:
    void on_pushButton_clicked();

private:
    Ui::hotelregister *ui;
};

#endif // HOTELREGISTER_H
