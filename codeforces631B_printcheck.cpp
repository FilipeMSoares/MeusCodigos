#include <stdio.h>
#include <iostream>
#include <iterator>
#include <map>

using namespace std;

const int MAXN = 100000, MAXM = 5000;
int n,m,k,vet[MAXN], cod = -1;
map<int,int> buf;

typedef map<int,int>::iterator mapit;

void print(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            printf("%d ",vet[m*i+j]);
        printf("\n");
    }
}

void fillLinha(int linha, int x){
    int idx;
    for(int j = 0; j < m; j++){
        idx = m*linha+j;
        vet[idx]=x;
    }
}

void fillColuna(int coluna, int x){
    int idx;
    for(int i = 0; i < n; i++){
        idx = m*i+coluna;
        vet[idx]=x;
    }
}

void load(int idx, int val){
    buf[idx] = val;
}

void unload(){
    for(mapit it = buf.begin(); it != buf.end(); it++){
        if(cod == 1){
            fillLinha(it->first,it->second);
        }else{
            fillColuna(it->first,it->second);
        }
    }
    buf.clear();
    cod = -1;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    int cd, idx, val;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) vet[i*m+j]=0;
    for(int i = 0; i < k; i++){
        scanf("%d%d%d",&cd,&idx,&val);
        if(cod == -1 || cod == cd){
            cod = cd;
            load(idx-1,val);
        }else if(cod != cd){
            unload();
            cod = cd;
            load(idx-1,val);
        }
    }
    unload();
    print();
    return 0;
}
