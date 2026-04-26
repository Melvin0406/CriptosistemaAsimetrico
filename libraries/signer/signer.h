#ifndef SIGNER_H
#define SIGNER_H

#include <iostream>
#include <cstdint>
#include <string>
#include "chemash.h"
#include "math.h"

class Signer
{
    private:
    Chemash chehash_generator;
    Math math_helper;

    public:
    Signer();
    ~Signer();

    uint64_t sign(std::string message, uint64_t d, uint64_t n);
};

#endif