
CC          =	gcc

# Flags that are sent to the compiler  change the std if you wish

CFLAGS      =	-Wall -std=c99 -pedantic -g


test: src/Test.c src/SchnarrListAPI.c 

	$(CC) $(CFLAGS) src/Test.c src/SchnarrListAPI.c -Iinclude -o bin/test

	
simulation: src/SchnarrLight.c src/SchnarrListAPI.c

	$(CC) $(CFLAGS) src/SchnarrLight.c src/SchnarrListAPI.c -Iinclude -o bin/simulation


doxy: Doxyfile

	doxygen



clean:

	rm  -r bin/