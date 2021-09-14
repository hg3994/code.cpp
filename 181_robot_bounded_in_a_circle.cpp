
/*

Harshit Gupta | 16th August, 2021
---------------------------------

Problem Statement:
    On an infinite plane, a robot initially stands at (0, 0) and faces north. The robot can receive one of three instructions:

    "G": go straight 1 unit;
    "L": turn 90 degrees to the left;
    "R": turn 90 degrees to the right.
    The robot performs the instructions given in order, and repeats them forever.

    Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.

 

Example 1:
    Input: instructions = "GGLLGG"
    Output: true
    Explanation: The robot moves from (0,0) to (0,2), turns 180 degrees, and then returns to (0,0).
    When repeating these instructions, the robot remains in the circle of radius 2 centered at the origin.

Example 2:
    Input: instructions = "GG"
    Output: false
    Explanation: The robot moves north indefinitely.

Example 3:
    Input: instructions = "GL"
    Output: true
    Explanation: The robot moves from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ...

https://leetcode.com/problems/robot-bounded-in-circle/
------

Solution: 
        If after the iteration, the robot comes at the center again OR
        OR is somewhere else but not facing in the initial direction (North), then it will be confined in a circle
        of some size and keep moving there infinitely.

    TC: O(n)
    SC: O(1)

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/



class Solution {
public:
    bool isRobotBounded(string s) {
        int x=0;
        int y=0;
        int dir=0; // 0-> N, 1->E, 2->S, 3->W (clockwise)
        
        for(int i=0;i< s.size(); i++){
            if(s[i] == 'G')
                if(dir == 0)
                    y++;
                else if (dir == 1)
                    x++;
                else if (dir == 2)
                    y--;
                else
                    x--;
            else if (s[i] == 'L')
                if(dir == 0)
                    dir=3;
                else
                    dir--;
            else // move right
                if(dir==3)
                    dir=0;
                else
                    dir++;
        }
        // If after the whole walking, you come at the center again, OR
        // it's not at the center but has a different direction then init, then it will move in a loop
        // otherwise, it will go out of the circle.
        if(x == 0 && y == 0)
            return true;
        else if (dir != 0)
            return true;
        else
            return false;
    }
};