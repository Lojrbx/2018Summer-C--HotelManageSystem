#include "userdialog.h"
#include "ui_userdialog.h"
#pragma execution_character_set("utf-8")
UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
    ui->box->hide();
    ui->pay->hide();
    ui->Return->hide();
    ui->evaluate->hide();
    ui->valuebox->hide();
    ui->refee->hide();
    this->settable();

}

UserDialog::~UserDialog()
{
    delete ui;
}

//建立与数据库的连接
void UserDialog::connectdb()
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

//建立链表，将所有酒店信息存在里面
void UserDialog::createlist(QSqlDatabase db)
{
    connectdb();
    QSqlQuery query(db);
    query.exec("select *from HotelInfo");
    query.first();
    QString name = query.value(0).toString();
    QString city = query.value(1).toString();
    QString address = query.value(2).toString();
    QString dial = query.value(3).toString();
    int sglroom = query.value(4).toInt();
    int psgl = query.value(5).toInt();
    int dblroom = query.value(6).toInt();
    int pdbl = query.value(7).toInt();
    int bbroom = query.value(8).toInt();
    int pbbd = query.value(9).toInt();
    int suite = query.value(10).toInt();
    int psuite = query.value(11).toInt();
    float discount = query.value(12).toFloat();
    float evaluation = query.value(13).toFloat();
    QString discription = query.value(14).toString();

    QString out = query.value(15).toString();
    QString in_1 = query.value(16).toString();
    QString in_2 = query.value(17).toString();
    QString password = query.value(18).toString();
    //头结点建立
    HotelNode * First = new HotelNode (name,city,address,sglroom,psgl,dblroom,pdbl,bbroom,pbbd,suite,psuite,discount,evaluation,dial,discription,out,in_1,in_2,password);
    List = new hotellist (First);

    //插入剩余结点
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString city = query.value(1).toString();
        QString address = query.value(2).toString();
        QString dial = query.value(3).toString();
        int sglroom = query.value(4).toInt();
        int psgl = query.value(5).toInt();
        int dblroom = query.value(6).toInt();
        int pdbl = query.value(7).toInt();
        int bbroom = query.value(8).toInt();
        int pbbd = query.value(9).toInt();
        int suite = query.value(10).toInt();
        int psuite = query.value(11).toInt();
        float discount = query.value(12).toFloat();
        float evaluation = query.value(13).toFloat();
        QString discription = query.value(14).toString();
        QString out = query.value(15).toString();
        QString in_1 = query.value(16).toString();
        QString in_2 = query.value(17).toString();
        QString password = query.value(18).toString();
        List->insert(name,city,address,sglroom,psgl,dblroom,pdbl,bbroom,pbbd,suite,psuite,discount,evaluation,dial,discription,out,in_1,in_2,password);
        (List->count)++;
    }

}
//生成一行表格
void UserDialog::setitem(int i,HotelNode* p)
{
    ui->Hoteltable->setItem(i,0,new QTableWidgetItem(p->name));
    ui->Hoteltable->setItem(i,1,new QTableWidgetItem(p->city));
    ui->Hoteltable->setItem(i,2,new QTableWidgetItem(p->address));
    ui->Hoteltable->setItem(i,3,new QTableWidgetItem(QString::number(p->price)));
    ui->Hoteltable->setItem(i,4,new QTableWidgetItem(QString::number(p->evaluation)));
    ui->Hoteltable->setItem(i,5,new QTableWidgetItem(QString::number(p->sglroom+p->dblroom+p->bbdroom+p->suite)));
    ui->Hoteltable->setItem(i,6,new QTableWidgetItem(QString::number(p->discount)));
}

