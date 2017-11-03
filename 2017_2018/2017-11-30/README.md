# System functions overview

## Using `stdio.h`
Let's start with a simple program
```C
#include <stdio.h>

int main( )
{
    const char *s = "Hello, world!\n";
    printf( "%s", s );
    return 0;
}
```

You can see the system calls by running
```bash
strace ./a.out
```
```
....
write(1, "Hello, world!\n", 14)         = 14
....
+++ exited with 0 +++
```
The system call for outputing to terminal is write. Let's use it directly

## Using write from `unistd.h`
```C
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main( )
{
    const char *s = "Hello, world!\n";
    size_t len = strlen( s );
    size_t written = 0;
    ssize_t wresult;

    while( written != len ) {
        wresult = write( STDOUT_FILENO, s + written, len - written );
        if( wresult < 0 ) {
            perror( "write" );
            return 1;
        }
        written += wresult;
    }

    return 0;

```

We have to run in a loop (see the documentation below)

```
The number of bytes written may be less than  count  if,  for  example,
there  is  insufficient space on the underlying physical medium, or the
RLIMIT_FSIZE resource limit is encountered (see setrlimit(2)),  or  the
call was interrupted by a signal handler after having written less than
count bytes.  (See also pipe(7).)

```

## Using syscall
The write function is only a thin wrapper around syscall. We can rewrite the program by calling syscall directly with the appropriate syscall number

```C

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

int main( )
{
    const char *s = "Hello, world!\n";
    size_t len = strlen( s );
    size_t written = 0;
    ssize_t wresult;

    while( written != len ) {
        wresult = syscall( SYS_write, STDOUT_FILENO, s + written, len - written );
        if( wresult < 0 ) {
            perror( "write" );
            return 1;
        }
        written += wresult;
    }

    return 0;
}
```

## Generating a software interrupt from assembly for X86
We can replace syscall with the assembly equivalent.

First we have to place the parameters in the registers eax, ebx, ecx, edx

After that we can use the `int` instruction to generate a software interrupt
```assembly
mov %[syscall_number], %%eax
mov %[fd], %%ebx
mov %[buf], %%ecx
mov %[to_write], %%edx
int $0x80
mov %%eax, %[wresult]
```
See [asm_x86.c](asm_x86.c) for full example

## Generating a software interrupt from assembly for X64_86
Newer CPUs have a faster way for calling system functions without the full overhead of a software interrupt. This is done via the `syscall` instruction

See [asm_x64_86.c](asm_x64_86.c) for full example

## References
* http://man7.org/linux/man-pages/man2/write.2.html
* http://man7.org/linux/man-pages/man2/syscall.2.html
* https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux