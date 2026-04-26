#include <iostream>
#include <cstdint>
#include "libraries/math/math.h"

uint64_t n_global;
uint64_t e_global;
uint64_t d_global;

void generarLlaves() {
    uint64_t e = 65537; // Exponente público comúnmente usado

    while (true) {
        uint64_t p = Math::GeneratePrime();
        uint64_t q = Math::GeneratePrime();

        if (p == q) continue;

        uint64_t n = p * q;
        uint64_t phi = (p - 1) * (q - 1);

        if (Math::GCD(e, phi) != 1) continue; // Asegurarse de que e y phi sean coprimos

        uint64_t d = Math::ModInverse(e, phi);

        n_global = n;
        e_global = e;
        d_global = d;

        break;
    }
}
