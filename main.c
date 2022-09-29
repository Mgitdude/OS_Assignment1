#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define BUFSIZE 512
#define READ_END	0
#define WRITE_END	1
#define PERM    0777

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        perror ("Usage: (name of the exe) (name of file to read letter from) (the letter to be read)");
        exit(1);
    }
}
