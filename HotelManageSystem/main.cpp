#include <QApplication>
#include"choose.h"
#include<QSqlDatabase>
#include<QString>
#include<QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //选择功能入口
    Choose dlg_chs;
    if(dlg_chs.exec()==QDialog::Accepted)
    return 0;
}
