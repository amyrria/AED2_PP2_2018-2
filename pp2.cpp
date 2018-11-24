#include <iostream>
#include<iomanip>

#define inf 999

using namespace std;

template <class T> class NodeFila{
public:
    T item;
    double dist;
    NodeFila *prox;
    NodeFila *ant;
    NodeFila(const T &item = T(), NodeFila *proximo = NULL, NodeFila *anterior = NULL) : item(item), prox(proximo), ant(anterior){}
    T getItem(){return item;}
    double getDist(){return dist;}
    NodeFila *getProx(){return prox;}
    NodeFila *getAnt(){return ant;}
    void setDist(double dist) {this->dist = dist;}
};

template <class T> class Fila{
private:
    int tamanho;
    NodeFila<T> *frente, *atras;
public:
    Fila(){
        frente = new NodeFila<T>();
        atras = new NodeFila<T>();
        tamanho = 0;
    }
    ~Fila() {
        delete frente;
        delete atras;
    }
    void enfileirar(T &item){
        if (!empty()) {
            NodeFila<T> *ultNode = atras->ant;
            NodeFila<T> *newNode = new NodeFila<T>(item, NULL, ultNode);
            ultNode->prox = newNode;
            atras->ant = newNode;
            tamanho++;
        }
        else {
            NodeFila<T> *newNode = new NodeFila<T>(item);
            frente->prox = newNode;
            atras->ant = newNode;
            tamanho++;
        }
    }
    T desenfileirar(){
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
    int getTam(){return tamanho;}
    bool empty(){return (this->tamanho == 0);}
    NodeFila<T> * getFrente(){return this->frente->prox;}
    NodeFila<T> extract_min(){
        NodeFila<T> *it = frente->getProx();
        NodeFila<T> *menor = it;
        while(it!=NULL){
            if (menor->getDist() > it->getDist()){
                menor = it;
            }
            it = it->getProx();
        }

        if(menor->ant!=NULL){
            menor->ant->prox = menor->prox;
        }else{
            frente = menor->prox;
        }
        if (menor->prox!=NULL){
            menor->prox->ant = menor->ant;
        }else{
            atras = menor->ant;
        }

        NodeFila<T> retorno = *menor;
        delete menor;
        return retorno;
    }
};


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

    void dijsktra (int s){
        // INICIALIZA(G,s)
        NodeFila<T> *vetorNode = new NodeFila<T>[getV()+1];
        for (int i = 1; i <= getV(); i++){
            vetorNode[i].dist = inf;
            vetorNode[i].ant = NULL; 
        }
        vetorNode[s].dist = 0;

        Fila<NodeFila<T>> S;
        Fila<NodeFila<T>> Q;
        for (int i = 1; i <= getV(); i++){
            Q.enfileirar(vetorNode[i]);
        }
        NodeFila<T> u;
        // while(!Q.empty()){
            // EXTRACT-MIN(Q)
            u = Q.extract_min();
        // }
    }
};

int main(){
    int brain_n, brain_m, block_n, block_m, u, v, block_in, block_out, qtd_sick, sick;
    float weight;
    cin >> brain_n >> brain_m;
    Graph<int> brain(brain_n), *block = new Graph<int>[brain_n+1];
    for(int i = 1; i <= brain_m; i++){
        cin >> u >> v >> weight;
        brain.addEdge(u, v, weight);
    }
    cin >> block_in >> block_out;
    for(int i = 1; i <= brain_n; i++){
        cin >> block_n >> block_m >> qtd_sick;
        for(int j = 1; j <= qtd_sick; j++) cin >> sick;
        
        block[i].createGraph(block_n);

        for(int j = 1; j <= block_m; j++){
            cin >> u >> v >> weight;
            block[i].addEdge(u, v, weight);
        }
    }
    block[1].print();
    brain.print();
    brain.dijsktra(1);

}    
    
