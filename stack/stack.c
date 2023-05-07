#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


int stackInit(IntStack *self) {	
	self->first = NULL; 	// self->first  =  (*self).first
	self->last = NULL;
	return 0;
}

void stackRelease(IntStack *self) {
	while (!stackIsEmpty(self)) {
		stackPop(self);
	}	
}

void stackPush(IntStack *self, int i) {
	StackElem *elem = (StackElem*) malloc(sizeof(StackElem));
	elemInit(elem, i);

	if (self->first == NULL) {
		self->first = elem;
		self->last = elem;
	} else {
		elem->next = self->first;
		self->first->prev = elem;
		self->first = elem;
	}
}

int stackTop(const IntStack *self) {
	if (self->first == NULL) {
		fprintf(stderr, "Stack is empty, cannot inspect top!\n");
		exit(ERROR_TOP);
	}
	return self->first->value;
}

int stackPop(IntStack *self) {
	if (self->first == NULL) {
		fprintf(stderr, "Stack is empty, cannot pop!\n");
		exit(ERROR_POP);
	}
	StackElem *toRemove = self->first;
	int value = toRemove->value;
	
	if (toRemove->next == NULL) {
		self->first = NULL;
		self->last = NULL;
	} else {
		self->first = toRemove->next;
		self->first->prev = NULL;
	}
	free(toRemove);
	return value;
}

int stackIsEmpty(const IntStack *self) {
	return self->first == NULL;
}

void stackPrint(const IntStack *self) {
	StackElem *iter = self->first;
	printf("[TOP]\n");
	while (iter != NULL) {
		printf("%d\n", iter->value);
		iter = iter->next;
	}
	printf("[BOTTOM]\n");
}

