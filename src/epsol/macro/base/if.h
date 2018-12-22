#ifndef EPSOL_MACRO_BASE_IF_H_
#define EPSOL_MACRO_BASE_IF_H_

#include "./concat.h"

#define EPSOL_IF(mbool) EPSOL_CONCAT(EPSOL_DETAIL_IF_, mbool)

#define EPSOL_DETAIL_IF_true(t, ...) t

#define EPSOL_DETAIL_IF_false(t, ...) __VA_ARGS__


#endif // EPSOL_MACRO_BASE_IF_H_
