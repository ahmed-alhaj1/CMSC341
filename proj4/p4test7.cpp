// File: p4test7.cpp
//
// UMBC CMSC 341 Fall 2017 Project 4
//
// Timing run
//

#include <iostream>
#include <cstdlib>
using namespace std ;

#include "MedianHeap.h"

bool lt(const int& x, const int& y) {
  return x < y ;
}

bool gt(const int& x, const int& y) {
  return x > y ;
}


int main(int argc, char *argv[]) {

    if (argc < 2) {
       cout << "Usage: " << argv[0] << " reps\n" ; 
       return 1 ;
    }

    // number of repetitions from the command line
    //
    int reps = atoi(argv[1]) ;

    MedianHeap<int> MH(lt,gt,250*reps) ;
    int checkMin = 0 ;
    int checkMed = 0 ;
    int checkMax = 0 ;

    int val = 0 ;

    for (int i=0 ; i < reps ; i++) {
        val += 1000 ;

	for (int j=0 ; j < 57 ; j++) {
	   MH.insert(val - j) ;
	   checkMin = 37 * checkMin + MH.getMin() ;
	   checkMed = 53 * checkMed + MH.getMedian() ;
	   checkMax = 19 * checkMax + MH.getMax() ;
	}

	for (int j=0 ; j < 57 ; j++) {
	   MH.insert(val + j) ;
	   checkMin = 37 * checkMin + MH.getMin() ;
	   checkMed = 53 * checkMed + MH.getMedian() ;
	   checkMax = 19 * checkMax + MH.getMax() ;
	}

	for (int j=0 ; j < 57 ; j++) {
	   MH.insert(val - 3 * j) ;
	   checkMin = 37 * checkMin + MH.getMin() ;
	   checkMed = 53 * checkMed + MH.getMedian() ;
	   checkMax = 19 * checkMax + MH.getMax() ;
	}

	for (int j=0 ; j < 57 ; j++) {
	   MH.insert(val + 3 * j) ;
	   checkMin = 37 * checkMin + MH.getMin() ;
	   checkMed = 53 * checkMed + MH.getMedian() ;
	   checkMax = 19 * checkMax + MH.getMax() ;
	}
    }

    cout << "checkMin = " << checkMin << endl ;
    cout << "checkMed = " << checkMed << endl ;
    cout << "checkMax = " << checkMax << endl ;
    
}

