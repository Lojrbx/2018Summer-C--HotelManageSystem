#ifndef HOTELLIST_H
#define HOTELLIST_H
#include<QString>
#include<QPixmap>
#include"list.h"
//酒店表格内容包括：酒店名、城市、具体地址、单人标间余量、
//双人标间余量、大床房余量、套房余量、优惠（折扣）、已完成订单总数、评分（满分为5）、
//客房描述、酒店电话、图片
class HotelNode
{
public:
    HotelNode(QString Name, QString City, QString Address, int Sglroom, int Psgl, int Dblroom, int Pdbl,
              int Bbdroom, int Pbbd, int Suite, int Psuite, float Discount, float Evaluation, QString Dial, QString Discription, QString Outside, QString IN_01, QString IN_02, QString Password);
    HotelNode *next;
    QString name;
    QString city;
    QString address;
    int sglroom;
    int psgl;
    int dblroom;
    int pdbl;
    int bbdroom;
    int pbbd;
    int suite;
    int psuite;
    float discount;
    float evaluation;
    QString dial;
    QString discription;
    int price;
    QString outside;
    QString in_01;
    QString in_02;
    QString password;
};


class hotellist
{
public:
    hotellist(HotelNode *First);
    //用于在尾部添加结点
    void insert(QString Name,QString City,QString Address,int Sglroom,int Psgl,int Dblroom,int Pdbl,
                int Bbdroom,int Pbbd,int Suite,int Psuite,float Discount,float Evaluation,QString Dial,QString Discription,QString Outside,QString IN_01,QString IN_02,QString Password);
   hotellist* copylist();
    HotelNode *first;
    int count;
};

#endif // HOTELLIST_H
