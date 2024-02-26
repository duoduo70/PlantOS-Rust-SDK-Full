#include <debug_config.h>

#include <ctypes.h>
void *
memrchr(s, c, n)
    const void *s;
    int c;
    size_t n;
{
#ifdef DEBUG
    logkf("memrchr\n");
#endif
    const unsigned char *cp;

    if (n != 0) {
	cp = (unsigned char *)s + n;
	do {
	    if (*(--cp) == (unsigned char)c)
		return((void *)cp);
	} while (--n != 0);
    }
    return((void *)0);
}