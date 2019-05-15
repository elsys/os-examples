# Разгледани теми

## Обхождане на съдържанието на директория

Използват се системните функции:
- opendir
- readdir
- closedir

Преди използването на readdir, трябва да отворим директорията с opendir (подобно на работата с файлове). Съответно накрая трябва да извикаме closedir.

Извикването на readdir ще ни върне информация за един от файловете в директорията. За да вземем информация за следващия, трябва да я извикаме отново (и така докато върне NULL)

Функцията връща указател към структура:

```c
struct dirent {
    ino_t          d_ino;       /* Inode number */
    off_t          d_off;       /* Not an offset; see below */
    unsigned short d_reclen;    /* Length of this record */
    unsigned char  d_type;      /* Type of file; not supported
                                    by all filesystem types */
    char           d_name[256]; /* Null-terminated filename */
};
```

Имайте предвид, че е възможно следващото извикване на readdir да използва същата памет, т.е. трябва да си копирате информацията, ако ви трябва след следващото извикване на readdir

Пример:

```c
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    while(entry = readdir(dir)) {
        printf("%s\n", entry->d_name);
    }


    closedir(dir);
}
```


## Взимане на информация за даден файл
За да получим повече информация за файл се използва функцията stat

Тя изисква да заделим структура от следния тип и да ѝ я подадем като аргумент:
```c
struct stat {
    dev_t     st_dev;         /* ID of device containing file */
    ino_t     st_ino;         /* Inode number */
    mode_t    st_mode;        /* File type and mode */
    nlink_t   st_nlink;       /* Number of hard links */
    uid_t     st_uid;         /* User ID of owner */
    gid_t     st_gid;         /* Group ID of owner */
    dev_t     st_rdev;        /* Device ID (if special file) */
    off_t     st_size;        /* Total size, in bytes */
    blksize_t st_blksize;     /* Block size for filesystem I/O */
    blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

    /* Since Linux 2.6, the kernel supports nanosecond
        precision for the following timestamp fields.
        For the details before Linux 2.6, see NOTES. */

    struct timespec st_atim;  /* Time of last access */
    struct timespec st_mtim;  /* Time of last modification */
    struct timespec st_ctim;  /* Time of last status change */

#define st_atime st_atim.tv_sec      /* Backward compatibility */
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};
```

Пример:

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>



int main() {
    struct stat st;
    stat("stat.c", &st);
    printf("%ld\n", st.st_size);
}
```

Голяма част от информацията не е в потребителски четим вид и трябва да се обработи допълнително:
- st_mode - Побитова карта, съдържащ правата и типа на файла
- st_uid/st_gid - ID на потребител/група
- st_atim/st_mtim/st_ctim - Различни времена от типа Unix Time, трябва да се използва функции от типа [localtime](https://linux.die.net/man/3/localtime) за да станат четими

## Побитова карта

### Въведение

Нека си представим, че имаме управление на 4 LED диода. 

В C можем да го преставим като:
```C
int status[4];
```
или:
```C
short status[4];
```
съответно ще помни състоянието на всеки в отделен елемент на този масив:
- status[0] - Първи LED
- status[1] - Втори LED
- status[2] - Трети LED
- status[3] - Четвърти LED

Тъй като обаче реално ни е необходим само 1 бит, то няма нужда да заделяме цял short/int

По-оптимално е да си заделим само едно число short (което е поне 16 бита според C стандарта).

Ако разгледаме това число като двоично число, то то изглежда така:
 - 0000000000000000

 Съответно можем да си изберем по един бит за всеки LED. Например:
- Най-десния - Първи LED
- Следващия отдясно наляво - Втори LED
- Следващия (трети) - Трети LED
- Следващия - Четвърти LED

Съответно бихме имали:
 - 0000000000000001 - Свети първия
 - 0000000000000010 - Свети втория
 - 0000000000000100 - Свети третия
 - 0000000000001000 - Свети четвъртия

 Тъй като използват независими битове, можем да ги комбинираме, т.е:
  - 0000000000001111 - Светят всички
  - 0000000000001010 - Светят четири и две

### Взимане на състояние

За да вземем състоянието само на един, трябва да използваме побитов AND:

```
0000000000001111 - Светят всички
&
0000000000001000 - Маска, която да вземе само четвъртия бит
=
0000000000001000 - Всички битове се нулират, освен този, който ни трябва
```
както и:
```
0000000000000111 - Светят всички без 4
&
0000000000001000 - Същата маска
=
0000000000000000
```

Тоест можем да използваме следния код за проверка на състояние:
```c
#define LED4_MASK 0b0000000000001000

