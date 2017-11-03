#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/syscall.h>

int main( )
{
    const char *s = "Hello, world!\n";
    size_t len = strlen( s );
    size_t written = 0;
    ssize_t wresult;

    const void *buf;
    int64_t to_write;

    while( written != len ) {
        buf = s + written;
        to_write = len - written;

        __asm__ volatile( "mov %[syscall_number], %%rax\n\t"
                          "mov %[fd], %%rdi\n\t"
                          "mov %[buf], %%rsi\n\t"
                          "mov %[to_write], %%rdx\n\t"
                          "syscall\n\t"
                          "mov %%rax, %[wresult]\n\t"
                          : [wresult] "=m" (wresult)
                          : [syscall_number] "i" (SYS_write),
                            [fd] "i" (STDOUT_FILENO),
                            [buf] "m" (buf),
                            [to_write] "m" (to_write)
                          : );

        if( wresult < 0 ) {
            perror( "write" );
            return 1;
        }
        written += wresult;
    }

    return 0;
}
