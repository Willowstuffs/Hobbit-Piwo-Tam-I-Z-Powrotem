#include <queue> // do BFS
#include <vector> // do grafu
#include <algorithm> // do min
#include <stdexcept> // do wyjatkow
#include "maxflow.h" 

Graf::Graf(int il_wierzcholkow) : V(il_wierzcholkow) {
    przepustowosc.assign(V, std::vector<int>(V, 0));
    sasiedzi.resize(V); 
}

void Graf::dodajKrawedz(int u, int v, int przepustowosc) {
    if( u >= 0 && u < V && v >= 0 && v < V) { // sprawdzamy czy wierzcholki sa w zakresie
        this->przepustowosc[u][v] += przepustowosc; //dodajemy przepustowosc do krawedzi
        sasiedzi[u].push_back(v); // dodajemy krawedz do listy sasiedztwa
        sasiedzi[v].push_back(u); // krawedz rezydualna
    }
    else {
        throw std::out_of_range("Wierzcholek poza zakresem"); // wyrzucamy wyjatek
    }
}

bool Graf::bfs(int zrodlo, int ujscie, std::vector<int>& rodzic) {
    std::fill(rodzic.begin(), rodzic.end(), -1); // inicjalizujemy rodzicow jako nieodwiedzeni
    std::queue<int> kolejka;
    kolejka.push(zrodlo); // dodajemy zrodlo do kolejki
    rodzic[zrodlo] = -2; // oznaczamy zrodlo jako odwiedzone

    while(!kolejka.empty()) { 
        int u = kolejka.front(); 
        kolejka.pop(); 
        for(int v : sasiedzi[u]) {
            if(rodzic[v] == -1 && przepustowosc[u][v] > 0) { // nieodwiedzony i ma krawedz rezydualna
                rodzic[v] = u; 
                if(v == ujscie) {
                    return true; // dotarlismy do ujscia
                }
                kolejka.push(v);
            }
        }
    }
    return false; // nie ma sciezki do ujscia
}

int Graf::fordFulkerson(int zrodlo, int ujscie) {
    int przeplyw = 0; // zmienna do przechowywania przeplywu
    std::vector<int> rodzic(V); // tablica do przechowywania sciezki
    while( bfs(zrodlo, ujscie, rodzic)) {
        int nowy_przeplyw = INT_MAX; 
        for( int v = ujscie; v != zrodlo; v = rodzic[v]) { // cofamy sie od ujscia do zrodla
            int u = rodzic[v];
            nowy_przeplyw = std::min(nowy_przeplyw, przepustowosc[u][v]);
        }
        for( int v = ujscie; v != zrodlo; v = rodzic[v]) {
            int u = rodzic[v];
            przepustowosc[u][v] -= nowy_przeplyw; // zmniejszamy przepustowosc krawedzi
            przepustowosc[v][u] += nowy_przeplyw; // zwiekszamy przepustowosc krawedzi rezydualnej
        }
        przeplyw += nowy_przeplyw; // dodajemy do calkowitego przeplywu
    }
    return przeplyw; // zwracamy calkowity przeplyw
}

// super source -> jeczmien -> browary -> karczmy -> super sink