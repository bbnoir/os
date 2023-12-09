#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


const char *string_to_write = "hw6-2, 311551xxx";   // Same as hw6_write1.c, but this one is "hw6-2".

int main() {
    // 1. Create and Open your own shared file
    int fd = open("shared_file2", , );               // Same as hw6_write1.c.
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // 2. Set the size of shared file
    int data_size = ;                               // Same as hw6_write1.c.
    if (ftruncate(fd, data_size) == -1) {
        perror("ftruncate");
        return 1;
    }
    
    // 3. Use mmap() to map the memory
    char *shared_data = mmap(, , PROT_NONE, , , );  // Don't permit any access, others same as hw6_write1.c.
    if (shared_data == MAP_FAILED) {
        perror("mmap failed\n");
        return 1;
    }
    // 4. Use mprotect to permit the write access. 
    if (mprotect(, , ) == -1) {                     // Task: Complete mprotect() function.
        perror("mprotect");
        return 1;
    }

    // 5. Write data
    strcpy( , );                                    // Same as hw6_write1.c.

    
    // 6. Use munmap() to un map the memory
    if (munmap(, ) == -1) {                         // Same as hw6_write1.c.
        perror("munmap failed\n");
        return 1;
    }
    
    close(fd);
    
    return 0;
}

