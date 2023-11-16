#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

using namespace std;

int main(int argc, char *argv[])
{
    pid_t pid;
    cout << "Input Heathcliff's PID: ";
    cin >> pid;
    int pid_len = snprintf(NULL, 0, "%d", pid);
    char pid_str[pid_len + 1];
    snprintf(pid_str, sizeof(pid_str), "%d", pid);

    const char *shm_name = "/hw5_shm";
    const int shm_size = 0xC8763;

    // create shared memory
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(1);
    }

    // truncate shared memory
    if (ftruncate(shm_fd, shm_size) == -1)
    {
        perror("ftruncate");
        exit(1);
    }

    // create a new mapping in the virtual address space of the calling process.
    void *shm_ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    // write pid for times until the length to be 0xC8763
    char *shm_ptr_char = (char *)shm_ptr;
    int len = strlen((char *)shm_ptr);
    int i = 0;
    while (len < 0xC8763)
    {
        *shm_ptr_char = pid_str[i++ % pid_len];
        shm_ptr_char++;
        len = strlen((char *)shm_ptr);
    }

    // send SIGUSR1 to pid
    kill(pid, SIGUSR1);
    cout << "SIGUSR1 sent successfully" << endl;
    sleep(1);

    munmap(shm_ptr, shm_size);
    close(shm_fd);
    shm_unlink(shm_name);
}