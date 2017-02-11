#ifndef EPSOL_TIME_
#define EPSOL_TIME_

// mark the difference between local time and GMT
// alse defines epsol::time::now()
#include "time/time-zone.h"

// extract time informations like 'year' etc. from std::chrono::time_point
#include "time/extract.h"

// turn std::duration to string and enable streaming output
#include "time/to-string.h"

// timer utility
#include "time/timer.h"

#endif // EPSOL_TIME_
