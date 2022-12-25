#include "greedy_robot.h"
#include <iostream>
#include <string>
using namespace std; 

Greedy_Robot::Greedy_Robot(int max_distance, int x, int y, int treasure_x, int treasure_y) : max_distance_(max_distance), start_{x,y}, end_{treasure_x, treasure_y} {
    answer_="";
    paths_=0;
    if (max_distance_ <= 0){
        cout<< "No possible movement"<<endl;
    } else{
        ShortestPossibleDistance(start_.x, start_.y);
    }
}

int Greedy_Robot::max_distance(){
    return max_distance_;
}

bool Greedy_Robot::set_max_distance(int distance){
    if (distance >= 0){
        max_distance_ = distance;
        return true;
    }
    return false;
}

int Greedy_Robot::paths(){
    return paths_;
}

bool Greedy_Robot::set_paths(int total){
    if (total >= 0){
        paths_ = total;
        return true;
    }
    return false;

}

void Greedy_Robot:: ShortestPossibleDistance(int start, int end){
    FindPaths(start, end, answer_);
    cout<<"Number of Paths: "<< paths_<<endl;

}
bool Greedy_Robot:: CheckIfUnique(string direction, char i){
    int counter= 1;
    int max_repeated = 1; 
    //create temporary string to count if char frequency exceeds max limit
    string temp = direction; 
    temp+=i;
    for (int j = 0; j < temp.size(); j++){
        if (temp[j] == temp[j+1] && j < temp.size()-1){
            max_repeated++;
        } else{
            if (max_repeated >= counter){
                counter = max_repeated;
            }
            max_repeated = 1;
        }
        
    }
    if (counter> max_distance_){
        return false;
    }
    return true;
}

//void because we are setting paths private variable and paths will always be set with no error thus we have no boolean return value
void Greedy_Robot::FindPaths (int x, int y, string possible_path){

    if (end_.y >y){ //move north
        if (CheckIfUnique(possible_path, 'N')){
            FindPaths(x, y+1, possible_path+'N');
        }
    }
    if (end_.x > x){ //move east because we need to move positively
        if (CheckIfUnique(possible_path, 'E')){
            FindPaths(x+1, y, possible_path+'E');
        }

    }
    if (end_.y <y){ //move north
        if (CheckIfUnique(possible_path, 'S')){
            FindPaths(x, y-1, possible_path+'S');
        }
    }
    if (end_.x < x){ //move east
        if (CheckIfUnique(possible_path, 'W')){
            FindPaths(x-1, y, possible_path+'W');
        }

    }

    if (x == end_.x && y == end_.y){
        cout<<possible_path<<endl;
        paths_+=1;
        possible_path = "";
    }
    return;
}



