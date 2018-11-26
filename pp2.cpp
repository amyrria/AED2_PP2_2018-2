#include <iostream>
#include<iomanip>
#include<climits> 
#define inf (int)1e6

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
class Grafo;

template <class T> class Fila{
	private:
        int tamFila;
        No<T> *frente, *atras;
        No<T> *vetor;
        int tamHeap;

	public:
        Fila(){
            frente = new No<T>();
            atras = new No<T>();
            tamFila = 0;
        }
        ~Fila() {
                delete frente;
                delete atras;
        }
        void troca (Vertice *u, Vertice *v){
            Vertice aux = *u;
            *u = *v;
            *v = aux;
        }

        int pai(int i){return i/2;}
        int esq(int i) { return 2*i; }
        int dir(int i) { return 2*i + 1;} 

        void criar_FP(int tam){
            tamHeap = 0;
            vetor = new No<T>[tam];
        }
        void insere (No<T> item){
            tamHeap++; 
            int i = tamHeap; 
            vetor[i] = item; //id+ distancia + antecessor
          
            // Corrige as propriedades do heap 
            while (i != 1 && vetor[pai(i)].getItem().getDistancia() > vetor[i].getItem().getDistancia()) 
            { 
               troca(&vetor[i].getItem(), &vetor[pai(i)].getItem()); 
               i = pai(i); 
            } 
        }
        Vertice extractMin() 
        {  
            if (tamHeap == 1) 
            { 
                tamHeap--; 
                return vetor[0]; 
            } 
          
            // armazena o valor minimo 
            Vertice root = vetor[0]; 
            vetor[0] = vetor[tamHeap-1]; 
            tamHeap--; 
            MinHeapify(0); 
          
            return root; 
        } 
        void MinHeapify(int i) 
        { 
            int l = esq(i); 
            int r = dir(i); 
            int min = i; 
            if (l < tamHeap && vetor[l] < vetor[i]) 
                min = l; 
            if (r < tamHeap && vetor[r] < vetor[min]) 
                min = r; 
            if (min != i) 
            { 
                troca(&vetor[i], &vetor[min]); 
                MinHeapify(min); 
            } 
        } 


        void enfileirar(T &item){
            if (!empty()) {
                No<T> *ultNo = atras->getAnt();//ultimo no
                No<T> *no = new No<T>(item, ultNo);//novo no
                ultNo->setProx(no);
                atras->setAnt(ultNo->getProx());
                tamFila++;
            }
            else {
                No<T> *no = new No<T>(item);
                atras->setAnt(no);
                frente->setProx(atras->getAnt());
                tamFila++;
            }
        }
        T desenfileirar(){
            if(!empty()){
                No<T> *aux = frente;//no de vertice No<Vertice>
                if (frente == atras) frente = atras = 0; //nenhum nó permance dps da exclusao
                else{
                    frente = frente->getProx();
                }
                T item = aux->getItem();//item = Vertice
                delete aux;
                tamFila--;
                return item;
            }else{
                return T();
            }
        }
        int getTam(){return tamFila;}

        bool empty(){return tamFila == 0;}
        bool emptyFP(){return tamHeap == 0;}

        No<T> * getFrente(){return frente;}
};

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
	Fila<Vertice> S;
    Fila<Vertice> Q;
    Vertice *it = g->getVertice(); //me retorna um vertice(id,distancia,antecessor)

    // Q = G.V
    Vertice v;
    for(int i = 1; i <= g->getV(); i++){
        v = it[i]; 
        Q.insere(it[i]);//tentando adicionar o valor do ponteiro, o vertice
    }
    Vertice u;
    while(!Q.emptyFP()){
        u = Q.desenfileirar();
        //u = extract_min(Q);
        S.enfileirar(u);
        for(int i = 1; i <= g->getV(); i++){
            if(g->getPeso(u.getId(), i) > 0){
                //RELAXA(u,v,w) u = vertice, v = vertice, w = distancia
                //RELAXA(u,v, g->getPeso(u.getId(), i));
            }
        }
    }
}

int main(){
    int brain_n, brain_m, block_n, block_m, u, v, block_in, block_out, qtd_sick, sick;
    float weight;
    cin >> brain_n >> brain_m;
    Grafo brain(brain_n), *block = new Grafo[brain_n+1];
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
    //brain.dijsktra(1);

}    
    
