#include <iostream>
#include <cstdint>
#include "libraries/keyGenerator/keyGenerator.h"
#include "libraries/signer/signer.h"
#include "libraries/math/math.h"
#include "libraries/verifier/verifier.h"

// Vamos a probar si las llaves se generan bien. 
int main()
{
    std::string message = "Adomination";
    KeyPair keys = KeyGenerator::GenerateKeys();

    std::cout << "n: " << keys.n << std::endl;
    std::cout << "e: " << keys.e << std::endl;
    std::cout << "d: " << keys.d << std::endl;

    // Probamos la firma simulando la encriptación de RSA
    Signer signer;
    uint64_t firma = signer.sign(message, keys.d, keys.n);
    std::cout << "Firma: " << firma << std::endl;

    // Probamos la verificación
    Verifier verifier;
    bool is_valid = verifier.verify(message, firma, keys.e, keys.n);
    std::cout << "Firma valida: " << is_valid << std::endl;

    return 0;
}
