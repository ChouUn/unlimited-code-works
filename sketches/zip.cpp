//
// Created by ChouUn on 2019/4/9.
//

#include <iostream>
#include <list>
#include <vector>
#include <util/zip>

#include <typeinfo>

int main() {
    std::vector<int> one{{1, 11}};
    auto two = [] { return std::vector<short>{2, 22}; };
    const std::list<float> three{{3.3, 33.33}};
    std::vector<std::string> four{"4", "44"};
    std::vector<short> five{5, 55};
    for (auto a : zip(one, two(), three, four, five)) {
//        std::printf("%d %d %f %d\n", std::get<0>(a), std::get<1>(a), std::get<2>(a), std::get<3>(a));
        std::cout << typeid(std::get<0>(a)).name() << " "
                  << typeid(std::get<1>(a)).name() << " "
                  << sizeof(std::get<1>(a)) << std::endl;
        std::cout << std::get<0>(a) << " " << std::get<1>(a) << " "
                  << std::get<2>(a) << " " << std::get<3>(a) << " "
                  << std::get<4>(a) << std::endl;
    }

    return 0;
}
