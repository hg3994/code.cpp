

/*

Harshit Gupta | 2nd July, 2021
---------------------------------

Given a characters array tasks, representing the tasks a CPU needs to do, where each letter represents 
    a different task. Tasks could be done in any order. Each task is done in one unit of time. For each 
    unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period between two same tasks 
(the same letter in the array), i.e., that there must be at least n units of time between any two same tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.

EXAMPLES:

Example 1:
    Input: tasks = ["A","A","A","B","B","B"], n = 2
    Output: 8
    Explanation: 
    A -> B -> idle -> A -> B -> idle -> A -> B
    There is at least 2 units of time between any two same tasks.

Example 2:
    Input: tasks = ["A","A","A","B","B","B"], n = 0
    Output: 6
    Explanation: On this case any permutation of size 6 would work since n = 0.

Example 3:
    Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
    Output: 16
    Explanation: 
    One possible solution is
    A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A



Solution: 
    1. The total number of CPU intervals we need consists of busy and idle slots. Number of busy slots is 
        defined by the number of tasks to execute: len(tasks). The problem is to compute a number of idle slots.
    2. Maximum possible number of idle slots is defined by the frequency of the most frequent task: 
        idle_time <= (f_max - 1) * n.
    3. This maximum idle time could be decreased because one doesn't need to keep the CPU idle during 
        cooling periods. It could execute different tasks as well.
    4. Pick the elements in the descending order one by one. At each step, decrease the idle time by 
        min(f_max - 1, f) where f is a current frequency. Remember, that idle_time is greater or equal to 0.
    5. Min of fmax-1 and freq[i] because at max we can fill fmax-1 from this task, not more than that.



    ["A","A","A","B","B","B"], n = 2
    freq = (3,3), fmax=3

    A--A--A, idle_time=(3-1)*2 = 4
    AB-AB-AB, idle_time= 4-min(3-1,3) = 2

    required Slots: 6+2= 8
    --------------------------------------------------------
        
    ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
    freq = (1,1,1,1,1,1,6), fmax = 6

    A--A--A--A--A--A, idle_time=(6-1)*2 = 10
    AB-A--A--A--A--A, idle_time= 10-min(6-1, 1) = 9
    ABCA--A--A--A--A, idle_time=  9-min(6-1, 1) = 8
    ABCAD-A--A--A--A, idle_time=  8-min(6-1, 1) = 7
    ABCADEA--A--A--A, idle_time=  7-min(6-1, 1) = 6
    ABCADEAF-A--A--A, idle_time=  6-min(6-1, 1) = 5
    ABCADEAFGA--A--A, idle_time=  5-min(6-1, 1) = 4

    required Slots: 12+4= 16
    --------------------------------------------------------
TC: 
SC:

Paradigm:
---
  NOTE: #Agoda

*/
    
    
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        if(n==0)
            return tasks.size();
        
        vector<int> freq(26,0);
        for(auto c: tasks){
            freq[c-'A']++;
        }
        
        sort(freq.begin(), freq.end());
        
        int fmax = freq[25];
        int idle_time = (fmax - 1)*n;
        
        for(int i=freq.size()-2; i>=0 && idle_time>0; --i){
            idle_time -= min(fmax-1, freq[i]);
            if(idle_time <= 0){
                idle_time = 0;
                break;
            }
        }
        return idle_time+tasks.size();
    }
};


// Another solution:
// 1. First count the number of occurrences of each element.
// 2. Let the max frequency seen be M for element E
// 3. We can schedule the first M-1 occurrences of E, each E will be followed by at least N CPU cycles in between successive schedules of E
// 4. Total CPU cycles after scheduling M-1 occurrences of E = (M-1) * (N + 1) // 1 comes for the CPU cycle for E itself
// 5. Now schedule the final round of tasks. We will need at least 1 CPU cycle of the last occurrence of E. If there are multiple tasks with frequency M, they will all need 1 more cycle.
// 6. Run through the frequency dictionary and for every element which has frequency == M, add 1 cycle to result.
// 7. If we have more number of tasks than the max slots we need as computed above we will return the length of the tasks array as we need at least those many CPU cycles.

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char,int>mp;
        int count = 0;
        for(auto e : tasks) {
            mp[e]++;
            count = max(count, mp[e]);
        }
        
        int ans = (count-1)*(n+1);
        for(auto e : mp) 
            if(e.second == count) 
                ans++;

        return max((int)tasks.size(), ans);
    }
};