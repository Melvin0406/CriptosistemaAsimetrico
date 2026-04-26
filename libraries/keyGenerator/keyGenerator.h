#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <cstdint>

struct KeyPair {
    uint64_t n;
    uint64_t e;
    uint64_t d;
};

class KeyGenerator
{
public:
    static KeyPair GenerateKeys();
};

#endif
