#include <iostream>
#include <string>
#include "chemash.h"

class Signer
{
    private:
    Chemash chehash_generator;

    public:
    Signer();
    ~Signer();

    uint64_t sign(std::string message, uint32_t d, uint64_t n);
};