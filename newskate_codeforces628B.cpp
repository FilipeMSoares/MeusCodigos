// Example program
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 300000;
char digits[MAXN];
int tam;
long long int qntDivBy4(){
    long long int cnt = 0;
    for(int i = 0; i < tam; i++){
        if( (digits[i]-'0') % 2 == 0 ){
            if( digits[i] == '0' || digits[i] == '4' || digits[i] == '8' ) cnt++;
            if(i > 0){
                if( (2*digits[i-1]+digits[i]-(2*('0'))) % 4 == 0 ){
                    cnt+=i;
                }
            }
        }
    }
    return cnt;
}

int main(void){
    scanf("%s",digits); tam = strlen(digits);
    printf("%I64d\n",qntDivBy4());
    return 0;
}
