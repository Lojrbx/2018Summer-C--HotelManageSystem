#ifndef PLATFORMDIALOG_H
#define PLATFORMDIALOG_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include"hotellist.h"
namespace Ui {
class platformdialog;
}

class platformdialog : public QDialog
{
    Q_OBJECT

public:
    explicit platformdialog(QWidget *parent = 0);
    void connectdb();
    void createlist(QSqlDatabase db);
    void setitem(int i,HotelNode* p);
    void settable();
    QString hotel;
    hotellist* List;
    QSqlDatabase db;
    ~platformdialog();

private slots:
    void on_table_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::platformdialog *ui;
};

#endif // PLATFORMDIALOG_H
