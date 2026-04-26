#include <iostream>
#include <cstdint>
#include <random>

uint64_t n_global;
uint64_t e_global;
uint64_t d_global;


// Manera segura de realizar multiplicación modular para evitar overflow
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

// Test de primalidad de Miller-Rabin
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

// Euclides
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Euclides extendido para encontrar el inverso multiplicativo
int64_t mod_inverse(int64_t e, int64_t phi) {
    int64_t t = 0, new_t = 1;
    int64_t r = phi, new_r = e;

    while (new_r != 0) {
        int64_t q = r / new_r;

        int64_t temp = new_t;
        new_t = t - q * new_t;
        t = temp;

        temp = new_r;
        new_r = r - q * new_r;
        r = temp;
    }

    if (r > 1) return -1; // No existe inverso
    if (t < 0) t += phi;

    return t;
}

void generarLlaves() {
    uint64_t e = 65537; // Exponente público comúnmente usado

    while (true) {
        uint64_t p = generatePrime();
        uint64_t q = generatePrime();

        if (p == q) continue;

        uint64_t n = p * q;
        uint64_t phi = (p - 1) * (q - 1);

        if (gcd(e, phi) != 1) continue; // Asegurarse de que e y phi sean coprimos

        uint64_t d = mod_inverse(e, phi);

        n_global = n;
        e_global = e;
        d_global = d;

        break;
    }
}