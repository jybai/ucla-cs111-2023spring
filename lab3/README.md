# Hash Hash Hash
This lab attempts to build a thread-safe hash table by implementing locking with `pthread_mutex_t`.

## Building
```
make
```

## Running
```shell
./hash-table-tester -t [NUM_OF_THREADS] -s [NUM_OF_TABLE_ENTRIES_TO_ADD_PER_THREAD]
```

## First Implementation
In the `hash_table_v1_add_entry` function, accessing any table entry requires acquiring a universal mutex lock.
Any modifications to entries is only permitted after acquiring of the lock.

### Performance
```shell
./hash-table-tester -t 4 -s 50000
Generation: 31,687 usec
Hash table base: 217,471 usec
  - 0 missing
Hash table v1: 497,514 usec
  - 0 missing
Hash table v2: 112,834 usec
  - 0 missing
```

This time version 1 is about twice as slow as the serial base version.
This is because when a thread tries to add a table entry, it gets blocked until the universal lock is available.
Thus, version 1 essentially runs serially (only 1 thread can change the table at once) but with the additional overhead of locking and unlocking.
Assuming the locking mechanism is approximately the same time complexity as adding a table entry, this explains the 2x runtime.

## Second Implementation
In the `hash_table_v2_add_entry` function, a mutex lock is created for each hash table entry.
Thus, threads accessing different table entries can run in parallel.
Locking and blocking only happens when two threads tries to add to the same hash table entry.
Since the hash table is sufficiently large and implemented properly, collision is unlikely.
Thus, we would expect k times speed up for k threads running on a machine with no less than k CPU cores.

### Performance
```shell
./hash-table-tester -t 4 -s 50000
Generation: 31,687 usec
Hash table base: 217,471 usec
  - 0 missing
Hash table v1: 497,514 usec
  - 0 missing
Hash table v2: 112,834 usec
  - 0 missing

```

This time the speed up of v2 is 4x compared to v1 and 2x compared to base serial.
This correctly corresponds to having 4 threads running in parallel.
Our design in v2 of having a mutex lock for each table entry thus sucessfully avoids excessive blocking.
The 2x compared to serial requires factoring the (approximately) 2x more work for the locking mechanism.

## Cleaning up
```
make clean
```
