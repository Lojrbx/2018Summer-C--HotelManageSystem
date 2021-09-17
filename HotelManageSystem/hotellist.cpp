#include "hotellist.h"


//结点构造函数
HotelNode::HotelNode(QString Name, QString City, QString Address, int Sglroom, int Psgl, int Dblroom, int Pdbl,
                     int Bbdroom, int Pbbd, int Suite, int Psuite, float Discount, float Evaluation, QString Dial, QString Discription,QString Outside,QString IN_01,QString IN_02,QString Password)
{
    name = Name;
    city = City;
    address = Address;
    sglroom = Sglroom;
    psgl = Psgl;
    pdbl = Pdbl;
    pbbd = Pbbd;
    psuite = Psuite;
    dblroom = Dblroom;
    bbdroom = Bbdroom;
    suite = Suite;
    discount = Discount;
    evaluation = Evaluation;
    dial = Dial;
    discription = Discription;
    outside = Outside;
    in_01 = IN_01;
    in_02 = IN_02;
    next = NULL;
    price = psgl;
    password = Password;
    if(pdbl<price)price = pdbl;
    if(psuite<price)price = psuite;
    if(pbbd<price)price = pbbd;


}

//在后面插入结点
void hotellist::insert(QString Name, QString City, QString Address, int Sglroom, int Psgl, int Dblroom, int Pdbl,
                       int Bbdroom, int Pbbd, int Suite, int Psuite, float Discount, float Evaluation, QString Dial, QString Discription, QString Outside, QString IN_01, QString IN_02, QString Password)
{
    HotelNode * NewNode = new HotelNode(Name,City,Address,Sglroom,Psgl,Dblroom,Pdbl,
                                        Bbdroom,Pbbd,Suite,Psuite,Discount,Evaluation,Dial,Discription,Outside,IN_01,IN_02,Password);
    HotelNode * p = this->first;
    while(p->next)
    {
        p = p->next;
    }
    p->next = NewNode;
}

//链表构造函数
hotellist::hotellist(HotelNode* First)
{
    first = First;
    count = 1;
}

//复制一个新链表，与之前的链表完全相同，并返回新链表的地址
hotellist* hotellist::copylist()
{
    HotelNode* p = this->first;
    QString name = p->name;
    QString city = p->city;
    QString address = p->address;
    int sglroom = p->sglroom;
    int psgl = p->psgl;
    int dblroom = p->dblroom;
    int pdbl = p->pdbl;
    int bbdroom = p->bbdroom;
    int pbbd = p->pbbd;
    int suite = p->suite;
    int psuite = p->psuite;
    float discount = p->discount;
    float evaluation = p->evaluation;
    QString dial = p->dial;
    QString discription = p->discription;
    QString outside = p->outside;
    QString in_01 = p->in_01;
    QString in_02 = p->in_02;
    QString password = p->password;
    HotelNode *first = new HotelNode(name,city,address,sglroom,psgl,dblroom,pdbl,bbdroom,pbbd,suite,psuite,discount,evaluation,dial,discription,outside,in_01,in_02,password);
    hotellist *List = new hotellist(first);
    if(p->next!=NULL)p = p->next;
    while(p)
    {
        QString name = p->name;
        QString city = p->city;
        QString address = p->address;
        int sglroom = p->sglroom;
        int psgl = p->psgl;
        int dblroom = p->dblroom;
        int pdbl = p->pdbl;
        int bbdroom = p->bbdroom;
        int pbbd = p->pbbd;
        int suite = p->suite;
        int psuite = p->psuite;
        float discount = p->discount;
        float evaluation = p->evaluation;
        QString dial = p->dial;
        QString discription = p->discription;
        QString outside = p->outside;
        QString in_01 = p->in_01;
        QString in_02 = p->in_02;
        QString password = p->password;
        List->insert(name,city,address,sglroom,psgl,dblroom,pdbl,bbdroom,pbbd,suite,psuite,discount,evaluation,dial,discription,outside,in_01,in_02,password);
        p = p->next;

    }
    return List;
}
