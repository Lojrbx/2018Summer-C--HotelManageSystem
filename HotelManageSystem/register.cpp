#include "register.h"
#include "ui_register.h"
#pragma execution_character_set("utf-8")
Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->checkPassword->setEchoMode(QLineEdit::Password);
    ui->Password->setEchoMode(QLineEdit::Password);
}

Register::~Register()
{
    delete ui;
}

QSqlDatabase Register::dbconnect()
{
    //添加数据库驱动文件，这里使用的是sqlite

    QSqlDatabase db;

    if(QSqlDatabase::contains("qt_sql_default_connection"))

      db = QSqlDatabase::database("qt_sql_default_connection");

    else

      db = QSqlDatabase::addDatabase("QSQLITE");
    //添加已创建好的数据库文件HM.db
    db.setDatabaseName(".\\sqlite\\Platform.db");

    if(!db.open()){
       QMessageBox::critical(0,qApp->tr("Cannot open the database"),
             qApp->tr("Unable to establish a database connection."),QMessageBox::Cancel);
       this->close();
    }
    return db;
}

int Register::checkdata(QSqlDatabase db)
{
    //声明一个字符串，把“用户名”后面的行编辑器内的内容赋给该字符串
    QString username = ui->Username->text().trimmed();

    //声明一个查询实例
    QSqlQuery query(db);

    query.exec("select *from UserInfo");
    //执行循环，寻找
    while(query.next())
    {
        if(username == query.value(0).toString())
        {
            QMessageBox::warning(NULL,"Info","This Name has been occupied,please enter again.",QMessageBox::Ok);
            return (1);
        }
    }
    return (0);
}

void Register::insertdata(QSqlDatabase db)
{
    QString Username = ui->Username->text().trimmed();
    QString Password = ui->Password->text().trimmed();
    QString Phonenumber = ui->Phonenumber->text().trimmed();
    QSqlQuery query(db);

    QString insert = "insert into UserInfo(Username,Password,Phonenumber)";
    insert += QString(" VALUES('%1','%2','%3')")
            .arg(Username)
            .arg(Password)
            .arg(Phonenumber);
    bool ok = query.exec(insert);
    if(ok)
    {
        QMessageBox::information(NULL,"Register","注册成功!",QMessageBox::Ok);
    }
    else   QMessageBox::information(NULL,"Register","SORRY!CANNOT REGISTER!",QMessageBox::Ok);
}
void Register::on_pushButton_clicked()
{
    QSqlDatabase db = this->dbconnect();
    int temp = checkdata(db);
    if(temp == 1)
    {
        ui->Username->clear();
        ui->Username->setFocus();
    }
        if(temp == 0)
        {
            if(ui->Password->text().trimmed() != ui->checkPassword->text().trimmed())
            {
                QMessageBox::warning(NULL,"Warning","The two passwords you entered are different, please enter again.",QMessageBox::Ok,QMessageBox::Ok);
                ui->checkPassword->clear();
                ui->Password->clear();
                ui->Password->setFocus();
            }
            else {
                this->insertdata(db);
            }
        }
        db.close();
    this->close();
}
