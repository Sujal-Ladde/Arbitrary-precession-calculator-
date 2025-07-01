#include "APC_DLL.h"

/*
=================================================================================
                                MAIN FUNCTION
=================================================================================
*/

/*
 * Functionality: Entry point of the precision calculator.
 * Logic: Parses command-line arguments, determines the operation (+, -, *, /),
 *        and calls the corresponding arithmetic function on the DLL-represented
 * numbers. Arguments: argc (argument count), argv (argument vector - CLI input)
 * Returns: int (exit code)
 */

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("Error: Too few arguments.\nUsage: ./a.out <operand1> <operator> "
           "<operand2>\n");
    return 1;
  }

  char *op1_str = argv[1];
  char *op_char = argv[2];
  char *op2_str = argv[3];

  // --- Parsing Operand 1  ---
  char sign_op1 = '+';
  int i = 0;
  if (op1_str[0] == '-') {
    sign_op1 = '-';
    i++;
  } else if (op1_str[0] == '+') {
    i++;
  }
  while (op1_str[i] == '0' && op1_str[i + 1] != '\0') {
    i++;
  } // Skip leading zeros, but keep one if it's the only digit

  // --- Parsing Operand 2 ---
  char sign_op2 = '+';
  int j = 0;
  if (op2_str[0] == '-') {
    sign_op2 = '-';
    j++;
  } else if (op2_str[0] == '+') {
    j++;
  }
  while (op2_str[j] == '0' && op2_str[j + 1] != '\0') {
    j++;
  }

  // --- Division by Zero Check ---
  if (op_char[0] == '/' && op2_str[j] == '0' && op2_str[j + 1] == '\0') {
    printf("Error: Division by zero.\n");
    return 1;
  }

  // --- Create Linked Lists ---
  DLL *op1_head = NULL, *op1_tail = NULL;
  while (op1_str[i] != '\0') {
    if (!isdigit(op1_str[i])) {
      printf("Error: Invalid number %s\n", op1_str);
      return 1;
    }
    insert_last(&op1_head, &op1_tail, op1_str[i] - '0');
    i++;
  }

  DLL *op2_head = NULL, *op2_tail = NULL;
  while (op2_str[j] != '\0') {
    if (!isdigit(op2_str[j])) {
      printf("Error: Invalid number %s\n", op2_str);
      return 1;
    }
    insert_last(&op2_head, &op2_tail, op2_str[j] - '0');
    j++;
  }

  char sign_res = '+';
  DLL *result_head = NULL;
  int magnitude_compare = compare_DLL(op1_head, op2_head);

  // --- Perform Operation ---
  switch (op_char[0]) {
  case '+':
    if (sign_op1 == sign_op2) {
      sign_res = sign_op1;
      result_head = addition(op1_tail, op2_tail);
    } else {
      if (magnitude_compare >= 0) { // |op1| >= |op2|
        sign_res = sign_op1;
        result_head = subtraction(op1_tail, op2_tail);
      } else { // |op1| < |op2|
        sign_res = sign_op2;
        result_head = subtraction(op2_tail, op1_tail);
      }
    }
    break;

  case '-':
    if (sign_op1 != sign_op2) {
      sign_res = sign_op1;
      result_head = addition(op1_tail, op2_tail);
    } else {
      if (magnitude_compare >= 0) { // |op1| >= |op2|
        sign_res = sign_op1;
        result_head = subtraction(op1_tail, op2_tail);
      } else { // |op1| < |op2|
        sign_res =
            (sign_op2 == '+') ? '-' : '+'; // Result sign is opposite of op2
        result_head = subtraction(op2_tail, op1_tail);
      }
    }
    break;

  case 'x':
    result_head = multiplication(op1_tail, op2_tail);
    if (sign_op1 != sign_op2) {
      sign_res = '-';
    }
    break;

  case '/':
    result_head = division(op1_head, op2_head);
    if (result_head == NULL) { // Check for sentinel
      printf("Error: Division by zero.\n");
      return 1;
    }
    if (sign_op1 != sign_op2) {
      sign_res = '-';
    }
    break;

  default:
    printf("Error: Invalid operator '%s'. Use +, -, x, /\n", op_char);
    return 1;
  }

  // --- Print Result ---
  printf("Result: ");
  // Don't print sign if result is 0
  if (result_head->data == 0 && result_head->next_node == NULL) {
    // It's zero, no sign.
  } else if (sign_res == '-') {
    printf("%c", sign_res);
  }

  print_DLL(result_head);
  printf("\n");

  // --- Cleanup ---
  destroy_DLL(&op1_head);
  destroy_DLL(&op2_head);
  destroy_DLL(&result_head);

  return 0;
}