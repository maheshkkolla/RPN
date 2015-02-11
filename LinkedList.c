#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

LinkedList createList(void) {
	LinkedList *list = malloc(sizeof(LinkedList));
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;	
	return *list;
}

NodePtr create_node(void *data) {
	NodePtr node = malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

int add_to_list(LinkedList * list,Node * node) {
	if(list->tail==NULL) list->head = node;
	else list->tail->next = node;
	list->tail = node;
	list->count = list->count + 1;
	return 1;
}

void traverse(LinkedList list, traverseOperation operation) {
	NodePtr walker;
	for (walker = list.head; walker != NULL; walker=walker->next) {
		operation(walker->data);
	}
}

void *get_first_element(LinkedList list) {
	return list.head->data;
}

void *get_last_element(LinkedList list) {
	return list.tail->data;
}

void *getElementAt(LinkedList list, int index) {
	NodePtr walker= list.head;
	int i;
	if(index >= list.count)return NULL;
	for (i=0;i<index;i++) {
		walker=walker->next;
	}
	return (walker->data);
}

int indexOf(LinkedList list, void *element) {
	NodePtr walker;
	int index = -1, count = 0;
	for (walker= list.head; walker != NULL; walker = walker->next) {
		if(walker->data == element){
			index = count;
			break;
		}
		count++;
	}
	return index;
}

void *deleteElementAt(LinkedList *list, int index) {
	NodePtr walker= list->head;
	int i;
	if(index >= list->count)return NULL;
	for (i=0;i<index-1;i++) {
		walker=walker->next;
	}
	walker->next = walker->next->next;
	list->count--;
	return walker->next;
}


