#ifndef _MEDIANHEAP_H
#define _MEDIANHEAP_H

#define PARENT(i) ((i) >> 1)//  calculate the root using right shift to divid by2
#define LCHILD(i) ((i <<1) ) // left child using left shift to multiply by 2 
#define RCHILD(i) ((i <<1)+1 ) // right child using left shift again

#include<iostream>

using namespace std;
// very unnecessary I just though it is required;
template<typename T>
struct Heap{
	Heap(){};
	T m_data;
	Heap(T data): m_data(data){};
};


template<typename T> 
class MedianHeap{

public :

   MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap=100 ) ;
   MedianHeap(const MedianHeap<T>& otherH) ;
   ~MedianHeap()  ;

   const MedianHeap<T>& operator=(const MedianHeap<T>& rhs)  ;
   
   int size() ;

   int capacity() ;

   void insert(const T& item) ;
   void heapify_min_up(int pos);
   void heapify_max_up(int pos);

   T getMedian() ;
	
   T getMin() ;
	
   T getMax() ;
	
   bool deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&) ) ;
   void dump() ;
	
   int maxHeapSize() ;
	
   int minHeapSize() ;
   void update_min_max();
	
   T locateInMaxHeap(int pos) ;

   T locateInMinHeap(int pos) ;
   void balance();
	
   void insert_min(Heap<T> new_node);
   void insert_max(Heap<T> new_node);
   Heap<T> create_node(T data);
	
   void swap_min(int pos_x, int pos_y);
   void swap_max(int pos_x, int pos_y);
   void heapify_down_max(int posx);
   void heapify_down_min(int posx);
   T pop_maxheap();
   T pop_minheap();

private:
	Heap<T> *m_minheap;
	Heap<T> *m_maxheap;
	int m_minsize;
	int m_maxsize;
	int m_capacity;
	int m_size;
	T m_min;
	T m_max;
	bool (*less_than) (const T& , const T&);
	bool (*greater_than) (const T& ,  const T&);
	bool (*equalTo) (const T& , const T&);
};

#include "MedianHeap.cpp"
#endif


