
//Ahmed Alhaj
#include "MedianHeap.h"
#include <stdio.h>
#include <cstdlib>

template <typename T>
   MedianHeap<T>::MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap ) {
	less_than = lt; 
	greater_than = gt;
	m_capacity = cap;
	m_minsize = 1;
	m_maxsize = 1;
	m_minheap  = new Heap<T>[(cap/2)+2];
	m_maxheap  = new Heap<T>[(cap/2)+2];
}

template <typename T>
   MedianHeap<T>::MedianHeap(const MedianHeap<T>& otherH){
	if(this != &otherH){
		return ;	
	}
	m_capacity = otherH.m_capacity;
	m_size = otherH.m_size;
	m_min = otherH.m_min;
	m_max = otherH.m_max;
	m_minheap = new Heap<T>[(otherH.m_capacity/2)+2];	
	m_maxheap = new Heap<T>[(otherH.m_capacity/2)+2];
		
	for (int i = 0; i < m_capacity ;i++){
		this->insert(otherH.m_minheap[i].m_data);
		this->insert(otherH.m_minheap[i].m_data); 

		}
	}

template <typename T>
   MedianHeap<T>::~MedianHeap() {
	delete [] m_minheap;
	delete [] m_maxheap;
	

}
template<typename T>

void MedianHeap<T>:: update_min_max(){
	T min =T() , max = T();
	for(int i = 0; i< m_maxsize+1; i++){
		min = (!!less_than(m_maxheap[i].m_data, m_min))  ? locateInMaxHeap(i) : m_min;
                max = (!!greater_than(m_minheap[i].m_data, m_max))?locateInMinHeap(i):   m_max;
        }
        m_min = min;
        m_max = max;
		
}

template<typename T>
Heap<T> MedianHeap<T>::create_node(T data){
	Heap<T> node = Heap<T>(data);
	return node;
}

//here at the assigment operator I am using the copy constructor 
//so when I deallocate memory I get memory loss basically I dont have to ;
//
template <typename T>
   const MedianHeap<T>& MedianHeap<T>::operator=(const MedianHeap<T>& rhs) {
	if(this != &rhs ){
		greater_than = NULL;
		less_than = NULL;
		equalTo = NULL;
		MedianHeap(*rhs);
	}
	return *this;
}

template <typename T>
   int MedianHeap<T>::size() {
	m_size = m_minsize + m_maxsize ;
	return m_size-2;
}


