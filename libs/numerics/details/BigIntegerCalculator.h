//
// Created by ChouUn on 2019/6/18.
//

#ifndef UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_H
#define UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_H

#include <vector>

#include <cul/std>

namespace cul {
    namespace BigIntegerCalculator {
        // typedef
        typedef std::vector<u32> container;

        // static
        static const i32 MultiplyThreshold = 32;
        static const i32 AllocationThreshold = 256;

        // public
        static container Add(const container &left, u32 right);

        static container Add(const container &left, const container &right);

        static container Subtract(const container &left, u32 right);

        static container Subtract(const container &left, const container &right);

        static container Multiply(const container &left, u32 right);

        static container Multiply(const container &left, const container &right);

        static container Divide(const container &left, u32 right);

        static container Divide(const container &left, const container &right);

        static u32 Remainder(const container &left, u32 right);

        static container Remainder(const container &left, const container &right);

        // private
        static void Add(const u32 *left, i32 leftLength,
                        const u32 *right, i32 rightLength,
                        u32 *bits, i32 bitsLength);

        static void AddSelf(u32 *left, i32 leftLength,
                            const u32 *right, i32 rightLength);

        static void Subtract(const u32 *left, i32 leftLength,
                             const u32 *right, i32 rightLength,
                             u32 *bits, i32 bitsLength);

        static i32 Compare(const container &left, const container &right);

        static i32 Compare(const u32 *left, i32 leftLength,
                           const u32 *right, i32 rightLength);

        static void Multiply(const u32 *left, i32 leftLength,
                             const u32 *right, i32 rightLength,
                             u32 *bits, i32 bitsLength);

        static void SubtractCore(const u32 *left, i32 leftLength,
                                 const u32 *right, i32 rightLength,
                                 u32 *core, i32 coreLength);

        static void Divide(u32 *left, i32 leftLength,
                           const u32 *right, i32 rightLength,
                           u32 *bits, i32 bitsLength);

        static u32 AddDivisor(u32 *left, i32 leftLength,
                              const u32 *right, i32 rightLength);

        static u32 SubtractDivisor(u32 *left, i32 leftLength,
                                   const u32 *right, i32 rightLength,
                                   u64 q);

        static bool DivideGuessTooBig(u64 q, u64 valHi, u32 valLo,
                                      u32 divHi, u32 divLo);
    }; // namespace BigIntegerCalculator
} // namespace cul

#endif //UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_H
