#include <iostream>
#include "libraries/signer/signer.h"

int main() {
    // p = 5, q = 11, n = p * q = 55, phi(n) = (p-1)(q-1) = 40
    // Datos del ejemplo de la presentación, debería poder encriptar y desencriptar
    uint64_t n = 55;
    uint64_t d = 27;
    uint64_t e = 3;

    Signer signer;

    // Encriptación
    uint64_t firma = signer.sign("Un mayhemsito? De chill", e, n);
    std::cout << "Firma: " << firma << std::endl;

    // Desencriptación (verificar la firma)
    // Hacemos la operación pero con d en lugar de e
    uint64_t verificacion = 1;
    for (uint32_t i = 0; i < d; i++)
    {
        verificacion = (verificacion * firma) % n;
    }
    std::cout << "Verificacion: " << verificacion << std::endl;

    // Si todo sale bien, la verificación debería ser igual al hash del mensaje original

    return 0;
}
