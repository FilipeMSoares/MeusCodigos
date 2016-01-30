#include <stdio.h>

typedef struct jgcrt{
	int atk;
	int def;
	int skl;
} carta;

carta mao[20];

void reading(int idx){
	carta *c = &mao[idx];
	scanf("%d%d%d",&(c->atk),&(c->def),&(c->skl));
}

char vai(int idx, int nc, int n, int a, int d, int h){
	if(a == 0 && d == 0 && h == 0 && nc >= 2) return 'Y';
	if(a < 0 || d < 0 || h < 0) return 'N';
	if(idx == n) return 'N';
	char c;
	c = vai(idx+1,nc+1,n,a-mao[idx].atk,d-mao[idx].def,h-mao[idx].skl);
	if(c == 'Y') return c;
	c = vai(idx+1,nc,n,a,d,h);
	if(c == 'Y') return c;
	return 'N';
}

int main (void){
	int n, a, d, h;
	scanf("%d%d%d%d",&n,&a,&d,&h);
	for(int i = 0; i < n; i++){
		reading(i);
	}
	printf("%c\n",vai(0,0,n,a,d,h));
	return 0;
}
