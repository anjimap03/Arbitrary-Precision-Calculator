#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"header.h"
int dl_insert_last(apc **head, apc **tail, int data)
{
    apc*new=malloc(sizeof(apc));// Allocate memory for new node
    if(new==NULL)// Check memory allocatio
    return FAILURE;
    new->data=data;// Assign data
    new->prev=NULL;// Initialize prev
    new->next=NULL;// Initialize next
    if(*head==NULL)// If list is empty
    {
        *head=new;// Set head to new node
        *tail=new;// Set tail to new node
    }
    else
    {
        (*tail)->next =new;// Link last node to new node
        new->prev=*tail;// Set new node's prev
        *tail=new;// Update tail
    }
    return SUCCESS;
}
int dl_insert_first(apc**head,apc**tail, int data)
{
    apc *new = malloc(sizeof(apc));// Allocate memory for new node
    if (new == NULL) 
    return FAILURE;// Check memory allocation

    new->data = data;// Assign data
    new->prev = NULL;// Initialize prev
    new->next = NULL;// Initialize next

    if (*head == NULL)// If list is empty
    {
        *head = new;// Set head to new node
        *tail = new;// Set tail to new node
    }
    else
    {
        (*head)->prev = new;// Set old head's prev to new
        new->next = *head;// Link new node to old head
        *head = new;// Update head
    }
    return SUCCESS;// Return success
}
int dl_delete_list(apc **head, apc **tail)
{
    if (*head == NULL) // Check if list is empty
    return FAILURE; 

    apc *temp = *head; // Start from head

    while (temp != NULL) // Traverse the list
    {
        *head = temp->next; // Move head to next node
        free(temp); // Free current node
        temp = *head; // Update temp
    }

    *tail = NULL; // Set tail to NULL after deletion
    return SUCCESS; // Return success
}
int dl_delete_first(apc**head,apc **tail)
{
    if(*head==NULL)//check if list is empty
    return FAILURE;
    if((*head)->next==NULL)//if only one node exist
    {
        free(*head);//free the only node
        *head=NULL;//set head to null
        *tail=NULL;//set tail to null
    }
    else
    {
        apc*temp=*head;// Store current head
        *head=(*head)->next;// Move head to next node
        (*head)->prev=NULL;// Set new head's prev to NULL
        free(temp);// Free old head
    }
    return SUCCESS;
}
int dl_delete_last(apc**head, apc **tail)
{
    if (*head == NULL)// Check if list is empty
     return FAILURE;
    if((*head)->next==NULL)// If only one node exists
    {
        free(*head);// Free the only node
        *head=NULL;// Set head to NULL
        *tail=NULL;// Set tail to NULL
    }
    else
    {
    apc *temp=(*tail)->prev;// Store second last node
    temp->next=NULL;// Set its next to NULL
    free(*tail);//update tail
    }
    return SUCCESS;

}
void print_list(apc *head, int sign)
{
    if (head == NULL)//checking head is null or not
    {
        printf("0\n");
        return;
    }

    if (sign == -1)//checking the sign
        printf("-");

    apc *temp = head;//declaring temp
    while (temp != NULL)//traversing the loop
    {
        printf("%d", temp->data);//printing 
        temp = temp->next;//changing the temp to next node
    }

    printf("\n");
}
