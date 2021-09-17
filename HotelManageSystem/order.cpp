#include "order.h"
#pragma execution_character_set("utf-8")

//构造函数
ordernode::ordernode(QString Username,QString Sex,QString Phonenumber,QString Hotel,QString Roomtype,int Daynumber,int Number,int Price,float Discount,QString CheckinDate,QString LeaveDate,QString OrderStatus)
{
    username = Username;
    sex = Sex;
    phonenumber = Phonenumber;
    hotel = Hotel;
    roomtype = Roomtype;
    daynumber = Daynumber;
    number = Number;
    price = Price;
    discount = Discount;
    totalprice = price*daynumber*number*(1-discount);
    checkindate = CheckinDate;
    leavedate = LeaveDate;
    orderstatus = OrderStatus;
    No = QString::number(daynumber)+QString::number(number)+QString("2018")+username;
    next = NULL;

}

//在尾部插入节点
void order::insert(QString Username,QString Sex,QString Phonenumber,QString Hotel,QString Roomtype,int Daynumber,int Number,int Price,float Discount,QString CheckinDate,QString LeaveDate,QString OrderStatus)
{
    ordernode * NewNode = new ordernode(Username,Sex,Phonenumber,Hotel,Roomtype,Daynumber,Number,Price,Discount,CheckinDate,LeaveDate,OrderStatus);

    ordernode * p = this->first;
    while(p->next)
    {
        p = p->next;
    }
    p->next = NewNode;
}

//构造函数
order::order(ordernode *First)
{
    first = First;
    count = 1;
}
