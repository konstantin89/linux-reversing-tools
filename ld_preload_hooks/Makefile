
# The -ldl flag in the gcc command you provided is used to link against the libdl library. 
# This library, often referred to as the "Dynamic Loading" library, provides functions for dynamically 
# loading shared libraries during program execution.

# -ldl: Specifies that the libdl library should be linked. 
# This library contains functions such as dlopen and dlsym, 
# which are used for dynamic loading and symbol resolution. 
# In the context of your example, dlsym is used to obtain the 
# address of the open function from the C runtime.

all: hook_lib app

app: app.c
	gcc app.c -o app

# Note the -ldl flag!
hook_lib: hook.c
	gcc -shared -fPIC -o hook.so hook.c -ldl