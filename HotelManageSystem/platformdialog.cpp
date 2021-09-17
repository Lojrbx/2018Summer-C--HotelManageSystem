#include "platformdialog.h"
#include "ui_platformdialog.h"
#pragma execution_character_set("utf-8")
platformdialog::platformdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::platformdialog)
{
    ui->setupUi(this);
    this->settable();
}

//连接数据库
void platformdialog::connectdb()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))

      db = QSqlDatabase::database("qt_sql_default_connection");

    else

      db = QSqlDatabase::addDatabase("QSQLITE");

    //添加已创建好的数据库文件Platform.db
    db.setDatabaseName(".\\sqlite\\Platform.db");

    if(!db.open()){
       QMessageBox::critical(0,qApp->tr("Cannot open the database"),
             qApp->tr("Unable to establish a database connection."),QMessageBox::Cancel);
        this->close();
    }
}

//建立链表，将待审核的所有数据储存在里面
void platformdialog::createlist(QSqlDatabase db)
{
    connectdb();
    QSqlQuery query(db);
    query.exec("select *from AuditInfo");
    query.first();
    QString name = query.value(0).toString();
    QString city = query.value(2).toString();
    QString address = query.value(3).toString();
    QString dial = query.value(4).toString();
    int sglroom = query.value(5).toInt();
    int psgl = query.value(6).toInt();
    int dblroom = query.value(7).toInt();
    int pdbl = query.value(8).toInt();
    int bbroom = query.value(9).toInt();
    int pbbd = query.value(10).toInt();
    int suite = query.value(11).toInt();
    int psuite = query.value(12).toInt();
    float discount = query.value(13).toFloat();
    float evaluation = query.value(14).toFloat();
    QString discription = query.value(15).toString();

    QString out = query.value(16).toString();
    QString in_1 = query.value(17).toString();
    QString in_2 = query.value(18).toString();
    QString password = query.value(1).toString();
    //头结点建立
    HotelNode * First = new HotelNode (name,city,address,sglroom,psgl,dblroom,pdbl,bbroom,pbbd,suite,psuite,discount,evaluation,dial,discription,out,in_1,in_2,password);
    List = new hotellist (First);

    //插入剩余结点
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString city = query.value(2).toString();
        QString address = query.value(3).toString();
        QString dial = query.value(4).toString();
        int sglroom = query.value(5).toInt();
        int psgl = query.value(6).toInt();
        int dblroom = query.value(7).toInt();
        int pdbl = query.value(8).toInt();
        int bbroom = query.value(9).toInt();
        int pbbd = query.value(10).toInt();
        int suite = query.value(11).toInt();
        int psuite = query.value(12).toInt();
        float discount = query.value(13).toFloat();
        float evaluation = query.value(14).toFloat();
        QString discription = query.value(15).toString();
        QString out = query.value(16).toString();
        QString in_1 = query.value(17).toString();
        QString in_2 = query.value(18).toString();
        QString password = query.value(1).toString();
        List->insert(name,city,address,sglroom,psgl,dblroom,pdbl,bbroom,pbbd,suite,psuite,discount,evaluation,dial,discription,out,in_1,in_2,password);
        (List->count)++;
    }
}


platformdialog::~platformdialog()
{
    delete ui;
}

