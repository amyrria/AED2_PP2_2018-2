#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
using namespace std;
template <class T>
class Graph 
{ 
    private:
        int V;
        T **adj;
    public:
        Graph(const int &V){
            this->V = V;
            adj = new T*[V+1];
            for(int i = 0;i <= V; ++i)
                adj[i] = new T[V+1];

            for(int i = 0;i <= V; ++i)
                for(int j = 0;j <= V; ++j)
                    adj[i][j] = 0;
        }
        ~Graph(){    
            for(int i = 0;i <= V; ++i)
                delete[] adj[i];
            delete[] adj; 
        }
        void addEdge(const int &v1, const int &v2, const float &w) { 
            adj[v1][v2] = w;
            adj[v2][v1] = w;
        }
        void print() {
            for(int i=1; i<=V; i++){
                for(int j=1; j<=V; j++){
                    cout << adj[i][j] << " ";
                }
                cout << endl;
            }
        }
};


#endif