#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <cmath>
#include <string.h> // for memset

typedef int data_t;

#define assert_stk(stk) {\
    if ( !(stk_is_ok(stk)) ) {\
        printf("| !!!Assertion failed!!!\n");\
        printf("|       what: stk_is_ok(%s),\n", #stk);\
        printf("|   !!!DUMP!!!\n");\
        abort();\
    }\
}

const size_t canary_value1 = 13579;
const data_t canary_value2 = 24680;
const char poison = 255;

struct stack {                          //stack declaration
    size_t canary_left = canary_value1;
    
    data_t* ptr_stk = nullptr;

    size_t size = poison;
    size_t cap = poison;
    data_t* data = nullptr;
    
    size_t canary_right = canary_value1;
};

enum STACK_ERRORS {                    //errors declaration
    STACK_OK = 000000,
    STACK_ERROR_CTOR = 100010,
    STACK_ERROR_INIT = 0b100001,
    STACK_ERROR_PUSH = 100011,
    STACK_ERROR_PUSH_REALLOC = 100100,
    STACK_ERROR_POP = 100101,
    STACK_ERROR_POP_REALLOC = 100110,
};

size_t stk_ctr(stack* stk, size_t cap, size_t size);

void stk_dtr(struct stack* stk);

size_t stk_push(stack *stk, data_t variable);

data_t stk_pop(stack *stk);

void print_stk (const void *elem, stack *stk, FILE *f_out);

size_t stk_mem(stack* stk);

size_t stk_mem_inc(struct stack* stk);

size_t stk_mem_dec(struct stack* stk);

bool stk_is_ok(stack *stk);

void fill_with_poison(struct stack *stk, size_t start, size_t end);

void stk_dump(stack* stk, FILE *f_out, void (*print) (const void *elem, stack *stk, FILE *f_out));