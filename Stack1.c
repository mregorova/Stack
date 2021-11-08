#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define NMAX 100                       //max number of elements

struct stack {                        //stack declaration
  float elem[NMAX];                   //array for keeping elements
  int top;                            //index of element on the top of stack
};

void init(struct stack *stk) {       //stack initialisation
  stk->top = 0;                      //index of the first element is equal to 0 
}

void push(struct stack *stk, float f) {      //adding an element to stack
  
    if (stk -> top < NMAX) {
        stk -> elem[stk->top] = f;                 //shift left
        stk -> top++;

    } else
        printf("Stack is fuul, number of elements: %d !\n", stk->top);
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

  if (isempty(stk) == 1) return; // ???? ????
  do {
    i--;
    printf("%f\n", stk -> elem[i]);
  } while(i > 0);
}

int main() {
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

    do {
        printf("Extracting an element %f, ", pop(stk));
        printf("There are %d elements left in stack\n", getcount(stk));
    } while (isempty(stk) == 0);

    getchar(); getchar();

    return 0;    

    //stack Ctor(&stk);
    //StackPush(&stk, 10);

    //StackDtor(&stk);
}