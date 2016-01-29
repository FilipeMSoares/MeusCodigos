// Example program
#include <stdio.h>
#include <cmath>

using namespace std;

int powd(int b, int n){
    if(n == 0) return 1;
    if(n == 1) return b;
    int r = pow(b,n/2);
    r = r*r;
    if(n % 2) r*=b;
    return r;
}

int main()
{
    int n, e;
    scanf("%d",&n);
    e = log(n)/log(2);
    int r = powd(2,e);
    if(r*2 == n && n >= 8){ e++; r*=2; }
    //printf("%d %d\n",r,e);
    while(n > 0){
        if(n >= r){
            n-=r;
            printf("%d",e+1);
            if(n > 0) printf(" ");
        }
        r/=2;
        e--;
    }printf("\n");
}
