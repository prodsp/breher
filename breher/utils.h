#ifndef UTILS_H
#define UTILS_H

#include <string>

constexpr uint32_t COMMAND_MAX_SIZE = 1024;
std::string format(const char *fmt, ...);
std::string vformat (const char *fmt, va_list ap);

#endif // UTILS_H
