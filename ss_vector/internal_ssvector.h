#ifndef INTERNAL_SS_VECTOR_H
#define INTERNAL_SS_VECTOR_H

#include <stdbool.h>
#include "ssvector.h"

#define GROWTH_FACTOR 2

bool _internal_ssv_resize(ssv_vector_t *vec);

#endif
