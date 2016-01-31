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

unsigned int indexSearch(int k, int i){
	for(unsigned int j = 0; j < docs[k].size(); j++){
		if(i == docs[k][j].first){
			return j;
		}
	}
	return -1;
}

int partida = 1, ciclo = 0;
void removerFolhas(int i){
	mrc[i] = 1;
	if(!ciclo){
		if(docs[i].size() == 1){
			int k = docs[i][0].first;
			docs[i].erase(docs[i].begin());
			docs[k].erase(docs[k].begin()+indexSearch(k,i));
			if(i == partida){
				partida = k;
				removerFolhas(k);
			}
		}else{
			for(unsigned int j = 0; j < docs[i].size(); j++){
				if(docs[i][j].second){
					if(!mrc[docs[i][j].first]){
						removerFolhas(docs[i][j].first);
					}
				}
			}
			if(docs[i].size() > 1){
				ciclo = 1;
			}else if(docs[i].size() == 1){
				removerFolhas(i);
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
	while(T--){
		leitura();
		partida = 1;
		ciclo = 0;
		while( (partida = findUnmarked() ) ) removerFolhas(partida);
		if(ciclo){
		    cout << "SIM";
		}else{
		    cout << "NAO";
		}
		cout << "\n";
	}
	return 0;
}

