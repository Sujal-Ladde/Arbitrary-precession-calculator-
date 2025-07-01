#include "ADD.h"
/*
=================================================================================
                              ADDITION FUNCTION
=================================================================================
*/

/*
 * Functionality: Adds two large integers represented as doubly linked lists.
 * Logic: Performs digit-wise addition from LSB to MSB while handling carry
 * propagation. Arguments:
 *    - first_operand_tail: DLL* pointing to tail (LSB) of first number
 *    - second_operand_tail: DLL* pointing to tail (LSB) of second number
 *    - result_head: DLL* pointer to store result's head (not used directly
 * here)
 *    - result_tail: DLL** pointer to store result's tail
 * Returns: DLL* result_head (not explicitly returned; result_tail is updated)
 */

 DLL *addition(DLL *op1_tail, DLL *op2_tail) {
  DLL *result_head = NULL, *result_tail = NULL;
  DLL *t1 = op1_tail, *t2 = op2_tail;
  int carry = 0;

  while (t1 != NULL || t2 != NULL || carry != 0) {
    int val1 = (t1 != NULL) ? t1->data : 0;
    int val2 = (t2 != NULL) ? t2->data : 0;
    int sum = val1 + val2 + carry;

    carry = sum / 10;
    insert_first(&result_head, &result_tail, sum % 10);

    if (t1)
      t1 = t1->previous_node;
    if (t2)
      t2 = t2->previous_node;
  }
  trim_leading_zeros(&result_head, &result_tail);
  return result_head;
}