#ifndef BSTREE_H
#define BSTREE_H
#include "account.h"
class BSTree{ 
    private: 
        struct Node {  
            Account* p_acct; 
            Node* right; 
            Node* left; 
        }; 
        Node* root_;  
    public: 
        BSTree(); 
        ~BSTree(); //delete dynamically allocated tree accounts
        
        bool Insert(Account *account); 
        bool InsertHelper(Node* crawler, Account* account);
        // retrieve object, first parameter is the ID of the account 
        // second parameter holds pointer to found object, NULL if not found 
        bool Retrieve(const int& account_id, Account* & account) const; 
        Account* RetrieveHelper(Node* crawler, const int& id) const;
        // Delete object, first parameter is the ID of the account 
        // second parameter holds pointer to found object, NULL if not found 
        bool Delete(const int& account_id, Account* & account); 
        Node* RemoveValue(Node* curr, const int& account_id, Account*& acc, bool& success);
        Node* SmallestRHS(Node* current);
        void DeleteTree(Node* curr);

        // displays the contents of a tree instead of overload << to display
        void Display() ;  
        void DisplayHelper(Node* crawler) ; 
        void DisplayFunds(); //same thing as display, but includes a funds summary per account
        void DisplayFundsHelper(Node* crawler);
        int Size(); //represents how many accounts are open
        int SizeHelper(Node* curr);
        
}; 
#endif