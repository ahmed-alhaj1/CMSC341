#include <iostream>
using namespace std ;

#include "MedianHeap.h"

#include "City.h"

// global array of cities

int numItems = 10 ;

City cities[10] = 
{  {"Akutan", "AK", 54.13556, -165.77306, 1027, 51},
   {"Anchor_Point", "AK", 59.77667, -151.83139, 1930, 39},
   {"Anchorage", "AK", 61.21806, -149.90028, 291826, 31},
   {"Badger", "AK", 64.8, -147.53333, 19482, 144},
   {"Barrow", "AK", 71.29058, -156.78872, 4212, 3},
   {"Bear_Creek", "AK", 60.16417, -149.395, 1956, 33},
   {"Bethel", "AK", 60.79222, -161.75583, 6080, 1},
   {"Big_Lake", "AK", 61.52139, -149.95444, 3350, 44},
   {"Butte", "AK", 61.54222, -149.03333, 3246, 28},
   {"Cohoe", "AK", 60.36861, -151.30639, 1364, 17}
} ;

int main() {
   string cityName, state ;
   

   // Declare MedianHeap of City pointers
   //
   MedianHeap<City> PopH (City::smallerPopulation, City::biggerPopulation, 30) ;
   MedianHeap<City> ElevH (City::smallerElevation, City::biggerElevation, 30) ;


   // Add items to MedianHeaps
   //
   for (int i=0 ; i < numItems ; i++) {
      PopH.insert(cities[i]) ;
      ElevH.insert(cities[i]) ;
   }

   
   cout << "\n\n Dump of Population MedianHeap\n" ;
   PopH.dump() ;

   cout << "\n\n Dump of Elevation MedianHeap\n" ;
   ElevH.dump() ;


   // Test deleteItem() with Population MedianHeap
   //

   City item1 = {"Anchorage", "AK"} ;
   bool found ;

   found = PopH.deleteItem(item1,City::sameCity) ;
   if (found) {
      cout << "Found and delted:\n" << item1 << endl ;
   } else {
      cout << "Did not delete:\n" << item1 << endl ;
   }

   // Do another deletion, but this time from the Elevation MedianHeap
   //
   City item2 = {"Bear_Creek", "AK"} ;

   found = ElevH.deleteItem(item2, City::sameCity) ;
   if (found) {
      cout << "Found and delted:\n" << item2 << endl ;
   } else {
      cout << "Did not delete:\n" << item2 << endl ;
   }

   // Take a look at both MedianHeaps after deletion:
   //
   cout << "\n\n Dump of Population MedianHeap (after deleting Anchorage, AK)\n" ;
   PopH.dump() ;

   cout << "\n\n Dump of Elevation MedianHeap (after deleting Bear_Creek, AK)\n" ;
   ElevH.dump() ;

   return 0 ;
}
