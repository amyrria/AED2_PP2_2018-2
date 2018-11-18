#include <cstdlib>
#include <iostream>
#define inf -1
using namespace std;


template <class T>
class Node {
public:
    Node(const T &e = T(),const double&w = 0, Node *n = NULL, Node *p = NULL) : elemento(e), peso(w), prox(n), anterior(p) {}
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
private:
    T Item;
    NodeFila *prox;
public:
    NodeFila(){}
    T getItem(){return this->Item;}
    NodeFila *getProx(){return this->prox;}
    void setItem(T Item){this->Item = Item;}
    void setProx(NodeFila *prox){this->prox = prox;}
};

template <class T> class Fila 
{
public:
    int size;
    NodeFila<T> *front, *back;
public:
    Fila();
    void enfileirar(T&);
    T desenfileirar();
    bool empty();
};

template <class T> Fila<T>::Fila() 
{
    back = new NodeFila<T>();
    back->setProx(NULL);
    front = back;
    size = 0;
}
template <class T> void Fila<T>::enfileirar(T& N) 
{
    NodeFila<T> *qNode = new NodeFila<T>();
    qNode->setProx(NULL);
    qNode->setItem(N);
    back->setProx(qNode);
    back = qNode;
    if (size==0) front = back;
    size++;
}
template <class T> T Fila<T>::desenfileirar()
{
    if(!empty()){
        NodeFila<T> *aux = front;
        front = aux->getProx();
        size--;
        T item = aux->getItem();
        delete aux;
        return item;
    }else{
        return T();
    }

}
template <class T> bool Fila<T>::empty(){return (this->size == 0);}


template <class T>
class Lista {
private:
    Node<T> *cabeca;
    Node<T> *cauda;
    Node<T> *node;
    int size;
    
public:
    Lista() {
        cabeca = new Node<T>();
        cauda = new Node<T>();
    }
    ~Lista() {
        delete cabeca;
        delete cauda;
    }
    int get_Size(){return this->size;}
    Node<T> * getCabecaProx(){return this->cabeca->prox;}
    Node<T> * getCaudaAnterior(){return this->cauda->anterior;}
    bool isEmpty() { return (cabeca->prox == NULL); }
    void inserir(T &e, double w) {
        
        if (!isEmpty()) {
            Node<T> *ultNode = cauda->anterior;
            Node<T> *newNode = new Node<T>(e,w, NULL, ultNode);
            ultNode->prox = newNode;
            cauda->anterior = newNode;
            size++;
        }
        else {
            Node<T> *newNode = new Node<T>(e,w);
            cabeca->prox = newNode;
            cauda->anterior = newNode;
            size++;
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
    int * BFS(int s, int *inimigos, int e) 
    { 
        Fila<int> fila; 
        int i; 
        bool *visitado = new bool[V+1]; 
        int *predecessor = new int[V+1];

        for(int i = 1; i < V+1; i++) visitado[i] = false;
        for(int i = 0; i<e; i++) {visitado[inimigos[i]] = true; predecessor[inimigos[i]] = -1;}

        visitado[s] = true; 
        predecessor[s] = -1;
        fila.enfileirar(s);

      
        while(!fila.empty()) 
        { 
            s = fila.desenfileirar();
            Node<int> *node;
            node = adj[s].getCabecaProx();

            while(node!=NULL){
                i =  node->get_Element();
                
                if (!visitado[i]) 
                {
                    predecessor[i] = s;
                    visitado[i] = true; 
                    fila.enfileirar(i);
                } 
                node = node->prox;
            };

        } 
        return predecessor;
        
    };
    double DFS_visita(int v, bool visitado[]) 
    { 
        int i;
        visitado[v] = true; 
        double peso = 0;
        Node<int> *node;
        node = adj[v].getCabecaProx();
        while(node!=NULL){
            i =  node->get_Element();
            if (!visitado[i]) 
            {
                peso += node->get_Peso();
                peso += DFS_visita(i, visitado);
            }
            node = node->prox;
        };
        return peso;
    };
    double DFS()
    { 
        bool *visitado = new bool[V+1];
        double peso=0;
        for (int i = 1; i < V; i++) visitado[i] = false;
        for (int i = 1; i < V; i++){
            if(!visitado[i]){
                peso += DFS_visita(i, visitado); 
            };
        };
        return peso;
    };

  
};
int main(){
    int N, M, u, v,n,m,e, qtdI, orig, dest;
    double w;
    cin>> N >> M;
    Grafo G(N); 
    for(int i=1; i<= M;i++) {
        cin >> u>>v;
        G.addAresta(u, v, 1);
    };

    cin>>qtdI;
    int *inimigos = new int[qtdI];
    for(int i=0; i<qtdI;i++){
        cin >> e;
        inimigos[i] = e;  
    }
    cin>> orig >> dest;
    int *predecessor = G.BFS(orig,inimigos, qtdI);
    Grafo *g = new Grafo[N+1];
    for(int i = 1; i <= N; i++){
        cin >> n >> m;
        g[i].iniciar(n);        
        for(int j=0; j < m; j++) {
            cin >> u >> v >> w;
            g[i].addAresta(u, v, w);
        };

    };
    double peso=0;
    while(dest != -1){
        peso += g[dest].DFS();    
        dest = predecessor[dest];
    }    
    cout.precision(1);
    cout << fixed<< peso << endl;
    return 0;
}