#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>



int main() {
    struct stat st;
    stat("stat.c", &st);
    printf("%ld\n", st.st_size);

    struct passwd *pwd;
    pwd = getpwuid(st.st_uid);
    printf("%s\n", pwd->pw_name);
}

