/* 
Harshit Gupta | 20th October, 2018

C++ program for Minimum Number of Platforms Required for a Railway/Bus Station
    Given arrival and departure times of all trains that reach a railway station, find the minimum number of platforms 
    required for the railway station so that no train waits.
    We are given two arrays which represent arrival and departure times of trains that stop

Solution: We can use direct addresss table to solve this. 
    Just keep on marking the arrival and departure. The number of consecutive arrivals 
    would be the minimum number of platforms required. 
    NOTE: This doesn't handle the case when both the train arrives and depart at the same time.

Time Complexity: O(n)

*/

#include <bits/stdc++.h>
using namespace std; 

void findMaxPlatforms(vector<int> arr, vector<int> dep){
    vector<char> times(2400,'x');
    
    for(int i=0;i<arr.size();i++){
        times[arr[i]] = 'a';
    }
    
    for(int i=0;i<dep.size();i++){
        times[dep[i]] = 'd';
    }
    
    int a=0,d=0,a_max=0;
    for(int i=0;i<2400;i++){
        if(times[i]=='a'){
            a++;
        }
        else if(times[i]=='d'){
            a=0;
        }

        if(a_max < a){
            a_max++;
        }
    }
    cout<<a_max<<endl;

}

int main(){
    vector<int> arr = {900, 940, 950, 1100, 1500, 1800}; 
    vector<int> dep = {910, 1200, 1120, 1130, 1900, 2000};
    findMaxPlatforms(arr,dep);
    return 0;
}