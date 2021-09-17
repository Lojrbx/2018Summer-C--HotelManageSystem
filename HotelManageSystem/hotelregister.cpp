#include "hotelregister.h"
#include "ui_hotelregister.h"
#pragma execution_character_set("utf-8")
hotelregister::hotelregister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hotelregister)
{
    ui->setupUi(this);
    ui->checkPassword->setEchoMode(QLineEdit::Password);
    ui->Password->setEchoMode(QLineEdit::Password);
}

hotelregister::~hotelregister()
{
    delete ui;
}

QSqlDatabase hotelregister::dbconnect()
{
    //添加数据库驱动文件，这里使用的是sqlite

    QSqlDatabase db;

    if(QSqlDatabase::contains("qt_sql_default_connection"))

      db = QSqlDatabase::database("qt_sql_default_connection");

    else

      db = QSqlDatabase::addDatabase("QSQLITE");//添加数据库驱动文件，这里使用的是sqlite


    //添加已创建好的数据库文件platform.db
    db.setDatabaseName(".\\sqlite\\Platform.db");

    if(!db.open()){
       QMessageBox::critical(0,qApp->tr("Cannot open the database"),
             qApp->tr("Unable to establish a database connection."),QMessageBox::Cancel);
       this->close();
    }
    return db;
}

//检测用户名是否重复，两次密码是否相同
int hotelregister::checkdata(QSqlDatabase db)
{
    //声明一个字符串，把“用户名”后面的行编辑器内的内容赋给该字符串
    QString hotelname = ui->Hotelname->text().trimmed();

    if(hotelname=="")
    {
        QMessageBox::warning(NULL,"注册","用户名不能为空！",QMessageBox::Ok);
    }

    //声明一个查询实例
    else
    {
        QSqlQuery query(db);

        //在表格“HotelInfo”中查找是否有重复的酒店名。
        query.exec("select *from HotelInfo");
        //执行循环，寻找
        while(query.next())
        {
            if(hotelname == query.value(0).toString())
            {
                QMessageBox::warning(NULL,"Info","This Name has been occupied,please enter again.",QMessageBox::Ok);
                return (1);
            }
        }
    }
    return (0);

}

void hotelregister::insertdata(QSqlDatabase db)
{
    QString Hotelname = ui->Hotelname->text().trimmed();
    QString Password = ui->Password->text().trimmed();
    QString Dial = ui->Dial->text().trimmed();
    QString Address = ui->Address->text().trimmed();
    QString City = ui->City->text().trimmed();

    QSqlQuery query(db);

    QString insert = "insert into HotelInfo(Hotelname,Password,City,Address,Dial)";
    insert += QString(" VALUES('%1','%2','%3','%4','%5')")
            .arg(Hotelname)
            .arg(Password)
            .arg(City)
            .arg(Address)
            .arg(Dial);
    bool ok = query.exec(insert);
    if(ok)
    {
        QMessageBox::information(NULL,"Register","注册成功!",QMessageBox::Ok);
    }
    else   QMessageBox::information(NULL,"Register","注册失败!",QMessageBox::Ok);
}
void hotelregister::on_pushButton_clicked()
{
    QSqlDatabase db = this->dbconnect();
    int temp = checkdata(db);
    if(temp == 1)
    {
        ui->Hotelname->clear();
        ui->Hotelname->setFocus();
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

