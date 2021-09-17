#ifndef HOTELLOGIN_H
#define HOTELLOGIN_H

#include <QDialog>
#include"hotelregister.h"
#include"hotelmanagerdialog.h"
#include"list.h"
namespace Ui {
class hotellogin;
}

class hotellogin : public QDialog
{
    Q_OBJECT

public:
    explicit hotellogin(QWidget *parent = 0);
    QSqlDatabase connectdb();
    list* createlist(QSqlDatabase db);
    bool check(list* List);
    ~hotellogin();
    QString hotelname;

private slots:
    void on_rgsBtn_clicked();

    void on_loginBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::hotellogin *ui;
    hotelregister* rgs_dlg = new hotelregister;
    hotelmanagerdialog* htl_dlg = new hotelmanagerdialog;
signals:
    void sendName(QString);
};

#endif // HOTELLOGIN_H
