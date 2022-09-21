
ifunc-resolver: *.c
	gcc -o ifunc-resolver -Wall -Wpedantic program.c

dump: ifunc-resolver
	./ifunc-resolver

clean:
	rm -f ifunc-resolver

.PHONY: dump clean
