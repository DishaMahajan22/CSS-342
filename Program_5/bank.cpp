#include "bank.h"
#include "account.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
Bank::Bank(){}

bool Bank::TransactionProcessor(char* file_name){
    if (TransactionReader(file_name) == false){
        return false;
    }
    while(!transactions_.empty()){ //until transactions queue is not empty
         Transaction transaction = transactions_.front(); //always grab the first element in queue
        if (transaction.type() == 'O'){ //open account
            OpenAccount(transaction); //open transaction first line and parse through to open account
        } else if (transaction.type() == 'D'){ //desposit money into fund
            DepositFund(transaction); 
        } else if (transaction.type() == 'W'){
            WithdrawFund(transaction);
        } else if (transaction.type() == 'T'){
            TransferFunds(transaction);
        } else if (transaction.type() == 'A'){  
            AccountTransactionHistory(transaction);
        } else if (transaction.type() == 'F'){
            FundTransactionHistory(transaction);
        }
        transactions_.pop();
    }
    all_accounts.Display();
    return true;
}

bool Bank::TransactionReader(char* file_name){ //read all file transactions into queue but do not process them
    ifstream input_file;
    input_file.open(file_name);
    if (input_file.is_open()){
        string line;
        while(getline(input_file, line)){ 
            istringstream trans(line);
            char trans_type;
            trans>>trans_type;
            if (trans_type == 'O'){
                int trans_id;
                string f_name, l_name; 
                trans>> trans_id >> l_name >> f_name;
                Transaction open_trans(trans_type, trans_id, f_name, l_name);
                transactions_.push(open_trans);
            } else if (trans_type == 'D' || trans_type == 'W'){
                int trans_id, fund_id, amount; 
                trans >> trans_id >> fund_id >> amount; 
                Transaction update_trans(trans_type, trans_id, fund_id, amount);
                transactions_.push(update_trans);
            } else if (trans_type == 'T'){
                int account_id, fund_id, transfer_id, transfer_fund_id, amount;
                trans>> account_id >> fund_id >> transfer_id >> transfer_fund_id >> amount; 
                Transaction transfer_trans(trans_type, account_id, fund_id, transfer_id, transfer_fund_id, amount);
                transactions_.push(transfer_trans);
            } else if (trans_type == 'A'){
                int account_id; 
                trans>> account_id; 
                Transaction account_hist(trans_type, account_id);
                transactions_.push(account_hist);
            } else if (trans_type == 'F'){
                int account_id, fund_id; 
                trans >> account_id >> fund_id; 
                Transaction fund_hist(trans_type, account_id, fund_id);
                transactions_.push(fund_hist);
            } else{
                cerr<<"Error in pushing Transactions" <<endl;
                return false;
            }
        }
    } else{
        cout<<"failed to open file"<<endl;
        return false;
    }
    input_file.close();
    return true;
}

void Bank::OpenAccount(Transaction& transaction){
       
        int temp_id = transaction.account_number(); 
        string l_name = transaction.last_name(); 
        string f_name = transaction.first_name();
        if (temp_id < 0){
            cerr<<"ERROR: Account number cannot be negative!"<<endl;
            return;
        }
         Account* user = new Account(temp_id, f_name, l_name);
        if (!all_accounts.Insert(user)){ //if not able to insert, delete the dynamically allocated object we have created
            delete user; 
            user = nullptr;
        }
}

void Bank::DepositFund(Transaction& transaction){
    int user_id = transaction.account_number(); //store id
    int fund_num = transaction.fund_id(); //store fund type
    int amount = transaction.amount();
    if (amount < 0){
        cerr<<"ERROR: Amount deposited cannot be negative!"<<endl;
        return;
    } else if (user_id < 0){
        cerr<<"ERROR: Invalid Account Id"<<endl;
        return;
    } else if (fund_num < 0 || fund_num > 7){
        cerr<<"ERROR: Invalid fund number of "<< fund_num << endl;
        return;
    }
    Account* temp_account = nullptr;
    if (all_accounts.Retrieve(user_id, temp_account)){
        temp_account->GetFund(fund_num)->UpdateFundHistory(transaction);

        temp_account->AddFund(fund_num, amount);
    } else{
        cerr<<"ERROR: Account number with ID " << user_id << " was not found for deposit."<<endl;
    }
}

