#include <iostream>
using namespace std ;

#include "MedianHeap.h"
#include "City.h"


int numItems1 = 10 ;
City cities1[10] = 
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


int numItems2 = 47 ;    // was 49 in previous verison
City cities2[47] =
{  {"Laporte", "CO", 40.62637, -105.13776, 2450, 1543},
   {"Las_Animas", "CO", 38.06667, -103.22271, 2410, 1188},
   {"Leadville", "CO", 39.25082, -106.29252, 2602, 3097},
   {"Leadville_North", "CO", 39.2576, -106.30138, 1794, 3073},
   {"Limon", "CO", 39.26388, -103.69217, 1880, 1639},
   {"Lincoln_Park", "CO", 38.42916, -105.21999, 3546, 1643},
   {"Littleton", "CO", 39.61332, -105.01665, 41737, 1631},
   {"Lochbuie", "CO", 40.00721, -104.71608, 4726, 1530},
   {"Loma", "CO", 39.19581, -108.81316, 1293, 1374},
   {"Lone_Tree", "CO", 39.55171, -104.8863, 10218, 1813},
   {"Longmont", "CO", 40.16721, -105.10193, 86270, 1519},
   {"Louisville", "CO", 39.97776, -105.13193, 18376, 1626},
   {"Loveland", "CO", 40.39776, -105.07498, 66859, 1519},
   {"Lyons", "CO", 40.22471, -105.27138, 2033, 1637},
   {"Mancos", "CO", 37.345, -108.28925, 1336, 2142},
   {"Manitou_Springs", "CO", 38.85971, -104.9172, 4992, 1938},
   {"Mead", "CO", 40.23332, -104.99859, 3405, 1525},
   {"Meeker", "CO", 40.03747, -107.91313, 2475, 1902},
   {"Meridian", "CO", 39.55166, -104.85887, 2970, 1795},
   {"Milliken", "CO", 40.32943, -104.85525, 5610, 1448},
   {"Minturn", "CO", 39.58637, -106.43086, 1027, 2396},
   {"Monte_Vista", "CO", 37.57917, -106.14808, 4444, 2336},
   {"Montrose", "CO", 38.47832, -107.87617, 19132, 1770},
   {"Monument", "CO", 39.09166, -104.87276, 5530, 2126},
   {"Mountain_Village", "CO", 37.93138, -107.85645, 1320, 2926},
   {"Nederland", "CO", 39.96138, -105.51083, 1445, 2508},
   {"New_Castle", "CO", 39.57276, -107.53644, 4518, 1706},
   {"Niwot", "CO", 40.10387, -105.17082, 4006, 1553},
   {"Northglenn", "CO", 39.88554, -104.9872, 35789, 1639},
   {"Olathe", "CO", 38.60499, -107.98229, 1849, 1633},
   {"Orchard_City", "CO", 38.82832, -107.9709, 3119, 1660},
   {"Orchard_Mesa", "CO", 39.04304, -108.55232, 6836, 1417},
   {"Ordway", "CO", 38.21806, -103.75606, 1080, 1314},
   {"Ouray", "CO", 38.02277, -107.67145, 1000, 2375},
   {"Pagosa_Springs", "CO", 37.26945, -107.00976, 1727, 2172},
   {"Palisade", "CO", 39.11026, -108.35092, 2692, 1441},
   {"Palmer_Lake", "CO", 39.12221, -104.9172, 2420, 2224},
   {"Paonia", "CO", 38.86832, -107.592, 1451, 1732},
   {"Parachute", "CO", 39.45192, -108.05285, 1085, 1552},
   {"Parker", "CO", 39.5186, -104.76136, 45297, 1789},
   {"Penrose", "CO", 38.425, -105.02276, 3582, 1626},
   {"Perry_Park", "CO", 39.25666, -104.99248, 1646, 1971},
   {"Platteville", "CO", 40.21498, -104.82275, 2485, 1467},
   {"Ponderosa_Park", "CO", 39.40832, -104.65108, 3232, 2037},
   {"Pueblo", "CO", 38.25445, -104.60914, 106595, 1430},
   {"Pueblo_West", "CO", 38.35, -104.72275, 29637, 1544},
   {"Rangely", "CO", 40.08748, -108.80483, 2365, 1595}
} ;


