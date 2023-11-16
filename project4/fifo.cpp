#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <string.h>

using namespace std;

int main()
{
    string read_fifo = "hw5_read.fifo";
    string write_fifo = "hw5_write.fifo";
    int ret;
    ret = mkfifo(read_fifo.c_str(), 0666);
    if (ret == -1)
    {
        std::cout << "mkfifo failed" << endl;
        return EXIT_FAILURE;
    }

    ret = mkfifo(write_fifo.c_str(), 0666);
    if (ret == -1)
    {
        std::cout << "mkfifo failed" << endl;
        return EXIT_FAILURE;
    }

    int fd_read = open(read_fifo.c_str(), O_RDONLY);
    if (fd_read == -1)
    {
        std::cout << "open failed" << endl;
        return EXIT_FAILURE;
    }
    int fd_write = open(write_fifo.c_str(), O_WRONLY);
    if (fd_write == -1)
    {
        std::cout << "open failed" << endl;
        return EXIT_FAILURE;
    }

    int i = 1;
    char msg_read[100];
    char msg_write[100];
    while (1)
    {
        // read one line from read_fifo
        ret = read(fd_read, &msg_read, sizeof(msg_read));
        if (ret == -1)
        {
            std::cout << "read failed" << endl;
            return EXIT_FAILURE;
        }
        std::cout << "Received: " << msg_read;
        // check if the test is done
        if (strcmp(msg_read, "Well done!\n") == 0)
            break;
        strcpy(msg_write, msg_read);
        // sort the string
        sort(msg_write, msg_write + strlen(msg_write) - 1);
        // write to write_fifo
        ret = write(fd_write, &msg_write, sizeof(msg_write));
        if (ret == -1)
        {
            std::cout << "write failed" << endl;
            return EXIT_FAILURE;
        }
        std::cout << "Answer: " << msg_write << endl;
        // wait for 1 second
        sleep(1);
    }
    close(fd_read);
    close(fd_write);
    unlink(read_fifo.c_str());
    std::cout << "read_fifo unlinked" << endl;
    unlink(write_fifo.c_str());
    std::cout << "write_fifo unlinked" << endl;
    return EXIT_SUCCESS;
}
