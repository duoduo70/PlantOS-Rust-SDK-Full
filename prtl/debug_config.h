#ifdef DEBUG
#include <stdio.h>
#define PRTL_DEBUG_INCLUDE_CURRENT_FUNC logkf("PRTL: %s/%s called\n", __FILE__, __PRETTY_FUNCTION__);
#else
#define PRTL_DEBUG_INCLUDE_CURRENT_FUNC
#endif