#include "hotelmanagerdialog.h"
#include "ui_hotelmanagerdialog.h"
#pragma execution_character_set("utf-8")
hotelmanagerdialog::hotelmanagerdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hotelmanagerdialog)
{
    ui->setupUi(this);
    ui->groupBox->hide();
    count = 0;

}

//设置全部lineedit不可编辑
void hotelmanagerdialog::Unable()
{
    ui->hotelname->setEnabled(false);
    ui->address->setEnabled(false);
    ui->dial->setEnabled(false);
    ui->discription->setEnabled(false);
    ui->sglnum->setEnabled(false);
    ui->dblnum->setEnabled(false);
    ui->suitenum->setEnabled(false);
    ui->bbdnum->setEnabled(false);
    ui->discount->setEnabled(false);
    ui->psgl->setEnabled(false);
    ui->pdbl->setEnabled(false);
    ui->pbbd->setEnabled(false);
    ui->psuite->setEnabled(false);
}
//设置lineedit可编辑
void hotelmanagerdialog::Edable()
{
    ui->address->setEnabled(true);
    ui->dial->setEnabled(true);
    ui->discription->setEnabled(true);
    ui->sglnum->setEnabled(true);
    ui->dblnum->setEnabled(true);
    ui->suitenum->setEnabled(true);
    ui->bbdnum->setEnabled(true);
    ui->discount->setEnabled(true);
    ui->psgl->setEnabled(true);
    ui->pdbl->setEnabled(true);
    ui->pbbd->setEnabled(true);
    ui->psuite->setEnabled(true);

}
//连接数据库
void hotelmanagerdialog::dbconnect()
{
    //添加数据库驱动文件，这里使用的是sqlite


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
}
//将数据库中hotelinfo表中的数据转成链表
void hotelmanagerdialog::createlist()
{
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
//用指针p寻找本酒店，并将数据显示在屏幕上
void hotelmanagerdialog::searchthis()
{
    HotelNode* p = List->first;
    while(p)
    {
        if(p->name == Hotelname)break;
        p = p->next;
    }
    ui->hotelname->setText(p->name);
    ui->address->setText(p->address);
    ui->dial->setText(p->dial);
    ui->sglnum->setText(QString::number(p->sglroom));
    ui->dblnum->setText(QString::number(p->dblroom));
    ui->bbdnum->setText(QString::number(p->bbdroom));
    ui->discription->setText(p->discription);
    ui->suitenum->setText(QString::number(p->suite));
    ui->psgl->setText(QString::number(p->psgl));
    ui->pdbl->setText(QString::number(p->pdbl));
    ui->pbbd->setText(QString::number(p->pbbd));
    ui->psuite->setText(QString::number(p->psuite));
    ui->discount->setText(QString::number(p->discount));

}


//上传一条数据到数据库的待审核表中
bool hotelmanagerdialog::updatedata()
{
    HotelNode* p = List->first;
    while(p)
    {
        if(p->name == Hotelname)break;
        p = p->next;
    }
    QSqlQuery query(db);
    QString insert = "insert into AuditInfo(HotelName,Password,City,Address,Dial,Singleroom,SinglePrice,Doubleroom,DoublePrice,Bigbedroom,BbdPrice,Suiteroom,SuitePrice,Evaluation,Discount,Discription)";
    insert += QString(" VALUES('%1','%2','%3','%4','%5','%6','%7','%8','%9'")
            .arg(p->name)
            .arg(p->password)
            .arg(p->city)
            .arg(p->address)
            .arg(p->dial)
            .arg(p->sglroom)
            .arg(p->psgl)
            .arg(p->dblroom)
            .arg(p->pdbl);
    insert += QString(",'%10','%11','%12','%13','%14','%15','%16')")
            .arg(p->bbdroom)
            .arg(p->pbbd)
            .arg(p->suite)
            .arg(p->psuite)
            .arg(p->evaluation)
            .arg(p->discount)
            .arg(p->discription);
    bool ok = query.exec(insert);
    return ok;

}

hotelmanagerdialog::~hotelmanagerdialog()
{
    delete ui;
}
//接受信号的槽
void hotelmanagerdialog::receiveName(QString data)
{
    //获取传递过来的数据
    this->Hotelname = data;
    ui->hotelname->setText(Hotelname);
    Unable();
    dbconnect();
    createlist();
    searchthis();
    createorderlist();
    settable();
    evaluate();
}
//修改按键
void hotelmanagerdialog::on_pushButton_8_clicked()
{
    //使除酒店名外的lineEdit处于可修改状态
    Edable();    
}
//提交修改按键
void hotelmanagerdialog::on_pushButton_7_clicked()
{
    HotelNode* p = List->first;
    while(p)
    {
        if(p->name == Hotelname)break;
        p = p->next;
    }
    //用屏幕上修改后的lineEdit的内容更新p的数据域
    p->address = ui->address->text().trimmed();
    p->dial = ui->dial->text().trimmed();
    p->sglroom = ui->sglnum->text().trimmed().toInt();
    p->dblroom = ui->dblnum->text().trimmed().toInt();
    p->bbdroom = ui->bbdnum->text().trimmed().toInt();
    p->discription = ui->discription->text().trimmed();
    p->suite = ui->suitenum->text().trimmed().toInt();
    p->psgl = ui->psgl->text().trimmed().toInt();
    p->discount = ui->discount->text().trimmed().toFloat();
    p->pdbl = ui->pdbl->text().trimmed().toInt();
    p->pbbd = ui->pbbd->text().trimmed().toInt();
    p->psuite = ui->psuite->text().trimmed().toInt();
    bool ok = updatedata();
    if(ok)
    {
        QMessageBox::information(NULL,"Submitted","Successfully Submitted!",QMessageBox::Ok);

    }
    if(!ok)
    {
        QMessageBox::warning(NULL,"Wrong","Failed to Submit!",QMessageBox::Ok);
    }
}

//计算酒店的评分
void hotelmanagerdialog::evaluate()
{
    int sum=0;
    ordernode* p = Orderlist->first;
    while(p)
    {
        if(p->hotel==Hotelname&&(p->orderstatus=="已完成"))
        {
            count++;
            sum+=p->evaluation;
        }
        p=p->next;
    }
    //此处使用异常处理，防止count可能为0的情况
    try{
        if(count==0)throw 1;
        evaluation = (sum/count);
    }catch(int e){
        evaluation = 0;
    }
    HotelNode* q = List->first;
    while(q)
    {
        if(q->name==Hotelname)break;
        q = q->next;
    }
    q->evaluation = evaluation;
    QSqlQuery query(db);
    query.prepare("update HotelInfo set Evaluation=? where HotelName=?");
    query.addBindValue(QString::number(q->evaluation));
    query.addBindValue(q->name);
    query.exec();
}
//将order表中的数据转成链表
void hotelmanagerdialog::createorderlist()
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
//生成一行表格
void hotelmanagerdialog::setitem(int i,ordernode* p)
{
    ui->ordertable->setItem(i,0,new QTableWidgetItem(p->username));
    ui->ordertable->setItem(i,1,new QTableWidgetItem(p->sex));
    ui->ordertable->setItem(i,2,new QTableWidgetItem(p->phonenumber));
    ui->ordertable->setItem(i,3,new QTableWidgetItem(p->roomtype));
    ui->ordertable->setItem(i,4,new QTableWidgetItem(QString::number(p->daynumber)));
    ui->ordertable->setItem(i,5,new QTableWidgetItem(p->checkindate));
    ui->ordertable->setItem(i,6,new QTableWidgetItem(QString::number(p->number)));
    ui->ordertable->setItem(i,7,new QTableWidgetItem(QString::number(p->totalprice)));
    ui->ordertable->setItem(i,8,new QTableWidgetItem(p->orderstatus));

}

//生成表格
void hotelmanagerdialog::settable()
{
    QHeaderView* headerView = ui->ordertable->verticalHeader();
    headerView->setHidden(true);
    //创建链表并把数据都显示在表格中
    dbconnect();
    createorderlist();
    ordernode* p = Orderlist->first;
    int j =0;
    do{
        if(p->hotel == Hotelname)
        {
            j++;
        }
        p = p->next;

        }while(p);
    p = Orderlist->first;
    ui->ordertable->setRowCount(j);
    int i = 0;
    do{
        if(p->hotel == Hotelname)
        {
            setitem(i,p);
            i++;
        }
        p = p->next;

        }while(p);
    ui->ordertable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
//选择外景图片
void hotelmanagerdialog::on_chooseout_clicked()
{
        //定义文件对话框类
        QFileDialog *fileDialog = new QFileDialog(this);
        //定义文件对话框标题
        fileDialog->setWindowTitle(tr("打开图片"));
        //设置默认文件路径
        fileDialog->setDirectory(".");
        //设置文件过滤器
        fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
        //设置视图模式
        fileDialog->setViewMode(QFileDialog::Detail);
        QString fileName;
        if(fileDialog->exec())
            {
               fileName = fileDialog->selectedFiles().first();
            }
        ui->img_out->setText(fileName);
}
//选择内景图片01
void hotelmanagerdialog::on_choosein1_clicked()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    QString fileName;
    if(fileDialog->exec())
        {
           fileName = fileDialog->selectedFiles().first();
        }
    ui->img_in01->setText(fileName);
}
//选择内景图片02
void hotelmanagerdialog::on_choosein2_clicked()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    QString fileName;
    if(fileDialog->exec())
        {
           fileName = fileDialog->selectedFiles().first();
        }
    ui->img_in02->setText(fileName);
}
//按键 更新数据库中的 图片信息
void hotelmanagerdialog::on_updateimg_clicked()
{
    Hotelname = ui->hotelname->text().trimmed();
    QString img_out = ui->img_out->text();
    QString img_in1 = ui->img_in01->text();
    QString img_in2 = ui->img_in02->text();
    QSqlQuery query(db);
    query.prepare("update HotelInfo set img_out=?,img_in_01=?,img_in_02=? where HotelName=?");
    query.addBindValue(img_out);
    query.addBindValue(img_in1);
    query.addBindValue(img_in2);
    query.addBindValue(Hotelname);
    bool ok = query.exec();
    if(ok)
    {
        QMessageBox::information(NULL,"Info","上传成功！",QMessageBox::Ok);
    }
    else QMessageBox::information(NULL,"Info","上传失败",QMessageBox::Ok);
}

