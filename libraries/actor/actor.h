#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include "libraries/keyGenerator/keyGenerator.h"
#include "libraries/chemash/chemash.h"
#include "libraries/math/math.h"

struct PublicKeyPair {
    uint64_t n;
    uint64_t e;
};

class Actor
{
    std::string name;
    KeyPair keys;

    Math math_helper;
    Chemash chehash_generator;

    uint64_t generateSessionKey() const;

public:
    Actor(std::string name);
    virtual ~Actor();

    PublicKeyPair getPublicKey() const;
    std::string getName() const;

    void generateMessage(std::string message, std::string receiverName, PublicKeyPair receiverPublicKey);
    void readMessage();

};

#endif