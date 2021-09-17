#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include<QStandardItemModel>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
#include"hotellist.h"
#include"order.h"
namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = 0);
    void connectdb();
    void createlist(QSqlDatabase db);
    void setitem(int i,HotelNode* p);
    void settable();
    bool insertdata();
    void createorderlist();
    void setordertable();
    void setorderitem(int i,ordernode* p);
    ~UserDialog();
    QString Username;
    QString Hotel;
    hotellist * List;
    order* Orderlist;
    QSqlDatabase db;

private slots:
    void on_check_clicked();

    void on_Evaluation_clicked();

    void on_price_clicked();

    void on_Hoteltable_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_Submit_clicked();

  //接受用户名信号的槽
    void receiveData(QString data);

    void on_ordertable_cellDoubleClicked(int row, int column);

    void on_evaluate_clicked();

    void on_pay_clicked();

    void on_Return_clicked();

    void on_submit_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_refee_clicked();

private:
    Ui::UserDialog *ui;

};

#endif // USERDIALOG_H
