#ifndef EPSOL_RANGE_MACRO_
#define EPSOL_RANGE_MACRO_

#define RANGE(container) begin(container), end(container)
#define RANGE_R(container) rbegin(container), rend(container)

#define FOR_EACH(val_name, container) for (auto val_name : container)
#define FOR_EACH_REF(val_name, container) for (auto &val_name : container)
#define FOR_EACH_CREF(val_name, container)                                    \
    for (const auto &val_name : container)

#endif // EPSOL_RANGE_MACRO_