#include <iostream>
#include <cstdint>
#include "libraries/keyGenerator/keyGenerator.h"
#include "libraries/signer/signer.h"
#include "libraries/math/math.h"

// Vamos a probar si las llaves se generan bien. 
int main()
{
    KeyPair keys = KeyGenerator::GenerateKeys();

    std::cout << "n: " << keys.n << std::endl;
    std::cout << "e: " << keys.e << std::endl;
    std::cout << "d: " << keys.d << std::endl;

    // Probamos la firma simulando la encriptación de RSA
    Signer signer;
    uint64_t firma = signer.sign("Adomination", keys.d, keys.n);
    std::cout << "Firma: " << firma << std::endl;

    // Ahora voy a desencriptar y debería de coincidir con el hash original
    uint64_t desencriptado = Math::ModExp(firma, keys.e, keys.n);
    std::cout << "Desencriptado: " << desencriptado << std::endl;

    return 0;
}
