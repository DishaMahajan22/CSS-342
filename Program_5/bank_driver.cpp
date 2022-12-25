#include <iostream>
#include "bank.h"
using namespace std;

int main(int argc, char* argv[]){
    if (argc <= 0){
        cout<<"Not a valid number of arguements"<<endl;
        return 1;
    }else{
        Bank bank_a; 
        if (bank_a.TransactionProcessor(argv[1]) == false){
            return 1;
        }
        return 0;
    }
}