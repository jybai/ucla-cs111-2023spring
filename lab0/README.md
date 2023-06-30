## UID: 405729088

(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

# A Kernel Seedling

Implement a process counter via the proc file interface (`/proc/count`).

## Building

Build the kernel module by running `make`.

## Running

Load the kernel module with `sudo insmod proc_count.ko`. Read the proc file `/proc/count` for result (e.g. `cat /proc/count`).

## Cleaning Up

Remove the kernel module with `sudo rmsmod proc_count`. Remove the compiled results with `make clean`.

## Testing

Testing is done on kernel version `5.14.8-arch1-1`.
