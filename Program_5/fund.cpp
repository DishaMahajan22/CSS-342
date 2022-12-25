#include "fund.h"
#include <iostream>
#include <string>

Fund::Fund() : id_(0), name_(""), balance_(0){}
Fund::Fund(int id) : id_(id), balance_(0){
    switch(id){
        case 0:
            name_ = "Money Market";
            break;
        case 1:
            name_ = "Prime Money Market";
            break;
        case 2:
            name_ = "Long-Term Bond";
            break;
        case 3:
            name_ = "Short-Term Bond";
            break;
        case 4:
            name_ = "500 Index Fund";
            break;
        case 5:
            name_ = "Capital Value Fund";
            break;
        case 6:
            name_ = "Growth Equity Fund";
            break;
        case 7:
            name_ = "Growth Index Fund";
            break;
    }
}

int Fund::id(){
    return id_;
} 
bool Fund::set_id(int id){
    id_ = id; 
    return true;
}
string Fund::name(){
    return name_;
}
bool Fund::set_name(string name){
    name_ = name; 
    return true;
}
int Fund::balance() const{
    return balance_;
}
bool Fund::AddBalance(int amount){
    balance_ += amount; 
    return true;
}
bool Fund::SubtractBalance(int amount){
    if (amount < 0 || balance_ - amount < 0){
        return false;
    }
    balance_ -= amount; 
    return true;
}
void Fund::UpdateFundHistory(Transaction& transaction){
    fund_history_.push_back(transaction);
}
bool Fund::HasFundHistory(){
    if (fund_history_.size() == 0){
        return false;
    }else{
        return true;
    }
}
void Fund::FundHistory(){
    for (int i = 0; i<fund_history_.size(); i++){
        cout<<fund_history_[i]<<endl;
    }
}
ostream& operator << (ostream& stream, const Fund& fund){
    stream<< "$" << fund.balance();
    return stream;
}