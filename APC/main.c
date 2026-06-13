/*
 Name        : Anjima P
 Date        : 03-02-2026

 Description :
 This project implements an Arbitrary Precision Calculator (APC)
 using Doubly Linked Lists in C. It allows arithmetic operations on
 very large integers that cannot be handled using standard data types.

 Each digit of a number is stored in a node of a doubly linked list.
 Arithmetic operations are performed digit-by-digit starting from
 the least significant digit, similar to manual calculations.

 The following functions are implemented:
  - dl_insert_first() : Inserts a digit at the beginning of the list
  - dl_insert_last()  : Inserts a digit at the end of the list
  - print_list()      : Displays the number stored in the linked list
  - compare_list()    : Compares two large numbers
  - add()             : Performs addition of two large numbers
  - sub()             : Performs subtraction of two large numbers
  - multi()           : Performs multiplication of two large numbers
  - division()        : Performs division using repeated subtraction
*/

#include<stdio.h>
#include<stdlib.h>
#include"header.h"
int main(int argc,char*argv[])
{
    apc*head1=NULL;//initialising the head for operand 1
    apc*head2=NULL;//initialising the head for operand 2
    apc*tail1=NULL;//initialising the tail for operand 1
    apc*tail2=NULL;//initialising the tail  for operand 2
    apc*reshead=NULL;//initialising the head for result
    apc*restail=NULL;//initialising the tail for operand 1
    if(argc!=4)//checking argument count
    {
        printf("Insufficient arguments \n");
        return FAILURE;
    }
    int sign1=1,sign2=1,i=0;
   if(argv[1][0] == '-')// checking  sign
    {
        sign1= -1;
        i = 1;
    }
    while (argv[1][i] != '\0')//traversing the loop
    {
        int num = argv[1][i] - '0';//changing the string to int
        dl_insert_last(&head1, &tail1, num);//inserting
        i++;
    }
    int j = 0;
    if (argv[3][0] == '-')//checking sign
    {
        sign2 = -1;
        j = 1;
    }
    while (argv[3][j] != '\0')//traversing the loop
    {
        int n = argv[3][j] - '0';//changing the string to int
        dl_insert_last(&head2, &tail2, n);//inserting
        j++;
    }
    switch(argv[2][0])// check operator from command line argument
    {
        case '+':
                {
                    reshead = restail = NULL;// initialize result list

                    if(sign1 == sign2)// if both numbers have same sign
                    {
                        add(tail1, tail2, &reshead, &restail);// perform addition
                        print_list(reshead, sign1);
                    }
                    else
                    {
                        int c = compare_list(head1, head2);// compare magnitudes of numbers

                        if(c == 2)
                            sub(tail1, tail2, &reshead, &restail), print_list(reshead, sign1);// subtract and print with sign1
                        else if(c == 1)
                            sub(tail2, tail1, &reshead, &restail), print_list(reshead, sign2);// subtract and print with sign2
                        else
                            printf("0\n");
                    }
                    break;
                }
        case '-':
                {
                    reshead = restail = NULL;// initialize result list
                    if(sign1 != sign2)// if numbers have different signs
                    {
                        add(tail1, tail2, &reshead, &restail);// perform addition
                        print_list(reshead, sign1);
                    }
                    else
                    {
                        int c = compare_list(head1, head2);// compare magnitudes

                        if(c == 2)
                        {  
                            sub(tail1, tail2, &reshead, &restail);// subtract numbers
                            print_list(reshead, sign1);
                        }
                        else if(c == 1)
                        {
                            sub(tail2, tail1, &reshead, &restail);// subtract numbers
                            print_list(reshead, -sign1);
                        }
                        else
                            printf("0\n"); // result is zero
                    }
                    break;
                }
        case 'x':
                {
                    reshead = restail = NULL;// initialize result list
                    multi(tail1, tail2, &reshead, &restail);// perform multiplication
                    int res_sign;// store result sign
                    if (sign1 != sign2)// if signs are different
                        res_sign = -1;// result is negative
                    else
                        res_sign = 1;// result is positive

                    print_list(reshead, res_sign);
                    break;
                }
        case '/':
                {
                    if (head2 == NULL)// check if divisor is zero
                    {
                        printf("Division by zero error\n");
                        return 0;
                    }
                    reshead = NULL;// initialize result head
                    restail = NULL;// initialize result tail
                    division(tail1, tail2, &reshead, &restail);// perform division
                    int res_sign;// store result sign
                    if (sign1 != sign2)// if signs are different
                        res_sign = -1;// result is negative
                    else
                        res_sign = 1;// result is positive

                    print_list(reshead, res_sign);
                    break;
                }
        default:
            printf("Invalid operator\n"); // handle invalid operator
            break;
    }
    return 0;
}