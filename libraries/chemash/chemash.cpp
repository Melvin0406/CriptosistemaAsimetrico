#include "chemash.h"
#include <cmath>

Chemash::Chemash()
{
    generated_hash = 0;

    // Calculate initial hash values and round constants
    CalculateInitialHashValues();
    CalculateRoundConstants();
}

Chemash::~Chemash() {}

void Chemash::CalculateInitialHashValues()
{
    // For each chose number, calculate the square root, and save the first 32 bits of its decimal part representation in binary
    for (int i = 0; i < 8; i++) {
        double x = sqrt(chemo_numbers[i]);
        hash_values[i] = (uint32_t)((x - floor(x)) * pow(2, 32));
    }
}

void Chemash::CalculateRoundConstants()
{
    // For each of the first 64 prime numbers containing an 8, calculate the cubic root, and save the first 32 bits of its decimal part representation in binary
    for (int i = 0; i < 64; i++) {
        double x = cbrt(chemo_numbers_64[i]);
        round_constants[i] = (uint32_t)((x - floor(x)) * pow(2, 32));
    }
}

void Chemash::GenerateHash(const std::string& input_string)
{
    // First step - Round up size to nearest 'PADDING_LENGTH' bit string
    PadOriginalMessage(input_string);

    // Second step - Parse padded message into 'PADDING_LENGTH' blocks of 32 bit 'words'
    ParsePaddedMessage(padded_bytes);
    

}

void Chemash::PadOriginalMessage(const std::string& original_message)
{
    // Convert string into a vector of bytes
    padded_bytes.assign(original_message.begin(), original_message.end());

    // Append a '1' bit
    padded_bytes.push_back(0x80);

    // Append '0' bits until we have 64 bits before nearest 'PADDING_LENGTH' bit string
    int padding_bytes = (PADDING_LENGTH - 64) / 8;
    while (padded_bytes.size() % 32 != padding_bytes) {
        padded_bytes.push_back(0x00);
    }

    // Calculate original message length and append it in binary representation
    uint64_t original_length = original_message.size() * 8;
    for (int i = 7; i >= 0; i--) {
        padded_bytes.push_back((original_length >> (i * 8)) & 0xFF);
    }
}

void Chemash::ParsePaddedMessage(const std::vector<unsigned char>& padded_bytes)
{
    // Calculate number of blocks in padded message
    int num_blocks = padded_bytes.size() / 32;

    // Separate padded message into N blocks of M words each
    for (int block = 0; block < num_blocks; block++) {
        std::vector<uint32_t> words(16);

        int block_offset = block * 32;
        for (int i = 0; i < 16; i++) {
            words[i] = (padded_bytes[block_offset + i * 4]     << 24) |
                       (padded_bytes[block_offset + i * 4 + 1] << 16) |
                       (padded_bytes[block_offset + i * 4 + 2] << 8)  |
                       (padded_bytes[block_offset + i * 4 + 3]);
        }

        message_blocks.push_back(words);
    }
}

unsigned long long Chemash::Generated_hash() const
{
    return generated_hash;
}

unsigned long long& Chemash::Generated_hash()
{
    return generated_hash;
}