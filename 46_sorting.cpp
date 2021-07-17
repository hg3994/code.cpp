/* 
Harshit Gupta | 19th January, 2019


C++ program for sorting algorithms.
http://bigocheatsheet.com/
https://www.geeksforgeeks.org/topological-sorting/

Solution: 

	Selection Sort: We 'select' the minimum element after every iteration and make an array of that.

	Insertion Sort: Pick elements one by one and 'insert' them at their correct place in the already
		sorted sequence.
	
	Bubble Sort: This works by repeatedly swapping the adjacent elements if they are in wrong order.

	Merge Sort: divides input array in two halves, calls itself for the two halves and then merges 
		the two sorted halves. Merge Sort is useful for sorting linked lists in O(nLogn) time.
		
	Quick Sort: picks an element as pivot and partitions the given array around the picked pivot 
		such that all the elements lesser than the pivot element are placed to its left and all the 
		elements greater than it are placed to its right.
		


================================================================================
Algorithm	|				Time Complexity					|	Space Complexity
================================================================================				
			|	Best			Average			Worst		|	Worst
================================================================================				
Quicksort		Ω(n log(n))		Θ(n log(n))		O(n^2)			O(log(n))
Mergesort		Ω(n log(n))		Θ(n log(n))		O(n log(n))		O(n)
Heapsort		Ω(n log(n))		Θ(n log(n))		O(n log(n))		O(1)
Bubble Sort		Ω(n)			Θ(n^2)			O(n^2)			O(1)
Insertion Sort	Ω(n)			Θ(n^2)			O(n^2)			O(1)
Selection Sort	Ω(n^2)			Θ(n^2)			O(n^2)			O(1)


Timsort			Ω(n)			Θ(n log(n))		O(n log(n))		O(n)
Tree Sort		Ω(n log(n))		Θ(n log(n))		O(n^2)			O(n)
Shell Sort		Ω(n log(n))		Θ(n(log(n))^2)	O(n(log(n))^2)	O(1)
Bucket Sort		Ω(n+k)			Θ(n+k)			O(n^2)			O(n)
Radix Sort		Ω(nk)			Θ(nk)			O(nk)			O(n+k)
Counting Sort	Ω(n+k)			Θ(n+k)			O(n+k)			O(k)
Cubesort		Ω(n)			Θ(n log(n))		O(n log(n))		O(n)

Paradigm: Sorting

*/

#include <bits/stdc++.h>
using namespace std; 

