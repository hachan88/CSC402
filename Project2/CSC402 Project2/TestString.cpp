/*
 File Name: TestString.cpp
 Author: Tim McCord
 Course: CSC 402
 Date: 01/01/1970
 */

// Visual Studio-specific
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "String.h"

using namespace std;

int main() {
  
  
  /* =================== REMADME ======================================
   I start with almost all of main commented out.
   As you add constructors and other functions, simply move the
   comment block characters to allow more of main to run.
   In your submitted version, all of it should run.
   ===================================================================
   */
  
  
   
   // single and no-arg constructor tests
   String str1;
   String str2("constructed with a c-string literal");
   const char* c_str { "constructed with a c-string variable" };
   String str3(c_str);
   // intializer list syntax
   String str4 { "I am str4" };
   
   String str5 { "str5 as the source of a copy" };
  
   // copy constructor
   String str6(str5);
   
   // copy = operator
   String str7;
   str7 = str6;
   
   // move constructor
   String tmp_str1{ "Source of move constructor" };
   String str8(std::move(tmp_str1));
   
   // move = operator
   String tmp_str2{ "Source of move = operator" };
   String str9;
   str9 = std::move(tmp_str2);
   
   cout << "str1: " << str1 << endl;
   cout << "str2: " << str2 << endl;
   cout << "str3: " << str3 << endl;
   cout << "str4: " << str4 << endl;
   cout << "str5: " << str5 << endl;
   cout << endl;
   
   cout << "str6 and str7 are both copies of str5: " << endl;
   cout << "str6: " << str6 << endl;
   cout << "str7: " << str7 << endl;
   cout << endl;
   
   cout << "str8 stole the contents of tmp_str1: " << endl;
   cout << "str8: " << str8 << endl;
   cout << "str9 stole the contents of tmp_str2: " << endl;
   cout << "str9: " << str9 << endl;
   cout << endl;
   
   // to test that these objects are invalid, uncomment these statements
   // cout << tmp_str1 << endl;
   // cout << tmp_str2 << endl;
   
   // length() function test
   cout << "length of str1: " << str1.length() << endl;
   cout << "length of str2: " << str2.length() << endl;
   cout << endl;
   
   // empty() function test
   cout << "str1 is empty? (1 = true): " << str1.empty() << endl;
   cout << "str2 is empty? (0 = false): " << str2.empty() << endl;
   cout << endl;
   
   // find() function tests
   cout << "str2.find(str1) returns pos: "  << str2.find(str1) << endl;
   cout << "str2.find(\"cde\") returns pos: "  << str2.find("cde") << endl;
   cout << "str2.find(\"with s\") returns pos: "  << str2.find("with a") << endl;
   cout << endl;
   
   // compare() function test
   cout << "str4.compare(str1): " << str4.compare(str1) << endl;
   cout << "str2.compare(\"constructed with c-string literal\"): "
   << str2.compare("constructed with a string literal") << endl;
   cout << "str2.compare(str3): " << str2.compare(str3) << endl;
   cout << "str3.compare(str2): " << str3.compare(str2) << endl;
   cout << endl;
   
   // clear() function test
   cout << "str4 before clear has length : " << str4.length() << endl;
   str4.clear();
   cout << "str4 after clear has length : " << str4.length() << endl;
   cout << endl;
  
  
   // insert function() tests
   cout << "str4 before insert is empty: " << str4 << endl;
   str4.insert(0, "abcdef");
   cout << "str4 after insert of abcdef at pos 0: " << str4 << endl;
   str4.insert(6, "ghijkl");
   cout << "str4 after insert of ghijkl at pos 6: " << str4 << endl;
   str4.insert(3, "zzz");
   cout << "str4 after insert of zzz at pos 3: " << str4 << endl;
  
   String str_ins("mnopqr");
   String new_str = str4.insert(15, str_ins);
   cout << "new_str after insert of a String object at pos 15 of str4: " << new_str << endl;
   cout << endl;
  
   // == operator tests
   String str10("abcde");
   String str11("abcde");
   String str12("fgh");
   
   cout << "str10: " << str10 << endl;
   cout << "str11: " << str11 << endl;
   cout << "str12: " << str12 << endl;
   cout << endl;
   
   cout << boolalpha;  // turn on true-false display
   cout << "str10 == str11 is " << (str10 == str11) << endl;
  
  cin.get();
  return 0;
}
