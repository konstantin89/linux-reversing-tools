#define _GNU_SOURCE
#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>

typedef int (*open_type)(const char *pathname, int flags, ...);

int open(const char *pathname, int flags, ...) 
{
    // Get the original open function from libc using dlsym
    // Please note the RTLD_NEXT. It will find the next symbol named open
    open_type original_open = dlsym(RTLD_NEXT, "open");

    // Print a message indicating that open is being called
    printf("Hook: Intercepted open call: %s\n", pathname);

    // Call the original open function
    va_list args;
    va_start(args, flags);
    int result = original_open(pathname, flags, va_arg(args, mode_t));
    va_end(args);

    return result;
}