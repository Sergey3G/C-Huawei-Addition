#ifndef LISTERRORS_H
#define LISTERRORS_H

typedef enum ListErrors
{
    NO_ERRORS = 0,
    DATA_NULL_PTR = 1,
    NEXT_NULL_PTR = 2,
    PREV_NULL_PTR = 4,
    CAP_LT_ZERO = 8,
    DATA_CANARY_DEAD = 16,
    NEXT_CANARY_DEAD = 32,
    PREV_CANARY_DEAD = 64
} ListErrors;

#endif
