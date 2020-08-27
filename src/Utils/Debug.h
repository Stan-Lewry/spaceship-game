#pragma once

#include <cstdio>
#include <cstdarg>
#include <vector>
#include <string>

extern std::vector<std::string> globalDebugStringList;

template<typename... Args>
void SDEBUG(const char* format, Args... args) {
    char str[100];
    sprintf(str, format, args...);

    char out[100];
    sprintf(out, "[DEBUG]     %s", str);

    printf("%s\n", out);

    //globalDebugStringList.push_back(std::string(out));
}

template<typename... Args>
void SERROR(const char* format, Args... args) {
    char str[50];
    sprintf(str, format, args...);

    printf("[ERROR]     %s\n", str);
}
