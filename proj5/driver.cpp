#include <iostream>
#include <cstdlib>
#include <set>
using namespace std ;

#include "HashTable.h"
#include "words.h"


int main() {
   HashTable T(883) ;
   set<string> S ;
   char *str ;
   int Tsize, T2size, T3size;

   // insert 900 words
   for (int i=100 ; i < 1000 ; i++) {
      T.insert(words[i]) ; 
   }

   // remove 100 words
   for (int i=400 ; i < 500 ; i++) {
      str = T.remove(words[i]) ;
      Tsize = T.size(0) + T.size(1) ;

      free(str) ;
   }

   // insert 5,000 words
   for (int i=30000 ; i < 40000 ; i++) {
      T.insert(words[i]) ;
   }

   // remove 2000 words + try to remove 2000 not in table
   for (int i=28000 ; i < 32000 ; i++) {
      str = T.remove(words[i]) ;
      free(str) ;
   }


   T.dump();
   HashTable T2 = T;

   //HashTable *T2 = new HashTable(T) ;
   HashTable *T3 = new HashTable(T2);
   HashTable T4(*T3);
   //Tsize = T.size(0) + T.size(1) ;
   T2size = T2.size(0) + T2.size(1) ;
   T3size = T3->size(0) + T3->size(1) ;
   
   printf("Tsize = %d, T2size = %d T3size =%d  \n", Tsize, T2size, T3size);
   T2.dump();
   T3->dump();
   T4.dump();
   delete T3;
   return 0;
}
