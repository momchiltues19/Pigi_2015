//Name: Momchil Todorov
//Number: 19
//Class: XIA
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "read.h"
/*
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

void *read_image(char *path) {
        int fd = open(path, O_RDONLY);
        if (fd < 0) {
            return NULL;
        }
        size_t size = 1000;
        size_t offset = 0;
        size_t res;
        char *buff = malloc(size);

        while((res = read(fd, buff + offset, 100)) != 0) {
                offset += res;
                if (offset + 100 > size) {
                        size *= 2;
                        buff = realloc(buff, size);
                }
        }
        close(fd);
        return buff;
}
*/

int compare(uint8_t *, uint8_t *, uint8_t);

int main(int argc,char* argv[]){
    uint32_t i, ii;
    uint8_t* f;
    if(read_image(argv[1])==NULL)
    {
        printf("Unable to open file\n");
        return 0;
    }
    else f = read_image(argv[1]);
    uint32_t width = 0, height = 0, file_size = 0;
    uint8_t help[4]={'I','H','D','R'};
    uint8_t eof[4]={'I','E','N','D'};
    uint8_t check_png[8]={0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};//decimal version of 89 50 4E 47 0D 0A 1A 0A
    if(!compare(f,check_png,8))
    {
        printf("Unable to parse file\n");
        return 0;
    }
    for(i=0;;i++){
        uint8_t *current= f+i;
        if(compare(current,help,4))
        {
            width =*(uint32_t*)(current+4);
            width = ntohl(width);
            printf("PNG image width: %d\n",width);
            height =*(uint32_t*)(current+8);
            height = ntohl(height);
            printf("PNG image height: %d\n",height);
        }
    }
    for(ii=i;;ii++)
    {
        uint8_t current= f+ii;
        if(compare(current,eof,4))
        {
            file_size = ii+4;//end of the file has 4 bytes for CRC
            printf("PNG file size: %d\n", file_size);
            break;
        }
    }
    return 0;
}

int compare(uint8_t *first, uint8_t *second, uint8_t size)
{
    uint8_t i;
    for(i=0;i<size;i++)
    {
        if(first[i]!=second[i])return 0;
    }
    return 1;
}