//退出键
void hotelmanagerdialog::on_exit_clicked()
{
    this->close();
    db.close();
}

void hotelmanagerdialog::on_ordertable_cellClicked(int row, int column)
{
    Username = ui->ordertable->item(row,0)->text();
    Sex = ui->ordertable->item(row,1)->text();
    Phonenumber = ui->ordertable->item(row,2)->text();
    Room = ui->ordertable->item(row,3)->text();
    Daynumber = ui->ordertable->item(row,4)->text();
    Checkindate = ui->ordertable->item(row,5)->text();
}

//修改按键，弹出隐藏的box
void hotelmanagerdialog::on_changestatus_clicked()
{
    Hotelname = ui->hotelname->text();
    createorderlist();
    ordernode* p = Orderlist->first;
    while(p)
    {
        if((p->hotel==Hotelname)&&(p->sex==Sex)&&(p->phonenumber==Phonenumber)&&(p->roomtype==Room)&&(p->checkindate==Checkindate))
        break;
        else p = p->next;
    }
    ui->No->setText(p->No);

    ui->Username->setText(p->username);
    ui->Total->setText(QString::number(p->totalprice));
    ui->groupBox->show();
    ui->No->setEnabled(false);
    ui->Total->setEnabled(false);
    ui->Username->setEnabled(false);
}

