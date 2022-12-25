#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <string>
using namespace std;
class Transaction{
    public:
        Transaction();
        Transaction(char type, int account_number, string first_name, string last_name); //open acc trans
        Transaction(char type, int account_number, int fund_type, int amount); // deposit and withdraw trans
        Transaction(char type, int account_number, int fund_type, int transfer_account, int transfer_fund, int amount); // transfer
        Transaction(char type, int account_number, int fund_type); //find fund trans
        Transaction(char type, int account_number);  //find acc trans

        friend ostream& operator <<(ostream& stream, const Transaction& trans); 
        //setters and getters for private variables
        char type() const;
        void set_type(char letter);
        int account_number() const;
        bool set_account_number(int number);
        string first_name() const;
        void set_first_name(string f_name);
        string last_name() const;
        void set_last_name(string l_name);
        int fund_id() const;
        bool set_fund_id(int id);
        int amount() const;
        bool set_amount(int number);
        int transfer_account_id() const; 
        bool set_transfer_account_id(int id);
        int transfer_fund() const; 
        bool set_transfer_fund(int type);
        string error () const; 
        void set_error();
        int size() const; 
    private:
        char type_; 
        int account_number_;
        string first_name_; string last_name_, error_; 
        int fund_id_, amount_, transfer_account_id_, transfer_fund_, size_; 

};

#endif