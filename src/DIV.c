#include "DIV.h"
/*
=================================================================================
                            DIVISION FUNCTION
=================================================================================
*/

/*
 * Functionality: Performs integer division between two large integers
 * represented as DLLs. Logic: Mimics long division. Repeatedly subtracts the
 * divisor from parts of the dividend, digit by digit. Arguments:
 *    - first_operand_tail: DLL* tail of dividend
 *    - second_operand_tail: DLL* tail of divisor
 *    - result_head: DLL* pointer to head of result (not used directly here)
 *    - result_tail: DLL** pointer to tail of result list
 * Returns: DLL* result_head (not explicitly returned; result_tail is updated)
 */

 DLL *division(DLL *op1_head, DLL *op2_head) {

  if (op2_head->data == 0 && op2_head->next_node == NULL) {
    return NULL; // Sentinel for division by zero
  }

  // If dividend < divisor, quotient is 0
  if (compare_DLL(op1_head, op2_head) < 0) {
    DLL *q_head = NULL, *q_tail = NULL;
    insert_last(&q_head, &q_tail, 0);
    return q_head;
  }

  DLL *quotient_head = NULL, *quotient_tail = NULL;
  DLL *current_dividend_head = NULL, *current_dividend_tail = NULL;
  DLL *temp_op1 = op1_head;

  while (temp_op1 != NULL) {
    // Bring down one digit
    insert_last(&current_dividend_head, &current_dividend_tail, temp_op1->data);
    trim_leading_zeros(&current_dividend_head, &current_dividend_tail);

    int count = 0;
    while (compare_DLL(current_dividend_head, op2_head) >= 0) {
      DLL *temp_sub =
          subtraction(current_dividend_tail,
                      op2_head); // Note: op2_head is wrong, should be tail

      // Correctly get tail of op2
      DLL *op2_tail = op2_head;
      while (op2_tail && op2_tail->next_node)
        op2_tail = op2_tail->next_node;

      DLL *new_dividend = subtraction(current_dividend_tail, op2_tail);
      destroy_DLL(&current_dividend_head);
      current_dividend_head = new_dividend;
      // Recalculate tail
      current_dividend_tail = current_dividend_head;
      if (current_dividend_tail) {
        while (current_dividend_tail->next_node)
          current_dividend_tail = current_dividend_tail->next_node;
      }

      count++;
    }

    insert_last(&quotient_head, &quotient_tail, count);
    temp_op1 = temp_op1->next_node;
  }

  trim_leading_zeros(&quotient_head, &quotient_tail);
  destroy_DLL(&current_dividend_head);
  return quotient_head;
}
