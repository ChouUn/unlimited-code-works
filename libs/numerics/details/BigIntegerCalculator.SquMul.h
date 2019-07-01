//
// Created by ChouUn on 2019/6/18.
//

#ifndef UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_SQUMUL_H
#define UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_SQUMUL_H

#include <numerics/details/BigIntegerCalculator.h>

namespace cul {
    namespace BigIntegerCalculator {
        container Multiply(const container &left, u32 right) {
            assert(!left.empty());

            // Executes the multiplication for one big and one 32-bit integer.
            // Since every step holds the already slightly familiar equation
            // a_i * b + c <= 2^32 - 1 + (2^32 - 1)^2 < 2^64 - 1,
            // we are safe regarding to overflows.
            i32 i = 0;
            u64 carry = 0ULL;
            container bits = container(left.size() + 1);

            for (; i < left.size(); i++) {
                u64 digits = (u64) left[i] * right + carry;
                bits[i] = (u32) digits;
                carry = digits >> 32;
            }
            bits[i] = (u32) carry;

            return bits;
        }

        container Multiply(const container &left, const container &right) {
            assert(!left.empty());
            assert(!right.empty());
            assert(left.size() >= right.size());

            // Switching to unsafe pointers helps sparing
            // some nasty index calculations...

            container bits = container(left.size() + right.size());

            Multiply(left.data(), left.size(),
                     right.data(), right.size(),
                     bits.data(), bits.size());

            return bits;
        }