...

short status = 0b0000000000001111;


if (status & LED4_MASK) {
    //LED 4 свети
}

```

### Промяна на състояние

За да вдигнем даден флаг трябва да използваме побитов OR:
```c
#define LED4_MASK 0b0000000000001000

...

short status = 0b0000000000000111;


status = status | LED4_MASK;

//status ще е 0b0000000000001111

```

### Допълнителна информация:
[Wikipedia - Bit field](https://en.wikipedia.org/wiki/Bit_field)


## Права и тип

st_mode представлява такава побитова карта с информация за:
- Тип файлове
- За всяко право (може да има множество битове със стойност 1)

### Тип
За типа на файла са заделени 12 бита в st_mode. 

Тъй като един файл може да е само от един тип, то ако имаме например:
```
0000000000000001 - обикновен файл
0000000000000010 - директория
```
то комбинацията
```
0000000000000011 - обикновен файл и директория
```
няма смисъл, поради което тези комбинации се използват за означаване на трети тип файлове.

Тези числа са примерни, истинските може да намерите в документацията:
```c
S_IFSOCK   0140000   socket
S_IFLNK    0120000   symbolic link
S_IFREG    0100000   regular file
S_IFBLK    0060000   block device
S_IFDIR    0040000   directory
S_IFCHR    0020000   character device
S_IFIFO    0010000   FIFO
```

За да си вземете всичките 12 бита за тип на файл, трябва да направите побитово И с S_IFMT:
```c
sb.st_mode & S_IFMT
```
След това следва резултата да го сравните с горните стойности.


Алтернативно може да използвате готови макроси:
```c
S_ISREG(m)  is it a regular file?
S_ISDIR(m)  directory?
S_ISCHR(m)  character device?
S_ISBLK(m)  block device?
S_ISFIFO(m) FIFO (named pipe)?
S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)
```
 


### Права
Правата имат следните маски (същото като LED4_MASK по-горе)
 
```c
S_IRWXU     00700   owner has read, write, and execute permission
S_IRUSR     00400   owner has read permission
S_IWUSR     00200   owner has write permission
S_IXUSR     00100   owner has execute permission

S_IRWXG     00070   group has read, write, and execute permission
S_IRGRP     00040   group has read permission
S_IWGRP     00020   group has write permission
S_IXGRP     00010   group has execute permission

S_IRWXO     00007   others (not in group) have read, write, and execute permission
S_IROTH     00004   others have read permission
S_IWOTH     00002   others have write permission
S_IXOTH     00001   others have execute permission

```


Повече информация може да намерите в 
```sh
man inode
```


## Взимане на информация за името на потребител/група

Става чрез фукнциите getpwuid/getgrgid

Пример за потребителско име (за група е еквивалентно, но е с функцията getgrgid)

```c
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
```

## getopt

За по-лесна обработка на аргументи от типа на (всичките са еквивалентни):
```sh
ls -la
ls -l -a
ls -a -l
ls -al
```
може да използвате функцията
```sh
man 3 getopt
```

```c
#include <unistd.h>

int getopt(int argc, char * const argv[],
            const char *optstring);
```

Тя приема аргументите на main - argc и argv, както и низ включващ опцците, които искате да обработите.

В документацията има примерен код