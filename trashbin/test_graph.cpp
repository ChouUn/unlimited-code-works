//
// Created by ChouUn on 2019-04-04.
//

#include <iostream>
#include <list>
#include <ds/graph>
#include <ds/rich_graph>
#include <graph/scc>

int main() {
    cul::rich_graph<> g;
    g.build(5);
    g.add_edge(1, 0);
    g.add_edge(0, 2);
    g.add_edge(2, 1);
    g.add_edge(0, 3);
    g.add_edge(3, 4);

    for (size_t i = 0; i < 5; ++i) {
        for (auto j : g.edges(i)) {
            std::cout << i << " " << j.to << std::endl;
        }
    }

    cul::Kosaraju kos;
    kos.solve(g);

    std::list<int> l;

    return 0;
}
