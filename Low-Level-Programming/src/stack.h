#ifndef _STACK_H_
#define _STACK_H_

#include "stddef.h"
#include "stdint.h"
#include "stdbool.h"

struct list;

struct stack {
    struct list* first;
    struct list* last;
    size_t count;
};

struct stack stack_init(void);
void stack_deinit(struct stack* s);

void stack_push(struct stack* s, int value);
int stack_pop(struct stack* s);
bool stack_is_empty(const struct stack* s );

void stack_foreach(struct stack* s, void (f)(int));

#endif  /* _STACK_H_ */
