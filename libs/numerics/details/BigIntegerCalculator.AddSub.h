//
// Created by ChouUn on 2019/6/18.
//

#ifndef UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_ADDSUB_H
#define UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_ADDSUB_H

#include <numerics/details/BigIntegerCalculator.h>

namespace cul {
    namespace BigIntegerCalculator {
        static container Add(const container &left, u32 right) {
            assert(!left.empty());

            // Executes the addition for one big and one 32-bit integer.
            // Thus, we've similar code than below, but there is no loop for
            // processing the 32-bit integer, since it's a single element.

            container bits = container(left.size() + 1);

            i64 digit = (i64) left[0] + right;
            bits[0] = (u32) digit;
            i64 carry = digit >> 32;

            for (i32 i = 1; i < left.size(); i++) {
                digit = left[i] + carry;
                bits[i] = (u32) digit;
                carry = digit >> 32;
            }
            bits[left.size()] = (u32) carry;

            return bits;
        }

        static container Add(const container &left, const container &right) {
            assert(!left.empty());
            assert(!right.empty());
            assert(left.size() >= right.size());

            // Switching to unsafe pointers helps sparing
            // some nasty index calculations...

            container bits = container(left.size() + 1);

            Add(left.data(), left.size(),
                right.data(), right.size(),
                bits.data(), bits.size());

            return bits;
        }

        static void Add(const u32 *left, i32 leftLength,
                        const u32 *right, i32 rightLength,
                        u32 *bits, i32 bitsLength) {
            assert(leftLength >= 0);
            assert(rightLength >= 0);
            assert(leftLength >= rightLength);
            assert(bitsLength == leftLength + 1);

            // Executes the "grammar-school" algorithm for computing z = a + b.
            // While calculating z_i = a_i + b_i we take care of overflow:
            // Since a_i + b_i + c <= 2(2^32 - 1) + 1 = 2^33 - 1, our carry c
            // has always the _value 1 or 0; hence, we're safe here.

            i32 i = 0;
            i64 carry = 0L;

            for (; i < rightLength; i++) {
                i64 digit = (left[i] + carry) + right[i];
                bits[i] = (u32) digit;
                carry = digit >> 32;
            }
            for (; i < leftLength; i++) {
                i64 digit = left[i] + carry;
                bits[i] = (u32) digit;
                carry = digit >> 32;
            }
            bits[i] = (u32) carry;
        }

        static void AddSelf(u32 *left, i32 leftLength,
                            const u32 *right, i32 rightLength) {
            assert(leftLength >= 0);
            assert(rightLength >= 0);
            assert(leftLength >= rightLength);

            // Executes the "grammar-school" algorithm for computing z = a + b.
            // Same as above, but we're writing the result directly to a and
            // stop execution, if we're out of b and c is already 0.

            i32 i = 0;
            i64 carry = 0L;

            for (; i < rightLength; i++) {
                i64 digit = (left[i] + carry) + right[i];
                left[i] = (u32) digit;
                carry = digit >> 32;
            }
            for (; carry != 0 && i < leftLength; i++) {
                i64 digit = left[i] + carry;
                left[i] = (u32) digit;
                carry = digit >> 32;
            }

            assert(carry == 0);
        }

        static container Subtract(const container &left, u32 right) {
            assert(!left.empty());
            assert(left[0] >= right || left.size() >= 2);

            // Executes the subtraction for one big and one 32-bit integer.
            // Thus, we've similar code than below, but there is no loop for
            // processing the 32-bit integer, since it's a single element.

            container bits = container(left.size());

            i64 digit = (i64) left[0] - right;
            bits[0] = (u32) digit;
            i64 carry = digit >> 32;

            for (i32 i = 1; i < left.size(); i++) {
                digit = left[i] + carry;
                bits[i] = (u32) digit;
                carry = digit >> 32;
            }

            return bits;
        }

        static container Subtract(const container &left, const container &right) {
            assert(!left.empty());
            assert(!right.empty());
            assert(left.size() >= right.size());
            assert(Compare(left, right) >= 0);

            // Switching to unsafe pointers helps sparing
            // some nasty index calculations...

            container bits = container(left.size());

            Subtract(left.data(), left.size(),
                     right.data(), right.size(),
                     bits.data(), bits.size());

            return bits;
        }

        static void Subtract(const u32 *left, i32 leftLength,
                             const u32 *right, i32 rightLength,
                             u32 *bits, i32 bitsLength) {
            assert(leftLength >= 0);
            assert(rightLength >= 0);
            assert(leftLength >= rightLength);
            assert(Compare(left, leftLength, right, rightLength) >= 0);
            assert(bitsLength == leftLength);

            // Executes the "grammar-school" algorithm for computing z = a - b.
            // While calculating z_i = a_i - b_i we take care of overflow:
            // Since a_i - b_i doesn't need any additional bit, our carry c
            // has always the _value -1 or 0; hence, we're safe here.

            i32 i = 0;
            i64 carry = 0L;

            for (; i < rightLength; i++) {
                i64 digit = (left[i] + carry) - right[i];
                bits[i] = (u32) digit;
                carry = digit >> 32;
            }
            for (; i < leftLength; i++) {
                i64 digit = left[i] + carry;
                bits[i] = (u32) digit;
                carry = digit >> 32;
            }

            assert(carry == 0);
        }

        static i32 Compare(const container &left, const container &right) {
            assert(!left.empty());
            assert(!right.empty());

            if (left.size() < right.size()) { return -1; }
            if (left.size() > right.size()) { return 1; }

            for (i32 i = left.size() - 1; i >= 0; i--) {
                if (left[i] < right[i]) { return -1; }
                if (left[i] > right[i]) { return 1; }
            }

            return 0;
        }

        static i32 Compare(const u32 *left, i32 leftLength,
                           const u32 *right, i32 rightLength) {
            assert(leftLength >= 0);
            assert(rightLength >= 0);

            if (leftLength < rightLength) { return -1; }
            if (leftLength > rightLength) { return 1; }

            for (i32 i = leftLength - 1; i >= 0; i--) {
                if (left[i] < right[i]) { return -1; }
                if (left[i] > right[i]) { return 1; }
            }

            return 0;
        }
    } // namespace BigIntegerCalculator
} // namespace cul

#endif //UNLIMITED_CODE_WORKS_BIGINTEGERCALCULATOR_ADDSUB_H
