//algoritmo KMP string matching ou pattern matching "comentado"
//retire os '//' para poder ver o que está acontecendo na execução do programa
//link do algoritmo: http://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/
//melhor explicado: http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/

#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 10000;
int lps[MAXN];
char pat[MAXN+1], text[2*MAXN+1];

void precompLPS();

void KMPsearch(){
    precompLPS();
    int n = strlen(pat), m = strlen(text);
    int i = 0, j = 0;
    while(i < m){
        if(pat[j] == text[i]){
            //printf("igualou! i e j avancam p/ %d e %d\n", i+1, j+1);
            i++; j++;
        }
        if(j == n){
            printf("Found pattern at index %d\n", i-j);
            j = lps[j-1];
        }else if(i < m){
            if(pat[j] != text[i]){
                //printf("diferentes\n");
                if(j != 0){
                    //printf("j != 0 vai de %d p/ %d\n",j,lps[j-1]);
                    j = lps[j-1];
                }else{
                    //printf("i avanca para %d pois j = 0\n", i+1);
                    i++;
                }
            }
        }        
    }
}

void precompLPS(){
    int n = strlen(pat);
    lps[0] = 0;
    int len = 0, i = 1;
    while(i < n){
        if(pat[i] == pat[len]){
            //printf("igualou! lps[%d] = %d+1\n", i, len);
            //printf("i e len avancam para %d e %d, respectivamente\n",i+1,len+1);
            lps[i++] = ++len;
        }else{
            if(len != 0){
                //printf("(len = lps[len-1] = %d) len foi de %d ",lps[len-1],len);
                len = lps[len-1];
                //printf("para %d\n", len);
            }else{
                //printf("len = 0 e i avancou para %d\n",i+1);
                //printf("lps[%d] = 0\n",i);
                lps[i++] = 0;
            }
        }/*
        for(int i = 0; i < n; i++){
            printf(" %d",lps[i]);
        }printf("\n");*/
    }
}

int main()
{
    scanf("%s",text);
    scanf("%s",pat);
    KMPsearch();
}