template <typename T>
   int MedianHeap<T>::capacity() {
	
	return m_capacity;
}
	

 //insert(): insert a elem into the heap 3edge case heap is  1- heap is empty, check data_value, balance() 
 //input : data to be insert
 //output : inserting data in the right palce keep updating the balance
 template <typename T>
   void MedianHeap<T>::insert(const T& item) {
	if(size() > capacity()+1 ) throw out_of_range("there is an overflow");
	if(m_maxsize==1) m_min = item, m_max = item;
	if(!! less_than(item, m_min)) m_min = item;
	if (!!greater_than(item, m_max)) m_max =  T(item)  ;
	Heap<T> h_node = Heap<T>(item);	
	if( size()  == 0){
		m_maxheap[m_maxsize] = h_node  ;
		m_maxsize++;
		
	}else{
		// I am using the ternary operator to say if data < m_maxheap[1].m_data : insert max else , insert_min
		(!!less_than(item , m_maxheap[1].m_data) ) ? insert_max(h_node) : insert_min(h_node);

	balance();

	}
}
  //insert_min() insert to min heap pos start at 1; 	
  template<typename T>
  void MedianHeap<T>::insert_min(Heap<T> new_node){
	m_minsize++;
 	int pos = m_minsize-1;
	m_minheap[pos] = new_node;
	while(pos !=1  && less_than( m_minheap[pos].m_data , m_minheap[PARENT(pos)].m_data))  {
		int posy = PARENT(pos);

		swap_min(pos, posy);
		pos = PARENT(pos);
	} 
}

  template<typename T>
  void MedianHeap<T>::heapify_min_up(int pos){
	 
	int small = pos;
  	small = ( pos !=1 && PARENT(pos) > 0   && less_than(m_minheap[pos].m_data, m_minheap[PARENT(pos)].m_data))  ? PARENT(pos) : small;
	if(small != pos && pos != 1 ){
		int posy = PARENT(pos);
		swap_min(pos, posy);
		heapify_min_up(posy);
		}
  	}
  template<typename T >
  void MedianHeap<T>::heapify_max_up(int pos){
	
	int large = pos;
  	large = (pos!= 1 && PARENT(pos) > 0  && less_than(m_maxheap[PARENT(pos)].m_data, m_maxheap[pos].m_data))? PARENT(pos) : large;
	if(large != pos && pos != 1){
		int posy =PARENT(pos);
		swap_max(pos,posy);
		heapify_max_up(posy);

  }
 
  }
 
  //insert_max() insert into max heap pos start at 1;
  template<typename T>
  void MedianHeap<T>::insert_max(Heap<T> new_node ){

	m_maxsize++;
	int pos = m_maxsize-1;
	m_maxheap[pos] = new_node;
	while(pos != 1 && less_than(m_maxheap[PARENT(pos)].m_data , m_maxheap[pos].m_data)){
		int posy = PARENT(pos);
		swap_max(pos, posy);
		pos = PARENT(pos);

	}
}
  // check the sizes of min_heap & max_heap if there is imbalance and pop from heap and insert to other;
  template<typename T>
  void MedianHeap<T>::balance(){
	
	if( minHeapSize() > (maxHeapSize() +1)  ){
		T data = pop_minheap();
		insert_max( data);
		    
	}
	else if(maxHeapSize() > minHeapSize() +1 ){
		T data = pop_maxheap();
		insert_min(data);
		
	}
	
}
  //getMedian(): return median 
  // uses ternary operator to set median if size of min greater max return minhea[1] else return max[1] 
  template <typename T>
  T MedianHeap<T>::getMedian(){
	if(m_maxsize==1 && m_minsize==1 ) throw out_of_range("out of range request ");
	T median = (m_minsize > m_maxsize ) ? m_minheap[1].m_data: m_maxheap[1].m_data ;
	return median;
	}

   //getMin() return min value in the haep
   // again using ternary operator to check size and return median if size is one becase
   // zero postion is empty;
   template <typename T>
   T MedianHeap<T>::getMin() {
	if(m_maxsize==1 && m_minsize==1 ) throw out_of_range("out of range request ");

	return m_min;
	}

   template <typename T>
   T MedianHeap<T>::getMax(){
	if(m_maxsize==1 && m_minsize==1 ) throw out_of_range("out of range request ");


	return m_max;
	}

   //delete runs in O((n/2) +lg(n))
   //search for the given item if exist in maxheap set in_max flag =1  if in_min set in_min flag =1
   //then I swap the position of element with last and m_size--;	
   template <typename T>
   bool MedianHeap<T>::deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&) ) {
	this->equalTo = equalTo;
	int in_max, in_min;
	int rchild, lchild, item_pos ;
	for(int i = 1 ; i < (m_maxsize+1) ; i++ ){
		in_max =0;
		in_min =0;
		lchild = LCHILD(i);
		rchild = RCHILD(i);
		if( (i <= m_maxsize) && this->equalTo( m_maxheap[i].m_data, givenItem) ){
			in_max = 1;
			item_pos= i;
			break;		
		}	
		else if(lchild <= m_maxsize && this->equalTo(m_maxheap[lchild].m_data , givenItem)){
			in_max = 1;
			item_pos = lchild;
			break;
		}
	
		else if(RCHILD(i) <= m_maxsize && this->equalTo(m_maxheap[rchild].m_data , givenItem)){
			in_max =1;
			item_pos = rchild;
			break;
		}
	
		
		if(i <= m_minsize && this->equalTo( m_minheap[i].m_data, givenItem)) {
			in_min =1;
			item_pos = i;
			break;
		}
		
		else if( lchild <= m_minsize && this->equalTo(m_minheap[lchild].m_data, givenItem)){
			in_min = 1;
			item_pos =lchild;
			break;
			
		}
		
		else if( rchild <= m_minsize && this->equalTo(m_minheap[rchild].m_data , givenItem)){
			in_min =1;
			item_pos = rchild;
			break;
		}
		
	}
	//here where the actual delete happens
	if(in_max == 1){
		int pos = item_pos;
		int parent = PARENT(pos);
		swap_max(pos, (m_maxsize-1));
		m_maxsize--;
		if( parent > 0 && greater_than(m_maxheap[pos].m_data, m_maxheap[PARENT(pos)].m_data )){
		       	heapify_max_up(pos);
			       
		}else{	
			//if( /*(LCHILD(pos) < m_maxsize && RCHILD(pos) < m_maxsize) &&*/ (  less_than(m_maxheap[pos].m_data, m_maxheap[LCHILD(pos)].m_data) || less_than(m_maxheap[pos].m_data, m_maxheap[LCHILD(pos)].m_data)) ){

			heapify_down_max(pos);
			//}
		}
		balance();
		update_min_max();	
		return true; 
			}
	
	if(in_min == 1){
		int pos = item_pos;
		int parent = PARENT(pos);
		swap_min(pos, m_minsize-1 );
		m_minsize--;
		if( parent > 0 &&  less_than( m_minheap[pos].m_data, m_maxheap[PARENT(pos)].m_data)) {
			heapify_min_up(pos);
			
		}else{
			//if( (LCHILD(pos) < m_minsize && RCHILD(pos) < m_minsize ) && */(greater_than(m_minheap[pos].m_data, m_minheap[LCHILD(pos)].m_data) || greater_than(m_minheap[pos].m_data, m_minheap[RCHILD(pos)].m_data)) ){
			heapify_down_min(pos);
			//}
		}
		balance();
		return true;	
	}

	
		return false;
		
	

	}
  //dump(): print the data inside minheap and maxheap; 
  // I am using shit operator to divivd just in case u are confuse;
  template <typename T>
   void MedianHeap<T>::dump(){
	cout <<"... MedianHeap::dump() ..." <<endl;
        cout <<"------------Max Heap------------"<<endl;
        cout << "size = " << m_maxsize -1<<" capacity = " << (m_capacity >> 1)+2 << endl;
        for(int  j = 1  ; j < m_maxsize ; j++){
                cout << "Heap[" << j << "] = (" << m_maxheap[j].m_data << ")"<< endl;

        }
        cout <<"------------Min Heap------------"<<endl;
        cout << "size = " << m_minsize-1 <<" capacity = " <<(m_capacity >> 1) +2 << endl;
        for(int j= 1 ;  j < m_minsize  ; j++ ){
                cout << "Heap[" << j << "] = (" << m_minheap[j].m_data << ")"<< endl;



	}
	cout <<" ----------------------------------" << endl;
	cout <<"min      = " << getMin() << endl;
	cout <<"median   = " << getMedian() << endl;
	cout <<"max      = " << getMax() << endl;
  } 

  template <typename T>
   int MedianHeap<T>::maxHeapSize() {
	return m_maxsize-1 ;
	}

   template <typename T>
   int MedianHeap<T>::minHeapSize(){
	return m_minsize-1 ;

		
	}
   // I am using as subtool for balancing the heap
   // pop the first element  of min_heap and it heapify_down;
   template<typename T>
   T MedianHeap<T>::pop_minheap(){
		if(!minHeapSize())throw underflow_error("min heap is empty ");
		T data = m_minheap[1].m_data;
		m_minheap[1] = m_minheap[m_minsize-1];
		m_minsize--;
		heapify_down_min(1);
		
		return data;
	}
   //pop the first elem in the max heap and it heapify_down;
   template<typename T>
   T MedianHeap<T>::pop_maxheap(){
		if(!maxHeapSize()) throw underflow_error("max heap is empty ");
		T data = m_maxheap[1].m_data; 
		m_maxheap[1] = m_maxheap[m_maxsize-1];
		m_maxsize--;
		heapify_down_max(1);
		
		return data;
	}
   // heapify_down() run recursivly till both child greater root (my logic childs not less than root) pos_elem which mean its the root;
   //also I am using the ternary operator to say if lessthan set small = this child else set small = small ; or keep it the same
   template<typename T>
   void MedianHeap<T>::heapify_down_min(int pos){
	int small =pos;
	
	int lchild  =  LCHILD(pos);
	int rchild =  RCHILD(pos);
	small = ( lchild < m_minsize && less_than(m_minheap[lchild].m_data , m_minheap[small].m_data)) ? lchild : small;
	small = ( rchild < m_minsize && less_than(m_minheap[rchild].m_data ,  m_minheap[small].m_data)) ? rchild : small;
	if(pos != small ){
		swap_min(pos, small);
		heapify_down_min(small);

	}
	//return true ;
}


    // heapify_down_max : same logic as above;
    // again to using ternary oeprator as above.
    template<typename T>
    void MedianHeap<T>::heapify_down_max(int pos){
	if(m_maxsize == 0 ) throw underflow_error("wrong range");
	int lchild = LCHILD(pos) ;
	int rchild = RCHILD(pos);
	int large = pos;
	large =  (lchild < m_maxsize && less_than(m_maxheap[large].m_data ,  m_maxheap[lchild].m_data))? lchild :large ; 		
	large = (rchild < m_maxsize && less_than( m_maxheap[large].m_data , m_maxheap[rchild].m_data)) ?rchild : large  ;
	if( pos != large){
		 swap_max(pos, large);
		 heapify_down_max(large);
		 
	}
	//return true;


	}  
   //locateInMaxHeap () return the location of the minheap;
   template <typename T>
   T MedianHeap<T>::locateInMaxHeap(int pos){
		return m_maxheap[pos].m_data;
	}
   //lcoateInMaxHeap() retur the location of the maxheap;
   template <typename T>
   T MedianHeap<T>::locateInMinHeap(int pos){
		return m_minheap[pos].m_data;
	}
		

  // swap_min(): swap data in the minheap;
  template <typename T>
  void MedianHeap<T>::swap_min(int pos_x, int pos_y){
        Heap<T> curr;
        curr = m_minheap[pos_x];
        m_minheap[pos_x] = m_minheap[pos_y];
        m_minheap[pos_y] = curr;

}


// swap_max(): swap data in the max heap;
  template <typename T>
  void MedianHeap<T>::swap_max(int pos_x, int pos_y){
        Heap<T> curr;
        curr = m_maxheap[pos_x];
        m_maxheap[pos_x] = m_maxheap[pos_y];
        m_maxheap[pos_y] = curr;
}


