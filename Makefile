CC=tigcc
CFLAGS=-std=c99 -O2

.PHONY: clean

./bin/i68soyuz.9xz: ./src/i68soyuz.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm ./bin/i68soyuz.9xz
