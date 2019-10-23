#include <iostream>
#include "Customer.h"
#include "Product.h"
using namespace std;

int Customer::counter = 0; // defines and initializes


Customer::Customer(int customerID, const char name[], bool credit) :
          balance(0), numPurchased(0), id(customerID) {
     setName(name);
     setCredit(credit);
}

int Customer::getID() const { return id; }

const char* Customer::getName() const { return name; }

void Customer::setName(char const customerName[]){
     if (strlen(customerName) > 0)
        strcpy(name, customerName);
     else{
          ostringstream oss;
          counter++;
          oss << "Customer " << counter;
          strcpy(name, oss.str().c_str());
          //copies from string stream so append counter to name without problems
     }
}

bool Customer::getCredit() const { return credit; }

void Customer::setCredit(bool hasCredit){
     if(hasCredit)
          credit = true;
     else
          credit = false;
}

double Customer::getBalance() const { return balance; }

bool Customer::processPayment(double amount){
     if(amount<0)
          return false;
     else{
          balance += amount;
          return true;
     }
}

bool Customer::processPurchase(double amount, Product product){
     //credit can enable a negative balance
     if(getCredit())
          balance-=amount;
     else if(amount<0)
          return false;
     else{
          if(balance>=amount)
               balance-=amount;
          else
               return false;
     }
     //this first part does all checks for process purchase

     for(int r = 0; r<5; r++){
          if(productsPurchased[r] == product.getName())
          return true;
     }
     for(int z = 4; z>0; z--){
          strcpy(productsPurchased[z], productsPurchased[z-1]);
     }
     if(numPurchased<5)
          numPurchased++;
     strcpy(productsPurchased[0], product.getName());
     return true;
     //second part actually checks if product is in array, adds product, and shifts array accordingly
}

//outputs specifically in mimir formatting
std::ostream& operator<<(std::ostream& os, const Customer& customer) {
     os << "Customer Name: " << customer.getName() << endl;
     os << "Customer ID: " << customer.getID() << endl;
     bool creditbool = false;
     //mimir wants true or false and you cannot edit const customer so a new bool was created
     if(customer.getCredit() == 1)
          creditbool = true;
     else
          creditbool = false;
     os << "Has Credit: " << boolalpha << creditbool << endl;
     //boolalpha formats creditbool to print true or false instead of 1 or 0
     os << "Balance: " << customer.getBalance() << endl;
     customer.outputRecentPurchases(os);
     //prints out all recent purchases
     return os;
}

void Customer::outputRecentPurchases(std::ostream& os) const {
     os << "Products Purchased --" << endl;
     for(int i = 0; i<numPurchased; i++){
          os<<productsPurchased[i]<<endl;
     }
}
