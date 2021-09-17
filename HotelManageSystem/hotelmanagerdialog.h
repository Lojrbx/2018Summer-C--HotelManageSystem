#ifndef HOTELMANAGERDIALOG_H
#define HOTELMANAGERDIALOG_H

#include <QDialog>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
#include<QString>
#include<QFile>
#include<QFileDialog>
#include"hotellist.h"
#include"order.h"
namespace Ui {
class hotelmanagerdialog;
}

class hotelmanagerdialog : public QDialog
{
    Q_OBJECT

public:
    explicit hotelmanagerdialog(QWidget *parent = 0);
    void dbconnect();
    void Unable();
    void Edable();
    void createlist();
    void searchthis();
    bool updatedata();
    void setitem(int i,ordernode* p);
    void settable();
    void createorderlist();
    void evaluate();
    //计数订单总数；
    int count;
    //评价
    float evaluation;
    hotellist* List;
    order* Orderlist;
    QSqlDatabase db;
    ~hotelmanagerdialog();
    QString Hotelname;
    //几个用于确定订单的字符串
    QString Username;
    QString Sex;
    QString Phonenumber;
    QString Room;
    QString Daynumber;
    QString Checkindate;
private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();
    //接受用户名信号的槽
    void receiveName(QString data);

    void on_chooseout_clicked();

    void on_choosein1_clicked();

    void on_choosein2_clicked();

    void on_updateimg_clicked();


    void on_exit_clicked();

    void on_ordertable_cellClicked(int row, int column);

    void on_changestatus_clicked();

    void on_save_clicked();

    void on_refresh_clicked();

    void on_exit_2_clicked();

private:
    Ui::hotelmanagerdialog *ui;
};


#endif // HOTELMANAGERDIALOG_H
