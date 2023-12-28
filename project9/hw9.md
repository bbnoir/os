# Project 9 File System Operations

110511010 楊育陞

## Part 1

![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-21-42-07-image.png)


First I open the source file for reading and destination file for writing by specifying the file name and the mode. And I check if the file is opened successfully by checking if the file pointer is NULL.



![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-21-42-50-image.png)


Then I read the contents of the source file into the buffer by using `fread()` function. And I check if the file is read successfully by checking if buffer pointer is NULL.



![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-21-43-12-image.png)


I use a for loop to swap to reverse the contents of the buffer.



![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-21-58-32-image.png)

After reversing the buffer, I use `fwrite()` function to write the reversed buffer to the destination file. And I check if the file is written successfully by checking if the return value of `fwrite()` is equal to the size of the buffer.



![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-21-58-42-image.png)


I use `free()` function to free the memory allocated to the buffer. And I use `fclose()` function to close the source file and destination file.

## Part 2

![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-22-02-24-image.png)



First I open the directory specified by the command line argument by using `opendir()` function. And I check if the directory is opened successfully by checking if the directory pointer is NULL.



![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-22-04-16-image.png)



Then I loop through each entry in the directory by using `readdir()` function in a while loop.



![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-22-02-49-image.png)



Then I store the information of the entry in the `statBuffer` by using `stat()` function. And I check if the information is stored successfully by checking if the return value of `stat()` is equal to -1.



![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-22-04-39-image.png)



Then I print the information of the entry.
To print the file name, I use `d_name` in the `entry`.
To print the file size, I use `st_size` in the `statBuffer`.
To print the file type, I use `S_ISREG()` function to check if the file is a regular file and use `S_ISDIR()` function to check if the file is a directory.
To print the modification time, I use `st_mtime` in the `statBuffer` and use `ctime()` function to convert the modification time to a string.



![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-22-05-17-image.png)



Finally, I use `closedir()` function to close the directory.



screenshot of test result:



![](C:\Users\User\AppData\Roaming\marktext\images\2023-12-28-22-00-49-image.png)
