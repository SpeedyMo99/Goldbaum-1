#ifndef STACK_H
#define STACK_H


#define NULL 0
#define ERROR_TOP -1
#define ERROR_POP -2


typedef struct {
	int value;
	struct StackElem *next;
	struct StackElem *prev;
} StackElem;

void elemInit(StackElem *elem, int value) {
	elem->value = value;
	elem->next = NULL;
	elem->prev = NULL;
}


typedef struct {
	StackElem *first;
	StackElem *last;
} IntStack;

extern int 
stackInit(IntStack *self);

extern void 
stackRelease(IntStack *self);

extern void 
stackPush(IntStack *self, int i);

extern int 
stackTop(const IntStack *self);

extern int 
stackPop(IntStack *self);

extern int 
stackIsEmpty(const IntStack *self);

extern void
stackPrint(const IntStack *self);


#endif
