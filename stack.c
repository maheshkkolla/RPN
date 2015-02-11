#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack createStack(void) {
	Stack *stack = malloc(sizeof(Stack));
	stack->top = NULL;
	stack->count = 0;
	return *stack;
}

int push(Stack *stack, void *data) {
	ItemPtr item = malloc(sizeof(Item));
	item->data = data;
	if(stack->count == 0) item->prev = NULL; 
	else{
		item->prev = stack->top;
		item->prev->next = item;	
	} 
	item->next = NULL;	
	stack->top = item;
	stack->count = stack->count + 1;	
	return 1;
}

void *pop(Stack *stack) {
	ItemPtr popedItem = stack->top->data;
	if(stack->count > 1){
		stack->top = stack->top->prev;
		stack->top->next->prev = NULL;
		stack->top->next = NULL;
	} else stack->top = NULL;
	stack->count = stack->count - 1;
	return popedItem;
}



