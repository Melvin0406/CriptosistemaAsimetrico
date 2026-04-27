#include "signer.h"

Signer::Signer(){}

Signer::~Signer(){}

uint64_t Signer::sign(std::string message, uint64_t d, uint64_t n)
{
    // Generate hash of the message using Chemash
    chehash_generator.GenerateHash(message);
    uint64_t hash = chehash_generator.Generated_hash();
    hash = hash % n; // Ensure hash is within mod n

    // Sign the hash like RSA: signature = hash^d mod n
    uint64_t signature = math_helper.ModExp(hash, d, n); // We use modular exponentiation for efficiency

    return signature;
}