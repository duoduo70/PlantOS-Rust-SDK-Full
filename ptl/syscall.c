#include <debug_config.h>
#include <stdarg.h>
#include <syscall.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>

#define SYS_read 0
#define SYS_write 1
#define	SYS_open 2
#define	SYS_close 3
#define	SYS_lseek 8
#define SYS_fork 57
#define SYS_exit 60

#define VAFUNC_CALL(args_num, ret_type, fncall) \
    {                                           \
        int temp__ = args_num;                  \
        va_list valist__;                       \
        va_start(valist__, temp__);             \
        ret_type ret_code__ = fncall;           \
        va_end(valist__);                       \
        return ret_code__;                      \
    }
#define VAFUNC_CALL_NORET(args_num, fncall) \
    {                                       \
        int temp__ = args_num;              \
        va_list valist__;                   \
        va_start(valist__, temp__);         \
        fncall;                             \
        va_end(valist__);                   \
        break;                              \
    }
#define VA_READ(type) va_arg(valist__, type)

void sys_exit(int retcode)
{
    exit();
}
int sys_fork()
{
    return fork();
}
ssize_t sys_read(int fd, void *buf, size_t count)
{
    if (fd == 0) {
        return read((int)stdin, buf, count);
    } else if (fd == 1) {
        return read((int)stdout, buf, count);
    } else if (fd == 2) {
        return read((int)stderr, buf, count);
    } else {
        return read(fd, buf, count);
    }
    
}
ssize_t sys_write(int fd, const void *buf, size_t count)
{
    if (fd == 0) {
        return write((int)stdin, buf, count);
    } else if (fd == 1) {
        return write((int)stdout, buf, count);
    } else if (fd == 2) {
        return write((int)stderr, buf, count);
    } else {
        return write(fd, buf, count);
    }
}
int sys_open(const char *pathname, int flags)
{
    return open(pathname, flags);
}
int sys_close(int fd)
{
    if (fd == 0) {
        return close((int)stdin);
    } else if (fd == 1) {
        return close((int)stdout);
    } else if (fd == 2) {
        return close((int)stderr);
    } else {
        return close(fd);
    }
    return close(fd);
}
int sys_lseek(int fd, off_t offset, int whence)
{
    if (fd == 0) {
        return lseek((int)stdin, offset, whence);
    } else if (fd == 1) {
        return lseek((int)stdout, offset, whence);
    } else if (fd == 2) {
        return lseek((int)stderr, offset, whence);
    } else {
        return lseek(fd, offset, whence);
    }
}

void *syscall(int num, ...)
{
#ifdef DEBUG
    logkf("syscall: %d\n", num);
#endif
    switch (num)
    {
    case SYS_exit:
        VAFUNC_CALL_NORET(1, sys_exit(VA_READ(int)));
    case SYS_fork:
        return sys_fork();
    case SYS_read:
        VAFUNC_CALL(3, ssize_t, sys_read(VA_READ(int), VA_READ(void *), VA_READ(size_t)));
    case SYS_write:
        VAFUNC_CALL(3, ssize_t, sys_write(VA_READ(int), VA_READ(const void *), VA_READ(size_t)));
    case SYS_open:
        VAFUNC_CALL(2, ssize_t, sys_open(VA_READ(const char *), VA_READ(int)));
    case SYS_close:
        VAFUNC_CALL(1, ssize_t, sys_close(VA_READ(int)));
    case SYS_lseek:
        VAFUNC_CALL(3, ssize_t, sys_lseek(VA_READ(int), VA_READ(off_t), VA_READ(int)));
    default:
        break;
    }
    return 0;
}