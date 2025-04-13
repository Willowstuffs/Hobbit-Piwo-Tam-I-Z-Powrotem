#include <iostream>
#include "maxflow.h"

int main(){
    int V; // liczba wierzcholkow
    std::cout << "Podaj liczbe wierzcholkow: ";
    std::cin >> V;
    Graf graf(V); // tworzymy graf o zadanej liczbie wierzcholkow

    std::cout << "Podaj krawedzie w formacie: u v przepustowosc (0 0 0 konczy wczytywanie):\n";
    while(true) {
        int u, v, przepustowosc;
        std::cin >> u >> v >> przepustowosc;
        if (u == 0 && v == 0 && przepustowosc == 0) {
            break; // konczymy wczytywanie
        }
        graf.dodajKrawedz(u, v, przepustowosc); // dodajemy krawedz do grafu
    }

    std::cout << "Maksymalny przeplyw: " << graf.fordFulkerson(0, V - 1) << std::endl; // zrodlo to 0, ujscie to V-1
    std::cout << "Wykonano." << std::endl; // informacja o zakonczeniu

    return 0;
}