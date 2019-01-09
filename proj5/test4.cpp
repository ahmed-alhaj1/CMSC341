// File: test4.cpp
//
// Robustness test with lots of inserts, finds and removes.
//

#include <iostream>
#include <cstdlib>
#include <set>
using namespace std ;

#include "HashTable.h"
#include "words.h"

bool isInSet(set<string>& S, const char * str) ;
void addToSet(set<string>& S, const char *str) ;
void removeFromSet(set<string>& S, const char *str) ;
void sanityCheck(HashTable& T, set<string> S) ;


int main() {
   HashTable T(883) ;
   set<string> S ;
   char *str ;
   int Tsize;

   // insert 900 words
   for (int i=100 ; i < 1000 ; i++) {
      T.insert(words[i]) ;  addToSet(S,words[i]) ;
   }

   // remove 100 words
   for (int i=400 ; i < 500 ; i++) {
      str = T.remove(words[i]) ;
      Tsize = T.size(0) + T.size(1) ;
      printf("i = %d Tsize = %d Ssize =%d  \n", i ,Tsize, S.size());

      free(str) ;
      removeFromSet(S,words[i]) ;
   }

   // insert 10,000 words
   for (int i=30000 ; i < 40000 ; i++) { 
      printf("I am doing insert i=%d \n", i);
      T.insert(words[i]) ;  addToSet(S,words[i]) ;
   }

   // remove 2000 words + try to remove 2000 not in table
   for (int i=28000 ; i < 32000 ; i++) {
      str = T.remove(words[i]) ;  
      free(str) ;
      removeFromSet(S,words[i]) ;
   }

   // now do 10,000 random finds
   int r ;
   int Tcount = 0 ;
   int Scount = 0 ;
   srand(843150) ;
   for (int i=0 ; i<10000 ; i++) {
      r = rand() % numWords ;
      if ( T.find(words[r]) ) Tcount++ ;
      if ( isInSet(S,words[r]) ) Scount++ ;
   }

   if (Tcount == Scount) {
      cout << "Passed random find() tests: "
           << "Tcount = " << Tcount << ", "
	   << "Scount = " << Scount << endl ;
   } else {
      cout << "***Failed random find() tests: "
           << "Tcount = " << Tcount << ", "
	   << "Scount = " << Scount << endl ;
   }

   sanityCheck(T,S) ;

   return 0 ;
}


bool isInSet(set<string>& S, const char * str) {
   set<string>::iterator it ;

   it = S.find(str) ;
   if (it != S.end() ) return true ;
   return false ;
}


void addToSet(set<string>& S, const char *str) {
   pair< set<string>::iterator, bool>  p ;

   p = S.insert(str) ;
}


void removeFromSet(set<string>& S, const char *str) {
   S.erase(str) ;
}


void sanityCheck(HashTable& T, set<string> S) {
   
   int Tsize ;
   const char * ONE = (char *) 1 ;

   // Check hash table size vs set size
   //
   if ( T.isRehashing() ) {
      Tsize = T.size(0) + T.size(1) ;
   } else {
      Tsize = T.size(0) ;
   }

   if ( Tsize == S.size() ) {
      cout << "Sets sizes are both " << Tsize << endl ;
   } else {
      cout << "Sets sizes are different:  " 
           << "T size = " << Tsize << ", "
	   << "S.size() = " << S.size() << endl ;
   }

   // Construct STL set<string> for all strings in the hash table
   //
   set<string> Tset ;
   const char *str ;

   int n = T.tableSize(0) ;
   for (int i=0 ; i < n ; i++) {
      str = T.at(i,0) ;
      if (str != NULL && str != ONE) addToSet(Tset,str) ;
   }
   if ( T.isRehashing() ) {
      n = T.tableSize(1) ;
      for (int i=0 ; i < n ; i++) {
	 str = T.at(i,1) ;
	 if (str != NULL && str != ONE) addToSet(Tset,str) ;
      }
   }

   set<string>::iterator it ; 

   int inSnotT = 0 ;
   int inTnotS = 0 ;

   for (it = S.begin() ; it != S.end() ; it++) {
      if (! isInSet(Tset, it->c_str()) ) inSnotT++ ;
   }

   for (it = Tset.begin() ; it != Tset.end() ; it++) {
      if (! isInSet(S, it->c_str()) ) inTnotS++ ;
   }

   if (inSnotT == 0 && inTnotS == 0) {
      cout << "Passed set equality test\n" ;
   } else {
      cout << "***Failed set equality test\n" ;
      cout << "   " << inSnotT << " words in set S but not in hash table T.\n" ;
      cout << "   " << inTnotS << " words in hash table T but not in set S.\n" ;
   }
}
