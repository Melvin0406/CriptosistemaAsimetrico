#ifndef MATH_H
#define MATH_H

#include <cstdint>

class Math
{
    public:
    static uint64_t ModMul(uint64_t a, uint64_t b, uint64_t mod);
    static uint64_t ModExp(uint64_t base, uint64_t exp, uint64_t mod);
    static bool IsPrime(uint64_t n);
    static uint32_t GeneratePrime();
    static uint64_t GCD(uint64_t a, uint64_t b);
    static uint64_t ModInverse(uint64_t e, uint64_t phi);
};

#endif
