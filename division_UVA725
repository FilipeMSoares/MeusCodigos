#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pairII{
	long int x, y;
} pii;

pii mkPii(long int k, long int z){
	pii p;
	p.x = k;
	p.y = z;
	return p;
}

pii stock[80][1000];

int n;
short int vis[10], sz[80];
char digits[11], aux[11], num1[6], num2[6];
pii transfer(){
	for(int i = 0; i < 10; i++){
		if(i < 5){
			num1[i] = aux[i];
		}else{
			num2[i-5] = aux[i];
		}
	}
	return mkPii(atoi(num1),atoi(num2));
}

void init(){
	for(int i = 0; i < 80; i++) sz[i] = 0;
	for(int i = 0; i < 10; i++){
		digits[i] = '0'+i;
		vis[i] = 0;
	}
	digits[10] = aux[10] = '\0';
	num1[5] = '\0';
	num2[5] = '\0';
}

void perm(int k){
	if(k == 10){
		pii p =transfer();
		if(p.x > p.y){
			if(p.x % p.y == 0){
				int k = p.x/p.y;
				stock[k][sz[k]++] = p;
			}
		}
	}else{
		for(int i = 0; i < 10; i++){
			if(!vis[i]){
				vis[i] = 1;
				aux[k] = digits[i];
				perm(k+1);
				vis[i] = 0;
			}
		}
	}
}

void printPII(pii p){
	if(p.x < 10000) printf("0");
	printf("%ld / ",p.x);
	if(p.y < 10000) printf("0");
	printf("%ld = %d\n", p.y, n);
}

int main (void){
	init();
	perm(0);
	scanf("%d", &n);
	while(n != 0){
		if(sz[n] == 0){
			printf("There are no solutions for %d.\n",n);
		}else{
			for(int i = 0; i < sz[n]; i++){
				printPII(stock[n][i]);
			}
		}
		scanf("%d", &n);
		if(n != 0) printf("\n");
	}
	return 0;
}
