#ifndef DLL_H
#define DLL_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DLL_node {
    int data;
    struct DLL_node *next_node;
    struct DLL_node *previous_node;
  } DLL;
  

DLL *insert_first(DLL **head, DLL **tail, int data);
    
  
  // Inserts a digit at the end of the list
  DLL *insert_last(DLL **head, DLL **tail, int data);
    
  
  // Deletes the first node (MSD)
  DLL *delete_first(DLL **head, DLL **tail);
    
  
  // Deletes the last node (LSD)
  DLL *delete_last(DLL **head, DLL **tail);
    
  
  // Frees all nodes in the list
  void destroy_DLL(DLL **head);
    
  
  // Prints the list from head to tail
  void print_DLL(DLL *head);
   
  
  // Compares two numbers in DLLs
  int compare_DLL(DLL *op1_head, DLL *op2_head);


  // Removes leading zeros, leaving a single '0' if the result is zero
  void trim_leading_zeros(DLL **head, DLL **tail);
#endif