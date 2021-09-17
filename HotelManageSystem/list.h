#ifndef LIST_H
#define LIST_H
#include<QString>

class Node
{
public:
    Node(QString Username,QString Password);
    Node *next;
    QString username;
    QString password;
};

class list
{
public:
    list(Node *First);
    //用于在尾部添加结点
    void insert(QString Username,QString Password );
    Node *first;
};
#endif // LIST_H
