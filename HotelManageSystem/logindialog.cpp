#include "logindialog.h"
#include "ui_logindialog.h"
#pragma execution_character_set("utf-8")
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
    connect(this,SIGNAL(sendData(QString)),usr_diag,SLOT(receiveData(QString)));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_rgsBtn_clicked()
{

    rgs_diag->exec();

}
//建立与数据库的连接
QSqlDatabase LoginDialog::connectdb()
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
list *LoginDialog::createlist(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.exec("select *from UserInfo");
    query.first();
    QString username = query.value(0).toString();
    QString password = query.value(1).toString();
    Node * First = new Node (username,password);
    list* List = new list (First);
    do
    {
        QString username = query.value(0).toString();
        QString password = query.value(1).toString();
        List->insert(username,password);
    }while(query.next());
    db.close();
    return List;
}

//检测用户名是否重复，密码是否输入正确。
bool LoginDialog::check(list *List)
{
    QString username = ui->Username->text().trimmed();
    QString password = ui->Password->text().trimmed();

   Node *p = List->first;
   while(p)
   {
       if(p->username == username && p->password == password)
           return true;
       p = p->next;
   }
   return false;
}
void LoginDialog::on_loginBtn_clicked()
{
    QSqlDatabase db = connectdb();
    list * List = createlist(db);

    bool ok = check(List);
    if(!ok)
    {
        QMessageBox::warning(NULL,"Error","Password is WRONG or Username DOES NOT EXISTED!",QMessageBox::Ok,QMessageBox::Ok);
        ui->Username->clear();
        ui->Password->clear();
    }
    if(ok)
    {
        QMessageBox::information(NULL,"Info","LOGIN SUCCESSFULLY!",QMessageBox::Ok,QMessageBox::Ok);
        Username = ui->Username->text().trimmed();
        emit sendData(Username);
        this->close();
        usr_diag->exec();
    }
    db.close();

}
