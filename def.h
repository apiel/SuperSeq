#ifndef _DEF_H_
#define _DEF_H_

#include <stdio.h>
#include <stdlib.h>
#ifndef WIN32
# include <unistd.h>
#endif
#include "lo/lo.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef log
#define log printf
#endif

#ifndef logError
#define logError printf
#endif

#ifndef MAX_SEQ
#define MAX_SEQ 512
#endif

#ifndef MAX_PATCH
#define MAX_PATCH 512
#endif

#ifndef PATCH_NAME_LEN
#define PATCH_NAME_LEN 32
#endif

#endif