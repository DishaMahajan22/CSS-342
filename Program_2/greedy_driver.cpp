#include "greedy_robot.h"
#include <iostream>
using namespace std; 

int main(int argc, char *argv[]){
    if (argc > 6 || argc <6){
        cout<<"Arguments are not valid!"<<endl;
    }else{
        Greedy_Robot greedy(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }
    return 0;
}