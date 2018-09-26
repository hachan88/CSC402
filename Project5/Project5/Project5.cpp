/*
 File Name: Project5.cpp
 Author: Hayato Hiroura
 Course: CSC 402
 Date: 4/15/2018
 */

#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <string>
#include <map>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

#pragma once

using namespace std;

//Use a struct declared at file scope called ItemInfo as the representation of the items in the Catalog map
struct ItemInfo{
  string description;
  double price;
  double weight;
  
  ItemInfo(string d = "Item not found", double p = 0.00, double w = 0.00){
    description = d;
    price = p;
    weight = w;
  }
};

//Create typedefs at file scope for the catalog and order entities
typedef map<string, ItemInfo> Catalog;
typedef map<string, int> Order;

//forward declaration
void readCatalog(Catalog& catalog, const string& fileName)throw(runtime_error);
void printCatalog( const Catalog& catalog );
ItemInfo getItemData( const Catalog& catalog, const string& sku );
void displayOrderItems( const Order& order, const Catalog& catalog );
void addItem( Order & order, const Catalog& catalog, const string& sku, int quantity )throw (logic_error);
void removeItem( Order & order, const string& sku, int quantity )throw (logic_error);
void displayOrderSummary( const Order& order, const Catalog& catalog );

int main ()
{
  // construct default Order and Catalog
  Catalog catalog;
  Order order;
  
  // test readCatalog exception handling by opening a non-existent file
  try{
    readCatalog(catalog, "/Users/Hayato/Downloads/CatalogData.txt");  //open CatalogData.txt by calling readCatalog which populates the Catalog map
  }
  catch(runtime_error e){
    cout << "File: " << e.what() << endl;
    cout << endl;
  }
  
  printCatalog(catalog);  // print out the entire catalog
  
  // search for a few specific items by SKU, some found, at least one that cannot be found
  // print out the details of few items using getItemData
  string sku1 = "4123BLA";
  string sku2 = "AAA";
  ItemInfo item1 = getItemData(catalog, sku1);
  ItemInfo item2 = getItemData(catalog, sku2);
  cout << "Product description for sku " << sku1 << ": " << item1.description << endl;
  cout << "Product description for sku " << sku2 << ": " << item2.description << endl;
  cout << endl;
  

  // Add several items to order
  try{
    addItem(order, catalog, "4123BLA", 5);
    addItem(order, catalog, "4123BLU", 5);
    addItem(order, catalog, "4123GRE", 5);
  }
  catch (logic_error e){
    cout << "Added Item: " << e.what() << endl;
    cout << endl;
  }
  
  displayOrderItems(order, catalog);  // display items in the order
  
  try{
     removeItem(order, "4123BLA", 4);  // remove item(s) such that no item is completely removed
  }
  catch (logic_error e){
    cout << "Removed Item: " << e.what() << endl;
    cout << endl;
  }
 
  displayOrderItems(order, catalog);  // display items in the order to verify quantities
  
  // try to remove an item that is not in the order to test exception handling
  try{
    removeItem(order, "AAA", 1);
  }
  catch (logic_error e){
    cout << "Removed Item: " << e.what() << endl;
    cout << endl;
  }
  
  // remove all of at least one item to make sure the order no longer shows it
  try{
    removeItem(order, "4123BLA", 1);
  }
  catch (logic_error e){
    cout << "Removed Item: " << e.what() << endl;
    cout << endl;
  }
  
  displayOrderItems(order, catalog);  // display items in the order
  
  displayOrderSummary(order, catalog); // display the order summary
  
  cin.get();
  return 0;
}

// reads the input file and creates the catalog; throws a runtime_error if the file cannot be opened
void readCatalog(Catalog& catalog, const string& fileName) throw (runtime_error){
  ifstream file;  //creating the ifstream object from the input file
  file.open(fileName);
  if(file.fail()){
    throw runtime_error("File couldn't be opened");
  }
  
  string str = "";
  while(getline(file, str)){
    vector<string> tokens;
    stringstream ss(str);
    string tmp = "";
    
    while( getline( ss, tmp, ':' ) ) {  // : as separator
      tokens.push_back( tmp );  // turn the string into a series of tokens stored in a vector of strings called tokens
    }
    //use the strtod  function of the C standard library to convert the  C++ string values to doubles
    ItemInfo item(tokens[1], stod(tokens[2], NULL), stod(tokens[3], NULL));
    catalog.insert(make_pair(tokens[0], item));
  }
}

