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

    void sign(std::string message);
};