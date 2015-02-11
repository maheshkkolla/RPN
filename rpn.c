#include "rpn.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

void stringCopy(char *source, char **destination, int from, int sizeOfDestination) {
	int destinationIndex, sourceIndex = from;
	for (destinationIndex = 0; destinationIndex < sizeOfDestination; ++destinationIndex, ++sourceIndex) {
		(*destination)[destinationIndex] = source[sourceIndex];
	}
}

int isCharSpaceOrNull(char character) {
	return (character == ' ' || (int)character == (int)0);
}

void insertTokenToTokens(LinkedList *tokens, char **token) {
	NodePtr node = create_node(*token);
	add_to_list(tokens, node);
}

int makeToken(char *expression, int tokenStartIndex, LinkedList *tokens, int index) {
	int sizeOfToken = (index - tokenStartIndex) - 1;
	if(sizeOfToken > 0){
		char *token = calloc(sizeOfToken+1,1);
		stringCopy(expression,&token,tokenStartIndex + 1 ,sizeOfToken);
		insertTokenToTokens(tokens, &token);
	}	
	return index;
}

LinkedList splitExpression(char *expression) {
	LinkedList tokens = createList();
	int count = strlen(expression), index, tokenStartIndex = -1;
	for (index = 0; index < count+1; ++index) {
		if(isCharSpaceOrNull(expression[index]))
			(tokenStartIndex = makeToken(expression,tokenStartIndex, &tokens, index));
	}
	return tokens;
}

int isOperand(void *data) {
	char *token = data;
	return(token[0] >= '0' && token[0] <= '9');
}

void pushTheOperandIntoStack(void *data, Stack *stack) {
	int *operand = malloc(sizeof(int));
	*operand = atoi(data);
	push(stack, operand);
}

int *popTwoOperands(Stack *stack){
	int *operands = malloc(sizeof(int)*2);
	operands[0] = *(int *)pop(stack);
	operands[1] = *(int *)pop(stack);
	return operands;
}

Status performOperation(char operator, int *operands) {
	switch(operator){
		case '+': return(Status){0,(operands[1] + operands[0])};
		case '-': return(Status){0,(operands[1] - operands[0])};
		case '*': return(Status){0,(operands[1] * operands[0])};
		case '/': return(Status){0,(operands[1] / operands[0])};
		case '^': return(Status){0,(operands[1] ^ operands[0])};
	}
	return (Status){1,0};
}

int isError(LinkedList tokens) {
	NodePtr walker;
	int countOfOperands = 0, countOfOperators = 1;
	for (walker = tokens.head; walker != NULL; walker=walker->next) {
		if(isOperand(walker->data))countOfOperands++; 
		else countOfOperators++;
	}
	return(countOfOperands != countOfOperators);
}

Status evaluate(char *expression) {
	Status status;
	Stack stack = createStack();
	LinkedList tokens = splitExpression(expression);
	NodePtr walker;
	if(isError(tokens)) return(Status){1,0};	
	for (walker = tokens.head; walker != NULL; walker=walker->next) {
		if(isOperand(walker->data))
			pushTheOperandIntoStack(walker->data, &stack);
		else {
			status = performOperation(*(char *)walker->data, popTwoOperands(&stack));
			push(&stack,&status.result);
		}
	}
	return status;
}

int getPrecedence(char operator) {
	switch(operator){
		case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
}

void insertOperatorsInStackToQueue(Stack *stack, Queue *outputQueue) {
	while(stack->top != NULL){
		enQueue(outputQueue, pop(stack));
	}
}

void queueToString(Queue *outputQueue, char *expression) {
	while(outputQueue->head != NULL){
		strcat(expression, (char *)deQueue(outputQueue));
		if(outputQueue->head != NULL)strcat(expression," ");
	}
}

int canPushTokenToStack(Stack stack, char token) {
	return(stack.top == NULL || token == '(' || (getPrecedence(token) > getPrecedence(*(char *)stack.top->data)));
}

int hasStackTopHigherPrecedence(char token, Stack stack) {
	return(getPrecedence(token) <= getPrecedence(*(char *)stack.top->data));
}

void popTillStackTopGetsLowerPrecedence(char token, Stack *stack, Queue *outputQueue) {
	while(hasStackTopHigherPrecedence(token, *stack)){
		enQueue(outputQueue, pop(stack));
		if(stack->top == NULL) break;
	}
}

void handleOperator(Stack *stack, NodePtr walker, char token, Queue *outputQueue) {
	if(canPushTokenToStack(*stack,token))
		push(stack, walker->data);
	else {
		popTillStackTopGetsLowerPrecedence(token, stack, outputQueue);
		if(token == ')') pop(stack); 
		else push(stack, walker->data);
	}
}

void handleEachToken(Stack *stack, NodePtr walker, Queue *outputQueue) {
	char token = *(char *)walker->data;
	if(isOperand(walker->data)) enQueue(outputQueue, walker->data);
	else handleOperator(stack, walker, token, outputQueue);
}

char *infixToPostfix(char *expression) {
	LinkedList tokens = splitExpression(expression);
	Queue outputQueue = createQueue();
	Stack stack = createStack();
	char *outputExpression = calloc(sizeof(char),strlen(expression));
	NodePtr walker;
	for (walker = tokens.head; walker != NULL; walker=walker->next) {
		handleEachToken(&stack, walker, &outputQueue);	
	}
	insertOperatorsInStackToQueue(&stack,&outputQueue);
	queueToString(&outputQueue, outputExpression);
	return outputExpression;
}