CFLAGS=\
	-static \
	-flto \
	-O3 \
	-masm=intel \
	-nostdlib \
	-ffreestanding \
	-fno-asynchronous-unwind-tables \
	-fno-ident \
	-Wl,--build-id=none \
	-s \
# /CFLAGS

hello: hello.c Makefile
	clang ${CFLAGS} -o $@ $<

.PHONY: hello.run
.SILENT: hello.run
hello.run: hello
	./$<

.PHONY: env
env: compile_flags.txt
compile_flags.txt: Makefile
	printf "%s\n" ${CFLAGS} > $@

.PHONY: clean
clean:
	rm -f hello compile_flags.txt
