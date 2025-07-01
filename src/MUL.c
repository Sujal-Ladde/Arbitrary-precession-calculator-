
#include "MUL.h"
/*
=================================================================================
                            MULTIPLICATION FUNCTION
=================================================================================
*/

/*
 * Functionality: Multiplies two large integers represented as DLLs.
 * Logic: Uses a digit-wise multiplication approach (like manual
 * multiplication), storing intermediate sums and managing carry. Arguments:
 *    - first_operand_tail: DLL* tail pointer of the first number
 *    - second_operand_tail: DLL* tail pointer of the second number
 *    - result_head: DLL* pointer to head of result (not used directly here)
 *    - result_tail: DLL** pointer to tail of result list
 * Returns: DLL* result_head (not explicitly returned; result_tail is updated)
 */

 DLL *multiplication(DLL *op1_tail, DLL *op2_tail) {
  DLL *total_result_head = NULL, *total_result_tail = NULL;
  insert_last(&total_result_head, &total_result_tail,
              0); // Initialize result to 0

  DLL *t2 = op2_tail;
  int shift = 0;

  while (t2 != NULL) {
    DLL *partial_result_head = NULL, *partial_result_tail = NULL;
    DLL *t1 = op1_tail;
    int carry = 0;

    // Add trailing zeros for shifting
    for (int i = 0; i < shift; ++i) {
      insert_first(&partial_result_head, &partial_result_tail, 0);
    }

    while (t1 != NULL || carry != 0) {
      int val1 = (t1 != NULL) ? t1->data : 0;
      int product = (val1 * t2->data) + carry;
      carry = product / 10;
      insert_first(&partial_result_head, &partial_result_tail, product % 10);
      if (t1)
        t1 = t1->previous_node;
    }

    DLL *temp_sum = addition(total_result_tail, partial_result_tail);
    destroy_DLL(&total_result_head);
    total_result_head = temp_sum;

    // Update total_result_tail
    total_result_tail = total_result_head;
    if (total_result_tail) {
      while (total_result_tail->next_node) {
        total_result_tail = total_result_tail->next_node;
      }
    }

    destroy_DLL(&partial_result_head);
    t2 = t2->previous_node;
    shift++;
  }
  trim_leading_zeros(&total_result_head, &total_result_tail);
  return total_result_head;
}
