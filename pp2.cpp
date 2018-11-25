#include <iostream>
#include<iomanip>

#define inf 999

using namespace std;

class Vertice{
    private:
        int id;
        float distancia;
        Vertice* antecessor;
    public:
        Vertice(){}
        int getId(){
            return id;
        }
        float getDistancia(){
            return distancia;
        }
        Vertice* getAntecessor(){
            return antecessor;
        }
        void setId(int id){
            this->id = id;
        }
        void setDistancia(float d){
            distancia = d;
        }
        void setAntecessor(Vertice* v){
            antecessor = v;
        }
};

template <class T> class No{
    private:
        T item;
        No *prox;
        No *ant;
    public:
        No(const T &item = T(), No *anterior = NULL, No *proximo = NULL) : item(item), ant(anterior), prox(proximo){}
        T getItem(){return item;}
        No *getProx(){return prox;}
        No *getAnt(){return ant;}
        void setProx(No *p){
            prox = p;
        }
        void setAnt(No *a){
            ant = a;
        }
};

template <class T> class Fila{
	private:
        int tamanho;
        No<T> *frente, *atras;
	public:
        Fila(){
            frente = new No<T>();
            atras = new No<T>();
            tamanho = 0;
        }
        ~Fila() {
                delete frente;
                delete atras;
        }
        void enfileirar(T &item){
            if (!empty()) {
                No<T> *ultNo = atras->getAnt();
                No<T> *no = new No<T>(item, ultNo);
                ultNo->setProx(no);
                atras->setAnt(ultNo->getProx());
                tamanho++;
            }
            else {
                No<T> *no = new No<T>(item);
                atras->setAnt(no);
                frente->setProx(atras->getAnt());
                tamanho++;
            }
        }
        T desenfileirar(){
            if(!empty()){
                No<T> *aux = frente->getProx();
                frente->setProx(aux->getProx());
                tamanho--;
                T item = aux->getItem();
                // delete aux;
                return item;
            }else{
                return T();
            }
        }
        int getTam(){return tamanho;}
        bool empty(){return tamanho == 0;}
        No<T> * getFrente(){return frente;}
};

No<Vertice> extract_min(Fila<Vertice> *f){
	return f->desenfileirar();
}

class Grafo{
    private:
        int V;
        float **adj;
        Vertice *vertice;
    public:
        Grafo(){}
        Grafo(int V){
            this->V = V;
            adj = new float*[V+1];
            for(int i = 0;i <= V; ++i)
                adj[i] = new float[V+1];
            for(int i = 0;i <= V; ++i)
                for(int j = 0;j <= V; ++j)
                    adj[i][j] = float();
            vertice = new Vertice[V+1];
        }
        ~Grafo(){
            for(int i = 0;i <= V; ++i)
                delete[] adj[i];
            delete[] adj; 
        }
        void createGraph(int V){
            this->V = V;
            adj = new float*[V+1];
            for(int i = 0;i <= V; ++i)
                adj[i] = new float[V+1];
            for(int i = 0;i <= V; ++i)
                for(int j = 0;j <= V; ++j)
                    adj[i][j] = float();
            vertice = new Vertice[V+1];
        }
        void addEdge(int v1, int v2, float w) {
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
        Vertice *getVertice(){return vertice;}
        float getPeso(int v1, int v2){return adj[v1][v2];}
};

void INICIALIZA(Grafo *g, int s){
	Vertice *v = g->getVertice();
	for(int i = 1; i <= g->getV(); i++){
        v[i].setId(i);
		v[i].setDistancia(inf);
		v[i].setAntecessor(NULL);
	}
	v[s].setDistancia(0);
}

void RELAXA(Vertice *u, Vertice *v, float w){
	if (v->getDistancia() > u->getDistancia() + w) {
		v->setDistancia(u->getDistancia() + w);
		v->setAntecessor(u);
	}
}

void DIJKSTRA(Grafo *g, int s){
	INICIALIZA(g, s);
	Fila<Vertice*> S;
    Fila<Vertice*> Q;
    Vertice *it = g->getVertice();
    // Q = G.V
    for(int i = 1; i <= g->getV(); i++){
        Q.enfileirar(&it[i]);
    }
    Vertice u;
    while(!Q.empty()){
        u = Q.desenfileirar();
        S.enfileirar(u);
        for(int i = 1; i <= g->getV(); i++){
            if(g->getPeso(u.getId(), i) > 0){
                RELAXA()
            }
        }
    }
}

int main(){
    int brain_n, brain_m, block_n, block_m, u, v, block_in, block_out, qtd_sick, sick;
    float weight;
    cin >> brain_n >> brain_m;
    Grafo<int> brain(brain_n), *block = new Grafo<int>[brain_n+1];
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
    
