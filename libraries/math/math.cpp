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
// La base matemática es que si n es primo, entonces para cualquier base a se cumple:
// a^d ≡ 1 (mod n) o a^(d*2^r) ≡ -1 (mod n), con r < s y n-1 = d * 2^s
bool Math::IsPrime(uint64_t n)
{
    if (n < 2) return false;
    // Checar si es divisible por primos chiquitos
    for (uint64_t p : {2, 3, 5, 7, 11}) {
        if (n % p == 0) return n == p;
    }

    // Representamos n-1 como d * 2^s
    uint64_t d = n - 1;
    int s = 0;
    // Mientras d sea par, dividimos entre 2 y aumentamos s
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    // Testigos suficientes para garantizar primalidad en nuestro caso
    for (uint64_t a : {2, 7, 61}) {
        if (a >= n) continue;
        // x = a^d % n
        uint64_t x = ModExp(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = ModMul(x, x, n); // x = x² % n  →  siguiente término
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
    // Asignamos semilla
    static std::mt19937_64 rng(std::random_device{}());
    // Genera números de 32 bits aleateorios
    std::uniform_int_distribution<uint32_t> dist(1ULL << 31, 0xFFFFFFFF);

    while (true) {
        // Aseguramos que el número sea impar
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
    // r     = t     * e  +  (algo) * phi
    // new_r = new_t * e  +  (algo) * phi
    __int128 t = 0, new_t = 1;
    __int128 r = phi, new_r = e;

    while (new_r != 0) {
        // r = q * new_r + residuo
        __int128 q = r / new_r;

        // t y new_t son nuestras variables que trackean el inverso multiplicativo
        // t - q * new_t vendría siendo el siguiente coeficiente de e en la combinación lineal
        __int128 temp = new_t;
        new_t = t - q * new_t;
        t = temp;

        // Nuestro nuevo r es el residuo y r pasa a ser el dividendo
        // Corresponde al algoritmo de Euclides normal
        temp = new_r;
        new_r = r - q * new_r;
        r = temp;
    }

    // r es el gcd, t es el inverso multiplicativo
    if (r > 1) return 0; // No existe inverso
    if (t < 0) t += phi; // ajusta si t salió negativo (mod phi)

    return (uint64_t)t;
}
