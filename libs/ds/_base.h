//
// Created by ChouUn on 2019-07-06.
//

#ifndef UNLIMITED_CODE_WORKS__BASE
#define UNLIMITED_CODE_WORKS__BASE

#include <cul/std>

const u32 null_index = std::numeric_limits<u32>::max();

namespace cul {
    enum NodeRelation : u32 {
        L = 0u,
        R = 1u,
    }; // enum NodeRelation
} // namespace cul

#endif // UNLIMITED_CODE_WORKS__BASE
