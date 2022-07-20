#include <stdio.h>
#include <linux/stat.h>
#include <linux/types.h>
#include <fcntl.h>

int main()
{
    int fd=0;
    fd=open("/home/vico/Desktop/test",O_RDRW,0777);
    if (fd < 0) {
        perror("\nopen error.\n");
    }
    else {
        printf("\nopen sucess.\n");
    }
    return 0;
}
