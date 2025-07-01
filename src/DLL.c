#include "DLL.h"


DLL *insert_first(DLL **head, DLL **tail, int data) {
  DLL *new_node = (DLL *)malloc(sizeof(DLL));
  if (new_node == NULL) {
    perror("Error: Memory allocation failed");
    exit(1);
  }
  new_node->data = data;
  new_node->previous_node = NULL;
  new_node->next_node = *head;

  if (*head != NULL) {
    (*head)->previous_node = new_node;
  } else {
    // If the list was empty, new node is also the tail
    *tail = new_node;
  }
  *head = new_node;
  return *head;
}

// Inserts a digit at the end of the list
DLL *insert_last(DLL **head, DLL **tail, int data) {
  if (*head == NULL) {
    return insert_first(head, tail, data);
  }

  DLL *new_node = (DLL *)malloc(sizeof(DLL));
  if (new_node == NULL) {
    perror("Error: Memory allocation failed");
    exit(1);
  }
  new_node->data = data;
  new_node->next_node = NULL;
  new_node->previous_node = *tail;

  if (*tail != NULL) {
    (*tail)->next_node = new_node;
  }
  *tail = new_node;
  return *tail;
}

// Deletes the first node (MSD)
DLL *delete_first(DLL **head, DLL **tail) {
  if (*head == NULL)
    return NULL;

  DLL *temp = *head;
  *head = (*head)->next_node;

  if (*head != NULL) {
    (*head)->previous_node = NULL;
  } else {
    // List is now empty
    *tail = NULL;
  }
  free(temp);
  return *head;
}

// Deletes the last node (LSD)
DLL *delete_last(DLL **head, DLL **tail) {
  if (*tail == NULL)
    return NULL;

  DLL *temp = *tail;
  *tail = (*tail)->previous_node;

  if (*tail != NULL) {
    (*tail)->next_node = NULL;
  } else {
    *head = NULL;
  }
  free(temp);
  return *tail;
}

// Frees all nodes in the list
void destroy_DLL(DLL **head) {
  DLL *current = *head;
  while (current != NULL) {
    DLL *next = current->next_node;
    free(current);
    current = next;
  }
  *head = NULL;
}

// Prints the list from head to tail
void print_DLL(DLL *head) {
  if (head == NULL) {
    printf("0");
    return;
  }
  DLL *temp = head;
  while (temp != NULL) {
    printf("%d", temp->data);
    temp = temp->next_node;
  }
}

// Compares two numbers in DLLs
int compare_DLL(DLL *op1_head, DLL *op2_head) {
  int len1 = 0, len2 = 0;
  DLL *t1 = op1_head, *t2 = op2_head;

  while (t1) {
    len1++;
    t1 = t1->next_node;
  }
  while (t2) {
    len2++;
    t2 = t2->next_node;
  }

  if (len1 > len2)
    return 1;
  if (len2 > len1)
    return -1;

  // Lengths are equal, compare digit by digit
  t1 = op1_head;
  t2 = op2_head;
  while (t1) {
    if (t1->data > t2->data)
      return 1;
    if (t2->data > t1->data)
      return -1;
    t1 = t1->next_node;
    t2 = t2->next_node;
  }

  return 0; // Numbers are equal
}

// Removes leading zeros, leaving a single '0' if the result is zero
void trim_leading_zeros(DLL **head, DLL **tail) {
  while (*head != NULL && (*head)->next_node != NULL && (*head)->data == 0) {
    delete_first(head, tail);
  }
}
