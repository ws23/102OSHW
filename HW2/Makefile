main: src/main.o src/crypt.o src/file.o
	gcc src/main.o src/crypt.o src/file.o -o ./mycopy -O2 -Wall -Wshadow -lm
	rm -rf src/*.o src/*.gch
main.o: src/main.c
	gcc src/main.c -c

crypt.o: src/crypt.c src/crypt.h
	gcc src/crypt.c src/crypt.h -c

file.o: src/file.c src/file.h
	gcc src/file.c src/file.h -c
