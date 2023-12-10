# HW7 REPORT

110511010 楊育陞

**Q1: In Part 1, you used three APIs: mmap(), munmap(), and open(). Please explain the arguments passed to each API.**

a. mmap():

```
char *shared_data = mmap(NULL, data_size, PROT_WRITE, MAP_SHARED, fd, 0);
```

1. NULL: the kernel chooses the address at which to create the mapping
2. data_size: the length of the mapping, here it is the length of the string
3. PROT_WRITE: set the memory protection of the mapping to allow writing
4. MAP_SHARED: share this mapping with all other processes that map this object
5. fd: the file descriptor of the file to be mapped
6. 0: the offset within the file to start the mapping
   return -> shared_data: the starting address of the mapping

b. munmap():

```
munmap(shared_data, data_size);
```

1. shared_data: the starting address of the mapping to be unmapped
2. data_size: the length of the mapping to be unmapped

c. open():

```
int fd = open("shared_file1", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
```

1. "shared_file1": the name of the file to be opened
2. O_RDWR: open the file for reading and writing
3. O_CREAT: create the file if it does not exist
4. S_IRUSR | S_IWUSR: set the file permissions to read and write for the user if the file is created
   return -> fd: the file descriptor of the opened file

**Q2: In Part2, you used the API mprotect(). Please explain the arguments passed to mprotect().**

```
mprotect(shared_data, data_size, PROT_WRITE);
```

1. shared_data: the starting address of the mapping to be protected
2. data_size: the length of the mapping to be protected
3. PROT_WRITE: set the memory protection of the mapping to allow writing

**Q3: What advantages does memory-mapped I/O offer over standard file I/O (e.g. read, read, …)?**

Memory-mapped I/O is faster than standard file I/O because it does not require the kernel to copy data from the kernel buffer to the user buffer. Instead, the user buffer is mapped directly to the kernel buffer. This is especially useful when the file is large.