//保存按键，将修改的状态更新至数据库中
void hotelmanagerdialog::on_save_clicked()
{
    Hotelname = ui->hotelname->text();
    createorderlist();
    ordernode* p = Orderlist->first;
    while(p)
    {
        if((p->hotel==Hotelname)&&(p->sex==Sex)&&(p->phonenumber==Phonenumber)&&(p->roomtype==Room)&&(p->checkindate==Checkindate))
        break;
        else p = p->next;
    }

    int temp = ui->comboBox->currentIndex();
    switch (temp) {
    case 0:
        p->orderstatus = "已下单";
        break;
    case 1:
        p->orderstatus = "已支付";
        break;
    case 2:
        p->orderstatus = "已退款";
        break;
    case 3:
        p->orderstatus = "已入住";
        break;
    case 4:
        p->orderstatus = "已完成";
        break;
    }
    QSqlQuery query(db);
    query.prepare("update OrderInfo set OrderStatus=? where No=?");
    query.addBindValue(p->orderstatus);
    query.addBindValue(p->No);
    bool ok = query.exec();
    if(ok)
    {
        QMessageBox::information(NULL,"状态修改","修改成功！",QMessageBox::Ok);
    }
    else QMessageBox::information(NULL,"状态修改","修改失败！",QMessageBox::Ok);

    //如果状态修改为已完成，则对应订单的房间释放，相应的房间类型数量加1
    HotelNode* q = List->first;
    while(q)
    {
        if(q->name==Hotelname)break;
        q = q->next;
    }
    if(temp==4&&ok)
    {
        if(p->roomtype=="单人标间")
            q->sglroom++;
        if(p->roomtype=="双人标间")
            q->dblroom++;
        if(p->roomtype=="大床房")
            q->bbdroom++;
        if(p->roomtype=="豪华套房")
            q->suite++;
    }
    QSqlQuery que(db);
    que.prepare("update HotelInfo set Singleroom=?,Doubleroom=?,Bigbedroom=?,Suiteroom=? where HotelName=?");
    que.addBindValue(QString::number(q->sglroom));
    que.addBindValue(QString::number(q->dblroom));
    que.addBindValue(QString::number(q->bbdroom));
    que.addBindValue(QString::number(q->suite));
    que.addBindValue(q->name);
    que.exec();

    ui->groupBox->hide();
}

//刷新，重新载入表格。
void hotelmanagerdialog::on_refresh_clicked()
{
    Hotelname = ui->hotelname->text();
    createorderlist();
    settable();
}

void hotelmanagerdialog::on_exit_2_clicked()
{
    this->close();
    db.close();
}
