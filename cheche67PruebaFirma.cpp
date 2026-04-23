#include <iostream>
#include "libraries/signer/signer.h"

int main() {
    // p = 61, q = 53, n = p * q = 3233, phi(n) = (p-1)(q-1) = 3120
    // Voy a ver cómo se comporta la firma con estos datos y encontrar errores
    uint64_t n = 3233;
    uint64_t d = 2753;

    Signer signer;

    // Caso normal
    uint64_t firma = signer.sign("Un mayhemsito? De chill", d, n);
    std::cout << "Firma: " << firma << std::endl;

    // Mismo mensaje debe dar misma firma
    uint64_t firma2 = signer.sign("Un mayhemsito? De chill", d, n);
    std::cout << "Misma firma?: " << (firma == firma2 ? "SI" : "NO") << std::endl;

    // Mensaje distinto debe dar firma distinta
    uint64_t firma3 = signer.sign("El bicho", d, n);
    std::cout << "Firma diferente con mensaje alterado?: " << (firma != firma3 ? "SI" : "NO") << std::endl;

    return 0;
}
