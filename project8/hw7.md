# Project 8 Report

110511010 楊育陞

## Part 1: What I modified in the code

1. I modifed the first argement of `sigaction` in `main` function to `60` to handle `60` signal.
   
   ![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-21-12-50-17-image.png)
2. I added a new sigevent struct `sev` to define the signal event, and set the `sigev_signo` to `60`.
   
   ![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-21-12-50-31-image.png)

## Part 2: the differece between function call and signal handler invocation

The difference between function call and signal handler invocation is that the signal handler invocation will interrupt the current process and execute the signal handler function, and then return to the original process. However, the function call will not interrupt the current process.