#include "actor.h"
#include <fstream>
#include <random>
#include <cstdint>
#include <algorithm>
#include "libraries/json.hpp"
#include "libraries/signer/signer.h"
#include "libraries/verifier/verifier.h"

Actor::Actor(std::string name) : name(name)
{
    // Generate keys on startup
    keys = KeyGenerator::GenerateKeys();
}

Actor::~Actor() {}

PublicKeyPair Actor::getPublicKey() const
{
    return {keys.n, keys.e};
}

std::string Actor::getName() const
{
    return name;
}

uint64_t Actor::generateSessionKey() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());

    // Establish min and max numbers
    uint64_t min = 1000000000ULL;
    uint64_t max = (9999999999ULL < keys.n - 1) ? 9999999999ULL : keys.n - 1;
    
    // Generate a random 10-digit number
    std::uniform_int_distribution<uint64_t> dist(min, max);
    
    return dist(gen);
}

void Actor::generateMessage(std::string message, std::string receiverName, PublicKeyPair receiverPublicKey)
{
    // Convert message to number to use with ModExp
    uint64_t messageValue = 0;
    for (char c : message) {
        messageValue = messageValue * 256 + (uint64_t)c;
    }

    // Generate hash of the message using Chemash
    chehash_generator.GenerateHash(std::to_string(messageValue));
    uint64_t hash = chehash_generator.Generated_hash();

    hash = hash % keys.n; // Ensure hash is within mod n

    // Generate session key
    uint64_t sessionKey = generateSessionKey();

    // Encrypt the message with XOR (replacing AES), using the session key
    uint64_t encrypted_message = messageValue ^ sessionKey;

    // Encrypt the session key
    uint64_t encrypted_session_key = math_helper.ModExp(sessionKey, receiverPublicKey.e, receiverPublicKey.n);

    // Sign the hash with RSA
    uint64_t signature = math_helper.ModExp(hash, keys.d, keys.n);

    // Generate JSON message file
    nlohmann::json package;

    package["sender"] = name;
    package["receiver"] = receiverName;
    package["encrypted_message"] = encrypted_message;
    package["encrypted_session_key"] = encrypted_session_key;
    package["signature"] = signature;
    package["hash_algorithm"] = "Chemash";
    package["sender_public_key"] = {
        {"e", keys.e},
        {"n", keys.n}
    };

    std::ofstream file("message.json");
    file << package.dump(4);
    file.close();
}

void Actor::readMessage()
{
    // Open and parse the message file
    std::ifstream file("message.json");
    nlohmann::json package;
    file >> package;
    file.close();

    // Access member fields
    std::string sender = package["sender"];
    std::string receiver = package["receiver"];

    // Retrieve session key
    uint64_t encrypted_session_key = package["encrypted_session_key"];
    uint64_t decrypted_session_key = math_helper.ModExp(encrypted_session_key, keys.d, keys.n);

    // Decrypt the message
    uint64_t encrypted_message = package["encrypted_message"];
    uint64_t decrypted_message = encrypted_message ^ decrypted_session_key;

    // Decode the message
    std::string decoded = "";
    uint64_t temp = decrypted_message;
    while (temp > 0) {
        decoded = (char)(temp % 256) + decoded;
        temp /= 256;
    }

    // Verify signature
    uint64_t signature = package["signature"];
    uint64_t sender_e = package["sender_public_key"]["e"];
    uint64_t sender_n = package["sender_public_key"]["n"];
    uint64_t decrypted_signature = math_helper.ModExp(signature, sender_e, sender_n);

    // Validate message
    // Recompute the hash of the decrypted message
    chehash_generator.GenerateHash(std::to_string(decrypted_message));
    uint64_t recomputed_hash = chehash_generator.Generated_hash();
    recomputed_hash = recomputed_hash % sender_n;

    // Identify sender and receiver
    std::cout << "Sender: " << sender << std::endl;
    std::cout << "Receiver: " << receiver << std::endl;
    std::cout << "Decrypted message value: " << decoded << std::endl;
    std::cout << std::endl;

    // Compare recomputed hash with decrypted signature
    if (decrypted_signature == recomputed_hash)
    {
        std::cout << "[VALIDA] La firma es valida." << std::endl;
        std::cout << "El mensaje no fue alterado y corresponde al emisor indicado." << std::endl;
    }
    else
    {
        std::cout << "[INVALIDA] La firma no es valida." << std::endl;
        std::cout << "El mensaje pudo haber sido alterado o la llave publica no corresponde al emisor." << std::endl;
        std::cout << "  Expected hash: " << recomputed_hash << std::endl;
        std::cout << "  Signature hash: " << decrypted_signature << std::endl;
    }
}