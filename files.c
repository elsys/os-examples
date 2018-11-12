#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>



int main() {
    char buff[10];

    int fd = open("files.c", O_RDONLY);
    if (fd == -1) {
        printf("error\n");
    }
    int result;
    
    while ((result = read(fd, buff, 10)) > 0) {
        int written = 0;
        while (written < result) {
            int w_result = write(STDIN_FILENO, buff + written, 
                                 result - written);
            if (w_result == -1) {
                printf("error\n");
                return -1;
            }
            written += w_result;
        }
        
    }
    if (result == -1) {
        printf("error\n");
    }
    

    if (close(fd) == -1) {
        printf("error\n");
    }
}
