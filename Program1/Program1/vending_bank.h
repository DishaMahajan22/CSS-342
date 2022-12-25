#ifndef VENDING_BANK_H_ 
#define VENDING_BANK_H_ 
#include <string> 
using namespace std;

class VendingBank 
{ 
 
 public: 
  VendingBank(); 
  VendingBank(int id); 
  VendingBank(int id, int quarter, int dime, int nickel, int pennies);
  VendingBank(int id, int dime, int nickel, int pennies);  
  VendingBank(int id, int nickel, int pennies); 
  VendingBank(int id, int pennies); 
 ~VendingBank();
  //getters-setters 
  int id() const;
  int set_id(int& id); 

  int dime() const; 
  int set_dime(); 
  int get_dime_count() const;

  int nickel() const; 
  int set_nickel();
  int get_nickel_count() const;

  int quarter() const; 
  int set_quarter();
  int get_quarter_count() const; 

  int pennies() const;
  int set_pennies(); 
  int get_pennies_count() const;
  //bool to check if user entered in a valid amount and calculate this amount
  bool user_deposit(int quarters, int dimes, int nickel, int pennies) const; 

  int get_vending_total_coins() const;
  int set_vending_total_coins(); 

  void get_user_coins() const;
  //public functions

  //total change without printing every type of coin
  int total_change(int price) const;

  //total change which prints every type of coin
  void change_breakdown(int total)const; 

  bool add_coins(string coinType, int amount);
  bool take_coins(string coinType, int amount);

  friend ostream& operator << (ostream &out, VendingBank& bank);
  friend ostream& operator >> (ostream &out, VendingBank& bank);
  VendingBank& operator + (const VendingBank& bank);
  VendingBank& operator - (const VendingBank& bank);
  bool operator != (const VendingBank& bank)const;
  bool operator == (const VendingBank& bank) const;
  VendingBank& operator += (VendingBank& bank);
  VendingBank& operator -= (VendingBank& bank);
   

private: 

  int id_;
  int total_vending_coins_;
  int vending_dime_;
  int vending_nickel_;
  int vending_quarter_;
  int vending_pennies_;

  //total coint amount user has deposited in pennies
  int total_user_coins;

  //calculates for deposit function total coins user_deposit
  void calculate_user_coins(int quarters, int dimes, int nickel, int pennies);

  //breakdowns for every type of coin that can be returned from total change user can get - all these functions will be called in the change_breakdown function
  int quarter_breakdown(int total_coins) const;
  int dime_breakdown(int total_coins) const;
  int nickel_breakdown(int total_coins) const;
  int pennies_breakdown(int total_coins) const;


};
#endif