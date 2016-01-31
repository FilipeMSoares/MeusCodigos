#include <stdio.h>

using namespace std;

const int MAXN = 10000;
int v[MAXN];

//todos os sorts

//insertion sort
void insertionSort(int n){
	int k, j;
	for(int i = 1; i < n; i++){
		k = v[i];
		for(j = i-1; j >= 0 && v[j] > k ; j--){
			v[j+1] =  v[j];
		}
		v[j+1] = k;
	}
}

//merge sort
void intercalar(int p, int q, int r){
	int i = p, j = q, k = 0;
	while(i <= q-1 && j <= r){
		if(nums[i] < nums[j]){
			aux[k++] = nums[i++];
		}else{
			aux[k++] = nums[j++];
		}
	}
	while(i <= q-1) aux[k++] = nums[i++];
	while(j <= r) aux[k++] = nums[j++];
	for(int i = p; i <= r; i++){
		nums[i] = aux[i-p];
	}
}

void mergeSort(int begin, int end){
	if(begin == end) return ;
	int meio = (begin+end)/2;
	mergeSort(begin, meio);
	mergeSort(meio+1, end);
	intercalar(begin,meio+1,end);
}

//main
int main (){
	int n;
	int c;
	scanf("%d",&n); getchar();
	for(int i = 0; i < n; i++){
		scanf("%d",&c);
		v[i] = c;
	}getchar();
	insertionSort(n);
	for(int i = 0; i < n; i++){
		printf("%d ", v[i]);
	}printf("\n");
	return 0;
}
