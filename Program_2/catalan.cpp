#include <iostream>
#include <vector>
using namespace std; 

long Catalan (long n);

int main(int argc, char *argv[]){
    if (argc > 2 || argc <= 1){
        cout<<"Please enter one number only."<<endl;
    }else{
        long num = atoi(argv[1]);
        cout << Catalan(num) << endl;
    }
    return 0;
}
long Catalan(long n){
    if (n<1){
        return 1;
    }
    long sum = 0;
    for (int i = 0; i<n; i++){ //sigma sign in formula is represented through this loop
        sum += Catalan(i) * Catalan(n-i-1);
    }
    return sum;
}
