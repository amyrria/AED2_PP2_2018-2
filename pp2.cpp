#include <iostream>
#include<iomanip>
#include<climits> 
#define inf (int)1e6

using namespace std;

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

class Aresta{
	private:
		int v1;
		int v2;
		float peso;
	public:
		Aresta(){}
		void insere(int u, int v, float w){
			v1 = u;
			v2 = v;
			peso = w;
		}
		int getV1(){return v1;}
		int getV2(){return v2;}
		float getPeso(){return peso;}
		void setV1(int v){v1 = v;}
		void setV2(int v){v2 = v;}
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

		// int j = i;
		// vetor[i] = item; //id+ distancia + antecessor
		
		// Corrige as propriedades do heap 
		// while (j != 1 && v[pai(j)].getDistancia() > v[j].getDistancia()) 
		// { 
		// 	TROCA(&v[j], &v[pai(j)]); 
		// 	j = pai(j); 
		// } 
	}
	v[s].setDistancia(0);
}

void RELAXA(Vertice *u, Vertice *v, float w){
	if (v->getDistancia() > u->getDistancia() + w) {
		v->setDistancia(u->getDistancia() + w);
		v->setAntecessor(u);
	}
}

void HEAPFICA(Grafo *g, int i ){
	int l = esq(i); // l = 4
	int r = dir(i); // r = 5
	int min = i; // 2
	Vertice *A = g->getVertice();
	int tamHeap = g->getV();
	if (l <= tamHeap && A[l].getDistancia() < A[i].getDistancia()) {
		min = l; 
	}
	if (r <= tamHeap && A[r].getDistancia() < A[min].getDistancia()){
		min = r;
	}
	if (min != i) 
	{ 
		// TROCA(A[i], A[min])
		Vertice aux = A[i];
		A[i] = A[min];
		A[min] = aux;
		HEAPFICA(g, min); 
	} 
}

void CONSTROI_HEAP(Grafo *g){
	int tamHeap = g->getV(); // 5
	for (int i = tamHeap/2; i >= 1; i--) // 2 à 1
		HEAPFICA(g, i);
}

int BUSCA(Grafo *g, int v){
	int i;
	Vertice *it = g->getVertice();
	for(i = 1; i <= g->getV(); i++){
		if(v==it[i].getId())
			break;
	}
	return i;
}

void INSERE_HEAP(Grafo *g, int i ){
	Vertice *A = g->getVertice();
	while(i != 1 && A[pai(i)].getDistancia() > A[i].getDistancia())
	{
		TROCA(&A[pai(i)],&A[i]);
		i = pai(i);
	}
}

Vertice * EXTRAI_MIN(Grafo *g, int s){
	Vertice *it = g->getVertice();
	int menor=s;
	for (int i = s;i<=g->getV(); i++){
		if(it[menor].getDistancia() > it[i].getDistancia())
			menor = i;
	}
	TROCA(&it[menor],&it[s]);
	return &it[s];
}

void DIJKSTRA(Grafo *g, int s){
	INICIALIZA(g, s);
	// S = 0
	// Q = G.V
	Vertice *it = g->getVertice();
	Vertice *u, *v;
	int c_Q = 1;
	float w;
	while(c_Q<=g->getV()){
		u = EXTRAI_MIN(g,c_Q);
		c_Q++;
		for(int i = 1; i <= g->getV(); i++){
			w = g->getPeso(u->getId(), i);
			if(w >= 0){
				v = &it[BUSCA(g, i)];
				RELAXA(u,v, w);
			}
		}
	}
}
int find_set(int i, int *parente) {
	if (i == parente[i])
		return i;
	else
		return find_set(parente[i], parente);
}

void union_set(int u, int v, int *parente) {
    parente[u] = parente[v];
}

float KRUSKAL(Grafo &g){
	float w, total=0.0;
	int count =0;
	Aresta a[g.getOrdem()];
	int parente[g.getV()+1];
	for (int i = 0; i <= g.getV(); i++)
		parente[i] = i;
	for(int y = 1; y <= g.getV(); y++){
		for(int x = y+1; x <= g.getV(); x++){
			w = g.getPeso(y, x);
			if(w >= 0){
				a[count].insere(y, x, w);
				count++;
			}
		}
	}
	// Ordena
	for (int i = 0; i < count - 1; i++) {
		for (int j = i+1; j < count; j++) {
			if(a[i].getPeso() > a[j].getPeso())
				swap(a[i], a[j]);
		}
	}

	int uRep, vRep;
	for (int i = 0; i < count; i++) {
		uRep = find_set(a[i].getV1(), parente); // 0
		vRep = find_set(a[i].getV2(), parente); // 1
		if (uRep != vRep) {
			total += a[i].getPeso();
			union_set(uRep, vRep, parente);
		}
	}
	return total;
}

int main(){
	int brain_n, brain_m, block_n, block_m, u, v, block_in, block_out, *qtd_sick, sick;
	float weight;
	cin >> brain_n >> brain_m;
	Grafo brain(brain_n, brain_m), *block = new Grafo[brain_n+1];
	qtd_sick = new int[brain_n+1];
	for(int i = 1; i <= brain_m; i++){
		cin >> u >> v >> weight;
		brain.addEdge(u, v, weight);
	}
	cin >> block_in >> block_out;
	for(int i = 1; i <= brain_n; i++){
		cin >> block_n >> block_m >> qtd_sick[i];
		for(int j = 0; j < qtd_sick[i]; j++) cin >> sick;
		
		block[i].createGraph(block_n, block_m);

		for(int j = 1; j <= block_m; j++){
			cin >> u >> v >> weight;
			block[i].addEdge(u, v, weight);
		}
	}
	DIJKSTRA(&brain, block_in);
	Vertice *it = brain.getVertice();
	Vertice *it2 = &it[BUSCA(&brain, block_out)];
	float total = 0;
	while(it2!=NULL){
		if (qtd_sick[it2->getId()] > 0) {
			total += KRUSKAL(block[it2->getId()]);
		}
		it2 = it2->getAntecessor();
	}
	cout<<total;
}    
	
