# Report

110511010 楊育陞

## Part 1

a. test result:

![hw5_1.png](\\wsl.localhost\Ubuntu-22.04\home\bbnoir\OS\project4\pic\hw5_1.png)

b. What might happen if your program didn't call sleep(1) ? Why?
=> The program will read the same value from the FIFO, because the program will read the FIFO before the shell finish reading the FIFO and write to it, which is usually slower than the program.


c. What happens when a process writes to a FIFO, but there is no process reading from it?
=> According to linux manual, the process will be blocked until another process opens the FIFO for reading.

![](C:\Users\User\AppData\Roaming\marktext\images\2023-11-16-13-13-35-image.png)


