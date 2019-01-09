#include <iostream>
using namespace std ;

#include "MedianHeap.h"


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


bool lt(const int& x, const int& y) {
  return x < y ;
}


bool gt(const int& x, const int& y) {
  return x > y ;
}


int main() {
    MedianHeap<int> MH(lt,gt) ;

    for (int i = 100 ; i>75 ; i--) {
       MH.insert(i) ;
    }

    MH.dump() ;

    for (int i = 1 ; i<25 ; i++) {
       MH.insert(i) ;
    }

    MH.dump() ;

    sanityCheck(MH,lt,gt) ;
}

