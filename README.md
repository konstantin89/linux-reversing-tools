# linux-reversing-tools

## Resources
[Reverse engineering tools](https://www.thegeekstuff.com/2012/03/reverse-engineering-tools/)

## Tools

### strings
Print the strings in the binary.
``` bash
 strings whereis

/lib/ld-linux-armhf.so.3
D519F
 #*i!Q
"Bw)
gII"fY/
setuid
fflush
__printf_chk
setlocale
strncmp
strrchr
pipe
dcgettext
closedir
nanosleep
strncpy
fork
warnx
__stack_chk_fail
abort
_exit
getpid
strdup
__assert_fail
fgets
calloc
...
```

### fuser 
Find what user uses a resourse (file, socket, etc.)  

Check what processes are using the `/dev/null`
``` bash
fuser -v /dev/null
                     USER        PID ACCESS COMMAND
/dev/null:           pi          619 f.... systemd
                     pi          635 f.... pipewire
                     pi          636 f.... pulseaudio
                     pi          641 F.... dbus-daemon
                     pi          642 f.... lxsession
                     pi          651 f.... pipewire-media-
                     pi          755 f.... gvfsd
                     pi          771 f.... gvfsd-fuse
                     pi          779 f.... mutter
                     pi          781 f.... lxpolkit
                     pi          784 f.... lxpanel
                     pi          786 f.... pcmanfm
                     pi          805 f.... applet.py
                     pi          921 F.... menu-cached
                     pi          925 f.... gvfs-udisks2-vo
                     pi          930 f.... gvfs-gphoto2-vo
                     pi          934 f.... gvfs-goa-volume
                     pi          940 f.... gvfs-mtp-volume
                     pi          944 f.... gvfs-afc-volume
                     pi          994 f.... gvfsd-trash
                     pi        12087 f.... sh
                     pi        12097 f.... node
                     pi        12365 f.... node
                     pi        12605 f.... node
                     pi        12628 f.... node
                     pi        14679 f.... node
```

Show what process is using TCP port 80:
``` bash
fuser -v -n tcp 80
```


### ldd
Shows what shared libraries the executable uses.  

``` bash
ldd /usr/bin/wget
        /usr/lib/arm-linux-gnueabihf/libarmmem-${PLATFORM}.so => /usr/lib/arm-linux-gnueabihf/libarmmem-v8l.so (0xf7df5000)
        libpcre2-8.so.0 => /lib/arm-linux-gnueabihf/libpcre2-8.so.0 (0xf7d48000)
        libuuid.so.1 => /lib/arm-linux-gnueabihf/libuuid.so.1 (0xf7d31000)
        libidn2.so.0 => /lib/arm-linux-gnueabihf/libidn2.so.0 (0xf7d02000)
        libnettle.so.8 => /lib/arm-linux-gnueabihf/libnettle.so.8 (0xf7cad000)
        libgnutls.so.30 => /lib/arm-linux-gnueabihf/libgnutls.so.30 (0xf7ac3000)
        libz.so.1 => /lib/arm-linux-gnueabihf/libz.so.1 (0xf7a9b000)
        libpsl.so.5 => /lib/arm-linux-gnueabihf/libpsl.so.5 (0xf7a7a000)
        libc.so.6 => /lib/arm-linux-gnueabihf/libc.so.6 (0xf7927000)
        /lib/ld-linux-armhf.so.3 (0xf7e0a000)
        libpthread.so.0 => /lib/arm-linux-gnueabihf/libpthread.so.0 (0xf78fb000)
        libunistring.so.2 => /lib/arm-linux-gnueabihf/libunistring.so.2 (0xf777e000)
        libp11-kit.so.0 => /lib/arm-linux-gnueabihf/libp11-kit.so.0 (0xf7671000)
        libtasn1.so.6 => /lib/arm-linux-gnueabihf/libtasn1.so.6 (0xf7650000)
        libhogweed.so.6 => /lib/arm-linux-gnueabihf/libhogweed.so.6 (0xf7602000)
        libgmp.so.10 => /lib/arm-linux-gnueabihf/libgmp.so.10 (0xf758b000)
        libffi.so.7 => /lib/arm-linux-gnueabihf/libffi.so.7 (0xf7573000)
        libdl.so.2 => /lib/arm-linux-gnueabihf/libdl.so.2 (0xf755f000)
        libgcc_s.so.1 => /lib/arm-linux-gnueabihf/libgcc_s.so.1 (0xf7532000)
```

### ltrace
Trace library calls (funtions from libraries).
``` bash
# Instal command
sudo apt-get install ltrace
```

```
Here's a simplified overview of how ltrace works:

    Library Interception:
    When you run a program using ltrace, ltrace inserts itself between the program and the shared libraries it uses.   
    It does this by using the LD_PRELOAD environment variable to load its own shared library before the standard libraries.  

    Dynamic Linking:
    During the dynamic linking phase of the program's execution, the LD_PRELOAD library (in this case, the ltrace library) is   
    loaded into the process's address space.

    Function Hooking:
    ltrace uses function hooking to intercept calls to functions within shared libraries. 
    It replaces the original function calls with its own code, allowing it to log information about the function calls.

    Tracing Execution:
    As the program runs, ltrace captures information about each library call, including the function name, 
    arguments, and return values.

    Output:
    The collected information is then printed to the standard output or redirected to a file, 
    allowing users to analyze the sequence of library calls made by the traced program.
```

### strace
[strace tutorial](https://psychocod3r.wordpress.com/2021/06/25/reverse-engineering-a-linux-process-with-strace/)

``` bash
strace -o strace.txt -f sh -c 'ls /tmp | grep me'
strace curl
```

``` 
Here's a simplified overview of how strace works:

    Instrumentation:
    When you run a program with strace, strace starts the target process and attaches to it. 
    It does this by using the ptrace system call, which allows a process to observe and control the 
    execution of another process.

    Tracing System Calls:
    strace intercepts system calls made by the target process. System calls are the interface 
    between user-level programs and the kernel, responsible for requesting services from the operating system.

    Logging Information:
    For each intercepted system call, strace logs information such as the system call name, 
    arguments, and return values. It also records additional details, including the process ID and timestamps.

    Displaying Output:
    The collected information is then displayed on the terminal or redirected to a file. The output provides a detailed 
    trace of the system calls made by the traced process, offering insights into its behavior and interactions with the 
    operating system.

    Optional Filtering:
    strace allows users to filter the traced system calls based on criteria such as system call name, process ID, or signal. 
    This can help focus the output on specific aspects of the program's behavior.
```
