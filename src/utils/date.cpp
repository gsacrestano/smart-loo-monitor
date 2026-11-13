#include <Arduino.h>
#include "date.h"
#include "time.h"

namespace
{
    const char *ntpServer1 = "pool.ntp.org";
    const char *ntpServer2 = "time.nist.gov";
    // POSIX timezone string for Italy (CET/CEST with automatic EU DST adjustment)
    const char *timezone_posix = "CET-1CEST-2,M3.5.0/01:00:00,M10.5.0/01:00:00";
    struct tm timeinfo;
}

namespace date
{
    void begin()
    {
        configTzTime(timezone_posix, ntpServer1, ntpServer2);
    }

    uint8_t get_day_of_the_month()
    {
        return timeinfo.tm_mday;
    }

} // namespace date
