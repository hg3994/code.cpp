/* 
Harshit Gupta | 6th November, 2018

https://ide.geeksforgeeks.org/ykfb0bHQ5x
https://www.geeksforgeeks.org/merge-one-array-of-size-n-into-another-one-of-size-mn/

C++ program for "There are two sorted arrays. First one is of size m+n containing 
    only m elements. Another one is of size n and contains n elements. 
    Merge these two arrays into the first array of size m+n such that the output is sorted."

Solution:   1) Move m elements of longArr[] to end. Call it longArr_sorted[].
            2) Start from nth element of the longArr_sorted[] and 0th 
                element of shortArr[] and merge them into longArr_sorted[].

Time Complexity: O(m+n)

Space Complexity: O(m+n)
*/

#include <bits/stdc++.h>
using namespace std; 

// Assuming -1 is filled for the places where element is not available
#define NA -1 

// Helper Function to print the array
void printArr(int arr[], int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

// Move the numbers in the longArr towards the End and fill the front with NAs.
// We do this and get a new longArr_sorted from it.
void moveNumbersToEndInLongArr(int *longArr, int *longArr_sorted, int m, int n){
    
    // Copying 'n' NAs in the front
    for(int i=0;i<n;i++)
        longArr_sorted[i] = NA;
        
    int iterator_to_add_numbers=n;
    
    // Copying the remaining 'm' numbers in the end.
    for(int i=0;i<m+n;i++){
        if(longArr[i]!=NA){
            longArr_sorted[iterator_to_add_numbers++] = longArr[i];
        }
    }
}

// Merges two sorted arrays 
//    one with size m+n having m elements and n NULLS (sorted)
//    other with size n having n elements (sorted)
void mergeTwoSortedArrays(int *longArr, int *shortArr, int m, int n){
    int longArr_sorted[m+n];

    // gets the numbers moved towards the end and NULLS towards starting in the longArr
    moveNumbersToEndInLongArr(longArr, longArr_sorted, m ,n);
    
    // printArr(longArr_sorted, m+n);
    
    // An iterator for the NULLS starting in longArr, 
    // one for the numbers in longArr and another for the shortArr
    int iterator_of_NULLS_in_longArr_sorted = 0;
    int iterator_of_numbers_in_longArr_sorted = n;
    int iterator_of_shortArr = 0;
    
    // Till I reach the end of the longArr
    while(iterator_of_NULLS_in_longArr_sorted < m+n){
        
        // If the number in shortArr are smaller
        // OR we don't have numbers left to process in longArr,
        // then we copy the number from shortArr to the appropriate place and move the iterators.
        if(longArr_sorted[iterator_of_numbers_in_longArr_sorted] > shortArr[iterator_of_shortArr] 
            || iterator_of_numbers_in_longArr_sorted==m+n){
            longArr_sorted[iterator_of_NULLS_in_longArr_sorted] = shortArr[iterator_of_shortArr];
            iterator_of_shortArr++;
            iterator_of_NULLS_in_longArr_sorted++;
        }
        
        // If the number in shortArr are larger,
        // Then we replace NULLS in front from the number from longArr's end
        // and move the iterators to the appropriate place
        else{
            longArr_sorted[iterator_of_NULLS_in_longArr_sorted] = longArr_sorted[iterator_of_numbers_in_longArr_sorted];
            iterator_of_NULLS_in_longArr_sorted++;
            iterator_of_numbers_in_longArr_sorted++;
        }
    }
    
    printArr(longArr_sorted, m+n);
}

int main() 
{
    int longArr[] = {NA, 2, 8, NA, NA, 13, NA, 15, 20};
    int shortArr[] = {5, 7, 9, 25};
    int size_longArr = sizeof(longArr)/sizeof(longArr[0]);
    int size_shortArr = sizeof(shortArr)/sizeof(shortArr[0]);
    mergeTwoSortedArrays(longArr, shortArr, size_longArr-size_shortArr, size_shortArr);
    return 0; 
} 
