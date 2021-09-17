#include "list.h"


Node::Node(QString Username,QString Password )
{
    username = Username;
    password = Password;
    next = NULL;
}


void list::insert(QString Username,QString Password)
{
    Node * NewNode = new Node(Username,Password);
    Node * p = this->first;
    while(p->next)
    {
        p = p->next;
    }
    p->next = NewNode;
}


list::list(Node* First)
{
    first = First;
}

