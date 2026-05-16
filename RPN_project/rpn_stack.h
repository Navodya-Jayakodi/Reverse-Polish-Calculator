#ifndef RPN_STACK_H
#define RPN_STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE, TRUE} Boolean;
typedef double StackEntry;

typedef struct node {
    StackEntry entry;
    struct node *next;
} Node;

typedef struct {
    int no_ele;
    Boolean full;
    Node *top;
} Stack;

// Function Prototypes
void CreateStack(Stack *s);
Boolean IsStackEmpty(const Stack *s);
void Push(StackEntry item, Stack *s);
void Pop(StackEntry *item, Stack *s);
StackEntry Top(const Stack *s);
void DestroyStack(Stack *s);

#endif
