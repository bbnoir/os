#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


const char *string_to_write = "hw6-1, 311551xxx";   // Task0: Change this string with your own student ID.

int main() {
    // 1. Create and Open your own shared file
    int fd = open("shared_file1", , );               // Task1: Complete open() function.
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // 2. Set the size of shared file
    int data_size = ;                               // Task2: Complete data_size.
    if (ftruncate(fd, data_size) == -1) {
        perror("ftruncate");
        return 1;
    }
    
    // 3. Use mmap() to map the memory
    char *shared_data = mmap(, , , , , );           // Task3: Complete mmap() function.
    if (shared_data == MAP_FAILED) {
        perror("mmap failed\n");
        return 1;
    }

    // 4. Write data
    strcpy( , );                                    // Task4: Complete write data part.

    
    // 5. Use munmap() to un map the memory
    if (munmap(, ) == -1) {                         // Task5: Complete munmap() function.
        perror("munmap failed\n");
        return 1;
    }
    
    close(fd);
    
    return 0;
}

