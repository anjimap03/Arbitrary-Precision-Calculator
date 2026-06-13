#ifndef HEADER_H
#define HEADER_H
#include<stdio.h>
#define SUCCESS 1
#define FAILURE 0
typedef struct node
{
    int data;
    struct node*prev;
    struct node*next;
}apc;
typedef struct node2
{
    int data;
    struct node*link;
}sll;
int dl_insert_last(apc **head, apc **tail, int data);
int dl_insert_first(apc**head,apc**tail, int data);
int dl_delete_list(apc **head, apc **tail);
int dl_delete_first(apc**head,apc **tail);
int dl_delete_last(apc**head, apc **tail);
void print_list(apc *head, int sign);
int compare_list(apc *h1, apc *h2);
int add(apc*tail1,apc*tail2,apc**reshead,apc**restail);
int sub(apc*tail1,apc*tail2,apc**reshead,apc**restail);
int multi(apc*tail1,apc*tail2,apc**reshead,apc**restail);
void division(apc *tail1, apc *tail2, apc **reshead, apc **restail);
#endif