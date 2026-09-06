#pragma once

#include <stdlib.h>

#define iterator_define(iter_type,element_type) \
struct iter_type { \
    element_type (*next) (void*); \
    int (*more) (void*); \
    void* state; \
};

#define iterator_define_array(iter_type,element_type,array_type,iter_constructor_fn_name) \
struct iter_type ## Array { \
    array_type *arr; \
    int idx; \
}; \
\
static inline element_type iter_type ## _array_next(void *_state_ptr) { \
    struct iter_type ## Array *state = (struct iter_type ## Array *)_state_ptr; \
    return state->arr->items[state->idx++]; \
} \
\
static inline int iter_type ## _array_more(void *_state_ptr) { \
    struct iter_type ## Array *state = (struct iter_type ## Array *)_state_ptr; \
    return state->idx < state->arr->length; \
} \
\
static inline struct iter_type iter_constructor_fn_name(void *state) { \
    return (struct iter_type){ \
        .next = iter_type ## _array_next, \
        .more = iter_type ## _array_more, \
        .state = state \
    }; \
}
