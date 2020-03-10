#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include "curl/curl.h"
#include <string>

class DataFetcher
{
public:
    DataFetcher();
    std::string* getData(const std::string&);

private:
    static size_t writeFunction(void*, size_t, size_t, std::string*);
};

#endif // DATAFETCHER_H
