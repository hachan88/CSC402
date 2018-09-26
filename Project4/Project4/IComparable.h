/*
 File Name: IComparable.h
 Author: Hayato Hiroura
 Course: CSC 402
 Date: 3/6/2018
 */

#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>

using namespace std;

class IComparable{  //implement interface
public:
  
  virtual ~IComparable(){}; //destructor
  
  virtual const IComparable& operator= (const IComparable & rhs) = 0;
  
  virtual int compare( const IComparable& icmp ) const = 0;
  
  virtual void print( ostream& out= cout ) const = 0;
  
  virtual bool operator==  ( const IComparable& rhs ) const { // ==operator
    return ( compare(rhs) == 0 ) ;
  }
  
  virtual bool operator< (const IComparable& rhs) const{  // <operator
    return (compare (rhs) == -1);
  }
  
  virtual bool operator> (const IComparable& rhs) const{  // >opearator
    return (compare (rhs) == 1);
  }
  
  virtual bool operator!= (const IComparable& rhs) const{ // !=operator
    return !(compare (rhs) == 0);
  }
  
  virtual bool operator<= (const IComparable& rhs) const{ // <=operator
    return (compare (rhs) <= 0);
  }
  
  virtual bool operator>= (const IComparable& rhs) const{ // >=operator
    return (compare (rhs) >= 0);
  }
};

//derived class
class Integer : public IComparable{
private:
  int value;  //data member is simple primitive type
  
public:
  
  // default and single arg constructor
  Integer( const int i= 0) : value(i) { }
  
  // copy constructor for stack-based Integers
  Integer(const Integer& rhs) : value((rhs).value) { }
  
  // copy assignment operator for stack-based Integers
  Integer & operator=(const Integer& rhs){
    if(this == &rhs) return *this;
    value = rhs.value;
    return *this;
  }
  
  // copy constructor for IComparable references
  Integer(const IComparable& rhs) : value(dynamic_cast<const Integer &>(rhs).value) {   }
  
  // copy assignment operator for IComparable references
  IComparable &operator=(const IComparable& rhs){
    if (this == &rhs) return *this;
    value = dynamic_cast<const Integer &>(rhs).value;
    return *this;
  }
  
  // As per the contract, compare must accept an IComparable reference
  // return -1 if this object < icmp, 0 if this ojbect == icmp, 1 if icmp > this object (see hints below)
  int compare( const IComparable & rhs ) const {
    int icmp = dynamic_cast<const Integer&>(rhs).value ;
    
    if(value < icmp) return -1;
    else if(value > icmp) return 1;
    else return 0;
  }
  
  //print() function that will be called by the external << operator overload
  void print( ostream & out =cout ) const { out << value; }
};

//derived class
class Character : public IComparable{
private:
  char value; //data member is simple primitive type
  
public:
  // default and single arg constructor
  Character( const char i = '?') : value(i)  { }
  
  // copy constructor for stack-based Character
  Character(const Character& rhs) : value((rhs).value) { }
  
  // copy assignment operator for stack-based Character
  Character & operator=(const Character& rhs){
    if(this == &rhs) return *this;
    value = rhs.value;
    return *this;
  }
  
  // copy constructor for IComparable references
  Character(const IComparable& rhs)
  : value(dynamic_cast<const Character &>(rhs).value) {   }
  
  // copy assignment operator for IComparable references
  IComparable & operator=(const IComparable& rhs){
    if (this == &rhs) return *this;
    value = dynamic_cast<const Character &>(rhs).value;
    return *this;
  }
  
  // As per the contract, compare must accept an IComparable reference
  // return -1 if this object < icmp, 0 if this ojbect == icmp, 1 if icmp > this object
  int compare( const IComparable & rhs ) const {
    int icmp = dynamic_cast<const Character&>(rhs).value ;
    
    if(value < icmp) return -1;
    else if(value > icmp) return 1;
    else return 0;
  }
  
  //print() function that will be called by the external << operator overload
  void print( ostream & out =cout ) const { out << value; }
};

ostream& operator<< ( ostream& out, const IComparable & rhs){
  rhs.print();
  return out;
};

