#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct vint{
	int* v, sz, capacity;
	int init(){
		if(v != NULL) return 1;
		v = (int*) malloc(100*sizeof(int));
		sz = 0; capacity = 100;
		return v != NULL;
	}
	int aumenta(){
		if(sz < capacity) return 1;
		int* mv = (int*) realloc(v,(capacity+100)*sizeof(int));
		if(mv == NULL) return 0;
		v = mv;
		capacity+=100;
		return 1;
	}
	int size(){
		if(v == NULL) return -1;
		return sz;
	}
	void clear(){
		free(v);
	}
	int* operator[](int i){
		if(i > sz || i >= capacity || i < 0) return NULL;
		return (v+i);
	}
	void print(){
		for(int i = 0; i < size(); i++){
			printf("%d ", v[i]);
		}printf("\n");
	}
	static void copy(vint v, vint& u){
		if(!u.init()) return;
		while(v.capacity > u.capacity) u.aumenta();
		u.sz = v.size();
		for(int i = 0; i < v.size(); i++){
			*u[i] = *v[i];
		}
	}
} dvi;

typedef struct h{
	dvi list;
	int init(){
		list.v = NULL;
		return list.init();
	}
	void clear(){
		list.clear();
	}
	void trade(int i, int j){
		int aux = *list[i];
		*list[i] = *list[j];
		*list[j] = aux;
	}
	void subir(int i){
		if(i == 0) return ;
		int m = (i+1)/2-1;
		if(*list[i] > *list[m]){
			trade(i,m);
			subir(m);
		}
	}
	void descer(int i, int n){
		int j = 2*i+1;
		if(j < n){
			if(j < n-1){
				if(*list[j] < *list[j+1]) j++;
			}
			if(*list[i] < *list[j]){
				trade(i,j);
				descer(j,n);
			}
		}
	}
	int add(int i){
		if(!list.init()) return 0;
		if(!list.aumenta()) return 0;
		*list[list.sz] = i;
		subir(list.sz);
		list.sz++;
		return 1;
	}
	void auto_arrange(){
		int m = list.size()/2-1;
		for(int i = m; i >= 0; i--){
			descer(i,list.size());
		}
	}
	dvi ordlist(){
		int m = list.size()-1;
		while(m >= 0){
			trade(0,m);
			m = m-1;
			descer(0,m+1);
		}
		dvi aux; aux.v = NULL;
		dvi::copy(list,aux);
		auto_arrange();
		return aux;
	}
	int operator[](int i){
		return *list[i];
	}
	void print(){
		for(int i = 0; i < list.size(); i++){
			printf("%d ", *list[i]);
		}printf("\n");
	}
} heapi;

int main(void){
	heapi v; dvi v2; int x;
	v.init();
	for(int i = 0; i < 7; i++){
		scanf("%d",&x);
		v.add(x);
	}
	v2 = v.ordlist();
	v.print();
	v2.print();
	return 0;
}
