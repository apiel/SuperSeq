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

#ifndef MAX_MSG
#define MAX_MSG 512
#endif

#endif