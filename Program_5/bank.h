#ifndef BANK_H
#define BANK_H
#include "account.h"
#include "transaction.h"
#include <string>
#include <queue>
#include <vector>
#include "BSTree.h"
class Bank{
    public: 
        Bank();
        friend ostream& operator << (ostream& stream, const Bank& bank); //prints out BSTree values
        bool TransactionProcessor(char* file_name); 
        bool TransactionReader(char* file_name);
        void OpenAccount(Transaction& transaction); 
        void DepositFund(Transaction& transaction);
        bool WithdrawFund(Transaction& transaction);
        bool TransferFunds (Transaction& transaction);
        void AccountTransactionHistory(Transaction transaction);
        void FundTransactionHistory (Transaction transaction);

        void PrintAccounts(); 
    private:
        queue <Transaction> transactions_; 

        BSTree all_accounts; 
};
#endif