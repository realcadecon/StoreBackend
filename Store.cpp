#include <iostream>
#include "Store.h"
#include "Product.h"
#include "Customer.h"
using namespace std;

int Store::counter = 0; // defines and initializes

Store::Store(): numProducts(0), numCustomers(0) {
     setName("");
}

Store::Store(const char name[]): numProducts(0), numCustomers(0) {
     setName(name);
}

const char* Store::getName() { return name; }

void Store::setName(const char storeName[]){
     if (strlen(storeName) > 0) {
         strcpy(name, storeName);
     }
     else {
          ostringstream oss;
          counter++;
          oss << "Store " << counter;
          strcpy(name, oss.str().c_str());
          //copies from string stream so append counter to name without problems
     }
}

bool Store::addProduct(int productID, const char productName[]){
     if(numProducts>99){
          return false;
     }
     //checks if array is full
     for(int i = 0; i<numProducts; i++){
          if((*products[i]).getID() == productID)
               return false;
               //returns false if it cannot find matching ID
     }
     Product* ptr = new Product(productID, productName);
     products[numProducts++] = ptr;
     ptr = nullptr;
     //resets the pointer so you don't delete the content in products
     delete ptr;
     //frees space on heap
     return true;
}

Product* Store::getProduct(int productID){
     for(int i = 0; i<numProducts; i++){
          if((*products[i]).getID() == productID)
               return products[i];
     }
     return nullptr;
}
// even though getProduct should be private, it helps autograding to make it public

bool Store::addCustomer(int customerID, const char customerName[], bool credit){
     if(numCustomers>99){
          return false;
     }
     //checks if array is full
     for(int i = 0; i<numCustomers; i++){
          if((*customers[i]).getID() == customerID)
               return false;
               //returns false if it cannot find matching ID
     }
     //finds specific customer
     Customer* ptr = new Customer(customerID, customerName, credit);
     customers[numCustomers++] = ptr;
     ptr = nullptr;
     //resets the pointer so you don't delete the content in products
     delete ptr;
     //frees space on heap
     return true;
}

Customer* Store::getCustomer(int customerID){
     for(int i = 0; i<numCustomers; i++){
          if((*customers[i]).getID() == customerID)
               return customers[i];
     }
     //finds specific customer
     return nullptr;
     //returns nullptr if customer cannot be found
}
// even though getCustomer should be private, it helps autograding to make it public

bool Store::takeShipment(int productID, int quantity, double cost){
     if(quantity<0 || cost<0){
          return false;
     }
     int x = -1;
     for(int i=0; i<numProducts; i++){
          if((*products[i]).getID() == productID)
               x = i;
     }
     if(x == -1)
          return false;
     //returns false if product isn't found
     (*products[x]).addShipment(quantity, cost);
     return true;
}

bool Store::sellProduct(int customerID, int productID, int quantity){
     int x = -1;
     for(int i=0; i<numProducts; i++){
          if((*products[i]).getID() == productID)
               x = i;
     }
     //finds specifc product
     int z = -1;
     for(int i=0; i<numCustomers; i++){
          if((*customers[i]).getID() == customerID)
               z = i;
     }
     //finds specific customer
     if(z==-1 || x==-1)
          return false;
     //returns false if customer or product isn't found
     double amount = quantity * (*products[x]).getPrice();
     if((*customers[z]).processPurchase(amount, (*products[x]))) {}
     else{
          return false;
     }
     return (*products[x]).reduceInventory(quantity);
}

bool Store::takePayment(int customerID, double amount){
     int x = -1;
     for(int i=0; i<numCustomers; i++){
          if((*customers[i]).getID() == customerID)
               x = i;
     }
     //finds specific customer
     if(x == -1)
          return false;
     //returns false if customer isn't found
     if((*customers[x]).processPayment(amount))
          return true;
     return false;
}

void Store::outputProducts(std::ostream& os){
     for(int i = 0; i<numProducts; i++){
          os<<(*products[i])<<endl;
     }
}

void Store::outputCustomers(std::ostream& os){
     for(int i = 0; i<numCustomers; i++){
          os<<(*customers[i])<<endl;
     }
}
