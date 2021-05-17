CC=clang
main: *c
	$(CC) main.c -o bfi --std=c99