all:
	gcc -O2 fork1.c -o fork1 -Wall
	gcc -O2 fork2.c -o fork2 -Wall
	gcc -O2 threads1.c -o threads1 -pthread -Wall
	gcc -O2 spawn_proc.c -o spawn_proc -Wall
	gcc -O2 spawn_threads.c -o spawn_threads -pthread -Wall

clean:
	rm -f fork1 fork2 threads1 spawn_proc spawn_threads
