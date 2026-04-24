#include "math.h"

uint64_t Math::ModExp(uint64_t base, uint64_t exp, uint64_t mod)
    {
        uint64_t result = 1;
        base = base % mod;

        while (exp > 0)
        {
            if (exp % 2 == 1) // If exp is odd
            {
                result = ((__uint128_t)result * base) % mod;
            }

            exp = exp >> 1; // Divide exp by 2
            base = ((__uint128_t)base * base) % mod;
        }
        return result;
    }