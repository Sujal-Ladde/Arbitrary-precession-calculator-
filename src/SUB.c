#include "SUB.h"
/*
=================================================================================
                             SUBTRACTION FUNCTION
=================================================================================
*/


/*
 * Functionality: Subtracts the second large number from the first, both
 * represented as DLLs. Logic: Performs digit-wise subtraction from LSB to MSB
 * while managing borrow. Arguments:
 *    - first_operand_tail: DLL* tail pointer of minuend
 *    - second_operand_tail: DLL* tail pointer of subtrahend
 *    - result_head: DLL* pointer to head of result (not used directly here)
 *    - result_tail: DLL** pointer to tail of result list
 * Returns: DLL* result_head (not explicitly returned; result_tail is updated)
 */

 DLL *subtraction(DLL *op1_tail, DLL *op2_tail) {
  DLL *result_head = NULL, *result_tail = NULL;
  DLL *t1 = op1_tail, *t2 = op2_tail;
  int borrow = 0;

  while (t1 != NULL) {
    int val1 = t1->data;
    int val2 = (t2 != NULL) ? t2->data : 0;

    val1 = val1 - borrow;
    if (val1 < val2) {
      val1 += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    int diff = val1 - val2;
    insert_first(&result_head, &result_tail, diff);

    t1 = t1->previous_node;
    if (t2)
      t2 = t2->previous_node;
  }
  trim_leading_zeros(&result_head, &result_tail);
  return result_head;
}