void printArr(vector<int> arr){
	int n = arr.size();
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void swap(int *xp, int *yp) {
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

void topologicalSort(vector <vector<int>> grid){
	// Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for 
	// every directed edge uv, vertex u comes before v in the ordering	
	int size = grid.size();

	// Visited array to keep track of what has already been discovered. 
	// If we don't use this, we'll get into an infinite loop.
	int visited[size] = {0};

	// A hash to store int -> char for nodes. hash[1] = 'A';	hash[2] = 'B';
	unordered_map<int, char> hash; 	
	for(int i=0;i<size;i++){
		hash[i] = (char)i+65;
	}

	// To store the end result of the order.
	vector<int> order;

	// Loop for all the rows of the 2D matrix of the DAG.
	for(int i=0;i<size;i++){
		// A flag variable to figure out the row which has all zeros. This would be the output.
		int flag = 0;
		int j;
		// Look out for all the columns for that specific row.
		for(j=0;j<size;j++){
			// If the grid has a 1, then it means there is an edge from i to j.
			// But we are looking for a row(i) which has all the grid[i][j] as zeros, so set flag as 1 and break;
			if(grid[i][j] == 1){
				flag = 1;
				break;
			}
		}
		// Only if the entire row [i] has zeros and has never been visited earlier, 
		// We mark it as visited. Know this is the endpoint and is inserted in the output. 
		// Mark i=-1 so that it starts over again.
		// We mark this specific colm(j) as 0 in all other rows since this node is already considered
		if(flag == 0 && visited[i]==0){
			visited[i]=1;
			order.push_back(i);
			// Mark this column as 0 in all other rows
			for(int k=0;k<size;k++){
				grid[k][i]=0;
			}
			i=-1;
		}
	}
	cout<<"START->";
	for(int i=0;i<size;i++){
		cout<<hash[order[i]]<<"->";
	}
	cout<<"END"<<endl;
}

int partitionQuickSort(vector<int> &arr, int low, int high){
	// This function takes last element as pivot, places the pivot element at its correct position in sorted
  	// array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot
	
	// Choose the last element as the pivot.
	int pivot = arr[high];

	// Take a variable which will store the index of the array before & equal to 
	// which all elements will be lesser than the pivot element
	int smaller_index = low-1;
	
	// Move from the 'low' index to 'less than' high index (since 'high' is already pivot)
	for(int i=low; i<high; i++){

		// If the element is more than the pivot, we don't do anything.
		// If the element is less than the pivot, then we increase the 'smaller_index' variable
			// since this index means all the elements before it are lesser than the pivot.
			// Automatically, the index greater than the pivot would go after the 'smaller_index'
			// We also swap the arr[i] and arr[smaller_index] in case when we have a greater element than the pivot
			// in between two smaller elements. Pivot = last element = 70. Arr = [30, 80, 10, 70]. SmallIndex=-1
			// 30 < 70, smaller_index=0, swap 30 with arr[0] => Arr = [30, 80, 10, 70]
			// 80 > 70, so do nothing => Arr = [30, 80, 10, 70].
			// 10 < 70, smaller_index=1, swap 10 with arr[1] => Arr = [30, 10, 80, 70]
		if(arr[i]<=pivot){
			smaller_index++;
			swap(&arr[i], &arr[smaller_index]);
		}
	}
	// Now place the pivot element at the correct place (smaller_index+1) so that all the elements
	// lesser than it are on its left and all the elements greater than it are on its right.
	// The array becomes [30, 10, 70, 80] now.
	swap(&arr[smaller_index+1], &arr[high]);

	// return the index of the correctly placed element so that we can call QS on both the halves.
	// These halves would look like [30, 10] and [80] since 70 is placed in its correct place.
	return smaller_index+1;
}

void quickSortUtil(vector<int> &arr, int l, int r){
	if (l < r){
		// pi is partitioning index, arr[pi] is now at right place
		int pi = partitionQuickSort(arr, l, r);

		// Call the quicksort function on both the halves.
		quickSortUtil(arr, l, pi-1);
		quickSortUtil(arr, pi, r);
	}
}

void quickSort(vector<int> arr){
	// Quick Sort is a Divide and Conquer algorithm. It picks an element as pivot and partitions 
	// the given array around the picked pivot such that all the elements lesser than the pivot element
	// are placed to its left and all the elements greater than it are placed to its right.
	// We will always pick up the last element as the 'pivot' element and then place it in its correct place
	// such that lesser are on its left, greater are on its right and then call quick sort on both the halves.
	// This way, each of the element will be placed in its correct place and the array is sorted.
	quickSortUtil(arr, 0, arr.size()-1);
	printArr(arr);
}

void merge(vector<int> &arr, int l, int m, int r){
	// Merges two sorted sub-arrays of arr[]. 
	// First sub-array is arr[l..m] 
	// Second sub-array is arr[m+1..r]
	int n1 = m-l+1;
	int n2 = r-m;
	
	// create temp arrays to compare and update 
	int L[n1], R[n2];

	// Copy data to temp arrays L[] and R[]
	for(int i=0;i<n1;i++)
		L[i] = arr[l+i];   // arr[l...]
	for(int i=0;i<n2;i++)
		R[i] = arr[m+1+i]; // arr[m+1...]

	// Merge the temp arrays back into arr[l..r]
	int i=0; // Initial index of first sub-array L[]
	int j=0; // Initial index of second sub-array R[]
	int k=l; // Initial index of merged sub-array arr[]

	// Compare the two sorted temp array and then update the arr[]
	while (i<n1 && j<n2){
		if(L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if there are any
	while(i<n1){
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if there are any
	while(j<n2){
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSortUtil(vector<int> &arr, int l, int r){
	// Till l is less than r, we split, split and merge
	if (l<r){
		int m = l+(r-l)/2;
		mergeSortUtil(arr, l, m);
		mergeSortUtil(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

void mergeSort(vector<int> a){
	// Merge Sort is Divide and Conquer algorithm. 
	// It divides input array in two halves, calls itself for the two halves and then merges the two sorted halves.
	// The merge() function is used for merging two halves. The merge(arr, l, m, r) is key process that assumes 
	// that arr[l..m] and arr[m+1..r] are sorted and merges the two sorted sub-arrays into one.
	vector<int> arr = a;
	mergeSortUtil(arr, 0, arr.size()-1);
	printArr(arr);
}

void bubbleSort(vector<int> a){
	// This works by repeatedly swapping the adjacent elements if they are in wrong order. After every iteration, we 
	// push the maximum element of the unsorted part to the sorted part. We start with the unsorted array and 
	// in the first pass we figure out the maximum element by repeatedly comparing adjacent elements. This will
	// go towards the ending which will be out sorted part of the array. Next pass, we only have to compare
	// adjacent elements till n-1 elements since we know the maximum is stored at the nth index. This pass, we will 
	// store the second max at n-1 th index and thus the array is sorted.
	// Note that we don't stop after n iterations. If, in any iteration, we don't change/swap any two elements,
	// then we know that the array is already sorted and we can stop there. We use a flag variable to do this.
	// Due to this, the best case complexity (when the array is already sorted) reduces to O(n) since nothing 
	// is changed and in only one pass we can stop.

	vector<int> arr = a;
	int n = arr.size();

	// Iterate for 
	for(int i=0; i<n; i++){
		bool swapped = false;
		for(int j=0; j<n-i-1; j++){
			if(arr[j]>arr[j+1]){
				swap(&arr[j], &arr[j+1]);
				swapped = true;
			}
		}
    // Uncomment to see how the array changes after every iteration.    
		// printArr(arr);
		if(swapped == false)
			break;
	}

	printArr(arr);
}

void insertionSort(vector<int> a){
	// We have to pick elements one by one and 'insert' them at their correct place in the already sorted sequence.
	// The only problem is how to insert elements at the correct place in the sorted array. 
	// Firstly, we start with an unsorted array and then gradually we will convert it to a sorted array.
	// We will start with the second element and compare it with the first element, and insert both of them in their 
	// correct place. We now have a sorted array of 2 elements and an unsorted array of n-1 elements. 
	// So, generally, we will pick all the elements from i= 1 to n, one by one and compare it will all the elements
	// before it from j=i-1 to j>=0. Also, we know that this sub array which j is pointing to is sorted since we have
	// been keeping all the elements sorted here. So, we iterate j=i-1 to j>=0 and try to figure out if this 
	// is the correct place to put arr[i]? If yes, then we put it but if not we keep shifting the elements since
	// we know arr[i] would be put somewhere later in the sorted array. Also, just to ensure that we don't lose 
	// the element stored in arr[i] and we don't replace it, we would keep that in a variable called 'key' and
	// now even though we would replace/shift the a[i-1]th item to arr[i] in case if it's not the correct place,
	// then we won't lose arr[i] since we have it in the 'key' variable.


	vector<int> arr = a;
	int n = arr.size();

	// Iterate over the array from i=1 to n-1	
	for(int i=1;i<n;i++){

		// Initialize j to move from i-1 to j>=0 (condition in while loop)
		int j = i-1;

		// Make sure we have stored the arr[i] in 'key' so that we don't lose it.
		int key = arr[i];

		// Keep searching for the correct place of the 'key' or arr[i]. Loop till the elements are largers than key
		while(j>=0 && arr[j]>key){

			// and shift the elements forward (Thank god we saved arr[i] in a variable called 'key' already!)
			arr[j+1] = arr[j];
			j--;
		}
		// Found the correct place of 'key' which is j+1, so storing it.
		arr[j+1] = key;

		// Uncomment to see how the array changes after every iteration.    
		// printArr(arr);
	}

	printArr(arr);
}

void selectionSort(vector<int> a){
	// The array is divided into two parts sorted and unsorted. We start with the unsorted part
	// having n elements and sorted part having 0 elements. Then we find the minimum element 
	// from the unsorted part and move it to the first index which is the first element of the sorted array.
	// Then we iterate over the rest of the unsorted array to find the minimum element and then that would the 
	// second minimum element and this is how we will increase the size of the sorted array to n and 
	// decrease the size of unsorted array to 0. We now get a sorted array.
	
	vector<int> arr = a;
	int n = arr.size();
	
	// Iterate over the array to get the minimum element from the unsorted part.
	// After n iterations, the unsorted part would become zero and sorted part will have all the n elements.
	for(int i=0; i<n; i++){

		// Set the minimum index as i
		int min_index = i;

		// Iterate over the unsorted list to find the real minimum index from the unsorted part.
		for(int j=i+1; j<n; j++){
			if(arr[j] < arr[min_index]){
				min_index = j;
			}
		}

		// Swap the minimum element from the unsorted list to the sorted list.
    	swap(arr[min_index], arr[i]);
    
	// printArr(arr);
	}

	printArr(arr);
}


int main() 
{
	vector<int> arr = {65, 11, 35, 12, 9};
	selectionSort(arr);
	insertionSort(arr);
	bubbleSort(arr);
	mergeSort(arr);
	quickSort(arr);

	// A⟶B⟶C
	//	   ⤷D⤴ 
	vector <vector<int>> grid = { {0,1,0,0}, {0,0,1,1}, {0,0,0,0}, {0,0,1,0}};
	topologicalSort(grid);

  return 0; 
} 
