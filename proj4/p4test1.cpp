#include <iostream>
using namespace std ;

#include "MedianHeap.h"

bool lt(const int& x, const int& y) {
  return x < y ;
}


bool gt(const int& x, const int& y) {
  return x > y ;
}


int main() {
	MedianHeap<int> SM(lt,gt,50), MH(lt,gt,12) ;

  //  for(int i = 0; i < 23 ;i++){
//	int x = (i % 4 == 3 )? (i * 2 +1) :( i + 3);
//	int p = (i % 3 == 0 )? ((i+1) *7) : (i +3 ) ;
//	Heap<int> node = SM.create_node(p+x);
//	SM.insert_min(node);
//	SM.dump();
//	}
//	SM.dump();
//	cout <<"#######################################" << endl;
    	
    MH.insert(5) ;
    MH.dump();
    MH.insert(7) ;
    MH.dump();
    MH.insert(8);
    MH.dump();
    MH.insert(28);
    MH.dump();
    MH.insert(13) ;
    MH.dump();
    MH.insert(9) ;
    MH.dump();
    MH.insert(17) ;
    MH.dump() ;

    // test some edge cases
    MedianHeap<int> MH2(lt,gt,3) ;

    cout << "\n\nTest some edge cases:\n" ;

    MH2.insert(10) ;
    cout << "MH2.getMin() = " << MH2.getMin() << endl ;
    cout << "MH2.getMedian() = " << MH2.getMedian() << endl ;
    cout << "MH2.getMax() = " << MH2.getMax() << endl ;

    MH2.insert(20) ;
    cout << "MH2.getMin() = " << MH2.getMin() << endl ;
    cout << "MH2.getMedian() = " << MH2.getMedian() << endl ;
    cout << "MH2.getMax() = " << MH2.getMax() << endl ;

    MH2.insert(5) ;
    cout << "MH2.getMin() = " << MH2.getMin() << endl ;
    cout << "MH2.getMedian() = " << MH2.getMedian() << endl ;
    cout << "MH2.getMax() = " << MH2.getMax() << endl ;
}

