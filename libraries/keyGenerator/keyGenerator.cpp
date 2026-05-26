#include "keyGenerator.h"
#include "libraries/math/math.h"

KeyPair KeyGenerator::GenerateKeys()
{
    uint64_t e = 65537; // Exponente público comúnmente usado

    while (true) {
        uint32_t p = Math::GeneratePrime();
        uint32_t q = Math::GeneratePrime();

        if (p == q) continue;

        // Calculamos n y phi (coprimos de n)
        uint64_t n = (uint64_t)p * (uint64_t)q;
        uint64_t phi = ((uint64_t)p - 1) * ((uint64_t)q - 1);

        if (Math::GCD(e, phi) != 1) continue; // Asegurarse de que e y phi sean coprimos

        // Calculamos el inverso multiplicativo, que es parte de la llave privada
        uint64_t d = Math::ModInverse(e, phi);

        return {n, e, d};
    }
}
