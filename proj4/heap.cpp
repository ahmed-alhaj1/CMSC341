#include<stdexcept>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

#define PARENT(i) ((i>>1))
#define RCHILD(i) (i<<1)
#define LCHILD(i) (i)
#define CAP 20

//using namespace std;

int greater_than(int x, int y ){
		return x > y;
}
//bool less_than(int x , int y){
//		return x < y;
//}

//void heapify_down(int arr[],  int pos){
	//parent = 1;
//	int large = pos;
//	int lchild = LCHILD(pos);
//	int rchild = RCHILD(pos);
	

//}
void heapify_down(int *arr , int size, int pos){
	
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


int insert(int *arr, int item, int size, int cap) {
        printf( "I am at insert item=%d, size =%d    \n", item,  size ) ;
        if(size > cap ) throw out_of_range("there is an overflow");

        if( size == 1 ){
                arr[size] = item  ;
                size++;

        }else if(size > 1 ){
		size++;
        	int pos = size-1;
      		arr[pos] = item;
        	while(pos > 1 && !!greater_than(arr[pos] , arr[PARENT(pos)])){
                	int posy = PARENT(pos);
                	int temp = arr[posy];
			arr[pos] = arr[posy];
			arr[posy] = temp; 

        	}
	}
	printf("size = %d \n", size);
	return size;
        }

void print(int *arr, int size){

	for (int i = 1 ; i < size ; i++){

		printf("size = %d, array[%d] = %d \n",size,  i, arr[i] );
	}
}


int main(){

	int *array =  new int[CAP]; //malloc(sizeof(int) * CAP);
	int size = 1;
	int sizex = 1;
	for(int i = 1 ; i < 12 ; i++){
		int x = (i < 4 && i > 0  ) ? (i + 4) : (i+1) ;
		//int y = (i % 4  == 2 && i > 0) ? (i +5) : (i + 3) ;
		
		//int y = (i % 4  == 2 ) ? (i +5) : (i + 3) ;

		(i <8) ? printf("x =%d , i = %d \t",x,  i) : printf("x= %d \t", x);
		//if (i < 8)  { 
		size = insert( array, 2*x , size, CAP);
		//sizex++;
		//}//else{ 
		//size = insert(array, i , size, CAP);}

	
	}
	printf("size = %d sizex = %d \n", size, sizex );
	print(array, size);
	
	
	
	return 0;

} 
	
