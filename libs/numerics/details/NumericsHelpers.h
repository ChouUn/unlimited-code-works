//
// Created by ChouUn on 2019/6/18.
//

#ifndef UNLIMITED_CODE_WORKS_NUMERICSHELPERS_H
#define UNLIMITED_CODE_WORKS_NUMERICSHELPERS_H

#include <cul/std>

namespace cul {
    namespace NumericsHelpers {
        static const i32 kcbitUint = 32;

        static u32 Abs(i32 a) {
            u32 mask = (u32) (a >> 31);
            return ((u32) a ^ mask) - mask;
        }

        static u64 MakeUlong(u32 uHi, u32 uLo) {
            return ((u64) uHi << kcbitUint) | uLo;
        }

        static u32 CombineHash(u32 u1, u32 u2) {
            return ((u1 << 7) | (u1 >> 25)) ^ u2;
        }

        static i32 CombineHash(i32 n1, i32 n2) {
            return (i32) CombineHash((u32) n1, (u32) n2);
        }
    } // namespace NumericsHelpers
} // namespace cul

#endif //UNLIMITED_CODE_WORKS_NUMERICSHELPERS_H
