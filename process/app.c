#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/process_file_device"

int main(void)
{
    char RX_Buffer[20];
    int fd = 0;
    int size = 0;

    fd = open(DEVICE_FILE, O_RDWR);
    if(fd < 0)
    {
        printf("Open file is failed\n");
        return -1;
    }

    size = read(fd, &RX_Buffer[0], 1);
    if(size < 0)
    {
        printf("Read file failed\n");
        return -1;
    }

    return 0;
}

