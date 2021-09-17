#include "hotellogin.h"
#include "ui_hotellogin.h"
#pragma execution_character_set("utf-8")
hotellogin::hotellogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hotellogin)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
    connect(this,SIGNAL(sendName(QString)),htl_dlg,SLOT(receiveName(QString)));
}

hotellogin::~hotellogin()
{
    delete ui;
}
//建立与数据库的连接
QSqlDatabase hotellogin::connectdb()
{
    //添加数据库驱动文件，这里使用的是sqlite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    //添加已创建好的数据库文件Platform.db
    db.setDatabaseName(".\\sqlite\\Platform.db");

    if(!db.open()){
       QMessageBox::critical(0,qApp->tr("Cannot open the database"),
             qApp->tr("Unable to establish a database connection."),QMessageBox::Cancel);
        this->close();
    }
    return db;

}

//建立链表，将所有用户名和密码存在里面
list *hotellogin::createlist(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.exec("select *from HotelInfo");
    query.first();
    QString hotelname = query.value(0).toString();
    QString password = query.value(18).toString();
    Node * First = new Node (hotelname,password);
    list* List = new list (First);
    while(query.next())
    {
        QString hotelname = query.value(0).toString();
        QString password = query.value(18).toString();
        List->insert(hotelname,password);
    }
    db.close();
    return List;
}

//检查用户名密码是否与链表中的某组匹配
bool hotellogin::check(list *List)
{
    QString hotelname = ui->Hotelname->text().trimmed();
    QString password = ui->Password->text().trimmed();

   Node *p = List->first;
   while(p)
   {
       if(p->username == hotelname && p->password == password)
           return true;
       p = p->next;
   }
   return false;
}

//点击注册按键
void hotellogin::on_rgsBtn_clicked()
{
    rgs_dlg->exec();
}


//点击登录按键
void hotellogin::on_loginBtn_clicked()
{
    QSqlDatabase db = connectdb();
    list * List = createlist(db);
    db.close();
    bool ok = check(List);
    if(!ok)
    {
        QMessageBox::warning(NULL,"Error","Password is WRONG or Username DOES NOT EXISTED!",QMessageBox::Ok,QMessageBox::Ok);
        ui->Hotelname->clear();
        ui->Password->clear();
    }
    if(ok)
    {
        QMessageBox::information(NULL,"Info","LOGIN SUCCESSFULLY!",QMessageBox::Ok,QMessageBox::Ok);
        hotelname = ui->Hotelname->text().trimmed();
        emit sendName(hotelname);
        this->close();
        htl_dlg->exec();
    }
}

void hotellogin::on_exitBtn_clicked()
{
    this->close();
}
