#ifndef FUND_H 
#define FUND_H
#include "transaction.h"
#include <string>
#include <vector>
using namespace std;
class Fund{
    public: 
        Fund(); 
        Fund(int id);

        //will update the fund_history and add a transaction object every time AddBalance or SubtractBalance is called
        void UpdateFundHistory(Transaction& transaction);
        //will add to current balance variable of specific fund object in account fund array
        bool AddBalance(int amount); 
        //take away from current balance of a specific fund object in account fund array
        bool SubtractBalance(int amount);
        //prints the fund_history_ vector
        void FundHistory(); 
        //check if there even are any transactions
        bool HasFundHistory(); 
        //setters and getters
        int id(); 
        bool set_id(int id); 
        string name(); 
        bool set_name(string name);
        int balance() const; 

        //overload 
        friend ostream& operator << (ostream& stream, const Fund& acc);

    private: 
        int id_;
        string name_; 
        vector <Transaction> fund_history_;
        int balance_; 
};

#endif