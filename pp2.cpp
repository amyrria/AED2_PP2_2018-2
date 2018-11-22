#include <iostream>
#include<iomanip>

#define inf -1
using namespace std;
template <class T> class NodeFila 
{
public:
    T item;
    double custo;
    NodeFila *prox;
    NodeFila(const T &item = T(),const double&custo = 0, NodeFila *n = NULL) : item(item), custo(custo), prox(n){}
    ~NodeFila(){}
    //void setItem(T Item){this->Item = Item;}
    T getItem(){return this->item;}
    T getCusto(){return this->custo;}
    NodeFila *getProx(){return this->prox;}    
    //void setProx(NodeFila *prox){this->prox = prox;}
};

template <class T> class Fila 
{
public:
    int tamanho;
    NodeFila<T> *frente, *atras;
public:
    Fila();
    void enfileirar(T &item, double custo);
    void enfileirarPrioridade(T &item);
    T desenfileirar();
    NodeFila<T> * getFrente(){return this->frente->prox;}
    int comparar()const;
    bool empty();

    ~Fila() {
    	delete frente;
    	delete atras;
	}
};

template <class T> Fila<T>::Fila() 
{
    frente = new NodeFila<T>();
    atras = new NodeFila<T>();
    tamanho = 0;

}
template <class T> void Fila<T>::enfileirar(T& item, double custo) 
{
    NodeFila<T> *qNode = new NodeFila<T>(item,custo);
    atras->prox = qNode;
    atras = qNode;
    if (tamanho==0) frente = atras;
    tamanho++;
}
template <class T> void Fila<T>::enfileirarPrioridade(T& item) 
{
    NodeFila<T> *qNode = new NodeFila<T>(item, 0);
    atras->prox = qNode;
    atras = qNode;
    if (tamanho==0) frente = atras;
    tamanho++;
}

template <class T> T Fila<T>::desenfileirar()
{
    if(!empty()){
        NodeFila<T> *aux = frente;
        frente = aux->getProx();
        tamanho--;
        T item = aux->getItem();
        delete aux;
        return item;
    }else{
        return T();
    }

}
template <class T> int Fila<T>::comparar () const
{ 
	NodeFila<T> *node = frente;
	if(!empty())return node->getItem() > node->getProx()->getItem();
	else{
		return node->getItem();
	}

} 

template <class T> bool Fila<T>::empty(){return (this->tamanho == 0);}

template <class T> class Graph
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

    int dijsktra (int V, int src){
    	Fila<T> fila; 
        int i; 
        bool *visitado = new bool[V+1]; 
        int *caminho = new int[V+1];
        double *distancia = new double[V+1];

        for(int i = 1; i < V+1; i++) visitado[i] = false; distancia[i] = inf;

        distancia[src] = 0;
        
        visitado[src] = true;
        predecessor[src] = inf;
        fila.enfileirar(src , distancia[src]);

        int count = 1;
        while(!fila.empty()) 
        { 
            int u = fila.comparar();

            visitado[u] = true;
            // Update dist value of the adjacent vertices of the picked vertex.
            for (int v = 1; v < V+1; v++) {
            	count++;
            	if (!visitado[v] && adj[u][v] && distancia[u] != inf && distancia[v]> distancia[u]+adj[u][v]){ 
            		distancia[v] = distancia[u] + adj[u][v];
            		fila.enfileirar(v,distancia[v]);
            		caminho[count]=v;

            	}
            }
            // for (int i = src; i < V+1; i++){
            // 	for (int j = 1; j < V+1; j++)
            // 	{
            // 		else (!visitado[j] && distancia[j] > distancia[src] + adj[src][j]){
            // 			distancia[j] = distancia[src]+ adj[src][j];
            // 			fila.enfileirar(j,distancia[j]);
            // 			visitado[src]=true;
            // 		}
            // 	}
            // }

        }
        return caminho;
    }
};

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
    dijkstra(Graph<float>,1);
    block[1].print();
}
