#include <iostream>
#include <cstdint>
#include <random>

uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t mod) {
    return (a * b) % mod;
}

uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = mod_mul(result, base, mod);
        base = mod_mul(base, base, mod);
        exp >>= 1;
    }
    return result;
}

bool isPrime(uint64_t n) {
    if (n < 2) return false;
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
        uint64_t x = mod_exp(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}


uint32_t generatePrime() {
    static std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<uint32_t> dist(1ULL << 31, 0xFFFFFFFF);

    while (true) {
        uint32_t candidate = dist(rng) | 1; 
        if (isPrime(candidate)) {
            return candidate;
        }
    }
}

int main() {
    uint32_t prime = generatePrime();
    std::cout << "Generated prime: " << prime << std::endl;
    return 0;
}