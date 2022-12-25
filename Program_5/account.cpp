#include "account.h"
#include <fstream>
#include <iostream>
#include <string>

Account::Account() : id_(0), first_name_(""), last_name_(""){
    string fund_names[] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund"};
    for (int i =0; i < 8; i++){
         all_funds_[i].set_name(fund_names[i]);
    }
}

Account::Account(int id, string first_name, string last_name) : id_(id), first_name_(first_name), last_name_(last_name){
    string fund_names[] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund"};
    for (int i =0; i < 8; i++){
         all_funds_[i].set_name(fund_names[i]);
    }
}
ostream& operator << (ostream& stream, const Account& acc){
    stream<< "ID: "<< acc.id_<< " Name: "<< acc.first_name_ << " "<<acc.last_name_<<endl;
    return stream;
}
int Account::id() const{
    return id_;
} 
bool Account::set_id(int number){
    id_ = number;
    return true;
}
string Account::first_name(){
    return first_name_;
}
bool Account::set_first_name(string f_name){
    first_name_ = f_name;
    return true;
}
string Account::last_name(){
    return last_name_;
} 
bool Account::set_last_name(string l_name){
    last_name_ = l_name; 
    return true;
}
bool Account::AddFund(int id, int amount){
    if (id > 7 || id < 0){
        return false;
    }
    all_funds_[id].AddBalance(amount);
    return true;
}

bool Account::SubtractFund(int id, int amount){
    if (id > 7 || id < 0){
        return false;
    }
    all_funds_[id].SubtractBalance(amount);
    return true;
}

void Account::PrintFund(int id){
    if (id > 7 || id < 0){
        cout<<"invalid access"<<endl;
        return;
    }
    cout<<all_funds_[id].name()<< " : "<< all_funds_[id].balance()<<endl;
}

void Account::PrintAllFunds(){
    cout<<"All funds in account: "<<endl;
    for (int i =0; i < 8; i++){
        cout<<all_funds_[i].name()<<" : " << all_funds_[i].balance()<<endl;
    }
}

int Account::get_fund_balance(int id){
    int fund_amount = all_funds_[id].balance();
    return fund_amount;
}

void Account::AccountHistory(){
   cout<<"Transaction History for " << first_name_ <<" "<< last_name_ << " by fund."<<endl;
    for (int i = 0; i <8; i++){
        //print the type fund and the curr balance
        if (all_funds_[i].HasFundHistory()){
            cout<<all_funds_[i].name()<<": $"<< all_funds_[i].balance()<<endl;
            all_funds_[i].FundHistory();
        }
    }
    cout<<endl;
}

void Account::AllAccountHistory(){
    cout<<first_name()<< " " << last_name() << " Account ID: " << id()<<endl;
    for (int i = 0; i <8; i++){
            cout<<"    "<<all_funds_[i].name()<<": $"<< all_funds_[i].balance()<<endl;
    }
    cout<<endl;
}
Fund* Account::GetFund(int id){
    if (id<0 || id>7){
        cerr<<"ERROR: get fund id not valid"<<endl;
        return nullptr;
    } else{
        Fund* ptr = &all_funds_[id];
        return ptr;
    }
}

bool Account::operator < (const Account& acc) const{
    if (id() < acc.id()){
        return true;
    } else {
        cerr << "ID " << id() << " is not less than ID " << acc.id() << endl;
        return false;
    }
}
bool Account::operator > (const Account& acc) const{
    if (id() > acc.id()){
        return true;
    } else {
        cerr << "ID " << id() << " is not greater than ID " << acc.id() << endl;
        return false;
    }
}
bool Account::operator <= (const Account& acc) const{
    if (id() <= acc.id()){
        return true;
    } else {
        cerr << "ID " << id() << " is not less than or equal to ID " << acc.id() << endl;
        return false;
    }
}
bool Account::operator >= (const Account& acc) const{
    if (id() >= acc.id()){
        return true;
    } else {
        cerr << "ID " << id() << " is not greater than or equal to ID " << acc.id() << endl;
        return false;
    }
}
bool Account::operator == (const Account& acc) const{
    if (id() == acc.id()){
        return true;
    } else {
        cerr << "ID " << id() << " is not equal to ID " << acc.id() << endl;
        return false;
    }
}
bool Account::operator != (const Account& acc) const{
    if (id() != acc.id()){
        return true;
    }else{
        cerr << "ID " << id() << " is not not equal to ID " << acc.id() << endl;
        return false;
    }
}
