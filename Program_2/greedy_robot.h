#ifndef GREEDY_ROBOT_H
#define GREEDY_ROBOT_H
#include <iostream>
#include <cstdlib>
#include <string>

struct Coordinates{
    int x;
    int y;
};
class Greedy_Robot{
    public:
        Greedy_Robot(int max_distance, int x, int y, int treasure_x, int treasure_y);

        int max_distance();
        bool set_max_distance(int distance);
        int paths();
        bool set_paths(int total);

        void ShortestPossibleDistance(int start, int end);

    private:
        int max_distance_;
        std::string answer_; //no getter or setter for this as this variable will be manipulated in function and should not be touched afterwards
        int paths_;

        Coordinates start_;
        Coordinates end_;
        bool CheckIfUnique(std::string direction, char i);
        void FindPaths(int x, int y, std::string possible_path);
};
#endif