#ifndef ORDER_H
#define ORDER_H

#include<QString>
#include"hotellist.h"
//订单类
//用结点储存每个订单的信息

class ordernode
{
public:
    ordernode(QString Username,QString Sex,QString Phonenumber,QString Hotel,QString Roomtype,int Daynumber,int Number,int Price,float Discount,QString CheckinDate,QString LeaveDate,QString OrderStatus);
    QString username;
    QString sex;
    QString phonenumber;
    QString hotel;
    QString roomtype;
    int daynumber;
    int number;
    int price;
    float totalprice;
    float discount;
    QString checkindate;
    QString leavedate;
    QString orderstatus;
    QString No;
    int evaluation;
    QString comment;
    ordernode* next;

};

class order
{
public:
    order(ordernode* First);
    //用于在尾部添加结点
    void insert(QString Username,QString Sex,QString Phonenumber,QString Hotel,QString Roomtype,int Daynumber,int Number,int Price,float Discount,QString CheckinDate,QString LeaveDate,QString OrderStatus);
    ordernode* first;
    int count;
};

#endif // ORDER_H