//keep in mind that money market [0] + prime money market [1] and long-term [2] + short-term [3] are linked in their respsective pairs
bool Bank::WithdrawFund(Transaction& transaction){
    int amount = transaction.amount(); 
    int account_num = transaction.account_number();
    int fund_id = transaction.fund_id();
    //preliminary error checks
    if (amount < 0){
        cerr<<"ERROR: Amount withdrawn must be positive"<<endl;
        transaction.set_error();
        return false;
    } else if (fund_id < 0 || fund_id > 7){
        cerr<<"ERROR: Fund is out of bounds"<<endl;
        transaction.set_error();
        return false;
    }
    //retrieve account for withdrawal
    Account* temp_account = nullptr; 
    if (all_accounts.Retrieve(account_num, temp_account) == false){
        cerr<< "ERROR: Not able to retrieve account ID " << account_num << endl;
        return false;
    }
    int balance = temp_account->get_fund_balance(fund_id); //amount in our current fund
    if (amount > balance){ //we are asking to withdraw more than we have in current fund
        if (fund_id == 0 || fund_id == 2 ){
            int linked_fund_balance = temp_account->get_fund_balance(fund_id + 1); //access linked fund
            if (linked_fund_balance + balance >= amount){ //check if money in linked is enough

                //take out everything from original fund
                Transaction temp_trans = transaction; 
                temp_trans.set_amount(balance);
                temp_account->SubtractFund(fund_id, balance);
                temp_account->GetFund(fund_id)->UpdateFundHistory(temp_trans);

                //take out neccessary amount from linked fund (we can re-use temp_trans)
                temp_trans.set_fund_id(fund_id + 1); 
                temp_trans.set_amount(amount-balance);
                temp_account->SubtractFund(temp_trans.fund_id(), temp_trans.amount());
                temp_account->GetFund(temp_trans.fund_id())->UpdateFundHistory(temp_trans);
                return true;
            }
        }else if (fund_id == 3 || fund_id == 1){
            int linked_fund_balance = temp_account->get_fund_balance(fund_id - 1);
            if (linked_fund_balance + balance >= amount){
                //take out everything from original fund
                Transaction temp_trans = transaction; 
                temp_trans.set_amount(balance);
                temp_account->SubtractFund(fund_id, balance);
                temp_account->GetFund(fund_id)->UpdateFundHistory(temp_trans);

                //take out neccessary amount from linked fund (we can re-use temp_trans)
                temp_trans.set_fund_id(fund_id - 1); 
                temp_trans.set_amount(amount-balance);
                temp_account->SubtractFund(temp_trans.fund_id(), temp_trans.amount());
                temp_account->GetFund(temp_trans.fund_id())->UpdateFundHistory(temp_trans);
                return true;
            } 
        } //no linked accounts
        cerr<<"ERROR: Not enough funds to withdraw " << amount << " from "<< temp_account->first_name()<< " " << temp_account->last_name() << " " << temp_account->GetFund(fund_id)->name()<<endl;
        transaction.set_error();
        temp_account->GetFund(fund_id)->UpdateFundHistory(transaction);
        return false;
    } //we have the neccessary amount in our original fund
    temp_account->SubtractFund(fund_id, amount);
    //update history
    temp_account->GetFund(fund_id)->UpdateFundHistory(transaction);
    return true;
}
bool Bank::TransferFunds(Transaction& transaction){
    int acc_id = transaction.account_number(); 
    int transfer_acc_id = transaction.transfer_account_id(); 
    
    int acc_fund = transaction.fund_id(); 
    int transfer_fund  = transaction.transfer_fund(); 

    int transfer_amount = transaction.amount(); 

    if (acc_id < 0 || transfer_acc_id < 0){
        cerr<< "ERROR: In transfer one of your ids is less than 0"<<endl;
        return false;
    } else if (acc_fund < 0 || acc_fund >8 || transfer_fund < 0 || transfer_fund > 8){
        cerr<<"ERROR: Invalid fund recorded while transfering funds"<<endl;
        return false;
    } else if (transfer_amount < 0){
        cerr<<"ERROR: Invalid amount to transfer"<<endl;
        return false;
    }

    //get both accounts which will be transferred 
    Account* temp_account = nullptr; 
    Account* transfer_temp_acc = nullptr; 

    if (all_accounts.Retrieve(acc_id, temp_account) == false){
        cerr<<"ERROR: Account " << acc_id<< " not found. Transferal refused."<<endl;
        transaction.set_error();
        //update history
        transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(transaction);
        return false;
    } else if (all_accounts.Retrieve(transfer_acc_id, transfer_temp_acc) == false){
        cerr<<"ERROR: Account " << transfer_acc_id<< " not found. Transferal refused."<<endl;
        transaction.set_error();
        //update history
        temp_account->GetFund(acc_fund)->UpdateFundHistory(transaction);
        return false;
    }

    int balance = temp_account->get_fund_balance(acc_fund); 
    //get both of the transfer funds of the accounts ex. T 1234 0 5678 0 1000 - 1234 money market 1000 gets transferred to 5678 money market
    if (transfer_amount > temp_account->get_fund_balance(acc_fund)){ // we don't have enough money to transfer 
        if (acc_fund == 0 || acc_fund == 2 ){ //check if fund is linked 
            int linked_fund_balance = temp_account->get_fund_balance(acc_fund + 1); //get linked fund account balance

            if (acc_fund + 1 == transfer_fund){ // special case if we are transferring to linked fund and dont have enough money
                //transfer as much as we can from original fund
                Transaction temp_trans = transaction; 
                temp_trans.set_amount(balance);
                temp_account->GetFund(acc_fund)->SubtractBalance(balance);
                temp_account->GetFund(acc_fund)->UpdateFundHistory(temp_trans);

                transfer_temp_acc->GetFund(transfer_fund)->AddBalance(balance); //add to transfer fund
                transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(temp_trans); //update transfer
                return true;

            } else if (linked_fund_balance + balance >= transfer_amount){ //if linked fund has enough money
                //transfer as much as we can from original fund
                Transaction temp_trans = transaction; 
                temp_trans.set_amount(balance);
                temp_account->GetFund(acc_fund)->SubtractBalance(balance);
                temp_account->GetFund(acc_fund)->UpdateFundHistory(temp_trans);

                //update the transfer in the transfer account
                transfer_temp_acc->GetFund(transfer_fund)->AddBalance(balance);
                transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(temp_trans);
                //transfer from linked
                temp_trans.set_fund_id(acc_fund + 1);
                temp_trans.set_amount(transfer_amount - balance);
                temp_account->SubtractFund(temp_trans.fund_id(), transfer_amount - balance); //subtract from linked
                temp_account->GetFund(temp_trans.fund_id())->UpdateFundHistory(temp_trans); //update linked history
                transfer_temp_acc->GetFund(transfer_fund)->AddBalance(transfer_amount-balance); //add to transfer fund
                transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(temp_trans); //update transfer
                return true;

            } else{ //failed
                cerr<<"ERROR: Not valid transfer. There is not enough money to transfer " << transfer_amount << " from "<< temp_account->first_name()<< " " << temp_account->last_name() << " " << temp_account->GetFund(acc_fund)->name()<<endl;
                transaction.set_error();
                Transaction temp_trans = transaction; 

                //update history
                temp_account->GetFund(acc_fund)->UpdateFundHistory(transaction);
                transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(transaction);
                return false;
            }
        }else if (acc_fund == 3 || acc_fund == 1){
            int linked_fund_balance = temp_account->get_fund_balance(acc_fund - 1);
            if (acc_fund - 1 == transfer_fund){
                //transfer as much as we can from original fund
                Transaction temp_trans = transaction; 
                temp_trans.set_amount(balance);
                temp_account->GetFund(acc_fund)->SubtractBalance(balance);
                temp_account->GetFund(acc_fund)->UpdateFundHistory(temp_trans);

                transfer_temp_acc->GetFund(transfer_fund)->AddBalance(balance); //add to transfer fund
                transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(temp_trans); //update transfer
                return true;

            } else if (linked_fund_balance + balance >= transfer_amount){
                //transfer as much as we can from original fund
                Transaction temp_trans = transaction; 
                temp_trans.set_amount(balance);
                temp_account->GetFund(acc_fund)->SubtractBalance(balance);
                temp_account->GetFund(acc_fund)->UpdateFundHistory(temp_trans);
                //update the transfer in the transfer account
                transfer_temp_acc->GetFund(transfer_fund)->AddBalance(balance);
                transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(temp_trans);
                //transfer from linked
                temp_trans.set_fund_id(acc_fund - 1);
                temp_trans.set_amount(transfer_amount - balance);
                temp_account->SubtractFund(temp_trans.fund_id(), transfer_amount - balance);
                temp_account->GetFund(temp_trans.fund_id())->UpdateFundHistory(temp_trans);
                transfer_temp_acc->GetFund(transfer_fund)->AddBalance(transfer_amount-balance);
                transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(temp_trans);
                return true;
 
            } else{ //not one of our linked funds
            cerr<<"ERROR: Not valid transfer. There is not enough money to transfer " << transfer_amount << " from "<< temp_account->first_name()<< " " << temp_account->last_name() << " " << temp_account->GetFund(acc_fund)->name()<<endl;
            transaction.set_error();
            //update history
            temp_account->GetFund(acc_fund)->UpdateFundHistory(transaction);
            transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(transaction);
            return false;
            }
        } else{
            cerr<<"ERROR: Not valid transfer. There is not enough money to transfer " << transfer_amount << " from "<< temp_account->first_name()<< " " << temp_account->last_name() << " " << temp_account->GetFund(acc_fund)->name()<<endl;
            transaction.set_error();
            //update history
            temp_account->GetFund(acc_fund)->UpdateFundHistory(transaction);
            transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(transaction);
            return false;
        }
        
    }
    //actual transferring of the funds
        temp_account->SubtractFund(acc_fund, transfer_amount);
        transfer_temp_acc->AddFund(transfer_fund, transfer_amount); 
        //update history
        temp_account->GetFund(acc_fund)->UpdateFundHistory(transaction);
        transfer_temp_acc->GetFund(transfer_fund)->UpdateFundHistory(transaction);
        return true;
}
void Bank::AccountTransactionHistory(Transaction transaction){
   int user_id = transaction.account_number(); //store id
    Account* temp_account = nullptr;
    if (all_accounts.Retrieve(user_id, temp_account)){
        temp_account->AccountHistory();
    } else{
        cerr<<"ERROR: Cannot retrieve id "<< user_id << endl;
        return;
    }
}

void Bank::FundTransactionHistory(Transaction transaction){ //ex. F 1253 4
    int acc_id = transaction.account_number(); 
    int fund_id = transaction.fund_id(); 
    if (fund_id < 0 || fund_id > 7){
        cerr<<"ERROR: Fund ID " << fund_id << " is not valid"<<endl;
        return;
    }
    Account* temp_account = nullptr;
    if (all_accounts.Retrieve(acc_id, temp_account)){
        Fund* fund_selector = temp_account->GetFund(fund_id); 
        cout<<"Transaction History for " << temp_account->first_name() << " " << temp_account->last_name() << " " <<fund_selector->name() <<" : $"<< fund_selector->balance()<<endl;
        fund_selector->FundHistory();
        cout<<endl;
    } else{
        cerr<<"ERROR: ID "<< acc_id << " does not exist " << endl;
        return;
    }
}