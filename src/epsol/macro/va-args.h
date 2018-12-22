#ifndef EPSOL_MACRO_VA_ARGS_H_
#define EPSOL_MACRO_VA_ARGS_H_

#include "./base.h"
#include "./maybe.h"

/// HEAD & TAIL

#define EPSOL_VA_HEAD(a, ...) a
#define EPSOL_VA_TAIL(a, ...) __VA_ARGS__

/// EMPTY

#define EPSOL_VA_EMPTY(...)                                                 \
    EPSOL_MAYBE_VALUE_OR(                                                   \
        EPSOL_CONCAT(EPSOL_DETAIL_VA_EMPTY_,                                \
                     EPSOL_VA_HEAD(__VA_ARGS__ __EPSOL_VA_EMPTY_TESTER__)), \
        false)

#define EPSOL_DETAIL_VA_EMPTY___EPSOL_VA_EMPTY_TESTER__ EPSOL_JUST(true)

/// FOREACH

#define EPSOL_VA_FOREACH(f, ...) \
    EPSOL_EVAL_MAX(EPSOL_DETAIL_VA_FOREACH(f, __VA_ARGS__))

#define EPSOL_DETAIL_VA_FOREACH(f, ...)                         \
    EPSOL_IF(EPSOL_VA_EMPTY(__VA_ARGS__))                       \
    (, f(EPSOL_VA_HEAD(__VA_ARGS__))                            \
           EPSOL_DELAY_2(EPSOL_DETAIL_VA_FOREACH_TRANPOLINE)()( \
               f, EPSOL_VA_TAIL(__VA_ARGS__)))

#define EPSOL_DETAIL_VA_FOREACH_TRANPOLINE() EPSOL_DETAIL_VA_FOREACH

#endif  // EPSOL_MACRO_VA_ARGS_H_
