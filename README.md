# ThreadPool
A custom C++ thread pool 

It is extraordinarily simple, and I made it just to dip my hands into concurrency. 
                 
SMALL CHUNKS: 1e6 additions each on a different thread

\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

Running on main thread: 4 milliseconds

Running on 1 thread: 1150 milliseconds

Running on 2 thread: 1031 milliseconds

Running on 3 thread: 1016 milliseconds

Running on 4 thread: 1119 milliseconds

Running on 5 thread: 1898 milliseconds

Running on 6 thread: 5597 milliseconds

Running on 7 thread: 5755 milliseconds

Running on 8 thread: 6144 milliseconds

Running on 9 thread: 5590 milliseconds

Running on 10 thread: 6033 milliseconds

BIG CHUNKS: 1e3 additions of chunks of 1e6 size

\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

Running on main thread: 1684 milliseconds

Running on 1 thread: 1666 milliseconds

Running on 2 thread: 859 milliseconds

Running on 3 thread: 582 milliseconds

Running on 4 thread: 461 milliseconds

Running on 5 thread: 380 milliseconds

Running on 6 thread: 326 milliseconds

Running on 7 thread: 291 milliseconds

Running on 8 thread: 360 milliseconds

Running on 9 thread: 284 milliseconds

Running on 10 thread: 285 milliseconds

These tests show how there is quite a significant overhead in creating threads, but if each thread does enough work it does result in a significant speed up.
