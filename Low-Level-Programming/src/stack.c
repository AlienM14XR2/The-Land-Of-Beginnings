#include "stdio.h"
#include "malloc.h"
#include "stack.h"

struct list {
    int value;
    struct list* next;
};

static struct list* list_new(int item, struct list* next) {
    struct list* new_list = malloc(sizeof(*new_list));
    new_list->value = item;
    new_list->next = next;
    return new_list;
}

void stack_push(struct stack* s, int value) {
    s->first = list_new(value, s->first);
    if(s->last == NULL) {
        s->last = s->first;
    }
    s->count++;
}

int stack_pop(struct stack* s) {
    struct list* const head = s->first;
    int value;
    if(head) {
        if(head->next) {
            s->first = head->next;
        }
        value = head->value;
        free(head);
        if(-- s->count) {
            s->first = s->last = NULL;
        }
        return value;
    }
    return 0;
}

void stack_foreach(struct stack* s, void (f)(int)) {
    struct list* cur;
    for(cur = s->first; cur; cur=cur->next) {
        f(cur->value);
    }
}

bool stack_is_empty(const struct stack* s) {
    return s->count == 0;
}

struct stack stack_init(void) {
    struct stack empty = {NULL,NULL,0};
    return empty;
}

void stack_deinit(struct stack* s) {
    while(! stack_is_empty(s)) {
        stack_pop(s);
    }
    s->first = NULL;
    s->last = NULL;
}
