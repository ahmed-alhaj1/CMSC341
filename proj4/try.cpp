//#include<stdio.h>
#include <iostream> 
#include <stdexcept> 
using namespace std; 
//#define swap(x,y) do{ typeof(x) swap =x; x=y y=swap; }while(0)
#define PARENT(i) ((i-1)>> 1) 
// To heapify a subtree rooted with node i which is 
// an index in arr[]. n is size of heap 
void heapify(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest]) {
        largest = l; 
	}
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest]){
        largest = r; 
  	}
    // If largest is not root 
    if (largest != i) 
    { 
        swap(arr[i],arr[largest]); 
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    } 
} 
  
// main function to do heap sort 

void heapSort(int arr[], int n) 
{ 
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
	} 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(arr[0], arr[i]); 
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0); 
    } 
} 

int insert_min(int arr[], int data, int size, int cap=10){
	cout <<"size = " << size <<" data = " << data <<endl;
	if(size == cap ){
		cout <<"some issue heap is full " << endl;
		throw out_of_range("heap out of range");
	}
	++size;
	int i = size -1;
	arr[i] = data;
	while(i != 0 && arr[PARENT(i)] > arr[i]){
		swap(arr[i] , arr[PARENT(i)]);
		i = PARENT(i);
	
	}

	return size;
}

void printlist(int arr[] ){

	for(int i =0; i < 10; i++ ){

		cout <<"i = " << i  << " arr[i]= " << arr[i]<< endl;
	}

}

/* A utility function to print array of size n */
void printArray(int arr[], int n) 
{ 
    for (int i=0; i<n; ++i) 
        cout << arr[i] << " "; 
    cout << "\n"; 
} 
  
// Driver program 
int main() 
{ 
    int xsize =0;
    int arr[] = {12, 11, 13, 16, 6, 7, 8,5,9,3,2}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
    int list[10];
    //heapSort(arr, n); 
    for(int i= 0; i< 9 ; i++){
	int data = (i%2 == 0 && i > 4 ) ? i * 3 : arr[i];
	xsize = insert_min(list, data, xsize );
	} 
    cout << "Sorted array is \n"; 
    printArray(list, 9); 
    heapSort(arr, n);
    printArray(arr, n);
} 
