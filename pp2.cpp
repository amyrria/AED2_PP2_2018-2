#include <iostream>
#include<iomanip>
#include<climits> 
#define inf (int)1e6

using namespace std;
//template <class T>
class Vertice{
	private:
		int id = 0;
		float distancia = inf;
		Vertice* antecessor = NULL;
	public:
		Vertice(){}
		int getId(){return id;}
		float getDistancia(){return distancia;}
		Vertice* getAntecessor(){return antecessor;}
		void setId(int id){this->id = id;}
		void setDistancia(float d){distancia = d;}
		void setAntecessor(Vertice* v){antecessor = v;}
};
template <class T>
class Aresta{
	private:
		T v1;
		T v2;
		float peso;
	public:
		Aresta(){}
		void insere(T u, T v, float w){
			v1 = u;
			v2 = v;
			peso = w;
		}
		T getV1(){return v1;}
		T getV2(){return v2;}
		float getPeso(){return peso;}
		void setV1(T v){v1 = v;}
		void setV2(T v){v2 = v;}
		void setPeso(float p){peso = p;}
};

class Grafo{
	private:
		int V;
		int ordem;
		float **adj;
		Vertice *vertice;
	public:
		Grafo(){}
		Grafo(int V, int o){
			this->V = V;
			adj = new float*[V+1];
			for(int i = 0;i <= V; ++i)
				adj[i] = new float[V+1];
			for(int i = 0;i <= V; ++i)
				for(int j = 0;j <= V; ++j)
					adj[i][j] = float(-1);
			vertice = new Vertice[V+1];
			ordem = o;
		}
		~Grafo(){
			for(int i = 0;i <= V; ++i)
				delete[] adj[i];
			delete[] adj; 
		}
		void createGraph(int V, int o){
			this->V = V;
			adj = new float*[V+1];
			for(int i = 0;i <= V; ++i)
				adj[i] = new float[V+1];
			for(int i = 0;i <= V; ++i)
				for(int j = 0;j <= V; ++j)
					adj[i][j] = float(-1);
			vertice = new Vertice[V+1];
			ordem = o;
		}
		void add_aresta(int v1, int v2, float w) {
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
		void printVertice(){
			for(int i=1; i<=V; i++){
				cout << "uid: " << i;
				cout << "\tid: " << vertice[i].getId();
				cout << "\tDist: " << vertice[i].getDistancia();
				cout << "\tAnt: " << (vertice[i].getAntecessor()!=NULL?vertice[i].getAntecessor()->getId():0);
				cout << endl;
			}
		}
		int getOrdem(){return ordem;}
		int getV(){ return V; }
		Vertice *getVertice(){return vertice;}
		float getPeso(int v1, int v2){return adj[v1][v2];}
};

void TROCA(Vertice *u, Vertice *v){
	Vertice aux = *u;
	*u = *v;
	*v = aux;
}

int pai(int i) { return i/2;}
int esq(int i) { return 2*i;}
int dir(int i) { return 2*i + 1;} 

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

int BUSCA(Grafo *g, int v){
	int i;
	Vertice *iterador = g->getVertice();
	for(i = 1; i <= g->getV(); i++){
		if(v==iterador[i].getId())
			break;
	}
	return i;
}

Vertice * EXTRAI_MIN(Grafo *g, int s){
	Vertice *iterador = g->getVertice();
	int menor=s;
	for (int i = s;i<=g->getV(); i++){
		if(iterador[menor].getDistancia() > iterador[i].getDistancia())
			menor = i;
	}
	TROCA(&iterador[menor],&iterador[s]);
	return &iterador[s];
}

void DIJKSTRA(Grafo *g, int s){
	INICIALIZA(g, s);
	Vertice *iterador = g->getVertice();
	Vertice *u, *v;
	int c_Q = 1;
	float w;
	while(c_Q<=g->getV()){
		u = EXTRAI_MIN(g,c_Q);
		c_Q++;
		for(int i = 1; i <= g->getV(); i++){
			w = g->getPeso(u->getId(), i);
			if(w >= 0){
				v = &iterador[BUSCA(g, i)];
				RELAXA(u,v, w);
			}
		}
	}
}
int FIND_SET(int i, int *parente) {
	if (i == parente[i])
		return i;
	else
		return FIND_SET(parente[i], parente);
}

void UNION(int u, int v, int *parente) {
    parente[u] = parente[v];
}

float KRUSKAL(Grafo &g){
	float w, total=0.0;
	int count = 0;
	Aresta<int> a[g.getOrdem()];
	int parente[g.getV()+1];

	for (int i = 0; i <= g.getV(); i++) parente[i] = i;
	for(int y = 1; y <= g.getV(); y++){
		for(int x = y+1; x <= g.getV(); x++){
			w = g.getPeso(y, x);
			if(w >= 0){
				a[count].insere(y, x, w);
				count++;
			}
		}
	}
	for (int i = 0; i < count - 1; i++) {
		for (int j = i+1; j < count; j++) {
			if(a[i].getPeso() > a[j].getPeso())
				swap(a[i], a[j]);
		}
	}

	int vertice1, vertice2;
	for (int i = 0; i < count; i++) {
		vertice1 = FIND_SET(a[i].getV1(), parente);
		vertice2 = FIND_SET(a[i].getV2(), parente);
		if (vertice1 != vertice2) {
			total += a[i].getPeso();
			UNION(vertice1, vertice2, parente);
		}
	}
	return total;
}

int main(){
	int v_Cerebro, a_Cerebro;
	cin >> v_Cerebro >> a_Cerebro;

	Grafo Grafo_Cerebro(v_Cerebro, a_Cerebro), *grafo_BlocoNeuronio = new Grafo[v_Cerebro+1];

	int  v1, v2;
	float peso;
	for(int i = 1; i <= a_Cerebro; i++){
		cin >> v1 >> v2 >> peso;
		Grafo_Cerebro.add_aresta(v1, v2, peso);
	}

	int  origem, destino;
	cin >> origem >> destino;

	int *qtd_doente, neuronios_doentes;
	qtd_doente = new int[v_Cerebro+1];

	int v_BlocoNeuronio, a_BlocoNeuronio;

	for(int i = 1; i <= v_Cerebro; i++){
		cin >> v_BlocoNeuronio >> a_BlocoNeuronio >> qtd_doente[i];
		for(int j = 0; j < qtd_doente[i]; j++) cin >> neuronios_doentes;
		
		grafo_BlocoNeuronio[i].createGraph(v_BlocoNeuronio, a_BlocoNeuronio);
		for(int j = 1; j <= a_BlocoNeuronio; j++){
			cin >> v1 >> v2 >> peso;
			grafo_BlocoNeuronio[i].add_aresta(v1, v2, peso);
		}
	}
	DIJKSTRA(&Grafo_Cerebro, origem);
	Vertice *iterador = Grafo_Cerebro.getVertice();
	Vertice *iterador2 = &iterador[BUSCA(&Grafo_Cerebro, destino)];
	float total = 0;
	while(iterador2!=NULL){
		if (qtd_doente[iterador2->getId()] > 0) {
			total += KRUSKAL(grafo_BlocoNeuronio[iterador2->getId()]);
		}
		iterador2 = iterador2->getAntecessor();
	}
	cout<<total<< endl;
}    
	
