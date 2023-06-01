#include "utils.h"
#include <string>
#include <cstdarg>
#include <vector>

std::string
format(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    std::string buf = vformat(fmt, ap);
    va_end(ap);
    return buf;
}

std::string
vformat (const char *fmt, va_list ap)
{
    size_t size = COMMAND_MAX_SIZE;
    char buf[COMMAND_MAX_SIZE];

    va_list apcopy;
    va_copy(apcopy, ap);
    int needed = vsnprintf(&buf[0], size, fmt, ap);

    if ((needed <= static_cast<int>(size)) && (needed >= 0))
    {
        return std::string (&buf[0]);
    }
    else
    {
        std::vector <char> buf;
        size = needed;
        buf.resize (size);
        needed = vsnprintf (&buf[0], size, fmt, apcopy);
        return std::string (&buf[0]);
    }
}
