#include<iostream>
#include<stdexcept>
//#include<stdio.h>
#define PARENT(i) ((i>>1))
#define RCHILD(i) (i<<1)
#define LCHILD(i) (i)
#define CAP 20

using namespace std;

bool greater_than(int x, int y ){
		return x > y;
}
bool less_than(int x , int y){
		return x < y;
}

//void heapify_down(int arr[],  int pos){
	//parent = 1;
//	int large = pos;
//	int lchild = LCHILD(pos);
//	int rchild = RCHILD(pos);
	

//}
void heapify_down(int arr[], int size, int pos){
	
 // If left child is larger than root 
	int root = 1;
	int large = pos;
	int lchild = LCHILD(pos);
	int rchild = RCHILD(pos);
	 
	large = (lchild == pos ) ? large : (arr[pos] <= arr[rchild]) ? rchild : lchild ;
	
	if(arr[root] < arr[large]){
		int temp = arr[root];
		arr[large] = temp;
		heapify_down(arr ,size,  large ); 
	}
}


int insert(int arr[], int item, int size, int cap) {
        cout <<  "I am at insert "<<  endl ;
        if(size > cap ) throw out_of_range("there is an overflow");

        if( size < 2 ){
                arr[size] = item  ;
                size++;

        }else if(size > 2 ){
		size++;
        	int pos = size-1;
      		arr[pos] = item;
        	while(pos > 1 && greater_than(arr[pos] , arr[PARENT(pos)])){
                	//int posy = PARENT(pos);
                	int temp = arr[PARENT(pos)];
			arr[pos] = arr[PARENT(pos)];
			arr[PARENT(pos)] = temp; 

        	}
	}
	return size;
        }

void print(int arr[], int size){

	for (int i = 1 ; i < size ; i++){

		//printf("index = %d , array[i=%d] = %d \n", i, i, arr[i] );
	}
}


int main(){

	int array[CAP];
	int size = 1;
	for(int i = 1 ; i < 12 ; i++){
		//int x = (i < 4 && i > 0  ) ? i + 4 : i+1;
		//int y = (i % 4  == 2 && i > 0) ? (i +5) : (i + 3) ;
		//int z = ( y % x == 0  ) ? x : y;
		//(i <8) ? printf("z =%d \t", z) : printf("x = %d \t", x);
		if (i < 8 ) { insert( array, 2*i , size, CAP);
		}else{  insert(array, i , size, CAP);}

	
	}
	print(array, size);
	
	
	


} 
	