//生成一行表格
void platformdialog::setitem(int i, HotelNode *p)
{
    ui->table->setItem(i,0,new QTableWidgetItem(p->name));
    ui->table->setItem(i,1,new QTableWidgetItem(p->city));
    ui->table->setItem(i,2,new QTableWidgetItem(p->address));
    ui->table->setItem(i,3,new QTableWidgetItem(p->dial));
    ui->table->setItem(i,4,new QTableWidgetItem(QString::number(p->sglroom)));
    ui->table->setItem(i,5,new QTableWidgetItem(QString::number(p->psgl)));
    ui->table->setItem(i,6,new QTableWidgetItem(QString::number(p->dblroom)));
    ui->table->setItem(i,7,new QTableWidgetItem(QString::number(p->pdbl)));
    ui->table->setItem(i,8,new QTableWidgetItem(QString::number(p->bbdroom)));
    ui->table->setItem(i,9,new QTableWidgetItem(QString::number(p->pbbd)));
    ui->table->setItem(i,10,new QTableWidgetItem(QString::number(p->suite)));
    ui->table->setItem(i,11,new QTableWidgetItem(QString::number(p->psuite)));
    ui->table->setItem(i,12,new QTableWidgetItem(QString::number(p->evaluation)));
    ui->table->setItem(i,13,new QTableWidgetItem(QString::number(p->discount)));
    ui->table->setItem(i,14,new QTableWidgetItem(p->discription));
}

//生成表格
void platformdialog::settable()
{
    ui->groupBox->hide();
    QHeaderView* headerView = ui->table->verticalHeader();
    headerView->setHidden(true);
    //创建链表并把数据都显示在表格中
    connectdb();
    createlist(db);
    HotelNode* p = List->first;
    ui->table->setRowCount(List->count);
    int i = 0;
    do{
        setitem(i,p);
        p = p->next;
        i++;
    }while(p);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void platformdialog::on_table_cellDoubleClicked(int row, int column)
{
    hotel = ui->table->item(row,0)->text();
    ui->groupBox->show();
    ui->hotelname->setText(hotel);
}

//点击 是 键通过审核
void platformdialog::on_pushButton_clicked()
{
    HotelNode* p = List->first;
    while(p)
    {
        if(p->name == hotel)break;
        p = p->next;
    }
    //用该条数据，更新表hotelinfo中的数据。
    QSqlQuery query(db);
    query.prepare("update HotelInfo set City=?,Address=?,Dial=? where HotelName=?");
    query.addBindValue(p->city);
    query.addBindValue(p->address);
    query.addBindValue(p->dial);
    query.addBindValue(p->name);
    query.exec();
    query.prepare("update HotelInfo set Singleroom=?,SinglePrice=?,Doubleroom=?,DoublePrice=? where HotelName=?");
    query.addBindValue(p->sglroom);
    query.addBindValue(p->psgl);
    query.addBindValue(p->dblroom);
    query.addBindValue(p->pdbl);
    query.addBindValue(p->name);
    query.exec();
    query.prepare("update HotelInfo set Bigbedroom=?,BbdPrice=?,Suiteroom=?,SuitePrice=? where HotelName=?");
    query.addBindValue(p->bbdroom);
    query.addBindValue(p->pbbd);
    query.addBindValue(p->suite);
    query.addBindValue(p->psuite);
    query.addBindValue(p->name);
    query.exec();
    query.prepare("update HotelInfo set Discount=?,Discription=? where HotelName=?");
    query.addBindValue(p->discount);
    query.addBindValue(p->discription);
    query.addBindValue(p->name);
    bool ok = query.exec();
    if(ok)
    {
        QMessageBox::information(NULL,"Info","已通过审核",QMessageBox::Ok);
        ui->groupBox->hide();
        QSqlQuery query1(db);
        query1.prepare(QString("DELETE FROM AuditInfo WHERE HotelName=?"));
        query1.addBindValue(p->name);
        query1.exec();
        this->settable();
    }


}
//点击 否 键不通过审核
void platformdialog::on_pushButton_2_clicked()
{
    QSqlQuery query(db);
    query.prepare(QString("DELETE FROM AuditInfo WHERE HotelName=?"));
    query.addBindValue(hotel);
    bool ok = query.exec();
    if(ok)
    {
        QMessageBox::information(NULL,"Info","修改未通过审核",QMessageBox::Ok);
        this->settable();
        ui->groupBox->hide();
    }
}
//点击 退出 键关闭窗口和数据库
void platformdialog::on_pushButton_3_clicked()
{
    this->close();
    db.close();
}
