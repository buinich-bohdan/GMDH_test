#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>

void print_arr(int *arr, size_t n)
{

    for (int i = 0; i < 1000000; i++)
        std:: cout << arr[i] << std::endl;
}

int compare(const void * x1, const void * x2)
{
    return ( *(int*)x1 - *(int*)x2 );
}

int main(int argc, char * argv[]){

    struct stat buffer;

    int status;
    int fd;

    fd = open("/home/bohdan/CLionProjects/GMDH/task3.1/logfile.txt", O_RDONLY);
    status = fstat(fd, &buffer);
    size_t n = buffer.st_size/sizeof(int);
    std::cout << "number of data items in file: " <<  n << std::endl;

    /* void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset)
     * mmap() creates a new mapping in the virtual address space of the
       calling process.
     * PROT_READ  Pages may be read.
     * MAP_SHARED Shared map.
     */

    int *mem = static_cast<int*>(mmap(nullptr, n, PROT_READ, MAP_SHARED, fd, 0));
    std::qsort(mem, n, sizeof(int), compare);
    print_arr(mem, n);
    return 0;
}