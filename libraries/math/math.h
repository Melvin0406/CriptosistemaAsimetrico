#ifndef MATH_H
#define MATH_H

#include <cstdint>

class Math
{
    public:
    uint64_t ModExp(uint64_t base, uint64_t exp, uint64_t mod);
};

#endif