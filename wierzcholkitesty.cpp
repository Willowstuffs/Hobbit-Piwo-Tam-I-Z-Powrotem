#include <iostream>
#include "maxflow.h"

enum class TypWierzcholka { 
    POLE, BROWAR, KARCZMA // typy wierzcholkow
};

struct Wierzcholek { // struktura do przechowywania wierzcholkow
    int id; // nr wierzcholka
    TypWierzcholka typ;
    int zasob; //ile jeczmienia/piwa produkuje/potrzebuje
};

// Funkcja do budowania grafu z danych
void budujGraf(Graf& graf, int sZrodlo, int sUjscie, 
    const std::vector<Wierzcholek>& pola, 
    const std::vector<Wierzcholek>& browary, 
    const std::vector<Wierzcholek>& karczmy, 
    const std::vector<std::tuple<int, int, int>>& drogi) {

    for (const auto& pole : pola) {
        graf.dodajKrawedz(sZrodlo, pole.id, pole.zasob); // dodajemy krawedz z zrodla do pola z jeczmieniem
    }

    for (const auto& karczma : karczmy) {
        graf.dodajKrawedz(karczma.id, sUjscie, karczma.zasob); // dodajemy krawedz z karczmy do ujscia
    }

    for (const auto& [u, v, przepustowosc] : drogi) {
        graf.dodajKrawedz(u, v, przepustowosc); // dodajemy krawedz miedzy pozostalymi elementami
    }
}

int main(){
    
    // 0 = super source, 1 = super sink
    // 2-3 pola, 4-5 browary, 6-7 karczmy

    int V = 8; //liczba wierzcholkow, na razie stala do pierwszego testu
    Graf graf(V);

    // DANE TESTOWE
    std::vector<Wierzcholek> pola = {
        {2, TypWierzcholka::POLE, 10}, // pole 1 o produkcji 10 jednostek jeczmienia
        {3, TypWierzcholka::POLE, 8}   // pole 2 o produkcji 8 jednostek jeczmienia
    };

    std::vector<Wierzcholek> browary = {
        {4, TypWierzcholka::BROWAR, 0}, // browar 1
        {5, TypWierzcholka::BROWAR, 0}  // browar 2
    };

    std::vector<Wierzcholek> karczmy = {
        {6, TypWierzcholka::KARCZMA, 9}, // karczma 1 o zapotrzebowaniu 9 jednostek piwa
        {7, TypWierzcholka::KARCZMA, 16} // karczma 2 o zapotrzebowaniu 16 jednostek piwa
    };

    std::vector<std::tuple<int, int, int>> drogi = {
        {2, 4, 100}, // pole 2 -> browar 4
        {3, 5, 80},   // pole 3 -> browar 5
        {4, 6, 90},   // browar 4 -> karczma 6
        {5, 7, 100}   // browar 5 -> karczma 7
    };

    // budujemy graf
    budujGraf(graf, 0, 1, pola, browary, karczmy, drogi);

    // uruchamiamy algorytm Forda-Fulkersona
    int maksymalnyPrzeplyw = graf.fordFulkerson(0, 1); // zrodlo -> ujscie
    std::cout << "Maksymalny przeplyw: " << maksymalnyPrzeplyw << std::endl; // wyswietlamy wynik
    std::cout << "Wykonano." << std::endl; // informacja o zakonczeniu

    return 0;
}