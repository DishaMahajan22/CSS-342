#include "transaction.h"
#include <iostream>
//different types of transactions accounted for
Transaction::Transaction() : type_(0), account_number_(0), first_name_(""), last_name_(""), fund_id_(0), amount_(0), transfer_account_id_(0), transfer_fund_(0), size_(0){}
Transaction::Transaction(char type, int account_number, string first_name, string last_name) : type_(type), account_number_(account_number), first_name_(first_name), last_name_(last_name), error_(""), size_(4){}
Transaction::Transaction(char type, int account_number, int fund_type, int amount) : type_(type), account_number_(account_number), fund_id_(fund_type), amount_(amount), error_(""), size_(4){}
Transaction::Transaction(char type, int account_number, int fund_type, int transfer_account, int transfer_fund, int amount) : type_(type), account_number_(account_number), fund_id_(fund_type), transfer_account_id_(transfer_account), transfer_fund_(transfer_fund), amount_(amount), error_(""), size_(6){}
Transaction::Transaction(char type, int account_number, int fund_type) : type_(type), account_number_(account_number), fund_id_(fund_type), error_(""), size_(3){}
Transaction::Transaction(char type, int account_number) : type_(type), account_number_(account_number), error_(""), size_(2){}

char Transaction::type() const{
    return type_;
}
void Transaction::set_type(char letter){
    type_ = letter;
}
int Transaction::account_number() const{
    return account_number_;
}
bool Transaction::set_account_number(int number){
    if (number >= 0){
        account_number_ = number;
        return true;
    }
    return false;
}
string Transaction::first_name() const{
    return first_name_;
}
void Transaction::set_first_name(string f_name){
    first_name_ = f_name;
}
string Transaction::last_name() const{
    return last_name_;
}
void Transaction::set_last_name(string l_name){
    last_name_ = l_name;
}
int Transaction::fund_id() const{
    return fund_id_;
}
bool Transaction::set_fund_id(int id){
    if (id >= 0){    
        fund_id_ = id; 
        return true;
    }
    return false;
}
int Transaction::amount() const{
    return amount_;
}
bool Transaction::set_amount(int number){
    if (number >=0){
        amount_ = number;
        return true;
    }
    return false;
}
int Transaction::size() const{
    return size_;
}
int Transaction::transfer_account_id() const{
    return transfer_account_id_;
}
bool Transaction::set_transfer_account_id(int id){
    if (id >=0){
        transfer_account_id_ = id; 
        return true;
    } 
    return false;
}
int Transaction::transfer_fund() const{
    return transfer_fund_;
}
bool Transaction::set_transfer_fund(int type){
    if (type >=0 && type <=7){
        transfer_fund_ = type; 
        return true;
    }else{
        return false;
    }

}
string Transaction::error() const{
    return error_;
}
void Transaction::set_error(){
    error_ = "(Failed)";
}

ostream& operator <<(ostream& stream, const Transaction& trans){
    if (trans.size() == 4){ //will be deposit or withdraw
        stream<<"  "<< trans.type() << " " << trans.account_number() << " " << trans.fund_id() <<" "<< trans.amount() << " " << trans.error();
        return stream;
    } else if (trans.size() == 6){
        stream<<"  "<< trans.type() << " " << trans.account_number() << " "<< trans.fund_id() << " " << trans.transfer_account_id() << " " << trans.transfer_fund() <<" " << trans.amount()<< " " << trans.error(); 
        return stream;
    } else if (trans.size() == 3){
        stream<< "  "<< trans.type() << " " << trans.account_number() << " " << trans.fund_id()<< " " << trans.error(); 
        return stream; 
    } else if (trans.size() == 2){
        stream<<"  "<< trans.type()<< " " << trans.account_number()<< " " << trans.error();
        return stream;
    } 
    return stream;
}