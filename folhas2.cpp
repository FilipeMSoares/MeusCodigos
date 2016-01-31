#include <iostream>
#include <vector>
#define MAXN 10000
using namespace std;

int ndoc, ndep;
vector< pair<int,int> > docs[MAXN+1];
int mrc[MAXN+1];

void leitura(){
	cin >> ndoc >> ndep;
	int x,y;
	for(int i = 1; i <= ndoc; i++){
		docs[i].clear();
		mrc[i] = 0;
	}
	for(int i = 0; i < ndep; i++){
		cin >> x >> y;
		docs[x].push_back(make_pair(y,1));
		docs[y].push_back(make_pair(x,0));
	}
}

int indexSearch(int k, vector<int> v){
	int u;
	for(unsigned int i = 0; i < v.size(); i++){
		u = v[i];
		for(int j = 0; j < (int) docs[k].size(); j++){
			if(u == docs[k][j].first && (docs[k][j].second)){
				return j;
			}
		}
	}
	return -1;
}

int partida = 1, ciclo = 0;
void busca(int i, vector<int> path){
	path.push_back(i);
	mrc[i] = 1;
	int u;
	for(int j = 0; j < (int) docs[i].size() && !ciclo; j++){
		if(docs[i][j].second){
			u = docs[i][j].first;
			if(indexSearch(u,path) >= 0){
				ciclo = 1;
				return ;
			}
			if(!mrc[u]){
				busca(u,path);
			}
		}
	}
}

int findUnmarked(){
	for(int i = 1; i <= ndoc; i++)
		if(mrc[i] == 0) return i;
	return 0;
}

int main(void)
{
	int T;
	cin >> T;
	vector<int> path;
	while(T--){
		leitura();
		partida = 1;
		ciclo = 0;
		while( (partida = findUnmarked() ) ) busca(partida,path);
		if(ciclo){
		    cout << "SIM";
		}else{
		    cout << "NAO";
		}
		cout << "\n";
	}
	return 0;
}
