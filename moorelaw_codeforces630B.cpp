// Example program
#include <stdio.h>
#include <iostream>
const double base = 1.000000011;

using namespace std;

double pow(double b, int e){
    if(e == 0) return 1;
    
    double result = pow(b,e/2);
    result = result*result;
    if(e % 2) result = result*b;
    return result;
}

int main(void){
    int n, t;
    scanf("%d%d",&n,&t);
    double result = n*pow(base,t);
    cout.precision(30);
    cout << fixed << result << endl;
    return 0;
}