void UserDialog::settable()
{
    QHeaderView* headerView = ui->Hoteltable->verticalHeader();
    headerView->setHidden(true);
    //创建链表并把数据都显示在表格中
    connectdb();
    createlist(db);
    HotelNode* p = List->first;
    ui->Hoteltable->setRowCount(List->count);
    ui->tabWidget_2->hide();
    int i = 0;
    do{
        setitem(i,p);


       p = p->next;
       i++;
    }while(p);
    ui->Hoteltable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

//查询
//按照当前LineEdit和box中的字符进行查找
void UserDialog::on_check_clicked()
{
    //读取界面输入的文字
    QString City = ui->City->text();
    int roomtype = ui->comboBox->currentIndex();
    ui->Hoteltable->clearContents();
    HotelNode* p = List->first;
    int i = 0;
    while(p)
    {
        switch(roomtype) {
        case 0:
            if(City!=NULL){
                if(p->city==City&&(p->sglroom>0))
                {
                    this->setitem(i,p);
                    i++;
                }


            }
            if(City==NULL){
                if(p->sglroom>0){
                    this->setitem(i,p);
                    i++;
                }

            }

            break;
        case 1:
            if(City!=NULL){
                if(p->city==City&&(p->dblroom>0))
                {
                    this->setitem(i,p);
                    i++;
                }

            }
            if(City==NULL){
                if(p->dblroom>0){
                    this->setitem(i,p);
                    i++;
                }
            }
            break;
        case 2:
            if(City!=NULL){
                if(p->city==City&&(p->bbdroom>0))
                {
                    this->setitem(i,p);
                    i++;
                }

            }
            if(City==NULL){
                if(p->bbdroom>0){
                    this->setitem(i,p);
                    i++;
                }

            }
            break;
        case 3:
            if(City!=NULL){
                if(p->city==City&&(p->suite>0))
                {
                    this->setitem(i,p);
                    i++;
                }
                i++;
            }
            if(City==NULL){
                if(p->suite>0){
                    this->setitem(i,p);
                    i++;
                }

            }
            break;
        }
        p = p->next;

    }
}

//按找酒店的评分进行排序
void UserDialog::on_Evaluation_clicked()
{
    hotellist *list = List->copylist();
    HotelNode* p = list->first;
    HotelNode* q = p->next;
    HotelNode* s = q->next;
    while(1){
        int temp = 0;

        while(s)
        {
            HotelNode* a = list->first;
            HotelNode* b = a->next;
            if((a->evaluation)<(b->evaluation))
            {
                a->next = b->next;
                list->first = b;
                b->next = a;
                temp = 1;
            }
            if((q->evaluation)<(s->evaluation))
            {
                p->next = s;
                q->next = s->next;
                s->next = q;
                temp = 1;
            }
            p = p->next;
            q = p->next;
            s = q->next;
        }
        if(temp==0)break;
    }
    p = list->first;
    int i = 0 ;
    while(p)
    {
        setitem(i,p);
        p = p->next;
        i++;
    }

}
//按价格从高到低排序
void UserDialog::on_price_clicked()
{hotellist *list = List->copylist();
    HotelNode* p = list->first;
    HotelNode* q = p->next;
    HotelNode* s = q->next;
    while(1){
        int temp = 0;

        while(s)
        {
            HotelNode* a = list->first;
            HotelNode* b = a->next;
            if((a->price)<(b->price))
            {
                a->next = b->next;
                list->first = b;
                b->next = a;
                temp = 1;
            }
            if((q->price)<(s->price))
            {
                p->next = s;
                q->next = s->next;
                s->next = q;
                temp = 1;
            }
            p = p->next;
            q = p->next;
            s = q->next;
        }
        if(temp==0)break;
    }
    p = list->first;
    int i = 0 ;
    while(p)
    {
        setitem(i,p);
        p = p->next;
        i++;
    }
}


//双击某个酒店所在行，将打开新的一页，显示酒店的相应信息和下单功能。
void UserDialog::on_Hoteltable_cellDoubleClicked(int row, int column)
{
    ui->tabWidget_2->show();
    Hotel = ui->Hoteltable->item(row,0)->text();
    HotelNode* p = List->first;
    while(p)
    {
        if(p->name == Hotel)
            break;
        p = p->next;
    }
    ui->Hotel->setText(p->name);
    ui->Address->setText(p->address);
    ui->discription->setText(p->discription);
    QPixmap *pixmap1 = new QPixmap(p->outside);
    pixmap1->scaled(ui->img_out->size(), Qt::KeepAspectRatio);
    ui->img_out->setScaledContents(true);
    ui->img_out->setPixmap(*pixmap1);
    QPixmap *pixmap2 = new QPixmap(p->in_01);
    pixmap2->scaled(ui->img_in01->size(), Qt::KeepAspectRatio);
    ui->img_in01->setScaledContents(true);
    ui->img_in01->setPixmap(*pixmap2);
    QPixmap *pixmap3 = new QPixmap(p->in_02);
    pixmap3->scaled(ui->img_in02->size(), Qt::KeepAspectRatio);
    ui->img_in02->setScaledContents(true);
    ui->img_in02->setPixmap(*pixmap3);
}

//返回酒店查询界面
void UserDialog::on_pushButton_clicked()
{
    ui->tabWidget_2->hide();
    Username = ui->Name->text();
    setordertable();
}
//返回查询界面
void UserDialog::on_pushButton_4_clicked()
{
    ui->tabWidget_2->hide();
    Username = ui->Name->text();
    setordertable();
}
//插入数据
bool UserDialog::insertdata()
{
    HotelNode* p = List->first;
    while(p)
    {
        if(p->name == Hotel)
            break;
        p = p->next;
    }
    float discount = p->discount;
    int singlePrice;
    QString RoomType;
    QString Sex;
    int type = ui->typebox->currentIndex();
    switch (type) {
    case 0:
        RoomType = "单人标间";
        singlePrice = p->psgl;
        p->sglroom--;
        break;
    case 1:
        RoomType = "双人标间";
        singlePrice = p->pdbl;
        p->dblroom--;
        break;
    case 2:
        RoomType = "大床房";
        singlePrice = p->pbbd;
        p->bbdroom--;
        break;
    case 3:
        RoomType = "豪华套房";
        singlePrice = p->suite;
        p->suite--;
        break;
    }
    int sex = ui->Sex->currentIndex();
    switch (sex) {
    case 0:
        Sex = "男";
        break;
    case 1:
        Sex = "女";
        break;
    }
    QString Username = ui->Name->text().trimmed();
    QString Phonenumber = ui->Phonenumber->text().trimmed();
    QString Checkindate = ui->checkindate->date().toString();
    QString Daynumber = QString::number(ui->Daynumber->value());
    QString Number = QString::number(ui->Number->value());
    float totalPrice = singlePrice*(Number.toInt())*(Daynumber.toInt())*(1-discount);
    QString Price = QString::number(singlePrice);
    QString TotalPrice = QString::number(totalPrice);
    QString Discount = QString::number(discount);
    QString No = Daynumber+Number+QString("2018")+Username;
    QString Orderstatus = "已下单";
    connectdb();
    QSqlQuery query(db);
    if((type==0&&p->sglroom==0)||(type==1&&p->dblroom==0)||(type==2&&p->bbdroom==0)||(type==3&&p->suite==0))
    {
        QMessageBox::warning(NULL,"Warning","该房型无剩余房间！",QMessageBox::Ok);
        return false;
    }
   //如果填写正确，生成一条订单数据，并存入数据库。
    else{
        if(Number!="0"&&Daynumber!="0"&&Username!=""&&Sex!=""&&Phonenumber!="")
    {
        QString insert = "insert into OrderInfo(Username,Sex,Phonenumber,Hotel,RoomType,Daynumber,Number,Price,TotalPrice,Discount,CheckinDate,OrderStatus,No)";
        insert += QString(" VALUES('%1','%2','%3','%4','%5','%6','%7','%8','%9'")
                .arg(Username)
                .arg(Sex)
                .arg(Phonenumber)
                .arg(p->name)
                .arg(RoomType)
                .arg(Daynumber)
                .arg(Number)
                .arg(Price)
                .arg(TotalPrice);
        insert += QString(",'%10','%11','%12','%13')")
                .arg(Discount)
                .arg(Checkindate)
                .arg(Orderstatus)
                .arg(No);
        bool ok = query.exec(insert);
        return ok;
    }
        //如果信息填写错误，弹出提示框，提示重新输入。
        else {
            QMessageBox::warning(NULL,"order","数据不可为空！请重试。",QMessageBox::Ok);
            ui->Name->clear();
            ui->Sex->clear();
            ui->Phonenumber->clear();
            ui->Name->setFocus();
        }
    }
}


//下面是下单界面的操作函数
void UserDialog::on_Submit_clicked()
{
    Hotel = ui->Hotel->text();
    HotelNode* p = List->first;
    while(p)
    {
        if(p->name == Hotel)
            break;
        p = p->next;
    }
        bool ok = insertdata();
        if(ok)
        {
               QMessageBox::information(NULL,"Order","成功生成订单！",QMessageBox::Ok);
               QSqlQuery query(db);
               query.prepare("update HotelInfo set Singleroom=?,Doubleroom=?,Bigbedroom=?,Suiteroom=? where HotelName=?");
               query.addBindValue(QString::number(p->sglroom));
               query.addBindValue(QString::number(p->dblroom));
               query.addBindValue(QString::number(p->bbdroom));
               query.addBindValue(QString::number(p->suite));
               query.addBindValue(p->name);
               query.exec();
        }
        else   QMessageBox::information(NULL,"Order","生成订单失败!",QMessageBox::Ok);


    db.close();
}

void UserDialog::receiveData(QString data)
{
    //获取传递过来的数据
    this->Username = data;
    QString hello = "Hello!"+data;
    hello += QString("!");
    ui->hello->setText(hello);
    ui->Name->setText(Username);
    ui->Name->setEnabled(false);
    setordertable();
}

//创建订单链表
void UserDialog::createorderlist()
{
    QSqlQuery query(db);
    query.exec("select *from OrderInfo");
    query.first();
    QString username = query.value(0).toString();
    QString sex = query.value(1).toString();
    QString phonenumber = query.value(2).toString();
    QString hotel = query.value(3).toString();
    QString roomtype = query.value(4).toString();
    int daynumber = query.value(5).toInt();
    int number = query.value(6).toInt();
    int price = query.value(7).toInt();
    float discount = query.value(9).toFloat();
    QString checkindate = query.value(10).toString();
    QString leavedate = query.value(11).toString();
    QString orderstatus = query.value(12).toString();
    ordernode* First = new ordernode(username,sex,phonenumber,hotel,roomtype,daynumber,number,price,discount,checkindate,leavedate,orderstatus);
    Orderlist = new order (First);

    while(query.next())
    {
            QString username = query.value(0).toString();
            QString sex = query.value(1).toString();
            QString phonenumber = query.value(2).toString();
            QString hotel = query.value(3).toString();
            QString roomtype = query.value(4).toString();
            int daynumber = query.value(5).toInt();
            int number = query.value(6).toInt();
            int price = query.value(7).toInt();
            float discount = query.value(9).toFloat();
            QString checkindate = query.value(10).toString();
            QString leavedate = query.value(11).toString();
            QString orderstatus = query.value(12).toString();
            Orderlist->insert(username,sex,phonenumber,hotel,roomtype,daynumber,number,price,discount,checkindate,leavedate,orderstatus);
            (Orderlist->count)++;

    }
}

//用于将一个结点的数据显示在一行中对应单元格中的函数
void UserDialog::setorderitem(int i, ordernode *p)
{
    ui->ordertable->setItem(i,0,new QTableWidgetItem(p->hotel));
    ui->ordertable->setItem(i,1,new QTableWidgetItem(p->roomtype));
    ui->ordertable->setItem(i,2,new QTableWidgetItem(QString::number(p->daynumber)));
    ui->ordertable->setItem(i,3,new QTableWidgetItem(p->checkindate));
    ui->ordertable->setItem(i,4,new QTableWidgetItem(QString::number(p->totalprice)));
    ui->ordertable->setItem(i,5,new QTableWidgetItem(p->orderstatus));
}

//用于将当前用户的订单全部显示在界面中的函数
void UserDialog::setordertable()
{
    QHeaderView* headerView = ui->ordertable->verticalHeader();
    headerView->setHidden(true);
    //创建链表并把数据都显示在表格中
    connectdb();
    createorderlist();
    ordernode* p = Orderlist->first;


    int j = 0;
    do{
        if(p->username == Username)
        {
            j++;
        }
        p = p->next;

        }while(p);
    p = Orderlist->first;
    ui->ordertable->setRowCount(j);

    int i = 0;
    do{
        if(p->username == Username)
        {
            setorderitem(i,p);
            i++;
        }
        p = p->next;

        }while(p);
    //
    ui->ordertable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void UserDialog::on_ordertable_cellDoubleClicked(int row, int column)
{
    ui->box->show();
    Hotel = ui->ordertable->item(row,0)->text();
    QString type = ui->ordertable->item(row,1)->text();
    QString dn = ui->ordertable->item(row,2)->text();
    QString date = ui->ordertable->item(row,3)->text();
    ordernode* p = Orderlist->first;
    while(p)
    {
        if((p->hotel == Hotel)&&(p->roomtype == type)&&(QString::number(p->daynumber)==dn)&&(p->checkindate==date))
            break;
        p = p->next;
    }
    ui->No->setText(p->No);
    ui->OrderStatus->setText(p->orderstatus);
    ui->Hotelname->setText(p->hotel);
    ui->TotalPrice->setText(QString::number(p->totalprice));
    ui->Room->setText(p->roomtype);
    if(p->orderstatus=="已下单")
        {
        ui->pay->show();
    }
    else if(p->orderstatus=="已完成")
    {
        ui->evaluate->show();
    }
    else if(p->orderstatus=="已支付")
        {
            ui->refee->show();
        }
        else ui->Return->show();
}

void UserDialog::on_evaluate_clicked()
{
    ui->valuebox->show();
    Hotel = ui->Hotelname->text();
}
//支付按钮
void UserDialog::on_pay_clicked()
{

    Hotel = ui->Hotelname->text().trimmed();
    QString No = ui->No->text().trimmed();
    QSqlQuery query(db);
    query.prepare("update OrderInfo set OrderStatus=? where No=?");
    query.addBindValue("已支付");
    query.addBindValue(No);
    bool ok = query.exec();
    if(ok)
    {
        QMessageBox::information(NULL,"支付","付款成功！",QMessageBox::Ok);
    }
    else QMessageBox::information(NULL,"支付","付款失败！",QMessageBox::Ok);
    ui->pay->hide();
    ui->evaluate->hide();
    ui->box->hide();
}
//返回按钮
void UserDialog::on_Return_clicked()
{
    ui->box->hide();
    ui->Return->hide();
}
//提交按钮
void UserDialog::on_submit_clicked()
{
    int evalution = ui->value->text().toInt();
    QString comment = ui->comment->text();
    QString No = ui->No->text();
    QSqlQuery query(db);
    query.prepare("update OrderInfo set Evaluation=?,Comment=? where No=?");
    query.addBindValue(QString::number(evalution));
    query.addBindValue(comment);
    query.exec(No);
    ui->pay->hide();
    ui->evaluate->hide();
    ui->box->hide();
}
//退出
void UserDialog::on_pushButton_3_clicked()
{
    this->close();
    db.close();
}
//刷新
void UserDialog::on_pushButton_2_clicked()
{
    Username = ui->Name->text();
    setordertable();
}



void UserDialog::on_refee_clicked()
{
    Hotel = ui->Hotelname->text().trimmed();
    QString No = ui->No->text().trimmed();
    QSqlQuery query(db);
    query.prepare("update OrderInfo set OrderStatus=? where No=?");
    query.addBindValue("已退款");
    query.addBindValue(No);
    bool ok = query.exec();
    if(ok)
    {
        QMessageBox::information(NULL,"退款","退款成功！",QMessageBox::Ok);
    }
    else QMessageBox::information(NULL,"退款","退款失败！",QMessageBox::Ok);
    ui->refee->hide();
    ui->evaluate->hide();
    ui->box->hide();
}
