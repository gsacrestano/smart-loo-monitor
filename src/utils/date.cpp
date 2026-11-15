#include <Arduino.h>
#include "date.h"
#include "time.h"

namespace
{
    const char *ntpServer1 = "pool.ntp.org";
    const char *ntpServer2 = "time.nist.gov";
    // POSIX timezone string for Italy (CET/CEST with automatic EU DST adjustment)
    const char *timezone_posix = "CET-1CEST-2,M3.5.0/2,M10.5.0/3";
    struct tm timeinfo;
}

namespace date
{
    void begin()
    {
        configTzTime(timezone_posix, ntpServer1, ntpServer2);
        getLocalTime(&timeinfo);
        Serial.printf("%d:%d", timeinfo.tm_hour, timeinfo.tm_min);
    }

    uint8_t get_day_of_the_month()
    {
        if (!getLocalTime(&timeinfo))
            return 1;
        return timeinfo.tm_mday;
    }

} // namespace date
