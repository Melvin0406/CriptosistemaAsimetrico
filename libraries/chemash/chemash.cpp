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
    
    // Third step - Execute the main hash computation
    ExecuteHashComputation();

    // Fourth step - Calculate final generated hash
    CalculateFinalGeneratedHash();
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

void Chemash::ParsePaddedMessage(const std::vector<unsigned char>& bytes)
{
    // Make sure blocks are cleared
    message_blocks.clear();

    // Calculate number of blocks in padded message
    int num_blocks = bytes.size() / 32;

    // Separate padded message into N blocks of M words each
    for (int block = 0; block < num_blocks; block++) {
        std::vector<uint32_t> words(16);

        int block_offset = block * 32;
        for (int i = 0; i < 16; i++) {
            words[i] = (bytes[block_offset + i * 4]     << 24) |
                       (bytes[block_offset + i * 4 + 1] << 16) |
                       (bytes[block_offset + i * 4 + 2] << 8)  |
                       (bytes[block_offset + i * 4 + 3]);
        }

        message_blocks.push_back(words);
    }
}

void Chemash::ExecuteHashComputation()
{
    // Store number of blocks
    int N = padded_bytes.size() / 32;

    for (int i = 1; i <= N; i++) {
        // Step 1 - Prepare message schedule
        PrepareMessageSchedule(N);

        // Step 2 - Initialize the 8 working variables
        a = hash_values[0];
        b = hash_values[1];
        c = hash_values[2];
        d = hash_values[3];
        e = hash_values[4];
        f = hash_values[5];
        g = hash_values[6];
        h = hash_values[7];

        // Step 3 - Call compression function
        Compress();

        // Step 4 - Update hash values
        hash_values[0] += a;
        hash_values[1] += b;
        hash_values[2] += c;
        hash_values[3] += d;
        hash_values[4] += e;
        hash_values[5] += f;
        hash_values[6] += g;
        hash_values[7] += h;
    }
}

void Chemash::CalculateFinalGeneratedHash()
{
    // Use two of the hash values as indices
    int index1 = hash_values[6] % 8;
    int index2 = hash_values[7] % 8;

    // Make sure they are different
    if (index1 == index2) {
        index2 = (index2 + 1) % 8;
    }

    // Set final hash value
    generated_hash = ((uint64_t)hash_values[index1] << 32) | hash_values[index2];
}

void Chemash::PrepareMessageSchedule(const int& N)
{
    // Copy the 16 words from the current block into the schedule
    for (int i = 0; i < 16; i++) {
        w_message_schedule[i] = message_blocks[N - 1][i];
    }

    // Expand to 64 words
    for (int i = 16; i < 64; i++) {
        uint32_t s0 = RightRotate(w_message_schedule[i - 15], 3)  ^
                      RightRotate(w_message_schedule[i - 15], 13) ^
                      (w_message_schedule[i - 15] >> 11);

        uint32_t s1 = RightRotate(w_message_schedule[i - 2], 23) ^
                      RightRotate(w_message_schedule[i - 2], 7) ^
                      (w_message_schedule[i - 2] >> 15);

        w_message_schedule[i] = w_message_schedule[i - 16] + s0 +
                                w_message_schedule[i - 7] + s1;
    }
}

uint32_t Chemash::RightRotate(uint32_t value, int amount)
{
    return (value >> amount) | (value << (32 - amount));
}

void Chemash::Compress()
{
    for (int t = 0; t < 64; t++)
    {
        uint32_t S1 = RightRotate(e, 23) ^ RightRotate(e, 5) ^ RightRotate(e, 7);
        uint32_t ch = (e & f) ^ (~e & g);
        uint32_t temp1 = h + S1 + ch + round_constants[t] + w_message_schedule[t];

        uint32_t S0 = RightRotate(a, 7) ^ RightRotate(a, 19) ^ RightRotate(a, 3);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
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