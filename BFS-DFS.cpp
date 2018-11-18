#include <cstdlib>
#include <iostream>
#define INFINITO -1
using namespace std;


template <class T>
class Node {
public:
    Node(const T &elemento = T(),const double&custo = 0, Node *n = NULL, Node *p = NULL) : elemento(elemento), peso(custo), prox(n), anterior(p) {}
    ~Node() {}
    int get_Element(){return elemento;};
    int get_Peso(){return peso;};
    T elemento;
    double peso;
    Node *prox;
    Node *anterior;
    
};

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
    T desenfileirar();
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
template <class T> bool Fila<T>::empty(){return (this->tamanho == 0);}


template <class T>
class Lista {
private:
    Node<T> *cabeca;
    Node<T> *cauda;
    Node<T> *node;
    int tamanho;
    
public:
    Lista() {
        cabeca = new Node<T>();
        cauda = new Node<T>();
    }
    ~Lista() {
        delete cabeca;
        delete cauda;
    }
    int get_tamanho(){return this->tamanho;}
    Node<T> * getCabecaProx(){return this->cabeca->prox;}
    Node<T> * getCaudaAnterior(){return this->cauda->anterior;}
    bool isEmpty() { return (cabeca->prox == NULL); }
    void inserir(T &elemento, double custo) {
        
        if (!isEmpty()) {
            Node<T> *ultNode = cauda->anterior;
            Node<T> *novoNode = new Node<T>(elemento,custo, NULL, ultNode);
            ultNode->prox = novoNode;
            cauda->anterior = novoNode;
            tamanho++;
        }
        else {
            Node<T> *novoNode = new Node<T>(elemento,custo);
            cabeca->prox = novoNode;
            cauda->anterior = novoNode;
            tamanho++;
        }   
    }    
};

class Grafo 
{ 
    int V;
    Lista<int> *adj; 
public: 
    Grafo() {}; 
    Grafo(int V) 
    { 
        this->V = V; 
        adj = new Lista<int>[V+1];
    };
    void iniciar(int V) 
    { 
        this->V = V; 
        adj = new Lista<int>[V+1];
    };
    void addAresta(int u, int v, double w) 
    { 
        adj[u].inserir(v,w);
        adj[v].inserir(u,w);
    };
    void mostrar ( ){
        for(int i=1; i<=V;i++){
            Node<int> *node;
            node = adj[i].getCabecaProx();
            while(node!=NULL){
                node = node->prox;
            };
        };
    }
  
};
int main(){
    int N, M, vertice1, vertice2,n,m,doentes, qtDoentes, orig, dest;
    double custo;
    cin>> N >> M;
    Grafo G(N); 
    for(int i=1; i<= M;i++) {
        cin >> vertice1 >> vertice2 >> custo;
        G.addAresta(vertice1, vertice2, custo);
    };

    cin>>qtDoentes;
    int *NeuroniosDoentes = new int[doentes];
    for(int i=0; i<qtDoentes;i++){
        cin >> qtDoentes;
        NeuroniosDoentes[i] = doentes;  
    };
    cin>> orig >> dest;
    //int *percurso = G.dijkstra(orig, dest);
    

    Grafo *g = new Grafo[N+1];
    for(int i = 1; i <= N; i++){
        cin >> n >> m;
        g[i].iniciar(n);        
        for(int j=0; j < m; j++) {
            cin >> vertice1 >> vertice2 >> custo;
            g[i].addAresta(vertice1, vertice2, custo);
        };

    };
    double peso=0;
    while(dest != -1){
        //peso += g[dest].DFS();    
        //dest = predecessor[dest];
    }    
    cout.precision(1);
    cout << fixed<< peso << endl;
    return 0;
}