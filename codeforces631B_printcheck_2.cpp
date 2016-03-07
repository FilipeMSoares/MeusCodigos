#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

const int MAXN = 100000, MAXC = 5000;
int n,m,k, vet[MAXN], mrcl[MAXC], mrcc[MAXC];
pair<int,pair<int,int> > queries[MAXN];

int main(){
    scanf("%d%d%d",&n,&m,&k);
    //printf("%d %d %d\n",n,m,k);
    int cd, idx, val;
    for(int i = 0; i < k; i++){
        scanf("%d%d%d",&cd,&idx,&val);
        //printf("%d %d %d\n",cd,idx,val);
        queries[i] = make_pair(cd,make_pair(idx-1,val));
    }
    for(int i = k-1; i >= 0; i--){
        idx = queries[i].second.first;
        if(queries[i].first == 1){
            if(!mrcl[idx]){
                for(int j = 0; j < m; j++){
                    if(vet[m*idx+j] == 0) vet[m*idx+j] = queries[i].second.second;
                }
                mrcl[idx] = queries[i].second.second;
            }
        }else{
            if(!mrcc[idx]){
                for(int j = 0; j < n; j++){
                    if(vet[m*j+idx] == 0) vet[m*j+idx] = queries[i].second.second;
                }
                mrcc[idx] = queries[i].second.second;
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ",vet[m*i+j]);
        }printf("\n");
    }
    return 0;
}
