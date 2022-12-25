#include "BSTree.h"
#include <fstream>
#include <iostream>
#include <stack>
BSTree:: BSTree(){ root_ = nullptr;}
BSTree::~BSTree(){
    DeleteTree(root_);
}
void BSTree::DeleteTree(Node* curr){
    if (curr == nullptr){
        return;
    }
    DeleteTree(curr->left);
    DeleteTree(curr->right);
    delete curr->p_acct;
    delete curr; 
    curr = nullptr;
    root_ = nullptr;
}
bool BSTree::Insert (Account* account){
    if (root_ == nullptr){
        root_ = new Node();
        root_->p_acct = account; 
        return true;
    } else{
        return InsertHelper(root_, account);
    }
}
int BSTree::Size(){
    if (root_ == nullptr){
        return 0;
    }
    return SizeHelper(root_);
}
int BSTree::SizeHelper(Node* curr){
    if (curr == nullptr){
        return 0;
    }
    int left = SizeHelper(curr->left);
    int right = SizeHelper(curr->right);
    return 1 + left + right;
}
bool BSTree:: InsertHelper(Node* crawler, Account* account){
    if (crawler->left == nullptr && account->id() < crawler->p_acct->id()){
        crawler->left = new Node(); 
        crawler->left->p_acct = account;
        return true;
    }
    if (crawler->right == nullptr && account->id() > crawler->p_acct->id()){
        crawler->right = new Node(); 
        crawler->right->p_acct = account;
        return true;
    }
    if (crawler->p_acct->id() == account->id()){
        cerr<< "ERROR: Account "<< account->id() << " is already open. Transaction refused."<<endl;
        return false;
    }
    if (crawler->p_acct->id() > account->id()){ //since our account is less than it must go to the left of the binary tree
        return InsertHelper(crawler->left, account);
    }
    if (crawler->p_acct->id() < account->id()){ //since our account is greater than it must go to the right of the binary tree
        return InsertHelper(crawler->right, account);
    }
    return false;
}
bool BSTree::Retrieve(const int& account_id, Account* & account) const{
    account = RetrieveHelper(root_, account_id);
    if (account == nullptr){
        return false;
    } else{
        return true;
    }
}
Account* BSTree::RetrieveHelper(Node* crawler, const int& id) const{
    if (crawler == nullptr){
        return nullptr;
    }
    if (crawler->p_acct->id() == id){
        return crawler->p_acct;
    }else if (crawler->p_acct->id() < id){
        return RetrieveHelper(crawler->right, id);
    }else{ //we can assume id id smaller than where we currently are
        return RetrieveHelper(crawler->left, id);
    }
}
void BSTree:: Display() {
    cout<<"FINAL BALANCE:"<<endl;
    if (root_ == nullptr){
        return;
    }
    DisplayHelper(root_);  
}

void BSTree:: DisplayHelper(Node* crawler) {
    if (crawler == nullptr){
        return;
    }
    DisplayHelper(crawler->left);
    crawler->p_acct->AllAccountHistory(); 
    DisplayHelper(crawler->right);
}

void BSTree:: DisplayFunds() {
    if (root_ == nullptr){
        return;
    }
    DisplayFundsHelper(root_);  
}

void BSTree:: DisplayFundsHelper(Node* crawler) {
    if (crawler == nullptr){
        return;
    }
    DisplayFundsHelper(crawler->left);
    cout<<crawler->p_acct->first_name() << " "<< crawler->p_acct->last_name()<< " " << crawler->p_acct->id()<<endl;
    crawler->p_acct->PrintAllFunds();
    DisplayFundsHelper(crawler->right);
}

bool BSTree::Delete(const int& account_id, Account* & account){ //Used Carrano textbook psuedocode for help and lecture notes  
    bool success = false; 
    root_ = RemoveValue(root_, account_id, account, success);
    return success; 
}

BSTree::Node* BSTree::RemoveValue(Node* curr, const int& account_id, Account*& acc, bool& success){
    if (curr == nullptr){
        success = false;
        return curr; 
    } else if (account_id < curr->p_acct->id()){
        curr->left = RemoveValue(curr->left, account_id, acc, success); 
    } else if (account_id > curr->p_acct->id()){
        curr->right = RemoveValue(curr->right, account_id, acc, success); 
    } else{
        if (curr->left == nullptr && curr->right == nullptr){
            acc = curr->p_acct;
            delete curr; 
            curr = nullptr; 
            success = true; 
        } else if (curr->right == nullptr){
            acc = curr->p_acct;
            Node* temp = curr; 
            curr = curr->left; 
            delete temp;
            success = true; 
        } else if (curr->left == nullptr){
            acc = curr->p_acct;
            Node* temp = curr; 
            curr = curr->right; 
            delete temp;
            success = true; 
        } else {
            acc = curr->p_acct;
            Node* temp = SmallestRHS(curr->right);
            curr->p_acct = temp->p_acct;
            curr->right = RemoveValue(curr->right, account_id, temp->p_acct, success);
            success = true; 
        }
    }
    return curr; 
}


BSTree::Node* BSTree::SmallestRHS(Node* current){
    current = current->right; 
    while(current->left != nullptr){
        current = current->left; 
    }
    return current; 
 }
