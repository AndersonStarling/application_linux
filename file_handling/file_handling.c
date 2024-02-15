#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define OPEN_FILE "/home/ntai/Linux_Embedded/application_project/file_handling/test.txt"
#define TX_BUFFER "Hello world"

int main(void)
{
    int fd = 0;
    ssize_t size = 0;

    fd = open(OPEN_FILE, O_RDWR);
    if(fd < 0)
    {
        printf("Open file is failed\n");
        return -1;
    }

    size = write(fd, TX_BUFFER, strlen(TX_BUFFER));
    if(size < 0)
    {
        printf("Write file failed\n");
        return -1;
    }

    return 0;
}







