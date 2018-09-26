/*
 File Name: Comparable.h
 Author: Hayato Hiroura
 Course: CSC 402
 Date: 3/24/2018
 */
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>

using namespace std;

template <typename T>
class Comparable
{
  /* Document the assumptions being made about T in this class
   */
public:
  // For reasons which will become clear later, there is no suitable
  //   default parameter to create a default constructor
  //Comparable( const T& initValue )
  //: value( initValue )    { }
  
  // However, if we assume one more thing about T, we can provide
  //   a default parameter to the constructor above.
  //   If you get everything else working, give it a try
  Comparable( const T& initValue = T() ) :  value( initValue ) { } //default constructor
  
  Comparable( const Comparable &rhs) : value( (rhs).value ) { }  //copy constructor
  
  // copy assignment operator
  const Comparable& operator=(const Comparable& rhs){
    if(this == &rhs) return *this;
    value = rhs.value;
    return *this;
  }
  
  // Implement the relational operators: <, >, ==, !=, <=, and >=
  //   without using any other member function
  bool operator==  ( const Comparable& rhs ) const { // ==operator
    return ( compare(rhs) == 0 ) ;
  }
  
  bool operator< (const Comparable& rhs) const{  // <operator
    return (compare (rhs) == -1);
  }
  
  bool operator> (const Comparable& rhs) const{  // >opearator
    return (compare (rhs) == 1);
  }
  
  bool operator!= (const Comparable& rhs) const{ // !=operator
    return !(compare (rhs) == 0);
  }
  
  bool operator<= (const Comparable& rhs) const{ // <=operator
    return (compare (rhs) <= 0);
  }
  
  bool operator>= (const Comparable& rhs) const{ // >=operator
    return (compare (rhs) >= 0);
  }
  
  // return -1 if this object < cmp, 0 if this ojbect == cmp, 1 if cmp > this object
  int compare( const Comparable & rhs ) const {
    T cmp = rhs.value;
    
    if(value < cmp) return -1;
    else if(value > cmp) return 1;
    else return 0;
  }
  
  // print is again used to assist with the external << operator
  void print( ostream & out= cout ) const
  {  out << value ; }
  
private:
  T value ;
} ;

//<< operator overload as a template function
template <typename T>
ostream& operator<< ( ostream& out, const Comparable<T>& rhs){
  rhs.print();
  return out;
};
