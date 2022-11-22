#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"

void stk_dtr(struct stack* stk) { //TODO rename stk -> stack everywhere
    assert_stk(stk);

    if (stk->data != nullptr) {
        memset(stk->data, poison, stk->cap + 2);
        free (stk->data);                           //cleaning Data 

        stk->data = nullptr;
    }
    
    stk->canary_left = poison;

    stk->size = poison;
    stk->cap = poison;

    stk->canary_right = poison;
}

size_t stk_push(stack *stk, data_t variable) {      //adding an element to stack
    assert_stk(stk);

    if (stk->cap == stk->size) {
        size_t check = stk_mem_inc(stk);

        if (check == STACK_ERROR_PUSH_REALLOC) return STACK_ERROR_PUSH;
    }

    stk->data[stk->size++] = variable;
    
    assert_stk(stk);
    return 0;
}

data_t stk_pop(stack *stk) {                //deleting an element from stack
    assert_stk(stk);

    if (stk->size == 0) {
        printf("Atata! Nothing here\n");
    }

    data_t pop_elem = stk->data[stk->size--];

    if (stk->cap == (stk->size * 4)) {
        size_t check = stk_mem_dec(stk);

        if (check == STACK_ERROR_POP_REALLOC) return STACK_ERROR_POP;
    }

    assert_stk(stk);
    return pop_elem;
}

void print_stk (const void *elem, stack *stk, FILE *f_out) {  //printing elements of stack
    assert_stk(stk);

    fprintf (f_out, "%d ", *(int*) elem);
}

size_t stk_mem(stack* stk) {
    assert_stk(stk);

    stk->cap = 2;
    stk->data = (data_t*) calloc((stk->cap + 2), sizeof(data_t));
    
    if (stk->data == nullptr) {
        printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

        return STACK_ERROR_INIT;
    }

    stk->data[0] = canary_value2;
    stk->data[stk->cap + 1] = canary_value2;

    assert_stk(stk);
    return 0;
}

size_t stk_mem_inc(struct stack* stk) {
    assert_stk(stk);

    if (stk->cap == 0) stk->cap = 2;
    else               stk->cap *= 2;

    if (stk->data) 
        stk->data = (data_t*) realloc(stk->data, (stk->cap + 2) * sizeof(data_t));   
    else
        stk->data = (data_t*) calloc((stk->cap + 2), sizeof(data_t));    

    if (stk->data == nullptr) {
        printf("%s", "Error! No data in stack ((\n");
        return STACK_ERROR_PUSH_REALLOC;
    }

    stk->data[0] = canary_value2;
    stk->data[stk->cap + 1] = canary_value2;

    assert_stk(stk);
    return 0;
}

size_t stk_mem_dec(struct stack* stk) {
    assert_stk(stk);

    stk->cap /= 2;
    stk->data = (data_t*) realloc(stk->data, (stk->cap + 2) * sizeof(data_t));    
    
    if (stk->data == nullptr) {
        printf("%s", "Error! No data in stack ((\n");

        return STACK_ERROR_POP_REALLOC;
    }

    stk->data[0] = canary_value2;
    stk->data[stk->cap + 1] = canary_value2;

    assert_stk(stk);
    return 0;
}                                  

bool stk_is_ok(stack *stk) {

    if (stk == nullptr)                             
        return false;

    if ((stk->canary_left != canary_value1) || 
        (stk->canary_right != canary_value1))       
        
        return false;

    if ((stk->cap < 0) || (stk->cap == poison))     
        return false;

    if ((stk->size < 0) || (stk->cap == poison))    
        return false;

    if (stk->cap < stk->size)                       
        return false;
}

void fill_with_poison(struct stack *stk, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i)
    {
        stk->data[i] = poison;
    }
}

void stk_dump(stack* stk, FILE *f_out, void (*print) (const void *elem, stack *stk, FILE *f_out)) {
    FILE *dump = fopen("f_out.txt", "a");

    fprintf(dump, "#----------------------------------------------------------\n");
    fprintf(dump, "# Stack stk");
    fprintf(dump, " [%p] ", stk);
    if (stk == nullptr) {
        fprintf(dump, "(!!!ERROR!!!) {\n");
        return;
    }
    else fprintf(dump, "{\n");

    fprintf(dump, "#    capacity = %ld", stk->cap);
    if (stk->cap == poison) fprintf(dump, " (poison?)\n");
    else fprintf(dump, "\n");

    fprintf(dump, "#    size = %ld", stk->size);
    if (stk->size == poison) fprintf(dump, " (poison?)");

    if (stk->cap < stk->size) fprintf(dump, " (!!!!!)\n");
    else fprintf(dump, "\n");

    if (stk->data != nullptr) {
        fprintf(dump, "#    data[%ld] [%p]: {\n", stk->size, stk->data);
        for (size_t i = 0; i < stk->cap + 2; i++) {
            fprintf(dump, "#      [%li] = %d", i, stk->data[i]);

            if (stk->data[i] == canary_value2) fprintf(dump, " (canary)\n");
            else if (stk->data[i] == poison) fprintf(dump, " (poison?)\n");
            else fprintf(dump, "\n");
        }

        fprintf(dump, "#    }\n# }\n");
        fprintf(dump, "#----------------------------------------------------------\n");
        fclose(dump);
    }

    else {
        fprintf(dump, "#    data = nullptr (!!!!!) {\n");
        fprintf(dump, "# }\n");
        fprintf(dump, "#----------------------------------------------------------\n");
        fclose(dump);
    }
}

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