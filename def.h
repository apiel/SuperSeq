#ifndef _DEF_H_
#define _DEF_H_

#include <stdio.h>
#include <stdlib.h>
#ifndef WIN32
# include <unistd.h>
#endif
#include "lo/lo.h"

#ifndef log
#define log printf
#endif

#ifndef MAX_SEQ
#define MAX_SEQ 512
#endif

#endif