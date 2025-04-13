#ifndef MAXFLOW_H
#define MAXFLOW_H

#include <vector>

class Graf{
    public:
    Graf(int il_wierzcholkow);

    void dodajKrawedz(int u, int v, int przepustowosc);
    int fordFulkerson(int zrodlo, int ujscie);

    private:
    bool bfs(int zrodlo, int ujscie, std::vector<int>& rodzic);
    int V;
    std::vector<std::vector<int>> przepustowosc;
    std::vector<std::vector<int>> sasiedzi;
};


#endif// MAXFLOW_H