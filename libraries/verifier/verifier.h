#ifndef VERIFIER_H
#define VERIFIER_H

#include <iostream>
#include <cstdint>
#include "chemash.h"
#include "math.h"

class Verifier
{
    public:
    Verifier();
    ~Verifier();

    bool verify(std::string message, uint64_t signature, uint64_t e, uint64_t n);
};

#endif