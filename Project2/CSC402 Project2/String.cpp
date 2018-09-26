/*
 File Name: String.h
 Author: Hayato Hiroura
 Course: CSC 402
 Date: 2/20/2018
 */

#define _CRT_SECURE_NO_WARNINGS

#include "String.h"
#include <iostream>

//copy constructor
String::String(const String &c){
  str = new char[strlen(c.str) + 1];
  strcpy(str, c.str);
}

//copy assignement
String& String::operator=(const String &c){
  char* p = new char[strlen(c.str) + 1];
  strcpy(p, c.str);
  delete c.str;
  str = p;

  return *this;
}

//move constructor
String::String(String &&c){
  str = c.str;
  c.str = nullptr;
}

//move assignment
String& String::operator=(String &&c){
  str = c.str;
  c.str = nullptr;
  return *this;
}

bool String::empty(){
  if(strlen(str) == 0) return 1;
  else return 0;
}

int String::find ( const String &s ){
  char* a;
  int position;
  a = strstr(str, s.str); //call strstr() to find a pointer to the first occurrence
  position = a - str;
  if(a == NULL) //strstr() returns null if there is no occurrence
    return -1;
  else return position;
}

int String::find ( const char* s ){
  char* a;
  int position;
  a = strstr(str, s); //call strstr() to find a pointer to the first occurrence
  position = a - str;
  if(a == NULL) //strstr() returns null if there is no occurrence
    return -1;
  else return position;
}

int String::compare ( const String& s ){
  if(strcmp(str, s.str) == 0) return 0; //the contents of both strings are equal
  else if(strcmp(str, s.str) < 0) return 1;   //the first character that does not match has a lower value in str than in s
  else return -1; //the first character that does not match has a greater value in str than in s
}

int String::compare ( const char* s ){
  if(strcmp(str, s) == 0) return 0; //the contents of both strings are equal
  else if(strcmp(str, s) < 0) return -1;  //the first character that does not match has a lower value in str than in s
  else return 1;  //the first character that does not match has a greater value in str than in s
}

void String::clear( ){
  int size = strlen(str); //size is length of char
  for(int i = size; i >= 0;  i--){
    str[i] = NULL;  //initialize all character
  }
}

String& String::insert ( int pos, const String& s ){
  int size = strlen(str) + strlen(s.str) + 1;
  char* temp = (char*)malloc(size); //allocate memory
  strncpy(temp, str, pos);  //copy contetns of str into temp (the part before inserting position)
  temp[pos] = '\0';
  strcat(temp, s.str);  //insert the contents
  strcat(temp, str + pos);  
  strcpy(str, temp);  //copy to str
  free(temp);
  
  return *this;
}

String& String::insert ( int pos, const char* s ){
  char* temp;
  int size = strlen(str) + strlen(s) + 1;
  temp = (char*)malloc(size); //allocate memory
  strncpy(temp, str, pos);  //copy contetns of str into temp (the part before inserting position)
  temp[pos] = '\0';
  strcat(temp, s);  //insert the contents
  strcat(temp, str + pos);
  strcpy(str, temp);  //copy to str
  free(temp);
  
  return *this;
}

ostream& operator<< ( ostream& out, const String& s){
  s.print(out);
  return out;
}




