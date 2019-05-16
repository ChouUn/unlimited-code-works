//
// Created by ChouUn on 2019-04-04.
//

#include <iostream>
#include <list>
#include <cul/stream>
#include <ds/graph>
#include <graph/scc>

int main() {
    /**
     * 2 <----
     * |     |
     * v     |
     * 1 --> 0 --> 3 --> 4
     */

    cul::graph<> G;
    G.build(5);
    G.add_edge(1, 0);
    G.add_edge(0, 2);
    G.add_edge(2, 1);
    G.add_edge(0, 3);
    G.add_edge(3, 4);

    for (size_t i = 0; i < 5; ++i) {
        for (auto j : G.edges(i)) {
            std::cout << i << " " << j << std::endl;
        }
    }

    auto K = cul::make_kosaraju(G);
    for (auto &compo : K.compos) {
        for (auto &elem : compo) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
