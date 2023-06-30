#!/bin/bash
make
./ext2-create
dumpe2fs cs111-base.img
sleep 1
fsck.ext2 cs111-base.img
mkdir mnt
sudo mount -o loop cs111-base.img mnt
ls -ain mnt
ls -ain "mnt/lost+found"
cat mnt/hello-world
cat mnt/hello
sudo umount mnt
rmdir mnt
make clean