        void Multiply(const u32 *left, i32 leftLength,
                      const u32 *right, i32 rightLength,
                      u32 *bits, i32 bitsLength) {
            assert(leftLength >= 0);
            assert(rightLength >= 0);
            assert(leftLength >= rightLength);
            assert(bitsLength == leftLength + rightLength);

            // Executes different algorithms for computing z = a * b
            // based on the actual length of b. If b is "small" enough
            // we stick to the classic "grammar-school" method; for the
            // rest we switch to implementations with less complexity
            // albeit more overhead (which needs to pay off!).

            // NOTE: useful thresholds needs some "empirical" testing,
            // which are smaller in DEBUG mode for testing purpose.

            if (rightLength < MultiplyThreshold) {
                // Multiplies the bits using the "grammar-school" method.
                // Envisioning the "rhombus" of a pen-and-paper calculation
                // should help getting the idea of these two loops...
                // The inner multiplication operations are safe, because
                // z_i+j + a_j * b_i + c <= 2(2^32 - 1) + (2^32 - 1)^2 =
                // = 2^64 - 1 (which perfectly matches with u64!).

                for (i32 i = 0; i < rightLength; i++) {
                    u64 carry = 0UL;
                    for (i32 j = 0; j < leftLength; j++) {
                        u64 digits = bits[i + j] + carry + (u64) left[j] * right[i];
                        bits[i + j] = (u32) digits;
                        carry = digits >> 32;
                    }
                    bits[i + leftLength] = (u32) carry;
                }
            } else {
                // Based on the Toom-Cook multiplication we split left/right
                // into two smaller values, doing recursive multiplication.
                // The special form of this multiplication, where we
                // split both operands into two operands, is also known
                // as the Karatsuba algorithm...

                // https://en.wikipedia.org/wiki/Toom-Cook_multiplication
                // https://en.wikipedia.org/wiki/Karatsuba_algorithm

                // Say we want to compute z = a * b ...

                // ... we need to determine our new length (just the half)
                i32 n = rightLength >> 1;
                i32 n2 = n << 1;

                // ... split left like a = (a_1 << n) + a_0
                const u32 *leftLow = left;
                i32 leftLowLength = n;
                const u32 *leftHigh = left + n;
                i32 leftHighLength = leftLength - n;

                // ... split right like b = (b_1 << n) + b_0
                const u32 *rightLow = right;
                i32 rightLowLength = n;
                const u32 *rightHigh = right + n;
                i32 rightHighLength = rightLength - n;

                // ... prepare our result array (to reuse its memory)
                u32 *bitsLow = bits;
                i32 bitsLowLength = n2;
                u32 *bitsHigh = bits + n2;
                i32 bitsHighLength = bitsLength - n2;

                // ... compute z_0 = a_0 * b_0 (multiply again)
                Multiply(leftLow, leftLowLength,
                         rightLow, rightLowLength,
                         bitsLow, bitsLowLength);

                // ... compute z_2 = a_1 * b_1 (multiply again)
                Multiply(leftHigh, leftHighLength,
                         rightHigh, rightHighLength,
                         bitsHigh, bitsHighLength);

                i32 leftFoldLength = leftHighLength + 1;
                i32 rightFoldLength = rightHighLength + 1;
                i32 coreLength = leftFoldLength + rightFoldLength;

                if (coreLength < AllocationThreshold) {
                    u32 leftFold[leftFoldLength];
                    std::fill_n(leftFold, leftFoldLength, u32());
                    u32 rightFold[rightFoldLength];
                    std::fill_n(rightFold, rightFoldLength, u32());
                    u32 core[coreLength];
                    std::fill_n(core, coreLength, u32());

                    // ... compute z_a = a_1 + a_0 (call it fold...)
                    Add(leftHigh, leftHighLength,
                        leftLow, leftLowLength,
                        leftFold, leftFoldLength);

                    // ... compute z_b = b_1 + b_0 (call it fold...)
                    Add(rightHigh, rightHighLength,
                        rightLow, rightLowLength,
                        rightFold, rightFoldLength);

                    // ... compute z_1 = z_a * z_b - z_0 - z_2
                    Multiply(leftFold, leftFoldLength,
                             rightFold, rightFoldLength,
                             core, coreLength);
                    SubtractCore(bitsHigh, bitsHighLength,
                                 bitsLow, bitsLowLength,
                                 core, coreLength);

                    // ... and finally merge the result! :-)
                    AddSelf(bits + n, bitsLength - n, core, coreLength);
                } else {
                    u32 *leftFold = new u32[leftFoldLength];
                    u32 *rightFold = new u32[rightFoldLength];
                    u32 *core = new u32[coreLength];
                    {
                        // ... compute z_a = a_1 + a_0 (call it fold...)
                        Add(leftHigh, leftHighLength,
                            leftLow, leftLowLength,
                            leftFold, leftFoldLength);

                        // ... compute z_b = b_1 + b_0 (call it fold...)
                        Add(rightHigh, rightHighLength,
                            rightLow, rightLowLength,
                            rightFold, rightFoldLength);

                        // ... compute z_1 = z_a * z_b - z_0 - z_2
                        Multiply(leftFold, leftFoldLength,
                                 rightFold, rightFoldLength,
                                 core, coreLength);
                        SubtractCore(bitsHigh, bitsHighLength,
                                     bitsLow, bitsLowLength,
                                     core, coreLength);

                        // ... and finally merge the result! :-)
                        AddSelf(bits + n, bitsLength - n, core, coreLength);
                    }
                }
            }
        }

        void SubtractCore(const u32 *left, i32 leftLength,
                          const u32 *right, i32 rightLength,
                          u32 *core, i32 coreLength) {
            assert(leftLength >= 0);
            assert(rightLength >= 0);
            assert(coreLength >= 0);
            assert(leftLength >= rightLength);
            assert(coreLength >= leftLength);

            // Executes a special subtraction algorithm for the multiplication,
            // which needs to subtract two different values from a core _value,
            // while core is always bigger than the sum of these values.

            // NOTE: we could do an ordinary subtraction of course, but we spare
            // one "run", if we do this computation within a single one...

            i32 i = 0;
            i64 carry = 0L;

            for (; i < rightLength; i++) {
                i64 digit = (core[i] + carry) - left[i] - right[i];
                core[i] = (u32) digit;
                carry = digit >> 32;
            }
            for (; i < leftLength; i++) {
                i64 digit = (core[i] + carry) - left[i];
                core[i] = (u32) digit;
                carry = digit >> 32;
            }
            for (; carry != 0 && i < coreLength; i++) {
                i64 digit = core[i] + carry;
                core[i] = (u32) digit;
                carry = digit >> 32;
            }
        }
    } // namespace BigIntegerCalculator
} // namespace cul

#endif //UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_SQUMUL_H
