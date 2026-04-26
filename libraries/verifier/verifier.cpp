#include "verifier.h"

Verifier::Verifier(){}
Verifier::~Verifier(){}

bool Verifier::verify(std::string message, uint64_t signature, uint64_t e, uint64_t n)
{
    // Generate hash of the message using Chemash
    Chemash chehash_generator;
    chehash_generator.GenerateHash(message);
    uint64_t hash = chehash_generator.Generated_hash();
    hash = hash % n;

    // Decrypt the signature: decrypted_signature = signature^e mod n
    Math math_helper;
    uint64_t decrypted_signature = math_helper.ModExp(signature, e, n);

    // Compare the decrypted signature with the original hash, returning a bool
    return decrypted_signature == hash;
}