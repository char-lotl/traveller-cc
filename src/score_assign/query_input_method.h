#ifndef QUERY_INPUT_METHOD_H
#define QUERY_INPUT_METHOD_H

enum input_type {
    ROLL_SCORES,
    MANUAL_ENTRY,
    POINT_BUY
};

input_type query_input_method();

#endif
