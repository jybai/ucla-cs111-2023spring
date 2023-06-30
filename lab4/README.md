## UID: 405729088

# Hey! I'm Filing Here
This lab attempts to create an disk image formatted in the EXT2 file system and mount it.

## Building
The program builds a EXT2 formatted file system by sequentially writing the following data to a file:
1. Superblock information
2. Group descriptors
3. Block bitmap
4. Inode bitmap
5. Inode table
7. Corresponding files in the image (directories and files)

## Running
Compile:
```
make # compile the executable
```

Create image:
```
./ext2-create # run the executable to create cs111-base.img
```

Create directory to mount image:
```
mkdir mnt # create a directory to mnt your filesystem to
```

Mount:
```
sudo mount -o loop cs111-base.img mnt # mount your filesystem, loop lets you use a file
```

Sample output of `ls -ain` of the mounted image, `cs111-base.img`:
```
total 7
     2 drwxr-xr-x 3    0    0 1024 May 30 11:37 .
942169 drwxr-xr-x 4 1000 1000 4096 May 30 11:37 ..
    13 lrw-r--r-- 1 1000 1000   11 May 30 11:37 hello -> hello-world
    12 -rw-r--r-- 1 1000 1000   12 May 30 11:37 hello-world
    11 drwxr-xr-x 2    0    0 1024 May 30 11:37 lost+found
```

## Cleaning up
Unmount:
```
sudo umount mnt
```

Remove mount directory:
```
rmdir mnt
```

Clean up binaries:
```
make clean
```

