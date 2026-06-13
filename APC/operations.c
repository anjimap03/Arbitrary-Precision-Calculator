#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
int add(apc*tail1, apc*tail2, apc**reshead, apc**restail)
{
    int carry = 0, res = 0;// initialize carry and result digit
    apc *temp1 = tail1;// pointer to traverse first number from LSB
    apc *temp2 = tail2;// pointer to traverse second number from LSB

    while (temp1 != NULL || temp2 != NULL || carry)// loop while digits or carry exist
    {
        if (temp1 != NULL && temp2 != NULL)// if both numbers have digits
        {
            res = temp1->data + temp2->data + carry;// add both digits and carry
            temp1 = temp1->prev;// move to next digit of first number
            temp2 = temp2->prev;// move to next digit of second number
        }
        else if (temp1 != NULL)// if only first number has digits
        {
            res = temp1->data + carry;// add digit and carry
            temp1 = temp1->prev;// move to next digit of first number
        }
        else if (temp2 != NULL)// if only second number has digits
        {
            res = temp2->data + carry;// add digit and carry
            temp2 = temp2->prev;// move to next digit of second number
        }
        else
            res = carry;// if only carry is left

        if (res > 9)// if sum produces carry
        {
            carry = res / 10;// calculate new carry
            res = res % 10;// keep only single digit
        }
        else
            carry = 0;// reset carry if not needed

        dl_insert_first(reshead, restail, res);// insert result digit at front
    }
    return 0;
}
int sub(apc*tail1, apc*tail2, apc**reshead, apc**restail)
{
    int flag = 0, res = 0;// flag for borrow and result digit
    apc* temp1 = tail1;// pointer to traverse first number from LSB
    apc* temp2 = tail2;// pointer to traverse second number from LSB
    while (temp1 != NULL || temp2 != NULL)// loop through digits
    {
        if (flag == 1)// if previous digit borrowed
        {
            if (temp1->data == 0)// if current digit is zero
            {
                temp1->data = 9;// convert zero to nine after borrow
                flag = 1;// keep borrow for next digit
            }
            else
            {
                temp1->data = temp1->data - 1;// reduce digit by one
                flag = 0;// clear borrow
            }
        }
        if (temp1 != NULL && temp2 != NULL)// if both numbers have digits
        {
            if (temp1->data >= temp2->data)// if subtraction possible without borrow
            {
                res = temp1->data - temp2->data;// subtract digits
            }
            else
            {
                res = temp1->data + 10 - (temp2->data);// borrow and subtract
                flag = 1;// set borrow for next digit
            }
        }
        else if (temp1 != NULL && temp2 == NULL)// if only first number has digits
        {
            res = temp1->data;// copy remaining digit
        }
        dl_insert_first(reshead, restail, res);// insert result digit at front
        if (temp1 != NULL) temp1 = temp1->prev;// move to next digit of first number
        if (temp2 != NULL) temp2 = temp2->prev;// move to next digit of second number
        while (*reshead != NULL && (*reshead)->data == 0 && *reshead != *restail)// remove leading zeros
        {
            dl_delete_first(reshead, restail);// delete zero from front
        }
    }
}
int multi(apc *tail1, apc *tail2, apc **reshead, apc **restail)
{
    apc *temp1 = tail1;// pointer to traverse first number from LSB
    apc *temp2 = tail2;// pointer to traverse second number from LSB
    apc *res1head = NULL, *res1tail = NULL;// store final multiplication result
    int pos = 0;// position for place value shifting
    while (temp2 != NULL)// loop through each digit of second number
    {
        apc *partial_head = NULL, *partial_tail = NULL;// store partial product
        int carry = 0;// carry for multiplication
        temp1 = tail1;// reset first number pointer for each digit
        while (temp1 != NULL)// multiply one digit of second number with all digits of first
        {
            int res = temp1->data * temp2->data + carry;// multiply digits and add carry
            carry = res / 10;// calculate new carry
            res = res % 10;// get single digit result
            dl_insert_first(&partial_head, &partial_tail, res);// insert result digit at front
            temp1 = temp1->prev;// move to next digit of first number
        }
        if (carry)// if carry remains after multiplication
            dl_insert_first(&partial_head, &partial_tail, carry);// insert carry at front

        for (int i = 0; i < pos; i++)// add zeros based on digit position
            dl_insert_last(&partial_head, &partial_tail, 0);// append zero at end
        if (res1head == NULL)// if final result is empty
        {
            res1head = partial_head;// assign first partial product
            res1tail = partial_tail;// assign tail
        }
        else
        {
            apc *sum_head = NULL, *sum_tail = NULL;// store sum of partial and final result
            add(res1tail, partial_tail, &sum_head, &sum_tail);// add partial product to final result
            dl_delete_list(&res1head, &res1tail);// delete old final result list
            dl_delete_list(&partial_head, &partial_tail);// delete partial product list
            res1head = sum_head;// update final result head
            res1tail = sum_tail;// update final result tail
        }
        pos++;// increment position for next digit multiplication
        temp2 = temp2->prev;// move to next digit of second number
    }
    *reshead = res1head;// store final result head
    *restail = res1tail;// store final result tail
    while (*reshead && (*reshead)->data == 0 && *reshead != *restail)// remove leading zeros
    {
        dl_delete_first(reshead, restail);// delete zero at front
    }
    return 0;
}
void division(apc *tail1, apc *tail2, apc **reshead, apc **restail)
{
    if (tail2 == NULL)// if divisor is NULL (zero), return
        return;
    apc *temp1 = tail1;// pointer to traverse dividend from LSB
    apc *temph = NULL, *tempt = NULL;// temporary list to store dividend copy
    while (temp1 != NULL)// copy dividend into temporary list
    {
        dl_insert_first(&temph, &tempt, temp1->data);// insert digit into temp list
        temp1 = temp1->prev;// move to next digit of dividend
    }
    int count = 0;// store quotient count
    while (compare_list(temph, tail2) != 1)// while dividend >= divisor
    {
        apc *subhead = NULL, *subtail = NULL;// store subtraction result
        sub(tempt, tail2, &subhead, &subtail);// subtract divisor from dividend
        dl_delete_list(&temph, &tempt);// delete old dividend list
        temph = subhead;// update dividend head
        tempt = subtail;// update dividend tail
        count++;// increment quotient
    }
    if (count == 0)// if quotient is zero
    {
        dl_insert_last(reshead, restail, 0);// insert 0 as result
        return;
    }
    while (count > 0)// convert quotient number into list
    {
        dl_insert_first(reshead, restail, count % 10);// insert digit into result list
        count /= 10;// move to next digit
    }
    while (*reshead && (*reshead)->data == 0 && *reshead != *restail)// remove leading zeros
        dl_delete_first(reshead, restail);// delete zero from front
}
int compare_list(apc *h1, apc *h2)
{
    int l1 = 0, l2 = 0;// store lengths of both lists
    apc *t;// temporary pointer for traversal
    for (t = h1; t; t = t->next)// traverse first list
        l1++;// count nodes of first list
    for (t = h2; t; t = t->next)// traverse second list
        l2++;// count nodes of second list
    if (l1 < l2)// if first number has fewer digits
        return 1;// first number is smaller
    if (l1 > l2)// if first number has more digits
        return 2;// first number is larger
    while (h1 && h2)// if both have same length, compare digit by digit
    {
        if (h1->data < h2->data)// if current digit of first is smaller
            return 1;// first number is smaller
        if (h1->data > h2->data)// if current digit of first is larger
            return 2;// first number is larger
        h1 = h1->next;// move to next digit of first number
        h2 = h2->next;// move to next digit of second number
    }
    return 0;
}