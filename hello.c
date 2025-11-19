typedef unsigned long size_t;
typedef   signed long ssize_t;

static
ssize_t write(int fd, const void* data, size_t size)
{
    register ssize_t count asm("rax");
    asm (
        "mov rax, $1;"
        "mov edi, %[fd];"
        "lea rsi, %[data];"
        "mov rdx, %[size];"
        "syscall;"
        : "=r" (count)
        : [fd] "ir"(fd), [data] "im"(*(char*) data), [size] "ir"(size)
        : "edi", "rsi", "rdx"
    );
    return count;
}

static _Noreturn
void exit(int code)
{
    asm (
        "mov rax, $60;"
        "mov edi, %[code];"
        "syscall;"
        :
        : [code] "ir"(code)
        : "rax", "edi"
    );
    __builtin_unreachable();
}

static __attribute((always_inline))
int _main() {
    __attribute((section(".text")))
    static const char hello[] = "👋\n";
    ssize_t count = write(1, hello, sizeof(hello)-1);
    return count < 0 ? -count : 0;
}

void _start() {
    exit(_main());
}
