#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t pid;

void sigusr1_handler(int signo) {
    printf("Heathcliff is under attack.\n");

    const char* shm_name = "/hw5_shm";
    const int shm_size = 0xFFFFF;

    // create shared memory
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // create a new mapping in the virtual address space of the calling process.
    void* shm_ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // read message
    int immortal_object = 0;
    if (strlen((char*)shm_ptr) == 0xC8763) {
        int length = snprintf(NULL, 0, "%d", pid);
        char pid_str[length + 1];
        snprintf(pid_str, sizeof(pid_str), "%d", pid);
        
        for (int skill = 0; skill < length; skill++)
            for (int i = skill; i < 0xC8763; i+=length)
                if (*((char*)shm_ptr + i) != pid_str[skill]){
                    immortal_object = 1;
                    break;
                }
    }
    else
        immortal_object = 2;

    munmap(shm_ptr, shm_size);
    close(shm_fd);

    if (immortal_object) {
        printf("Isn't it quite a dramatic plot development?\n");
        return;
    }
    else {
        printf("You dare use my own spells against me, Kirito?\n");
        exit(0);
    }
}

int main() {
    printf("This, might be a game, but it isn't meant to be played.\n\t\t\t-by SAO Programmer Kayaba Akihiko\n");
    pid = getpid();
    printf("Heathcliff's PID: %d\n", pid);

    if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }
    while(1) // Oops, the logout button is missing from the main menu.
        pause();
    return 0;
}