// prints the SKU, description, price, and weight of every item in the catalog
void printCatalog( const Catalog& catalog ){
  cout << setw(10) << left << "SKU";
  cout << setw(60) << left << "Description";
  cout << setw(15) << left << "Unit Price";
  cout << setw(25) << left << "Shipping Wt. (lbs.)";
  cout << endl;
  cout << setfill('=') << setw(110) << "=" << endl;
  cout << setfill(' ');
  
  Catalog::const_iterator iterator;
  for (iterator = catalog.begin(); iterator != catalog.end(); iterator++) { // iterator->first is key and second is value
    cout << setw(10) << left << iterator->first;
    cout << setw(60) << left << iterator->second.description;
    cout << setw(15) << fixed << setprecision(2) << left << iterator->second.price;
    cout << setw(25) << fixed << setprecision(1) << left << iterator->second.weight;
    cout << endl;
  }
  cout << endl;
}

// finds a single item by SKU and returns the details as a struct
// returns a dummy struct with the description "Item not found", price 0.00, and weight 0.00 if the SKU is not in the catalog
ItemInfo getItemData( const Catalog& catalog, const string& sku ){
  ItemInfo item;
  Catalog::const_iterator iterator = catalog.find(sku); //use the find() function of the map container, which returns an iterator
  if (iterator != catalog.end()){
    item = ItemInfo(iterator->second.description, iterator->second.price, iterator->second.weight);
  }
  else{
    item = ItemInfo();
  }
  return item;
}

// Lists the SKU, description, and quantity of each type of order item
void displayOrderItems( const Order& order, const Catalog& catalog ){
  cout << setw(10) << left << "SKU";
  cout << setw(60) << left << "Description";
  cout << setw(15) << left << "Quantity";
  cout << endl;
  cout << setfill('=') << setw(85) << "=" << endl;
  cout << setfill(' ');
  
  Order::const_iterator iterator;
  ItemInfo item;
  for (iterator = order.begin(); iterator != order.end(); iterator++) {
    item = getItemData(catalog, iterator->first);
    cout << setw(10) << left << iterator->first;
    cout << setw(60) << left << item.description;
    cout << setw(15) << left << iterator->second;
    cout << endl;
  }
  cout << endl;
}

// adds item(s) to the order; throws a logic_error if the item cannot be found in the catalog
void addItem( Order & order, const Catalog& catalog, const string& sku, int quantity )throw (logic_error){
  ItemInfo item = getItemData(catalog, sku);
  if (item.description.compare("Item not found") != 0){
    Order::iterator iterator = order.find(sku);
    if (iterator != order.end()){
      iterator->second += quantity; //add
    }
    else{
      order.insert(make_pair(sku, quantity));
    }
  }
  else{
    throw logic_error("Item not found");
  }
}

// removes items(s) from the order; throws a logic_error if the item cannot be found in the order
void removeItem( Order & order, const string& sku, int quantity )throw (logic_error){
  Order::iterator iterator = order.find(sku);
  if (iterator != order.end()){
    if (quantity < iterator->second){
      iterator->second -= quantity; //remove
    }
    else{
      order.erase(sku);
    }
  }
  else{
    throw logic_error("Item not found");
  }
}

// displays the number of unique item types, the total number of items, the total cost, and the total shipping weight
void displayOrderSummary( const Order& order, const Catalog& catalog ){
  int itemTypes = 0, totalItems = 0;
  double totalCost = 0, totalWeight = 0;
  
  Order::const_iterator iterator;
  for ( iterator = order.begin(); iterator != order.end(); iterator++) {
    ItemInfo item = getItemData(catalog, iterator->first);
    itemTypes++;
    totalItems += iterator->second;
    totalCost += item.price * iterator->second;
    totalWeight += item.weight * iterator->second;
  }
  
  cout << setw(50) << left << "Order Summary";
  cout << endl;
  cout << setfill('=') << setw(85) << "=" << endl;
  cout << setfill(' ');
  cout << setw(50) << left << "Distinct Item Types: " << itemTypes << endl;
  cout << setw(50) << left << "Total number of items: " << totalItems << endl;
  cout << setw(50) << fixed << "Total Cost: " << setprecision(2) << totalCost << "$"<< endl;
  cout << setw(50) << fixed << "Total Weight: " << setprecision(1) << totalWeight << "lbs." << endl;
  cout << endl;
}


