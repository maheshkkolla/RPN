#include "rpn.h"
#include "expr_assert.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test_splitExpression_takes_simple_expression_and_gives_a_linkedList_by_splitting_as_tokens() {
	LinkedList tokens = splitExpression("2 3 +\0");
	assertEqual(tokens.count, 3);
	assertEqual(strcmp(tokens.head->data, "2"),0);
	assertEqual(strcmp(tokens.head->next->data,"3"), 0);
	assertEqual(strcmp(tokens.tail->data,"+"), 0);
}

void test_splitExpression_takes_expression_with_double_digits_and_gives_LinkedList_by_splitting_as_tokens() {
	LinkedList tokens = splitExpression("45 67 -\0");
	assertEqual(tokens.count, 3);
	assertEqual(strcmp(tokens.head->data, "45"),0);
	assertEqual(strcmp(tokens.head->next->data,"67"), 0);
	assertEqual(strcmp(tokens.tail->data,"-"), 0);
}

void test_splitExpression_takes_expression_with_three_digits_and_gives_LinkedList_by_splitting_as_tokens() {
	LinkedList tokens = splitExpression("245 567 *\0");
	assertEqual(tokens.count, 3);
	assertEqual(strcmp(tokens.head->data, "245"),0);
	assertEqual(strcmp(tokens.head->next->data,"567"), 0);
	assertEqual(strcmp(tokens.tail->data,"*"), 0);
}

void test_splitExpression_takes_simple_expression_with_more_spaces_should_also_gives_the_linkedList() {
	LinkedList tokens = splitExpression("   2    3    +        \0");
	assertEqual(tokens.count, 3);
	assertEqual(strcmp(tokens.head->data, "2"),0);
	assertEqual(strcmp(tokens.head->next->data,"3"), 0);
	assertEqual(strcmp(tokens.tail->data,"+"), 0);
}

void test_stringCopy_copies_the_string_from_source_to_destination() {
	char *source = "mahesh", *destination = calloc(7,1);
	stringCopy(source, &destination, 0, 6);
	assertEqual(strcmp(destination, source),0);
}

void test_stringCopy_copies_the_string_from_source_to_destination_from_specified_index() {
	char *source = "mahesh kumar", *destination = calloc(6,1);
	stringCopy(source, &destination, 7, 5);
	assertEqual(strcmp(destination, "kumar"),0);
}

void test_evaluate_takes_simple_expression_and_gives_the_result_of_expression() {
	char *expression = "2 3 +\0";
	Status status = evaluate(expression);
	assertEqual(status.error, 0);
	assertEqual(status.result, 5);
}

void test_evaluate_should_return_the_answer_for_complex_expressions(){
	char *expression = "2 2 2 * 2 - 3 + +";
	Status answer = evaluate(expression);
	assertEqual(answer.error, 0);
	assertEqual(answer.result, 7);
}

void test_evaluate_should_gives_the_error_if_there_is_more_operators_than_operands(){
	char *expression = "2 2 + +";
	Status status = evaluate(expression);
	assertEqual(status.error, 1);
}

void test_infixToPostfix_takes_simple_infix_expression_and_gives_back_postfix_expression() {
	char *expression = "3 + 2\0";
	char *postfix = infixToPostfix(expression);
	assertEqual(strcmp(postfix,"3 2 +"),0);
}

void test_infixToPostfix_takes_the_infix_expression_and_gives_as_postfix_expression() {
	char *expression = "3 + 4 * 2 / ( 1 - 5 ) ";
	char *postfixExpression = infixToPostfix(expression);
	assertEqual(strcmp(postfixExpression, "3 4 2 * 1 5 - / +"),0);
}