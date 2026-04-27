#include "math.h"
#include <random>

// Manera segura de realizar multiplicación modular para evitar overflow
uint64_t Math::ModMul(uint64_t a, uint64_t b, uint64_t mod)
{
    return ((__uint128_t)a * b) % mod;
}

uint64_t Math::ModExp(uint64_t base, uint64_t exp, uint64_t mod)
{
    uint64_t result = 1;
    base = base % mod;

    while (exp > 0)
    {
        if (exp % 2 == 1) // If exp is odd
            result = ((__uint128_t)result * base) % mod;

        exp = exp >> 1; // Divide exp by 2
        base = ((__uint128_t)base * base) % mod;
    }
    return result;
}

// Test de primalidad de Miller-Rabin
bool Math::IsPrime(uint64_t n)
{
    if (n < 2) return false;
    // Checar si es divisible por primos chiquitos
    for (uint64_t p : {2, 3, 5, 7, 11}) {
        if (n % p == 0) return n == p;
    }

    
    uint64_t d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (uint64_t a : {2, 7, 61}) {
        if (a >= n) continue;
        uint64_t x = ModExp(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = ModMul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

uint32_t Math::GeneratePrime()
{
    static std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<uint32_t> dist(1ULL << 31, 0xFFFFFFFF);

    while (true) {
        uint32_t candidate = dist(rng) | 1;
        if (IsPrime(candidate))
            return candidate;
    }
}

// Euclides
uint64_t Math::GCD(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Euclides extendido para encontrar el inverso multiplicativo
uint64_t Math::ModInverse(uint64_t e, uint64_t phi)
{
    __int128 t = 0, new_t = 1;
    __int128 r = phi, new_r = e;

    while (new_r != 0) {
        __int128 q = r / new_r;

        __int128 temp = new_t;
        new_t = t - q * new_t;
        t = temp;

        temp = new_r;
        new_r = r - q * new_r;
        r = temp;
    }

    if (r > 1) return 0; // No existe inverso
    if (t < 0) t += phi;

    return (uint64_t)t;
}
