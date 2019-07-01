//
// Created by ChouUn on 2019/6/18.
//

#ifndef UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_DIVREM_H
#define UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_DIVREM_H

#include <cul/builtin>
#include <numerics/details/BigIntegerCalculator.h>

namespace cul {
    namespace BigIntegerCalculator {
        // BigIntegerCalculator.DivRem.cs Line 37
        static container Divide(const container &left, u32 right) {
            assert(!left.empty());

            container quotient = container(left.size());

            u64 carry = 0UL;
            for (i32 i = left.size() - 1; i >= 0; i--) {
                u64 value = (carry << 32) | left[i];
                u64 digit = value / right;
                quotient[i] = (u32) digit;
                carry = value - digit * right;
            }

            return quotient;
        }

        // BigIntegerCalculator.DivRem.cs Line 58
        static u32 Remainder(const container &left, u32 right) {
            assert(!left.empty());

            u64 carry = 0UL;
            for (i32 i = left.size() - 1; i >= 0; i--) {
                u64 value = (carry << 32) | left[i];
                carry = value % right;
            }

            return (u32) carry;
        }

        // BigIntegerCalculator.DivRem.cs Line 104
        static container Divide(const container &left, const container &right) {
            assert(!left.empty());
            assert(!right.empty());
            assert(left.size() >= right.size());

            // NOTE: left will get overwritten, we need a local copy
            container localLeft = left;
            container bits = container(left.size() - right.size() + 1);

            Divide(localLeft.data(), localLeft.size(),
                   right.data(), right.size(),
                   bits.data(), bits.size());

            return bits;
        }

        // BigIntegerCalculator.DivRem.cs Line 129
        static container Remainder(const container &left, const container &right) {
            assert(!left.empty());
            assert(!right.empty());
            assert(left.size() >= right.size());

            // NOTE: left will get overwritten, we need a local copy
            container localLeft = left;

            Divide(localLeft.data(), localLeft.size(),
                   right.data(), right.size(),
                   nullptr, 0);

            return localLeft;
        }

        // BigIntegerCalculator.DivRem.cs Line 153
        static void Divide(u32 *left, i32 leftLength,
                           const u32 *right, i32 rightLength,
                           u32 *bits, i32 bitsLength) {
            assert(leftLength >= 1);
            assert(rightLength >= 1);
            assert(leftLength >= rightLength);
            assert(bitsLength == leftLength - rightLength + 1
                   || bitsLength == 0);

            // Executes the "grammar-school" algorithm for computing q = a / b.
            // Before calculating q_i, we get more bits into the highest bit
            // block of the divisor. Thus, guessing digits of the quotient
            // will be more precise. Additionally we'll get r = a % b.

            u32 divHi = right[rightLength - 1];
            u32 divLo = rightLength > 1 ? right[rightLength - 2] : 0;

            // We measure the leading zeros of the divisor
            i32 shift = clz(divHi);
            i32 backShift = 32 - shift;

            // And, we make sure the most significant bit is set
            if (shift > 0) {
                u32 divNx = rightLength > 2 ? right[rightLength - 3] : 0;

                divHi = (divHi << shift) | (divLo >> backShift);
                divLo = (divLo << shift) | (divNx >> backShift);
            }

            // Then, we divide all of the bits as we would do it using
            // pen and paper: guessing the next digit, subtracting, ...
            for (i32 i = leftLength; i >= rightLength; i--) {
                i32 n = i - rightLength;
                u32 t = i < leftLength ? left[i] : 0;

                u64 valHi = ((u64) t << 32) | left[i - 1];
                u32 valLo = i > 1 ? left[i - 2] : 0;

                // We shifted the divisor, we shift the dividend too
                if (shift > 0) {
                    u32 valNx = i > 2 ? left[i - 3] : 0;

                    valHi = (valHi << shift) | (valLo >> backShift);
                    valLo = (valLo << shift) | (valNx >> backShift);
                }

                // First guess for the current digit of the quotient,
                // which naturally must have only 32 bits...
                u64 digit = valHi / divHi;
                if (digit > 0xFFFFFFFF) { digit = 0xFFFFFFFF; }

                // Our first guess may be a little bit to big
                while (DivideGuessTooBig(digit, valHi, valLo, divHi, divLo))
                    --digit;

                if (digit > 0) {
                    // Now it's time to subtract our current quotient
                    u32 carry = SubtractDivisor(left + n, leftLength - n,
                                                right, rightLength, digit);
                    if (carry != t) {
                        assert(carry == t + 1);

                        // Our guess was still exactly one too high
                        carry = AddDivisor(left + n, leftLength - n,
                                           right, rightLength);
                        --digit;

                        assert(carry == 1);
                    }
                }

                // We have the digit!
                if (bitsLength != 0) { bits[n] = (u32) digit; }
                if (i < leftLength) { left[i] = 0; }
            }
        }

        // BigIntegerCalculator.DivRem.cs Line 239
        static u32 AddDivisor(u32 *left, i32 leftLength,
                              const u32 *right, i32 rightLength) {
            assert(leftLength >= 0);
            assert(rightLength >= 0);
            assert(leftLength >= rightLength);

            // Repairs the dividend, if the last subtract was too much

            u64 carry = 0UL;

            for (i32 i = 0; i < rightLength; i++) {
                u64 digit = (left[i] + carry) + right[i];
                left[i] = (u32) digit;
                carry = digit >> 32;
            }

            return (u32) carry;
        }

        // BigIntegerCalculator.DivRem.cs Line 260
        static u32 SubtractDivisor(u32 *left, i32 leftLength,
                                   const u32 *right, i32 rightLength,
                                   u64 q) {
            assert(leftLength >= 0);
            assert(rightLength >= 0);
            assert(leftLength >= rightLength);
            assert(q <= 0xFFFFFFFF);

            // Combines a subtract and a multiply operation, which is naturally
            // more efficient than multiplying and then subtracting...

            u64 carry = 0UL;

            for (i32 i = 0; i < rightLength; i++) {
                carry += right[i] * q;
                u32 digit = (u32) carry;
                carry = carry >> 32;
                if (left[i] < digit) { ++carry; }
                left[i] = left[i] - digit;
            }

            return (u32) carry;
        }

        // BigIntegerCalculator.DivRem.cs Line 287
        static bool DivideGuessTooBig(u64 q, u64 valHi, u32 valLo,
                                      u32 divHi, u32 divLo) {
            assert(q <= 0xFFFFFFFF);

            // We multiply the two most significant limbs of the divisor
            // with the current guess for the quotient. If those are bigger
            // than the three most significant limbs of the current dividend
            // we return true, which means the current guess is still too big.

            u64 chkHi = divHi * q;
            u64 chkLo = divLo * q;

            chkHi = chkHi + (chkLo >> 32);
            chkLo = chkLo & 0xFFFFFFFF;

            if (chkHi < valHi) { return false; }
            if (chkHi > valHi) { return true; }

            if (chkLo < valLo) { return false; }
            if (chkLo > valLo) { return true; }

            return false;
        }
    } // namespace BigIntegerCalculator
} // namespace cul}

#endif //UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_DIVREM_H
