/*
 File Name: String.h
 Author: Hayato Hiroura
 Course: CSC 402
 Date: 2/20/2018
 */

#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class String{
private:
  char* str; //data member
 
public:
  //Implement a single-arg constructor with the default being the empty string  
  explicit String(const char* s = ""){
    str = new char[strlen(s) + 1];
    strcpy(str, s);
  }
  
  ~String() {delete [] str;}  //destructor
  
  String(const String &c);  //copy constructor
  String& operator=(const String &c); //copy assignment
  
  String(String&& c); // move constructor
  String& operator=(String&& c);  // move assignment

  //accessor that returns a count of the number of characters in the string, not including the null terminator
  int length() const { return strlen(str);}
  
  //accessor that tests if the string is empty and returns true if the string is empty (its length is 0, not including the null terminator). Otherwise, it returns false.
  bool empty();
  
  //Accessor that searches the string for the content specified in either str or s, and returns the position of the first occurrence in the string, starting from position 0. If the search string is not found, return -1
  int find ( const String &s );
  int find ( const char* s );
  
  /*accessor that compares the content of this String object to the contents of a String object or primitive string.
  The member function returns 0 if the length is the same and all the characters in the two being compared are identical,
  -1 if this String object is shorter or the first character that does not match is less in this object than in the argument,
  and a positive 1 in the opposite case*/
  int compare ( const String& s );
  int compare ( const char* s );
  
  //mutator that sets the object’s content to an empty string, erasing any previous content and thus leaving its effective length at 0 characters
  void clear( );
  
  /* extends the current string content by inserting some additional content (either String object or a c-string)
  at a specific location (pos), starting from 0. Existing content is shifted to the right.   It returns a reference to itself */
  String& insert ( int pos, const String& s );
  String& insert ( int pos, const char* s );

  
  //public member function that you can call in your operator<< implementation
  void print( ostream & out = cout) const{ out << this->str << "\n";}
  
  //return true if two Strings have the same contents
  friend bool operator==(String a, String b){return a.str == b.str;}
  
};

// Non-member function:  operator<<
ostream& operator<< ( ostream& out, const String& s);

