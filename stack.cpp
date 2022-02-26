#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define NMAX 100                       //max number of elements

typedef int data_t;

enum STACK_ERRORS {                    //errors declaration

    STACK_ERROR_PUSH = 123,
    STACK_ERROR_POP = 456,
    STACK_ERROR_CTOR = -1,
};

struct stack {                          //stack declaration
    float elem[NMAX];                   //array for keeping elements

    size_t size;
    size_t cap;
    data_t* Data;
};

size_t Ctr(struct stack* stk, size_t cap) {

    if (cap < 0) {
        return STACK_ERROR_CTOR;
    }

    if (cap == 0) {
        stk->Data = NULL;
        stk->size = 0;
        stk->cap = 0;
    }

    if (cap > 0) {
        stk->cap = cap;
        stk->size = 0;

        StkMem(stk, cap);
    }

    return 0;
}

void Dtr(struct stack* stk) {
    stk->Data = NULL;
    stk->size = -123;
    stk->cap = -321;
}

size_t push(struct stack *stk, float f) {      //adding an element to stack
  
    if (stk->cap == stk->size) {
        StkMemInc(stk);
    }

    stk->Data[++stk->size] = f;
}

data_t pop(struct stack *stk) {         //delete an element from stack
  
    if (isempty(stk)) {
        printf("Atata! Nothing here");
    }

    else
    {
        return stk->Data[stk->size--];
    }

    if (stk->cap >= (stk->size * 4)) {
        StkMemDec(stk);
    }
}

int isempty(struct stack *stk) {      //is stack empty?
  
  if (stk->size == 0)    return 1;
  else return 0;
}

int getcount(struct stack *stk) {     //receiving the number of elements in stack
  return stk->size;
}

void stkPrint(struct stack *stk) {    //printing elements of stack
  
  int i;
  i = stk->size; // i - number of elements in stack

  if (isempty(stk) == 1) return;
  do {
    i--;
    printf("%f\n", stk->elem[i]);
  } while(i > 0);
}

size_t StkMem(struct stack* stk, size_t StartSize) {

    stk->cap = StartSize;
    stk->Data = (data_t*) calloc( (stk->cap + 2), sizeof(data_t));

    if (stk->Data == NULL) {
        printf("%s", "Error! No data in stack ((\n");
        return -2;
    }

    return 0;
}

size_t StkMemInc(struct stack* stk) {

    if (stk->cap == 0) 
        stk->cap = 2;
    else
        stk->cap *= 2;

    if (stk->Data) 
        stk->Data = (data_t*) realloc(stk->Data, (stk->cap + 2) * sizeof(data_t));   
    else
        stk->Data = (data_t*) calloc((nameStack->Capacity + 2), sizeof(data_t));    

    if (stk->Data == NULL) {
        printf("%s", "Error! No data in stack ((\n");
        return -2;
    }

    stk->size = stk->cap;                          // Have no idea how to write this string clearly

    return 0;
}

size_t StkMemDec(struct stack* stk) {
    
    if (stk->size < stk->cap / 4)
        stk->cap /= 4;

    stk->Data = (data_t*) realloc(stk->Data, (stk->cap + 2) * sizeof(data_t));  

    if (stk->Data == NULL) {
        printf("%s", "Error! No data in stack ((\n");
        return -2;
    }

    return 0;
}                                  

int main() {
    //struct Stack stk = {}; 
    struct stack *stk;
    int i = 0, n = 0;
    float elem;

    stk = (struct stack*)malloc(sizeof(struct stack));

    printf("Enter the number of elements in stack: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {

        printf("Enter an element %d:", i);
        scanf("%f", &elem);
        push(stk, elem);
    }

    printf("There are %d elements in stack\n\n", getcount(stk));
    stkPrint(stk);

    getchar(); getchar();

    if (stk->cap >= 0 && stk->size >= 0) {
    
        Ctr(&stk);

        push(&stk, 10);

        Dtr(&stk);
    }

    return 0;    
}