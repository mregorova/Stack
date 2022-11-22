#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"

int main() {
    stack stk_int = {};
    STACK_ERRORS err = STACK_OK;

    stk_ctr(&stk_int, 10, sizeof (int));
    stk_dump(&stk_int, nullptr, print_stk);

    for (data_t i = 7; i < 1240; i++){
        stk_push (&stk_int, i);

        if (!stk_is_ok (&stk_int)) {
            printf("ERR: %d %d\n", i);
            break;
        }
    }

    printf("%d %d\n\n", stk_int.cap, stk_int.size);

    err = STACK_OK;
    size_t old = stk_int.cap;

    stk_dump(&stk_int, nullptr, print_stk);

    while (err == STACK_OK) {
        int *x = (int*) stk_pop(&stk_int);

        if (!err && old != stk_int.cap) {
            printf("%d : %d -> %d\n", *x, old, stk_int.cap);
            old = stk_int.cap;
        }
    }

    stk_dump(&stk_int, nullptr, print_stk);
  
    printf("%d %d\n\n", stk_int.cap, stk_int.size);

    stk_dtr(&stk_int);

    stk_dump(&stk_int, nullptr, print_stk);
 
    printf("%d %d\n\n", stk_int.cap, stk_int.size);

    printf("DONE\n");

    return 0;    
}