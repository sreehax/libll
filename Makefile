all:
	gcc -c lists.c -I.
	ar rcs libll.a *.o
clean:
	rm *.o *.a
