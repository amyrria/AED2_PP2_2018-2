
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <iostream>
#include<iomanip>

#define inf -1
using namespace std;
template <class T>
class Dijkstra
{ 
    private:
    public:
	void menorCaminho(int graph[V][V], int src){
        	float distancia[];
        	bool visitados[];
		int predecessor[];
		for (int i=1; i<V+1;i++){
			distancia[i] = inf;
			visitados[i] = false;
			predecessor[i]=inf;
		}
		distancia[src] = 0;		
		
        

    }
};


#endif