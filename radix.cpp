#include <stdio.h>
#include <stdlib.h>

typedef struct t_no{
	int value;
	t_no* next;
} no;

int pow10(int e){
	int x = 1;
	while(e--){
		x*=10;
	}
	return x;
}

int intlog10(int n){
	if(n == 0) return 0xffffffff;
	int x = 1, k = 0;
	while(x <= n){
		x*=10;
		k++;
	}
	return k;
}

int extractDigit(int n, int d){
	//printf("extractDigit(%d,%d)\n",n,d);
	int q = pow10(d);
	//printf("q = %d\n",q);
	if(q > n) return 0;
	int x = (n/q) % 10;
	return x;
}

typedef struct list_t_no{
	no* head = NULL;
	no* end = NULL;
	int bigg;
	
	int init(int v){
		if(head != NULL) return 1;
		head = (no*) malloc(sizeof(no));
		if(head == NULL) return 0;
		head->value = v;
		head->next = NULL;
		end = head;
		bigg = v;
		return 1;
	}

	int insere(int v){
		if(head == NULL) if(init(v)) return 1;
		no* node = (no*) malloc(sizeof(no));
		if(node == NULL) return 0;
		node->value = v;
		node->next = NULL;
		end->next = node;
		end = node;
		if(v > bigg) bigg = v;
		return 1;
	}
	
	int insere(no* node){
		if(head == NULL){
			head = node;
			end = node;
			head->next = NULL;
			if(node->value > bigg) bigg = node->value;
			return 1;
		}
		end->next = node;
		end = node;
		end->next = NULL;
		if(node->value > bigg) bigg = node->value;
		return 1;
	}
	
	no* removeFront(){
		no* aux = head;
		if(head == end){
			head = end = NULL;
		}else{
			head = head->next;
		}
		aux->next = NULL;
		return aux;
	}
	
	void radix(){
		int d = intlog10(bigg), k, j;
		no* qwerty[10], *endi[10];
		for(int i = 0; i < d; i++){
			for(j = 0; j < 10; j++){
				qwerty[j] = NULL; endi[j] = NULL;
			}
			while(head != NULL){
				k = extractDigit(head->value,i);
				if(qwerty[k] == NULL){
					qwerty[k] = endi[k] = removeFront();
				}else{
					endi[k]->next = removeFront();
					endi[k] = endi[k]->next;
				}
			}
			j = 0;
			while(qwerty[j] == NULL) j++;
			head = qwerty[j];
			end = endi[j]; j++;
			for(; j < 10; j++){
				if(qwerty[j] != NULL){
					end->next = qwerty[j];
					end = endi[j];
				}
			}
		}
	}
	
	void print(){
		no* node = head;
		while(node != NULL){
			printf("%d ",node->value);
			node = node->next;
		}printf("\n");
	}
	
	void clear(){
		bigg = 0xffffffff;
		no* aux;
		while(head != NULL){
			aux = head->next;
			free(head);
			head = aux;
		}
		free(end);
	}
	
} lno;

int main(void){
	lno l;
	int n = 10, x;
	for(int i = 0; i < n; i++){
		x = rand() % 100;
		l.insere(x);
	}
	l.print();
	l.radix();
	l.print();
	l.clear();
	return 0;
}