template <typename T>
void sanityCheck(MedianHeap<T>& H, bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&)) {
   T minKey, maxKey, leftKey, rightKey ;
   int minPos, maxPos, pos ;
   
   bool passed=true ;

   cout << "=====================================================\n" ;
   cout << "sanityCheck called ...\n" ;

   int maxHSize = H.maxHeapSize() ;
   int minHSize = H.minHeapSize() ;

   if ( H.size() == maxHSize + minHSize ) {
      cout << "max and min heap sizes are consistent MedianHeap::size()\n" ;
   } else {
      cout << "max and min sizes are NOT consistent with MedianHeap::size()\n" ;
   }

   if (maxHSize < minHSize + 2 && minHSize < maxHSize + 2) {
      cout << "max and min heap sizes are within 1 of each other\n" ;
   } else {
      cout << "max heap or min heap too big\n" 
           << "   max heap size = " << maxHSize << endl 
           << "   min heap size = " << minHSize << endl ;
   }

   // Check that everything in max heap < min heap
   //
   if (maxHSize > 0 && minHSize > 0) {
      T maxHroot = H.locateInMaxHeap(1) ;
      T minHroot = H.locateInMinHeap(1) ;
      if (gt(maxHroot,minHroot) ) {
        passed = false ;
	cout << "*** Root of max heap > root of min heap\n" ;
      }
   }


   cout << "Sanity Check maxHeap...\n" ;

   for (int i=1; i <= maxHSize ; i++) {
      maxKey = H.locateInMaxHeap(i) ; 

      if (2*i <= maxHSize) {  // has left child
         leftKey = H.locateInMaxHeap(2*i) ;
	 if ( gt(leftKey,maxKey) ) {  // left child bigger than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << maxKey << ", " 
		 << "left key = " << leftKey 
		 << endl ;
	 }
      }  

      if (2*i+1 <= maxHSize) {  // has right child
         rightKey = H.locateInMaxHeap(2*i+1) ;
	 if ( gt(rightKey,maxKey) ) {  // right child bigger than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << maxKey << ", " 
		 << "right key = " << rightKey 
		 << endl ;
	 }
      }  
   }  // end of for (...)


   cout << "Sanity Check minHeap...\n" ;

   for (int i=1; i <= minHSize ; i++) {
      minKey = H.locateInMinHeap(i) ; 

      if (2*i <= minHSize) {  // has right child
         leftKey = H.locateInMinHeap(2*i) ; // left child smaller than root 
	 if ( lt(leftKey,minKey) ) {  
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << minKey << ", " 
		 << "left key = " << leftKey 
		 << endl ;
	 }
      }  

      if (2*i+1 <= minHSize) {  // has right child
         rightKey = H.locateInMinHeap(2*i+1) ;
	 if ( lt(rightKey,minKey) ) {  // right child smaller than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << minKey << ", " 
		 << "right key = " << rightKey 
		 << endl ;
	 }
      }  

   }  // end of for (...)



   if (passed) {
      cout << "Passed sanityCheck().\n" ;
   } else {
      cout << "*** Failed sanityCheck().\n" ;
   }

   cout << "=====================================================\n" ;
}

int main() {

   MedianHeap<City> H1(City::smallerPopulation, City::biggerPopulation, numItems1) ;
   for(int i=0 ; i < numItems1 ; i++) {
      H1.insert(cities1[i]) ;
   }

   MedianHeap<City> *Hptr = new MedianHeap<City>(H1) ;

   MedianHeap<City> H2(City::smallerPopulation, City::biggerPopulation, numItems2) ;
   for(int i=0 ; i < numItems2 ; i++) {
      H2.insert(cities2[i]) ;
   }

   H2 = *Hptr ;

   delete Hptr ;

   cout << "\nCheck H1...\n" ;
   sanityCheck(H1,City::smallerPopulation, City::biggerPopulation) ;

   cout << "\nCheck H2...\n" ;
   sanityCheck(H2,City::smallerPopulation, City::biggerPopulation) ;

   return 0 ; 
}
