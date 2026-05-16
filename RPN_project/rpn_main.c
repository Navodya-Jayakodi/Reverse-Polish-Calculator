#include "rpn_stack.h"

// Stack Function Implementations
void CreateStack(Stack *s) {
    s->top = NULL;
    s->no_ele = 0;
    s->full = FALSE;
}

Boolean IsStackEmpty(const Stack *s) {
    return (s->top == NULL);
}

void Push(StackEntry item, Stack *s) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        s->full = TRUE;
        printf("Stack is full\n");
        return;
    }
    new_node->entry = item;
    new_node->next = s->top;
    s->top = new_node;
    s->no_ele++;
}

void Pop(StackEntry *item, Stack *s) {
    Node *np;
    if (IsStackEmpty(s)) {
        printf("Stack is empty\n");
        exit(1);
    }
    *item = s->top->entry;
    np = s->top;
    s->top = s->top->next;
    s->no_ele--;
    free(np);
}

StackEntry Top(const Stack *s) {
    if (IsStackEmpty(s)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->top->entry;
}

void DestroyStack(Stack *s) {
    Node *np;
    while (!IsStackEmpty(s)) {
        np = s->top;
        s->top = s->top->next;
        free(np);
    }
    s->no_ele = 0;
}

// Main Logic
int main(void) {
    Stack s;
    char instruction;
    StackEntry operand1, operand2, result;
    double input_val;

    CreateStack(&s);


    printf("        REVERSE POLISH CALCULATOR         \n");
    printf(" Instructions:\n");
    printf("  [?] : Enter and Push Number\n");
    printf("  [+] : Addition\n");
    printf("  [-] : Subtraction\n");
    printf("  [*] : Multiplication\n");
    printf("  [/] : Division\n");
    printf("  [=] : Display Top (Result)\n");
    printf("  [q] : Quit Program\n");

    while (1) {
        printf("> ");
        scanf(" %c", &instruction);

        if (instruction == '?') {
            printf("Enter number: ");
            scanf("%lf", &input_val);
            Push(input_val, &s);
        } else if (instruction == '+' || instruction == '-' || instruction == '*' || instruction == '/') {
            if (s.no_ele < 2) {
                printf("Error: Not enough operands\n");
                continue;
            }
            Pop(&operand2, &s);
            Pop(&operand1, &s);

            if (instruction == '+') result = operand1 + operand2;
            else if (instruction == '-') result = operand1 - operand2;
            else if (instruction == '*') result = operand1 * operand2;
            else if (instruction == '/') {
                if (operand2 == 0) {
                    printf("Error: Division by zero\n");
                    Push(operand1, &s);
                    Push(operand2, &s);
                    continue;
                }
                result = operand1 / operand2;
            }
            Push(result, &s);
        } else if (instruction == '=') {
            if (IsStackEmpty(&s)) {
                printf("Stack is empty\n");
            } else {
                printf("Current Result = %g\n", Top(&s));
            }
        } else if (instruction == 'q') {
            printf("Exiting Calculator...\n");
            break;
        } else {
            printf("Invalid Instruction\n");
        }
    }

    DestroyStack(&s);
    return 0;
}
