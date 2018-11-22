#include <iostream>
#include "graph.h"
#include "dijkstra.h"
using namespace std;
int main(){
    int brain_n, brain_m, block_n, block_m, u, v, block_in, block_out, qtd_sick, sick;
    float weight;
    cin >> brain_n >> brain_m;
    Graph<float> brain(brain_n), *block = new Graph<float>[brain_n+1];
    for(int i = 1; i <= brain_m; i++){
        cin >> u >> v >> weight;
        brain.addEdge(u, v, weight);
    }
    cin >> block_in >> block_out;
		for(int i = 1; i <= brain_n; i++){
			cin >> block_n >> block_m >> qtd_sick;
      for(int j = 1; j <= qtd_sick; j++){
        cin >> sick;
      }
			block[i].createGraph(block_n);
      for(int j = 1; j <= block_m; j++){
        cin >> u >> v >> weight;
        block[i].addEdge(u, v, weight);
      }
		}
    block[1].print();
}