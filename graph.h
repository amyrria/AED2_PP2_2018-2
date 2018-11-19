#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include<iomanip>
using namespace std;
template <class T>
class Graph
{ 
    private:
        int V;
        T **adj;
    public:
				Graph(){}
        Graph(int V){
            this->V = V;
            adj = new T*[V+1];
            for(int i = 0;i <= V; ++i)
                adj[i] = new T[V+1];
            for(int i = 0;i <= V; ++i)
                for(int j = 0;j <= V; ++j)
                    adj[i][j] = T();
        }
        ~Graph(){    
            for(int i = 0;i <= V; ++i)
                delete[] adj[i];
            delete[] adj; 
        }
				void createGraph(int V){
            this->V = V;
            adj = new T*[V+1];
            for(int i = 0;i <= V; ++i)
                adj[i] = new T[V+1];
            for(int i = 0;i <= V; ++i)
                for(int j = 0;j <= V; ++j)
                    adj[i][j] = T();
        }
        void addEdge(int v1, int v2, T w) {
            adj[v1][v2] = w;
            adj[v2][v1] = w;
        }
        void print() {
            for(int i=1; i<=V; i++){
                for(int j=1; j<=V; j++){
                    cout << fixed << setprecision(1) << adj[i][j] << "\t";
                }
                cout << endl;
            }
        }
        int getV(){ return V; }
};


#endif