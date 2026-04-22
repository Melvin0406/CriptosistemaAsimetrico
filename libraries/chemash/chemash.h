#ifndef CHEMASH_H
#define CHEMASH_H

#include <cstdint>
#include <string>
#include "vector"

class Chemash
{
    unsigned long long generated_hash;

    std::vector<unsigned char> padded_bytes;
    std::vector<std::vector<uint32_t>> message_blocks;
    uint32_t w_message_schedule[64];
    uint32_t a, b, c, d, e, f, g, h;

    uint32_t hash_values[8];
    uint32_t round_constants[64];

    const int PADDING_LENGTH = 512;
    const int chemo_numbers[8] = {7, 420, 616, 67, 911, 69, 2, 11};
    const int chemo_numbers_64[64] = {
        83, 89, 181, 281, 283, 383, 389, 487,
        587, 683, 787, 809, 811, 821, 823, 827,
        829, 839, 853, 857, 859, 863, 877, 881,
        883, 887, 983, 1087, 1181, 1187, 1283, 1289,
        1381, 1481, 1483, 1487, 1489, 1583, 1783, 1787,
        1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867,
        1871, 1873, 1877, 1879, 1889, 1987, 2081, 2083,
        2087, 2089, 2281, 2287, 2381, 2383, 2389, 2683
    };

public:
    Chemash();
    virtual ~Chemash();

    void CalculateInitialHashValues();
    void CalculateRoundConstants();

    void GenerateHash(const std::string& input_string);
    void PadOriginalMessage(const std::string& original_message);
    void ParsePaddedMessage(const std::vector<unsigned char>& padded_bytes);
    void ExecuteHashComputation();
    void CalculateFinalGeneratedHash();

    void PrepareMessageSchedule(const int& N);
    uint32_t RightRotate(uint32_t value, int amount);

    void Compress();

    unsigned long long Generated_hash() const;
    unsigned long long& Generated_hash();

};

#endif