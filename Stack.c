#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define NMAX 100                       //max number of elements

struct stack {                          //stack declaration
    float elem[NMAX];                   //array for keeping elements
    int top;                            //index of element on the top of stack

    size_t size;
    size_t cap;
    int* Data;
};

size_t Ctr(struct stack* stk, size_t cap) {

    if (cap < 0) {
        stk->error = -1;              // TODO: error
    }

    if (cap == 0) {
        stk->Data = NULL;
        stk->size = 0;
        stk->cap = 0;
    }                                 // Do we need actions for (cap > 0)?

    return 0;
}

void Dtr(struct stack* stk) {
    stk->Data = NULL;
    stk->size = -123;
    stk->cap = -321;
}



void init(struct stack *stk) {       //stack initialisation
  stk->top = 0;                      //index of the first element is equal to 0 
}

void push(struct stack *stk, float f) {      //adding an element to stack
  
    if (stk -> top < NMAX) {
        stk -> elem[stk->top] = f;                 //shift left
        stk -> top++;

    } else
        printf("Stack is full, number of elements: %d !\n", stk->top);
}

float pop(struct stack *stk) {         //delete an element from stack
  
  float elem;

  if ((stk -> top) > 0) {
    return stk -> elem[(stk->top)--]; //return last element
  }

  else  {
    printf("???? ????!\n");
    return 0;
  }
}

float stkTop(struct stack *stk) {     //receiving the top element without deleting
  
    if ((stk -> top) > 0) {
    return stk -> elem[stk -> top-1];

  } else {
    printf("???? ????!\n");
    return 0;
  }
}

int isempty(struct stack *stk) {      //is stack empty?
  
  if (stk -> top == 0)    return 1;
  else return 0;
}

int getcount(struct stack *stk) {     //receiving the number of elements in stack
  return stk -> top;
}

void stkPrint(struct stack *stk) {    //printing elements of stack
  
  int i;
  i = stk -> top; // i - number of elements in stack

  if (isempty(stk) == 1) return;
  do {
    i--;
    printf("%f\n", stk -> elem[i]);
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

    stk->size = stk->cap;                          // Have no idea how to write this string clear

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
    init(stk);

    printf("Enter the number of elements in stack: ");
    scanf("%d", &n);

    for (i  =0; i < n; i++) {

        printf("Enter an element %d:", i);
        scanf("%f", &elem);
        push(stk, elem);
    }

    printf("There are %d elements in stack\n\n", getcount(stk));
    stkPrint(stk);
    printf("Top element is %f\n", stkTop(stk));

    getchar(); getchar();

    if (stk->cap >= 0 && stk->size >= 0) {
    
        Ctr(&stk);

        push(&stk, 10);

        Dtr(&stk);
    }

    return 0;    
}