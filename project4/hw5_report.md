# Report

110511010 楊育陞

## Part 1

**a. test result:**

![](C:\Users\User\AppData\Roaming\marktext\images\2023-11-16-15-52-21-image.png)

**b. What might happen if your program didn't call sleep(1) ? Why?**
=> The program will read the same value from the FIFO, because the program will read the FIFO before the shell finish reading the FIFO and write to it, which is usually slower than the program. And the shell will keep waiting to read.

![](C:\Users\User\AppData\Roaming\marktext\images\2023-11-16-13-42-52-image.png)

**c. What happens when a process writes to a FIFO, but there is no process reading from it?**
=> According to linux manual, the process will be blocked until another process opens the FIFO for reading.

![](C:\Users\User\AppData\Roaming\marktext\images\2023-11-16-13-13-35-image.png)

## Part 2

**a. test result:**

![](C:\Users\User\AppData\Roaming\marktext\images\2023-11-16-15-42-18-image.png)

**b. How did you defeat Heathcliff ?**
=> Write down the pid of Heathcliff repeatedly for size of 0xC8763 to shared memory, and send SIGUSR1 to Heathcliff.

**c. What might happen if you reverse steps 6 and 7, meaning, sending SIGUSR1 before writing the data?**
=> Heathcliff will start to read the shared memory before the data is finished writing, which may cause Heathcliff to read the wrong data and fail to defeat Heathcliff.

![](C:\Users\User\AppData\Roaming\marktext\images\2023-11-16-15-50-05-image.png)
