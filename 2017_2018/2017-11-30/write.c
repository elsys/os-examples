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
}
