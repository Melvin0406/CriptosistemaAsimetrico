#include "signer.h"

Signer::Signer(){}

Signer::~Signer(){}

uint64_t Signer::sign(std::string message, uint32_t d, uint64_t n)
{
    // Generate hash of the message using Chemash
    chehash_generator.GenerateHash(message);
    uint64_t hash = chehash_generator.Generated_hash();
    std::cout << "Hash del mensaje: " << hash << std::endl;

    // Sign the hash like RSA: signature = hash^d mod n
    uint64_t signature = 1;
    for (uint32_t i = 0; i < d; i++)
    {
        signature = (signature * hash) % n;
    }

    return signature;
}