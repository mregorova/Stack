#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

enum STACK_ERRORS {                    //errors declaration

    STACK_ERROR_PUSH = 123,
    STACK_ERROR_POP = 456,
    STACK_ERROR_CTOR = -1,
};

struct stack {                          //stack declaration
    ptrStk = nullptr;

    size_t size;
    size_t cap;
    data_t* Data;

    int error;

    unsigned long long canaryLeft = CANARY_LEFT;
    unsigned long long canaryRight = CANARY_RIGHT;
};

size_t Ctr(struct stack* stk, size_t cap) {

    stk->ptrStk = calloc(stk->cap, sizeof(stk->cap) + 2 * sizeof(int)); // +2 for canary

    *(((int*)stk->ptrStk) + 0) = CANARY_LEFT;

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

    *(((int*)stk->ptrStk) + stk->cap) = CANARY_RIGHT;

    return 0;
}

void Dtr(struct stack* stk) {
    free (stk->Data);                           //cleaning Data (what is the difference between free and StackMem?)

    stk->Data = NULL;
    stk->size = -123;
    stk->cap = -321;
}

size_t push(struct stack *stk, float f) {      //adding an element to stack
  
    if (stk->cap == stk->size) {
        StkMemInc(stk);
    }

    stk->Data[stk->size++] = f;
}

data_t pop(struct stack *stk) {                //delete an element from stack
  
    if (stk->size == 0) {
        printf("Atata! Nothing here\n");
    }

    else
    {
        return stk->Data[stk->size--];
    }

    if (stk->cap >= (stk->size * 4)) {
        StkMemDec(stk);
    }
}

void dump(const stack *stk) {
    if error mmmmm
}

void stkPrint(struct stack *stk) {    //printing elements of stack
  
  int i;
  i = stk->size; // i - number of elements in stack

  if (if (stk->size == 0) return;
  do {
    i--;
    printf("%f\n", stk->elem[i]);
  } while(i > 0);
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

int StkIsOk(struct Stack *stk) {

    if (stk->error != 0) {
        return stk->error;
    }

    else {
    
        if (stk->canaryLeft != CANARY_LEFT) {
            return leftCanary;
        }

        if (stk->canaryRight != CANARY_RIGHT) {
            return rightCanary;
        }

        if (*((int*)stk->ptrStk - 1) != CANARY_LEFT) {
            printf("%d\n", *((int*)stk->ptrStk - 1));
            return arrayLeftCanary;
        }

        if (*((int*)stk->ptrStk + stk->cap) != CANARY_RIGHT) {
            return arrayRightCanary;
        }

    }

}

void Stack_dump(FILE* file, struct Stack* stk) {

    if (stk->size == 0) return 1;

    const char* code = Stk_ERROR(stk);

    fprintf(file, "Stack (ERROR #%d: %s [%p] \"%s\" \n", stk->error, code, stk, stk->name);
    fprintf(file, "{\n");
    fprintf(file, "\tleft struct canary = %lx\n",  stk->canaryLeft);
    fprintf(file, "\tsize = %lu\n",                stk->size);
    fprintf(file, "\tcapacity = %lu\n",            stk->capacity);
    fprintf(file, "\tstruct hash = %lu\n",         stk->struct_hash);
    fprintf(file, "\tstack hash = %lu\n",          stk->stack_hash);
    fprintf(file, "\tright struct canary = %lx\n", stk->canaryRight);
    fprintf(file, "\tdata[%p]\n",                  stk->data);
    fprintf(file, "\t{\n");

    if ((stk->Data != nullptr) && (stk->error != NEGATIVE_CAPACITY))      //change the code for return stk->error = ...
    {
        Print_array(file, stk);                                           //create Print_array function
    }
    
    fprintf(file, "\t}\n"
                  "}\n\n\n");

    fflush(file);
}

void FillWthPoison(struct stack *stk, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
    {
        stk->data[i] = Poison;
    }
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

    printf("There are %d elements in stack\n\n", stk->size);
    stkPrint(stk);

    getchar(); getchar();

    if (stk->cap >= 0 && stk->size >= 0) {
    
        Ctr(&stk);

        push(&stk, 10);

        Dtr(&stk);
    }

    return 0;    
}


