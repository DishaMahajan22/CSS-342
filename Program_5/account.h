#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include "fund.h"
using namespace std;
class Account{
    public: 

        Account(); //initialize all funds here
        Account(int id, string first_name, string last_name);

        //overloads
        friend ostream& operator << (ostream& stream, const Account& acc); //print account and display its details

        //compare by ids
        bool operator < (const Account& acc) const;
        bool operator > (const Account& acc) const;
        bool operator <= (const Account& acc) const;
        bool operator >= (const Account& acc) const;
        bool operator == (const Account& acc) const;
        bool operator != (const Account& acc) const;

        //core functions
        void Deposit (int fund_id, int amount); //calls fund methods to undergo deposit
        bool Withdraw (int fund_id, int amount); //calls withdraw fund methods to undergo withdrawal
        void AccountHistory(); //prints transaction_history_ vector
        void AllAccountHistory(); //prints all accounts regardless of no transactions
        void GetFundHistory(int fund_id); //calls specific fund object in fund array "all_funds_" to print its private fund
        int TotalBalance(); //sum of balance in all funds
        void PrintFund(int id); //prints the fund information for a specific fund id
        void PrintAllFunds();
        bool AddFund(int id, int amount);
        bool SubtractFund(int id, int amount);
        Fund* GetFund(int id);
        //setters and getters
        int id() const; 
        bool set_id(int number); 
        string first_name(); 
        bool set_first_name(string f_name); 
        string last_name(); 
        bool set_last_name(string l_name);
        int get_fund_balance(int id);

    private: 

        int id_; 
        string first_name_;
        string last_name_;
        vector <Transaction> transaction_history_; //history for specific account
        Fund all_funds_ [8]; //create array of fund objects to store the 8 different types of funds
};

#endif