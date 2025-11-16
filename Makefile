
ifunc-resolver: program.c function-list.c
	gcc -o $@ -Wall -Wpedantic $^

glibc:
	git clone --depth=1 git://sourceware.org/git/glibc.git

function-list.c: glibc
	echo "#include <stddef.h>\nconst char* function_names[] = {" > $@
	grep -hr 'IFUNC_IMPL (' glibc | awk '{print substr($$4, 1, length($$4)-1)}' | LC_COLLATE=C sort -u | awk '{print "  \""$$1"\","}' >> $@
	echo "  NULL,\n};" >> $@

dump: ifunc-resolver
	./ifunc-resolver

clean:
	rm -f ifunc-resolver function-list.c

.PHONY: dump clean
