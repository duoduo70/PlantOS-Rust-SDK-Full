#include <debug_config.h>
#include <errno.h>

int *__errno_location (void)
{
  PRTL_DEBUG_INCLUDE_CURRENT_FUNC

  return &errno;
}