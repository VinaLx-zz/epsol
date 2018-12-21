#ifndef EPSOL_MACRO_BASE_H_
#define EPSOL_MACRO_BASE_H_

/// CONCAT

#define EPSOL_CONCAT(a, b) EPSOL_DETAIL_CONCAT(a, b)

#define EPSOL_DETAIL_CONCAT(a, b) a##b

/// IF

#define EPSOL_IF(mbool) EPSOL_CONCAT(EPSOL_DETAIL_IF_, mbool)

#define EPSOL_DETAIL_IF_true(t, ...) t

#define EPSOL_DETAIL_IF_false(t, ...) __VA_ARGS__

#define EPSOL_EMPTY()

/// DELAY

#define EPSOL_DELAY(f) f EPSOL_EMPTY()

#define EPSOL_DELAY_1(f) f EPSOL_EMPTY()

#define EPSOL_DELAY_2(f) EPSOL_DELAY(f) EPSOL_EMPTY()

#define EPSOL_DELAY_3(f) EPSOL_DELAY_2(f) EPSOL_EMPTY()

#define EPSOL_DELAY_4(f) EPSOL_DELAY_3(f) EPSOL_EMPTY()

/// EVAL

#define EPSOL_EVAL(...) __VA_ARGS__

#define EPSOL_EVAL_1(...) __VA_ARGS__

#define EPSOL_EVAL_2(...) EPSOL_EVAL_1(__VA_ARGS__)

#define EPSOL_EVAL_3(...) EPSOL_EVAL_2(__VA_ARGS__)

#define EPSOL_EVAL_4(...) EPSOL_EVAL_3(__VA_ARGS__)


#endif  // EPSOL_MACRO_BASE_H_
