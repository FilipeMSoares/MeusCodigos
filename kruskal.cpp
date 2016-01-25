
//Kruskal implementado com minhas estruturas
//Descobri que não precisava fazer uma estrutura pro grafo :P para o Kruskal
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//arestas
typedef struct midlink{
	int w;
	int peso;
} mlk;

mlk newMidLink(int b, int p){
	mlk e;
	e.w = b; e.peso = p;
	return e;
}

typedef struct link{
	int v;
	mlk m;
} lk;

lk newLink(int a, mlk b){
	lk e;
	e.v = a;
	e.m = b;
	return e;
}
//end arestas


//global var
int *pai, *sz;
lk *ars;
//end global var


//listas
//vi
typedef struct listadj{
    int sz;
    int capacity;
    mlk *vt;
    
    int init(){
        if(vt == NULL) return 0;
        vt = (mlk*) malloc(100*sizeof(mlk));
        if(vt != NULL){
			sz = 0;
			capacity = 100;
		}
        return vt != NULL;
    }
    
    int aumenta(){
        mlk* mais_vt = (mlk*) realloc(vt,sizeof(mlk)*(capacity+100));
        if(mais_vt == NULL) return 0;
        vt = mais_vt;
        capacity+=100;
        return 1;
    }
    
    int add(int v, int p){
        if(!init()) return 0;
        if(sz == capacity) if(!aumenta()) return 0;
        vt[sz++] = newMidLink(v,p);
        return 1;
    }
    
    int add(mlk m){
        if(!init()) return 0;
        if(sz == capacity) if(!aumenta()) return 0;
        vt[sz++] = m;
        return 1;
    }
    
    int size(){
		if(vt == NULL) return 0;
        return sz;
    }
    
    void clear(){
        if(vt != NULL) free(vt);
    }
} la;


//g
typedef struct grafo{
    int cap;
    la* vcs;
    
    int init(){
        if(vcs != NULL) return 1;
        vcs = (la*) malloc(100*sizeof(la));
        if(vcs != NULL){
			cap = 100;
		}
        return vcs != NULL;
    }
    
    int aumenta(){
        la* mais_vcs = (la*) realloc(vcs,(cap+100)*sizeof(la));
        if(mais_vcs == NULL) return 0;
        vcs = mais_vcs;
        cap+=100;
        return 1;
    }
    
    int add(lk e){
		if(!init()) return 0;
		while(cap < e.v) if(!aumenta()) return 0;
		while(cap < e.m.w) if(!aumenta()) return 0;
		mlk b = newMidLink(e.v,e.m.peso);
		int a = vcs[e.m.w].add(b);
		return a && vcs[e.v].add(e.m);
	}
    
    int capacity(){
		if(vcs == NULL) return 0;
        return cap;
    }
    
    void clear(){
        if(vcs != NULL) free(vcs);
    }
    
} g;
//end listas


//union-find
int UFfind(int v){
	while(v != pai[v]) v = pai[v];
	return v;
}
void UFunion(int v, int w){
	if(sz[v] < sz[w]){
		pai[v] = w;
		sz[w] += sz[v];
	}else{
		pai[w] = v;
		sz[v] += sz[w];
	}
}
//end union-find


//mergesort
void mergesort(int b, int e, lk **as){
	if(b >= e) return;
	int m = (b+e)/2;
	mergesort(b,m,as);
	mergesort(m+1,e,as);
	int i = b, j = m+1, k = 0;
	lk* aux = (lk*) calloc(e-b+1,sizeof(lk));
	lk* ax = *as;
	while(i <= m && j <= e){
		if(ax[i].m.peso > ax[j].m.peso){
			aux[k++] = ax[j++];
		}else{
			aux[k++] = ax[i++];
		}
	}
	while(i <= m) aux[k++] = ax[i++];
	while(j <= e) aux[k++] = ax[j++];
	for(k = 0; k <= e-b; k++){
		ax[k+b] = aux[k];
	}
	free(aux);
}
//end mergesort


//kruskal
void initk(int s){
	if(pai == NULL) pai = (int*) malloc(s*sizeof(int));
	if(sz == NULL) sz = (int*) malloc(s*sizeof(int));
	if(pai != NULL && sz != NULL){
		for(int i = 0; i < s; i++){
			pai[i] = i;
			sz[i] = 1;
		}
	}
}

lk* mstk(g graf,lk* as, int n, int m){
	initk(n);
	lk* mst = (lk*) malloc((n-1)*sizeof(lk));
	int x ,y;
	int i, k;
	mergesort(0,m-1,&as);
	
	for(i = k = 0; i < m && k < n-1; i++){
		x = UFfind(as[i].v); y = UFfind(as[i].m.w);
		if(x != y){
			UFunion(x,y);
			mst[k++] = as[i];
		}
	}
	return mst;
} 
//end kruskal


//init
void initars(int m){
	if(ars == NULL) ars = (lk*) malloc(m*sizeof(lk));
	int a, b, c;
	for(int i = 0; i < m; i++){
		scanf("%d%d%d",&a,&b,&c);
		ars[i] = newLink(a-1,newMidLink(b-1,c));
	}
}

g graph;
void initg(int n, int m){
	initars(m);
	graph.cap = n;
	for(int i = 0; i < m; i++){
		graph.add(ars[i]);
	}
}
//end init


int main()
{
	int n, m;
	scanf("%d%d",&n,&m);
	initg(n,m);
	lk* mst = mstk(graph, ars, n, m);
	int sum = 0;
	for(int i = 0; i < n-1; i++){
		printf("%d-%d\n",mst[i].v,mst[i].m.w);
		sum+=mst[i].m.peso;
	}
	printf("%d\n",sum);
	graph.clear();
	free(pai); free(ars); free(sz);
    return 0;
}
