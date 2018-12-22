#ifndef EPSOL_MACRO_LOGIC_H_
#define EPSOL_MACRO_LOGIC_H_

#include "./base/concat.h"
#include "./maybe.h"

/// AND

#define EPSOL_AND(l, r)                                                       \
    EPSOL_MAYBE_VALUE_OR(EPSOL_CONCAT(EPSOL_DETAIL_AND_, EPSOL_CONCAT(l, r)), \
                         false)
#define EPSOL_DETAIL_AND_truetrue EPSOL_JUST(true)

/// OR

#define EPSOL_OR(l, r)                                                       \
    EPSOL_MAYBE_VALUE_OR(EPSOL_CONCAT(EPSOL_DETAIL_OR_, EPSOL_CONCAT(l, r)), \
                         true)
#define EPSOL_DETAIL_AND_falsefalse EPSOL_JUST(true)

/// NOT

#define EPSOL_NOT(b) EPSOL_CONCAT(EPSOL_DETAIL_NOT_, b)
#define EPSOL_DETAIL_NOT_true false
#define EPSOL_DETAIL_NOT_false true

#endif  // EPSOL_MACRO_LOGIC_H_
