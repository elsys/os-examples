#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 5
#define ERROR_BUFFER_SIZE 4096

int main(int argc, char* argv[]){
    int fd;
    char buffer[BUFFER_SIZE];
    
    if (argc < 3) {
        char usage[ERROR_BUFFER_SIZE];
        
        // there is an easier way of writing a string in a buffer,
        // see the available functions in string.h
        strcpy(usage, "Usage: ");
        strcat(usage, argv[0]);
        strcat(usage, " FILE POSITION\n");        

        write(STDERR_FILENO, usage, strlen(usage));
        return 1;
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror(argv[1]);
        return 1;
    }

    off_t seek = lseek(fd, atoi(argv[2]), SEEK_SET);
    if (seek < 0) {
        perror(argv[2]);
        return 2;
    }

    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read < BUFFER_SIZE)
    {
        ssize_t current_bytes_read = read(fd, buffer + bytes_read, BUFFER_SIZE - bytes_read);
        if (current_bytes_read == -1) {
            perror("read()");
            return 1;
        }
        
        bytes_read = bytes_read + current_bytes_read;
    }
    
    ssize_t bytes_written = write(STDOUT_FILENO, buffer, BUFFER_SIZE);
    while (bytes_written < BUFFER_SIZE)
    {
        ssize_t current_bytes_written = write(fd, buffer + bytes_written, BUFFER_SIZE - bytes_written);
        if (current_bytes_written == -1) {
            perror("write()");
            return 1;
        }
        
        bytes_written = bytes_written + current_bytes_written;
    }
    
    //write an additional newline character
    write(STDOUT_FILENO, "\n", 1); // TODO: add error handling before using this line!
    
    
    int error = close(fd);
    if (error == -1) {
        perror("close()");
        return 1;
    }
    
    return 0;
}
