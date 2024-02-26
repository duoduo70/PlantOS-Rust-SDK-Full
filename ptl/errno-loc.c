#include <debug_config.h>
#include <errno.h>

int *__errno_location (void)
{
#ifdef DEBUG
    logkf("__errno_location\n");
#endif
  return &errno;
}