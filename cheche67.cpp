#include <iostream>
#include <cstdint>
#include "libraries/keyGenerator/keyGenerator.h"
#include "libraries/signer/signer.h"
#include "libraries/math/math.h"
#include "libraries/verifier/verifier.h"

void validationTest(std::string message, uint64_t n, uint64_t e, uint64_t d);

int main()
{
    // Generamos las llaves primero
    KeyPair keys = KeyGenerator::GenerateKeys();

    std::cout << "n: " << keys.n << std::endl;
    std::cout << "e: " << keys.e << std::endl;
    std::cout << "d: " << keys.d << std::endl;

    // Caso 1: Mensaje normal
    std::cout << "\nCASO 1: MENSAJE NORMAL" << std::endl;
    std::string message = "Mensaje normal";
    validationTest(message, keys.n, keys.e, keys.d);

    // Caso 2: Mensaje vacío
    std::cout << "\nCASO 2: MENSAJE VACIO" << std::endl;
    validationTest("", keys.n, keys.e, keys.d);

    // Caso 3: Mensaje alterado después de firmar
    // Firmamos el mensaje original pero verificamos con uno distinto
    std::cout << "\nCASO 3: MENSAJE ALTERADO DESPUES DE FIRMAR" << std::endl;
    Signer signer;
    Verifier verifier;
    uint64_t firma_original = signer.sign(message, keys.d, keys.n);
    bool alterado_valido = verifier.verify("Mensaje alterado", firma_original, keys.e, keys.n);
    std::cout << "Mensaje firmado:    " << message << std::endl;
    std::cout << "Mensaje verificado: Mensaje alterado" << std::endl;
    std::cout << "Firma valida: " << alterado_valido << std::endl;

    // Caso 4: Llave pública incorrecta
    std::cout << "\nCASO 4: LLAVE PUBLICA INCORRECTA" << std::endl;
    validationTest(message, keys.n, keys.e + 1, keys.d);

    // Caso 5: Firma inventada que no corresponde al mensaje
    std::cout << "\nCASO 5: FIRMA INVENTADA" << std::endl;
    uint64_t firma_falsa = 123456789;
    bool falsa_valida = verifier.verify(message, firma_falsa, keys.e, keys.n);
    std::cout << "Mensaje: " << message << std::endl;
    std::cout << "Firma inventada: " << firma_falsa << std::endl;
    std::cout << "Firma valida: " << falsa_valida << std::endl;

    // Caso 6: Entrada mal formada, n=0
    std::cout << "\nCASO 6: ENTRADA MAL FORMADA (n=0)" << std::endl;
    validationTest(message, 0, keys.e, keys.d);

    return 0;
}

void validationTest(std::string message, uint64_t n, uint64_t e, uint64_t d)
{
    // Validamos que n, e y d sean válidos antes de operar
    if (n < 2 || e == 0 || d == 0 || e >= n || d >= n) {
        std::cout << "Error: Entrada no valida." << std::endl;
        return;
    }

    Signer signer;
    Verifier verifier;

    uint64_t signature = signer.sign(message, d, n);
    bool is_valid = verifier.verify(message, signature, e, n);

    std::cout << "Mensaje: \"" << message << "\"" << std::endl;
    std::cout << "Firma: " << signature << std::endl;
    std::cout << "Firma valida: " << is_valid << std::endl;
}
