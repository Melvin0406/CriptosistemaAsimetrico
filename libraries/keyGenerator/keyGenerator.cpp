#include "keyGenerator.h"
#include "math.h"

KeyPair KeyGenerator::GenerateKeys()
{
    uint64_t e = 65537; // Exponente público comúnmente usado

    while (true) {
        uint64_t p = Math::GeneratePrime();
        uint64_t q = Math::GeneratePrime();

        if (p == q) continue;

        // Calculamos n y phi (coprimos de n)
        uint64_t n = p * q;
        uint64_t phi = (p - 1) * (q - 1);

        if (Math::GCD(e, phi) != 1) continue; // Asegurarse de que e y phi sean coprimos

        uint64_t d = Math::ModInverse(e, phi);

        return {n, e, d};
    }
}
