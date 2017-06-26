#ifndef UTIL_H
#define UTIL_H

#include <unistd.h>

/** 
 * procress structure
 * Basic model for input comprehension.
 */
struct process {
    int IN = STDIN_FILENO;
    int OUT = STDOUT_FILENO;
    int argc;
    char ** argv;
};
#endif